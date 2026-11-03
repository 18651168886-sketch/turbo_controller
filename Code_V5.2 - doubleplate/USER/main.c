/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp.h"
#include "NRIST_Comm.h"
#include "NRISTF4_Control.h"
#include "CYS_110WP_3_Control.h"

//声明信号量
SEM sem;
//定义栿
OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];
OS_STK ML[TASK_ML_STK_SIZE];
OS_STK SD[TASK_SD_STK_SIZE];
OS_STK SR[TASK_SR_STK_SIZE];
OS_STK CL[TASK_CL_STK_SIZE];
OS_STK IN[TASK_IN_STK_SIZE];
OS_STK SDCARD[TASK_SDIO_STK_SIZE];

int main(void)
{
    
	BSP_Init();
    AllDataInit();
    ECU_110WP_C_Control_initialize();
    ResetRegCheck();
    FlashCheck();
    IWDG_Feed();
    OSInit();
    SemCreat();
    OSTaskCreateExt(Task_Main , (void *)0 , &startup_task_stk[STARTUP_TASK_STK_SIZE-1] , TASK_MAIN_PRIO , TASK_MAIN_PRIO , startup_task_stk , STARTUP_TASK_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
//  发动机控制任势
    OSTaskCreateExt(Task_Control , (void *)0 , &ML[TASK_ML_STK_SIZE-1] , TASK_CTL_PRIO , TASK_CTL_PRIO , ML , TASK_ML_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
//  数据采样任务
    OSTaskCreateExt(Task_DataSample , (void *)0 , &IN[TASK_IN_STK_SIZE-1] , TASK_SAMPLE_PRIO , TASK_SAMPLE_PRIO , IN , TASK_IN_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
//  数据通信任务
    OSTaskCreateExt(Task_DataCOM , (void *)0 , &SD[TASK_SD_STK_SIZE-1], TASK_COM_PRIO , TASK_COM_PRIO , SD , TASK_SD_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
//  复位数据存储任务
    OSTaskCreateExt(Task_ResetDataSave , (void *)0 , &SR[TASK_SR_STK_SIZE-1], TASK_RES_PRIO , TASK_RES_PRIO , SR , TASK_SR_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
//  SD卡存傿实时数据存储
    OSTaskCreateExt(Task_RTDataSave , (void *)0 , &SDCARD[TASK_SDIO_STK_SIZE-1], TASK_SDCARD_PRIO , TASK_SDCARD_PRIO , SDCARD , TASK_SDIO_STK_SIZE , (void *)0 , OS_TASK_OPT_STK_CHK);
    OSStart();
    return 0;
}
/*********************************************************************************
** 函数名称: SemCreat
** 编 写 者: fy
** 参考资料: 无
** 函数功能: 信号量创廿
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 见注量
** 修 改 人: hr
** 备    注: 无
*********************************************************************************/
void SemCreat(void)
{
    u8 perr = 0;
    u16 i = 0;
		sem.Control       = OSSemCreate(0);
		sem.DataSample    = OSSemCreate(0);
		sem.DataCOM       = OSSemCreate(0);
		sem.RTDataSave    = OSSemCreate(0);
    sem.MutexMCtl     = OSMutexCreate(MUTEX_MAIN_PRIO , &perr);
    while (perr != OS_ERR_NONE)
    {
        i++;
        sem.MutexMCtl = OSMutexCreate(MUTEX_MAIN_PRIO + i , &perr);
    }
}
/*********************************************************************************
** 函数名称: TaskStkChk
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 主任务，点灯
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 见注量
** 修 改 人: hr
** 备    注: 无
*********************************************************************************/
void TaskStkChk(void)
{

    OS_STK_DATA stkData = {0};
    OSTaskStkChk(TASK_MAIN_PRIO , &stkData);
    printf("TASK_MAIN_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
    OSTaskStkChk(TASK_CTL_PRIO , &stkData);
    printf("TASK_CTL_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
    OSTaskStkChk(TASK_COM_PRIO , &stkData);
    printf("TASK_COM_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
    OSTaskStkChk(TASK_SAMPLE_PRIO , &stkData);
    printf("TASK_SAMPLE_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
    OSTaskStkChk(TASK_RES_PRIO , &stkData);
    printf("TASK_RES_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
    OSTaskStkChk(TASK_SDCARD_PRIO , &stkData);
    printf("TASK_SDCARD_PRIO used/free : %d/%d , usage:%d%%\r\n" , stkData.OSUsed , stkData.OSFree , stkData.OSUsed * 100 /(stkData.OSFree + stkData.OSUsed));
}

/*********************************************************************************
** 函数名称: Task_Start
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 主任务，点灯
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 见注量
** 修 改 人: hr
** 备    注: 无
*********************************************************************************/
void Task_Main(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
//    u8 err = 0;
    OS_CPU_SR cpu_sr = 0;
    OS_ENTER_CRITICAL();    //进入临界匿无法被中断打断
    OS_EXIT_CRITICAL();    //退出临界区 无法被中断打断
    while (1)
    {
        IWDG_Feed();
        if(0 == ECU_Uart4.Flag_rx_suc && UartRcv4.Flag_rx_suc)
        {
            memcpy(ECU_Uart4.RX_BUF , UartRcv4.RX_BUF , UartRcv4.Count_rx);
            ECU_Uart4.Count_rx = UartRcv4.Count_rx;
            ECU_Uart4.ComType = UartRcv4.ComType;
            ECU_Uart4.Flag_rx_suc = UartRcv4.Flag_rx_suc;

            UartRcv4.Flag_rx_suc = 0;
        }
        if(0 == ECU_Usart2.Flag_rx_suc && UsartRcv2.Flag_rx_suc)
        {
            memcpy(ECU_Usart2.RX_BUF , UsartRcv2.RX_BUF , UsartRcv2.Count_rx);
            ECU_Usart2.Count_rx = UsartRcv2.Count_rx;
            ECU_Usart2.Flag_rx_suc = UsartRcv2.Flag_rx_suc;

            UsartRcv2.Flag_rx_suc = 0;
						ECU_Usart2.Flag_rx_suc= 0;
					  UsartRcv2.Count_rx = 0;
        }
//				if(0 == ECU_Usart1.Flag_rx_suc && UsartRcv1.Flag_rx_suc)
//        {
//            memcpy(ECU_Usart1.RX_BUF , UsartRcv1.RX_BUF , UsartRcv1.Count_rx);
//            ECU_Usart1.Count_rx = UsartRcv1.Count_rx;
//            ECU_Usart1.Flag_rx_suc = UsartRcv1.Flag_rx_suc;

//            UsartRcv1.Flag_rx_suc = 0;
//						ECU_Usart1.Flag_rx_suc= 0;
//						UsartRcv1.Count_rx = 0;
//        }
//				//配置指令解析
//        if(ECU_Usart1.Flag_rx_suc && COM_CFG == ECU_Usart1.ComType)
//				{
//					AnalizeCfgCom();
//					ECU_Usart1.Flag_rx_suc = 0;
//				}
				
				
        //一分钟或发动机状态大亿时开启看门狗
        if(!ECUStatus.IWDGEnableFlag && (Timer.IWDGFlag.Value >= 60 || Engine.Status > 0))
        {
            ECUStatus.IWDGEnableFlag = 1;
            Timer.IWDGFlag.Enble = 0;
//            InitWatchdog();
        }
        IWDG_Feed();
/*        if(ECU_Usart1.Flag_rx_suc)
        {
            OSMutexPend(sem.MutexMCtl , 0 , &err);  //解析时，需获取互斥量
            AnalyseCommander(ECU_Usart1.RX_BUF);
            ECU_Usart1.Flag_rx_suc = 0;
            OSMutexPost(sem.MutexMCtl);     //释放
        }
*/
//        if(ECU_Usart1.Flag_rx_suc && COM_CFG == ECU_Usart1.ComType && (0 == Engine.Status) && !ECUStatus.IWDGEnableFlag) //没开启看门狗才可配置
//        {

//            ECU_Usart1.Flag_rx_suc = 0;
//        }
//        TaskStkChk();     //检测栈使用情况
 
// 		TIM_OCSetDutyCycle(TIM4,TIM_Channel_1,Engine.Accelerator);
		OSTimeDlyHMSM(0 , 0 , 0 , 80);		//500

   }
}

/*********************************************************************************
** 函数名称: Task_Control
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 发动机控制
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void Task_Control(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
    u8 err = 0;
	u16 StartMotorSpeed;
	u8 flag_N= 0;
    while (1)
    {
        OSMutexPend(sem.MutexMCtl , 0 , &err);      //PEND ON MUTUAL EXCLUSION SEMAPHORE
        OSSemPend(sem.Control , 0 , &err);
		StartMotorSpeed=((UsartRcv1.RX_BUF[5]<<8) + UsartRcv1.RX_BUF[6])/StartMotorGearNbr;
		if(pEngineControl_Out.Motor_Open==0)
		{
			
			if(flag_N < 10)
			{
				flag_N++;
			}
			else
			{
				Engine.RotaSpeed_Current=RotaSpeed2.PhyRealTime;
				flag_N=10;
			}
			
		}
		else
		{
			flag_N=0;
			Engine.RotaSpeed_Current=StartMotorSpeed;
		}
/* Step the model */
		/*
			sADC.AverageValue[3]——T4
			sADC.AverageValue[0]——sADC.Vol_Power——没用到
			sADC.AverageValue[2]——Tecu
			sADC.AverageValue[1]——sADC.V_EValve——没用到
			uFB.b.dhq——点火器状态报警
			uFB.b.fdcf——辐油反馈
			uFB.b.dcfs——主油反馈
			uFB.b.yqf——引气阀反馈
		*/
		if(ECU_Uart4.Flag_rx_suc)  
		{
			ECU_110WP_C_Control_Run(&ECU_Uart4.Flag_rx_suc , ECU_Uart4.RX_BUF , &Engine.ResetFlag ,
			   ResetInfo.buf , CfgInfo, Engine.RotaSpeed_Current,sADC.AverageValue[3], sADC.Vol_Power,sADC.AverageValue[2] ,
			   (u8)uFB.b.dhq, uFB.b.zdcf,(u8)uFB.b.fdcf , (u8)uFB.b.dcfs ,
			  (u8)uFB.b.yqf, sADC.POil ,sADC.T0, &pEngineControl_Out, &pSaveData_Out,&pSendData_Out);
			ECU_Uart4.Flag_rx_suc = 0;
		}
		else
		{
			ECU_110WP_C_Control_Run(&ECU_Uart4.Flag_rx_suc , ECU_Uart4.RX_BUF , 
			  &Engine.ResetFlag , ResetInfo.buf , CfgInfo, Engine.RotaSpeed_Current,
			  sADC.AverageValue[3], sADC.Vol_Power, sADC.AverageValue[2] , (u8)uFB.b.dhq, uFB.b.zdcf,
			  (u8)uFB.b.fdcf , (u8)uFB.b.dcfs ,(u8)uFB.b.yqf, sADC.POil , sADC.T0, &pEngineControl_Out, &pSaveData_Out,
			  &pSendData_Out);
		}

    /*自动代码补丁START*/
		if(pEngineControl_Out.Flag_Reset_Enable)
		{
			NVIC_SystemReset();
		}
		
		Engine.Status = pEngineControl_Out.EngineState;
		Engine.Accelerator = pEngineControl_Out.Accelerator;

//		if(pEngineControl_Out.EValve_Enable)
//		{
//			EValve_Power = EValveON;
//		}		
//		else
//		{
//			EValve_Power = EValveOFF;
//		}
//		Engine.EValve= pEngineControl_Out.EValve_Open/pEngineControl_Out.EValve_Cycle*ACCFULLRANGE;
//		PWM_OilPump(42000);//开主油
		
		Firework.EnableFlag = pEngineControl_Out.SWO_Firework;
		Firework.T_Cycle = 1000;	//开点火器
		Firework.T_Open = 900;

		BleedAir.EnableFlag = pEngineControl_Out.SWO_BleedAir;
		BleedAir.T_Cycle = 20;	//开气路电磁阀
		BleedAir.T_Open = 20;

		Eblast.EnableFlag = pEngineControl_Out.Eblast_Enable;	//开副油
		Eblast.T_Cycle = pEngineControl_Out.Eblast_Cycle;
		Eblast.T_Open = pEngineControl_Out.Eblast_Open;

		EValve.EnableFlag = pEngineControl_Out.EValve_Enable;	//开主油
		EValve.T_Cycle = pEngineControl_Out.EValve_Cycle;
		EValve.T_Open = pEngineControl_Out.EValve_Open;
		
//		Motor.EnableFlag =  pEngineControl_Out.Motor_Enable;
//		Motor.T_Cycle = pEngineControl_Out.Motor_Cycle;
//		Motor.T_Open = pEngineControl_Out.Motor_Open;
//		if(pEngineControl_Out.Motor_Open==60)
//		{
//			StartMotorL_Power=StartMotorLON;
//			StartMotorH_Power=StartMotorHON;
//		}
//		else if(pEngineControl_Out.Motor_Open==100)
//		{
//			StartMotorH_Power=StartMotorHON;
//			StartMotorL_Power=StartMotorLON;
//		}
//		else
//		{
//			StartMotorH_Power=StartMotorHOFF;
//			StartMotorL_Power=StartMotorLOFF;
//		}

		
		
		
		/******************主副油路电磁阀时间差1/2周期******************/
		if(Eblast.EnableFlag && EValve.EnableFlag)
		{
				if(Eblast.T_Cnt >= (u16)(Eblast.T_Cycle / 2))
				{
					EValve.T_Cnt = Eblast.T_Cnt - (u16)(Eblast.T_Cycle / 2);
				}
				else
				{
					EValve.T_Cnt = Eblast.T_Cnt + (u16)(Eblast.T_Cycle / 2);
				}
		}

		OSMutexPost(sem.MutexMCtl);     //POST TO A MUTUAL EXCLUSION SEMAPHORE

		OSTimeDlyHMSM(0,0,0,18);

   }
}

/*********************************************************************************
** 函数名称: Task_DataSample
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 数据采集
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void Task_DataSample(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
    u8 err = 0;
    while (1)
    {
        OSMutexPend(sem.MutexMCtl , 0 , &err);      //PEND ON MUTUAL EXCLUSION SEMAPHORE
        OSSemPend(sem.DataSample , 0 , &err);

        SampleData();
        IWDG_Feed();
        SampleSwitch();
        IWDG_Feed();
        SampleSpeed();

        OSMutexPost(sem.MutexMCtl);     //POST TO A MUTUAL EXCLUSION SEMAPHORE
		OSTimeDlyHMSM(0,0,0,18);
   }
}

/*********************************************************************************
** 函数名称: Task_DataCOM
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 数据采集
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
u16 sendtime;
void Task_DataCOM(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
    u8 err = 0;
    while (1)
    {
        OSMutexPend(sem.MutexMCtl , 0 , &err);      //PEND ON MUTUAL EXCLUSION SEMAPHORE
        OSSemPend(sem.DataCOM , 0 , &err);

			//配置通信后暂停实时数据发送10s
			if(Timer.CfgWait.Value >= 180)//
			{
				Timer.CfgWait.Enble = 0;
				Timer.CfgWait.Value = 0;
				ECUStatus.CfgStatus = 0;
				sendAckdataflag = 1;
				sendovertimeenable = 0;//关闭超时重发
			}
			
			if(1 == ECUStatus.CfgStatus && 0 == sendAckdataflag && sendovertimeenable == 1)
			{
				if((Timer.While-sendtime) >= 1000)//超时1S重发一次
				{
					sendtime = Timer.While;
					sendAckdataflag = 1;					
				}
			}

			//接收到读配置或写配置指令时，返回一组配置数据
			if(1 == ECUStatus.CfgStatus && 1 == sendAckdataflag)//sendcfgdataflag
			{
				//delay_ms(50);
				sendackData();
				sendAckdataflag = 0;
				sendtime = Timer.While;
			}		
			//非配置模式下实时数据发送
			if(0 == ECUStatus.CfgStatus && 0 == Timer.CfgWait.Value)
			{
				sendovertimeenable = 0;//关闭超时重发
				sendData();
				sendbumpData();
				sendstartmotorData();
        UsartRcv1.Flag_rx_suc = 0;
				UsartRcv1.Count_rx = 0;
			}					
			OSMutexPost(sem.MutexMCtl);     //POST TO A MUTUAL EXCLUSION SEMAPHORE
			OSTimeDlyHMSM(0,0,0,18);
   }
}

/*********************************************************************************
** 函数名称: Task_ResetDataSave
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 复位数据存储
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void Task_ResetDataSave(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
    while (1)
    {

        if((Timer.ReSetInfo.Value > T_ResetInfoSave && (1 || EngineStart == Engine.Status || EngineRun == Engine.Status)) || Engine.StatusChangeFlag)
        {
            LED1 = !LED1;
            if(0 != ResetInfoSaveUncheck(ResetInfo , SPIFlash.CurrentWriteAddr , Engine))
            {
                IWDG_Feed();
                ResetInfo.saveCnt ++;
                ResetInfo.saveAddrFlag = (!ResetInfo.saveAddrFlag) & 0x01;
                Timer.ReSetInfo.Value = 0;
                Engine.StatusChangeFlag = 0;
            }
        }

		OSTimeDlyHMSM(0,0,0,2);

   }
}



/*********************************************************************************
** 函数名称: Task_RTDataSave
** 编 写 者: ZY
** 参考资料: 无
** 函数功能: 实时数据存储
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
u16 jj;
void Task_RTDataSave(void *p_arg)
{
    p_arg = p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
    u16 ii;
		InitSDIO();
    SD_FileInit();
    while (1)
    {
			ii=Timer.wait2ms;
		    if( 0 != Engine.Status)
			{
				SD_FileWrite();
			}
			
			OSTimeDlyHMSM(0,0,0,50);
			jj=Timer.wait2ms-ii;
			
   }
}

