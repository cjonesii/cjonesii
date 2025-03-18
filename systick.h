#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>

void systick_init( void );
void systick_deinit( void );
void systick_reset_count( void );
uint32_t systick_get_count( void );

#endif // __SYSTICK_H__