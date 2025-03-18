#include <ch32v003fun.h>
#include <systick.h>
#include <stdio.h>

volatile uint32_t systick_cnt;

/*
 * Start up the SysTick IRQ
 */
void systick_init( void )
{
	/* disable default SysTick behavior */
	SysTick->CTLR = 0;

	/* enable the SysTick IRQ */
	NVIC_EnableIRQ(SysTicK_IRQn);

	/* Set the tick interval to 1ms for normal op */
	SysTick->CMP = (FUNCONF_SYSTEM_CORE_CLOCK/1000)-1;

	/* Start at zero */
	SysTick->CNT = 0U;
	systick_cnt = 0U;

	/* Enable SysTick counter, IRQ, HCLK/1 */
	SysTick->CTLR = SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE |
					SYSTICK_CTLR_STCLK;
}

void systick_deinit( void )
{
    systick_cnt = 0U;
	/* disable default SysTick behavior */
	SysTick->CTLR = 0;

	/* enable the SysTick IRQ */
	NVIC_DisableIRQ(SysTicK_IRQn);
}

void systick_reset_count( void )
{
    systick_cnt = 0U;
}

uint32_t systick_get_count( void )
{
    return systick_cnt;
}

/*
 * SysTick ISR just counts ticks
 * note - the __attribute__((interrupt)) syntax is crucial!
 */
void SysTick_Handler(void) __attribute__((interrupt));
void SysTick_Handler(void)
{
	// move the compare further ahead in time.
	// as a warning, if more than this length of time
	// passes before triggering, you may miss your
	// interrupt.
	SysTick->CMP += (FUNCONF_SYSTEM_CORE_CLOCK/1000);

	/* clear IRQ */
	SysTick->SR = 0U;

	/* update counter */
	systick_cnt++;
}
