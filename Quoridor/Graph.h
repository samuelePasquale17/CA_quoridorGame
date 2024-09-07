/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef GRAPH_H
#define GRAPH_H


/**
	@brief			Per tenere traccia dello stato di gioco della partita si utilizza
							un grafo pesato con archi non orientati. La situazione di gioco è
							descritta da 64 vertici che rappresentano i vertici superiori dei
							quadrati della scacchiera, mentre la posizione dei giocatori e dei 
							muri è descritta da degli archi pesati. 
*/


/* Include */
#include "Muro.h"


/* Defines */
#define NUM_VERTICI 64	/* perchè scacchiera 7*7 (8*8 = 64) */
#define NUM_ARCHI_PERIMETRO 7*4	/* perimetro scacchiera */
#define OFFSET_COLOR_PL 2


/**
	@brief 			Struttura che definisce un grafo con matrice delle
							adiacenze
*/
typedef struct graph_s {
	int madj[NUM_VERTICI][NUM_VERTICI];	/* matrice di adiacenze (0 -> no arco, 1 -> arco muro, color -> arco giocatore) */
} Graph;


/**
	@brief			Struttura che definisce un tipo di dato Edge per
							gli archi nel grafo. Gli archi sono pesati per 
							poter distinguere muri e giocatori all'interno del
							grafo
*/
typedef struct edge {
	int v;
	int w;
	int peso;
} Edge;


/* Prototipi */
void GRAPHreset(void);
void GRAPHload(void);
void GRAPHinsertEdge(int id1, int id2, int perimetro);
void GRAPHremoveEdge(int id1, int id2);
static void insertEdge(Edge edge);
static void removeEdge(Edge edge, int daGiocatore);
int EDGEtoccaLatoSinistro(Edge edge);
int EDGEtoccaLatoDestro(Edge edge);
int EDGEtoccaLatoAlto(Edge edge);
int EDGEtoccaLatoBasso(Edge edge);
void GRAPHgetMosseValide(int idVerticePartenza, int v[], int coloreGiocatore, int* flagDiagonale);
void GRAPHinserisciPerimetro(void);
void GRAPHrimuoviPerimetro(void);
int GRAPHgetVerticeDirezione(int id, int direzione);
int GRAPHgetVerticeDirezioneConSalto(int id, int direzione);
void GRAPHinserisciGiocatore(int id1, int coloreGiocatore);
void GRAPHrimuoviGiocatore(int id1, int coloreGiocatore);
int GRAPHverticeToccaLatoSuperiore(int id);
int GRAPHverticeToccaLatoInferiore(int id);
int GRAPHgetPosRandomValidMuro(int posGiocatore1, int posGiocatore2);
void GRAPHaggiungiMuro(int v, int isOrizzontale);
void GRAPHrimuoviMuro(int v, int isOrizzontale);
int GRAPHcheckPosizioneMuro(int v1_new, int v2_new, int v1_old, int v2_old, int posGiocatore1, int posGiocatore2);
int GRAPHcheckPercorsoGiocatori(int posGiocatore1, int posGiocatore2, int muro_v1, int muro_v2);
int GRAPHisPathExists(int start, int end[]);
int isPathExistsDFS(int start, const int end[], int visited[]);
int posCorretta(int id);
int GRAPHgetNextPossibleMoveNPC(int start, int colore);


#endif
