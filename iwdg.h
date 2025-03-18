#ifndef __IWDG_H__
#define __IWDG_H__

#include <stdio.h>

void iwdg_setup( uint16_t reload_val, uint8_t prescaler );
void iwdg_feed( void );

#endif // __IWDG_H__