/**
 * Llibreria per controlar les pulsacións de botons conectats als pins del micro controlador PIC18F45K22
 */
#include <xc.h>
#include "buttons.h"
#define _XTAL_FREQ 8000000  



byte edge_RA[8] = {0};
byte edge_RB[8] = {0};
byte edge_RC[8] = {0};
byte edge_RD[8] = {0};
byte edge_RE[3] = {0};

void configButton(char port, byte pin, byte raisingEdge){
   switch (port)
   {
   case 'A':
      ANSELA &= ~(1<<pin);
      TRISA  |=  (1<<pin);
      edge_RA[pin] = raisingEdge;
      break;
   case 'B':
      ANSELB &= ~(1<<pin);
      TRISB  |=  (1<<pin);
      edge_RB[pin] = raisingEdge;
      break;
   case 'C':
      ANSELC &= ~(1<<pin);
      TRISC  |=  (1<<pin);
      edge_RC[pin] = raisingEdge;
      break;
   case 'D':
      ANSELD &= ~(1<<pin);
      TRISD  |=  (1<<pin);
      edge_RD[pin] = raisingEdge;
      break;
   case 'E':
      ANSELE &= ~(1<<pin);
      TRISE  |=  (1<<pin);
      edge_RE[pin] = raisingEdge;
      break;
   default:
      break;
   }
}



// Detectores del puerto A:
byte old_RA[8] = {0};
int inputDetectorRA(byte pin) {
	int res = 0;
   int pin_val = ((PORTA >> pin) & 1);
	if (pin_val == edge_RA[pin] && pin_val != old_RA[pin]) {
		__delay_ms(15);
      pin_val = ((PORTA >> pin) & 1);
		if (pin_val == edge_RA[pin]) res = 1;
	}
	old_RA[pin] = pin_val;
	return res;
}

// Detectores del puerto B:
byte old_RB[8] = {0};
int inputDetectorRB(byte pin) {
	int res = 0;
   int pin_val = ((PORTB >> pin) & 1);
	if (pin_val == edge_RB[pin] && pin_val != old_RB[pin]) {
		__delay_ms(15);
      pin_val = ((PORTB >> pin) & 1);
		if (pin_val == edge_RB[pin]) res = 1;
	}
	old_RB[pin] = pin_val;
	return res;
}

// Detectores del puerto C:
byte old_RC[8] = {0};
int inputDetectorRC(byte pin) {
	int res = 0;
   int pin_val = ((PORTC >> pin) & 1);
	if (pin_val == edge_RC[pin] && pin_val != old_RC[pin]) {
		__delay_ms(15);
      pin_val = ((PORTC >> pin) & 1);
		if (pin_val == edge_RC[pin]) res = 1;
	}
	old_RC[pin] = pin_val;
	return res;
}

// Detectores del puerto D:
byte old_RD[8] = {0};
int inputDetectorRD(byte pin) {
	int res = 0;
   int pin_val = ((PORTD >> pin) & 1);
	if (pin_val == edge_RD[pin] && pin_val != old_RD[pin]) {
		__delay_ms(15);
      pin_val = ((PORTD >> pin) & 1);
		if (pin_val == edge_RD[pin]) res = 1;
	}
	old_RD[pin] = pin_val;
	return res;
}

// Detectores del puerto E:
byte old_RE[3] = {0};
int inputDetectorRE(byte pin) {
	int res = 0;
   int pin_val = ((PORTE >> pin) & 1);
	if (pin_val == edge_RE[pin] && pin_val != old_RE[pin]) {
		__delay_ms(15);
      pin_val = ((PORTE >> pin) & 1);
		if (pin_val == edge_RE[pin]) res = 1;
	}
	old_RE[pin] = pin_val;
	return res;
}