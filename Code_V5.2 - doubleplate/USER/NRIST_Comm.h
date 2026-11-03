#ifndef __NRIST_COMM_H
#define __NRIST_COMM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "NRISTF4_Config.h"
#include "sys.h"
#include "NRISTF4_Define.h"
#include "NRIST_calculate.h"
#include "NRISTF4_SPIflash.h"
#include "bsp.h"

#include "EngineControl_Out.h"
#include "CYS_110WP_3_Control.h"    /* Model's header file */
#include "rtwtypes.h"

/* Exported types ------------------------------------------------------------*/
void sendData(void);
void sendbumpData(void);
void sendstartmotorData(void);
void sendackData(void);
u8 W25Q64SaveData(SaveData_Out * DataBuf , u32 WriteAddr , u8 size);   //数据保存到SPI Flash
void AllDataInit(void);
u8 CfgInfoCheck(u8* pBuf , u8 BufSize);
void FlashCheck(void);
void ResetRegCheck(void);
//void AnalizeCfgCom(u8 *revBuf);              //配置通信解析并处理
void AnalizeCfgCom(void);              //配置通信解析并处理
void AnalyseCommander(u8 *revBuf);              //配置通信解析并处理

void funTemp(void);
void CommuniTest( u8 * revBuf);
extern u16 jj;
extern u16 B_Speed;


#endif
