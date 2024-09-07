/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


/* Include */
#include "Mossa.h"
#include "ST.h"
#include "Giocatore.h"


/* Define */
#define ROSSO 0
#define BLU 1
#define MAX_MOSSE 100


/**
	@brief			Per il salvataggio della cronologia di mosse dei giocatori si utilizza
							due vettori, uno per ciascun giocatore, sovraddimensionati a MAX_MOSSE 
							mosse. Parallelamente si tiene traccia del numero di mosse, e quindi di 
							conseguenza dell'indice dei vettori, con una variabile counter per ogni
							vettore. Nel caso in cui le mosse fossero più di MAX_MOSSE si inizia a 
							sovrascrivere la prima mossa e così via, eseguendo dunque una scrittura
							di tipo circolare sui due vettori delle mosse
*/
Mossa mosseRosso[MAX_MOSSE];
Mossa mosseBlu[MAX_MOSSE];
int cntMosseRosso = 0;
int cntMosseBlu = 0;


/**
	@brief			Funzione che fornite le informazioni della mossa tramite parametro crea
							una mossa e la aggiunge al vettore delle mosse del giocatore interessato.
							Una volta aggiunta incrementa il contatore del numero di mosse del giocatore
	@parameter	numeroGiocatore:				ID del giocatore che può essere {ROSSO=0, BLU=1}
	@parameter	mossaGiocatore:					Mossa del giocatore = 1 o Mossa di un muro = 0
	@parameter	verticaleOrizzontale:		Direzione di movimento del muro, orizzontale = 1,
																			verticale = 0
	@parameter	posizione:							ID del vertice in alto a sinistra del quadrato in 
																			cui il giocatore o il muro è stato mosso
*/
void MOSSAcrea(int numeroGiocatore, int mossaGiocatore, int verticaleOrizzontale, int posizione) {
	Mossa mossa;
	uint8_t y_8bit;
	uint8_t x_8bit;
	
	mossa.mossa = 0;
	
	if (numeroGiocatore == 1) mossa.mossa |= (1 << 24);	/* Giocatore 1, altrimenti giocatore 0 */
	
	if (!mossaGiocatore) mossa.mossa |= (1 << 20); /* Mosso un muro metto valore 1, altrimenti mosso giocatore (=0) */
	
	if (verticaleOrizzontale == 0) mossa.mossa |= (1 << 16); /* Orizzontale, metto valore 1, altrimenti verticale (=0) */
	
	x_8bit = (uint8_t)STgetVerticeX(posizione); /* Coordinata x e y */
	y_8bit = (uint8_t)STgetVerticeY(posizione);
	mossa.mossa |= (x_8bit << 0);
	mossa.mossa |= (y_8bit << 8);
	
	if (numeroGiocatore == ROSSO) { /* Giocatore Rosso */
		if (cntMosseRosso == MAX_MOSSE) cntMosseRosso = 0;
		mosseRosso[cntMosseRosso++] = mossa;
	} else { /* Giocatore Blu */
		if (cntMosseBlu == MAX_MOSSE) cntMosseBlu = 0;
		mosseBlu[cntMosseBlu++] = mossa;
	}
	
	GIOCATOREaddMossa(numeroGiocatore); /* Incremento numero mosse giocatore */
}


/**
	@brief			Funzione che crea una mossa void fatta dal giocatore passato come parametro.
							Una mossa è void se il giocatore non prende o non conferma una scelta di 
							mossa prima dello scadere del tempo a disposizione per ogni turno.
	@parameter	numeroGiocatore:				ID del giocatore che può essere {ROSSO=0, BLU=1}
*/
void MOSSAcreaVoid(int numeroGiocatore) {
	Mossa mossa;
	mossa.mossa = 0;
	
	if (numeroGiocatore == 1) mossa.mossa |= (1 << 24);	/* Giocatore 1, altrimenti giocatore 0 */

	mossa.mossa |= (1 << 16); /* Vertical/Horizzontal = 1 */
	
	if (numeroGiocatore == ROSSO) { /* Giocatore rosso */
		if (cntMosseRosso == MAX_MOSSE) cntMosseRosso = 0; /* Scrittura circolare */
		mosseRosso[cntMosseRosso++] = mossa;
	} else { /* Giocatore rosso */
		if (cntMosseBlu == MAX_MOSSE) cntMosseBlu = 0; /* Scrittura circolare */
		mosseBlu[cntMosseBlu++] = mossa;
	}
	
	GIOCATOREaddMossa(numeroGiocatore); /* Incremento numero mosse giocatore */
}


/**
	@brief			Funzione che dato l'ID di un giocatore restituisce l'ultima mossa che ha fatto,
							che è in pratica l'ultima mossa che è state memorizzata nel vettore delle mosse
							di quello specifico giocatore.
	@parameter	numeroGiocatore:				ID del giocatore che può essere {ROSSO=0, BLU=1}
	@return			Restituisce il riferimento dell'ultima mossa del giocatore
*/
Mossa MOSSAgetLastMossa(int numeroGiocatore) {
	if (numeroGiocatore == ROSSO) { /* Giocatore rosso */
		return (mosseRosso[cntMosseRosso-1]);
	} else { /* Giocatore blu */
		return (mosseBlu[cntMosseBlu-1]);
	}
}


/**
	@brief			Funzione che inizializza le strutture dati impostando i contatori di mosse a zero
*/
void MOSSAinit(void) {
	cntMosseBlu = 0;
	cntMosseRosso = 0;
}


uint32_t MOSSAgetMossaHandshake() {
	return 0xFF000000;
}


int MOSSAgetPlayerID(Mossa mossa) {
	int id, mossaVal;
	
	mossaVal = mossa.mossa;
	id = mossaVal >> 24;
	return id;
}

int MOSSAisPlayerMode(Mossa mossa) {
	int playerMove, mossaVal;
	
	mossaVal = mossa.mossa;
	playerMove = (mossaVal >> 20) & 0xF;
	return (playerMove == 0);
}

int MOSSAisVerticale(Mossa mossa) {
	int isVerticale, mossaVal;
	
	mossaVal = mossa.mossa;
	isVerticale = (mossaVal >> 16) & 0xF;
	
	return (isVerticale == 0);
}

int MOSSAgetPosizione(Mossa mossa, int isPlayer) {
	int x, y, mossaVal;
	
	mossaVal = mossa.mossa;
	y = (mossaVal >> 8) & 0x000000FF;
	x = mossaVal & 0x000000FF;
	
	return MOSSA_da_XY_2_posizione(x, y, isPlayer);
}


int MOSSA_da_XY_2_posizione(int x, int y, int isPlayer) {
	if (isPlayer == 1) { /* Giocatore */
		return (y*8)+(x);
	} else { /* Muro */
		return (y*8)+(x)+8;
	}
} 


void MOSSA_da_posizione_2_XY(int posizione, int isPlayer, int* x_p, int* y_p) {
	int x, y;
	if (isPlayer == 1) { /* Giocatore */
		x = posizione%8;
		y = posizione/8;
	} else { /* Muro */
		x = posizione%8;
		y = (posizione/8)-1;
	}
	*x_p = x;
	*y_p = y;
} 


Mossa MOSSAcrea_return(int numeroGiocatore, int mossaGiocatore, int isVerticale, int posizione) {
	Mossa mossa;
	int y_8bit;
	int x_8bit;
	
	mossa.mossa = 0;
	
	if (numeroGiocatore == ROSSO) { /* ROSSO: id=0 */
		mossa.mossa += 0x00000000;
	} else { /* BLU: id=1 */
		mossa.mossa += 0x01000000;
	}
	
	if (mossaGiocatore == 1) { /* Giocatore mosso */
		mossa.mossa += 0x00000000;
	} else { /* Muro mosso */
		mossa.mossa += 0x00100000;
	}
	
	
	if (isVerticale == 1 && mossaGiocatore != 1) { /* muro verticale */
		mossa.mossa += 0x00000000;
	} else if (isVerticale == 0 && mossaGiocatore != 1) {
		mossa.mossa += 0x00010000;
	}
	
	MOSSA_da_posizione_2_XY(posizione, mossaGiocatore, &x_8bit, &y_8bit);
	
	/* Aggiunta Y */
	mossa.mossa += (y_8bit << 8);
	
	/* Aggiunta X */
	mossa.mossa += x_8bit;
	
	return mossa;
}


int MOSSAisVoid(Mossa mossa) {
	int playerMove, wallPlacement;
	
	playerMove = MOSSAisPlayerMode(mossa);
	wallPlacement = MOSSAisVerticale(mossa);
	
	if (playerMove == 1 && wallPlacement == 0) return 1;
	return 0;
}
