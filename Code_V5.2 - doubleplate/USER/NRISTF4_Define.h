#ifndef __NRISTF4_DEFINE_H
#define __NRISTF4_DEFINE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "NRISTF4_Config.h"
#include "sys.h"
#include "CYS_110WP_3_Control.h"    /* Model's header file */
/* Exported types ------------------------------------------------------------*/
#define STMFlashAddrCfg              (0x0800E000)//0x080E0000
#define ACCFULLRANGE                 (84000)
#define SPI_FLASH_PageSize            256
#define SPI_FLASH_PerWritePageSize    256

#define EngineStoped	(0x04)          //停车
#define EnginePowerON	(0x00)          //上电
#define EngineStart  (0x01)          //起动
#define EngineRun	(0x02)          //运行
#define EngineManul     (0x03)          //手动

#define EngineGearCnt   (10)            //档位数量


#define W25X_WriteEnable		      0x06
#define W25X_SGWriteEnable		      0x50
#define W25X_WriteDisable		      0x04
#define W25X_ReadStatusReg1		      0x05
#define W25X_ReadStatusReg2	          0x35
#define W25X_WriteStatusReg		      0x01
#define W25X_ReadData			      0x03
#define W25X_FastReadData		      0x0B
#define W25X_FastReadDual		      0x3B
#define W25X_PageProgram		      0x02
#define W25X_BlockErase			      0xD8
#define W25X_SectorErase		      0x20
#define W25X_ChipErase			      0xC7
#define W25X_PowerDown			      0xB9
#define W25X_ReleasePowerDown	      0xAB
#define W25X_DeviceID			      0xAB
#define W25X_ManufactDeviceID   	  0x90
#define W25X_JedecDeviceID		      0x9F
#define WIP_Flag                      0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                    0xFF
typedef struct
{
    u8 Count_FlashErr;
}T_FLASH;
extern T_FLASH Flash;

//LED端口定义
#define LED1 PCout(1)


//驱动端口定义
#define Eblast_Power    PEout(7)        //副油电磁阀
#define EblastON        (0)
#define EblastOFF       (1)

#define SpareValve1_Power    PEout(8)        //主油电磁阀
#define SpareValve1ON        (0)
#define SpareValve1OFF       (1)

#define BleedAir_Power  PEout(10)     //引气阀
#define BleedAirON      (0)
#define BleedAirOFF     (1)

#define SpareValve2_Power    PEout(11)        //备用阀
#define SpareValve2ON        (0)
#define SpareValve2OFF       (1)

//#define StartMotorL_Power  PBout(6)     //低速
//#define StartMotorLON      (0)
//#define StartMotorLOFF     (1)

//#define StartMotorH_Power    PBout(7)        //高速
//#define StartMotorHON        (0)
//#define StartMotorHOFF       (1)

//#define OilPump_Power   PDout(11)        //油泵输出使能
//#define OilPumpON        (1)
//#define OilPumpOFF       (0)

//#define Motor_Power     PEout(12)        //电机控制
//#define MotorON         (1)
//#define MotorOFF        (0)

#define EValve_Work    PDout(11)        //未用
#define EValveEnableON        (1)
#define EValveEnableOFF       (0)

#define EValve_Power    PDout(12)        //未用
#define EValveON        (1)
#define EValveOFF       (0)

#define Firework_Power  PDout(13)     //点火器
#define FireworkON      (0)
#define FireworkOFF     (1)



//#define WuShua  PDout(5)     //电机
//#define WuShuaON      (0)
//#define WuShuaOFF     (1)

//#define EValveFeedback      PDin(7)        //主油反馈
#define SpareIOFeedback1		PEin(12)				//备用1
#define BleedAirFeedback    PEin(13)        //引气阀反馈
#define SpareIOFeedback2		PEin(14)				//主阀反馈
#define EblastFeedback      PEin(15)        //辐油反馈
#define ValveEnableFeedback       PDin(8)        //阀状态报警
#define FireEnableFeedback    PDin(9)        //点火器状态报警

#define SPI_FLASH_CS_LOW()            GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define SPI_FLASH_CS_HIGH()           GPIO_SetBits(GPIOB, GPIO_Pin_12)

/*******************中断优先级 抢占*******************/
#define PREPRIO_CAN1  1
#define PREPRIO_CAN2  1
#define PREPRIO_USART1 2
#define PREPRIO_USART2 2
#define PREPRIO_UART4 2
#define PREPRIO_DMAU2 3
#define PREPRIO_IC1 0
#define PREPRIO_IC2 0

/*******************中断优先级 响应*******************/
#define SUBPRIO_CAN1  0
#define SUBPRIO_CAN2  1
#define SUBPRIO_USART1 0
#define SUBPRIO_USART2 1
#define SUBPRIO_UART4 2
#define SUBPRIO_DMAU2 0
#define SUBPRIO_IC1 0
#define SUBPRIO_IC2 1

//#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define USART_TREC_LEN  		200  		//定义最大发送字节数 200
#define USART_RREC_LEN  		200  	//定义最大接收字节数 200
#define UsartBuf0           (0x55)
#define UsartBuf1           (0xAA)

#define COM_DATA        (0)     //数据通信
#define COM_CFG         (1)     //配置通信
/****************串口结构体*********************************/
typedef struct {
    u8 Flag_rx_suc ;                        //接收成功标志
    u8 Flag_tx_suc;						  	//数据发送成功标志位
    u8 Flag_tx_ready;					    //数据发送准备标志
    u8 Count;							    //串口计数器
    u16 DataLen_rx;							    //数据长度 modbus专用
    u16 DataLen_tx;							    //数据长度 modbus专用
    u16 Count_rx;                           //接收字节计数
    u16 Count_tx;                           //发送字节计数
    u8 RX_BUF[USART_RREC_LEN];
    u8 TX_BUF[USART_TREC_LEN];
    u8 ComType;                 //通信类型
}MYUSART;
extern MYUSART ECU_Usart1;              //串口1定义
extern MYUSART ECU_Usart2;              //串口2定义
extern MYUSART UsartRcv1;              //接收专用 缓存1帧
extern MYUSART UsartRcv2; 
extern MYUSART ECU_Uart4;              //串口4定义
extern MYUSART UartRcv4; 

#define ADC_BufSize         (10)
#define ADC_Buf2Size        (25)
#define ADC_CHANELCOUNT     (8)//3
#define ADCDMABufSize       (ADC_CHANELCOUNT * ADC_BufSize)

typedef struct{
    __IO uint16_t ConvertedValue[ADCDMABufSize];
    float RealValue[ADC_CHANELCOUNT][ADC_BufSize];
    float AverageValue[ADC_CHANELCOUNT];         //滤波均值
    float CovValue[ADC_CHANELCOUNT][ADC_Buf2Size];             //AD经转换后的值

    float V_EValve;                //阀压 ADC2-------PA2——暂无
    float T4;                         //排温 ADC4-------PA4
    float TempVol_ECU;                //ECU温度 ADC16
    float Temp_ECU;
	float T0;									//总温 ADC8-------PB0
	float Vol_Power;									//电源电压 ADC3-------PA3——暂无
	float POil;                       //燃油压力 ADC9----PB1
	float beiyong1;
	float beiyong2;
	float T0_V;
    u8 Count_ADC;	          
}ADC_STRUCT;
extern ADC_STRUCT sADC;              //ADC 定义

typedef union
{
  struct
  {
     u8 zdcf:    1;                      /*!< bit0:             */
     u8 fdcf:    1;                      /*!< bit1:   辐油反馈        */
     u8 dcfs:      1;                      /*!< bit2: 阀状态报警，4个中任意一个报警                */
     u8 dhq:     1;                      /*!< bit3:    点火器状态报警               */
	 u8 yqf:     1;                      /*!< bit3:      引气阀反馈             */
    u8 _reserved:     4;                /*!< bit4-7:  24..31  Reserved                           */
  } b;                                   /*!< Structure used for bit  access                  */
  u8 All;                            /*!< Type      used for word access                  */
} FEEDBACK_UNION;
extern FEEDBACK_UNION uFB;             //反馈信号 定义

typedef struct
{
    u8 Flag_rx_suc ;           //接收成功标志
    u8 Flag_tx_ready ;         //发送就绪标志
    CanRxMsg RxMsg;     //用于接收结构体;
    CanTxMsg TxMsg;     //用于发送结构体;
}CAN_Struct;
extern CAN_Struct S_CAN1 , S_CAN2;

typedef struct
{
    u8 Enble;           //定时器使能标志
    u8 Flag;           //被控制量使能标志
    u16 Value;           //计时器值
}TIMERTYPE;
#define T_ResetInfoSave      (500)       //2ms * 500 = 1000ms 复位信息存储周期
typedef struct
{
    u16 wait2ms ;           //毫秒 最大为30
    u16 wait1s ;            //秒 最大为2520
    __IO u16 While;                           //用于防止While陷入死循环
    __IO u16 While_bak;                       //用于防止While陷入死循环(备用，用于与Timer.While可能发生冲突时使用)
    TIMERTYPE MainLoop;
    TIMERTYPE DataSaveLoop;
    TIMERTYPE tCAN1;
    TIMERTYPE tCAN2;
    TIMERTYPE tUsart1;
    TIMERTYPE tUsart1OutTime;
    TIMERTYPE SpeedFMM;
    TIMERTYPE ADCSample;
    TIMERTYPE ReSetInfo;
    TIMERTYPE IWDGFlag; //累加1S
    TIMERTYPE StartControl; //起动控制
    TIMERTYPE SDCard;     //SD存储定时器
    TIMERTYPE Common;       //通用定时器
		TIMERTYPE CfgWait;       //配置等待定时器

}TIMERSTRUCT;
extern TIMERSTRUCT Timer;
typedef struct
{
    u8 T0msFlag;
    u8 T4msFlag;
    u8 T10msFlag;
    u8 T50_6msFlag;     //周期为50ms，6ms时置位
}MAINLOOPCTLSTRUCT;
extern MAINLOOPCTLSTRUCT MainloopCtl;
typedef union
{
  struct
  {
    uint32_t FrameCnt:     12;                      /*!< bit:  0.. 11  Usart                   */
    uint32_t Instr:         6;                      /*!< bit: 12.. 17  CAN                   */
    uint32_t State:         3;                      /*!< bit:  4.. 4  Temp_Total                   */
    uint32_t RxID:          4;                      /*!< bit:  6.. 6  Temp_Exhaust                   */
    uint32_t TxID:          4;                      /*!< bit:  8.. 9  Usart                   */
    uint32_t _reserved:     3;                      /*!< bit:  24..31  Reserved                           */
  } b;                                   /*!< Structure used for bit  access                  */
  uint32_t All;                            /*!< Type      used for word access                  */
} ExtIdSTRUCT;
extern ExtIdSTRUCT ExtId;

typedef struct
{
    float Accelerator;           //油门值
    u32 RealTimeDataAddr;       //实时数据存储地址
    u32 RotaSpeed_Load;         //装订转速
    u32 RotaSpeed_Current;      //当前转速
    u8 Status;
    u8 StatusChangeFlag;
    u8 Instr;
    u8 Flag_EnableManualAcc;
    u8 ResetFlag;
	u8 GearNbr;					//读配置信息中的齿数
	u8 StartStep;                //新增
	u32 EValve;//新增主阀
}ENGINESTRUCT;
extern ENGINESTRUCT Engine;

typedef union
{
  struct
  {
    uint32_t FreL:     16;                      /*!< bit:  0.. 15  FreL                   */
    uint32_t FreH:     16;                      /*!< bit: 16.. 32  FreH                   */
  } bit;                                   /*!< Structure used for bit  access                  */
  uint32_t All;                            /*!< Type      used for word access                  */
} CCRTYPE;

#define ROTABUFSIZE     (10)

typedef struct
{
    CCRTYPE FreGet[ROTABUFSIZE];        //测周法
    u32 Count_FMM;                      //测频法
    u32 TPeriodMin;
    u32 TPeriodMax;
    u32 TPeriodSum;
    u32 RealTime;                       //实时转速 测周法
    float SignalFreq;                     //实时转速 测频法
    u32 Nc_RealTime;
    u32 PhyRealTime;
//    u32 PhyLast;
    u32 Phy;                            //物理转速
    u8 Isr_Enable;                      //中断计数使能标志
}ROTASPEEDSTRUCT;
extern ROTASPEEDSTRUCT RotaSpeed1;
extern ROTASPEEDSTRUCT RotaSpeed2;

typedef union
{
  struct
  {
    u8 IWDGRST:     1;                      /*!< bit:  0 看门狗复位                   */
    u8 SFTRST:      1;                      /*!< bit:  1 软件复位                   */
    u8 BORRST:      1;                      /*!< bit:  2 欠压复位                   */
    u8 PORRST:      1;                      /*!< bit:  3 上电/掉电复位                   */
    u8 PINRST:      1;                      /*!< bit:  4 NRST Pin复位                  */
    u8 _rsv:        3;
  } bit;                                   /*!< Structure used for bit  access                  */
  u8 All;                            /*!< Type      used for word access                  */
} RESETTYPE;


extern u8 CfgInfo[CfgInfoLen];
extern u8 AckInfo[AckInfoLen];
extern u8 sendAckdataflag;
extern u8 sendovertimeenable;

typedef struct
{
    u8 IWDGEnableFlag;
    RESETTYPE ResetStartus;
    u8 CfgStatus;
	u32 SoftVersion;
}ECUSTATUSTRUCT;
extern ECUSTATUSTRUCT ECUStatus;

typedef struct
{
    u8 EnableFlag;
    u16 T_Cycle;    //周期时长 *2ms
    u16 T_Open;     //开通时长 *2ms
    u16 T_Cnt;      //计数器
}IODriver;
extern IODriver Eblast;
extern IODriver Motor;
extern IODriver Firework;
extern IODriver EValve;
extern IODriver BleedAir;


typedef struct
{
    u8 FlagSaveAlarm;   //保存告警

}SDIOSTRUCT;
extern SDIOSTRUCT sSDIO;

extern u16 motorDuty;
extern u16 fireworkTime;
extern u16 fireT4;

extern EngineControl_Out pEngineControl_Out;
extern SaveData_Out pSaveData_Out;
extern SendData_Out pSendData_Out;


#endif
