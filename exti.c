#include <ch32v003fun.h>
#include <config.h>
#include <exti.h>

void exti_init( void )
{
	// Ugh this is tricky.
	// This is how we set (INTSYSCR) to enable hardware interrupt nesting
	// and hardware stack. BUT this means we can only stack intterrupts 2 deep.
	//
	// This feature is called "HPE"
	//
	// Note: If you don't do this, you will need to set your functions to be
	// __attribute__((interrupt)) instead of  __attribute__((naked))  with an
	// mret.
	//
	// PLEASE BE CAREFUL WHEN DOING THIS THOUGH.  There are a number of things
	// you should know with HPE.  The issue is that HPE doesn't preserve s0,
	// and s1. You should review the following material before using HPE.
	//   https://github.com/cnlohr/ch32v003fun/issues/90
	//   https://www.reddit.com/r/RISCV/comments/126262j/notes_on_wch_fast_interrupts/
	//   https://www.eevblog.com/forum/microcontrollers/bizarre-problem-on-ch32v003-with-systick-isr-corrupting-uart-tx-data
	asm volatile(
#if __GNUC__ > 10
		".option arch, +zicsr\n"
#endif
 		"addi t1, x0, 3\n"
		"csrrw x0, 0x804, t1\n"
		 : : :  "t1" );

	// Configure the IO as an interrupt.
	AFIO->EXTICR = AFIO_EXTICR_EXTI4_PC; // | AFIO_EXTICR_EXTI2_PA; // Line 4, Line 2 // Add Line2 if button in PA2 is to be configured
	EXTI->INTENR = EXTI_INTENR_MR4; // | EXTI_INTENR_MR2;           // Enable interrupt Line 4, Line 2
	EXTI->RTENR = EXTI_RTENR_TR4;                               // Rising edge trigger
    EXTI->FTENR = EXTI_FTENR_TR4; // | EXTI_FTENR_TR2;              // Falling edge trigger

	// enable interrupt
	NVIC_EnableIRQ( EXTI7_0_IRQn );
}
