/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_ATUs/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides ATU for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "NRISTF4_Define.h"
#include "string.h"
#include "crc.h"

/** @addtogroup ATU_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    NVIC_SystemReset();
    return;
/*   Go to infinite loop when Hard Fault exception occurs
  while (1)
  {
  }
*/

}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{

  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None

void PendSV_Handler(void)
{
}
  */
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None

void SysTick_Handler(void)
{

}
*/

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */
/*********************************************************************************
** 函数名称: USART1_IRQHandler
** 编 写 者  : 张迎
** 参考资料: 无
** 函数功能: 串口通信  起动电机
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/
void USART1_IRQHandler(void)                	//ECU通信
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(USART1);    //(USART3->DR);	//读取接收到的数据
        Res = Res;  //消除编译警告，可删除
		if(UsartRcv1.Flag_rx_suc)    //接收已完成 不再接收
		{
            return;
        }
//        if(Timer.tUsart1OutTime.Value > 10)  //接收中断则重新开始接收
//        {
//            UsartRcv1.Count_rx = 0;
//        }

        Timer.tUsart1OutTime.Enble = 1;
        Timer.tUsart1OutTime.Value = 0;
				UsartRcv1.Flag_rx_suc = UsartReceive_DC1(UsartRcv1.RX_BUF ,&UsartRcv1.Count_rx , Res);
    }
}

/*********************************************************************************
** 函数名称: UART4_IRQHandler
** 编 写 者  : 张迎
** 参考资料: 无
** 函数功能: 串口通信 
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/
void UART4_IRQHandler(void)                	//ECU通信
{
	static unsigned char xcpCtoRxLength;
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(UART4);    //(USART3->DR);	//读取接收到的数据

		if(UartRcv4.Flag_rx_suc)    //接收已完成 不再接收
		{
            return;
        }
        if(Timer.tUsart1OutTime.Value > 1)  //接收中断则重新开始接收
        {
            UartRcv4.Count_rx = 0;
						xcpCtoRxLength = 0;
        }

        Timer.tUsart1OutTime.Enble = 1;
        Timer.tUsart1OutTime.Value = 0;
				UartRcv4.Flag_rx_suc = UartReceive_DC4(UartRcv4.RX_BUF , &UartRcv4.ComType , &UartRcv4.Count_rx , Res);
				BootComRs232CheckActivationRequest(&xcpCtoRxLength , Res);
	}
}

/************************************************************************************//**
** \brief     Receives the CONNECT request from the host, which indicates that the
**            bootloader should be activated and, if so, activates it.
** \return    none.
**
****************************************************************************************/
static void BootComRs232CheckActivationRequest(u8 *xcpCtoRxLength , u8 RcvChar)
{
  static unsigned char xcpCtoReqPacket[64+1];
  //static unsigned char xcpCtoRxLength;
  static unsigned char xcpCtoRxInProgress = 0;

  /* start of cto packet received? */
  if (xcpCtoRxInProgress == 0)
  {
    /* store the message length when received */
      xcpCtoReqPacket[0] = RcvChar;
      /* check that the length has a valid value. it should not be 0 */
      if ( (xcpCtoReqPacket[0] > 0) && (xcpCtoReqPacket[0] <= 64) )
      {
        /* indicate that a cto packet is being received */
        xcpCtoRxInProgress = 1;
        /* reset packet data count */
        *xcpCtoRxLength = 0;
      }
  }
  else
  {
    /* store the next packet byte */
			xcpCtoReqPacket[*xcpCtoRxLength+1] = RcvChar;
      /* increment the packet data count */
      (*xcpCtoRxLength)++;

      /* check to see if the entire packet was received */
      if (*xcpCtoRxLength == xcpCtoReqPacket[0])
      {
        /* done with cto packet reception */
        xcpCtoRxInProgress = 0;

        /* check if this was an XCP CONNECT command */
        if ((xcpCtoReqPacket[1] == 0xff) && (*xcpCtoRxLength == 2))
        {
          /* connection request received so start the bootloader */
          //BootActivate();
					NVIC_SystemReset();
        }
      }
  }
} /*** end of BootComRs232CheckActivationRequest ***/


/*********************************************************************************
** 函数名称: USART2_IRQHandler
** 编 写 者  : 张迎
** 参考资料: 无
** 函数功能: 串口通信  油泵电机
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/
void USART2_IRQHandler(void)                	//ECU通信
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(USART2);    //(USART3->DR);	//读取接收到的数据
        Res = Res;  //消除编译警告，可删除
		if(ECU_Usart2.Flag_rx_suc)    //接收已完成 不再接收
		{
            return;
        }
        if(Timer.tUsart1OutTime.Value > 10)  //接收中断则重新开始接收
        {
            UsartRcv2.Count_rx = 0;
        }

        Timer.tUsart1OutTime.Enble = 1;
        Timer.tUsart1OutTime.Value = 0;
				UsartRcv2.Flag_rx_suc = UsartReceive_DC2(UsartRcv2.RX_BUF ,&UsartRcv2.Count_rx , Res);
    }
}

u8 UsartReceive_DC(u8 *RxBuf , u16 *RxCnt , u8 RcvChar)              // 接收函数
{
    if(0 == *RxCnt && ComHead0 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    if(1 == *RxCnt && ComHead1 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    else if(1 == *RxCnt && ComHead0 != RcvChar)
    {
        *RxCnt = 0;
        return 0;
    }
    if(2 <= *RxCnt)     //数据长度
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;

        if(ComInstrLen == *RxCnt)
        {
            if(1)
            {
                return 1;       //接收成功
            }
            else
            {
                (*RxCnt) = 0;
                return 0;       //校验不通过
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

u8 UsartReceive_DC2(u8 *RxBuf , u16 *RxCnt , u8 RcvChar)              // 接收函数
{
    if(0 == *RxCnt && ComHead0 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    if(1 == *RxCnt && ComHead1 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    else if(1 == *RxCnt && ComHead0 != RcvChar)
    {
        *RxCnt = 0;
        return 0;
    }
    if(2 <= *RxCnt)     //数据长度
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;

        if(22 == *RxCnt)
        {
            unsigned short crc16temp=crc16(&RxBuf[5], 15);
						if( *(RxBuf + 22 - 1) == (crc16temp&0X00FF)
                && *(RxBuf + 22 - 2) == (crc16temp>>8))	
//						if(1)
            {
                return 1;       //接收成功
            }
            else
            {
                (*RxCnt) = 0;
                return 0;       //校验不通过
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

u8 UsartReceive_DC1(u8 *RxBuf , u16 *RxCnt , u8 RcvChar)              // 接收函数
{
    if(0 == *RxCnt && ComHead0 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    if(1 == *RxCnt && ComHead1 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        return 0;
    }
    else if(1 == *RxCnt && ComHead0 != RcvChar)
    {
        *RxCnt = 0;
        return 0;
    }
    if(2 <= *RxCnt)     //数据长度
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;

        if(9 == *RxCnt)
        {
            unsigned short crc16temp=crc16(&RxBuf[5], 2);
						if( *(RxBuf + 9 - 1) == (crc16temp&0X00FF)
                && *(RxBuf + 9 - 2) == (crc16temp>>8))	
//						if(1)
            {
                return 1;       //接收成功
            }
            else
            {
                (*RxCnt) = 0;
                return 0;       //校验不通过
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

u8 UartReceive_DC4(u8 *RxBuf , u8 *Ctype , u16 *RxCnt , u8 RcvChar)              //兵器导控所 接收函数
{
    static u8 ComType = COM_DATA;  //0为数据通信 1为配置通信
    if(0 == *RxCnt && ComHead0 == RcvChar)
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        ComType = COM_DATA;
        return 0;
    }
    if(0 == *RxCnt && CfgHead0 == RcvChar)      //配置头0
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;
        ComType = COM_CFG;
        return 0;
    }
    if (1 == *RxCnt)
    {
        if(COM_DATA == ComType)
        {
            if(ComHead1 == RcvChar)
            {
                *(RxBuf + *RxCnt) = RcvChar;
                (*RxCnt)++;
                return 0;
            }
            if(ComHead0 == RcvChar)
            {
                return 0;
            }
            if(CfgHead0 == RcvChar)     //通信类型转换
            {

                *RxBuf = RcvChar;
                ComType = COM_CFG;
                return 0;
            }
            *RxCnt = 0;
            return 0;
        }
        if(COM_CFG == ComType)
        {
            if(CfgHead1 == RcvChar)
            {
                *(RxBuf + *RxCnt) = RcvChar;
                (*RxCnt)++;
                return 0;
            }
            if(CfgHead0 == RcvChar)
            {
                return 0;
            }
            if(ComHead0 == RcvChar)     //通信类型转换
            {

                *RxBuf = RcvChar;
                ComType = COM_DATA;
                return 0;
            }
            *RxCnt = 0;
            return 0;
        }
    }
    if(2 <= *RxCnt)     //数据长度
    {
        *(RxBuf + *RxCnt) = RcvChar;
        (*RxCnt)++;

        if(ComInstrLen == *RxCnt && COM_DATA == ComType)
        {
            if( *(RxBuf + ComInstrLen - 1) == XORArray(RxBuf, 0, ComInstrLen - 2)
                && *(RxBuf + ComInstrLen - 2) == SumArray(RxBuf, 0, ComInstrLen - 2))
            {
                *Ctype = ComType;
                return 1;       //接收成功
            }
            else
            {
                (*RxCnt) = 0;
                return 0;       //校验不通过
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

/*********************************************************************************
** 函数名称: TIM7_IRQHandler
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 2ms定时器
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
//
void TIM7_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
    {
//        LED3 = !LED3;
        Timer.wait2ms++;
        Timer.While_bak++;
        Timer.While++;
        Timer.ADCSample.Value++;
        if(500 == Timer.wait2ms)
        {
//            LED1 = !LED1;
            Timer.wait2ms = 0;
            Timer.wait1s++;
            if(Timer.IWDGFlag.Enble)   //2ms
            {
                Timer.IWDGFlag.Value += 1;  //累加1S
            }
						if(Timer.CfgWait.Enble)   //2ms
            {
                Timer.CfgWait.Value += 1;  //累加1S
            }
						
        }
        if(5400 == Timer.wait1s)    //90分钟 5400秒
        {
            Timer.wait1s = 0;
        }

        if(Timer.MainLoop.Enble)
        {
            Timer.MainLoop.Value += 2;
            Timer.DataSaveLoop.Value += 2;
            if(Timer.MainLoop.Value >= 20)
            {
                Timer.MainLoop.Value = 0;
            }
            if(Timer.DataSaveLoop.Value >= 50)  //周期为50ms
            {
                Timer.DataSaveLoop.Value = 0;
            }
            if(6 == Timer.DataSaveLoop.Value && MainloopCtl.T50_6msFlag < 0xFF)
            {
//                MainloopCtl.T50_6msFlag ++;
                OSSemPost(sem.RTDataSave);
            }
            if(0 == Timer.MainLoop.Value && MainloopCtl.T0msFlag < 0xFF)
            {
//                MainloopCtl.T0msFlag ++;
                OSSemPost(sem.DataSample);
            }
            if(4 == Timer.MainLoop.Value && MainloopCtl.T4msFlag < 0xFF)
            {
//                MainloopCtl.T4msFlag ++;
                OSSemPost(sem.Control);
            }
            if(10 == Timer.MainLoop.Value && MainloopCtl.T10msFlag < 0xFF)
            {
//                MainloopCtl.T10msFlag ++;
                OSSemPost(sem.DataCOM);
            }
        }
        if(0 == (Timer.wait2ms % 5) && Timer.tCAN1.Enble)   //10ms
        {
            Timer.tCAN1.Value++;
        }
        if(0 == (Timer.wait2ms % 5) && Timer.tUsart1.Enble)   //10ms
        {
            Timer.tUsart1.Value++;
        }
        if(Timer.SpeedFMM.Enble)   //2ms
        {
            Timer.SpeedFMM.Value += 2;
        }

#if ECU110WP_DC
        Timer.tUsart1OutTime.Value++;   //防通信中断
#endif
        if(Timer.ReSetInfo.Enble && Timer.ReSetInfo.Value < 0xFFFF)
        {
            Timer.ReSetInfo.Value++;
        }
        if (Timer.StartControl.Enble && Timer.StartControl.Value < 0xFFFF)
        {
            Timer.StartControl.Value ++;
        }
//副油路电磁阀驱动
        if(Eblast.EnableFlag)
        {
            Eblast.T_Cnt++;
            if(Eblast.T_Cnt >= Eblast.T_Cycle)
            {
                Eblast.T_Cnt = 0;
                Eblast_Power = EblastON;
            }
            if(Eblast.T_Cnt >= Eblast.T_Open)
            {
                Eblast_Power = EblastOFF;
            }
        }
        else
        {
            Eblast_Power = EblastOFF;
        }
//主油路电磁阀驱动
        if(EValve.EnableFlag)
        {
            EValve.T_Cnt++;
			EValve_Work=EValveEnableON;
            if(EValve.T_Cnt >= EValve.T_Cycle)
            {
                EValve.T_Cnt = 0;
                EValve_Power = EValveON;//好像没用
				SpareValve1_Power=SpareValve1ON;//主阀
            }
            if(EValve.T_Cnt >= EValve.T_Open)
            {
                EValve_Power = EValveOFF;//好像没用
				SpareValve1_Power=SpareValve1OFF;//主阀
            }
        }
        else
        {
            EValve_Power = EValveOFF;
			SpareValve1_Power=SpareValve1OFF;
			EValve_Work=EValveEnableOFF;
        }

//引气阀控制
        if(BleedAir.EnableFlag)
        {
            BleedAir.T_Cnt++;
            if(BleedAir.T_Cnt >= BleedAir.T_Cycle)
            {
                BleedAir.T_Cnt = 0;
                BleedAir_Power = BleedAirON;
            }
            if(BleedAir.T_Cnt >= BleedAir.T_Open)
            {
                BleedAir_Power = BleedAirOFF;
            }
        }
        else
        {
            BleedAir_Power = BleedAirOFF;
        }
        if(Timer.Common.Enble && Timer.Common.Value < 0xFFFF)
        {
            Timer.Common.Value++;
        }
        if(Timer.SDCard.Enble && Timer.SDCard.Value < 0xFFFF)
        {
            Timer.SDCard.Value++;
        }
    }
    TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
}

static CCRTYPE OneCycleTime1;


//static CCRTYPE OneCycleTime2;
void TIM1_CC_IRQHandler(void)
{
    static u8  Arr_index = 0;
    if(TIM_GetITStatus(TIM1,TIM_IT_CC1)==SET)
    {
        TIM1->CNT = 68; //时间补偿 42 改成 68 84M -> 168M
        if(0 == RotaSpeed1.Isr_Enable)
        {
            TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);  //清除中断标志位
            return;
        }
		//兼容溢出中断同时发生
		if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
		{
			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);	//清除中断标志位
			OneCycleTime1.bit.FreH++;
			OneCycleTime1.bit.FreL = 0;
		}
		else
		{
			OneCycleTime1.bit.FreL = TIM1->CCR1;
		}
		
        if(OneCycleTime1.All > 1680u)   //50KHz以上才保存
        {
            RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All = OneCycleTime1.All;
            OneCycleTime1.All = 0;
            RotaSpeed1.Count_FMM++;
            if(0 == RotaSpeed1.TPeriodSum)
            {
                RotaSpeed1.TPeriodMin = RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All;
                RotaSpeed1.TPeriodMax = RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All;
            }
            else
            {
                if(RotaSpeed1.TPeriodMin > RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All)
                {
                    RotaSpeed1.TPeriodMin = RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All;
                }
                if(RotaSpeed1.TPeriodMax < RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All)
                {
                    RotaSpeed1.TPeriodMax = RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All;
                }
            }
            RotaSpeed1.TPeriodSum += RotaSpeed1.FreGet[Arr_index % ROTABUFSIZE].All;
            Arr_index++;
        }

        TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);  //清除中断标志位

    }

}
void TIM1_UP_TIM10_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)    //1000ms未发生中断则清空数组
    {
        TIM1->CNT = 68; //时间补偿
        TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除中断标志位
        if(0 == RotaSpeed1.Isr_Enable)
        {
            return;
        }
        OneCycleTime1.bit.FreH++;

        if(OneCycleTime1.bit.FreH > 1281)    //1000ms未发生中断则清空数组
        {
            memset(RotaSpeed1.FreGet , 0 , ROTABUFSIZE * 4);
        }
    }


}
/*********************************************************************************
** 函数名称: TIM3_IRQHandler
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 1ms定时器
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/
void TIM3_IRQHandler(void)
{
    static u8  Arr_index = 0;
    static CCRTYPE OneCycleTime;
    if(TIM_GetITStatus(TIM3,TIM_IT_CC2)==SET)
    {
        TIM3->CNT = 42; //时间补偿
        if(0 == RotaSpeed2.Isr_Enable)
        {
            TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);  //清除中断标志位
            return;
        }
        OneCycleTime.bit.FreL = TIM3->CCR2;
        RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All = OneCycleTime.All;
        OneCycleTime.All = 0;
        RotaSpeed2.Count_FMM++;

        if(0 == RotaSpeed2.TPeriodSum)
        {
            RotaSpeed2.TPeriodMin = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
            RotaSpeed2.TPeriodMax = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
        }
        else
        {
            if(RotaSpeed2.TPeriodMin > RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All)
            {
                RotaSpeed2.TPeriodMin = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
            }
            if(RotaSpeed2.TPeriodMax < RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All)
            {
                RotaSpeed2.TPeriodMax = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
            }
        }
        RotaSpeed2.TPeriodSum += RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
        Arr_index++;
        TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);  //清除中断标志位
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	//清除中断标志位
    }


    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
    {
        TIM3->CNT = 42; //时间补偿
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
        if(0 == RotaSpeed2.Isr_Enable)
        {
            return;
        }
        OneCycleTime.bit.FreH++;

        if(OneCycleTime.bit.FreH > 1281)    //1000ms未发生中断则清空数组
        {
            memset(RotaSpeed2.FreGet , 0 , ROTABUFSIZE * 4);
        }
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	//清除中断标志位
    }
}
/*********************************************************************************
** 函数名称: TIM2_IRQHandler
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 1ms定时器
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/
void TIM2_IRQHandler(void)
{
//    static u8  Arr_index = 0;
//    static CCRTYPE OneCycleTime;
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
//点火器控制
        if(Firework.EnableFlag)
        {
			Firework.T_Cnt++;
            if(Firework.T_Cnt >= Firework.T_Cycle)
            {
                Firework.T_Cnt = 0;
                Firework_Power = FireworkON;
            }
			if(Firework.T_Cnt >= Firework.T_Open)
			{
				Firework_Power = FireworkOFF;
			}
		}
		else
		{
			Firework_Power = FireworkOFF;
			Firework.T_Cnt = 0;
		}
//电机控制
//        if(Motor.EnableFlag)
//        {
//            		
////					  WuShua = WuShuaON;
//					
//					  Motor.T_Cnt++;
//            if(Motor.T_Cnt >= Motor.T_Cycle)
//            {
//                Motor.T_Cnt = 0;
//                Motor_Power = MotorON;
//            }
//            if(Motor.T_Cnt >= Motor.T_Open)
//            {
//                Motor_Power = MotorOFF;
//            }
//        }
//        else
//        {
//					
////						WuShua = WuShuaOFF;
//					
//            Motor_Power = MotorOFF;
//						Motor.T_Cnt = 0;
//        }

			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位

    }
//    if(TIM_GetITStatus(TIM2,TIM_IT_CC3)==SET)
//    {
//        TIM2->CNT = 42; //时间补偿
//        if(0 == RotaSpeed2.Isr_Enable)
//        {
//            TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);  //清除中断标志位
//            return;
//        }
//        OneCycleTime.bit.FreL = TIM2->CCR3;
//        RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All = OneCycleTime.All;
//        OneCycleTime.All = 0;
//        RotaSpeed2.Count_FMM++;

//        RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].bit.FreL = TIM2->CCR3;

//        if(0 == RotaSpeed2.TPeriodSum)
//        {
//            RotaSpeed2.TPeriodMin = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
//            RotaSpeed2.TPeriodMax = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
//        }
//        else
//        {
//            if(RotaSpeed2.TPeriodMin > RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All)
//            {
//                RotaSpeed2.TPeriodMin = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
//            }
//            if(RotaSpeed2.TPeriodMax < RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All)
//            {
//                RotaSpeed2.TPeriodMax = RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
//            }
//        }
//        RotaSpeed2.TPeriodSum += RotaSpeed2.FreGet[Arr_index % ROTABUFSIZE].All;
//        Arr_index++;

//        TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);  //清除中断标志位
//    }


//    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
//    {
//        TIM2->CNT = 42; //时间补偿
//        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
//        if(0 == RotaSpeed2.Isr_Enable)
//        {
//            return;
//        }
//        OneCycleTime.bit.FreH++;
//        if(OneCycleTime.bit.FreH > 1281)    //1000ms未发生中断则清空数组
//        {
//            memset(RotaSpeed2.FreGet , 0 , ROTABUFSIZE * 4);
//        }
//    }
}


/************************************CAN1报文接收中断服务程序(FIFO0)*************
** 函数名称：CAN1_RX0_IRQHandler
** 编写者  ：黄若
** 参考资料：无
** 函数功能：CAN1报文接收中断服务程序(FIFO0)
** 输入参数：无
** 输出参数：无
** 修改时间: 2015年6月3日
** 修改内容：1. 加入清除标志位
             2. 加入接收成功标志寄存器
             3. 加入释放FIFO指令
** 修改人  ：崔雷
** 备    注：无
*********************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);                                       //清除FIFO0消息挂号中断标志位
	CAN_Receive(CAN1, CAN_FIFO0, &S_CAN1.RxMsg);									    //将FIFO0中接收数据信息存入消息结构体中
//    LED2 = !LED2;
    ExtIdSTRUCT rx1extid;
    rx1extid.All = S_CAN1.RxMsg.ExtId;
    if(rx1extid.b.FrameCnt == 0x02)
    {
//        LED2 = !LED2;
    }

	if (0 == S_CAN1.Flag_rx_suc)// && S_CAN1.RxMsg.StdId == 0x01AD
    {
//        if(Detecting == TS_Control.DetectStatus)
        {
        }
        if(0x02 == S_CAN1.RxMsg.Data[0])        //速度反馈
        {
            memcpy(&S_CAN1.TxMsg.Data , &S_CAN1.RxMsg.Data , sizeof(S_CAN1.RxMsg.Data ));
            S_CAN1.Flag_rx_suc = 1;
        }
        else if(0x05 == S_CAN1.RxMsg.Data[0])   //电流反馈
        {
            S_CAN1.TxMsg.Data[0] = 0x05;
            S_CAN1.Flag_rx_suc = 1;
        }
        else
        {

        }
    }
	else
	{
	    S_CAN1.Flag_rx_suc = 0;															//接收失败
	}
}
/************************************CAN1报文接收中断服务程序(FIFO0)*************
** 函数名称：CAN2_RX0_IRQHandler
** 编写者  ：黄若
** 参考资料：无
** 函数功能：CAN1报文接收中断服务程序(FIFO0)
** 输入参数：无
** 输出参数：无
** 修改时间: 2015年6月3日
** 修改内容：1. 加入清除标志位
             2. 加入接收成功标志寄存器
             3. 加入释放FIFO指令
** 修改人  ：崔雷
** 备    注：无
*********************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
	CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);                                       //清除FIFO0消息挂号中断标志位
	CAN_Receive(CAN2, CAN_FIFO0, &S_CAN2.RxMsg);									    //将FIFO0中接收数据信息存入消息结构体中
	if (0 == S_CAN2.Flag_rx_suc)// && S_CAN1.RxMsg.StdId == 0x01AD
    {
//        if(Detecting == TS_Control.DetectStatus)
        {
        }
        if(0x02 == S_CAN2.RxMsg.Data[0])        //速度反馈
        {
            memcpy(&S_CAN2.TxMsg.Data , &S_CAN2.RxMsg.Data , sizeof(S_CAN2.RxMsg.Data ));
            S_CAN2.Flag_rx_suc = 1;
        }
        else if(0x05 == S_CAN2.RxMsg.Data[0])   //电流反馈
        {
            S_CAN2.TxMsg.Data[0] = 0x05;
            S_CAN2.Flag_rx_suc = 1;
        }
        else
        {

        }
    }
	else
	{
	    S_CAN2.Flag_rx_suc = 0;															//接收失败
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
