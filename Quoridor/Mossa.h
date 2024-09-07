/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef MOSSA_H
#define MOSSA_H

/**
	@brief			In Mossa si gestisce la codifica della mossa del giocatore tramite
							un valore intero su 32 bit che contiene alcune informazioni tra cui:
							- PlayerID 										[24, 31]	identificativo del giocatore
							- PlayerMove / WallPlacement	[20, 23]	tipo di mossa del giocatore
							- Vertical / Horizontal				[16, 19]	direzione muro posizionato
							- Y														[8, 15]		coordinata X
							- X														[0, 7]		coordinata Y
*/


/* Include */
#include <stdint.h>


/**
	@brief		Struct che definisce un tipo di dato di tipo Mossa contenente un intero
						unsigned su 32 bit
*/
typedef struct mossa_s {
	uint32_t mossa;
} Mossa;


/* Prototipi */
void MOSSAcreaVoid(int numeroGiocatore);
void MOSSAcrea(int numeroGiocatore, int mossaGiocatore, int verticaleOrizzontale, int posizione);
Mossa MOSSAcrea_return(int numeroGiocatore, int mossaGiocatore, int isVerticale, int posizione);
Mossa MOSSAgetLastMossa(int numeroGiocatore);
void MOSSAinit(void);
uint32_t MOSSAgetMossaHandshake(void);
int MOSSAgetPlayerID(Mossa mossa);
int MOSSAisPlayerMode(Mossa mossa);
int MOSSAisVerticale(Mossa mossa);
int MOSSAgetPosizione(Mossa mossa, int isPlayer);

int MOSSA_da_XY_2_posizione(int x, int y, int isPlayer);
void MOSSA_da_posizione_2_XY(int posizione, int isPlayer, int* x_p, int* y_p);

int MOSSAisVoid(Mossa mossa);

#endif
