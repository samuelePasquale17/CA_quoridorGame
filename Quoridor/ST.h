/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef ST_H
#define ST_H


/**
	@brief		Per la conversione da ID del nodo del grafo alle coordinate sullo schermo LCD si
						utilizza una symble table dichiarata staticamente come matrice NUM_VERTICI x 2 
						di interi. Ogni riga della matrice contiene una coppia di interi che rappresentano
						le coordinate (x, y) del nodo i-esimo sullo schermo LCD.
*/


#define NUM_VERTICI 64 /* Il numero di vertici del grafo sono 64 */


/* Prototipi */
int STsearch(int vertice[2]);
int STgetVerticeX(int id);
int STgetVerticeY(int id);


#endif
