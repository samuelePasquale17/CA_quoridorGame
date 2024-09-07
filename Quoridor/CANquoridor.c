#include "CANquoridor.h"
#include "../GLCD/GLCD.h"
#include "../CAN/CAN.h"


int handshake = 0;
int handshakeActive = 0;


void CANQhandshake() {
	
	handshakeActive = 1;
	/* Invio mossa handwhake */
	CAN_TxMsg.data[0] = 0xFF;
	CAN_TxMsg.data[1] = 0x00; 
	CAN_TxMsg.data[2] = 0x00;
	CAN_TxMsg.data[3] = 0x00;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);   // scriviamo il frame sul controller 1
	
	// WAIT 3 SECONDS
	// start timer0
	
	// controllo se handshake == 0 fail, altrimenti good, lo faccio nell
}


int CANhandshakeIsConfirmed() {
	return handshake;
}

Mossa CANQreadMossa() {
	int playerID, playerMove, vertical, y, x, campo, pos;
	
	CAN_rdMsg (1, &CAN_RxMsg);	                		/* Read the message */
  LPC_CAN1->CMR = (1 << 2);                    		/* Release receive buffer */
		
		
	playerID = CAN_RxMsg.data[0]; // leggo il pacchetto di 8 char
	campo = CAN_RxMsg.data[1]; // leggo il pacchetto di 8 char
	y = CAN_RxMsg.data[2]; // leggo il pacchetto di 8 char
	x = CAN_RxMsg.data[3]; // leggo il pacchetto di 8 char
	
	if (campo == 0x00) {
		playerMove = 0;
		vertical = 0;
	} else if (campo == 0x10) {
		playerMove = 1;
		vertical = 0;
	} else if (campo == 0x01) {
		playerMove = 0;
		vertical = 1;
	} else {
		// 0x11
	}
	pos = MOSSA_da_XY_2_posizione(x, y, playerMove == 0);
	return MOSSAcrea_return(playerID, playerMove == 0, vertical == 0, pos);
}


void CANQsendMossa(Mossa mossa) {
	//uint32_t test = mossa.mossa;
	int x, y, pos;
	int campo = 0x00;
	
	pos = MOSSAgetPosizione(mossa, MOSSAisPlayerMode(mossa));
	
	if (MOSSAisPlayerMode(mossa)) {
		campo = 0x00;
	} else {
		if (MOSSAisVerticale(mossa)) {
			campo = 0x10;
		} else {
			campo += 0x11;
		}
	}
	
	
	MOSSA_da_posizione_2_XY(pos, MOSSAisPlayerMode(mossa), &x, &y);
	
	CAN_TxMsg.data[0] = (uint8_t) MOSSAgetPlayerID(mossa); // ID
	CAN_TxMsg.data[1] = (uint8_t) campo; 
	CAN_TxMsg.data[2] = (uint8_t) y;
	CAN_TxMsg.data[3] = (uint8_t) x;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);   // scriviamo il frame sul controller 1
}


void CANhandshakeClear() {
	handshake = 0;
}
