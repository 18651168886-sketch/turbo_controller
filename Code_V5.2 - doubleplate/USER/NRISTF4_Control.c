#include "NRISTF4_Control.h"

/*********************************************************************************
** 函数名称: StartEngine
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 发动机起动
** 输入参数:EnginState 发动机状态
** 输出参数:发动机状态
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
u16 motorDuty = 5;
u16 fireworkTime = 20;
u16 fireT4 = 70;

void StartEngine(u8* EngineState , u8 Instr)
{
//    static u8 StartStep = 0;       //需要处理一下
////1、上电状态收到起动指令
//    if(*EngineState == EnginePowerON && 0xFC == Instr)
//    {
//        //上电状态收到起动指令，则对起动变量进行初始化
//        StartStep = 0;
//        *EngineState = EngineStart;
//    }
////2、发动机状态不是起动则返回
//    if(*EngineState != EngineStart)
//    {
//        return;
//    }
////3、起动时序
//    switch(StartStep)
//    {
//        case 0:     //开点火器，开电机
//            Firework.EnableFlag = 1;
//            Firework.T_Cycle = 20;  //开点火器
//            Firework.T_Open = 20;
//            Motor.EnableFlag = 1;   //电机4V 28*3/20 = 4.2V
//            Motor.T_Cycle = 100;
//            Motor.T_Open = motorDuty;
//            StartStep = 1;
//            break;
//        case 1:     //有转速后开始计时
//            if (Engine.RotaSpeed_Current > 200)
//            {
//                Timer.StartControl.Enble = 1;
//                Timer.StartControl.Value = 0;
//                StartStep++;
//            }
//            break;
//        case 2:     //点火器加热后开始给油
//            if ((Timer.StartControl.Value * 2) > (fireworkTime * 1000 - 500) && (Timer.StartControl.Value * 2) < (fireworkTime * 1000) )
//            {
////                Engine.Accelerator = ACCFULLRANGE * 0.4;        //油门填充
//            }
//            else if ((Timer.StartControl.Value * 2) > (fireworkTime * 1000))    //开副油
//            {
//                Engine.Accelerator = ACCFULLRANGE * 0.09;        //2.1V输出
//                Eblast.EnableFlag = 1;  //开副油 5Hz 10%
//                Eblast.T_Cycle = 30;
//                Eblast.T_Open = 3;
//                Timer.StartControl.Enble = 1;
//                Timer.StartControl.Value = 0;
//                Timer.Common.Enble = 1;
//                Timer.Common.Value = 0;
//                StartStep++;
//            }
//            break;
//        case 3:     //油门值由9%缓慢加至11%；
//            if(Timer.StartControl.Value > 50)
//            {
//                Engine.Accelerator++;
//                Timer.StartControl.Value = 0;
//            }
//            if(Engine.Accelerator > (ACCFULLRANGE * 0.10))
//            {
//                Engine.Accelerator = ACCFULLRANGE * 0.10;
//                StartStep++;
//            }
//            break;
//        case 4:     //判断转速到12000，油门值切到12%并供主油；
//            if (Engine.RotaSpeed_Current > 4000)
//            {
////                EValve_Power = EValveON;
//                //开主油，占空比为10%
//                EValve.EnableFlag = 1;
//                EValve.T_Cycle = Eblast.T_Cycle;
///******************主副油路电磁阀时间差1/2周期******************/
//                if(Eblast.T_Cnt >= (u16)(Eblast.T_Cycle / 2))
//                {
//                    EValve.T_Cnt = Eblast.T_Cnt - (u16)(Eblast.T_Cycle / 2);
//                }
//                else
//                {
//                    EValve.T_Cnt = Eblast.T_Cnt + (u16)(Eblast.T_Cycle / 2);
//                }
//                EValve.T_Open = 3;

//                Engine.Accelerator = ACCFULLRANGE * 0.11;
//                Timer.StartControl.Enble = 1;
//                Timer.StartControl.Value = 0;
//                StartStep++;
//            }
//            break;
//        case 5:         //逐渐主油增加占空比至100%
////            EValve_Power = EValveON;
//            if(EValve.T_Open < EValve.T_Cycle && Timer.StartControl.Value > 50)
//            {
//                EValve.T_Open++;
//                EValve.T_Cnt = EValve.T_Cnt < EValve.T_Cycle ? (EValve.T_Cnt + (EValve.T_Open % 2)) : (EValve.T_Cycle + (EValve.T_Open % 2));
//                Timer.StartControl.Value = 0;
//            }
//            if (Engine.RotaSpeed_Current > 10000)
//            {
//                EValve_Power = EValveON;
//                Firework.EnableFlag = 0;    //关点火器
//                Eblast.EnableFlag = 0;      //关副油
////                Motor.EnableFlag = 0;       //关电机
//                Timer.StartControl.Enble = 1;
//                Timer.StartControl.Value = 0;
//                Timer.Common.Enble = 0;
//                Timer.Common.Value = 0;
////                *EngineState = EngineRun;
//                StartStep++;
//            }
//            break;
//        case 6:
//            if(Timer.StartControl.Value > 100)
//            {
//                if(EValve.T_Open < EValve.T_Cycle)        //主油占空比先增加至100%，补刀用
//                {
//                    EValve.T_Open++;
//                    EValve.T_Cnt = EValve.T_Cnt <= (EValve.T_Cycle - 1) ? (EValve.T_Cnt + (EValve.T_Open % 2)) : 0;
//                }
//                else
//                {
//                    Engine.Accelerator++;
//                }
//                Timer.StartControl.Value = 0;
//            }
//            if(Engine.Accelerator > (ACCFULLRANGE * 0.15))
//            {
//                Engine.Accelerator = ACCFULLRANGE * 0.15;
//                StartStep++;
//            }
//            break;
//        default:
//            break;
//    }
//     //加电机占空比
//    if(StartStep >= 5 && Engine.RotaSpeed_Current > 20000)
//    {
//        Motor.EnableFlag = 0;       //关电机
//    }

//    if (StartStep >= 3 && Timer.Common.Value > 50)       //待定
//    {
//        Motor.T_Open ++;
//        Timer.Common.Value = 0;
//        if (Motor.T_Open > Motor.T_Cycle)
//        {
//            Motor.T_Open = Motor.T_Cycle;
//            Timer.Common.Enble = 0;
//        }
//    }
////4、由“起动”向“闭环”状态改变
//    if(Engine.RotaSpeed_Current >= 32000)
//    {
////        *EngineState = EngineRun;
//    }
//    Engine.StartStep = StartStep;
}

/*********************************************************************************
** 函数名称: ManualControl
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 手动控制
** 输入参数:EnginState 发动机状态
** 输出参数:发动机状态
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
void ManualControl(u8* EngineState , u8 Instr , u8* EnableFlag)
{
    if(0xF1 != Instr && 0xF2 != Instr)
    {
        return;
    }
    else
    {
        *EngineState = EngineManul;
    }

    if(*EnableFlag)
    {
        if(0xF1 == Instr)
        {
            Engine.Accelerator += ACCFULLRANGE * 0.005;
        }
        if(0xF2 == Instr)
        {
            Engine.Accelerator -= ACCFULLRANGE * 0.005;
        }
        //手动加减 油门上下限
        Engine.Accelerator = Engine.Accelerator > ManualACCMax ? ManualACCMax : Engine.Accelerator;
        Engine.Accelerator = Engine.Accelerator < ManualACCMin ? ManualACCMin : Engine.Accelerator;
        *EnableFlag = 0;
    }
}

/*********************************************************************************
** 函数名称: StopEngine
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 停车控制
** 输入参数:EnginState 发动机状态
** 输出参数:发动机状态
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
void StopEngine(u8* EngineState , u8 Instr)
{
//    if(*EngineState != EngineStoped && Instr != 0xF0)
//    {
//        return;
//    }
//    Engine.Accelerator = 0;
//    *EngineState = EngineStoped;
//    Eblast_Power = EblastOFF;
//    Eblast.EnableFlag = 0;   //关辅电磁阀
//    EValve.EnableFlag = 0;   //关主电磁阀
//    EValve_Power = EValveOFF;
////    OilPump_Power = OilPumpOFF;
//    Firework_Power = FireworkOFF;
//    Motor.EnableFlag = 0;   //关电机
//    return;
}

/*********************************************************************************
** 函数名称: ControlEngine
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 停车控制
** 输入参数:EnginState 发动机状态
** 输出参数:发动机状态
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
float Speed_D[EngineGearCnt] = {52000 , 59000 , 63000 , 68000 , 71000 , 74000 , 78000 , 84000 , 86000 , 89000 };

void ControlEngine(u8 EngineState)
{
//    if(0x0D == (Engine.Instr & 0x0D))   //&& sADC.T4 >= 100
//    {
//        if(EngineGearCnt <= (Engine.Instr >> 4))    //防止溢出
//        {
//            return;
//        }
//        Engine.Status = EngineRun;
//        Engine.RotaSpeed_Load = Speed_D[Engine.Instr >> 4];
//    }
//    if(0x0A == (Engine.Instr & 0x0A))   // && sADC.T4 >= 100
//    {
//        Engine.Status = EngineRun;
//    }
//    if(0xFC == Engine.Instr)
//    {
//        Engine.RotaSpeed_Load = Speed_D[0];
//    }
//    if(EngineState != EngineRun)
//    {
//        return;
//    }
//    CONTROLPARA CloopPara;
//    getControlParameter(Engine.RotaSpeed_Load , Engine.RotaSpeed_Current , &CloopPara);
//    Engine.Accelerator = PIDControler(Engine.Accelerator , Engine.RotaSpeed_Load , Engine.RotaSpeed_Current , CloopPara);
}


/*********************************************************************************
** 函数名称: PWM_OilPump
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 油泵驱动函数
** 输入参数: 油门值
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
void PWM_OilPump(float acc)
{
    TIM_OCSetDutyCycle(TIM4 , TIM_Channel_1 , (u16)acc);
}

/*********************************************************************************
** 函数名称: getControlParameter
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 油泵驱动函数
** 输入参数: 油门值
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
#define TabLen      (10)
const float NcTab[TabLen] = {35079.4 , 39921.2 , 45330.6 , 50456.2 , 54833.6 , 60389.2 , 65205.2 , 70167.4 , 75146.8 , 80014.4};
const float KpTab[TabLen] = {0.0011  , 0.0012  , 0.0013  , 0.0017  , 0.0017  , 0.0021  , 0.0027  , 0.0035  , 0.0049  , 0.0058};
const float KiTab[TabLen] = {0.000222 , 0.000238 , 0.000266 , 0.000337 , 0.000329 , 0.000414 , 0.000539 , 0.000695 , 0.000984 , 0.0012};
void getControlParameter(u32 AimNc , u32 CurrentNc , CONTROLPARA * ConPara)
{
    ConPara->AccMin = ACCFULLRANGE * 0.14;
    ConPara->AccMax = ACCFULLRANGE * 0.7;
    ConPara->Kp = OneDimensional_interpolation(NcTab , KpTab , CurrentNc , TabLen);
    ConPara->Ki = OneDimensional_interpolation(NcTab , KiTab , CurrentNc , TabLen);
    ConPara->RotaSeep_ErrorAllow = 300;
}


/*********************************************************************************
** 函数名称: PIDControler
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: PID控制器
** 输入参数: 油门值
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
**
*********************************************************************************/
float PIDControler(float AccLast , u32 AimNc ,  u32 CurrentNc , CONTROLPARA ConPara)
{
    float RotaSpeedError = (float)AimNc - (float)CurrentNc;
    static float RotaSpeedErrorLast = 0;
    float PID_Value;
    const float PIDMin = ACCFULLRANGE * -0.0023;
    const float PIDMax = ACCFULLRANGE * 0.0023;
    if(abswp(RotaSpeedError) < ConPara.RotaSeep_ErrorAllow)
    {
        RotaSpeedErrorLast = RotaSpeedError;
        return AccLast;
    }
    PID_Value = ConPara.Kp * (RotaSpeedError - RotaSpeedErrorLast) + ConPara.Ki * RotaSpeedError;
    PID_Value = PID_Value > PIDMax ? PIDMax : PID_Value;
    PID_Value = PID_Value < PIDMin ? PIDMin : PID_Value;
    RotaSpeedErrorLast = RotaSpeedError;
    if(AccLast + PID_Value > ConPara.AccMax)
    {
        return ConPara.AccMax;
    }
    else if(AccLast + PID_Value < ConPara.AccMin)
    {
        return ConPara.AccMin;
    }
    return AccLast + PID_Value;
}

