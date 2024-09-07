/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef GIOCATORE_H 
#define GIOCATORE_H


/**
	@bried			Per rappresentare un giocatore si utilizza un tipo di dato giocatore
							per salvare diverse informazioni utili aggiornate in fase di gioco
							in base alle scelte dei giocatori. In particolare le informazioni rilevanti
							di cui si tiene traccia è il numero di mosse e muri per ciascun giocatore 
							oltre alla sua posizione corrente
*/


/* Include */
#include "Mossa.h"


/* Defines */
#define MAX_NUM_MURI 8
#define MAX_NUM_MOSSE 100
#define POSIZIONE_INIZIALE_GIOCATORE_ROSSO 51
#define POSIZIONE_INIZIALE_GIOCATORE_BLU 3


/**
	@brief			Definizione di un nuovo tipo di dato Giocatore tramite struct
							con diversi campi tra cui il colore, che è un valore intero che
							rappresenta l'ID del giocatore e può essere di norma {ROSSO=0, BLU=1}.
							La posizione corrisponde all'ID del vertice che rappresenta l'angolo
							alto a sinistra del quadrato della scacchiera su cui il giocatore è
							posizionato in fase di gioco. si tiene poi traccia del numero di muri
							e mosse tramite un contatore
*/
typedef struct {
	int colore;
	int posizione;
	int cnt_muri;
	int cnt_mosse;
	int isNPC;				/* Flag che se attivo fa giocare in modo automatico il giocatore */
	int isExternalBoard;
} Giocatore;


/* Prototipi */
void GIOCATOREcrea(int colore, int isNPC, int isExternalBoard);
void GIOCATOREreset(int colore);
void GIOCATOREaddMossa(int colore);
int GIOCATOREgetColore(int colore);
int GIOCATOREgetNumMosse(int colore);
int GIOCATOREgetNumMuriPiazzati(int colore);
int GIOCATOREgetPosizione(int colore);
void GIOCATOREsetPosizione(int colore, int posizione);
int GIOCATOREgetNumeroMuri(int colore);
int GIOCATOREgetLastMossa(int colore, Mossa *mossa);
void GIOCATOREaddMuro(int colore);
void GIOCATOREremoveMuro(int colore);
int GIOCATOREisNPC(int colore);
int GIOCATORE_NPC_getBestDirection(int colore);
int GIOCATOREisExternalBoard(int colore);


#endif
