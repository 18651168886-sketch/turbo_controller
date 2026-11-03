/*******************************(C) By ZhangYing ************************************
* 文件名称: bsp.c
* 适用模块: STM32F407VG
* 描    述: 60所专用看门狗配置相关程序
* 实验平台: 涡喷发动机ECU平台
 * 文件版本: V1.0.0.0002
 * 作    者: 张迎
 * 作者部门: 航空电气研究室
 * 完成日期: 2019年6月6日
 *
 * 取代版本: 无
 * 原作者  : 无
 * 完成日期: 无
**********************************************************************************/

#include "bsp.h"
void BSP_Init(void)
{
	extern const unsigned long __Vectors[];
	SCB->VTOR = (unsigned long)&__Vectors[0];
	
  HSE_SetSysClock(8,336,2,7);         //配置系统时钟
	SysTick_init();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //2组响应优先级共有0-3 ，抢占为0-3
	
//初始化定时器
    InitTIM7();

#if DEBUG
    InitTIM2();     //测试用
#endif

		LED_GPIO_Init();   //LED初始化
    OUT_GPIO_Init();   //驱动输出
    IN_GPIO_Init();    //驱动反馈
//Flash 驱动初始化
//    W25QXX_Init();          //W25QXX初始化
    FRAM_Config();
    InitUsart1();//串口1 115200 422通信
    InitUsart2(); //串口2 115200 422通信
		InitUart4(); 
    InitADC();//ADC Init
//    InitPWM();// 油泵驱动
    InitIC1();//转速初始化
		InitIC2();
}

/****************************************
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 ****************************************/
void SysTick_init(void)
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
////删除了SysTick_CTRL_CLKSOURCE_Msk 保证8分频
//	SysTick->LOAD  = 168000000/8/OS_TICKS_PER_SEC - 1;                                  /* set reload register */
//	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
//	SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
//	SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk   |
//					 SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */

//如果需要支持OS.
	u32 reload;

 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

					//如果需要支持OS.
	reload=168/8;						//每秒钟的计数次数 单位为M
	reload*=1000000/1000;
	//reload*=1000000/OS_TICKS_PER_SEC;	//根据delay_ostickspersec设定溢出时间
											//reload为24位寄存器,最大值:16777216,在168M下,约合0.7989s左右

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload; 					//每1/delay_ostickspersec秒中断一次
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//开启SYSTICK

}
/*********************************************************************************
** 函数名称：PWM驱动
** 编写者  ：黄若
** 参考资料：无
** 函数功能：平台ADC初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitPWM(void)
{
	PWM1_GPIO_Init();
	TIM_DeInit(TIM4);
	TIM_InternalClockConfig(TIM4);
	TIM_InitConfig(TIM4, ACCFULLRANGE, 1);

	//PWM输出模式配置
	TIM_InitOC(TIM4, TIM_OCMode_PWM1, 0, TIM_OCPolarity_Low, 1);

}
/*********************************************************************************
** 函数名称：InitWatchdog
** 编写者  ：FY
** 参考资料：无
** 函数功能：InitWatchdog初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：500ms看门狗 程序会在上电1分钟后或发动机状态不为0时开启看门狗，保证配置
            片内Flash时，ECU不复位
*********************************************************************************/
void InitWatchdog(void)
{
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)!=RESET)
	{
		RCC_ClearFlag();
	}
    IWDG_Configuration(IWDG_Prescaler_32, 200);     //入库后新增1
    IWDG_ReloadCounter();
}

/*********************************************************************************
** 函数名称:PWM1_GPIO_Init
** 编写者  :崔雷
** 参考资料:无
** 函数功能:PWM1硬件端口初始化
** 输入参数:无
** 输出参数:无
** 修改时间:无
** 修改内容:无
** 修改人  :无
** 备    注:初始化PD12为复用输出口，并使能这个口的时钟
**          对应关系PWM1 —— PD12 —— TIM4 CH1
*********************************************************************************/
void PWM1_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  	      //TIM14时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	      //使能PORTF时钟

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);      //GPIOD12复用为定时器4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           					//GPIOD12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                  //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	          //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                  //上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);                        //初始化PD12

// 	GPIO_SetBits(GPIOD,GPIO_Pin_12);
}
/*************************************PWM占空比设置***********************************
** 函数名称：TIM_OCSetDutyCycle
** 编写者  ：黄若
** 参考资料：无
** 函数功能：PWM初始化
** 输入参数：TIMx       -----   定时器选择    TIM1（定时器1）
                                              TIM2（定时器2）
											  ……
										      TIM8（定时器8）

			 channel    -----   通道选择      TIM_Channel_1 （通道1） 0x00
			                                  TIM_Channel_2 （通道2） 0x04
											  TIM_Channel_3 （通道3） 0x08
										      TIM_Channel_4 （通道4） 0x0C

			 pulse      -----   跳变值设置    0x0000 ~ 0xFFFF


** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修 改 人：无
** 备     注：无
**********************************************************************************/
void TIM_OCSetDutyCycle(TIM_TypeDef* TIMx, uint8_t channel, uint16_t pulse)
{
    assert_param(IS_TIM_LIST8_PERIPH(TIMx));
	if (channel==TIM_Channel_1)
	{
	    TIMx->CCR1 = pulse;
	}
	else if (channel==TIM_Channel_2)
	{
	    TIMx->CCR2 = pulse;
	}
	else if (channel==TIM_Channel_3)
	{
	    TIMx->CCR3 = pulse;
	}
	else if (channel==TIM_Channel_4)
	{
	    TIMx->CCR4 = pulse;
	}
}

/*********************************************************************************
** 函数名称：TIM_InitOC
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：PWM初始化
** 输入参数：TIMx: where x can be  1 to 14 to select the TIM peripheral.

				mode        ——  模式选择       TIM_OCMode_Timing
											   TIM_OCMode_Active
											   TIM_OCMode_Inactive
											   TIM_OCMode_Toggle
											   TIM_OCMode_PWM1
											   TIM_OCMode_PWM2

				pulse       ——  跳变值设置     0x0000 ~ 0xFFFF

				polarity    ——  电平设置       TIM_OCPolarity_High  （Output Compare active high）
									           TIM_OCPolarity_Low   （Output Compare active low）

				channel     ——  通道选择       0x1 （通道1）
											   0x2 （通道2）
											   0x3 （通道3）
                                               0x4 （通道4）
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void TIM_InitOC(TIM_TypeDef* TIMx, uint16_t mode, uint16_t pulse, uint16_t polarity, uint8_t channel)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//初始化PWM模式
	TIM_OCInitStructure.TIM_OCMode = mode;                         //选择定时器模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = pulse;	                       //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = polarity;                 //输出极性:当定时器计数值小于CCR1_Val时为高或者低电平

    if (channel == 1)
    {
  	    TIM_OC1Init(TIMx, &TIM_OCInitStructure);	               //使能通道1
        TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);		     //使能TIM在CCR1上的预装载寄存器
    }
    else if (channel == 2)
    {
  	    TIM_OC2Init(TIMx, &TIM_OCInitStructure);	               //使能通道2
        TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);		     //使能TIM在CCR2上的预装载寄存器
    }
    else if (channel == 3)
    {
  	    TIM_OC3Init(TIMx, &TIM_OCInitStructure);	               //使能通道3
        TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);		     //使能TIM在CCR3上的预装载寄存器
    }
    else if (channel == 4)
    {
  	    TIM_OC4Init(TIMx, &TIM_OCInitStructure);	               //使能通道4
        TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);		     //使能TIM在CCR4上的预装载寄存器
    }

	TIM_ARRPreloadConfig(TIMx, ENABLE);                          //ARPE使能

	TIM_Cmd(TIMx, ENABLE);                                      //使能TIM
}

/*********************************************************************************
** 函数名称:LED_GPIO_Init
** 编 写 者:zy
** 参考资料:无
** 函数功能:LED初始化
** 输入参数:无
** 输出参数:无
** 修改时间:无
** 修改内容:无
** 修 改 人:无
** 备     注:
** H1   LED1 ---- PC1
*********************************************************************************/
void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);              //使能GPIOE时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//LED1，LED2和LED3对应IO口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                 //100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //上拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);                             //初始化GPIO

    GPIO_SetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);         //设置高，灯灭

}
/*********************************************************************************
** 函数名称:OUT_GPIO_Init
** 编 写 者:hk
** 参考资料:无
** 函数功能:开关量输出初始化
** 输入参数:无
** 输出参数:无
** 修改时间:无
** 修改内容:无
** 修 改 人:无
** 备     注:
** H1   副阀 ---- PE7
** H1   主阀 ---- PE8
** H1   引起阀 ---- PE10
** H1   备用 ---- PE11
** H1   电气未设计，原油泵 ---- PD11
** H1   电气未设计，原油泵 ---- PD12
** H1   点火器 ---- PD13
*********************************************************************************/
void OUT_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);                   //使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);                   //使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                   //使能GPIOE时钟

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11;  //IO1，IO2和IO3对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                           //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                          //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                            //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                  //初始化GPIO

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;	//GPIO_Pin_5| GPIO_Pin_6电机IO
	GPIO_Init(GPIOD, &GPIO_InitStructure);                                  //初始化GPIO

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//GPIO_Pin_5| GPIO_Pin_6电机IO
//	GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //初始化GPIO
	
	
    Eblast_Power = EblastOFF;
    SpareValve1_Power = SpareValve1OFF;
		BleedAir_Power = BleedAirOFF;
    SpareValve2_Power = SpareValve2OFF;      //默认置高，使能输出
    EValve_Power = EValveOFF;
    Firework_Power = FireworkOFF;
//		StartMotorH_Power=StartMotorHOFF;
//		StartMotorL_Power=StartMotorLOFF;
		//WuShua = WuShuaOFF;

}

/*
**  备用----PE12
**  引气----PE13
**  主阀----PE14
**  副阀----PE15
**  阀报警（上述4个阀任一个报警）----PD8
**  点火器报警----PD9
*/
void IN_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);                   //使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);                   //使能GPIOE时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;  //IO1F，IO2F和IO3F对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                            //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                            //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                  //初始化GPIO
	GPIO_SetBits(GPIOE, GPIO_InitStructure.GPIO_Pin);           //设置高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;  //IO4F对应IO口
	GPIO_Init(GPIOD, &GPIO_InitStructure);                                  //初始化GPIO
	GPIO_SetBits(GPIOD, GPIO_InitStructure.GPIO_Pin);           //设置高
}


/************************************SPI配置***********************************
** 函数名称：SPI_InitConfig
** 编写者  ：黄若
** 参考资料：无
** 函数功能：SPI初始化
** 输入参数：SPIx               -----    通道选择

             cpol  		        -----    空闲电平设置    SPI_CPOL_High
														 SPI_CPOL_LOW

			 cpha			    -----    触发边沿设置	 SPI_CPHA_1Edge(第一个边沿触发)
														 SPI_CPHA_2Edge(第二个边沿触发)

			 baudRatePrescaler  -----    波特率分频值  	 SPI_BaudRatePrescaler_x	   x= 2,4,8,16,32,64,128,256
                                                         分频后的时钟即为SPI的SCK的时钟频率
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/

/*********************************************************************************
** 函数名称：InitUsart
** 编写者  ：黄若
** 参考资料：无
** 函数功能：平台ADC初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitUsart1(void)
{
		USART1_GPIO_Init();
    USART_Configuration(USART1 , BaudRate2 , 8 , 1 , 0);
		USART_ITConfig(USART1 , USART_IT_RXNE , ENABLE);//开启相关中断
		NVIC_IT_Configuration(USART1_IRQn , SUBPRIO_USART1 , PREPRIO_USART1);
    MYDMA_Config(DMA2_Stream7 , DMA_Channel_4 , (u32)&USART1->DR , (u32)ECU_Usart1.TX_BUF , 9);//DMA2,STEAM7,CH4,外设为串口1,存储器为SendBuff,长度为:SEND_BUF_SIZE.
    DMA_ITConfig(DMA2_Stream7 , DMA_IT_TC , ENABLE);//开启相关中断
}

void InitUsart2(void)
{
		USART2_GPIO_Init();
    USART_Configuration(USART2 , BaudRate2 , 8 , 1 , 0);
		USART_ITConfig(USART2 , USART_IT_RXNE , ENABLE);//开启相关中断接收
		NVIC_IT_Configuration(USART2_IRQn , SUBPRIO_USART2 , PREPRIO_USART2);
    MYDMA_Config(DMA1_Stream6 , DMA_Channel_4 , (u32)&USART2->DR , (u32)ECU_Usart2.TX_BUF , 9);//DMA2,STEAM7,CH4,外设为串口2,存储器为SendBuff,长度为:SEND_BUF_SIZE.
    DMA_ITConfig(DMA1_Stream6 , DMA_IT_TC , ENABLE);//开启相关中断发送
}

void InitUart4(void)
{
		UART4_GPIO_Init();
    USART_Configuration(UART4 , BaudRate2 , 8 , 1 , 0);
		USART_ITConfig(UART4 , USART_IT_RXNE , ENABLE);//开启相关中断接收
		NVIC_IT_Configuration(UART4_IRQn , SUBPRIO_UART4 , PREPRIO_UART4);
    MYDMA_Config(DMA1_Stream4 , DMA_Channel_4 , (u32)&UART4->DR , (u32)ECU_Uart4.TX_BUF , 30);//DMA2,STEAM7,CH4,外设为串口2,存储器为SendBuff,长度为:SEND_BUF_SIZE.
    DMA_ITConfig(DMA1_Stream4 , DMA_IT_TC , ENABLE);//开启相关中断发送
}
//开启一次DMA传输
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//ndtr:数据传输量
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{

	DMA_Cmd(DMA_Streamx, DISABLE);                      //关闭DMA传输

	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//确保DMA可以被设置

	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //数据传输量

	DMA_Cmd(DMA_Streamx, ENABLE);                      //开启DMA传输
}


/*********************************************************************************
** 函数名称:USART1_GPIO_Init
** 编写者  :崔雷
** 参考资料:无
** 函数功能:USART1硬件端口初始化
** 输入参数:无
** 输出参数:无
** 修改时间:无
** 修改内容:无
** 修改人  :无
** 备    注:初始化PB6和PB7为复用输出口，并使能这2个口的时钟
**          对应关系USART1_TX —— GPIOA9
**                  USART1_RX —— GPIOA10
*********************************************************************************/
void USART1_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);              //使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);             //使能USART1时钟

	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);          //GPIOB6复用为USART1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);          //GPIOB7复用为USART1

	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;             //GPIOB6与GPIOB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                 //速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);                             //初始化PA9，PA10
}
void USART2_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);              //使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);             //使能USART2时钟

    //串口2对应引脚复用映射
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);          //GPIOD5复用为USART2
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);          //GPIOD6复用为USART2

    //USART2端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;             //GPIOD5与GPIOD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                    //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                             //初始化PD5，PD6
}

void UART4_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);              //使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);             //使能USART2时钟

    //串口2对应引脚复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);          //GPIOD5复用为USART2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);          //GPIOD6复用为USART2

    //USART2端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;             //GPIOD5与GPIOD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                    //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                             //初始化PD5，PD6
}


/*********************************************************************************
** 函数名称：USART_Configuration
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：串口初始化
** 输入参数：param  USARTx: Select the USART or the UART peripheral.
             This parameter can be one of the following values:
             USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
             BaudRate_Input    ——  波特率（建议115200, 9600等）
             WordLength_Input  ——  数据位： 8    8位数据
                                            9    9位数据
             StopBits_Input    ——  停止位： 1    1位停止位
                                            2    2位停止位
                                            3    0.5位停止位
                                            4    1.5位停止位
             Parity_Input      ——  校验位： 0    无校验
                                            1    寄校验
											                      2    偶校验
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void USART_Configuration(USART_TypeDef* USARTx, uint32_t BaudRate_Input, uint8_t WordLength_Input, uint8_t StopBits_Input, uint8_t Parity_Input)
{
		USART_InitTypeDef USART_InitStructure;

		assert_param(IS_USART_ALL_PERIPH(USARTx));                                      //检查参数

		USART_DeInit(USARTx);                                                           //复位串口
		//USART1 初始化设置
		USART_InitStructure.USART_BaudRate = BaudRate_Input;                            //波特率设置

		if(WordLength_Input == 9)
		{
				USART_InitStructure.USART_WordLength = USART_WordLength_9b;                 //9位数据
		}
		else
		{
				USART_InitStructure.USART_WordLength = USART_WordLength_8b;                 //8位数据
		}

		if(StopBits_Input == 2)
		{
				USART_InitStructure.USART_StopBits = USART_StopBits_2;                      //在帧结尾传输2个停止位
		}
		else if(StopBits_Input == 3)
		{
				USART_InitStructure.USART_StopBits = USART_StopBits_0_5;                    //在帧结尾传输0.5个停止位
		}
		else if(StopBits_Input == 4)
		{
				USART_InitStructure.USART_StopBits = USART_StopBits_1_5;                    //在帧结尾传输1.5个停止位
		}
		else
		{
				USART_InitStructure.USART_StopBits = USART_StopBits_1;                      //在帧结尾传输1个停止位
		}

		if(Parity_Input == 1)
		{
				USART_InitStructure.USART_Parity = USART_Parity_Odd ;                       //奇校验
		}
		else if(Parity_Input == 2)
		{
				USART_InitStructure.USART_Parity = USART_Parity_Even ;                      //偶校验
		}
		else
		{
				USART_InitStructure.USART_Parity = USART_Parity_No ;                        //无校验
		}

		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                //收发模式
		USART_Init(USARTx, &USART_InitStructure);                                       //初始化串口

		USART_Cmd(USARTx, ENABLE);                                                      //使能串口

}
/*********************************************************************************
** 函数名称：InitADC
** 编写者  ：黄若
** 参考资料：无
** 函数功能：平台ADC初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitADC(void)
{
	ADC_GPIO_Init();
	ADC1_DMA2S0_Configuration(ADC_SampleTime_84Cycles);
}

/*********************************************************************************
** 函数名称:ADC_GPIO_Init
** 编写者  :崔雷
** 参考资料:无
** 函数功能:ADC硬件端口初始化
** 输入参数:无
** 输出参数:无
** 修改时间:无
** 修改内容:无
** 修改人  :zy
** 备    注:初始化PA1，PA2为输入口，并使能这11个口的时钟
**          对应关系AN2  —— PA2未用
**                  AN3—— PA3未用
**                  AN4—— PA4排温
**                  AN5—— PA5总温基准
**                  AN6—— PA6备用
**                  AN8—— PB0总温
**                  AN9—— PB1油压
**                  AN16——CPU温度
*********************************************************************************/
void ADC_GPIO_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);              //使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);              //使能GPIOB时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);               //使能ADC1时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6; //AN2//AN5
                                                            
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                       //模拟输入
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);                             //初始化GPIO


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //AN8//AN9
                                                            
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                       //模拟输入
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

/*********************************************************************************
** 函数名称：ADC1_Configuration
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：ADC1初始化，配置ADC1的工作模式为DMA模式
** 输入参数：ADC_SampleTime  --  ADC_SampleTime_3Cycles     3个周期
            					           ADC_SampleTime_15Cycles    15个周期
								                 ADC_SampleTime_28Cycles    28个周期
								                 ADC_SampleTime_56Cycles    56个周期
								                 ADC_SampleTime_84Cycles	  84个周期
								                 ADC_SampleTime_112Cycles   112个周期
								                 ADC_SampleTime_144Cycles   144个周期
								                 ADC_SampleTime_480Cycles   480个周期
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void ADC1_DMA2S0_Configuration(uint8_t ADC_SampleTime)
{
 //   ADC1->ADC_CCR = ADC1->ADC_CCR | (0x000001 << 23);
	DMA_InitTypeDef DMA_InitStructure;                                          //DMA初始化结构
	ADC_InitTypeDef ADC_InitStructure;                                          //ADC初始化结构
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);                        //开启DMA1时钟
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);                        //关闭复位时钟

	/*****************DMA channel0 configuration*******************/
	DMA_DeInit(DMA2_Stream0);                                                   //将DMA的通道0寄存器重设为缺省值
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;                              //选择DMA通道，通道存在于数据流中
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;                 //ADC的源头地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sADC.ConvertedValue;     //DMA目标内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                     //外设作为数据传输的源头
	DMA_InitStructure.DMA_BufferSize = ADCDMABufSize;                           //DMA通道的DMA缓存大小，共8个通道，每个通道采集10次
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            //外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//外设数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	        //内存数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             //循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         //DMA通道X拥有高优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                      //禁止DMA FIFO，使用直连模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;           //FIFO阈值大小
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 //存储器突发单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         //外设突发单次传输
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);                                 //初始化

	DMA_Cmd(DMA2_Stream0, ENABLE);                                              //使能DMA外设

	/**********************ADC1 configuration**********************/
	ADC_DeInit();
	ADC_TempSensorVrefintCmd(ENABLE);                                           //开温度转换功能
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                    //独立模式
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                 //预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;     //DMA失能
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//两个采样阶段之间的延迟10个时钟
	ADC_CommonInit(&ADC_CommonInitStructure);                                   //初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                      //12位模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                //扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          //连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      //右对齐
	ADC_InitStructure.ADC_NbrOfConversion = ADC_CHANELCOUNT;                //转换通道2个
	ADC_Init(ADC1, &ADC_InitStructure);                                         //ADC初始化

	/*设置ADC1的11个规则组通道，设置它们的转化顺序和采样时间，转换时间=采样时间+12个周期*/
	assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));                           //参数校验

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime);   //AN2 未用
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime);  //AN3未用
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 3, ADC_SampleTime);  //AN16 CPU温度	
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime);  //AN4 排温
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime);  //AN5 总温基准
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime); //AN6 备用
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime); //AN8 总温
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime); //AN9 油压

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);                           //使能DMA请求
	ADC_DMACmd(ADC1, ENABLE);                                                   //使能ADC的DMA接口
	ADC_Cmd(ADC1, ENABLE);                                                      //使能ADC外设

	ADC_SoftwareStartConv(ADC1);                                     			//由于没有采用外部触发，所以使用软件触发ADC转换

}

/*********************************************************************************
** 函数名称：NVIC_IT_Configuration
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：中断优先级初始化
** 输入参数：IRQChannelx   ——  中断通道选择（见stm32f40x.h中IRQn_Type）
             Priorityx     ——  抢占优先级
             SubPriorityx  ——  响应优先级
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void NVIC_IT_Configuration(uint8_t IRQChannelx, uint8_t Priorityx, uint8_t SubPriorityx)
{
    NVIC_InitTypeDef NVIC_InitStructure;                                //中断初始化结构


		NVIC_InitStructure.NVIC_IRQChannel = IRQChannelx;                   //更新事件
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Priorityx;   //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriorityx;       //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //允许中断
    NVIC_Init(&NVIC_InitStructure);                                     //初始化
}

//DMAx的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:外设地址
//mar:存储器地址
//ndtr:数据传输量
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr)
{

	DMA_InitTypeDef  DMA_InitStructure;

	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
	{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能

	}else
	{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1时钟使能
	}
  DMA_DeInit(DMA_Streamx);

	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}//等待DMA可配置

  /* 配置 DMA Stream */
  DMA_InitStructure.DMA_Channel = chx;  //通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//存储器到外设模式
  DMA_InitStructure.DMA_BufferSize = ndtr;//数据传输量
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
  DMA_Init(DMA_Streamx, &DMA_InitStructure);//初始化DMA Stream
}

const float TEV[11]     = {0 , 504 , 999 , 1497, 2010, 2529, 3051, 3568, 4076, 4571, 4959};
const float TE[11]      = {0 , 100 , 200 , 300 , 400 , 500 , 600 , 700 , 800 , 900 , 980};
const float TotalT[6]   = {-50     , 0 , 50       , 100      , 200     , 300};
const float TotalTV[6]  = {0.803063, 1 , 1.193971 , 1.385055 , 1.75856 , 2.120515};

void SampleData(void)
{
    //局部变量
    u8 ChanelID = 0;
    u8 DataGet_i = 0;
    for(ChanelID = 0 ; ChanelID < ADC_CHANELCOUNT; ChanelID++)
    {
        for(DataGet_i = 0; DataGet_i < ADC_BufSize ; DataGet_i++)
        {
            sADC.RealValue[ChanelID][DataGet_i] = sADC.ConvertedValue[DataGet_i * ADC_CHANELCOUNT + ChanelID];
        }
        /***********************信号滤波处理*****************************/
        sADC.AverageValue[ChanelID] = OneDimensional_filter(sADC.RealValue[ChanelID], ADC_BufSize);//10个数取中间一部分数的平均值，算法有点问题，但不影响
    }
	//取4096后，转化成0-3v电压值，然后再转物理值
    sADC.CovValue[0][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[0], 0.0, 3.0, 0, 48.0);     //无
    sADC.CovValue[1][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[1], 0.0, 3.0, 0, 48.0) ; 		//无
    sADC.CovValue[2][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[2], 0.0, 3.0, 0, 3.0) ;   //ECU内部温度采集

    sADC.CovValue[3][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[3], 0.0, 3.0, 0, 1000) ;     //排温
    sADC.CovValue[4][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[4], 0.0, 3.3, 0, 6.0) ;     //总温基准
    sADC.CovValue[6][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[6], 0.0, 3.3, 0, 3.3) ;     //总温
	sADC.CovValue[7][sADC.Count_ADC] = ADC_convert(sADC.AverageValue[7], 0.5, 3.0, 0.5, 3.0) ; 		//燃油压力
	

	//同一采集通道，为了取25个数
    sADC.Count_ADC++;
    if(ADC_Buf2Size == sADC.Count_ADC)
    {
        sADC.Count_ADC = 0;
    }
    ///没用到
    sADC.V_EValve    = SumArray_float( sADC.CovValue[1] , 0 , ADC_Buf2Size) / ADC_Buf2Size;//没用到了
	if(sADC.V_EValve>25)
	{sADC.V_EValve=0;}
	else
	{sADC.V_EValve=1;}	
//		sADC.V_EValve		=	fabs(((sADC.V_EValve - 1.25f) * 141.0f) / 4.1f	*	1.05f * 10.0f-4.0f);
	//排温计算没用这里的，这里有问题，直接码值发给模型计算了，所以sADC.T4值不对，不要用
    sADC.T4             = SumArray_float( sADC.CovValue[3] , 0 , ADC_Buf2Size) / ADC_Buf2Size;//25个值再求平均值
    sADC.T4             = sADC.T4 > TEV[10] ? TEV[10]: sADC.T4;
    sADC.T4             = OneDimensional_interpolation(TEV , TE , sADC.T4 , 11);
	//同上，ecu温度没用到这里的计算值，模型自己计算了
    sADC.TempVol_ECU    = SumArray_float( sADC.CovValue[2] , 0 , ADC_Buf2Size) / ADC_Buf2Size;
    sADC.Temp_ECU       = ((sADC.TempVol_ECU - 0.76f) * 400.0f) + 5.0f;
	
	sADC.beiyong2				=SumArray_float( sADC.CovValue[4] , 0 , ADC_Buf2Size) / ADC_Buf2Size;
	sADC.T0_V			=	SumArray_float( sADC.CovValue[6] , 0 , ADC_Buf2Size) / ADC_Buf2Size;
//		sADC.T0			=	sADC.T0  * 2.0f / 0.133f * 10.0f;
	if((sADC.beiyong2-sADC.T0_V)<=0.1)
	{sADC.beiyong1			=9999;}
	else
	{sADC.beiyong1			=sADC.T0_V * 1000/(sADC.beiyong2-sADC.T0_V);}///计算电阻值，1000表示1k电阻
	float temp;
	temp = 0.2604*sADC.beiyong1;
	sADC.T0			=	0.25506*sADC.beiyong1-254.987696+80;//pt1000，温度加了80
	//没用到
	sADC.Vol_Power			=	SumArray_float( sADC.CovValue[0] , 0 , ADC_Buf2Size) / ADC_Buf2Size;
//		sADC.Vol_Power			=	((sADC.Vol_Power - 1.25f) * 141.0f) / 4.1f	*	1.05f;
	sADC.POil						= SumArray_float( sADC.CovValue[7] , 0 , ADC_Buf2Size) / ADC_Buf2Size;
}
void SampleSwitch(void)
{
//开关量采集：0为输出
    uFB.b.zdcf = SpareIOFeedback2;//主油反馈
    uFB.b.fdcf = EblastFeedback;//辐油反馈
    uFB.b.dcfs = ValveEnableFeedback;//任一路阀门报警
    uFB.b.dhq  = FireEnableFeedback;//点火器状态报警
	uFB.b.yqf  = BleedAirFeedback;//引气阀反馈
}

/*********************************************************************************
** 函数名称：TIM_InitConfig
** 编写者  ：崔雷
** 参考资料：无
** 函数功能：定时器初始化
** 输入参数：TIMx: where x can be  1 to 14 to select the TIM peripheral.
             period    ——  定时器周期	  0x0000 ~ 0xFFFF
			   								   周期为period * （prescaler/168）us
			       prescaler ——  预分频       0x0000 ~ 0xFFFF
			                                  设置预分频器分频系数prescaler，
											                  即APB2=168M, TIM_CLK=（168/prescaler）MHz
											                  即每一次计数（prescaler/168）us
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void TIM_InitConfig(TIM_TypeDef* TIMx, uint32_t period, uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	if(TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM6)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM7)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);		//开启计数器时钟
	}
	else if(TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);		//开启计数器时钟
	}

	TIM_TimeBaseStructure.TIM_Period = period - 1;                   //定时器周期
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler - 1;             //定时器分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;					 //时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      //向上计数模式

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);                  //初始化定时器
}


/*********************************************************************************
** 函数名称：Tim7_Init
** 编写者  ：FY
** 参考资料：无
** 函数功能：TIM3 2ms定时初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitTIM7(void)
{
	TIM_InitConfig(TIM7, 2000, 84);
	NVIC_IT_Configuration(TIM7_IRQn, 0, 3);
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM7, ENABLE);

}
/*********************************************************************************
** 函数名称：Tim2_Init
** 编写者  ：FY
** 参考资料：无
** 函数功能：TIM2 1ms定时初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitTIM2(void)
{
	TIM_InitConfig(TIM2, 10, 84);
	NVIC_IT_Configuration(TIM2_IRQn, 0, 0);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);

}

/*********************************************************************************
** 函数名称: InitIC1
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 转速采集
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
**          对应关系IC1 —— PE9 —— TIM1 CH1
*********************************************************************************/
void InitIC1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);          //TIM1时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);         //使能PORTc时钟

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);       //PE9复用位定时器1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                     //GPIOE9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                  //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;            //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                //下拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);                        //初始化PE9

    TIM_ICInitTypeDef  TIM_ICInitStructure;
    //初始化TIMx输入捕获参数
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;                     //通道选择
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;          //边沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;      //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;               //配置输入分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;                           //配置输入滤波器
    TIM_ICInit(TIM1, &TIM_ICInitStructure);



	TIM_InitConfig(TIM1, 0xFFFF, 1);
	NVIC_IT_Configuration(TIM1_CC_IRQn, 0, 1);
	NVIC_IT_Configuration(TIM1_UP_TIM10_IRQn, 0, 1);
	TIM_ClearFlag(TIM1, TIM_FLAG_CC1 | TIM_FLAG_Update);
	TIM_ITConfig(TIM1, TIM_IT_CC1 | TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

/*********************************************************************************
** 函数名称: InitIC2
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 转速采集
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
**          对应关系IC2 —— PC7 —— TIM3 CH2
*********************************************************************************/
void InitIC2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);          //TIM3时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);         //使能PORTc时钟

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);       //复用位定时器1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                     //GPIOC7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                  //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;            //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                //下拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);                        //初始化PC7

    TIM_ICInitTypeDef  TIM_ICInitStructure;
    //初始化TIMx输入捕获参数
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                     //通道选择
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;          //边沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;      //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;               //配置输入分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;                           //配置输入滤波器
    TIM_ICInit(TIM3, &TIM_ICInitStructure);



	TIM_InitConfig(TIM3, 0xFFFF, 1);
	NVIC_IT_Configuration(TIM3_IRQn, 0, 3);
	TIM_ClearFlag(TIM3, TIM_FLAG_CC2 | TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_CC2 | TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void InitCAN(void)
{
	CAN_InitGPIO();
	NVIC_IT_Configuration(CAN1_RX0_IRQn, PREPRIO_CAN1, SUBPRIO_CAN1);
	CAN_InitConfig(CAN1 , 3);   // 42/(3*14) = 1Mbps
	CAN_InitFilterStdId(CAN1 , 0x0EB00000);

	NVIC_IT_Configuration(CAN2_RX0_IRQn, PREPRIO_CAN2, SUBPRIO_CAN2);
	CAN_InitConfig(CAN2 , 3);   // 42/(3*14) = 1Mbps
	CAN_InitFilterStdId(CAN2 , 0x0EB00000);
}
/*********************************************************************************
** 函数名称：CAN_GPIOInit
** 编写者  ：樊瑜
** 参考资料：无
** 函数功能：GPIO初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void CAN_InitGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_CAN1);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_CAN2);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}
/*********************************************************************************
** 函数名称：CAN_InitConfig
** 编写者  ：樊瑜
** 参考资料：无
** 函数功能：CAN_Config初始化
** 输入参数：CANx                -----    通道选择    CAN1
                                             CAN2

			 baudrateprescaler   -----	  分频设置    0 ~ 1024

			 波特率 = ((时钟频率/(baudrateprescaler*(1+6+7))
							 APB1的时钟频率为42MHz
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void CAN_InitConfig(CAN_TypeDef* CANx, uint16_t baudrateprescaler)
{
	CAN_InitTypeDef    CAN_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_InitStructure);					          //CAN单元初始化

	CAN_InitStructure.CAN_TTCM=DISABLE;
  	CAN_InitStructure.CAN_ABOM=ENABLE;
  	CAN_InitStructure.CAN_AWUM=ENABLE;
  	CAN_InitStructure.CAN_NART=DISABLE;
  	CAN_InitStructure.CAN_RFLM=DISABLE;
  	CAN_InitStructure.CAN_TXFP=DISABLE;
  	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
  	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq;
  	CAN_InitStructure.CAN_BS2=CAN_BS2_6tq;
  	CAN_InitStructure.CAN_Prescaler=baudrateprescaler;
  	CAN_Init(CANx, &CAN_InitStructure);
}
/*********************************************************************************
** 函数名称：CAN_FilterInit
** 编写者  ：樊瑜
** 参考资料：无
** 函数功能：CAN_FilterInit初始化
** 输入参数：无
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void CAN_InitFilterStdId(CAN_TypeDef* CANx, uint32_t filterid)
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	if (CANx == CAN1)
	{
	    CAN_FilterInitStructure.CAN_FilterNumber=0;						                       //为CAN1绑定过滤器组0
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;		               //过滤器被关联到FIFO0
	}
	else if (CANx == CAN2)
	{
	    CAN_FilterInitStructure.CAN_FilterNumber=14;							                //为CAN2绑定过滤器组1
	    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO1;		                //过滤器被关联到FIFO1
	}

	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;	                            //工作在标识符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	                        //过滤器位宽为单个32位。
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0E20;				    //要过滤的ID高位
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;   //要过滤的ID低位
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0x0FF0;			//筛选器高16位每位必须匹配
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0x0000;			//筛选器低16位每位必须匹配
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			                            //使能过滤器

	CAN_FilterInit(&CAN_FilterInitStructure);
	if (CANx == CAN1)
	{
		CAN_ITConfig(CAN1, CAN_IT_FMP0 , ENABLE);	               //FIFO0信息接收
	}
	else if (CANx == CAN2)
	{
		CAN_ITConfig(CAN2, CAN_IT_FMP1 , ENABLE);				   //FIFO1信息接收
	}
}

/*********************************************************************************
** 函数名称: SampleSpeed
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 转速采集
** 输入参数:
** 输出参数:
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备     注: 无
*********************************************************************************/

void SampleSpeed(void)
{
    u32 RccSum = 0;
    if(Timer.SpeedFMM.Value < 20)
    {
        return;
    }
    RotaSpeed1.Isr_Enable = 0;
    RotaSpeed2.Isr_Enable = 0;

    //测频法计算 20ms中断10次及以上才用测频法
    if(RotaSpeed1.Count_FMM >= ROTABUFSIZE)
    {
        RotaSpeed1.SignalFreq = ((float)RotaSpeed1.Count_FMM - 2.0f) * 168000000.0f /
            ((float)RotaSpeed1.TPeriodSum - (float)RotaSpeed1.TPeriodMin - (float)RotaSpeed1.TPeriodMax - 0.3f * ((float)RotaSpeed1.Count_FMM - 2.0f));
    }
    else
    {
        RccSum = 0;
        //测周法计算H
			
        for(int i = 0 ; i < ROTABUFSIZE ; i++)
        {
            RccSum += RotaSpeed1.FreGet[i].All;
        }
        RccSum -= Sum_MaxAndMin((u32*)RotaSpeed1.FreGet, ROTABUFSIZE);
    //    memset(RotaSpeed1.FreGet , 0 , ROTABUFSIZE);
        if(0 == RccSum)
        {
            RotaSpeed1.SignalFreq = 0;
        }
        else
        {
            RotaSpeed1.SignalFreq = (float)168000000 * (ROTABUFSIZE - 2) / (RccSum - 5);  //RccSum - 5 为时间补偿
        }
    }

    if(RotaSpeed2.Count_FMM >= ROTABUFSIZE)
    {
        RotaSpeed2.SignalFreq = ((float)RotaSpeed2.Count_FMM - 2.0f) * 84000000.0f /
            ((float)RotaSpeed2.TPeriodSum - (float)RotaSpeed2.TPeriodMin - (float)RotaSpeed2.TPeriodMax - 0.3f * ((float)RotaSpeed2.Count_FMM - 2.0f));
    }
    else
    {
        //测周法计算
        RccSum = 0;
        for(int i = 0 ; i < ROTABUFSIZE ; i++)
        {
            RccSum += RotaSpeed2.FreGet[i].All;
        }
        RccSum -= Sum_MaxAndMin((u32*)RotaSpeed2.FreGet, ROTABUFSIZE);
    //    memset(RotaSpeed1.FreGet , 0 , ROTABUFSIZE);
        if(0 == RccSum)
        {
            RotaSpeed2.SignalFreq = 0;
        }
        else
        {
            RotaSpeed2.SignalFreq = (float)84000000 * (ROTABUFSIZE - 2) / (float)(RccSum - 5);  //RccSum - 5 为时间补偿
        }
    }


    Timer.SpeedFMM.Value = 0;
    RotaSpeed1.Count_FMM = 0;
    RotaSpeed1.TPeriodSum = 0;
    RotaSpeed2.Count_FMM = 0;
    RotaSpeed2.TPeriodSum = 0;

    RotaSpeed1.PhyRealTime = RotaSpeed1.SignalFreq * 60.0f / (float)EngineGearNbr;
    RotaSpeed2.PhyRealTime = RotaSpeed2.SignalFreq * 60.0f / (float)StartMotorGearNbr;
    if(RotaSpeed1.PhyRealTime >= (RotaSpeed1.Phy + 100))
    {
        RotaSpeed1.Phy = RotaSpeed1.Phy;

    }
    RotaSpeed1.Phy = RotaSpeed1.Phy < RotaSpeed1.PhyRealTime ? RotaSpeed1.PhyRealTime : RotaSpeed1.Phy;

    RotaSpeed1.Phy = (u32)((float)RotaSpeed1.Phy * 0.8f + (float)RotaSpeed1.PhyRealTime * 0.2f);
    RotaSpeed2.Phy = (u32)((float)RotaSpeed2.Phy * 0.8f + (float)RotaSpeed2.PhyRealTime * 0.2f);
//    Engine.RotaSpeed_Current = RotaSpeed2.PhyRealTime;

    RotaSpeed1.Isr_Enable = 1;
    RotaSpeed2.Isr_Enable = 1;

}
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
	ch = ch;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART1->SR & 0X40)==0);//循环发送,直到发送完毕
	USART1->DR = (u8) ch;
	return ch;
}


