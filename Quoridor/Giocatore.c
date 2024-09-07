/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


/* Include */
#include "Giocatore.h"
#include "Graph.h"


/* Defines */
#define RED 0xF800
#define ROSSO 0
#define BLU 1


/**
	@brief				Dichiarazione di due variabili globali che rappresentano i due giocatori
								in partita. Il giocatore 1 è il giocatore ROSSO mentre il giocatore 2 è 
								il giocatore BLU
*/
Giocatore giocatore1;
Giocatore giocatore2;

int visitedNPC[NUM_VERTICI];


/**
	@brief				Funzione che dato come parametro l'ID del giocatore inizializza la variabile
								globale del giocatore con la posizione di inizio partita in scacchiera e 
								azzerando i contatori relativi a muri e mosse
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@parameter		isNPC:							Flag che indica se è NPC (1) o no (0)
*/
void GIOCATOREcrea(int colore, int isNPC, int isExternalBoard) {
	int i;
	for (i = 0; i < NUM_VERTICI; i++) visitedNPC[i] = 0;


	if (colore == ROSSO) {
		giocatore1.colore = ROSSO;
		giocatore1.posizione = POSIZIONE_INIZIALE_GIOCATORE_ROSSO;
		giocatore1.cnt_muri = 0;
		giocatore1.cnt_mosse = 0;
		giocatore1.isNPC = isNPC;
		giocatore1.isExternalBoard = isExternalBoard;
	} else {
		giocatore2.colore = BLU;
		giocatore2.posizione = POSIZIONE_INIZIALE_GIOCATORE_BLU;
		giocatore2.cnt_muri = 0;
		giocatore2.cnt_mosse = 0;
		giocatore2.isNPC = isNPC;
		giocatore2.isExternalBoard = isExternalBoard;
	}
}


/**
	@brief				Funzione che dato come parametro l'ID del giocatore lo resetta, rimpostando
								i valori del giocatore a quelli di inizio partita. In particolare viene 
								riposizionato nella posizione dei default di inizio partita e il contatore
								di muri e di mosse viene azzerato
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
*/
void GIOCATOREreset(int colore) {
	int i;
	for (i = 0; i < NUM_VERTICI; i++) visitedNPC[i] = 0;
	
	if (colore == ROSSO) {
		giocatore1.posizione = POSIZIONE_INIZIALE_GIOCATORE_ROSSO;
		giocatore1.cnt_mosse = 0;
		giocatore1.cnt_muri = 0;
	} else {
		giocatore2.posizione = POSIZIONE_INIZIALE_GIOCATORE_BLU;
		giocatore2.cnt_mosse = 0;
		giocatore2.cnt_muri = 0;
	} 
}


/**
	@brief				Funzione che dato come parametro l'ID del giocatore lo resetta, incrementa il 
								contatore di numero di mosse di quel giocatore
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
*/
void GIOCATOREaddMossa(int colore) {
	if (colore == ROSSO) { /* Giocatore rosso */
		if (giocatore1.cnt_mosse == MAX_NUM_MOSSE) giocatore1.cnt_mosse = 0;
		giocatore1.cnt_mosse++;
	} else { /* Giocatore blu */
		if (giocatore2.cnt_mosse == MAX_NUM_MOSSE) giocatore2.cnt_mosse = 0;
		giocatore2.cnt_mosse++;
	}
}


/**
	@brief				Funzione che restituisce il colore del giocatore dato l'ID come parametro
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return 			Colore giocatore
*/
int GIOCATOREgetColore(int colore) {
	return colore;
}


/**
	@brief				Funzione che restituisce il numero di mosse del giocatore dato l'ID come 
								parametro
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return				Numero di mosse
*/
int GIOCATOREgetNumMosse(int colore) {
	if (colore == ROSSO) {
		return giocatore1.cnt_mosse;
	} else {
		return giocatore2.cnt_mosse;
	}
}


/**
	@brief				Funzione che restituisce il numero di muri piazzati dal giocatore dato 
								l'ID come parametro
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return 			Numero di muri piazzati
*/
int GIOCATOREgetNumMuriPiazzati(int colore) {
	if (colore == ROSSO) {
		return giocatore1.cnt_muri;
	} else {
		return giocatore2.cnt_muri;
	}
}


/**
	@brief				Funzione che restituisce la posizione del giocatore dato l'ID come 
								parametro
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return				Posizione giocatore, equivalente all'ID del vertice in alto a sinistra
								nella rappresentazione a grafo della partita
*/
int GIOCATOREgetPosizione(int colore) {
	if (colore == ROSSO) {
		return giocatore1.posizione;
	} else {
		return giocatore2.posizione;
	}
}


/**
	@brief				Funzione che imposta la posizione del giocatore dato l'ID come 
								parametro e la nuova posizione del giocatore
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
*/
void GIOCATOREsetPosizione(int colore, int posizione) {
	if (colore == ROSSO) {
		giocatore1.posizione = posizione;
	} else {
		giocatore2.posizione = posizione;
	}
}


/**
	@brief				Funzione che restituisce il numero di muri piazzati da un giocatore, 
								dato l'ID del giocatore
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return				Numero di muri piazzati dal giocatore
*/
int GIOCATOREgetNumeroMuri(int colore) {
	if (colore == ROSSO) {
		return giocatore1.cnt_muri; 
	} else {
		return giocatore2.cnt_muri;
	}
}


/**
	@brief				Funzione che dato l'ID del giocatore come parametro e un riferimento a mossa
								carica l'ultima mossa passandola by-reference e restituisce un valore intero
								che indica se la mossa c'è o meno.
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return				Se il giocatore non ha fatto alcuna mossa restituisce -1, altrimenti restituisce 0
*/
int GIOCATOREgetLastMossa(int colore, Mossa *mossa) {
	int nMosse = GIOCATOREgetNumMosse(colore);
	if (nMosse == 0) {
		return -1;
	} else {
		*mossa = MOSSAgetLastMossa(colore);
		return 0;
	}
}


/**
	@brief				Funzione che dato l'ID del giocatore come parametro incrementa il contatore del
								numero di muri posizionati dal giocatore
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
*/
void GIOCATOREaddMuro(int colore) {
	if (colore == ROSSO) { /* Giocatore rosso */
		giocatore1.cnt_muri++;
	} else if (colore == BLU) { /* Giocatore blu */
		giocatore2.cnt_muri++;
	}
}


/**
	@brief				Funzione che dato l'ID del giocatore come parametro decrementa il contatore del
								numero di muri posizionati dal giocatore
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
*/
void GIOCATOREremoveMuro(int colore) {
	if (colore == ROSSO) { /* Giocatore rosso */
		giocatore1.cnt_muri--;
	} else { /* Giocatore blu */
		giocatore2.cnt_muri--;
	}
} 


/**
	@brief				Funzione che restituisce se il giocatore con l'ID passato come
								parametro è NPC o no	
	@parameter		colore:							ID del giocatore, può essere {ROSSO=0, BLU=1}
	@return				Restituisce 1 se NPC o 0 se non è NPC
*/
int GIOCATOREisNPC(int colore) {
	if (colore == ROSSO) { /* Giocatore 1 */
		return (giocatore1.isNPC == 1);
	} else if (colore == BLU) { /* Giocatore 2 */
		return (giocatore2.isNPC == 1);
	}
	return 0;
}


/**
	@brief			Funzione che restituisce la prossima mossa che il	
							giocatore NPC deve fare
*/
int GIOCATORE_NPC_getBestDirection(int colore) {
	int mosseValide[5], flagDiagonale, posAttuale = GIOCATOREgetPosizione(colore);
	int IDsu = -1, IDgiu = -1, IDdestra = -1, IDsinistra = -1, i;
	int min = 100, direzione = 0, index;
	
	GRAPHgetMosseValide(GIOCATOREgetPosizione(colore), mosseValide, colore, &flagDiagonale);

	for (i = 0; i < 5; i++) {
		if (mosseValide[i] == posAttuale + 8 || mosseValide[i] == posAttuale + 16) {
			IDgiu = mosseValide[i];
		} else if (mosseValide[i] == posAttuale - 8 || mosseValide[i] == posAttuale - 16) {
			IDsu = mosseValide[i];
		} else if (mosseValide[i] == posAttuale + 1 || mosseValide[i] == posAttuale + 2) {
			IDdestra = mosseValide[i];
		} else if (mosseValide[i] == posAttuale - 1 || mosseValide[i] == posAttuale - 2) {
			IDsinistra = mosseValide[i];
		}
	}
	
	if (IDgiu != -1) {
		min = visitedNPC[IDgiu];
		index = IDgiu;
		direzione = 3;
	}
	
	if (IDsinistra != -1 && visitedNPC[IDsinistra] < min) {
		min = visitedNPC[IDsinistra];
		index = IDsinistra;
		direzione = 4;
	}
	
	if (IDdestra != -1 && visitedNPC[IDdestra] < min) {
		min = visitedNPC[IDdestra];
		index = IDdestra;
		direzione = 2;
	}
	
	if (IDsu != -1 && visitedNPC[IDsu] < min) {
		min = visitedNPC[IDsu];
		index = IDsu;
		direzione = 1;
	}
	
	if (direzione != 0) visitedNPC[index]++;
	
	
	return direzione;
}


int GIOCATOREisExternalBoard(int colore) {
	if (colore == ROSSO) { /* Giocatore 1 */
		return (giocatore1.isExternalBoard == 1);
	} else if (colore == BLU) { /* Giocatore 2 */
		return (giocatore2.isExternalBoard == 1);
	}
	return 0;
}
