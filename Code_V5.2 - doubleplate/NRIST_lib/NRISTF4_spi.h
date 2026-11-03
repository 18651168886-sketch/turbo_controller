#ifndef __NRISTF4_SPI_H
#define __NRISTF4_SPI_H
#include "sys.h"
#include "NRISTF4_Define.h"

void SPI2_Init(void);			 //初始化SPI2口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI2速度
u8 SPI2_ReadWriteByte(u8 TxData);//SPI2总线读写一个字节

#endif

