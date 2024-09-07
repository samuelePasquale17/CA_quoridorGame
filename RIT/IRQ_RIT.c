#include "lpc17xx.h"
#include "RIT.h"
#include <stdlib.h>
#include "../joystick/joystick.h"
#include "../Quoridor/Quoridor.h"
#include "../Quoridor/Modalita.h"
#include "../Quoridor/CANquoridor.h"



volatile int btn_down_counter[3];		// vettore da dichiarare extern negli altri files


void RIT_IRQHandler (void)
{	
	/* ---------------------------------- joystick management ---------------------------------- */
	static int J_down = 0;
	static int J_up = 0;
	static int J_left = 0;
	static int J_right = 0;
	static int J_press = 0;
	
	static int J_up_left = 0;
	static int J_up_right = 0;
	static int J_down_left = 0;
	static int J_down_right = 0;
	
	int fine;
	int altroTurno;
	Mossa mossa;
	

	if ((((LPC_GPIO1->FIOPIN & (1<<29)) == 0) && ((LPC_GPIO1->FIOPIN & (1<<27)) == 0) && PARTITAgetMossaDiagonaleAttiva() == 1) || (PARTITAis_NPC_up() == 1 && PARTITAis_NPC_left() == 1 && PARTITAis_NPC_right() == 0)) { // joystick up + left
		J_up_left++;
		switch(J_up_left){
			case 1:
				// do something 
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						altroTurno = !(PARTITAgetTurnoID());
						if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) - 8)) { //se giocatore sopra -> left + up
							QUORIDORmuoviGiocatore(4); // left
							QUORIDORmuoviGiocatore(1); // up 
						} else if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) - 1)) { // se giocatore a sinistra -> up + left
							QUORIDORmuoviGiocatore(1); // up 
							QUORIDORmuoviGiocatore(4); // left
						}
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_up_left = 0;
	}
	
	
	if ((((LPC_GPIO1->FIOPIN & (1<<29)) == 0) && ((LPC_GPIO1->FIOPIN & (1<<28)) == 0) && PARTITAgetMossaDiagonaleAttiva() == 1) || (PARTITAis_NPC_up() == 1 && PARTITAis_NPC_left() == 0 && PARTITAis_NPC_right() == 1)) { // joystick up + right
		J_up_right++;
		switch(J_up_right){
			case 1:
				// do something 
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						altroTurno = !(PARTITAgetTurnoID());
						if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) - 8)) { //se giocatore sopra -> right + up
							QUORIDORmuoviGiocatore(2); // right
							QUORIDORmuoviGiocatore(1); // up 
						} else if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) + 1)) { // se giocatore a destra -> up + right
							QUORIDORmuoviGiocatore(1); // up 
							QUORIDORmuoviGiocatore(2); // right
						}
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_up_right = 0;
	}
	

	if ((((LPC_GPIO1->FIOPIN & (1<<26)) == 0) && ((LPC_GPIO1->FIOPIN & (1<<27)) == 0) && PARTITAgetMossaDiagonaleAttiva() == 1) || (PARTITAis_NPC_down() == 1 && PARTITAis_NPC_left() == 1 && PARTITAis_NPC_right() == 0)) { // joystick down + left
		J_down_left++;
		switch(J_down_left){
			case 1:
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						altroTurno = !(PARTITAgetTurnoID());
						if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) + 8)) { // se giocatore sotto -> left + down
							QUORIDORmuoviGiocatore(4); // left
							QUORIDORmuoviGiocatore(3); // down
						} else if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) - 1)) { // se giocatore a left -> down + left
							QUORIDORmuoviGiocatore(3); // down
							QUORIDORmuoviGiocatore(4); // left
						}
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_down_left = 0;
	}

	if ((((LPC_GPIO1->FIOPIN & (1<<26)) == 0) && ((LPC_GPIO1->FIOPIN & (1<<28)) == 0) && PARTITAgetMossaDiagonaleAttiva() == 1) || (PARTITAis_NPC_down() == 1 && PARTITAis_NPC_left() == 0 && PARTITAis_NPC_right() == 1)) { // joystick down + right
		J_down_right++;
		switch(J_down_right){
			case 1:
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						altroTurno = !(PARTITAgetTurnoID());
						if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) + 8)) { // se giocatore sotto -> right + down
							QUORIDORmuoviGiocatore(2); // right
							QUORIDORmuoviGiocatore(3); // down
						} else if (GIOCATOREgetPosizione(altroTurno) == (GIOCATOREgetPosizione(PARTITAgetTurnoID()) + 1)) { // se giocatore a destra -> down + right
							QUORIDORmuoviGiocatore(3); // down
							QUORIDORmuoviGiocatore(2); // right
						}
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_down_right = 0;
	}
	

	
	if (((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && (LPC_GPIO1->FIOPIN & (1<<27)) != 0 && (LPC_GPIO1->FIOPIN & (1<<28)) != 0) || (PARTITAis_NPC_up() == 1 && PARTITAis_NPC_left() == 0 && PARTITAis_NPC_right() == 0)) { // joystick up
		J_up++;
		switch(J_up){
			case 1:
				// do something 
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						// modalità giocatore
						QUORIDORmuoviGiocatore(1); // direzione = 1 SU

					} else {
						// modalità muro
						QUORIDORmuoviMuro(1);
					}
				}  else if (QUORIDORisInit() == 1) {
					// selezione scelta menu SU
					QUORIDORupdateBtnMenu(BTN_UP);
				} 
				break;
			default:
				break;
		}
	} else {
			J_up = 0;
	}
	
	if (((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && (LPC_GPIO1->FIOPIN & (1<<29)) != 0 && (LPC_GPIO1->FIOPIN & (1<<26)) != 0) || (PARTITAis_NPC_right() == 1 && PARTITAis_NPC_up() == 0 && PARTITAis_NPC_down() == 0)) {	// joystick right
		J_right++;
		switch(J_right){
			case 1:
				// do something 
				if (QUORIDORisPartitaAttiva() == 1) {
					QUORIDORresetMosseNPC();
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						// modalità giocatore
						QUORIDORmuoviGiocatore(2); // direzione = 2 DESTRA
					} else {
						// modalità muro
						QUORIDORmuoviMuro(2);
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_right = 0;
	}
	
	if (((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && (LPC_GPIO1->FIOPIN & (1<<29)) != 0 && (LPC_GPIO1->FIOPIN & (1<<26)) != 0) || (PARTITAis_NPC_left() == 1 && PARTITAis_NPC_up() == 0 && PARTITAis_NPC_down() == 0)) { // joystick left
		J_left++;
		switch(J_left){
			case 1:
				// do something
				if (QUORIDORisPartitaAttiva() == 1) {
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						QUORIDORresetMosseNPC();
						// modalità giocatore
						QUORIDORmuoviGiocatore(4); // direzione = 4 SINISTRA
					} else {
						// modalità muro
						QUORIDORmuoviMuro(4);
					}
				}
				break;
			default:
				break;
		}
	} else {
			J_left = 0;
	}
	
	if (((LPC_GPIO1->FIOPIN & (1<<26)) == 0 && (LPC_GPIO1->FIOPIN & (1<<27)) != 0 && (LPC_GPIO1->FIOPIN & (1<<28)) != 0) || (PARTITAis_NPC_down() == 1 && PARTITAis_NPC_left() == 0 && PARTITAis_NPC_right() == 0)) { // joystick down
		J_down++;
		switch(J_down){
			case 1:
				// do something
				if (QUORIDORisPartitaAttiva() == 1) {
					QUORIDORresetMosseNPC();
					if (PARTITAgetModalita() == MOD_GIOCATORE) {
						// modalità giocatore
						QUORIDORmuoviGiocatore(3); // direzione = 3 GIU

					} else {
						// modalità muro
						QUORIDORmuoviMuro(3);
					}
				} else if (QUORIDORisInit() == 1) {
					// selezione scelta menu GIU
					QUORIDORupdateBtnMenu(BTN_DOWN);
				} 
				break;
			default:
				break;
		}
	} else {
			J_down = 0;
	}
	
	if (((LPC_GPIO1->FIOPIN & (1<<25)) == 0)){ // joystick pressed
		J_press++;
		switch(J_press){
			case 1:
				if (QUORIDORisInit() == 1) {
					// selezione scelta menu
					QUORIDORsceltaMenu();
				} else if (PARTITAgetModalita() == MOD_MURO) { // controllare la modalità, se init capire che cosa devo impostare e disegno e setto le cose giuste... se l'ultima lancio la partita  (start  modalità + giocaturno)e tolgo la modalita INIT
					QUORIDORconfermaMuro();
					if (!GIOCATOREisExternalBoard(PARTITAgetTurnoID()) && !GIOCATOREisNPC(PARTITAgetTurnoID())) {
						mossa = MOSSAcrea_return(PARTITAgetTurnoID(), 0, MUROisVertical(MUROgetLastMuro()), MUROgetVertice1(MUROgetLastMuro()));
						CANQsendMossa(mossa);
					}
					// swap
					QUORIDORswapTurno(1);
					QUORIDORgiocaTurno();
				} else if (PARTITAgetModalita() == MOD_GIOCATORE){
					// modalità giocatore
					if (!GIOCATOREisExternalBoard(PARTITAgetTurnoID()) && !GIOCATOREisNPC(PARTITAgetTurnoID())) {
						mossa = MOSSAcrea_return(PARTITAgetTurnoID(), 1, 0, GIOCATOREgetPosizione(PARTITAgetTurnoID()));
						CANQsendMossa(mossa);
					}
						fine = QUORIDORcheckWin();
						if (!fine) {
							QUORIDORswapTurno(1);
							QUORIDORgiocaTurno();
						} else {
							QUORIDORreset();
						}
				}
				break;
			default:
				break;
		}
	} else {
			J_press = 0;
	}
	
	/* ----------------------------------- button management ----------------------------------- */
	if(btn_down_counter[0]!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* KEY0 pressed */
			btn_down_counter[0]++;				
			switch(btn_down_counter[0]){
				case 2:				
						QUORIDORreset();
						QUORIDORinit();
						CANhandshakeClear();

						
						// disegno primo menu + gestire movimenti joystic e fare nulla con i bottoni
						QUORIDORdisegnaMenu();
						
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			btn_down_counter[0]=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts */
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}

	if(btn_down_counter[1]!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			btn_down_counter[1]++;				
			switch(btn_down_counter[1]){
				case 2:				
					// do something with button 1
					if (QUORIDORisPartitaAttiva() == 1 && GIOCATOREgetNumeroMuri(PARTITAgetTurnoID()) < 8 && PARTITAgetMossaPending() != 1) {
						// partita in gioco
						// cambio modalità 
						PARTITAsetMossaPending(0); // no mossa pending
						if (PARTITAgetModalita() == MOD_GIOCATORE) {
							PARTITAsetModalita(MOD_MURO); // = 0 modalità muro
							QUORIDORrimuoviMosseGiocatore();
							QUORIDORaggiungiMuro();
						} else {
							PARTITAsetModalita(MOD_GIOCATORE); // = 0 modalità muro
							QUORIDORrimuoviMuro();
							QUORIDORgiocaTurno();
						}
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			btn_down_counter[1]=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts */
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	
	if(btn_down_counter[2]!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			btn_down_counter[2]++;				
			switch(btn_down_counter[2]){
				case 2:				
					if (QUORIDORisPartitaAttiva() == 1 && PARTITAgetModalita() == MOD_MURO) {
						// rotazione muro
						QUORIDORruotaMuro();
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			btn_down_counter[2]=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts */
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}
