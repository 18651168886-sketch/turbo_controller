#ifndef _BSP_RCC_H_
#define _BSP_RCC_H_
#include "stm32f4xx.h"
void HSE_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q);
void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q);
#endif
