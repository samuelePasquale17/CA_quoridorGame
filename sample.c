/**
	@author		SAMUELE PASQUALE
	@date			1/14/2024
	@version	v2
*/


/* include */
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "GLCD/GLCD.h"
#include "CAN/CAN.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


/* main function */
int main (void) {
	SystemInit();	// inizializzazione sistema (PLL)
	
	
	/* -------------------------------- uso BUTTON ---------------------------------- */
	BUTTON_init(); // utilizzo in IRQ_RIT.c
	/* ------------------------------------------------------------------------------ */
	
	/* ------------------------------- uso JOYSTICK --------------------------------- */
	joystick_init(); // utilizzo in IRQ_RIT.c
	/* ------------------------------------------------------------------------------ */
	
	/* ---------------------------------- uso RIT ----------------------------------- */
	init_RIT(RIT_INTERVAL); // RIT_INTERVAL definito in RIT.h
	enable_RIT();
	/* ------------------------------------------------------------------------------ */

	/* --------------------------------- uso TIMER ---------------------------------- */
	/* uso TIMER 1 */
	init_timer(TIMER1, TIMER1_INTERVAL);	// timer schermo (1s)
	init_timer(TIMER0, TIMER0_INTERVAL);	// timer schermo (3s) // CAN handshake
	/* ------------------------------------------------------------------------------ */

	/* ---------------------------------- uso LCD ----------------------------------- */
	LCD_Initialization();
	/* ------------------------------------------------------------------------------ */
	
	/* ---------------------------------- uso CAN ----------------------------------- */
	CAN_Init();
	/* ------------------------------------------------------------------------------ */
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }
}
