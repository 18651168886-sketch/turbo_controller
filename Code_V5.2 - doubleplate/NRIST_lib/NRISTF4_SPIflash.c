#include "NRISTF4_SPIflash.h"
SPIFLASHSTRUCT SPIFlash;
RESETINFOSTRUCT ResetInfo;     //复位信息存储

u8 ResetInfoCheck(u8* pBuffer , u16 NumByteToCheck)
{
    if(pBuffer[0] != ResetInfoHead0 || pBuffer[1] != ResetInfoHead1)
    {
        return 0;
    }
    if(pBuffer[NumByteToCheck - 2] != SumArray(pBuffer, 0, NumByteToCheck - 2)
        || pBuffer[NumByteToCheck - 1] != XORArray(pBuffer, 0, NumByteToCheck - 2))
    {
        return 0;
    }
    return 1;
}
u8 ResetInfoSaveUncheck(RESETINFOSTRUCT sResetInfo , u32 RealTimeDataAddr , ENGINESTRUCT sEngine)
{
    if(sResetInfo.Status != t_Ready)
    {
        return 0;
    }
    sResetInfo.buf[0] = ComHead0;
    sResetInfo.buf[1] = ComHead1;
    sResetInfo.buf[2] = RealTimeDataAddr >> 24;
    sResetInfo.buf[3] = RealTimeDataAddr >> 16;
    sResetInfo.buf[4] = RealTimeDataAddr >> 8;
    sResetInfo.buf[5] = RealTimeDataAddr;
    sResetInfo.buf[6] = (u32)sEngine.Accelerator >> 8;
    sResetInfo.buf[7] = (u32)sEngine.Accelerator >> 8;
    sResetInfo.buf[8] = sEngine.Status;
    sResetInfo.buf[9] = sEngine.Instr;
    sResetInfo.buf[10] = sEngine.RotaSpeed_Load >> 16;
    sResetInfo.buf[11] = sEngine.RotaSpeed_Load >> 8;
    sResetInfo.buf[12] = sEngine.RotaSpeed_Load;
    sResetInfo.buf[13] = sEngine.RotaSpeed_Current >> 16;
    sResetInfo.buf[14] = sEngine.RotaSpeed_Current >> 8;
    sResetInfo.buf[15] = sEngine.RotaSpeed_Current;
    sResetInfo.buf[16] = sResetInfo.saveCnt;
    sResetInfo.buf[17] = SumArray(sResetInfo.buf, 0, 17);
    sResetInfo.buf[18] = XORArray(sResetInfo.buf, 0, 17);

    FM25_Write((u16)sResetInfo.saveAddrFlag * (u16)ResetInfoAddr1 , sResetInfo.buf , ResetInfoLen);
    return 1;
}

u8 CheckSPISectorisAble2Write(u32 SectorIndex)
{
    u32 FlashAddrStar = SectorIndex << 12;
 	u16 i;
    u16 notAble2WriteNbr = 0;
	W25QXX_CS=0;                            //使能器件
    SPI2_ReadWriteByte(W25X_ReadData);         //发送读取命令
    SPI2_ReadWriteByte((u8)((FlashAddrStar)>>16));  //发送24bit地址
    SPI2_ReadWriteByte((u8)((FlashAddrStar)>>8));
    SPI2_ReadWriteByte((u8)FlashAddrStar);
    for(i=0;i<SectorSize;i++)
	{
        if(0xFF != SPI2_ReadWriteByte(0XFF))   //循环读数
        {
            notAble2WriteNbr++;
        }
    }
	W25QXX_CS=1;
    return notAble2WriteNbr;
}

u32 SearchAddr_Able2Write(u32 StartAddr , u32 SearchCnt)
{
    u32 FlashCurrentAddr = StartAddr;
 	u32 BlankNbr = 0;
    u32 BlankAddr = 0;
    if(FlashCurrentAddr >= W25Q64MaxAddr)
    {
        return W25Q64MaxAddr;
    }
	W25QXX_CS=0;                            //使能器件
    SPI2_ReadWriteByte(W25X_ReadData);         //发送读取命令
    SPI2_ReadWriteByte((u8)((FlashCurrentAddr)>>16));  //发送24bit地址
    SPI2_ReadWriteByte((u8)((FlashCurrentAddr)>>8));
    SPI2_ReadWriteByte((u8)FlashCurrentAddr);
    while(FlashCurrentAddr <= W25Q64MaxAddr)
	{
        if(0xFF == SPI2_ReadWriteByte(0XFF))   //循环读数
        {
            BlankNbr++;
            if(1 == BlankNbr)
            {
                BlankAddr = FlashCurrentAddr;
            }
            if(BlankNbr >= SearchCnt)
            {
                W25QXX_CS=1;
                return BlankAddr;
            }
        }
        else
        {
            BlankNbr = 0;
        }
        FlashCurrentAddr++;
    }

	W25QXX_CS=1;
    if(BlankNbr > 0)
    {
        return BlankAddr;
    }
    return W25Q64MaxAddr;
}















/*************************这就是我的底线****************************************************************/

