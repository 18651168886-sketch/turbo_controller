==================================================================
20190827增加uCosII系统：
1、注释掉stm32f4xx_it.c 中的函数“PendSV_Handler”






==================================================================
20190822试车：
1、开点火器20S后给副油9%
2、油门值由9%缓慢加至11%；
3、加电机占空比
4、判断转速到12000，油门值切到12%并供主油；






==================================================================
20190821开始移植：
主电磁阀	IO4O	IO4		PB5	GPIO_OUT	
					IO4F	PD7	GPIO_IN	
副电磁阀	IO5O	IO5		PB4	GPIO_OUT	
					IO5F	PB3	GPIO_IN	
电机		IO2O	IO2		PE12	GPIO_OUT	TIM1_CH3N
					IO2F	PE14	GPIO_IN	
点火器		IO1O	IO1		PE11	GPIO_OUT	
					IO1F	PE13	GPIO_IN	
油泵		MOTOR	PWM2_OUT	PD12	PWM	TIM4_CH1
			IO6_OUT	PD11	GPIO_OUT	

