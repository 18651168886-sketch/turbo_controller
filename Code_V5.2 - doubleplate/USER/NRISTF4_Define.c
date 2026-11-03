#include "NRISTF4_Define.h"

T_FLASH Flash;
MYUSART ECU_Usart1;              //串口1定义
MYUSART UsartRcv1;               //接收专用 缓存1帧
MYUSART ECU_Usart2;              //串口2定义
MYUSART UsartRcv2; 
MYUSART ECU_Uart4;
MYUSART UartRcv4; 
ADC_STRUCT sADC;              //ADC 定义
FEEDBACK_UNION uFB;             //反馈信号 定义
CAN_Struct S_CAN1 , S_CAN2;
TIMERSTRUCT Timer;
MAINLOOPCTLSTRUCT MainloopCtl;
ExtIdSTRUCT ExtId;
ENGINESTRUCT Engine;
ROTASPEEDSTRUCT RotaSpeed1;
ROTASPEEDSTRUCT RotaSpeed2;
ECUSTATUSTRUCT ECUStatus;
IODriver Eblast = {0};
IODriver Motor = {0};
IODriver Firework = {0};
IODriver EValve = {0};
IODriver BleedAir = {0};



u8 CfgInfo[CfgInfoLen] = {0};
u8 AckInfo[AckInfoLen] = {0};
u8 sendAckdataflag = 1;
u8 sendovertimeenable = 0;
SDIOSTRUCT sSDIO;

EngineControl_Out pEngineControl_Out;
SaveData_Out pSaveData_Out;
SendData_Out pSendData_Out;







