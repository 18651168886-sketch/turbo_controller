/*******************************(C) By CuiLei ************************************
 * 文件名称：NRIST_wdg.c 
 * 适用模块：STM32F105VCT7
 * 描    述：60所专用看门狗配置相关程序         
 * 实验平台：涡喷发动机ECU平台
 * 库版本  ：ST3.5.0
 *
 * 文件版本：V1.0.0.0002
 * 作    者：崔雷
 * 作者部门：航空电气研究室 
 * 完成日期：2015年6月6日
 * 
 * 取代版本：无
 * 原作者  ：无 
 * 完成日期：无
**********************************************************************************/
#include "watchdog.h"

/*********************************************************************************
** 函数名称：IWDG_Configuration
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：独立看门狗配置初始化
** 输入参数：prer    ----    预分频值
                             This parameter can be one of the following values:
                             IWDG_Prescaler_4: IWDG prescaler set to 4
                             IWDG_Prescaler_8: IWDG prescaler set to 8
                             IWDG_Prescaler_16: IWDG prescaler set to 16
                             IWDG_Prescaler_32: IWDG prescaler set to 32
                             IWDG_Prescaler_64: IWDG prescaler set to 64
                             IWDG_Prescaler_128: IWDG prescaler set to 128
                             IWDG_Prescaler_256: IWDG prescaler set to 256
             rlr     ----    重装载值（低12位有效）,范围为0~0x0FFF
			                 IWDG的计数周期 = rlr * 1 / (40 / prer) s  
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void IWDG_Configuration(uint8_t prer, uint16_t rlr)
{ 	  
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);                 //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	IWDG_SetPrescaler(prer);                                      //设置IWDG时钟的预分频值
	IWDG_SetReload(rlr);                                          //设置IWDG的计数值
	IWDG_ReloadCounter();                                         //重载IWDG计数值
	IWDG_Enable();                                                //使能IWDG    	    		     
}

/*********************************************************************************
** 函数名称：IWDG_Feed
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：独立看门狗喂狗函数
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void IWDG_Feed(void)
{ 
    IWDG_ReloadCounter();                                         //重载IWDG计数值       
}

/*********************************************************************************
** 函数名称：WWDG_Configuration
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：窗口看门狗配置初始化
** 输入参数：fprer    ----    预分频值
                              This parameter can be one of the following values:
                              WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
                              WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
                              WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
                              WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
             Counter  ----    初始计数值（低7位有效）,最大值为0x7F
			                  WWDG的计数周期 = (Counter - 0x3F) * 1 / WWDG counter clock ms 
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void WWDG_Configuration(uint32_t fprer, uint8_t Counter)
{ 
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);          //打开窗口看门狗时钟
// 	WWDG_SetPrescaler(fprer);                                     //设置WWDG时钟的预分频值
//     WWDG_Enable(Counter);                                         //设置WWDG初始计数值
// 	WWDG_ClearFlag();                                             //清除WWDG早期唤醒中断（EWI）标志
// 	WWDG_EnableIT();                                              //使能WWDG早期唤醒中断（EWI）   
}

/*********************************************************************************
** 函数名称：WWDG_IRQHandler
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：窗口看门狗早期唤醒中断服务函数
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void WWDG_IRQHandler(void)
{ 
//     WWDG_SetCounter(0x7F);                                        //更新WWDG计数器
// 	WWDG_ClearFlag();                                             //清除WWDG早期唤醒中断（EWI）标志       
}











