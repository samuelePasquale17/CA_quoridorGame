/**
	@author		SAMUELE PASQUALE
	@date			1/14/2024
	@version	v2
*/

#include "button.h"
#include "lpc17xx.h"

extern int btn_down_counter[3];   // vettore dichiarato in IRQ_RIT.c

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	btn_down_counter[0] = 1;				// gestione bouncing tramite RIT	
	NVIC_DisableIRQ(EINT0_IRQn);
	LPC_PINCON->PINSEL4  &= ~(1 << 20);
	LPC_SC->EXTINT &= (1 << 0);    
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	btn_down_counter[1] = 1;				// gestione bouncing tramite RIT
	NVIC_DisableIRQ(EINT1_IRQn);
	LPC_PINCON->PINSEL4  &= ~(1 << 22);
	LPC_SC->EXTINT &= (1 << 1);     
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	btn_down_counter[2] = 1;				// gestione bouncing tramite RIT
	NVIC_DisableIRQ(EINT2_IRQn);
	LPC_PINCON->PINSEL4  &= ~(1 << 24);
	LPC_SC->EXTINT &= (1 << 2);   
}


