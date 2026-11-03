#include "NRIST_Comm.h"
#include "NRISTF4_Control.h"
#include "flash_helper.h"
#include "buffer.h"
#include "crc.h"
u16 B_Speed = 0;
u16 B_Speed_temp = 0;
u32 B_Speed_sum = 0;
double Huansuan_Speed = 0;
float zongWen = 0;
u8 zhenjishu = 0;

void sendData()
{
	if(pSendData_Out.senddata1 == 0)
	{
		return;
	}
	memcpy(&ECU_Uart4.TX_BUF[3] , &pSendData_Out.senddata3 , pSendData_Out.senddata2);
	
    ECU_Uart4.TX_BUF[0]  = ComHead0;
    ECU_Uart4.TX_BUF[1]  = ComHead1;
    ECU_Uart4.TX_BUF[2]  = 0x01;
//	if((u32)sADC.T0 >255)
//	{
//		ECU_Uart4.TX_BUF[4]  = 255;
//	}
//	else
//	{
//		ECU_Uart4.TX_BUF[4]  = (u32)(sADC.T0+0.5);
//	}
  	
//	  ECU_Uart4.TX_BUF[5]  = (u32)sADC.T0&0X00FF;
		
	//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 10]  = (u32)(sADC.T0)>>8;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 11]  = (u32)sADC.T0&0X00FF;//4	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 1]  = pSendData_Out.senddata26;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 2]  = pSendData_Out.senddata27;//4	
		B_Speed_temp = (ECU_Usart2.RX_BUF[5]<<8) + ECU_Usart2.RX_BUF[6];
		B_Speed = B_Speed*0.875 + B_Speed_temp*0.125;
	
		//ECU_Uart4.TX_BUF[19]  = (u32)(sADC.T0)>>8;//3
	  ECU_Uart4.TX_BUF[26]  = (B_Speed>>8);//3
		ECU_Uart4.TX_BUF[27]  = B_Speed&0X00FF;//4	
	
//	zongWen =  sADC.T0-80.0f;//3
//	Huansuan_Speed = (pSendData_Out.senddata15*256 + pSendData_Out.senddata16)*2*sqrt(288.15f/(273.15f+zongWen));
//	ECU_Uart4.TX_BUF[12]  = ((u16)(Huansuan_Speed/2)>>8);//3
//	ECU_Uart4.TX_BUF[13]  = (u16)(Huansuan_Speed/2)&0X00FF;//4	
	
	ECU_Uart4.TX_BUF[22]  = zhenjishu++ ;
	
    ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 3] = SumArray(ECU_Uart4.TX_BUF , 0 , 28);//5 4
    ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 4] = XORArray(ECU_Uart4.TX_BUF , 0 , 28);//6 4
	
	
	
	
//	ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 5]  = sADC.POil;
	
		
//		u8 j;
//		for(j=0,j<8,j++)
//		{
//			B_Speed_sum += B_Speed;
//		}
//		B_Speed_sum>>3;
	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 6]  = (B_Speed>>8);//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 7]  = B_Speed&0X00FF;//4	
//	
//	
////		B_Speed = B_Speed_temp;
//	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 8]  = RotaSpeed2.PhyRealTime>>8;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 9]  = RotaSpeed2.PhyRealTime&0X00FF;//4	
//	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 10]  = (u32)(sADC.T0)>>8;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 11]  = (u32)sADC.T0&0X00FF;//4	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 12]  = (u32)sADC.beiyong2>>8;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 13]  = (u32)sADC.beiyong2&0X00FF;//4	
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 14]  = (u32)sADC.beiyong1>>8;//3
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 15]  = (u32)sADC.beiyong1&0X00FF;//4	

//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 16]  = ECU_Usart2.RX_BUF[7];//目标转速
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 17]  = ECU_Usart2.RX_BUF[8];
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 18]  = ECU_Usart2.RX_BUF[9];//油泵电压
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 19]  = ECU_Usart2.RX_BUF[10];//油泵电流
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 20]  = ECU_Usart2.RX_BUF[11];
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 21]  = ECU_Usart2.RX_BUF[12];//输入电流
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 22]  = ECU_Usart2.RX_BUF[13];
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 23]  = ECU_Usart2.RX_BUF[14];//占空比
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 24]  = ECU_Usart2.RX_BUF[15];
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 25]  = ECU_Usart2.RX_BUF[16];//温度
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 26]  = ECU_Usart2.RX_BUF[17];
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 27]  = ECU_Usart2.RX_BUF[18];//故障
//		ECU_Uart4.TX_BUF[pSendData_Out.senddata2 + 28]  = ECU_Usart2.RX_BUF[19];//jj;//帧计数

		DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_TCIF4);
    USART_DMACmd(UART4 , USART_DMAReq_Tx , ENABLE);  //使能串口4的DMA发逿
    MYDMA_Enable(DMA1_Stream4 , 30);     //开始一次DMA传输
}

void sendbumpData()
{
    ECU_Usart2.TX_BUF[0]  = 0XAA;
    ECU_Usart2.TX_BUF[1]  = 0X55;
    ECU_Usart2.TX_BUF[2]  = 0x03;
		ECU_Usart2.TX_BUF[3]  = 0x00;
		ECU_Usart2.TX_BUF[4]  = 0x02;
	
		ECU_Usart2.TX_BUF[5]  = pSendData_Out.senddata17; //0X1E;//3
		ECU_Usart2.TX_BUF[6]  = pSendData_Out.senddata18; //0X00;//3
	
		unsigned short crc16temp=crc16(&ECU_Usart2.TX_BUF[5], 2);
    ECU_Usart2.TX_BUF[7] = (crc16temp>>8);//5 4
    ECU_Usart2.TX_BUF[8] = (crc16temp&0X00FF);//6 4

    DMA_ClearFlag(DMA1_Stream6 , DMA_FLAG_TCIF6);
    USART_DMACmd(USART2 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发逿
    MYDMA_Enable(DMA1_Stream6 , 9);     //开始一次DMA传输
}

void sendstartmotorData()
{
    ECU_Usart1.TX_BUF[0]  = 0XAA;
    ECU_Usart1.TX_BUF[1]  = 0X55;
    ECU_Usart1.TX_BUF[2]  = 0x03;
		ECU_Usart1.TX_BUF[3]  = 0x00;
		ECU_Usart1.TX_BUF[4]  = 0x02;
	
		ECU_Usart1.TX_BUF[5]  = 0x00; //0X1E;//3
		ECU_Usart1.TX_BUF[6]  = pSendData_Out.senddata19; //0X00;//3
	
		unsigned short crc16temp=crc16(&ECU_Usart1.TX_BUF[5], 2);
    ECU_Usart1.TX_BUF[7] = (crc16temp>>8);//5 4
    ECU_Usart1.TX_BUF[8] = (crc16temp&0X00FF);//6 4

    DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
    USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发逿
    MYDMA_Enable(DMA2_Stream7 , 9);     //开始一次DMA传输
}

void sendackData(void)
{
	memcpy(ECU_Uart4.TX_BUF , AckInfo , AckInfoLen);
	DMA_ClearFlag(DMA1_Stream2 , DMA_FLAG_TCIF2);
	USART_DMACmd(UART4 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发送
	MYDMA_Enable(DMA1_Stream2 , AckInfoLen);     //开始一次DMA传输
}

u8 W25Q64SaveData(SaveData_Out * DataBuf , u32 WriteAddr , u8 size)   //数据保存到SPI Flash
{
    u8 DataTemp[50] = {0};
    if(WriteAddr >= (W25Q64MaxAddr - size))
    {
        SPIFlash.Status = t_Full;
        return 0;
    }
    memcpy(DataTemp , DataBuf , size);
    DataTemp[size] = '\n';
    W25QXX_Write_NoCheck(DataTemp, WriteAddr, size + 1);
    return size + 1;
}

//u8 Bootloader_flag = 0;

void AllDataInit(void)
{
//		u8 cfgInfoTemp = 0;
	
    Timer.IWDGFlag.Enble = 1;
    Timer.tUsart1.Enble = 1;
    Timer.SpeedFMM.Enble = 1;
    Timer.tCAN1.Enble = 1;
    Timer.MainLoop.Enble = 1;
    Timer.ReSetInfo.Enble = 1;

    RotaSpeed1.TPeriodSum = 0;
    RotaSpeed1.TPeriodMin = 0xFFFFFFFF;
    RotaSpeed1.TPeriodMax = 0;

    ECUStatus.IWDGEnableFlag = 0;
    ExtId.b.RxID = 0x07;
    ExtId.b.TxID = 0x01;
    ExtId.b.FrameCnt = 0;
    ExtId.b.State = 0x01;
    ExtId.b.Instr = 0x0A;

    S_CAN1.TxMsg.ExtId = ExtId.All;
    S_CAN1.TxMsg.IDE = CAN_ID_EXT;     //扩展模式
    S_CAN1.TxMsg.RTR = CAN_RTR_DATA;   //发送的是数捿
    S_CAN1.TxMsg.DLC = 5;              //数据长度
    S_CAN1.TxMsg.Data[0] = 0x04;
    S_CAN1.TxMsg.Data[1] = 0x22;
    S_CAN1.TxMsg.Data[2] = 0x00;
    S_CAN1.TxMsg.Data[3] = 0xEA;
    S_CAN1.TxMsg.Data[4] = 0x60;
//
    S_CAN2.TxMsg.StdId = 0x01;
    S_CAN2.TxMsg.ExtId = 0x07;
    S_CAN2.TxMsg.IDE = CAN_ID_EXT;     //扩展模式
    S_CAN2.TxMsg.RTR = CAN_RTR_DATA;   //发送的是数捿
    S_CAN2.TxMsg.DLC = 8;              //数据长度
    Engine.Accelerator = 0;
    memset(&ECU_Uart4.TX_BUF , 0x00 , sizeof(ECU_Uart4.TX_BUF));

//		STMFLASH_Read(STMFlashAddrCfg , &cfgInfoTemp , 1);
//		if(cfgInfoTemp == 0xFF)//无Bootloader
//		{
//			Bootloader_flag = 0;
//		}
//		else if(cfgInfoTemp == 0x00)//有Bootloader
//		{
//			Bootloader_flag = 1;
//		}
}

u8 CfgInfoCheck(u8* pBuf , u8 BufSize)
{
    if(BufSize < 5)
    {
        return 0;
    }
    if(pBuf[0] != CfgBuf0)
    {
        return 0;
    }
    if(pBuf[1] != CfgBuf1)
    {
        return 0;
    }
    if(pBuf[BufSize - 2] != SumArray(pBuf, 0, BufSize - 2))
    {
        return 0;
    }
    if(pBuf[BufSize - 1] != XORArray(pBuf, 0, BufSize - 2))
    {
        return 0;
    }

    return 1;
}
void FlashCheck(void)
{
    u8 ResetInfo0[ResetInfoLen] = {0};
    u8 ResetInfo1[ResetInfoLen] = {0};
    SaveData_Out saveInfo;
    u32 SPIFlashAddr0 = 0;
    u32 SPIFlashAddr1 = 0;
    u8 CheckErrFlag0 = 0;
    u8 CheckErrFlag1 = 0;
    u8 ResetInfosaveCnt0 = 0;
    u8 ResetInfosaveCnt1 = 0;
    u8 ResetInfo_AddrStart = 2;
    u8 ResetInfo_SaveCntIndex = 16;
    u8 ResetInfoStatusIndex = 8;
//1、读取Reset信息1 并进行校验
    FM25_Read(ResetInfo0 , ResetInfoAddr0 , ResetInfoLen);
    if(!ResetInfoCheck(ResetInfo0 , ResetInfoLen))
    {
        CheckErrFlag0 = 1;
        memset(ResetInfo0 , 0 , ResetInfoLen);    //校验不通过数据清零
    }

//2、读取Reset信息2 并进行校验
    FM25_Read(ResetInfo1 , ResetInfoAddr1 , ResetInfoLen);
    if(!ResetInfoCheck(ResetInfo1 , ResetInfoLen))
    {
        CheckErrFlag1 = 1;
        memset(ResetInfo1 , 0 , ResetInfoLen);    //校验不通过数据清零
    }
//3、确定实时数据存储地址
    ResetInfosaveCnt0 = ResetInfo0[ResetInfo_SaveCntIndex];
    ResetInfosaveCnt1 = ResetInfo1[ResetInfo_SaveCntIndex];

    SPIFlashAddr0 |= (ResetInfo0[ResetInfo_AddrStart] << 24);
    SPIFlashAddr0 |= (ResetInfo0[ResetInfo_AddrStart + 1] << 16);
    SPIFlashAddr0 |= (ResetInfo0[ResetInfo_AddrStart + 2] << 8);
    SPIFlashAddr0 |= (ResetInfo0[ResetInfo_AddrStart + 3]);
    SPIFlashAddr0 &= 0x0FFFFFF;

    SPIFlashAddr1 |= (ResetInfo1[ResetInfo_AddrStart] << 24);
    SPIFlashAddr1 |= (ResetInfo1[ResetInfo_AddrStart + 1] << 16);
    SPIFlashAddr1 |= (ResetInfo1[ResetInfo_AddrStart + 2] << 8);
    SPIFlashAddr1 |= (ResetInfo1[ResetInfo_AddrStart + 3]);
    SPIFlashAddr1 &= 0x0FFFFFF;

    if(1 == CheckErrFlag1 && 1 == CheckErrFlag0)    //均校验不通过（初次上电或被擦除）
    {
        SPIFlash.CurrentWriteAddr = 2 * ResetInfoAddr1;
        SPIFlash.Status = t_Ready;
    }
    else if(1 == CheckErrFlag1)     //ResetInfo1 检验不通过，以 ResetInfo0 信息复位
    {
        SPIFlash.CurrentWriteAddr = SPIFlashAddr0;
        SPIFlash.Status = (SPIFlashStatus)(ResetInfo0[ResetInfo_AddrStart] >> 4);
        Engine.ResetFlag = ResetInfo0[ResetInfoStatusIndex] & 0x03; //状态为1、2、3时复位时置位
        memcpy(ResetInfo.buf , ResetInfo0 , ResetInfoLen);
    }
    else if(1 == CheckErrFlag0)     //ResetInfo0检验不通过，以ResetInfo1信息复位
    {
        SPIFlash.CurrentWriteAddr = SPIFlashAddr1;
        SPIFlash.Status = (SPIFlashStatus)(ResetInfo1[ResetInfo_AddrStart] >> 4);
        Engine.ResetFlag = ResetInfo1[ResetInfoStatusIndex] & 0x03; //状态为1、2、3时复位时置位
        memcpy(ResetInfo.buf , ResetInfo1 , ResetInfoLen);
    }
    else if(ResetInfosaveCnt0 - ResetInfosaveCnt1 < 10)     //均校验通过，以存储次数大的信息复位
    {
        SPIFlash.CurrentWriteAddr = SPIFlashAddr0;
        SPIFlash.Status = (SPIFlashStatus)(ResetInfo0[ResetInfo_AddrStart] >> 4);
        Engine.ResetFlag = ResetInfo0[ResetInfoStatusIndex] & 0x03; //状态为1、2、3时复位时置位
        memcpy(ResetInfo.buf , ResetInfo0 , ResetInfoLen);
    }
    else     //均校验通过，以存储次数大的信息复位
    {
        SPIFlash.CurrentWriteAddr = SPIFlashAddr1;
        SPIFlash.Status = (SPIFlashStatus)(ResetInfo1[ResetInfo_AddrStart] >> 4);
        Engine.ResetFlag = ResetInfo1[ResetInfoStatusIndex] & 0x03; //发动机状态为1、2、3时复位时置位
        memcpy(ResetInfo.buf , ResetInfo1 , ResetInfoLen);
    }
//3.1如果是ECU复位重启 则记录复位信息并继续存储
//    SPIFlash.CurrentWriteAddr = SearchAddr_Able2Write( SPIFlash.CurrentWriteAddr , BlankSpaceMin);
    if(Engine.ResetFlag > 0)
    {
        memset(&saveInfo , 0x5A , DataInfoLen);
//        saveInfo.savedata1 = ECUStatus.ResetStartus.All;
//将被改为SD卡存储        SPIFlash.CurrentWriteAddr += W25Q64SaveData(&saveInfo , SPIFlash.CurrentWriteAddr , DataInfoLen);
    }
    else    //正常启动写入文件头39个0
    {
        memset(&saveInfo , '\r' , DataInfoLen);
//        saveInfo.savedata1 = ECUStatus.ResetStartus.All;
//将被改为SD卡存储                SPIFlash.CurrentWriteAddr += W25Q64SaveData(&saveInfo , SPIFlash.CurrentWriteAddr , DataInfoLen);
    }


    if(EngineRun == Engine.ResetFlag || EngineStart == Engine.ResetFlag)
    {
        Engine.ResetFlag = 1;
    }
    else
    {
        Engine.ResetFlag = 0;
    }
//3.2如果是正常启动 则先写入文件头并继续存储

}

/*********************************************************************************
** 函数名称: AnalizeCfgCom
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 配置指令解析
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无AckInfo
*********************************************************************************/
//uint32_t flash_count = 0;			//固件总的字节数
//uint16_t flash_count_size = 0;//拆分固件包最大size
//uint16_t flash_xuhao = 1;			//固件拆分包序号
//uint32_t flash_down_count = 0;//固件烧写完成字节数

//void AnalizeCfgCom(void)              //配置通信解析并处理
//{
//		int32_t ind = 0;
//		uint16_t flash_res;
//		uint32_t new_app_offset;
//		uint16_t len;
//		
//	
//    if(ECU_Usart1.Flag_rx_suc == 0 || ECU_Usart1.ComType != COM_CFG)
//    {
//        return;
//    }
//    if(ECU_Usart1.Flag_rx_suc == 1 && ECU_Usart1.ComType == COM_CFG && Engine.Status != 0)
//    {
//        ECU_Usart1.Flag_rx_suc = 0;
//        return;
//    }
//		if(ECU_Usart1.RX_BUF[4] == 0xF0 )      //升级请求指令 校验发动机编号 硬件版本号 软件版本号
//    {
//      ECUStatus.CfgStatus = 1;
//			Timer.CfgWait.Value = 0;
//			Timer.CfgWait.Enble = 1;
//			
//			flash_count = 0;			//固件总的字节数
//			flash_count_size = 0;//拆分固件包最大size
//			flash_xuhao = 1;			//固件拆分包序号
//			flash_down_count = 0;//固件烧写完成字节数
//			
//			//添加校验处理和响应处理 0x01：允许升级 0x02：发动机不匹配 0x03：硬件不匹配
//			flash_res = 0x01;
//			if(ECU_Usart1.RX_BUF[7] != 0xFE)
//			{
//				flash_res = 0x02;
//			}
//			else if(ECU_Usart1.RX_BUF[8] != 0x01 || ECU_Usart1.RX_BUF[9] != 0x02 || ECU_Usart1.RX_BUF[10] != 0x03)//高字节在前，低字节在后
//			{
//				flash_res = 0x03;
//			}
//			else
//			{
//				flash_res = 0x01;
//			}
//			//delay_ms(100);
//			//memset(AckInfo , 0x00 , sizeof(AckInfo));
//			AckInfo[0] = 0xA5;
//			AckInfo[1] = 0x5A;
//			AckInfo[2] = 0xE0;
//			AckInfo[3] = ECU_Usart1.RX_BUF[2];//0xA1
//			AckInfo[4] = 0xF0;
//			AckInfo[5] = 0x00;//高字节在前，低字节在后
//			AckInfo[6] = 0x03;
//			AckInfo[7] = flash_res;
//			
//			if(Bootloader_flag == 1)//有Bootloader
//			{
//				AckInfo[8] = 0x01;
//			}
//			else
//			{
//				AckInfo[8] = 0x00;
//			}
//			
//			AckInfo[9] = 0x00;
//			uint16_t crc_calc = crc16(AckInfo , 10); 
//			AckInfo[10] = crc_calc>>8;//高字节在前，低字节在后
//			AckInfo[11] = crc_calc;
//			sendAckdataflag = 1;
//			sendovertimeenable = 1;//开启超时重发
////			DMA_ClearFlag(DMA1_Stream6 , DMA_FLAG_TCIF6);
////			USART_DMACmd(USART2 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发送
////			MYDMA_Enable(DMA1_Stream6 , 12);     //开始一次DMA传输
////			
////			while(DMA1_Stream6->NDTR != 0);//等待传输完成
//			
//    }
//		else if(ECU_Usart1.RX_BUF[4] == 0xF1 )      //升级信息指令 固件大小 拆分固件包数 单包最大size
//    {
//      ECUStatus.CfgStatus = 1;
//			Timer.CfgWait.Value = 0;
//			Timer.CfgWait.Enble = 1;
//			//添加校验处理和响应处理 0x01：允许升级 0x04：空间不足 0x05：缓存buffer不足 0x06：擦除失败
//			ind = 7;
//			flash_res = 0x01;
//			flash_count = buffer_get_uint32(ECU_Usart1.RX_BUF, &ind);
//			ind  += 2;
//			flash_count_size = buffer_get_uint16(ECU_Usart1.RX_BUF, &ind);
//			ind = 0;
//			if(flash_count >393216)
//			{
//				flash_res = 0x04;
//			}
//			else if(flash_count_size >2048)
//			{
//				flash_res = 0x05;
//			}
//			else
//			{
//				if(ECU_Usart1.RX_BUF[2] == 0xA2 )//擦除bootloader
//				{
//					flash_res = flash_helper_erase_new_bootloader(flash_count);
//				}
//				else////擦除new_app
//				{
//					flash_res = flash_helper_erase_new_app(flash_count);
//				}
//				
//				if(flash_res == FLASH_COMPLETE)
//				{
//					flash_res = 0x01;
//				}
//				else
//				{
//					flash_res = 0x06;
//				}
//			}
//			
//			AckInfo[0] = 0xA5;
//			AckInfo[1] = 0x5A;
//			AckInfo[2] = 0xE0;
//			AckInfo[3] = ECU_Usart1.RX_BUF[2];//0xA1
//			AckInfo[4] = 0xF1;
//			AckInfo[5] = 0x00;//高字节在前，低字节在后
//			AckInfo[6] = 0x03;
//			AckInfo[7] = flash_res;
//			AckInfo[8] = 0x00;
//			AckInfo[9] = 0x00;
//			uint16_t crc_calc = crc16(AckInfo , 10); 
//			AckInfo[10] = crc_calc>>8;//高字节在前，低字节在后
//			AckInfo[11] = crc_calc;
//			sendAckdataflag = 1;
////			DMA_ClearFlag(DMA1_Stream6 , DMA_FLAG_TCIF6);
////			USART_DMACmd(USART2 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发送
////			MYDMA_Enable(DMA1_Stream6 , 12);     //开始一次DMA传输
////			while(DMA1_Stream6->NDTR != 0);//等待传输完成
//			//delay_ms(40);
//    }
//		else if(ECU_Usart1.RX_BUF[4] == 0xF2 )      //写NEW_APP_DATA命令 第一包数据4字节Size 2字节crc16 高字节在前 低字节在后
//    {
//      ECUStatus.CfgStatus = 1;
//			Timer.CfgWait.Value = 0;
//			Timer.CfgWait.Enble = 1;
//			
//			ind = 7;
//			uint16_t flash_xuhao1 = buffer_get_uint16(ECU_Usart1.RX_BUF, &ind);//高字节在前，低字节在后
//			if(flash_xuhao != flash_xuhao1)
//			{
//				flash_res = 0x07;//数据包序号错误
//			}
//			else
//			{
//				new_app_offset = flash_down_count;
//				uint16_t len1 = buffer_get_uint16(ECU_Usart1.RX_BUF, &ind);
//				if(len1<= 2048)
//				{
//					len = len1;
//					
//					if(ECU_Usart1.RX_BUF[2] == 0xA2 )//写入bootloader程序
//					{
//						flash_res = flash_helper_write_new_bootloader_data(new_app_offset, ECU_Usart1.RX_BUF + ind, len);
//					}
//					else//写入APP程序
//					{
//						flash_res = flash_helper_write_new_app_data(new_app_offset, ECU_Usart1.RX_BUF + ind, len);
//					}
//					
//					ind = 0;
//					
//					if(flash_res == FLASH_COMPLETE)
//					{
//						flash_down_count += len;
//						flash_xuhao ++;
//						flash_res = 0x01;//接收数据OK
//					}
//					else
//					{
//						flash_res = 0x08;//数据包写入错误
//					}
//				}
//				else
//				{
//					flash_res = 0x05;//数据包数据长度错误
//				}
//			}
//			
//			AckInfo[0] = 0xA5;
//			AckInfo[1] = 0x5A;
//			AckInfo[2] = 0xE0;
//			AckInfo[3] = ECU_Usart1.RX_BUF[2];//0xA1
//			AckInfo[4] = 0xF2;
//			AckInfo[5] = 0x00;//高字节在前，低字节在后
//			AckInfo[6] = 0x03;
//			AckInfo[7] = flash_xuhao1>>8;//高字节在前，低字节在后
//			AckInfo[8] = flash_xuhao1;
//			AckInfo[9] = flash_res;
//			uint16_t crc_calc = crc16(AckInfo , 10); 
//			AckInfo[10] = crc_calc>>8;//高字节在前，低字节在后
//			AckInfo[11] = crc_calc;
//			sendAckdataflag = 1;
////			DMA_ClearFlag(DMA1_Stream6 , DMA_FLAG_TCIF6);
////			USART_DMACmd(USART2 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发送
////			MYDMA_Enable(DMA1_Stream6 , 12);     //开始一次DMA传输
////			while(DMA1_Stream6->NDTR != 0);//等待传输完成
//			//delay_ms(40);
//    }
//		else if(ECU_Usart1.RX_BUF[4] == 0xF3 )      //升级整个固件CRC信息指令
//    {
//      ECUStatus.CfgStatus = 1;
//			Timer.CfgWait.Value = 0;
//			Timer.CfgWait.Enble = 1;
//			//添加校验处理和响应处理 0x01：下载成功 0x09：数据校验错误
//			ind = 7;
//			uint16_t crc_app = buffer_get_uint16(ECU_Usart1.RX_BUF, &ind);
//			uint16_t crc_calc = 0;
//			if(ECU_Usart1.RX_BUF[2] == 0xA2 )
//			{
//				crc_calc = crc16((uint8_t *)0x080E0000, flash_count);//bootloader CRC校验
//			}
//			else
//			{
//				crc_calc = crc16((uint8_t *)0x08080006, flash_count);//APP CRC校验
//			}
//			
//			ind = 0;
//			if (crc_calc != crc_app) 
//			{
//				flash_res = 0x09;
//			}
//			else
//			{
//				flash_res = 0x01;
//			}
//			
//			AckInfo[0] = 0xA5;
//			AckInfo[1] = 0x5A;
//			AckInfo[2] = 0xE0;
//			AckInfo[3] = ECU_Usart1.RX_BUF[2];//0xA1
//			AckInfo[4] = 0xF3;
//			AckInfo[5] = 0x00;//高字节在前，低字节在后
//			AckInfo[6] = 0x03;
//			AckInfo[7] = flash_res;
//			AckInfo[8] = 0x00;
//			AckInfo[9] = 0x00;
//			uint16_t crc_calc1 = crc16(AckInfo , 10); 
//			AckInfo[10] = crc_calc1>>8;//高字节在前，低字节在后
//			AckInfo[11] = crc_calc1;
//			sendAckdataflag = 1;
////			DMA_ClearFlag(DMA1_Stream6 , DMA_FLAG_TCIF6);
////			USART_DMACmd(USART2 , USART_DMAReq_Tx , ENABLE);  //使能串口2的DMA发送
////			MYDMA_Enable(DMA1_Stream6 , 12);     //开始一次DMA传输
////			//此处需添加延时，等待数据发送完成后跳转
////			while(DMA1_Stream6->NDTR != 0);//等待传输完成
//			//delay_ms(40);			
//    }
//		else if(ECU_Usart1.RX_BUF[4] == 0xF4 )      //升级整个固定CRC信息指令
//    {
//      ECUStatus.CfgStatus = 1;
//			Timer.CfgWait.Value = 0;
//			Timer.CfgWait.Enble = 1;
//			
//			sendovertimeenable = 0;//关闭超时重发
//			if(ECU_Usart1.RX_BUF[2] == 0xA2)//最后应答帧
//			{
//				if(Bootloader_flag == 0)//Bootloader
//				{
//					u8 cfgInfoTemp = 0x00;//有Bootloader
//					STMFLASH_Write(STMFlashAddrCfg , &cfgInfoTemp , 1);
//					Bootloader_flag = 1;
//				}
//				
//				Timer.CfgWait.Enble = 0;
//				Timer.CfgWait.Value = 0;
//				ECUStatus.CfgStatus = 0;
//				
//			}
//			else if(ECU_Usart1.RX_BUF[2] == 0xA1)
//			{
//				flash_helper_jump_to_bootloader();	
//			}
//    }
//}

//void AnalizeCfgCom(u8 *revBuf)              //配置通信解析并处琿
//{
//    if(revBuf[2] == 0x11)      //写入配置
//    {
//        STMFLASH_Write(STMFlashAddrCfg , revBuf , CfgInfoLen);  //配置片内Flash
//        ECUStatus.CfgStatus = 1;
//        //串口返回配置成功标志
//        memcpy(ECU_Usart1.TX_BUF , revBuf , CfgInfoLen);
//        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
//        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
//        MYDMA_Enable(DMA2_Stream7 , CfgInfoLen);     //开始一次DMA传输＿
//    }
//    if(revBuf[2] == 0x13)      //读取配置
//    {
//        STMFLASH_Read(STMFlashAddrCfg , ECU_Usart1.TX_BUF , CfgInfoLen);
//        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
//        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
//        MYDMA_Enable(DMA2_Stream7 , CfgInfoLen);     //开始一次DMA传输＿
//    }
//    if(revBuf[2] == 0x14)      //擦除片外Flash
//    {
//        W25QXX_Erase_Chip();
//        memset(ECU_Usart1.TX_BUF , 0 , 100);
//        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
//        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
//        MYDMA_Enable(DMA2_Stream7 , CfgInfoLen);     //开始一次DMA传输＿

//        NVIC_SystemReset();
//    }

//}
void AnalyseCommander(u8 *revBuf)              //数据通信解析并处理
{
//    if(revBuf[2] != revBuf[3])
//    {
//        return;
//    }
//    u32 SpeedTemp = 0;
//    switch(revBuf[2])
//    {
//		case 0x1D:
//		case 0x2D:
//		case 0x3D:
//		case 0x4D:
//		case 0x5D:
//		case 0x6D:
//		case 0x7D:
//		case 0x8D:
//		case 0x9D:
//        case 0xAD:
//			Engine.Instr = revBuf[2];	//0xXD X=1~10
//			break;

//        case 0xE5:
//            Engine.Instr = revBuf[2];
//            Eblast.EnableFlag = 1;
//            Eblast.T_Open = (u16)(revBuf[6] << 8 | revBuf[7]);
//            Eblast.T_Cycle = (u16)(revBuf[8] << 8 | revBuf[9]);
//            break;

//        case 0xE6:
//            Engine.Instr = revBuf[2];
//            Eblast.EnableFlag = 0;
//            Eblast_Power = EblastOFF;
//            break;
//        case 0xE7:
//            Engine.Instr = revBuf[2];
//            EValve_Power = EValveON;
//            break;

//        case 0xE8:
//            Engine.Instr = revBuf[2];
//            EValve_Power = EValveOFF;
//            break;

//        case 0xE9:              //开电机
//            Engine.Instr = revBuf[2];
//            Motor.EnableFlag = 1;   //电机4V 28*3/20 = 4.2V
//            Motor.T_Cycle = 100;
//            Motor.T_Open = (revBuf[5] >> 4) * 10 + (revBuf[5] & 0x0F);;
//            break;

//        case 0xEA:              //关电机
//            Engine.Instr = revBuf[2];
//            Motor.EnableFlag = 0;
//            Motor.T_Open = 0;
//            break;

//        case 0xF0:      //停车
//            Engine.Instr = revBuf[2];
//            break;

//        case 0xF1:      //手动加油门
//            Engine.Instr = revBuf[2];
//            Engine.Flag_EnableManualAcc = 1;
//            break;

//        case 0xF2:      //手动减油门
//            Engine.Instr = revBuf[2];
//            Engine.Flag_EnableManualAcc = 1;
//            break;

//        case 0xF3:      //装订转速
//            SpeedTemp = (u32)((revBuf[4] << 8) +  revBuf[5]) * 2;
//            if(SpeedTemp >= Speed_D[0] && SpeedTemp <= Speed_D[EngineGearCnt - 1])
//            {
//                Engine.Instr = revBuf[2];
//                Engine.RotaSpeed_Load = SpeedTemp;
//            }
//            break;

//        case 0xFC:      //起动
//            Engine.Instr = revBuf[2];
//            if(0 != revBuf[5])
//            {
//                motorDuty = (revBuf[5] >> 4) * 10 + (revBuf[5] & 0x0F);
//            }
//            if(0 != revBuf[7])
//            {
//                fireworkTime = (revBuf[7] >> 4) * 10 + (revBuf[7] & 0x0F);
//            }
//            if(0 != revBuf[8] || 0 != revBuf[9])
//            {
//                fireT4 = (revBuf[8] & 0x0F) * 100 + (revBuf[9] >> 4) * 10 + (revBuf[9] & 0x0F);
//            }
//            break;

//        default:
//            break;
//    }
}

void ResetRegCheck(void)
{
//寄存器检浿
    ECUStatus.ResetStartus.bit.IWDGRST = RCC_GetFlagStatus(RCC_FLAG_IWDGRST);
    ECUStatus.ResetStartus.bit.SFTRST = RCC_GetFlagStatus(RCC_FLAG_SFTRST);
    ECUStatus.ResetStartus.bit.PORRST = RCC_GetFlagStatus(RCC_FLAG_PORRST);
    ECUStatus.ResetStartus.bit.BORRST = RCC_GetFlagStatus(RCC_FLAG_BORRST);
    ECUStatus.ResetStartus.bit.PINRST = RCC_GetFlagStatus(RCC_FLAG_PINRST);
    RCC_ClearFlag();    //清除RCC_CSR标志
}

void funTemp(void)
{
    u8 tempi = 0;
//**************************Flash Test  Start
    IWDG_Feed();
    while(0)
    {
//        IWDG_Feed();

    }
    TIM2->CNT = 0;
//    W25QXX_Erase_Sector(1);

    TIM2->CNT = 0;
//    W25QXX_Erase_Sector(100);
    TIM2->CNT = 0;
//    W25QXX_Erase_Chip();



//    W25QXX_Read(Data_FromFlash, Address_Data, 30);
//    addr1 =  TIM2->CNT;
    //********************Flash Test  ENED*****************************

    if(10 <= Timer.tUsart1.Value)
    {
        ECU_Usart1.Count_tx = 0;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = ComHead0;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = ComHead1;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = 0x03;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = (u8)sADC.V_EValve;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = 0;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = (u8)sADC.Temp_ECU;
        ECU_Usart1.TX_BUF[ECU_Usart1.Count_tx++] = (u8)(Engine.Accelerator * 200.0f / ACCFULLRANGE);

        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , ECU_Usart1.Count_tx);     //开始一次DMA传输＿
        Timer.tUsart1.Value = 0;
    }
    IWDG_Feed();
    if(ECU_Usart1.Flag_rx_suc)    //接收已完房不再接收
    {
        if(0x01 == ECU_Usart1.RX_BUF[3])
        {
            Engine.Accelerator += ACCFULLRANGE / 200;
        }
        else if(0x02 == ECU_Usart1.RX_BUF[3])
        {
            Engine.Accelerator -= ACCFULLRANGE / 200;
        }
        else if(0x03 == ECU_Usart1.RX_BUF[3])
        {
//            YHRelay = !YHRelay;
            //HYRelay = !HYRelay;
           // DFRelay = !DFRelay;
           // BYRelay = YHRelay;
        }
        Engine.Accelerator = Engine.Accelerator > ACCFULLRANGE ? ACCFULLRANGE : Engine.Accelerator;
        Engine.Accelerator = Engine.Accelerator < 0 ? 0 : Engine.Accelerator;
        TIM_OCSetDutyCycle(TIM4,TIM_Channel_1,Engine.Accelerator);
        ECU_Usart1.Flag_rx_suc = 0;
        ECU_Usart1.Count_rx = 0;
    }
    IWDG_Feed();

    if(10 <= Timer.tCAN1.Value)
    {
        CAN_Transmit(CAN1, &S_CAN1.TxMsg);
        /*for(int i = 0; i < 8 ; i++)
        {
            S_CAN1.TxMsg.Data[i] = i + tempi;
            S_CAN2.TxMsg.Data[i] = S_CAN1.TxMsg.Data[i] * 5;
        }
        if(ExtId.b.FrameCnt >= 2)
        {
            ExtId.b.State = 0x03;
            S_CAN1.TxMsg.ExtId = ExtId.All;
            CAN_Transmit(CAN1, &S_CAN1.TxMsg);
            ExtId.b.FrameCnt = 0;
        }
        else
        {
            ExtId.b.State = 0x02;
            S_CAN1.TxMsg.ExtId = ExtId.All;
            CAN_Transmit(CAN1, &S_CAN1.TxMsg);
            ExtId.b.FrameCnt++;
        }*/

//            CAN_Transmit(CAN2, &S_CAN2.TxMsg);
        tempi++;
        Timer.tCAN1.Value = 0;
//        LED1 = !LED1;
    }

}

void CommuniTest( u8 * revBuf)
{
    u8 spiFlashBuf[100] = {0};
    if(revBuf[3] == 0xC7)
    {
        u32 spiAddr = revBuf[6];
        memset(spiFlashBuf , 0xC7 , 20);
        W25QXX_Write(spiFlashBuf, spiAddr << 12, 10);
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        W25QXX_Read( ECU_Usart1.TX_BUF,spiAddr << 12,100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 100);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC6)      //擦除指定扇区指令
    {
        u32 spiAddr = revBuf[6];
        W25QXX_Erase_Sector(spiAddr);
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        W25QXX_Read( ECU_Usart1.TX_BUF,spiAddr << 12,100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 100);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC5)      //擦除整个片子 指令
    {
        u32 spiAddr = revBuf[6];
        W25QXX_Erase_Chip();
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        W25QXX_Read( ECU_Usart1.TX_BUF,spiAddr << 12,100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 100);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC4)      //读取指定扇区剿00个字芿
    {
        u32 spiAddr = revBuf[6];
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        W25QXX_Read( ECU_Usart1.TX_BUF,spiAddr << 12,100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 100);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC2)
    {
        if(((Timer.ReSetInfo.Value > T_ResetInfoSave ) || Engine.StatusChangeFlag)
             && 0x00 == W25QXX_Get_BusyStatus())
        {
            if(0 != ResetInfoSaveUncheck(ResetInfo , SPIFlash.CurrentWriteAddr , Engine))
            {
                ResetInfo.saveCnt ++;
                ResetInfo.saveAddrFlag = (!ResetInfo.saveAddrFlag) & 0x01;
                W25QXX_Erase_Sector_UnWait((u32)ResetInfo.saveAddrFlag);
                Timer.ReSetInfo.Value = 0;
                Engine.StatusChangeFlag = 0;
            }
        }
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 4);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC1)
    {
        u32 spiAddr = revBuf[6] << 16;
        u32 DstAddr = 0;
        spiAddr |= revBuf[7] << 8;
        spiAddr |= revBuf[8];
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        DstAddr = SearchAddr_Able2Write( spiAddr , 100);
        ECU_Usart1.TX_BUF[0] = DstAddr >> 24;
        ECU_Usart1.TX_BUF[1] = DstAddr >> 16;
        ECU_Usart1.TX_BUF[2] = DstAddr >> 8;
        ECU_Usart1.TX_BUF[3] = DstAddr;
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 4);     //开始一次DMA传输＿
    }
    if(revBuf[3] == 0xC3)
    {
//        YHRelay = !revBuf[6];
//        HYRelay = !revBuf[7];
//        DFRelay = !revBuf[8];
//        BYRelay = !revBuf[9];
        memset(ECU_Usart1.TX_BUF , 0 , 100);
        DMA_ClearFlag(DMA2_Stream7 , DMA_FLAG_TCIF7);
        USART_DMACmd(USART1 , USART_DMAReq_Tx , ENABLE);  //使能串口1的DMA发逿
        MYDMA_Enable(DMA2_Stream7 , 4);     //开始一次DMA传输＿
    }

}

