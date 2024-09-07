/**
	@author		SAMUELE PASQUALE
	@date			1/13/2024
	@version	v5
*/


#include "lpc17xx.h"
#include "timer.h"
#include "../Quoridor/Quoridor.h"
#include "../CAN/CAN.h"
#include "../Quoridor/CANquoridor.h"
#include "../GLCD/GLCD.h"


extern int handshake;

void TIMER0_IRQHandler (void)
{
	if (handshake == 1) {
		GUI_Text(50, 50, (uint8_t*) "Handshake successo", Red, Black); // notificare QUORIDOR.c comunicazione OK
	}else  {

		GUI_Text(50, 50, (uint8_t*) "Handshake fallito", Red, Black);  // notificare QUORIDOR.c comunicazione OK
	}
	disable_timer(TIMER0);
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER1_IRQHandler (void)
{
	QUORIDORdecrementTimer();	/* decremento timer secondi sullo schermo LCD */
	if (QUORIDORgetTimer() == 0) {
		/* swap */
		QUORIDORswapTurno(0);
		QUORIDORgiocaTurno();
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
