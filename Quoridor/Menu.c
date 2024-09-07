#include "Menu.h"
#include "../GLCD/GLCD.h"


#define ROSSO 0
#define BLU 1

// menu 1
#define X_STR_MENU_1 35
#define Y_STR_MENU_1 35

#define X_BTN_1_MENU 36
#define Y_BTN_1_MENU 138

#define X_BTN_2_MENU 36
#define Y_BTN_2_MENU 206

#define LEN_LATO_QUADRATO_PX 32

#define INTESTAZIONE_MENU_SPESSORE 80


#define MENU1 1
#define MENU2 2



Menu menu1;
Menu menu2;


void MENUinit() {
	menu1.posCursore = BTN_UP;
	menu2.posCursore = BTN_UP;
}


void MENUsetPosCursore(int pos, int menu_num) {
	int numMenu2;
	if (menu_num == MENU1) {
		switch (pos) {
			case BTN_UP:
				if (menu1.posCursore != BTN_UP) {
					menu1.posCursore = BTN_UP;

					MENUdisegnaBTNmenu2(0, 0, 1);	// si aggiorna GUI MENU
					MENUdisegnaBTNmenu1(0, 1, 1);
				}
			break;
			case BTN_DOWN:
				if (menu1.posCursore != BTN_DOWN) {
					menu1.posCursore = BTN_DOWN;
					MENUdisegnaBTNmenu1(0, 0, 1);	// si aggiorna GUI MENU
					MENUdisegnaBTNmenu2(0, 1, 1);
				}
			break;
			default:
				// - default -
			break;
		}
	} else if (menu_num == MENU2) {
			if (menu1.posCursore == BTN_UP) {
				numMenu2 = 2; // menu single player
			} else if (menu1.posCursore == BTN_DOWN) {
				numMenu2 = 3; // multiplayer
			}
			switch (pos) {
			case BTN_UP:
				if (menu2.posCursore != BTN_UP) {
					menu2.posCursore = BTN_UP;

					MENUdisegnaBTNmenu2(0, 0, numMenu2);	// si aggiorna GUI MENU
					MENUdisegnaBTNmenu1(0, 1, numMenu2);
				}
			break;
			case BTN_DOWN:
				if (menu2.posCursore != BTN_DOWN) {
					menu2.posCursore = BTN_DOWN;
					MENUdisegnaBTNmenu1(0, 0, numMenu2);	// si aggiorna GUI MENU
					MENUdisegnaBTNmenu2(0, 1, numMenu2);
				}
			break;
			default:
				// - default -
			break;
		}
	}
}



void MENUdisegnaMenuSelBoard(int num_menu) {
	int i;
	LCD_Clear(White);
	
	if (num_menu == MENU1) {
		for (i = 0; i < INTESTAZIONE_MENU_SPESSORE; i++) {
			LCD_DrawLine(0, 0+i, 240, 0+i, Blue);
		}
		
		GUI_Text(X_STR_MENU_1 + 5, Y_STR_MENU_1, (uint8_t *) "Select the GAME MODE", White, Blue);
		
		MENUdisegnaBTNmenu1(0, 1, 1);
		MENUdisegnaBTNmenu2(0, 0, 1);
		
	} else if (num_menu == MENU2) {
		if (menu1.posCursore == BTN_UP) {
			// scelto single board
			for (i = 0; i < INTESTAZIONE_MENU_SPESSORE; i++) {
				LCD_DrawLine(0, 0+i, 240, 0+i, Blue);
			}
			
			GUI_Text(X_STR_MENU_1 + 40, Y_STR_MENU_1, (uint8_t *) "SINGLE BOARD", White, Blue);
			GUI_Text(X_STR_MENU_1 - 18, Y_STR_MENU_1 + 20, (uint8_t *) "Select the opposite player", White, Blue);
			
			MENUdisegnaBTNmenu1(0, 1, 2); // bottoni in base al menu
			MENUdisegnaBTNmenu2(0, 0, 2);
		} else if (menu1.posCursore == BTN_DOWN){
			// scelto two board
			for (i = 0; i < INTESTAZIONE_MENU_SPESSORE; i++) {
				LCD_DrawLine(0, 0+i, 240, 0+i, Blue);
			}
			
			GUI_Text(X_STR_MENU_1 + 50, Y_STR_MENU_1, (uint8_t *) "TWO BOARDS", White, Blue);
			GUI_Text(X_STR_MENU_1 + 15, Y_STR_MENU_1 + 20, (uint8_t *) "Select your player", White, Blue);
			
			MENUdisegnaBTNmenu1(0, 1, 3);
			MENUdisegnaBTNmenu2(0, 0, 3);
		}
	}
}


void MENUdisegnaBTNmenu1(int daCancellare, int isSelezionato, int num_menu) {
	uint16_t coloreTesto;
	
	
	if (isSelezionato == 1) {
		// disegnare giocatore
		MENUdisegnaGiocatoreConCoordinate(X_BTN_1_MENU, Y_BTN_1_MENU, Red);
		coloreTesto = Red;
	} else {
		MENUdisegnaGiocatoreConCoordinate(X_BTN_1_MENU, Y_BTN_1_MENU, White);
		coloreTesto = Black;
	}

	
	if (daCancellare == 1) coloreTesto = White;
	
	if (num_menu == 1) {
		// game mode
		GUI_Text(X_BTN_1_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_1_MENU + 11, (uint8_t *) "SINGLE BOARD", coloreTesto, White);
	} else if (num_menu == 2) {
		// single board menu
		GUI_Text(X_BTN_1_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_1_MENU + 11, (uint8_t *) "HUMAN", coloreTesto, White);
	} else if (num_menu == 3) {
		// two boards menu
		GUI_Text(X_BTN_1_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_1_MENU + 11, (uint8_t *) "HUMAN", coloreTesto, White);
	}
}


void MENUdisegnaBTNmenu2(int daCancellare, int isSelezionato, int num_menu) {
	uint16_t coloreTesto;
	
	
	if (isSelezionato == 1) {
		// disegnare giocatore
		MENUdisegnaGiocatoreConCoordinate(X_BTN_2_MENU, Y_BTN_2_MENU, Red);
		coloreTesto = Red;
	} else {
		MENUdisegnaGiocatoreConCoordinate(X_BTN_2_MENU, Y_BTN_2_MENU, White);
		coloreTesto = Black;
	}

	
	if (daCancellare == 1) coloreTesto = White;
	
	if (num_menu == 1) {
		// game mode
		GUI_Text(X_BTN_2_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_2_MENU + 11, (uint8_t *) "TWO BOARDS", coloreTesto, White);
	} else if (num_menu == 2) {
		// single board menu
		GUI_Text(X_BTN_2_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_2_MENU + 11, (uint8_t *) "NPC", coloreTesto, White);
	} else if (num_menu == 3) {
		// two boards menu
		GUI_Text(X_BTN_2_MENU + LEN_LATO_QUADRATO_PX*2, Y_BTN_2_MENU + 11, (uint8_t *) "NPC", coloreTesto, White);
	}
}


void MENUdisegnaQuadratoBTN(int x, int y, uint16_t colore) {
	LCD_DrawLine(x, y, x+LEN_LATO_QUADRATO_PX, y, colore); // lato superiore
	LCD_DrawLine(x, y+LEN_LATO_QUADRATO_PX, x+LEN_LATO_QUADRATO_PX, y+LEN_LATO_QUADRATO_PX, colore); // lato inferiore
	LCD_DrawLine(x, y, x, y+LEN_LATO_QUADRATO_PX, colore); // lato sinistro
	LCD_DrawLine(x+LEN_LATO_QUADRATO_PX, y, x+LEN_LATO_QUADRATO_PX, y+LEN_LATO_QUADRATO_PX, colore); // lato destro
}


void MENUdisegnaGiocatoreConCoordinate(int x, int y, uint16_t GUIcolore) {
	int x1, y1, x2, y2, x3, y3, x4, y4, i;

	
	x1 = x;
	y1 = y;
	
	x2 = x1 + LEN_LATO_QUADRATO_PX/2;
	y2 = y1;
	
	x3 = x1 + LEN_LATO_QUADRATO_PX/2;
	y3 = y1;
	
	x4 = x1 + LEN_LATO_QUADRATO_PX;
	y4 = y1;
	

	
	// triangolo piccolo superiore
	for (i = 0; i <= LEN_LATO_QUADRATO_PX/4; i++) {
		LCD_DrawLine(x1, y1+i, x2, y2+i, White); // x1 - x2
		LCD_DrawLine(x2, y2+i, x3, y3+i, GUIcolore); // x2 - x3
		LCD_DrawLine(x3, y3+i, x4, y4+i, White); // x3 - x4
		
		if (i % 2 == 0) {
			x2--;
			x3++;
		}
	}
	
	// triangolo piccolo inferiore
	for (; i <= LEN_LATO_QUADRATO_PX/2; i++) {
		LCD_DrawLine(x1, y1+i, x2, y2+i, White); // x1 - x2
		LCD_DrawLine(x2, y2+i, x3, y3+i, GUIcolore); // x2 - x3
		LCD_DrawLine(x3, y3+i, x4, y4+i, White); // x3 - x4
		
		if (i % 2 == 0) {
			x2++;
			x3--;
		}
	}
	
	// triangolo grande superiore
	for (; i <= LEN_LATO_QUADRATO_PX; i++) {
		LCD_DrawLine(x1, y1+i, x2, y2+i, White); // x1 - x2
		LCD_DrawLine(x2, y2+i, x3, y3+i, GUIcolore); // x2 - x3
		LCD_DrawLine(x3, y3+i, x4, y4+i, White); // x3 - x4
		
		if (i % 2 == 0) {
			x2-=2;
			x3+=2;
		}
	}
	
	x1 = x;
	y1 = y;

	LCD_DrawLine(x1, y1, x1+LEN_LATO_QUADRATO_PX, y1, Black); // lato superiore
	LCD_DrawLine(x1, y1+LEN_LATO_QUADRATO_PX, x1+LEN_LATO_QUADRATO_PX, y1+LEN_LATO_QUADRATO_PX, Black); // lato inferiore
	LCD_DrawLine(x1, y1, x1, y1+LEN_LATO_QUADRATO_PX, Black); // lato sinistro
	LCD_DrawLine(x1+LEN_LATO_QUADRATO_PX, y1, x1+LEN_LATO_QUADRATO_PX, y1+LEN_LATO_QUADRATO_PX, Black); // lato destro
}


int MENUgetPosCursore(int num_menu) {
	if (num_menu == MENU1) {
		return menu1.posCursore;
	} else {
		return menu2.posCursore;
	}
}
