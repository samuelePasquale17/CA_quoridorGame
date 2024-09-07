/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


/* Include */
#include "ST.h"


/**
	@brief		Matrice di interi che contiene per ogni vertice del grafo le sue coordinate sullo 
						schermo LCD
*/
int tabHash[NUM_VERTICI][2] = {
        {2, 2},
        {36, 2},
        {70, 2},
        {104, 2},
        {138, 2},
        {172, 2},
        {206, 2},
        {240, 2},
        {2, 36},
        {36, 36},
        {70, 36},
        {104, 36},
        {138, 36},
        {172, 36},
        {206, 36},
        {240, 36},
        {2, 70},
        {36, 70},
        {70, 70},
        {104, 70},
        {138, 70},
        {172, 70},
        {206, 70},
        {240, 70},
        {2, 104},
        {36, 104},
        {70, 104},
        {104, 104},
        {138, 104},
        {172, 104},
        {206, 104},
        {240, 104},
        {2, 138},
        {36, 138},
        {70, 138},
        {104, 138},
        {138, 138},
        {172, 138},
        {206, 138},
        {240, 138},
        {2, 172},
        {36, 172},
        {70, 172},
        {104, 172},
        {138, 172},
        {172, 172},
        {206, 172},
        {240, 172},
        {2, 206},
        {36, 206},
        {70, 206},
        {104, 206},
        {138, 206},
        {172, 206},
        {206, 206},
        {240, 206},
        {2, 240},
        {36, 240},
        {70, 240},
        {104, 240},
        {138, 240},
        {172, 240},
        {206, 240},
        {240, 240}
};


/**
	@brief			Funzione che date le coordinate x, y dello schermo LCD restituisce l'ID del vertice
							del grafo.
	@parameter 	vertice: 	Vettore di 2 interi che contiene le coordinate (x, y)
	@return			ID del vertice
*/
int STsearch(int vertice[2]) {
	int i;
	for (i = 0; i < NUM_VERTICI; i++) {
		if (vertice[0] == tabHash[i][0] && vertice[1] == tabHash[i][1]) return i;
	}
	return -1;
}


/**
	@brief			Funzione che dato l'ID del vertice del grafo restituisce la coordinata x dello
							schermo LCD
	@parameter 	id: 				ID del vertice del grafo
	@return 		Coordinata x
*/
int STgetVerticeX(int id) {
	if (id >= NUM_VERTICI) return -1;
	return tabHash[id][0];
}


/**
	@brief			Funzione che dato l'ID del vertice del grafo restituisce la coordinata y dello
							schermo LCD
	@parameter 	id: 				ID del vertice del grafo
	@return 		Coordinata y
*/
int STgetVerticeY(int id) {
	if (id >= NUM_VERTICI) return -1;
	return tabHash[id][1];
}
