#ifndef __BSP_H
#define __BSP_H
#include "stm32f4xx.h"
#include "watchdog.h"
#include "NRISTF4_Define.h"
#include "NRIST_calculate.h"
#include "delay.h"
#include "bsp_rcc.h"
#include "string.h"
#include "fram.h"
#include "NRISTF4_flash.h"
//#include "w25qxx.h"
#include "NRISTF4_SPIflash.h"
//#include "NRIST_flash.h"
/*自动代码头文件*/
#include "EngineControl_Out.h"
#include "CYS_110WP_3_Control.h"    /* Model's header file */
#include "rtwtypes.h"
#include "nristf4_sdio.h"


#ifdef __cplusplus
 extern "C" {
#endif
#define ADC1_DR_Address		((uint32_t)ADC1+0x4c)

void BSP_Init(void);
void SysTick_init(void);
void InitWatchdog(void);

void LED_GPIO_Init(void);
void OUT_GPIO_Init(void);
void IN_GPIO_Init(void);

void Flash_GPIO_Configuration(void);
void SPI_InitConfig(SPI_TypeDef* SPIx, uint16_t cpol, uint16_t cpha, uint16_t baudRateprescaler);
uint8_t SPI_SRByte(SPI_TypeDef* SPIx, uint8_t byte);
void SPI_FLASH_SGWrite(uint8_t mode);
void InitUsart1(void);
void InitUsart2(void);
void InitUart4(void);	 

void InitADC(void);
void ADC_GPIO_Init(void);
void ADC1_DMA2S0_Configuration(uint8_t ADC_SampleTime);
void USART1_GPIO_Init(void);
void USART2_GPIO_Init(void);
void UART4_GPIO_Init(void);
void USART_Configuration(USART_TypeDef* USARTx, uint32_t BaudRate_Input, uint8_t WordLength_Input, uint8_t StopBits_Input, uint8_t Parity_Input);
void NVIC_IT_Configuration(uint8_t IRQChannelx, uint8_t Priorityx, uint8_t SubPriorityx);
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr);
void SampleData(void);
void SampleSwitch(void);
void TIM_InitConfig(TIM_TypeDef* TIMx, uint32_t period, uint16_t prescaler);
void InitTIM7(void);
void InitTIM2(void);
void CAN_InitGPIO(void);
void InitIC1(void);
void InitIC2(void);
void InitCAN(void);
void CAN_InitConfig(CAN_TypeDef* CANx, uint16_t baudrateprescaler);
void CAN_InitFilterStdId(CAN_TypeDef* CANx, uint32_t filterid);
void InitPWM(void);
void PWM1_GPIO_Init(void);
void TIM_InitOC(TIM_TypeDef* TIMx, uint16_t mode, uint16_t pulse, uint16_t polarity, uint8_t channel);
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr);
void TIM_OCSetDutyCycle(TIM_TypeDef* TIMx, uint8_t channel, uint16_t pulse);
void SampleSpeed(void);




#ifdef __cplusplus
}
#endif
#endif
