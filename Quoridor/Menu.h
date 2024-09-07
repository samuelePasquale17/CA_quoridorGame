#ifndef MENU_H 
#define MENU_H

#include <stdint.h>

#define BTN_UP 0
#define BTN_DOWN 1


typedef struct menu_s {
	int posCursore;
} Menu;


void MENUinit(void);
void MENUsetPosCursore(int pos, int menu_num); //  [UP, DOWN]

void MENUdisegnaMenuSelBoard(int num_menu);
void MENUdisegnaBTNmenu1(int daCancellare, int isSelezionato, int num_menu);
void MENUdisegnaBTNmenu2(int daCancellare, int isSelezionato, int num_menu);
void MENUdisegnaQuadratoBTN(int x, int y, uint16_t colore);
void MENUdisegnaGiocatoreConCoordinate(int x, int y, uint16_t GUIcolore);

int MENUgetPosCursore(int num_menu);

#endif
