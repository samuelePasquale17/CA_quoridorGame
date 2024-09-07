#include "../GLCD/GLCD.h"
#include "QuoridorGUI.h"
#include "ST.h"
#include <stdio.h>
#include <stdint.h>


#define ROSSO 0
#define BLU 1

// quadrati
#define LEN_LATO_QUADRATO_PX 32				// lunghezza lato quadrato
#define LEN_SPAZIO_TRA_QUADRATI_PX 2	// grandezza spazio tra quadrati 
#define OFFSET_VERTICE LEN_LATO_QUADRATO_PX+LEN_SPAZIO_TRA_QUADRATI_PX

// rettangoli
#define LUN_LATO_MAG_RETT_PX 72
#define LUN_LATO_MIN_RETT_PX 48
#define LEN_SPAZIO_LATERALE_TRA_RETT 6
#define LEN_SPAZIO_SOPRA_TRA_RETT 17

// timer
#define OFFSET_X_TIMER_STRING 24
#define OFFSET_Y_TIMER_STRING 16
#define START_TIMER_VALUE 20

// Wall number
#define OFFSET_X_WALL_STRING 10
#define OFFSET_Y_WALL_STRING 4
#define OFFSET_X_WALL_NUMBER 34
#define OFFSET_Y_WALL_NUMBER 30

// Win message
#define WIN_WINDOW_HEIGHT 236
#define X_WIN_MESSAGE 70
#define y_WIN_MESSAGE 104



#define POS_BTN_1 33
#define POS_BTN_2 49

#define HEIGHT_BTN 35
#define LEN_BTN 160






/**
	@id passato l'id del vertice
*/
void GUIdisegnaQuadrato(int id, uint16_t colore, int pieno) {
	int x, y, i;
	x = STgetVerticeX(id);
	y = STgetVerticeY(id);
	
	if (pieno == 1) { // quadrato pieno
		for (i = 0; i <= LEN_LATO_QUADRATO_PX; i++) {
			LCD_DrawLine(x, y+i, x+LEN_LATO_QUADRATO_PX, y+i, colore); // lato superiore
		}
	} else { // quadrato vuoto
		LCD_DrawLine(x, y, x+LEN_LATO_QUADRATO_PX, y, colore); // lato superiore
		LCD_DrawLine(x, y+LEN_LATO_QUADRATO_PX, x+LEN_LATO_QUADRATO_PX, y+LEN_LATO_QUADRATO_PX, colore); // lato inferiore
		LCD_DrawLine(x, y, x, y+LEN_LATO_QUADRATO_PX, colore); // lato sinistro
		LCD_DrawLine(x+LEN_LATO_QUADRATO_PX, y, x+LEN_LATO_QUADRATO_PX, y+LEN_LATO_QUADRATO_PX, colore); // lato destro	
	}
}


void GUIdisegnaScacchiera() {
	int id_vertice;
	LCD_Clear(White);
	for(id_vertice = 0; id_vertice < NUM_VERTICI-8; id_vertice++) GUIdisegnaQuadrato(id_vertice, Black, 0);
}


	// disegno timer
void GUIdisegnaTimer(int timerValue, uint16_t coloreTurno) {
	int x, y;
	x = (LEN_SPAZIO_LATERALE_TRA_RETT*2)+LUN_LATO_MAG_RETT_PX;
	y = (LEN_LATO_QUADRATO_PX*7) + (LEN_SPAZIO_TRA_QUADRATI_PX*7) + LEN_SPAZIO_SOPRA_TRA_RETT;
	
	// disegno quadrato
	LCD_DrawLine(x, y, x+LUN_LATO_MAG_RETT_PX, y, Black); // lato superiore
	LCD_DrawLine(x, y+LUN_LATO_MIN_RETT_PX, x+LUN_LATO_MAG_RETT_PX, y+LUN_LATO_MIN_RETT_PX, Black); // lato inferiore
	LCD_DrawLine(x, y, x, y+LUN_LATO_MIN_RETT_PX, Black); // lato sinistro
	LCD_DrawLine(x+LUN_LATO_MAG_RETT_PX, y, x+LUN_LATO_MAG_RETT_PX, y+LUN_LATO_MIN_RETT_PX, Black); // lato destro
	
	// disegno numero timer
	GUIstampaTimer(timerValue, 0, coloreTurno);
}


void GUIstampaTimer(int timerValue, int clear_prec, uint16_t colore) {
	int x, y, timerPrec;
	char strTimer[5], strTimerPrec[5];
	x = (LEN_SPAZIO_LATERALE_TRA_RETT*2)+LUN_LATO_MAG_RETT_PX;
	y = (LEN_LATO_QUADRATO_PX*7) + (LEN_SPAZIO_TRA_QUADRATI_PX*7) + LEN_SPAZIO_SOPRA_TRA_RETT;
	
	if (clear_prec == 1) {
		if (timerValue == 20) {
			timerPrec = 1;
		} else {
			timerPrec = timerValue + 1;
		}
		// disegno timer precedente in bianco
		sprintf(strTimerPrec, "%d s", timerPrec); // incremento valore perchè il timer è decrescente
		GUI_Text(x+OFFSET_X_TIMER_STRING, y+OFFSET_Y_TIMER_STRING, (uint8_t *) strTimerPrec, White, White);
	}
	
	// disegno timer
	sprintf(strTimer, "%d s", timerValue);
	GUI_Text(x+OFFSET_X_TIMER_STRING, y+OFFSET_Y_TIMER_STRING, (uint8_t *) strTimer, colore, White);
}


void GUIdisegnaNumeroMuriGiocatori() {
	int x1, y1, x2, y2;
	
	x1 = LEN_SPAZIO_LATERALE_TRA_RETT;
	y1 = (LEN_LATO_QUADRATO_PX*7) + (LEN_SPAZIO_TRA_QUADRATI_PX*7) + LEN_SPAZIO_SOPRA_TRA_RETT;
	x2 = (LEN_SPAZIO_LATERALE_TRA_RETT*3) + (LUN_LATO_MAG_RETT_PX*2);
	y2 = (LEN_LATO_QUADRATO_PX*7) + (LEN_SPAZIO_TRA_QUADRATI_PX*7) + LEN_SPAZIO_SOPRA_TRA_RETT;
	
	// disegno rettangolo P1
	LCD_DrawLine(x1, y1, x1+LUN_LATO_MAG_RETT_PX, y1, Black); // lato superiore
	LCD_DrawLine(x1, y1+LUN_LATO_MIN_RETT_PX, x1+LUN_LATO_MAG_RETT_PX, y1+LUN_LATO_MIN_RETT_PX, Black); // lato inferiore
	LCD_DrawLine(x1, y1, x1, y1+LUN_LATO_MIN_RETT_PX, Black); // lato sinistro
	LCD_DrawLine(x1+LUN_LATO_MAG_RETT_PX, y1, x1+LUN_LATO_MAG_RETT_PX, y1+LUN_LATO_MIN_RETT_PX, Black); // lato destro
	
	// stringa P1
	GUI_Text(x1+OFFSET_X_WALL_STRING, y1+OFFSET_Y_WALL_STRING, (uint8_t *) "P1 Wall", Black, White);
	GUIdisegnaNumeroMuriGiocatore(ROSSO, 0, x1, y1);
	
	// disegno rettangolo P2
	LCD_DrawLine(x2, y2, x2+LUN_LATO_MAG_RETT_PX, y2, Black); // lato superiore
	LCD_DrawLine(x2, y2+LUN_LATO_MIN_RETT_PX, x2+LUN_LATO_MAG_RETT_PX, y2+LUN_LATO_MIN_RETT_PX, Black); // lato inferiore
	LCD_DrawLine(x2, y2, x2, y2+LUN_LATO_MIN_RETT_PX, Black); // lato sinistro
	LCD_DrawLine(x2+LUN_LATO_MAG_RETT_PX, y2, x2+LUN_LATO_MAG_RETT_PX, y2+LUN_LATO_MIN_RETT_PX, Black); // lato destro
	
	// stringa P2
	GUI_Text(x2+OFFSET_X_WALL_STRING, y2+OFFSET_Y_WALL_STRING, (uint8_t *) "P2 Wall", Black, White);
	GUIdisegnaNumeroMuriGiocatore(BLU, 0, x2, y2);
}


void GUIdisegnaNumeroMuriGiocatore(int coloreGiocatore, int clear_prec, int x_rett, int y_rett) {
	int nWall = GIOCATOREgetNumMuriPiazzati(coloreGiocatore);
	if (clear_prec == 1) {
		PutChar(x_rett + OFFSET_X_WALL_NUMBER, y_rett + OFFSET_Y_WALL_NUMBER, '0' + (nWall-1), White, White);
	}
	// scrivo numero muri 
	PutChar(x_rett + OFFSET_X_WALL_NUMBER, y_rett + OFFSET_Y_WALL_NUMBER, '0' + nWall, Black, White);
}


void GUIdisegnaGrafica(Partita partita) {
	GUIdisegnaScacchiera();
	GUIdisegnaTimer(START_TIMER_VALUE, PARTITAgetTurnoGUI());
	GUIdisegnaNumeroMuriGiocatori();
}


void GUIdisegnaGiocatore(int coloreGiocatore) {
	
	int colore = coloreGiocatore, x1, y1, x2, y2, x3, y3, x4, y4, i;
	uint16_t GUIcolore;
	
	if (colore == ROSSO) {
		GUIcolore = Red;
	} else {
		GUIcolore = Blue;
	}
	
	//GUIdisegnaQuadrato(GIOCATOREgetPosizione(colore), GUIcolore, 1);
	
	x1 = STgetVerticeX(GIOCATOREgetPosizione(colore));
	y1 = STgetVerticeY(GIOCATOREgetPosizione(colore));
	
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
	
	x1 = STgetVerticeX(GIOCATOREgetPosizione(colore));
	y1 = STgetVerticeY(GIOCATOREgetPosizione(colore));

	LCD_DrawLine(x1, y1, x1+LEN_LATO_QUADRATO_PX, y1, Black); // lato superiore
	LCD_DrawLine(x1, y1+LEN_LATO_QUADRATO_PX, x1+LEN_LATO_QUADRATO_PX, y1+LEN_LATO_QUADRATO_PX, Black); // lato inferiore
	LCD_DrawLine(x1, y1, x1, y1+LEN_LATO_QUADRATO_PX, Black); // lato sinistro
	LCD_DrawLine(x1+LEN_LATO_QUADRATO_PX, y1, x1+LEN_LATO_QUADRATO_PX, y1+LEN_LATO_QUADRATO_PX, Black); // lato destro
	
//	x = STgetVerticeX(GIOCATOREgetPosizione(colore));
//	y = STgetVerticeY(GIOCATOREgetPosizione(colore));
//	
//	for (i = 0; i <= LEN_LATO_QUADRATO_PX; i++) {
//		LCD_DrawLine(x, y+i, x+LEN_LATO_QUADRATO_PX, y+i, GUIcolore);
//				LCD_DrawLine(x, y+i, x+LEN_LATO_QUADRATO_PX, y+i, GUIcolore); // lato superiore
//	}
}


/**
	@verticiValidi	Vettore di id dei vertici con size 4, se void == -1
*/
void GUIdisegnaMosseGiocatore(int verticiValidi[]) {
	int i;
	for (i = 0; i < 5; i++) {
		if (verticiValidi[i] != -1) {
			GUIdisegnaQuadrato(verticiValidi[i], Yellow, 1);
		}
	}
}


/**
	@verticiValidi	Vettore di id dei vertici con size 4, se void == -1
*/
void GUIrimuoviMosseGiocatore(int verticiValidi[]) {
	int i;
	for (i = 0; i < 5; i++) {
		if (verticiValidi[i] != -1) {
			GUIdisegnaQuadrato(verticiValidi[i], White, 1); // pulisco quadrato precedente
			GUIdisegnaQuadrato(verticiValidi[i], Black, 0);
		}
	}
}


void GUIrimuoviGiocatore(int coloreGiocatore) {
	GUIdisegnaQuadrato(GIOCATOREgetPosizione(coloreGiocatore), White, 1); // pulisco quadrato 
	GUIdisegnaQuadrato(GIOCATOREgetPosizione(coloreGiocatore), Black, 0);
}


void GUIstampaMessaggioVincitore(int coloreVincitore) {
	int i;
	uint16_t color = Red;
	
	if (coloreVincitore == BLU) color = Blue;
	
	for (i = 0; i <= WIN_WINDOW_HEIGHT; i++) {
		LCD_DrawLine(LEN_SPAZIO_TRA_QUADRATI_PX, LEN_SPAZIO_TRA_QUADRATI_PX+i, 240-LEN_SPAZIO_TRA_QUADRATI_PX, LEN_SPAZIO_TRA_QUADRATI_PX+i, color);
	}
	GUI_Text(X_WIN_MESSAGE, y_WIN_MESSAGE, (uint8_t*) "You Win!", White, color);
}


void GUIdisegnaMuro(Muro muro, uint16_t color) {
	int orientamento = MUROorientamento(muro);
	int x0, y0, x1, y1, i;

	x0 = STgetVerticeX(MUROgetVertice1(muro));
	y0 = STgetVerticeY(MUROgetVertice1(muro));

	x1 = STgetVerticeX(MUROgetVertice2(muro));
	y1 = STgetVerticeY(MUROgetVertice2(muro));

	if (orientamento == MURO_ORIZZONTALE) {
		for (i = 1; i < 2; i++) {
			LCD_DrawLine(x0, y0-i, x1-2, y1-i, color);
		}
	} else if (orientamento == MURO_VERTICALE) {
		for (i = 1; i < 2; i++) {
			LCD_DrawLine(x0-i, y0, x1-i, y1-2, color);
		}
	}
}


void GUIcancellaMuro(Muro muro) {
	int orientamento = MUROorientamento(muro);
	int x0, y0, x1, y1, i;
	x0 = STgetVerticeX(MUROgetVertice1(muro));
	y0 = STgetVerticeY(MUROgetVertice1(muro));

	x1 = STgetVerticeX(MUROgetVertice2(muro));
	y1 = STgetVerticeY(MUROgetVertice2(muro));

	if (orientamento == MURO_ORIZZONTALE) {
		for (i = 1; i < 2; i++) {
			LCD_DrawLine(x0, y0-i, x1-2, y1-i, White);
		}
	} else if (orientamento == MURO_VERTICALE) {
		for (i = 1; i < 2; i++) {
			LCD_DrawLine(x0-i, y0, x1-i, y1-2, White);
		}
	}
}
