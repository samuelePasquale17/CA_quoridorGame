#ifndef __TIMER_H
#define __TIMER_H



// timer 0
#define TIMER0										0
#define TIMER0_FREQ								25*1000000	// 25 MHz
#define TIMER0_PERIOD_SECONDS			3						// 3 seconds

// timer 1
#define TIMER1										1
#define TIMER1_FREQ								25*1000000	// 25 MHz
#define TIMER1_PERIOD_SECONDS			1						// 1 seconds

// timer 2
#define TIMER2										2
#define TIMER2_FREQ								25*1000000	// 25 MHz
#define TIMER2_PERIOD_SECONDS			3						// 3 seconds

// timer 3
#define TIMER3										3
#define TIMER3_FREQ								25*1000000	// 25 MHz
#define TIMER3_PERIOD_SECONDS			13					// 13 seconds

// intervalli timer
#define TIMER0_INTERVAL						TIMER0_FREQ*TIMER0_PERIOD_SECONDS		// 25MHz * n_seconds
#define TIMER1_INTERVAL						TIMER1_FREQ*TIMER1_PERIOD_SECONDS		// 25MHz * n_seconds
#define TIMER2_INTERVAL						TIMER2_FREQ*TIMER2_PERIOD_SECONDS		// 25MHz * n_seconds
#define TIMER3_INTERVAL						TIMER3_FREQ*TIMER3_PERIOD_SECONDS		// 25MHz * n_seconds

/* init_timer.c */
extern uint32_t init_timer( uint8_t timer_num, uint32_t timerInterval );
extern void enable_timer( uint8_t timer_num );
extern void disable_timer( uint8_t timer_num );
extern void reset_timer( uint8_t timer_num );
/* IRQ_timer.c */
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);

#endif /* end __TIMER_H */
