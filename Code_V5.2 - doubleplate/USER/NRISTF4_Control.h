#ifndef __NRISTF4_CONTROL_H
#define __NRISTF4_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "NRISTF4_Config.h"
#include "sys.h"
#include "NRISTF4_Define.h"
#include "bsp.h"
/* Exported types ------------------------------------------------------------*/
#define ManualACCMax    (ACCFULLRANGE * 0.97)
#define ManualACCMin    (0)
typedef struct
{
    float Kp;
    float Ki;
    float AccMin;
    float AccMax;
    float RotaSeep_ErrorAllow;
}CONTROLPARA;
//extern CONTROLPARA sControlPara;
extern float Speed_D[EngineGearCnt];

void getControlParameter(u32 AimNc , u32 CurrentNc , CONTROLPARA * ConPara);
float PIDControler(float AccLast , u32 AimNc ,  u32 CurrentNc , CONTROLPARA ConPara);
void StartEngine(u8* EnginState , u8 Instr);
void ManualControl(u8* EngineState , u8 Instr , u8* EnableFlag);
void StopEngine(u8* EngineState , u8 Instr);
void ControlEngine(u8 EngineState);
void PWM_OilPump(float acc);
#endif
