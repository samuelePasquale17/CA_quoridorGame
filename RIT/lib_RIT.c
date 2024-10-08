#include "lpc17xx.h"
#include "RIT.h"


void enable_RIT( void )
{
  LPC_RIT->RICTRL |= (1<<3);	
  return;
}


void disable_RIT( void )
{
	LPC_RIT->RICTRL &= ~(1<<3);	
  return;
}


void reset_RIT( void )
{
  LPC_RIT->RICOUNTER = 0;          // Set count value to 0
  return;
}

uint32_t init_RIT ( uint32_t RITInterval )
{
  LPC_SC->PCLKSEL1  &= ~(3<<26);
	
	/*
		la frequenza del RIT pu� essere cambiata usando dei Clock Divisor (CLK/2, CLK/4, CLK/8).
		Per i valori vedi tabella 42 (PCLKSEL1)
	*/
  LPC_SC->PCLKSEL1  |=  (1<<26);   // RIT Clock = CCLK (100 MHz)
	LPC_SC->PCONP     |=  (1<<16);   // Enable power for RIT
	
	LPC_RIT->RICOMPVAL = RITInterval;      // Set match value		
	LPC_RIT->RICTRL    = (1<<1) |    // Enable clear on match	
											 (1<<2) ;		 // Enable timer for debug	
	LPC_RIT->RICOUNTER = 0;          // Set count value to 0
	
	NVIC_EnableIRQ(RIT_IRQn);
  return (0);
}
