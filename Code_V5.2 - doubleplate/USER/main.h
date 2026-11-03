/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "ucos_ii.h"  		// uC/OS-II系统函数头文件
#include "os_cpu.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   256
#define TASK_ML_STK_SIZE     256
#define	TASK_SD_STK_SIZE     256
#define	TASK_SR_STK_SIZE     256
#define	TASK_CL_STK_SIZE     256
#define	TASK_IN_STK_SIZE     256
#define TASK_SDIO_STK_SIZE     1024*4

/*******************设置任务优先级*******************/
#define TASK_MAIN_PRIO      14u
#define	TASK_CTL_PRIO       10u
#define	TASK_COM_PRIO       11u
#define	TASK_SAMPLE_PRIO    12u
#define	TASK_RES_PRIO       13u
#define TASK_SDCARD_PRIO    20u

/*******************设置互斥量先级*******************/
#define MUTEX_MAIN_PRIO     2u

/*********************ucosii系统************************/
//定义栈
extern OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];
extern OS_STK ML[TASK_ML_STK_SIZE];
extern OS_STK SD[TASK_SD_STK_SIZE];
extern OS_STK SR[TASK_SR_STK_SIZE];
extern OS_STK CL[TASK_CL_STK_SIZE];
extern OS_STK IN[TASK_IN_STK_SIZE];
extern OS_STK SDCARD[TASK_SDIO_STK_SIZE];

typedef struct {		    //信号量
    OS_EVENT *Control;              //发动机控制
    OS_EVENT *DataSample;           //数据采集
    OS_EVENT *DataCOM;              //数据通信
    OS_EVENT *RTDataSave;           //实时数据存储
    OS_EVENT *MutexMCtl;            //主控互斥信号量
}SEM;
extern SEM sem;
/* Exported functions ------------------------------------------------------- */

void TimingDelay_Decrement(void);
void SemCreat(void);
void TaskStkChk(void);
void Task_Main(void *p_arg);        //监控
void Task_Control(void *p_arg);         //发动机控制
void Task_DataSample(void *p_arg);  //数据采集
void Task_DataCOM(void *p_arg);  //数据通信
void Task_ResetDataSave(void *p_arg);  //复位数据存储
void Task_RTDataSave(void *p_arg);  //实时数据存储

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
