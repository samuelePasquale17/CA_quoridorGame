/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


/* Include */
#include "Graph.h"
#include "ST.h"
#include "Giocatore.h"
#include "Muro.h"


/* Defines */
#define ROSSO 0
#define BLU 1


/* Prototipo */
static Edge EDGEcreate(int v, int w, int peso);


/**
	@brief			Variabile globale contenente il grafo che rappresenta
							lo stato della partita
*/
Graph graph;


/**
	@brief			Funzione che crea un arco del grafo
	@parameter	v:										Vertice 1
	@parameter	w:										Vertice 2
	@parameter	peso:									Peso dell'arco
*/
static Edge EDGEcreate(int v, int w, int peso) {
	Edge e;
	e.v = v; 
	e.w = w;
	e.peso = peso;
	return e;
}


/**
	@brief			Funzione che resetta il grafo rimuovendo tutti gli archi
*/
void GRAPHreset() {
	int i, j;
	for (i = 0; i < NUM_VERTICI; i++) {
		for (j = 0; j < NUM_VERTICI; j++) {
			(graph.madj)[i][j] = 0;
			(graph.madj)[j][i] = 0;
		}
	}
}


/**
	@brief			Funzione che carica il grafo con setUp iniziale, 
							aggiungendo i giocatori nella loro posizione iniziale
*/
void GRAPHload() {
	GRAPHreset();
	GRAPHinserisciGiocatore(POSIZIONE_INIZIALE_GIOCATORE_ROSSO, ROSSO);
	GRAPHinserisciGiocatore(POSIZIONE_INIZIALE_GIOCATORE_BLU, BLU);
}


/**
	@brief			Funzione che inserisce un arco nel grafo
	@parameter	id1:										Vertice 1
	@parameter	id2:										Vertice 2
	@parameter	peso:										Peso dell'arco
*/
void GRAPHinsertEdge(int id1, int id2, int peso) {
	insertEdge(EDGEcreate(id1, id2, peso));
}


/**
	@brief			Funzione che rimuove un arco nel grafo
	@parameter	id1:										Vertice 1
	@parameter	id2:										Vertice 2
*/
void GRAPHremoveEdge(int id1, int id2) {
	removeEdge(EDGEcreate(id1, id2, -1), 0);
}


/**
	@brief			Funzione che inserisce un arco nel grafo
	@parameter	edge:										Arco da inserire

*/
static void insertEdge(Edge edge) {
	int v = edge.v, w = edge.w, perimetro = edge.peso;

	graph.madj[v][w] = perimetro;
	graph.madj[w][v] = perimetro;
}


/**
	@brief			Funzione che rimuove un arco dal grafo
	@parameter	edge:										Arco da inserire

*/
static void removeEdge(Edge edge, int daGiocatore) {
	int v = edge.v, w = edge.w;

	if (daGiocatore == 1) {
		if (graph.madj[v][w] != 1) graph.madj[v][w] = 0;
		if (graph.madj[v][w] != 1) graph.madj[w][v] = 0;
	} else {
		if (graph.madj[v][w] == 1) graph.madj[v][w] = 0;
		if (graph.madj[v][w] == 1) graph.madj[w][v] = 0;
	}
}


/**
	@brief			Funzione che verifica se l'arco passato come parametro
							è tangente al lato sinistro della scacchiera
	@parameter	edge:										Arco da inserire
	@return			restituisce 1 se tocca lato sinistro, altrimenti 0
*/
int EDGEtoccaLatoSinistro(Edge edge) {
	return ((edge.v % 8 == 0) || (edge.w % 8 == 0));
}


/**
	@brief			Funzione che verifica se l'arco passato come parametro
							è tangente al lato destro della scacchiera
	@parameter	edge:										Arco da inserire
	@return			restituisce 1 se tocca lato destro, altrimenti 0
*/
int EDGEtoccaLatoDestro(Edge edge) {
	return (((edge.v-7) % 8 == 0) || ((edge.w-7) % 8 == 0));
}


/**
	@brief			Funzione che verifica se l'arco passato come parametro
							è tangente al lato alto della scacchiera
	@parameter	edge:										Arco da inserire
	@return			restituisce 1 se tocca lato alto, altrimenti 0
*/
int EDGEtoccaLatoAlto(Edge edge) {
	return ((edge.v >= 0 && edge.v <= 7) || (edge.w >= 0 && edge.w <= 7));
}


/**
	@brief			Funzione che verifica se l'arco passato come parametro
							è tangente al lato basso della scacchiera
	@parameter	edge:										Arco da inserire
	@return			restituisce 1 se tocca lato basso, altrimenti 0
*/
int EDGEtoccaLatoBasso(Edge edge) {
	return ((edge.v >= 56 && edge.v <= 63) || (edge.w >= 56 && edge.w <= 63));
}


/**
	@brief			Funzione che dato un ID di partenza e il colore del giocatore da prendere
							in considerazione, carica su un vettore di interi tutte le mosse valide
	@parameter	idVerticePartenza:					ID del vertice di partenza dal quale verificare le mosse valide
	@parameter	v:													Vettore di vertici caricati dalla funzione che corrispondono
																					alle posizioni valide
	@parameter	coloreGiocatore:						Colore del giocatore per il quale vanno verificate le mosse valide
	@parameter	flagDiagonale:							Riferimento a flag che indica se il giocatore può fare delle mosse 
																					in diagonale
*/
void GRAPHgetMosseValide(int idVerticePartenza, int v[], int coloreGiocatore, int* flagDiagonale) {
	int id1, id2, id3, id4, index, i;
	index = 0;
	
	GRAPHinserisciPerimetro(); /* Aggiungo perimetro a grafo */
	id1 = idVerticePartenza;
	id2 = id1+1;
	id3 = id1+8;
	id4 = id1+8+1;
	
	if ((graph.madj)[id1][id2] == 0 || (graph.madj)[id1][id2] == (OFFSET_COLOR_PL + coloreGiocatore)) {
		v[index++] = id1-8; /* Sopra */
	} else { /* Verifico se posso scavalcare */
		if (id1 >= 16 && graph.madj[id1][id1-8+1] != 0 && graph.madj[id1-8][id1-8+1] != 1 && graph.madj[id1][id1+1] != 1) {
			v[index++] = id1-16;
		} else { /* Controllo se posso andare di fianco muovendomi in diagonale */
			if (id1 >= 17 && id1 % 8 != 0 && (graph.madj)[id1][id1+1] != 1 && (graph.madj)[id1][id1-8] != 1) { // alto+sinistra
				v[index++] = id1-8-1;
				*flagDiagonale = 1;
			}
			if (id1 >= 16 && id1 % 8 != 7 && (graph.madj)[id1][id1+1] != 1 && (graph.madj)[id1+1][id1+1-8] != 1) { // alto+destra
				v[index++] = id1+1-8;
				*flagDiagonale = 1;
			}
		}
	}
	
	if (graph.madj[id3][id4] == 0 || graph.madj[id3][id4] == (OFFSET_COLOR_PL + coloreGiocatore)) {
		v[index++] =id1+8; /* Sotto */
	} else { /* Verifico se posso scavalcare */
		if (id1 <= 39 && (graph.madj)[id1+8][id1+8+8+1] != 0 && (graph.madj)[id1+16][id1+16+1] != 1&& (graph.madj)[id1+8][id1+1+8] != 1) {
			v[index++] = id1+16;
		} else { /* Controllo se posso andare di fianco muovendomi in diagonale */
			if (id1 <= 38 && id1 % 8 != 0 && (graph.madj)[id3][id3+1] != 1 && (graph.madj)[id3][id3+8] != 1) { // basso+sinistra
				v[index++] = id3-1;
				*flagDiagonale = 1;
			}
			if (id1 <= 37 && id1 % 8 != 7 && (graph.madj)[id3][id3+1] != 1 && (graph.madj)[id4+1][id4+8] != 1) { // basso+destra
				v[index++] = id4;
				*flagDiagonale = 1;
			}
		}
	}
	
	if ((graph.madj)[id1][id3] == 0 || (graph.madj)[id1][id3] == (OFFSET_COLOR_PL + coloreGiocatore)) {
		v[index++] = id1-1; /* Sinistra */
	} else { /* Verifico se posso scavalcare */
		if ((id1 % 8 >= 2) && (graph.madj)[id1][id1+8-1] != 0 && (graph.madj)[id1-1][id1+8-1] != 1 && (graph.madj)[id1][id1+8] != 1) {
			v[index++] = id1-2;
		} else { /* Controllo se posso andare di fianco muovendomi in diagonale */
			if (id1 % 8 != 1 && id1 >= 10 && (graph.madj)[id1][id3] != 1 && (graph.madj)[id1][id1-1] != 1) { // alto+sinistra
				v[index++] = id1-8-1;
				*flagDiagonale = 1;
			}
			if (id1 % 8 != 1 && id1 <= 46 && (graph.madj)[id1][id3] != 1 && (graph.madj)[id3][id3-1] != 1) { // basso+sinistra
				v[index++] = id3-1;
				*flagDiagonale = 1;
			}
		}
		
	}
	
	if ((graph.madj)[id2][id4] == 0 || (graph.madj)[id2][id4] == (OFFSET_COLOR_PL + coloreGiocatore)) {
		v[index++] = id1+1; /* Destra */
	} else { /* Verifico se posso scavalcare a destra */
		if ((id1 % 8 <= 4) && (graph.madj)[id1+1][id1+8+2] != 0 && (graph.madj)[id1+2][id1+2+8] != 1 && (graph.madj)[id1+1][id1+1+8] != 1) {
			v[index++] = id1+2;
		} else { /* Controllo se posso andare di fianco muovendomi in diagonale */
			if (id1 % 8 != 5 && id1 >= 8 && (graph.madj)[id2][id4] != 1 && (graph.madj)[id2][id2+1] != 1) { // alto+destra
				v[index++] = id2-8;
				*flagDiagonale = 1;
			}
			if (id1 % 8 != 5 && id1 <= 44 && (graph.madj)[id2][id4] != 1 && (graph.madj)[id4][id4+1] != 1) { // basso+destra
				v[index++] = id4;
				*flagDiagonale = 1;
			}
		}
		
	}
	
	/* Riempio vertici rimanenti con void */
	for (i = index; i < 5; i++) {
		v[i] = -1; /* -1 valore void */
	}
	
	GRAPHrimuoviPerimetro(); /* Rimuovo perimetro da grafo */
}


/**
	@brief			Funzione che aggiunge il perimetro esterno al grafo,
							può essere utile in alcune circostanze per delimitare
							la scacchiera con una fine invalicabile, come con i muri
*/
void GRAPHinserisciPerimetro() {
	int i;
	for (i = 0; i < 7; i++) { /* Perimetro superiore */
		insertEdge(EDGEcreate(i, i+1, 1));
	}
	for (i = 56; i < 63; i++) { /* Perimetro inferiore */
		insertEdge(EDGEcreate(i, i+1, 1));
	}
	for (i = 7; i < 63; i+=8) { /* Perimetro destro */
		insertEdge(EDGEcreate(i, i+8, 1));
	}
	for (i = 0; i < 56; i+=8) { /* Perimetro sinistro */
		insertEdge(EDGEcreate(i, i+8, 1));
	}
}


/**
	@brief			Funzione che rimuove il perimetro esterno del grafo
*/
void GRAPHrimuoviPerimetro() {
	int i;
	for (i = 0; i < 7; i++) { /* Perimetro superiore */
		removeEdge(EDGEcreate(i, i+1, -1), 0);
	}
	for (i = 56; i < 63; i++) { /* Perimetro inferiore */
		removeEdge(EDGEcreate(i, i+1, -1), 0);
	}
	for (i = 7; i < 63; i+=8) { /* Perimetro destro */
		removeEdge(EDGEcreate(i, i+8, -1), 0);
	}
	for (i = 0; i < 56; i+=8) { /* Perimetro sinistro */
		removeEdge(EDGEcreate(i, i+8, -1), 0);
	}
}


/**
	@brief			Funzione che dato un vertice restituisce l'ID del
							vertice successivo nella direzione passata come
							parametro
	@parameter	id							ID posizione di partenza
	@parameter	direzione				direzione in cui andare {SOPRA=1, DESTRA=2, SOTTO=3, SINISTRA=4}
	@return 		restituisce l'ID della nuova posizione o -1 se questa non esiste o non è valida
*/
int GRAPHgetVerticeDirezione(int id, int direzione) {
	int i;
	
	if (id == -1) return -1; /* -1 valore vertice void */
	
	if (direzione == 1) { /* Sopra */
		id -= 8;
	} else if (direzione == 2) { /* Destra */
		id += 1;
	} else if (direzione == 3) { /* Giù */
		id += 8;
	} else if (direzione == 4) { /* Sinistra */
		id -= 1;
	} 
	
	for (i = 7; i < 64; i+=8) { /* Evito perimetro */
		if (id == i) return -1; /* -1 valore vertice void */
	}
	
	for (i = 56; i < 64; i++) {
		if (id == i) return -1; /* -1 valore vertice void */
	}
	
	if (id >= 0 && id < 64) {
		return id;
	} else {
		return -1; /* -1 valore vertice void */
	}
}


/**
	@brief			Funzione che dato un vertice restituisce l'ID del
							vertice successivo con un salto di una casella 
							nella scacchiera nella direzione passata come
							parametro
	@parameter	id							ID posizione di partenza
	@parameter	direzione				direzione in cui andare {SOPRA=1, DESTRA=2, SOTTO=3, SINISTRA=4}
	@return 		restituisce l'ID della nuova posizione o -1 se questa non esiste o non è valida
*/
int GRAPHgetVerticeDirezioneConSalto(int id, int direzione) {
	int i;
	
	if (id == -1) return -1; /* -1 valore vertice void */
	if (direzione == 1) { /* sopra */
		id -= 16;
	} else if (direzione == 2) { /* destra */
		id += 2;
	} else if (direzione == 3) { /* giù */
		id += 16; 
	} else if (direzione == 4) { /* sinistra */
		id -= 2;
	} 
	
	for (i = 7; i < 64; i+=8) { /* evito perimetro */
		if (id == i) return -1; /* -1 valore vertice void */
	}
	
	for (i = 56; i < 64; i++) {
		if (id == i) return -1; /* -1 valore vertice void */
	}
	
	if (id >= 0 && id < 64) {
		return id;
	} else {
		return -1; /* -1 valore vertice void */
	}
}


/**
	@brief			Funzione che dato un ID e il colore del giocatore, inserisce
							il giocatore all'interno del grafo
	@parameter	id1:											Posizione in cui inserire il giocatore
	@parameter	coloreGiocatore:					Colore del giocatore da inserire	
*/
void GRAPHinserisciGiocatore(int id1, int coloreGiocatore) {
	int id2, id3, id4;
	/* aggiungo giocatore al grafo, l'aggiunta viene fatta mettendo due archi diagonali formando una X */
	id2 = id1+1;
	id3 = id2+8;
	id4 = id1+8;

	if((graph.madj)[id1][id3] != 1) insertEdge(EDGEcreate(id1, id3, OFFSET_COLOR_PL+coloreGiocatore)); 
	if((graph.madj)[id2][id4] != 1) insertEdge(EDGEcreate(id2, id4, OFFSET_COLOR_PL+coloreGiocatore));
	if((graph.madj)[id1][id2] != 1) insertEdge(EDGEcreate(id1, id2, OFFSET_COLOR_PL+coloreGiocatore));
	if((graph.madj)[id3][id4] != 1) insertEdge(EDGEcreate(id3, id4, OFFSET_COLOR_PL+coloreGiocatore));
	if((graph.madj)[id1][id4] != 1) insertEdge(EDGEcreate(id1, id4, OFFSET_COLOR_PL+coloreGiocatore));
	if((graph.madj)[id2][id3] != 1) insertEdge(EDGEcreate(id2, id3, OFFSET_COLOR_PL+coloreGiocatore));
}


/**
	@brief			Funzione che dato un ID e il colore del giocatore, rimuove
							il giocatore dal grafo
	@parameter	id1:											Posizione in cui inserire il giocatore
	@parameter	coloreGiocatore:					Colore del giocatore da inserire	
*/
void GRAPHrimuoviGiocatore(int id1, int coloreGiocatore) {
	int id2, id3, id4;

	id2 = id1+1;
	id3 = id2+8;
	id4 = id1+8;

	/* rimuovo tutti gli archi */
	if((graph.madj)[id1][id3] != 1) removeEdge(EDGEcreate(id1, id3, -1), 1);
	if((graph.madj)[id2][id4] != 1) removeEdge(EDGEcreate(id2, id4, -1), 1); 
	if((graph.madj)[id1][id2] != 1) removeEdge(EDGEcreate(id1, id2, -1), 1); 
	if((graph.madj)[id3][id4] != 1) removeEdge(EDGEcreate(id3, id4, -1), 1);
	if((graph.madj)[id1][id4] != 1) removeEdge(EDGEcreate(id1, id4, -1), 1); 
	if((graph.madj)[id2][id3] != 1) removeEdge(EDGEcreate(id2, id3, -1), 1); 
}


/**
	@brief			Funzione che verifica se il vertice passato come parametro
							tocca il lato superiore
	@parameter	id:				Posizione da controllare
	@return			Restituisce 1 se tocca il lato superiore, altrimenti no
*/
int GRAPHverticeToccaLatoSuperiore(int id) {
	return (id >= 0 && id <= 7);
}


/**
	@brief			Funzione che verifica se il vertice passato come parametro
							tocca il lato inferiore
	@parameter	id:				Posizione da controllare
	@return			Restituisce 1 se tocca il lato inferiore, altrimenti no
*/
int GRAPHverticeToccaLatoInferiore(int id) {
	return (id >= 48 && id <= 55);
}


/**
	@brief					Funzione che restituisce la posizione di un nuovo muro
									in una posizione valida sulla scacchiera
	@parameter			posGiocatore1:				Posizione vertice alto a sinistra del giocatore 1
	@parameter			posGiocatore2:				Posizione vertice alto a sinistra del giocatore 2
	@return					Valore vertice in v1 del muro 
*/
int GRAPHgetPosRandomValidMuro(int posGiocatore1, int posGiocatore2) {
	int v = 27, finito = 0;
	while (!finito) {
		if (v % 8 >= 1 && v % 8 <=5) {
			if ((graph.madj)[v][v+1] != 1 && (graph.madj)[v+1][v+2] != 1 && GRAPHcheckPercorsoGiocatori(posGiocatore1, posGiocatore2, v, v+2) == 1) {
				finito = 1;
			}
		}
		v++;
		if (v == 55) v = 9;
	}
	return v-1;
}


/**
	@brief					Funzione che aggiunge un muro nel  grafo
	@parameter			v:										Posizione vertice del muro
	@parameter			isOrizzontale:				Flag che indica se il muro è orizzontale
*/
void GRAPHaggiungiMuro(int v, int isOrizzontale) {
	if (isOrizzontale == 1) {
		(graph.madj)[v][v+1] = 1;
		(graph.madj)[v+1][v] = 1;
		
		(graph.madj)[v+1][v+2] = 1;
		(graph.madj)[v+2][v+1] = 1;	
	} else {
		(graph.madj)[v][v+8] = 1;
		(graph.madj)[v+8][v] = 1;
		
		(graph.madj)[v+8][v+16] = 1;
		(graph.madj)[v+16][v+8] = 1;
	}
}


/**
	@brief					Funzione che rimuove un muro nel  grafo
	@parameter			v:										Posizione vertice del muro
	@parameter			isOrizzontale:				Flag che indica se il muro è orizzontale
*/
void GRAPHrimuoviMuro(int v, int isOrizzontale) {
	int val = 0;
	if (isOrizzontale == 1) {
		if(v >= 0 && v <= 7) {
			val = (graph.madj)[v][v+1+8];
		} else {
			val = (graph.madj)[v][v-8+1];
		}
		if ((graph.madj)[v][v+1] == 1) (graph.madj)[v][v+1] = val;
		if ((graph.madj)[v+1][v] == 1) (graph.madj)[v+1][v] = val;
		
		if((v+1) >= 0 && (v+1) <= 7) {
			val = (graph.madj)[v+1][v+1+1+8];
		} else {
			val = (graph.madj)[v+1][v+1-8+1];
		}
		
		if ((graph.madj)[v+1][v+2] == 1) (graph.madj)[v+1][v+2] = val;
		if ((graph.madj)[v+2][v+1] == 1) (graph.madj)[v+2][v+1] = val;	
	} else {
		if(v % 8 == 7) {
			val = (graph.madj)[v][v+8-1];
		} else {
			val = (graph.madj)[v][v+8+1];
		}
		if ((graph.madj)[v][v+8] == 1) (graph.madj)[v][v+8] = val;
		if ((graph.madj)[v+8][v] == 1) (graph.madj)[v+8][v] = val;
		
		if((v+8) % 8 == 7) {
			val = (graph.madj)[v+8][v+8+8-1];
		} else {
			val = (graph.madj)[v+8][v+8+8+1];
		}
		if ((graph.madj)[v+8][v+16] == 1) (graph.madj)[v+8][v+16] = val;
		if ((graph.madj)[v+16][v+8] == 1) (graph.madj)[v+16][v+8] = val;
	}
}


/**
	@brief 			Funzione che controlla dato un muro, che la sua posizione sia
							valida e che non crei una trappola sulla scacchiera che non 
							permette ad uno dei due giocatori di vincere
	@parameter			v1_new:							Posizione vertice v1 nuova
	@parameter			v2_new:							Posizione vertice v2 nuova
	@parameter			v1_old:							Posizione vertice v1 vecchia
	@parameter			v2_old:							Posizione vertice v2 vecchia
	@parameter			posGiocatore1:			Posizione giocatore 1
	@parameter			posGiocatore2:			Posizione giocatore 2
	@return			Restituisce 1 se la posizione è valida, altrimenti 0
*/
int GRAPHcheckPosizioneMuro(int v1_new, int v2_new, int v1_old, int v2_old, int posGiocatore1, int posGiocatore2) {
	int tmp, resCammino, old_is_vertical;
	Muro muro;
	MUROcreaSenzaAggiungere(&muro, v1_old, v2_old);
	old_is_vertical = MUROisVertical(muro);
	if (v1_new > v2_new) {
		tmp = v1_new;
		v1_new = v2_new;
		v2_new = tmp;
	}
	if (v2_new - v1_new == 2) {
		if (v1_new <= 7 || v1_new >= 55) return 0;
		if ((v2_new % 8) - (v1_new % 8) != 2) return 0;
 	} else {
		if (v1_new % 8 == 0 || v1_new % 8 == 7) return 0;
		if (v1_new >= 48) return 0;
		if (v2_new <= 15) return 0;
	}

	if (old_is_vertical == 1) {
		GRAPHrimuoviMuro(v1_old, 0);
	} else {
		GRAPHrimuoviMuro(v1_old, 1);
	}
	
	resCammino = GRAPHcheckPercorsoGiocatori(posGiocatore1, posGiocatore2, v1_new, v2_new);
	
	if (old_is_vertical == 1) {
		GRAPHaggiungiMuro(v1_old, 0);
	} else {
		GRAPHaggiungiMuro(v1_old, 1);
	}
	
	if (resCammino == 0) return 0;
	return 1;
}


/**
	@brief				Funzione wrapper di una DFS sul grafo per la ricerca di un percorso valido 
								per la vittoria di entrambe i giocatori
	@parameter		posGiocatore1:	Posizione giocatore 1
	@parameter		posGiocatore3:	Posizione giocatore 2
	@parameter		muro_v1:				Vertice v1 del muro di test da aggiungere per il controllo. 
																Passare -1 se non si deve aggiungere nessun muro di test
	@parameter		muro_v2:				Vertice v2 del muro di test da aggiungere per il controllo.
																Passare -1 se non si deve aggiungere nessun muro di test
	@return 			Restituisce 1 se esiste la possibilità per entrambe i giocatori di 
								vincere ancora, altrimenti 0 se non è possibile
*/
int GRAPHcheckPercorsoGiocatori(int posGiocatore1, int posGiocatore2, int muro_v1, int muro_v2) {
	int isVerticale, percorsoEsiste, finito = 0;
	Muro muroTmp;
	int lineaVittoriaGiocatore1[7] = {0, 1, 2, 3, 4, 5, 6};
	int lineaVittoriaGiocatore2[7] = {48, 49, 50, 51, 52, 53, 54};
	
	/* Aggiungo v1_new v2_new */
	if (muro_v1 != -1 && muro_v2 != -1) {
		MUROcreaSenzaAggiungere(&muroTmp, muro_v1, muro_v2);
		isVerticale = MUROisVertical(muroTmp);
		if (isVerticale == 1) {
			GRAPHaggiungiMuro(muro_v1, 0);
		} else {
			GRAPHaggiungiMuro(muro_v1, 1);
		}
	}
	
	percorsoEsiste = GRAPHisPathExists(posGiocatore1, lineaVittoriaGiocatore1);
	if (percorsoEsiste == 1) finito = 1;
	
	if (finito == 0) {
		/* Rimuovo v1_new v2_new */
		if (muro_v1 != -1 && muro_v2 != -1) {
			if (isVerticale == 1) {
				GRAPHrimuoviMuro(muro_v1, 0);
			} else {
				GRAPHrimuoviMuro(muro_v1, 1);
			}
		}
		return 0;
	}
	
	finito = 0; /* Resetto per nuovo giocatore */
	
	percorsoEsiste = GRAPHisPathExists(posGiocatore2, lineaVittoriaGiocatore2);
	if (percorsoEsiste == 1) finito = 1;
	
	if (finito == 0) {
		/* Rimuovo v1_new v2_new */
		if (muro_v1 != -1 && muro_v2 != -1) {
			if (isVerticale == 1) {
				GRAPHrimuoviMuro(muro_v1, 0);
			} else {
				GRAPHrimuoviMuro(muro_v1, 1);
			}
		}
		return 0;
	}

	/* Rimuovo v1_new v2_new */
	if (muro_v1 != -1 && muro_v2 != -1) {
		if (isVerticale == 1) {
			GRAPHrimuoviMuro(muro_v1, 0);
		} else {
			GRAPHrimuoviMuro(muro_v1, 1);
		}
	}
	return 1;
}


/**
	@brief			Funzione wrapper DFS sul grafo per ricerca percorso
							per la vittoria
	@parameter 	start:		Posizione di partenza, cioè quella del giocatore
	@parameter 	end :			Vettore con posizioni di vittoria
	@return 		Restituisce 1 se èsiste, 0 altrimenti
*/
int GRAPHisPathExists(int start, int end[]) {
    int visited[NUM_VERTICI] = {0};

    return isPathExistsDFS(start, end, visited);
}


/**
	@brief				Funzione ricorsiva che implementa una DFS sul grafo
								ricercando un percorso da la posizione start a una
								delle posizioni salvate nel vettore end
	@parameter 		start:			Posizione di partenza
	@parameter 		end:				Posizioni di arrivo
	@parameter 		visited:		Vettore flag che segna posizioni già visitate
	@return 			Restituisce 1 se esiste, 0 altrimenti
*/
int isPathExistsDFS(int start, const int end[], int visited[]) {
	int j, id1, id2, id3, id4;
	for (j = 0; j < 7; j++) { /* Verifico se ho raggiunto la fine */
		if (start == end[j]) {
			return 1; /* Fine raggiunta, percorso esiste */
		}	
	}

    visited[start] = 1; /* Segno vertice visitato */
	

	id1 = start - 8; /* Su */
 	id2 = start + 1; /* Destra */
	id3 = start + 8; /* Giù */
	id4 = start - 1; /* Sinistra */
	
	if (id1 >= 0 && id1 <= 63 && !visited[id1] && posCorretta(id1) && start >= 0 && start <= 63 && (start+1) >= 0 && (start+1) <= 63 && (graph.madj)[start][start+1] != 1) { // visito su
		if (isPathExistsDFS(id1, end, visited)) {
								return 1; /* Trovato un cammino */
		}
	}
	if (id2 >= 0 && id2 <= 63 && !visited[id2] && posCorretta(id2) && (start+1) >= 0 && (start+1) <= 63 && (start+1+8) >= 0 && (start+1+8) <= 63 && (graph.madj)[start+1][start+1+8] != 1) { // visito destra
		if (isPathExistsDFS(id2, end, visited)) {
								return 1; /* Trovato un cammino */
		}
	}
	if (id3 >= 0 && id3 <= 63 && !visited[id3] && posCorretta(id3) && (start+8) >= 0 && (start+8) <= 63 && (start+8+1) >= 0 && (start+8+1) <= 63 && (graph.madj)[start+8][start+8+1] != 1) { // visito giù
		if (isPathExistsDFS(id3, end, visited)) {
								return 1; /* Trovato un cammino */
		}
	}
	if (id4 >= 0 && id4 <= 63 && !visited[id4] && posCorretta(id4) && start >= 0 && start <= 63 && (start+8) >= 0 && (start+8) <= 63 && (graph.madj)[start][start+8] != 1) { // visito sinistra
		if (isPathExistsDFS(id4, end, visited)) {
								return 1; /* Trovato un cammino */
		}
	}
  return 0; /* Nessun cammino Trovato */
}


/**
	@brief				Funzione che verifica se il valore di ID
								è interno alla scacchiera
	@parameter		id:		Posizione
	@return				Restituisce 1 se posizione valida, 0 altrimenti
*/
int posCorretta(int id) {
	if (id % 8 == 7) return 0;
	if (id >= 56 && id <= 63) return 0;
	return 1;
}


int GRAPHgetNextPossibleMoveNPC(int start, int colore) {
	int mosseValide[5], flagDiagonale;
	int min = 64, max = -1, i;
	
	GRAPHgetMosseValide(GIOCATOREgetPosizione(colore), mosseValide, colore, &flagDiagonale);
	
	if (colore == ROSSO) { /* Scelgo valore più piccolo */
		for (i = 0; i < 5; i++) {
			if (mosseValide[i] < min) min = mosseValide[i];
		}
		return min;
	} else { /* Scelgo valore più grande */
		for (i = 0; i < 5; i++) {
			if (mosseValide[i] > max) max = mosseValide[i];
		}
		return max;
	}
	
}
