/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/

#ifndef QUORIDORGUI_H 
#define QUORIDORGUI_H


/**
	@brief			Tramite la seguente libreria si separa il layer di implementazione
							del gioco dalla rappresentazione grafica sullo schermo LCD della
							scheda lantiger. In particolare internamente si occupa di convertire
							gli ID dei vertici del grafo che è stato utilizzato per rappresentare
							la partita in coordinate sullo schermo LCD tramite le funzioni definite
							in ST.h
*/


/* Include */
#include "Quoridor.h"


/* Prototipi */
void GUIdisegnaScacchiera(void);
void GUIdisegnaTimer(int timerValue, uint16_t coloreTurno);
void GUIstampaTimer(int timerValue, int clear_prec, uint16_t colore);
void GUIdisegnaNumeroMuriGiocatori(void);
void GUIdisegnaNumeroMuriGiocatore(int coloreGiocatore, int clear_prec, int x_rett, int y_rett);
void GUIdisegnaGrafica(Partita partita);
void GUIdisegnaGiocatore(int coloreGiocatore);
void GUIdisegnaMosseGiocatore(int verticiValidi[]);
void GUIrimuoviMosseGiocatore(int verticiValidi[]);
void GUIrimuoviGiocatore(int coloreGiocatore);
void GUIstampaMessaggioVincitore(int coloreVincitore);
void GUIdisegnaMuro(Muro muro, uint16_t color);
void GUIcancellaMuro(Muro muro);
void GUIdisegnaQuadrato(int id, uint16_t colore, int pieno);


#endif
