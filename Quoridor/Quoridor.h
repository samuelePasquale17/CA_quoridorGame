/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#ifndef QUORIDOR_H 
#define QUORIDOR_H


/**
	@brief			La partita viene rappresentata da una variabile di tipo Partita
							che contriene diverse informazioni legate alla partita corrente.
							Nel file Quoridor.c si definiscono le funzioni principali del gioco
							per quanto riguarda le mosse del giocatore e le diverse possibili
							scelte
*/


/* Includes */
#include "Giocatore.h"
#include "Muro.h"
#include <stdint.h>


/* Defines */
#define ROSSO 0
#define BLU 1
#define BTN_UP 0
#define BTN_DOWN 1
#define MENU1 1
#define MENU2 2
#define SINGLE_BOARD 1
#define TWO_BOARDS 2
#define HUMAN 0
#define NPC 1
#define DURATA_TURNO_SECONDI 20 
#define MOD_MURO 0
#define MOD_GIOCATORE 1
#define INIT_MODE 6 /* Impostazione di default solo in fase di inizializzazione */
#define NOT_INIT_MODE 0


/**
	@brief			Definizione del tipo di dato Partita che rappresenta la partita in corso 
*/
typedef struct partita_s {
	int timer_value;											/* Tempo turno */
	uint16_t turno_colorGUI;							/* Giocatore in gioco, di default parte il rosso */
	int turnoID; 													/* Giocatore di turno */
	int modGiocatore;											/* = 1 se modalità giocatore, = 0 se modalità muro */
	int partitaAttiva;										/* Flag che indica se la partita è in gioco o meno */
	int verticiValidiMossaCorrente[5]; 		/* Al più 4 mosse valide + la propria posizione */
	int mossaPending;											/* Flag che indica se la mossa deve essere ancora confermata */
	int posizioneOld;
	int mossaDiagonaleAttiva;
	int gameMode;
	int initActive;
	int currentMenu;
	
	int flagDirezioneNPC_Up;
	int flagDirezioneNPC_Down;
	int flagDirezioneNPC_Left;
	int flagDirezioneNPC_Right;
	int flagDirezioneNPC_Confirmed;

} Partita;


/* Prototipi */
int isMuroCorrente(void);
void QUORIDORinit(void);
void QUORIDORdecrementTimer(void);
void QUORIDORswapTurno(int turnoGiocato);
void QUORIDORreset(void);
void QUORIDORgiocaTurno(void);
void QUORIDORrimuoviMosseGiocatore(void);
int QUORIDORgetTimer(void);
int QUORIDORmuoviGiocatore(int direzione);
void QUORIDORturnoNonGiocato(void);
int QUORIDORcheckWin(void);
int PARTITAgetModalita(void);
void PARTITAsetModalita(int mod);
void QUORIDORconfermaMuro(void);
void QUORIDORrimuoviMuro(void);
void QUORIDORaggiungiMuro(void);
void QUORIDORruotaMuro(void);
int PARTITAgetGiocatore1(void);
int PARTITAgetGiocatore2(void);
int QUORIDORisPartitaAttiva(void);
uint16_t PARTITAgetTurnoGUI(void);
int PARTITAgetTurnoID(void);
void QUORIDORmuoviMuro(int direzione);
void PARTITAsetMossaPending(int val);
int PARTITAgetMossaPending(void);
int PARTITAgetMossaDiagonaleAttiva(void);
int muroNonPresente(Muro muroCorrente);
void PARTITAsetGameMode(int gameMode);
void QUORIDORstartSingleBoardHuman(void);
void QUORIDORstartSingleBoardNPC(void);
void QUORIDORstartTwoBoardsHuman(void);
void QUORIDORstartTwoBoardsNPC(void);


int QUORIDORisInit(void);
int PARTITAisSetNPC(Partita partita);
int PARTITAisTwoBoard(Partita partita);
void QUORIDORdisegnaMenu(void);


void QUORIDORsceltaMenu(void);
void QUORIDORupdateBtnMenu(int btn_dir);


void QUORIDORstart(void);


void QUORIDORdisabilitaComandiGiocatore(void);
void QUORIDORabilitaComandiGiocatore(void);
void QUORIDORresetMosseNPC(void);
void QUORIDORenableNPCdirection(int direzione);

int PARTITAis_NPC_up(void);
int PARTITAis_NPC_down(void);
int PARTITAis_NPC_left(void);
int PARTITAis_NPC_right(void);
void QUORIDORconfirmNPCdirection(void);
int PARTITAis_NPC_confirmed(void);
void QUORIDORresetConfermaNPC(void);
void QUORIDORaggiungiMuroNPC(int posizione, int isVerticale);
int QUORIDORisCurrentNPC(void);
void QUORIDORgiocaMossaExternal(Mossa mossa);


#endif

