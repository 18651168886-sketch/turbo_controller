#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#include "stm32f4xx.h"

void IWDG_Configuration(uint8_t prer, uint16_t rlr);
void IWDG_Feed(void);
void WWDG_Configuration(uint32_t fprer, uint8_t Counter);

#endif

/*WATCHDOG_H*/







