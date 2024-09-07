#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.21)
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_PINCON->PINSEL3 &= ~(3<<18);	//PIN mode GPIO (00b value per P1.25)
	LPC_GPIO1->FIODIR   &= ~(1<<25);	//P1.25 Input (joysticks on PORT1 defined as Input)
  LPC_PINCON->PINSEL3 &= ~(3<<20);	//PIN mode GPIO (00b value per P1.24)
	LPC_GPIO1->FIODIR   &= ~(1<<26);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_PINCON->PINSEL3 &= ~(3<<22);	//PIN mode GPIO (00b value per P1.23)
	LPC_GPIO1->FIODIR   &= ~(1<<27);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_PINCON->PINSEL3 &= ~(3<<24);	//PIN mode GPIO (00b value per P1.22)
	LPC_GPIO1->FIODIR   &= ~(1<<28);	//P1.25 Input (joysticks on PORT1 defined as Input)
}


/**
	@brief			Funzione che disabilita l'uso del Joystick
	@parameter	direction:			Direzione del Joystick da disabilitare {SU=1, DESTRA=2, GIU=3, SINISTRA=4, PUSH=5}
*/
void joystick_disable(int direction) {
	switch (direction) {
		case 1: /* Up */
			LPC_GPIO1->FIOMASK |= (1 << 29);
		break;
		case 2: /* Right */
			LPC_GPIO1->FIOMASK |= (1 << 28);
		break;
		case 3: /* Down */
			LPC_GPIO1->FIOMASK |= (1 << 26);
		break;
		case 4: /* Left */
			LPC_GPIO1->FIOMASK |= (1 << 27);		
		break;
		case 5: /* Push */
			LPC_GPIO1->FIOMASK |= (1 << 25);			
		break;
		default:
				/* -- default -- */
		break;
	}
}


/**
	@brief			Funzione che abilita l'uso del Joystick
	@parameter	direction:			Direzione del Joystick da disabilitare {SU=1, DESTRA=2, GIU=3, SINISTRA=4, PUSH=5}
*/
void joystick_enable(int direction) {
	switch (direction) {
		case 1: /* Up */
			LPC_GPIO1->FIOMASK &= ~(1<<29);
		break;
		case 2: /* Right */
			LPC_GPIO1->FIOMASK &= ~(1<<28);
		break;
		case 3: /* Down */
			LPC_GPIO1->FIOMASK &= ~(1<<26);
		break;
		case 4: /* Left */
			LPC_GPIO1->FIOMASK &= ~(1<<27);
		break;
		case 5: /* Push */
			LPC_GPIO1->FIOMASK &= ~(1<<25);	
		break;
		default:
				/* -- default -- */
		break;
	}
}
