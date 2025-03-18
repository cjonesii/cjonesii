#include <iwdg.h>
#include <ch32v003fun.h>

void iwdg_setup( uint16_t reload_val, uint8_t prescaler )
{
	IWDG->CTLR = 0x5555;
	IWDG->PSCR = prescaler;

	IWDG->CTLR = 0x5555;
	IWDG->RLDR = reload_val & 0xfff;

	IWDG->CTLR = 0xCCCC;
}

void iwdg_feed( void )
{
	IWDG->CTLR = 0xAAAA;
}
