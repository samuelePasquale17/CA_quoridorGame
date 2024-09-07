#ifndef __RIT_H
#define __RIT_H

#define RIT_PERIOD_MILLI_SECONDS 						50*0.001 															// 50 ms	
#define RIT_FREQ														100*1000000														// 100 MHz 								
#define RIT_INTERVAL 												RIT_PERIOD_MILLI_SECONDS * RIT_FREQ 	// 50 [ms] *100 [MHZ]


/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

#endif /* end __RIT_H */
