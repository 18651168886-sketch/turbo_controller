#ifndef _FRAM_H_
#define _FRAM_H_
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stdio.h"

#define Dummy_Byte                0xFF
#define FM25xxMaxAddr       (8 * 1024)  //×î´óµØÖ·

/*??????*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

#define SPI_FRAM_CS_LOW()      {GPIOB->BSRRH = GPIO_Pin_12;}
#define SPI_FRAM_CS_HIGH()     {GPIOB->BSRRL = GPIO_Pin_12;}
u8 SPI_FRAM_SendByte(uint8_t byte);
u8 SPI_FRAM_ReadByte(void);
void FRAM_Config(void);
void FRAM_WREN(void);
void FRAM_WRDI(void);
void FRAM_Write(u16 Addr,u8 Data);
void FM25_Write(u16 Addr,u8* Data , u16 nbr2Write);
u8 FRAM_Read(u16 Addr);
void FM25_Read(u8* Data , u16 Addr , u16 nbr2Read);

/**************************************/

void FM_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);

#endif
