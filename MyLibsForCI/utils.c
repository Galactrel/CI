
#include <xc.h>
#include "GLCD.h"
#include "utils.h"


int old_HLRpercent = 0;
void resetHLRBar(){
	old_HLRpercent = 0;
}
void progressBarHLR(byte p, int yi, int yf, int percent) {
   if (percent < 0) percent = 0;
   if (percent > 100) percent = 100;

   // Limpiamos un trozo de la barra anterior si hace falta
   if (percent < old_HLRpercent) 
      clearGLCD(p, p, (yf * percent/100), (yf * old_HLRpercent/100));
   // Si el nuevo porcentaje es mayor, rellenamos la diferencia.
   else if (percent != old_HLRpercent) {
      for (int i = yi; i < (yf * percent/100); i++) {
         writeByte(p, i, 0xFF); 
      }
   }
	old_HLRpercent = percent;
}

int old_HRLpercent = 0;

void resetHRLBar(){
	old_HRLpercent = 0;
}

void progressBarHRL(byte p, int yi, int yf, int percent) {
   if (percent < 0) percent = 0;
   if (percent > 100) percent = 100;

   // Limpiamos un trozo de la barra anterior si hace falta
   if (percent < old_HRLpercent) 
      clearGLCD(p, p, (yf * (100-old_HRLpercent)/100), (yf * (100-percent)/100));
   // Si el nuevo porcentaje es mayor, rellenamos la diferencia.
   else if (percent != old_HRLpercent) {
      for (int i = yf; i > (yf * (100-percent)/100); i--) {
         writeByte(p, i, 0xFF); 
      }
   }
	old_HRLpercent = percent;
}

int old_VDUpercent = 0;

void resetVDUBar() {
	old_VDUpercent = 0;
}

void progressBarVDU(byte pi, byte pf, int yi, int yf, int percent) {
   if (percent == old_VDUpercent) return;

   if (percent < 0) percent = 0;
   if (percent > 100) percent = 100;

   byte newPixels = (1+pi-pf)*8*percent/100;
   byte oldPixels = (1+pi-pf)*8*old_VDUpercent/100;

   // Limpiamos un trozo de la barra anterior si hace falta
   if (newPixels < oldPixels)  {
		for (int px = newPixels; px < oldPixels; px++) {
			int page = pi - (px / 8);
			int b = (7 - (px % 8));

			for (int y = yi; y <= yf; y++) {
				byte v = readByte(page, y);
				v &= ~(1 << b);
				writeByte(page, y, v);
			}
		}
   } 
   else {
      byte pageStart = pi;
      byte pageEnd   = (pi-(newPixels/8));
      // Rellenamos las paginas completas (Aquellas que tengan pintados los ocho pixeles).
      for (byte p = pageStart; p > pageEnd ; --p) {
         for (byte y = yi; y <= yf; y++) {
            writeByte(p, y, 0xFF);
         }
      }
   }
   // Rellenamos la pagina faltante como toque:
   if (newPixels%8 != 0) {
      for (int y = yi; y <= yf; y++) {
         byte mask = (0xFF << (8-newPixels%8));
         byte page = pi-(newPixels/8);
         writeByte(page, y, mask);
      }
   }
   old_VDUpercent = percent;
}

void removeSprite(Sprite *spr) { 
   if (!spr->initialized) return;   
   int p = spr->oldP;
   int y = spr->oldY;
   for (byte r = 0; r < spr->rows; r++) {
      byte page = p+r;
      for (byte c = 0; c < spr->cols; c++) {
         byte s = spr->mask[r * spr->cols + c];
         byte v = readByte(page, y);
         v &= ~s;
         writeByte(page, y+c, v);
      }
   }
   // Actualizamos los datos
   spr->initialized = 0;
   spr->oldP = -1;
   spr->oldY = -1;
}

void smartRemoveSprite(byte newP, byte newY, Sprite *spr) {
   if (!spr->initialized) return;

   byte rows = spr->rows;
   byte cols = spr->cols;

   byte oldP = spr->oldP;
   byte oldY = spr->oldY;

   int difY = newY-oldY;

   // Si no hay movimiento, no hacemos nada.
   if (difY == 0) return;

   // Si el movimiento es demasiado grande, borramos el sprite completo.
   if (difY >= cols || difY <= -cols) {
      removeSprite(spr);
      return;
   }

   // Movimiento hacia la derecha
   if (difY > 0) {
      for (byte r = 0; r < rows; r++) {
         byte p = oldP + r;
         if (p > 7) continue;

         for (int c = 0; c < difY; c++) {
            int posY = oldY + c;
            if (posY < 0 || posY > 127) continue;

            int cMask = c;
            if (spr->invert) 
					cMask = cols - 1 - c;

            byte m = spr->mask[r*cols+cMask];
            byte v = readByte(p, posY);
            v &= ~m;
            writeByte(p, posY, v);
         }
      }
   }
   
   // Movimiento hacia la izquierda
   else { // difY < 0
      int start = oldY + cols + difY;
      int end   = oldY + cols - 1; 
      for (byte r = 0; r < rows; r++) {
         byte p = oldP + r;
         if (p > 7) continue;

         for (int posY = start; posY <= end; posY++) {
            int c = posY + - oldY;
            if (posY < 0 || posY > 127) continue;
            if (c < 0 || c > cols) continue;

            int cMask = c;
            if (spr->invert) 
					cMask = cols - 1 - c;

            byte m = spr->mask[r*cols+cMask];
            byte v = readByte(p, posY);
            v &= ~m;
            writeByte(p, posY, v);
         }
      }
   }
   spr->initialized = 0;
}

void paintSprite(byte p, int y,  Sprite *spr) {
   for (byte r = 0; r < spr->rows; r++) {
      byte page = p+r;
      if (page > 7) continue;
      for (byte c = 0; c < spr->cols; c++) {
         int posY;
         if (spr->invert)  
            posY = y+(spr->cols-1-c);
         else 
            posY = y+c;
         if (posY > 127 || posY < 0) continue;
         byte bg = 0x00;
         if (spr->transparent) bg = readByte(page, posY);
         byte print = bg | spr->bitmap[r*(spr->cols) + c];
         writeByte(page, posY, print);
      }
   }
   // Actualizamos los datos
   spr->initialized = 1;
   spr->oldP = p;
   spr->oldY = y;
}


void moveSprite(Sprite *spr, byte newP, byte newY) {
   if (spr->oldP == newP && spr->oldY == newY) return;

   // Borramos el sprite anterior
   if (spr->initialized) 
      smartRemoveSprite(newP, newY, spr);
   
   // Dibujamos el nuevo sprite
   paintSprite(newP, newY, spr);
}

unsigned long secToDeci(int t[2]) {
	return ((unsigned long)t[1] * 10UL) +  // segundos -> decimas
          ((unsigned long)t[0]);          // decimas
}
