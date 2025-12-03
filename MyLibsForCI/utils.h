/**
 * Funciones utiles.
 */

typedef struct  {
   byte initialized;
   byte oldY;
   byte oldP;

   const byte *bitmap;
   const byte *mask;

   byte rows;
   byte cols;

   byte transparent;
   byte invert;
} Sprite;

/**
 * @brief Resetea el progreso de ProgessBarHLR, pone el valor antiguo a 0.
 */
void resetHLRBar();

void progressBarHLR(byte p, int yi, int yf, int percent);

/**
 * @brief Resetea el progreso de ProgessBarHRL, pone el valor antiguo a 0.
 */
void resetHRLBar();

void progressBarHRL(byte p, int yi, int yf, int percent);

/**
 * @brief Resetea el progreso de ProgessBarHVDU, pone el valor antiguo a 0.
 */
void resetVDUBar();

void progressBarVDU(byte pi, byte pf, int yi, int yf, int percent);

/**
 * @brief Elimina el sprite 'spr', si no ha sido imprimido no hace nada.
 * @param spr Puntero hacia un struct Sprite que contiene la información del sprite, utilizar con '&sprite'.
 */
void removeSprite(Sprite *spr);

/**
 * @brief Elmina de forma 'inteligente' parte del sprite, utilizalo si quieres eliminar solo una parte del sprite si lo has movido.
 * @param newP La nueva pagina donde esta el sprite
 * @param newY La nueva columna Y donde esta el sprite
 * @param spr Puntero hacia un struct Sprite que contiene la información del sprite, utilizar con '&sprite'.
 */
void smartRemoveSprite(byte newP, byte newY, Sprite *spr);

/**
 * @brief Pinta el sprite 'spr' empezando en la pagina 'p' y columna 'y', estas dos son la esquina superior izquierda del sprite.
 * @param p La pagina donde pintar el sprite
 * @param y La columna Y donde pintar el sprite
 * @param spr Puntero hacia un struct Sprite que contiene la información del sprite, utilizar con '&sprite'.
 */
void paintSprite(byte p, int y,  Sprite *spr);

/**
 * @brief Mueve el sprite spr, si no esta inicializado lo imprime en la nueva posición, si ya lo esta elimina de forma 'inteligente' el antiguo y imprime el sprite en la nueva posición.
 * @param spr Puntero hacia un struct Sprite que contiene la información del sprite, utilizar con '&sprite'.
 * @param newP La nueva pagina donde mover el sprite
 * @param newY La nueva columna Y donde mover el sprite
 */
void moveSprite(Sprite *spr, byte newP, byte newY);

/**
 * @brief Para timers, si tienes un vector con el primer elemento siendo decimales y el segundo siendo segundos, este te devuelve la traducción a decimales.
 * @param t un vector de dos elementos que contiene decimales y segundos.
 */
unsigned long secToDeci(int t[2]);