#include "QuoridorGUI.h"
#include "Menu.h"
#include "Giocatore.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "Graph.h"
#include "Modalita.h"
#include "../Joystick/Joystick.h"
#include "NPCcontroller.h"
#include "CANquoridor.h"


Partita partita;


int isMuroCorrente() {
	return (partita.modGiocatore == MOD_MURO);
}


/**
	@brief	Funzione che inizializza la partita, resettando i valori 
					dell'eventuale partita precedente. Partita è una valriabile
					globale in Quoridor.c
*/
void QUORIDORinit() {
	partita.initActive = INIT_MODE;
	partita.gameMode = 0;
	partita.partitaAttiva = 0;
	partita.currentMenu = MENU1;
	QUORIDORresetConfermaNPC();
	QUORIDORresetMosseNPC();
	QUORIDORabilitaComandiGiocatore();
	MENUinit(); // inizializzo il menu
	MODALITAinit();
}


/**
	
*/
void QUORIDORdecrementTimer() {
	GUIstampaTimer(partita.timer_value, 1, partita.turno_colorGUI);
	partita.timer_value--;
}


void QUORIDORswapTurno(int turnoGiocato) {
	int altroTurno, isVerticale;
	int spostamento;
	partita.timer_value = DURATA_TURNO_SECONDI;
	partita.mossaDiagonaleAttiva = 0;
	
	
	altroTurno = ROSSO;
	if (partita.turnoID == ROSSO) altroTurno = BLU;
	
	if (partita.modGiocatore == MOD_MURO) {
		// confermo il muro
		if (turnoGiocato == 1) {
			QUORIDORconfermaMuro();
		} else {
			// muro da non confermare
			GUIdisegnaMuro(MUROgetLastMuro(), White);
			isVerticale = MUROisVertical(MUROgetLastMuro());
			if (isVerticale == 1) {
				GRAPHrimuoviMuro(MUROgetVertice1(MUROgetLastMuro()), 0);
			} else {
				GRAPHrimuoviMuro(MUROgetVertice1(MUROgetLastMuro()), 1);
			}
			MUROrimuoviLastMuro(partita.turnoID);
			GUIdisegnaNumeroMuriGiocatori();
		}
	} else {
		// aggiorno posizione giocatore
		if (turnoGiocato == 1) {
			if (partita.posizioneOld == GIOCATOREgetPosizione(partita.turnoID)) {
				// giocatore non si è mosso ma ha confermato
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(altroTurno), altroTurno);
				GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), partita.verticiValidiMossaCorrente, partita.turnoID, &(partita.mossaDiagonaleAttiva));
				GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			} else {
				// giocatore si è mosso ed ha confermato
				GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				MOSSAcrea(GIOCATOREgetColore(partita.turnoID), 1, 0, GIOCATOREgetPosizione(partita.turnoID));
				GUIdisegnaGiocatore(partita.turnoID);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
				
				if (!GIOCATOREisNPC(partita.turnoID)) {
					spostamento = GIOCATOREgetPosizione(partita.turnoID) - partita.posizioneOld;
					if (spostamento >= 0) {
						if (spostamento == 8) {
							NPCCONTROLLERmossaAvversario(3);
						} else if (spostamento == 1) {
							NPCCONTROLLERmossaAvversario(2);
						}
					} else {
						if (spostamento == -8) {
							NPCCONTROLLERmossaAvversario(1);
						} else if (spostamento == -1) {
							NPCCONTROLLERmossaAvversario(4);
						}
					}
				}
			}

		} else {
			if (partita.mossaPending == 1) {
				// mossa fatta ma non confermata
				GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
				GIOCATOREsetPosizione(partita.turnoID, partita.posizioneOld);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(altroTurno), altroTurno);
				GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), partita.verticiValidiMossaCorrente, partita.turnoID, &(partita.mossaDiagonaleAttiva));
				GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				// ------
				// inserire di nuovo anche l'altro giocatore -----
				
				MOSSAcreaVoid(partita.turnoID);
				GUIdisegnaGiocatore(partita.turnoID);
				//GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				GUIdisegnaGiocatore(altroTurno);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			} else {
				// mossa non fatta, ne confermata
				GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				MOSSAcreaVoid(partita.turnoID);
				GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), partita.verticiValidiMossaCorrente, partita.turnoID, &(partita.mossaDiagonaleAttiva));
				GUIrimuoviMosseGiocatore(partita.verticiValidiMossaCorrente);
				GUIdisegnaGiocatore(partita.turnoID);
				GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			}

		}
		
	}
	
	partita.mossaPending = 0;
	partita.modGiocatore = MOD_GIOCATORE;
	
	if (partita.turno_colorGUI == Red) { // da red a blue
		partita.turno_colorGUI = Blue;
		partita.turnoID = BLU;
	} else {	// da blue a red
		partita.turno_colorGUI = Red;
		partita.turnoID = ROSSO;
	}
}


/**
	@brief	Funzione che resetta il contenuto della partita init e 
					blocca il conteggio dei timer
*/
void QUORIDORreset() {
	GRAPHreset();
	partita.partitaAttiva = 0;
	MODALITAinit();
	MOSSAinit(); // reset delle mosse
	
	disable_timer(TIMER1);
	reset_timer(TIMER1);
}


void QUORIDORgiocaTurno() {
	int verticiValidi[5], direzione; // al più 5 mosse valide
	int fine, flag = 0;
	int mosseValide[5];
	int res = 0, posizione, isVerticale;
	Mossa mossa;
	partita.mossaDiagonaleAttiva  = 0;
	GUIdisegnaGiocatore(partita.turnoID);
	
	partita.posizioneOld = GIOCATOREgetPosizione(partita.turnoID);
	if (partita.turno_colorGUI == Red) {	// turno rosso
		GRAPHgetMosseValide(GIOCATOREgetPosizione(ROSSO), verticiValidi, ROSSO, &(partita.mossaDiagonaleAttiva));
	} else { // turno blu
		GRAPHgetMosseValide(GIOCATOREgetPosizione(BLU), verticiValidi, BLU, &(partita.mossaDiagonaleAttiva));
	}
	GUIdisegnaMosseGiocatore(verticiValidi);

	if (MODALITAgetGameMode() == GAME_MODE_SINGLE_BOARD && MODALITAgetPlayerMode() == GAME_MODE_NPC) { /* SINGLE + NPC */
		if (GIOCATOREisNPC(partita.turnoID) == 1) { /* Giocatore del turno è NPC */
			QUORIDORdisabilitaComandiGiocatore(); /* Non disabilita INT0 */
			
			res = NPCCONTROLLERinserireMuro(&posizione, &isVerticale, !partita.turnoID);
			
			if (res == 1) { /* Posiziono muro */
				GRAPHgetMosseValide(GIOCATOREgetPosizione(PARTITAgetTurnoID()), mosseValide, PARTITAgetTurnoID(), &flag);
				GUIrimuoviMosseGiocatore(mosseValide);
				QUORIDORaggiungiMuroNPC(posizione, isVerticale);
				PARTITAsetModalita(MOD_MURO);
			
			} else { /* Posiziono giocatore */
				PARTITAsetModalita(MOD_GIOCATORE);
				direzione = GIOCATORE_NPC_getBestDirection(partita.turnoID);
				QUORIDORmuoviGiocatore(direzione);
			}
			GUIdisegnaNumeroMuriGiocatori();
			if (PARTITAgetModalita() == MOD_MURO) {
					QUORIDORconfermaMuro();
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
			} else if (PARTITAgetModalita() == MOD_GIOCATORE){ 
				fine = QUORIDORcheckWin();
				if (!fine) {
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else {
					QUORIDORreset();
				}
			}
			
		} else {
			QUORIDORresetMosseNPC();
			QUORIDORabilitaComandiGiocatore(); /* Riattivo i comandi del giocatore */
		}
	} else if (MODALITAgetGameMode() == GAME_MODE_TWO_BOARD && MODALITAgetPlayerMode() == GAME_MODE_HUMAN) { /* TWO + HUMAN */
		if (GIOCATOREisExternalBoard(partita.turnoID) == 1 && partita.turnoID != GIOCATOREgetColore(partita.turnoID)) { /* Giocatore del turno è EXTERNAL BOARD */
			QUORIDORdisabilitaComandiGiocatore(); /* Non disabilita INT0 */
			
			/* Leggo mossa */
			mossa = CANQreadMossa();
			QUORIDORgiocaMossaExternal(mossa);
			GUIdisegnaNumeroMuriGiocatori();
			


		} else {
			QUORIDORresetMosseNPC();
			QUORIDORabilitaComandiGiocatore(); /* Riattivo i comandi del giocatore */
			GUIdisegnaNumeroMuriGiocatori();
			


		}
	}	else if (MODALITAgetGameMode() == GAME_MODE_TWO_BOARD && MODALITAgetPlayerMode() == GAME_MODE_NPC) { /* TWO + NPC */
		if (GIOCATOREisExternalBoard(partita.turnoID) == 1) { /* Giocatore del turno è EXTERNAL BOARD */
			QUORIDORdisabilitaComandiGiocatore(); /* Non disabilita INT0 */
			
			/* Leggo mossa */
			mossa = CANQreadMossa();
			QUORIDORgiocaMossaExternal(mossa);
			GUIdisegnaNumeroMuriGiocatori();
		} else {
			QUORIDORdisabilitaComandiGiocatore(); /* Non disabilita INT0 */
			
			res = NPCCONTROLLERinserireMuro(&posizione, &isVerticale, !partita.turnoID);
			
			if (res == 1) { /* Posiziono muro */
				GRAPHgetMosseValide(GIOCATOREgetPosizione(PARTITAgetTurnoID()), mosseValide, PARTITAgetTurnoID(), &flag);
				GUIrimuoviMosseGiocatore(mosseValide);
				QUORIDORaggiungiMuroNPC(posizione, isVerticale);
				GUIdisegnaNumeroMuriGiocatori();
				mossa = MOSSAcrea_return(partita.turnoID, 0, !isVerticale, posizione);
				CANQsendMossa(mossa);
			} else { /* Posiziono giocatore */
				direzione = GIOCATORE_NPC_getBestDirection(partita.turnoID);
				QUORIDORmuoviGiocatore(direzione);
				mossa = MOSSAcrea_return(partita.turnoID, 1, 0, GIOCATOREgetPosizione(partita.turnoID));
				CANQsendMossa(mossa);
			}
			if (PARTITAgetModalita() == MOD_MURO) {
					QUORIDORconfermaMuro();
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
			} else if (PARTITAgetModalita() == MOD_GIOCATORE){ 
				fine = QUORIDORcheckWin();
				if (!fine) {
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else {
					QUORIDORreset();
				}
			}
		}
	}
}


void QUORIDORgiocaMossaExternal(Mossa mossa) {
	int fine;
	int playerID, isMossa, isVerticale, posizione;
	int flag, mosseValide[5], secondoVerticeOffset = 2;
	
	if (MOSSAisVoid(mossa) == 1) return; /* Mossa void */
	
	playerID = MOSSAgetPlayerID(mossa);
	isMossa = MOSSAisPlayerMode(mossa);
	isVerticale = MOSSAisVerticale(mossa);
	posizione = MOSSAgetPosizione(mossa, isMossa);
	
	if (partita.turnoID != playerID) {
		if (PARTITAgetModalita() == MOD_MURO) {
					QUORIDORconfermaMuro();
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
			} else if (PARTITAgetModalita() == MOD_GIOCATORE){ 
				fine = QUORIDORcheckWin();
				if (!fine) {
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else {
					QUORIDORreset();
				}
			}
		return; /* ID non corrispondono, errore */
	}
	if (isMossa == 1) { /* Muovere giocatore */
		GUIrimuoviGiocatore(partita.turnoID);
		GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), mosseValide, partita.turnoID, &flag);
		GUIrimuoviMosseGiocatore(mosseValide);
		GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
		GIOCATOREsetPosizione(partita.turnoID, posizione);
		GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
		GUIdisegnaGiocatore(partita.turnoID);
		if (PARTITAgetModalita() == MOD_MURO) {
					QUORIDORconfermaMuro();
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
			} else if (PARTITAgetModalita() == MOD_GIOCATORE){ 
				fine = QUORIDORcheckWin();
				if (!fine) {
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else {
					QUORIDORreset();
				}
			}
	} else { /* Mettere muro */
		if (isVerticale == 1) secondoVerticeOffset = 16;
		GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), mosseValide, partita.turnoID, &flag);
		GUIrimuoviMosseGiocatore(mosseValide);
		GRAPHaggiungiMuro(posizione, !isVerticale);
		MUROcrea(posizione, posizione + secondoVerticeOffset, partita.turnoID);
		GUIdisegnaMuro(MUROgetLastMuro(), Black);
		GUIdisegnaNumeroMuriGiocatori();
		if (PARTITAgetModalita() == MOD_MURO) {
					QUORIDORconfermaMuro();
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
			} else if (PARTITAgetModalita() == MOD_GIOCATORE){ 
				fine = QUORIDORcheckWin();
				if (!fine) {
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else {
					QUORIDORreset();
				}
			}
	}
}


void QUORIDORrimuoviMosseGiocatore() {
	int verticiValidi[5]; // al più 4 mosse valide
	if (partita.turno_colorGUI == Red) {	// turno rosso
		GRAPHgetMosseValide(GIOCATOREgetPosizione(ROSSO), verticiValidi, ROSSO, &(partita.mossaDiagonaleAttiva));
	} else { // turno blu
		GRAPHgetMosseValide(GIOCATOREgetPosizione(BLU), verticiValidi, BLU, &(partita.mossaDiagonaleAttiva));
	}
	
	// disegnare mosse a disposizione in giallo
	GUIrimuoviMosseGiocatore(verticiValidi);
}


int QUORIDORgetTimer() {
	return partita.timer_value;
}


int QUORIDORmuoviGiocatore(int direzione) {
	int v;
	int mossaValidaFlag = 0, i;

	
	// controllare se ok
	
	if (partita.mossaPending == 0) {
		// prima volta che muove
		//partita.posizioneOld = GIOCATOREgetPosizione(partita.turnoID);
		
		
		GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), partita.verticiValidiMossaCorrente, partita.turnoID, &(partita.mossaDiagonaleAttiva));
		v = GRAPHgetVerticeDirezione(GIOCATOREgetPosizione(partita.turnoID), direzione);
	
		// controllo se mossa valida senza salto
		for (i = 0; i < 5 && v != -1 && (mossaValidaFlag == 0); i++) {
			if (partita.verticiValidiMossaCorrente[i] != -1 && v == partita.verticiValidiMossaCorrente[i]) mossaValidaFlag = 1;
		}
		
		if (mossaValidaFlag == 0) v = GRAPHgetVerticeDirezioneConSalto(GIOCATOREgetPosizione(partita.turnoID), direzione);

		// controllo se mossa valida con salto
		for (i = 0; i < 5 && v != -1 && (mossaValidaFlag == 0); i++) {
			if (partita.verticiValidiMossaCorrente[i] != -1 && v == partita.verticiValidiMossaCorrente[i]) mossaValidaFlag = 1;
		}
		
		if (mossaValidaFlag == 1) {
			//partita.posizioneOld = GIOCATOREgetPosizione(partita.turnoID);
			GUIdisegnaQuadrato(GIOCATOREgetPosizione(partita.turnoID), Yellow, 1);
			for (i = 0; i < 5; i++) {
				if ((partita.verticiValidiMossaCorrente)[i] == v) {
					(partita.verticiValidiMossaCorrente)[i] = GIOCATOREgetPosizione(partita.turnoID);
				}
			}
			GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GIOCATOREsetPosizione(partita.turnoID, v);
			GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GUIdisegnaGiocatore(partita.turnoID);
			partita.mossaPending = 1;
		} else {
			// mossa non valida, non faccio nulla
			GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
		}
	} else {
		// mossa pending
		v = GRAPHgetVerticeDirezione(GIOCATOREgetPosizione(partita.turnoID), direzione);
	
		// controllo se mossa valida senza salto
		for (i = 0; i < 5 && v != -1 && (mossaValidaFlag == 0); i++) {
			if (partita.verticiValidiMossaCorrente[i] != -1 && v == partita.verticiValidiMossaCorrente[i]) mossaValidaFlag = 1;
		}
		
		if (mossaValidaFlag == 0) v = GRAPHgetVerticeDirezioneConSalto(GIOCATOREgetPosizione(partita.turnoID), direzione);

		// controllo se mossa valida con salto
		for (i = 0; i < 5 && v != -1 && (mossaValidaFlag == 0); i++) {
			if (partita.verticiValidiMossaCorrente[i] != -1 && v == partita.verticiValidiMossaCorrente[i]) mossaValidaFlag = 1;
		}
		
		if (mossaValidaFlag == 1) {
			//partita.posizioneOld = GIOCATOREgetPosizione(partita.turnoID);
			GUIdisegnaQuadrato(GIOCATOREgetPosizione(partita.turnoID), Yellow, 1);
			for (i = 0; i < 5; i++) {
				if ((partita.verticiValidiMossaCorrente)[i] == v) {
					(partita.verticiValidiMossaCorrente)[i] = GIOCATOREgetPosizione(partita.turnoID);
				}
			}
			GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GIOCATOREsetPosizione(partita.turnoID, v);
			GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GUIdisegnaGiocatore(partita.turnoID);
		} else {
			// massa non valida
			GRAPHrimuoviGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
			GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
		}
	}
	return mossaValidaFlag;
}


void QUORIDORturnoNonGiocato() {
	int verticiValidi[5];

	if (partita.mossaPending == 1) {
		GRAPHgetMosseValide(partita.posizioneOld, verticiValidi, partita.turnoID, &(partita.mossaDiagonaleAttiva));
		GUIrimuoviMosseGiocatore(verticiValidi);
		GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
	} else {
		GRAPHgetMosseValide(GIOCATOREgetPosizione(partita.turnoID), verticiValidi, partita.turnoID, &(partita.mossaDiagonaleAttiva));
		GUIrimuoviMosseGiocatore(verticiValidi);
		GRAPHinserisciGiocatore(GIOCATOREgetPosizione(partita.turnoID), partita.turnoID);
	}
}


int QUORIDORcheckWin() {
	
	if (GRAPHverticeToccaLatoInferiore(GIOCATOREgetPosizione(BLU)) == 1) {
		GUIstampaMessaggioVincitore(BLU); // vince il blu
		return 1;
	}
	if (GRAPHverticeToccaLatoSuperiore(GIOCATOREgetPosizione(ROSSO)) == 1) {
		GUIstampaMessaggioVincitore(ROSSO); // vince il rosso
		
		return 1;
	}
	return 0;
}


uint16_t PARTITAgetTurnoGUI() {
	return partita.turno_colorGUI;
}


int PARTITAgetTurnoID() {
	return partita.turnoID;
}


int PARTITAgetModalita() {
	return partita.modGiocatore;
}


void PARTITAsetModalita(int mod) {
	partita.modGiocatore = mod;
	partita.mossaDiagonaleAttiva = 0;
}


void QUORIDORconfermaMuro() {
	int isVertical, horiz;
	GUIdisegnaMuro(MUROgetLastMuro(), Black);
	isVertical = MUROisVertical(MUROgetLastMuro());
	if (isVertical == 1) {
		horiz = 0;
	} else {
		horiz = 1;
	}
	MOSSAcrea(partita.turnoID, 1, horiz, MUROgetVertice1(MUROgetLastMuro()));
}


void QUORIDORrimuoviMuro() {
	int v = MUROgetVertice1(MUROgetLastMuro());
	int isVerticale = MUROisVertical(MUROgetLastMuro());
	if (isVerticale == 1) {
		GRAPHrimuoviMuro(v, 0);
	} else {
		GRAPHrimuoviMuro(v, 1);
	}
	GUIcancellaMuro(MUROgetLastMuro());
	MUROrimuoviLastMuro(partita.turnoID);
	GUIdisegnaNumeroMuriGiocatori();
}


void QUORIDORaggiungiMuro() {
	int posMuro;
	int nMuriGiocatore = GIOCATOREgetNumeroMuri(partita.turnoID);
	if (nMuriGiocatore < 8) {
		posMuro = GRAPHgetPosRandomValidMuro(GIOCATOREgetPosizione(ROSSO), GIOCATOREgetPosizione(BLU));		// controllo anche già che quel muro non causi cicli
		MUROcrea(posMuro, posMuro+2, partita.turnoID);
		GRAPHaggiungiMuro(posMuro, 1); // aggiungiamo muro al grafo
		GUIdisegnaMuro(MUROgetLastMuro(), Magenta);
		GUIdisegnaNumeroMuriGiocatori();
	}
}


void QUORIDORaggiungiMuroNPC(int posizione, int isVerticale) {
	int posMuro;
	int nMuriGiocatore = GIOCATOREgetNumeroMuri(partita.turnoID);
	if (nMuriGiocatore < 8) {
		posMuro = posizione;
		MUROcrea(posMuro, posMuro+2, partita.turnoID);
		if (isVerticale == 1) {
			MUROruotaMuro();
		}
		GRAPHaggiungiMuro(posMuro, 1); // aggiungiamo muro al grafo
		GUIdisegnaMuro(MUROgetLastMuro(), Black);
		GUIdisegnaNumeroMuriGiocatori();
	}
}


int muroNonPresente(Muro muroCorrente) {
	return MUROmuroPresente(muroCorrente);
}


void QUORIDORruotaMuro() {
	int v1 = MUROgetVertice1(MUROgetLastMuro()), v2 = MUROgetVertice2(MUROgetLastMuro());
	int eraVerticale = MUROisVertical(MUROgetLastMuro());
	int v1_new, v2_new;
	Muro muroRuotato;
	
	if (eraVerticale == 1) {
		// da verticale a orizzontale
		v1_new = v1;
		v2_new = v1+2;
	} else {
		// da orizzontale a verticale
		v1_new = v1;
		v2_new = v1+16;
	}
	
	MUROcreaSenzaAggiungere(&muroRuotato, v1_new, v2_new);
	
	if (GRAPHcheckPosizioneMuro(v1_new, v2_new, v1, v2, GIOCATOREgetPosizione(ROSSO), GIOCATOREgetPosizione(BLU)) == 1 && MUROmuroPresente(muroRuotato) != 1 && MUROsiSovrappone(muroRuotato, MUROgetLastMuro()) != 1) {

		// rotazione valida
		QUORIDORrimuoviMuro();
		if (eraVerticale == 1) {
			MUROcrea(v1, v1+2, partita.turnoID);
			GRAPHaggiungiMuro(v1, 1); // aggiungiamo muro al grafo
		} else {
			MUROcrea(v1, v1+2, partita.turnoID);
			MUROruotaMuro();
			GRAPHaggiungiMuro(v1, 0); // aggiungiamo muro al grafo
		}
		GUIdisegnaMuro(MUROgetLastMuro(), Magenta);
		GUIdisegnaNumeroMuriGiocatori();

	}
}


int PARTITAgetGiocatore1() {
	return ROSSO;
}


int PARTITAgetGiocatore2() {
	return BLU;
}


int QUORIDORisPartitaAttiva() {
	return (partita.partitaAttiva == 1);
}


/**
	@direzione =1 SU, =2 DESTRA, =3 GIU, 4=SINISTRA
*/
void QUORIDORmuoviMuro(int direzione) {
	int v1_new, v2_new, v1 = MUROgetVertice1(MUROgetLastMuro()), v2 = MUROgetVertice2(MUROgetLastMuro()), i = 0, finito = 0;
	Muro muroMosso;
	
	for (i = 0; i < 7 && !finito; i++) {
		if (direzione == 1) { // su
			v1_new = v1 - 8 - (i*8);
			v2_new = v2 - 8 - (i*8);
		} else if (direzione == 2) { // destra
			v1_new = v1 + 1 + i;
			v2_new = v2 + 1 + i;
		} else if (direzione == 3) { // giu
			v1_new = v1 + 8 + (i*8);
			v2_new = v2 + 8 + (i*8);
		} else if (direzione == 4) { // sinistra
			v1_new = v1 - 1 - i;
			v2_new = v2 - 1 - i;
		}
		
		MUROcreaSenzaAggiungere(&muroMosso, v1_new, v2_new);
		
		if (MUROmuroPresente(muroMosso) != 1 && MUROsiSovrappone(muroMosso, MUROgetLastMuro()) != 1 && GRAPHcheckPosizioneMuro(v1_new, v2_new, v1, v2, GIOCATOREgetPosizione(ROSSO), GIOCATOREgetPosizione(BLU)) == 1) finito = 1;
	
	}
	
	if (finito == 1) {
		// nuova posizione valida
			QUORIDORrimuoviMuro();
			
			// aggiunta nuovo muro
			MUROcrea(v1_new, v2_new, partita.turnoID);
			
			if (MUROisVertical(MUROgetLastMuro()) == 1) {
				GRAPHaggiungiMuro(v1_new, 0); // aggiungiamo muro al grafo
			} else {
				GRAPHaggiungiMuro(v1_new, 1); // aggiungiamo muro al grafo
			}
			GUIdisegnaMuro(MUROgetLastMuro(), Magenta);
			GUIdisegnaNumeroMuriGiocatori();
	}

}


void PARTITAsetMossaPending(int val) {
	partita.mossaPending = val;
}


int PARTITAgetMossaPending() {
	return partita.mossaPending;
}


int PARTITAgetMossaDiagonaleAttiva(void) {
	return partita.mossaDiagonaleAttiva;
}


/**
	Funzione che disegna il menu 1
*/
void QUORIDORdisegnaMenu() {
	MENUdisegnaMenuSelBoard(partita.currentMenu);
}


int QUORIDORisInit(void) {
	return (partita.initActive == INIT_MODE);
}


void QUORIDORsceltaMenu() {
	int sceltaUtente;
	
	sceltaUtente = MENUgetPosCursore(partita.currentMenu);
	
	// gestire 3 scelte differenti in base alla prima scelta le successive due
	if (partita.currentMenu == MENU1) {
		// menu 1
		if (sceltaUtente == BTN_UP) {
			MODALITAsetGameMode(SINGLE_BOARD);
		} else {
			MODALITAsetGameMode(TWO_BOARDS);
		}
		partita.currentMenu = MENU2;
		MENUdisegnaMenuSelBoard(MENU2);
	} else if (partita.currentMenu == MENU2) {
		if (sceltaUtente == BTN_UP) {
			MODALITAsetPlayerType(HUMAN);
		} else {
			MODALITAsetPlayerType(NPC);
		}
		QUORIDORstart();
	}
}


void QUORIDORupdateBtnMenu(int btn_dir) {
	MENUsetPosCursore(btn_dir, partita.currentMenu);
}


void QUORIDORstart() {
	if (MODALITAgetGameMode() == SINGLE_BOARD) {
		if (MODALITAgetPlayerMode() == HUMAN) {
			// SINGLE BOARD + HUMAN
			QUORIDORstartSingleBoardHuman();
		} else if (MODALITAgetPlayerMode() == NPC) {
			// SINGLE BOARD + NPC
			QUORIDORstartSingleBoardNPC();
		}
	} else if (MODALITAgetGameMode() == TWO_BOARDS) {
		if (MODALITAgetPlayerMode() == HUMAN) {
			// TWO BOARDS + HUMAN
			QUORIDORstartTwoBoardsHuman();
		} else if (MODALITAgetPlayerMode() == NPC) {
			// TWO BOARDS + NPC
			QUORIDORstartTwoBoardsNPC();
		}
	}
}


/**
	funzione che fa partire il gioco in single board + human
*/
void QUORIDORstartSingleBoardHuman() {
	partita.initActive = NOT_INIT_MODE;
	partita.timer_value = DURATA_TURNO_SECONDI;
	partita.turno_colorGUI = Red;
	partita.turnoID = ROSSO;
	partita.modGiocatore = MOD_GIOCATORE;
	partita.posizioneOld = -1;
	partita.mossaDiagonaleAttiva = 0;
	partita.mossaPending = 0;
	partita.partitaAttiva = 1;
	
	
	
	// muri
	MUROinitMuri();
	
	// mosse
	MOSSAinit();
 
	
	// creazione giocatori
	
	GIOCATOREcrea(ROSSO, 0, 0); /* No NPC */
	GIOCATOREcrea(BLU, 0, 0);
	
	// caricamento grafo
	GRAPHload();
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(ROSSO), ROSSO); // aggiungiamo giocatori al grafo
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(BLU), BLU);
	
	// disegno grafica
	GUIdisegnaGrafica(partita);
	
	// disegno giocatori
	GUIdisegnaGiocatore(ROSSO);
	GUIdisegnaGiocatore(BLU);
	
	// partita iniziata
	partita.partitaAttiva = 1;

	enable_timer(TIMER1);
	
	MODALITAsetGameMode(GAME_MODE_SINGLE_BOARD);
	MODALITAsetPlayerType(GAME_MODE_HUMAN);
	QUORIDORgiocaTurno();     // START PARTITA
}


/**
	funzione che fa partire il gioco in single board + NPC
*/
void QUORIDORstartSingleBoardNPC() {
	partita.initActive = NOT_INIT_MODE;
	partita.timer_value = DURATA_TURNO_SECONDI;
	partita.turno_colorGUI = Red;
	partita.turnoID = ROSSO;
	partita.modGiocatore = MOD_GIOCATORE;
	partita.posizioneOld = -1;
	partita.mossaDiagonaleAttiva = 0;
	partita.mossaPending = 0;
	partita.partitaAttiva = 1;
	NPCControllerInit();
	
	
	// muri
	MUROinitMuri();
	
	// mosse
	MOSSAinit();
 
	
	// creazione giocatori
	
	GIOCATOREcrea(ROSSO, 0, 0);
	GIOCATOREcrea(BLU, 1, 0); /* Flag 1 per impostare che è un NPC */
	
	// caricamento grafo
	GRAPHload();
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(ROSSO), ROSSO); // aggiungiamo giocatori al grafo
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(BLU), BLU);
	
	// disegno grafica
	GUIdisegnaGrafica(partita);
	
	// disegno giocatori
	GUIdisegnaGiocatore(ROSSO);
	GUIdisegnaGiocatore(BLU);
	
	// partita iniziata
	partita.partitaAttiva = 1;
	
	MODALITAsetGameMode(GAME_MODE_SINGLE_BOARD);
	MODALITAsetPlayerType(GAME_MODE_NPC);

	enable_timer(TIMER1);
	QUORIDORgiocaTurno();     // START PARTITA
}


/**
	@brief			Funzione che disabilita i comandi del giocatore,
							non permettendogli di usare Joystick, BTN1 e BTN2.
							Questa funzione va utilizzata nel momento in cui il
							turno è di un NPC
*/
void QUORIDORdisabilitaComandiGiocatore(void) {
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT2_IRQn);
	joystick_disable(1); /* 5 eventi possibili con il Joystick */
	joystick_disable(2);
	joystick_disable(3);
	joystick_disable(4);
	//joystick_disable(5);
}


/**
	@brief			Funzione che abilita i comandi del giocatore,
							permettendogli di usare Joystick, BTN1 e BTN2.
							Questa funzione va utilizzata nel momento in cui il
							turno passa da NPC a Player reale
*/
void QUORIDORabilitaComandiGiocatore(void) {
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);	
	joystick_enable(1); /* 5 eventi possibili con il Joystick */
	joystick_enable(2);
	joystick_enable(3);
	joystick_enable(4);
	//joystick_enable(5);
}


void QUORIDORenableNPCdirection(int direzione) {
	switch (direzione) {
		case 1: /* Up */
			partita.flagDirezioneNPC_Up = 1;
		break;
		case 2: /* Right */
			partita.flagDirezioneNPC_Right = 1;
		break;
		case 3: /* Down */
			partita.flagDirezioneNPC_Down = 1;
		break;
		case 4: /* Left */
			partita.flagDirezioneNPC_Left = 1;
		break;
		default:
				/* -- default -- */
		break;
	}
}


void QUORIDORresetMosseNPC() {
	partita.flagDirezioneNPC_Up = 0;
	partita.flagDirezioneNPC_Down = 0;
	partita.flagDirezioneNPC_Left = 0;
	partita.flagDirezioneNPC_Right = 0;
}


int PARTITAis_NPC_up() {
	return partita.flagDirezioneNPC_Up;
}


int PARTITAis_NPC_down() {
	return partita.flagDirezioneNPC_Down;
}


int PARTITAis_NPC_left() {
	return partita.flagDirezioneNPC_Left;
}


int PARTITAis_NPC_right() {
	return partita.flagDirezioneNPC_Right;
}


void QUORIDORconfirmNPCdirection() {
	partita.flagDirezioneNPC_Confirmed = 1;
}


int PARTITAis_NPC_confirmed() {
	return partita.flagDirezioneNPC_Confirmed;
}


void QUORIDORresetConfermaNPC() {	
	partita.flagDirezioneNPC_Confirmed = 0;
}

void QUORIDORstartTwoBoardsHuman(void) {
	
	
	
	
	// handshake
	
	reset_timer(TIMER0);
	enable_timer(TIMER0);
	
	CANQhandshake();

	
	
	partita.initActive = NOT_INIT_MODE;
	partita.timer_value = DURATA_TURNO_SECONDI;
	partita.turno_colorGUI = Red;
	partita.turnoID = ROSSO;
	partita.modGiocatore = MOD_GIOCATORE;
	partita.posizioneOld = -1;
	partita.mossaDiagonaleAttiva = 0;
	partita.mossaPending = 0;
	partita.partitaAttiva = 1;
	
	
	
	// muri
	MUROinitMuri();
	
	// mosse
	MOSSAinit();
 
	
	// creazione giocatori
	
	GIOCATOREcrea(ROSSO, 0, 0); /* Io sono il ROSSO -> No NPC */ 
	GIOCATOREcrea(BLU, 0, 1); /* Avversario BLU -> External BOARD */
	
	// caricamento grafo
	GRAPHload();
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(ROSSO), ROSSO); // aggiungiamo giocatori al grafo
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(BLU), BLU);
	
	// disegno grafica
	GUIdisegnaGrafica(partita);
	
	// disegno giocatori
	GUIdisegnaGiocatore(ROSSO);
	GUIdisegnaGiocatore(BLU);
	
	// partita iniziata
	partita.partitaAttiva = 1;

	enable_timer(TIMER1);
	
	MODALITAsetGameMode(GAME_MODE_TWO_BOARD);
	MODALITAsetPlayerType(GAME_MODE_HUMAN);
	

	QUORIDORgiocaTurno();     // START PARTITA
}


void QUORIDORstartTwoBoardsNPC(void) {
	
	
	// handshake
	
	reset_timer(TIMER0);
	enable_timer(TIMER0);
	
	CANQhandshake();
	
	
	partita.initActive = NOT_INIT_MODE;
	partita.timer_value = DURATA_TURNO_SECONDI;
	partita.turno_colorGUI = Red;
	partita.turnoID = ROSSO;
	partita.modGiocatore = MOD_GIOCATORE;
	partita.posizioneOld = -1;
	partita.mossaDiagonaleAttiva = 0;
	partita.mossaPending = 0;
	partita.partitaAttiva = 1;
	
	
	
	// muri
	MUROinitMuri();
	
	// mosse
	MOSSAinit();
 
	
	// creazione giocatori
	
	GIOCATOREcrea(ROSSO, 1, 0); /* Io sono il ROSSO -> NPC */ 
	GIOCATOREcrea(BLU, 0, 1); /* Avversario BLU -> External BOARD */
	
	// caricamento grafo
	GRAPHload();
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(ROSSO), ROSSO); // aggiungiamo giocatori al grafo
	GRAPHinserisciGiocatore(GIOCATOREgetPosizione(BLU), BLU);
	
	// disegno grafica
	GUIdisegnaGrafica(partita);
	
	// disegno giocatori
	GUIdisegnaGiocatore(ROSSO);
	GUIdisegnaGiocatore(BLU);
	
	// partita iniziata
	partita.partitaAttiva = 1;

	enable_timer(TIMER1);
	
	MODALITAsetGameMode(GAME_MODE_TWO_BOARD);
	MODALITAsetPlayerType(GAME_MODE_NPC);
	QUORIDORgiocaTurno();     // START PARTITA
}
