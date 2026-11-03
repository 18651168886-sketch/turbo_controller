#ifndef __NRISTF4_SPIFLASH_H
#define __NRISTF4_SPIFLASH_H

#include "stm32f4xx.h"
#include "w25qxx.h"
#include "NRIST_calculate.h"
#include "fram.h"

#define SectorSize      (0x1000)    //4Kbytes

#define ResetInfoAddr0       ((u32)0x0000)   //第1 Sector首地址
#define ResetInfoAddr1       ((u32)0x0100)   //第2 Sector首地址
#define ResetInfoHead0   (0xAA)
#define ResetInfoHead1   (0x55)
#define ResetInfoLen     (19)        //复位信息长度
#define BlankSpaceMin    (100)          //片外Flash实时数据存储区的最小空白空间（可写空间）
#define DataInfoLen      (19)           //有效实时数据长度 21 - 2 = 19

typedef enum
{
    t_Ready = 0,
    t_Busy,
    t_Bad,
    t_Full,
} SPIFlashStatus;

typedef struct
{
    u32 CurrentWriteAddr;
    SPIFlashStatus Status;
}SPIFLASHSTRUCT;
extern SPIFLASHSTRUCT SPIFlash;     //实时数据存储

typedef struct
{
    u8 buf[40];
    u8 saveAddrFlag;    //复位信息存储位置标志 0:存储在第0sector;1:存储在第1sector;
    u8 saveCnt;         //用于计算存储次数
    u8 WriteFlag;         //复位信息写入标志
    SPIFlashStatus Status;
}RESETINFOSTRUCT;
extern RESETINFOSTRUCT ResetInfo;     //复位信息存储


u8 ResetInfoCheck(u8* pBuffer , u16 NumByteToCheck);
u8 CheckSPISectorisAble2Write(u32 SectorIndex);
u8 ResetInfoSaveUncheck(RESETINFOSTRUCT sResetInfo , u32 RealTimeDataAddr , ENGINESTRUCT sEngine);
u32 SearchAddr_Able2Write(u32 StartAddr , u32 Nbr);

#endif/*__NRISTF4_SPIFLASH_H*/
/*************************这就是我的底线****************************************************************/



