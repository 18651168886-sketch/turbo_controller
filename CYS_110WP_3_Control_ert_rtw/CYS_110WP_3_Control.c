/*
 * File: CYS_110WP_3_Control.c
 *
 * Code generated for Simulink model 'CYS_110WP_3_Control'.
 *
 * Model version                  : 1.393
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Fri Apr 07 14:47:02 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CYS_110WP_3_Control.h"
#include "CYS_110WP_3_Control_private.h"

/* Named constants for Chart: '<S205>/StateTranslation' */
#define CYS_110WP_3_Con_IN_IdleAndAbove ((uint8_T)3U)
#define CYS_110WP_3_Cont_IN_BinWanStart ((uint8_T)2U)
#define CYS_110WP_3_Control_IN_AirStart ((uint8_T)1U)
#define CYS_110WP_3_Control_IN_Manual  ((uint8_T)4U)
#define CYS_110WP_3_Control_IN_Origin  ((uint8_T)5U)
#define CYS_110WP_3_Control_IN_Start   ((uint8_T)6U)
#define CYS_110WP_3_Control_IN_Stop    ((uint8_T)7U)

/* Block signals (auto storage) */
B_CYS_110WP_3_Control_T CYS_110WP_3_Control_B;

/* Block states (auto storage) */
DW_CYS_110WP_3_Control_T CYS_110WP_3_Control_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_CYS_110WP_3_Control_T CYS_110WP_3_Control_PrevZCX;

/* Real-time model */
RT_MODEL_CYS_110WP_3_Control_T CYS_110WP_3_Control_M_;
RT_MODEL_CYS_110WP_3_Control_T *const CYS_110WP_3_Control_M =
  &CYS_110WP_3_Control_M_;

/* Forward declaration for local functions */
static real32_T CYS_110WP_3_Control_interp1(const real32_T varargin_1[2], const
  real32_T varargin_2[2], real32_T varargin_3);

/* Lookup 1D UtilityLookUpEven_U16_real32_T */
void LookUpEven_U16_real32_T(uint16_T *pY, const uint16_T *pYData, real32_T u,
  real32_T valueLo, uint32_T iHi, real32_T uSpacing)
{
  if (u <= valueLo ) {
    (*pY) = (*pYData);
  } else {
    real32_T uAdjusted = u - valueLo;
    real32_T tmpIdxLeft = uAdjusted / uSpacing;
    uint32_T iLeft = (uint32_T)tmpIdxLeft;
    if ((tmpIdxLeft >= 4294967296.0f) || (iLeft >= iHi) ) {
      (*pY) = pYData[iHi];
    } else {
      {
        real_T lambda;

        {
          real32_T num = (real32_T)uAdjusted - ( iLeft * uSpacing );
          lambda = (real_T)num / (real_T)uSpacing;
        }

        {
          real_T yLeftCast;
          real_T yRghtCast;
          yLeftCast = (real_T)pYData[iLeft];
          yRghtCast = (real_T)pYData[((iLeft)+1)];
          yLeftCast += lambda * ( yRghtCast - yLeftCast );

          {
            real_T rtb_dbl_tmp;
            rtb_dbl_tmp = floor(yLeftCast);
            if (rtIsNaN(rtb_dbl_tmp) || rtIsInf(rtb_dbl_tmp)) {
              rtb_dbl_tmp = 0.0;
            } else {
              rtb_dbl_tmp = fmod(rtb_dbl_tmp, 65536.0);
            }

            (*pY) = rtb_dbl_tmp < 0.0 ? (uint16_T)(int16_T)-(int16_T)(uint16_T)
              -rtb_dbl_tmp : (uint16_T)rtb_dbl_tmp;
          }
        }
      }
    }
  }
}

/* Lookup 1D UtilityLookUpEven_real32_T_real32_T */
void LookUpEven_real32_T_real32_T(real32_T *pY, const real32_T *pYData, real32_T
  u, real32_T valueLo, uint32_T iHi, real32_T uSpacing)
{
  if (u <= valueLo ) {
    (*pY) = (*pYData);
  } else {
    real32_T uAdjusted = u - valueLo;
    real32_T tmpIdxLeft = uAdjusted / uSpacing;
    uint32_T iLeft = (uint32_T)tmpIdxLeft;
    if ((tmpIdxLeft >= 4294967296.0f) || (iLeft >= iHi) ) {
      (*pY) = pYData[iHi];
    } else {
      {
        real32_T lambda;

        {
          real32_T num = (real32_T)uAdjusted - ( iLeft * uSpacing );
          lambda = num / uSpacing;
        }

        {
          real32_T yLeftCast;
          real32_T yRghtCast;
          yLeftCast = pYData[iLeft];
          yRghtCast = pYData[((iLeft)+1)];
          yLeftCast += lambda * ( yRghtCast - yLeftCast );
          (*pY) = yLeftCast;
        }
      }
    }
  }
}

real32_T look1_iflf_binlcapw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T y;
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex;
    frac = 0.0F;
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (iLeft == maxIndex) {
    y = table[iLeft];
  } else {
    y = (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
  }

  return y;
}

/*
 * Output and update for action system:
 *    '<S72>/Switch Case Action Subsystem5'
 *    '<S72>/Switch Case Action Subsystem1'
 *    '<S72>/Switch Case Action Subsystem4'
 *    '<S72>/Switch Case Action Subsystem6'
 */
void CYS__SwitchCaseActionSubsystem5(uint16_T rtu_In1, uint8_T rtu_In1_k,
  uint8_T rtu_In1_g, uint16_T rtu_In1_f, uint16_T rtu_In1_d, uint16_T rtu_In1_o,
  uint16_T rtu_In1_b, uint16_T rtu_In1_h, uint8_T rtu_In1_e, uint8_T rtu_In1_p,
  uint8_T rtu_In1_bp, uint16_T *rty_Out1, uint16_T *rty_Out1_k, uint16_T
  *rty_Out1_g, uint16_T *rty_Out1_f, uint16_T *rty_Out1_d, uint16_T *rty_Out1_o,
  uint8_T *rty_Out2, uint8_T *rty_Out2_h, uint8_T *rty_Out2_e, uint8_T
  *rty_Out2_p, uint8_T *rty_Out2_b)
{
  /* Gain: '<S80>/Gain1' */
  *rty_Out1 = rtu_In1;

  /* Gain: '<S80>/Gain10' */
  *rty_Out2_p = rtu_In1_k;

  /* Gain: '<S80>/Gain11' */
  *rty_Out2_b = rtu_In1_g;

  /* Gain: '<S80>/Gain2' */
  *rty_Out1_k = rtu_In1_f;

  /* Gain: '<S80>/Gain3' */
  *rty_Out1_g = rtu_In1_d;

  /* Gain: '<S80>/Gain4' */
  *rty_Out1_f = rtu_In1_o;

  /* Gain: '<S80>/Gain5' */
  *rty_Out1_d = rtu_In1_b;

  /* Gain: '<S80>/Gain6' */
  *rty_Out1_o = rtu_In1_h;

  /* Gain: '<S80>/Gain7' */
  *rty_Out2 = rtu_In1_e;

  /* Gain: '<S80>/Gain8' */
  *rty_Out2_h = rtu_In1_p;

  /* Gain: '<S80>/Gain9' */
  *rty_Out2_e = rtu_In1_bp;
}

/*
 * Initial conditions for atomic system:
 *    '<S17>/Range'
 *    '<S10>/Range'
 *    '<S51>/Range1'
 *    '<S65>/Range'
 *    '<S83>/Range'
 *    '<S85>/Range'
 *    '<S86>/Range'
 *    '<S87>/Range'
 *    '<S12>/Range'
 *    '<S184>/Range'
 *    '<S187>/Range'
 */
void CYS_110WP_3_Control_Range_Init(B_Range_CYS_110WP_3_Control_T *localB)
{
  localB->Out = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S17>/Range'
 *    '<S10>/Range'
 *    '<S51>/Range1'
 *    '<S65>/Range'
 *    '<S83>/Range'
 *    '<S85>/Range'
 *    '<S86>/Range'
 *    '<S87>/Range'
 *    '<S12>/Range'
 *    '<S184>/Range'
 *    '<S187>/Range'
 */
void CYS_110WP_3_Control_Range(real32_T rtu_In, real32_T rtu_Max, real32_T
  rtu_Min, B_Range_CYS_110WP_3_Control_T *localB)
{
  /* Gateway: CLM/Start/Range */
  /* During: CLM/Start/Range */
  /* Entry Internal: CLM/Start/Range */
  /* Transition: '<S113>:5' */
  if (rtu_In <= rtu_Min) {
    /* Transition: '<S113>:8' */
    /* Transition: '<S113>:12' */
    localB->Out = rtu_Min;

    /* Transition: '<S113>:31' */
  } else {
    /* Transition: '<S113>:14' */
    localB->Out = rtu_In;
  }

  /* Transition: '<S113>:32' */
  if (localB->Out >= rtu_Max) {
    /* Transition: '<S113>:16' */
    /* Transition: '<S113>:18' */
    localB->Out = rtu_Max;

    /* Transition: '<S113>:28' */
  } else {
    /* Transition: '<S113>:21' */
  }

  /* Transition: '<S113>:26' */
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S53>/D9-Nr-T5r' */
static real32_T CYS_110WP_3_Control_interp1(const real32_T varargin_1[2], const
  real32_T varargin_2[2], real32_T varargin_3)
{
  real32_T Vq;
  int32_T exitg1;
  real32_T x_idx_0;
  real32_T x_idx_1;
  real32_T y_idx_0;
  real32_T y_idx_1;
  y_idx_0 = varargin_2[0];
  x_idx_0 = varargin_1[0];
  y_idx_1 = varargin_2[1];
  x_idx_1 = varargin_1[1];
  Vq = 0.0F;
  CYS_110WP_3_Control_B.k = 1;
  do {
    exitg1 = 0;
    if (CYS_110WP_3_Control_B.k < 3) {
      if (rtIsNaNF(varargin_1[CYS_110WP_3_Control_B.k - 1])) {
        exitg1 = 1;
      } else {
        CYS_110WP_3_Control_B.k++;
      }
    } else {
      if (varargin_1[1] < varargin_1[0]) {
        x_idx_0 = varargin_1[1];
        x_idx_1 = varargin_1[0];
        y_idx_0 = varargin_2[1];
        y_idx_1 = varargin_2[0];
      }

      if (rtIsNaNF(varargin_3)) {
        Vq = (rtNaNF);
      } else if (varargin_3 > x_idx_1) {
        Vq = (varargin_3 - x_idx_1) / (x_idx_1 - x_idx_0) * (y_idx_1 - y_idx_0)
          + y_idx_1;
      } else if (varargin_3 < x_idx_0) {
        Vq = (varargin_3 - x_idx_0) / (x_idx_1 - x_idx_0) * (y_idx_1 - y_idx_0)
          + y_idx_0;
      } else {
        CYS_110WP_3_Control_B.r = (varargin_3 - x_idx_0) / (x_idx_1 - x_idx_0);
        if (CYS_110WP_3_Control_B.r == 0.0F) {
          Vq = y_idx_0;
        } else if (CYS_110WP_3_Control_B.r == 1.0F) {
          Vq = y_idx_1;
        } else if (y_idx_0 == y_idx_1) {
          Vq = y_idx_0;
        } else {
          Vq = (1.0F - CYS_110WP_3_Control_B.r) * y_idx_0 +
            CYS_110WP_3_Control_B.r * y_idx_1;
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Vq;
}

/* Model step function */
void ECU_110WP_C_Control_Run(uint8_T *arg_Flag_rx_suc, uint8_T
  arg_MyUsart2_Rxdata[50], uint8_T *arg_Flag_ECUReset, uint8_T
  arg_ECUReset_Information[20], uint8_T arg_MySet_Rxdata[50], real32_T arg_Nc,
  real32_T arg_T4, real32_T arg_S_Vpower, real32_T arg_Tecu, uint8_T
  arg_SWI_Firework, uint8_T arg_SWI_EValve, uint8_T arg_SWI_Eblast, uint8_T
  arg_SWI_ValveErr, uint8_T arg_SWI_BleedAir, real32_T arg_POil, real32_T arg_T0,
  EngineControl_Out *arg_Controldata, SaveData_Out *arg_savedata, SendData_Out
  *arg_senddata)
{
  /* local block i/o variables */
  uint16_T rtb_LookupTableDynamic_o;
  uint16_T rtb_LookupTableDynamic2_k;
  uint16_T rtb_LookupTableDynamic1_p;
  uint16_T rtb_LookupTableDynamic_h;
  boolean_T guard4 = false;
  uint8_T rtb_TimeDelay2;
  uint8_T rtb_Switch_gc;
  boolean_T rtb_LogicalOperator_fe;
  boolean_T rtb_LogicalOperator_pb;
  uint8_T rtb_Flag_ECUReset_Clear;
  uint8_T rtb_DataTypeConversion4_f;
  uint8_T rtb_Compare_pr;
  int8_T rtPrevAction;
  int8_T rtAction;
  uint8_T rtb_ECUReset_Save;
  uint8_T rtb_Switch_it;
  uint16_T rtb_DataTypeConversion25;
  uint16_T rtb_DataTypeConversion26;
  uint16_T rtb_DataTypeConversion6;
  uint16_T rtb_DataTypeConversion7;
  uint16_T rtb_DataTypeConversion8;
  boolean_T rtb_u_i;
  uint8_T rtb_Flag_RunState;
  uint16_T rtb_Motor_Open_m;
  uint16_T rtb_Switch_o3;
  uint16_T Motor_Cycle_cf;
  uint16_T Motor_Open_h;
  uint16_T EValve_Open_f;
  uint16_T Eblast_Cycle_j2;
  UNUSED_PARAMETER(arg_Flag_ECUReset);
  UNUSED_PARAMETER(arg_ECUReset_Information);
  UNUSED_PARAMETER(arg_MySet_Rxdata);

  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
  /* RelationalOperator: '<S132>/指令确认' incorporates:
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   */
  rtb_u_i = (arg_MyUsart2_Rxdata[3] == arg_MyUsart2_Rxdata[2]);

  /* Switch: '<S135>/Switch' incorporates:
   *  Constant: '<S132>/WuZhiLing'
   *  Constant: '<S137>/Constant'
   *  Constant: '<S138>/Constant'
   *  Constant: '<S140>/Constant'
   *  Constant: '<S141>/Constant'
   *  Constant: '<S142>/Constant'
   *  Constant: '<S143>/Constant'
   *  Constant: '<S144>/Constant'
   *  Constant: '<S145>/Constant'
   *  Constant: '<S146>/Constant'
   *  Constant: '<S147>/Constant'
   *  Constant: '<S148>/Constant'
   *  Constant: '<S149>/Constant'
   *  Constant: '<S150>/Constant'
   *  Constant: '<S151>/Constant'
   *  Constant: '<S152>/Constant'
   *  Constant: '<S154>/Constant'
   *  Constant: '<S155>/Constant'
   *  DataTypeConversion: '<S156>/Extract Desired Bits'
   *  Gain: '<S132>/ECU重置'
   *  Gain: '<S132>/闭环'
   *  Gain: '<S132>/丙烷起动'
   *  Gain: '<S132>/紧急停车'
   *  Gain: '<S132>/空中起动'
   *  Gain: '<S132>/起动'
   *  Gain: '<S132>/设定点火器'
   *  Gain: '<S132>/设定起动电机'
   *  Gain: '<S132>/设定引气'
   *  Gain: '<S132>/设定油路副阀'
   *  Gain: '<S132>/设定油路主阀'
   *  Gain: '<S132>/设定油门'
   *  Gain: '<S132>/手动加'
   *  Gain: '<S132>/手动减'
   *  Gain: '<S132>/停车'
   *  Gain: '<S132>/自检'
   *  Inport: '<Root>/Flag_rx_suc'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   *  Logic: '<S132>/指令更新'
   *  Logic: '<S153>/档位+装订 '
   *  Logic: '<S153>/档位范围'
   *  RelationalOperator: '<S137>/Compare'
   *  RelationalOperator: '<S138>/Compare'
   *  RelationalOperator: '<S140>/Compare'
   *  RelationalOperator: '<S141>/Compare'
   *  RelationalOperator: '<S142>/Compare'
   *  RelationalOperator: '<S143>/Compare'
   *  RelationalOperator: '<S144>/Compare'
   *  RelationalOperator: '<S145>/Compare'
   *  RelationalOperator: '<S146>/Compare'
   *  RelationalOperator: '<S147>/Compare'
   *  RelationalOperator: '<S148>/Compare'
   *  RelationalOperator: '<S149>/Compare'
   *  RelationalOperator: '<S150>/Compare'
   *  RelationalOperator: '<S151>/Compare'
   *  RelationalOperator: '<S152>/Compare'
   *  RelationalOperator: '<S154>/Compare'
   *  RelationalOperator: '<S155>/Compare'
   *  RelationalOperator: '<S157>/Compare'
   *  S-Function (sfix_bitop): '<S153>/低8位 '
   *  Sum: '<S132>/Add'
   */
  if (rtb_u_i && (*arg_Flag_rx_suc != 0)) {
    rtb_Switch_gc = (uint8_T)((((((((((((((((((uint32_T)((arg_MyUsart2_Rxdata[2]
      == 243) || (((arg_MyUsart2_Rxdata[2] & 15) == 13) && ((int32_T)((uint32_T)
      arg_MyUsart2_Rxdata[2] >> 4) <= 12)) ? 192 : 0) << 10) + ((uint32_T)
      ((arg_MyUsart2_Rxdata[2] == 252) << 7) << 9)) + ((uint32_T)
      ((arg_MyUsart2_Rxdata[2] == 251) << 7) << 10)) + ((uint32_T)
      ((arg_MyUsart2_Rxdata[2] == 241) << 7) << 11)) + ((arg_MyUsart2_Rxdata[2] ==
      242) * 160U << 11)) + ((arg_MyUsart2_Rxdata[2] == 240) * 192U << 11)) +
      ((arg_MyUsart2_Rxdata[2] == 225) * 224U << 11)) + ((uint32_T)
      ((arg_MyUsart2_Rxdata[2] == 227) << 7) << 12)) + ((arg_MyUsart2_Rxdata[2] ==
      244) * 144U << 12)) + ((arg_MyUsart2_Rxdata[2] == 226) * 160U << 12)) +
      ((arg_MyUsart2_Rxdata[2] == 230) * 176U << 12)) + ((arg_MyUsart2_Rxdata[2]
      == 231) * 192U << 12)) + ((arg_MyUsart2_Rxdata[2] == 232) * 208U << 12)) +
      ((arg_MyUsart2_Rxdata[2] == 233) * 224U << 12)) + ((arg_MyUsart2_Rxdata[2]
      == 161) * 240U << 12)) + ((uint32_T)((arg_MyUsart2_Rxdata[2] == 250) << 7)
      << 13)) >> 16);
  } else {
    rtb_Switch_gc = 0U;
  }

  /* End of Switch: '<S135>/Switch' */

  /* Switch: '<S136>/Switch' incorporates:
   *  Delay: '<S132>/Delay'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   */
  if (rtb_u_i) {
    rtb_Switch_it = arg_MyUsart2_Rxdata[2];
  } else {
    rtb_Switch_it = CYS_110WP_3_Control_DW.Delay_DSTATE_l;
  }

  /* End of Switch: '<S136>/Switch' */

  /* Switch: '<S160>/Switch' incorporates:
   *  Constant: '<S133>/DiMianTingChe'
   *  Constant: '<S133>/DiMianTingChe1'
   *  Constant: '<S133>/QiDong'
   *  Constant: '<S133>/QiDong1'
   *  Constant: '<S133>/QiDongZhuangDing'
   *  Constant: '<S164>/Constant'
   *  Constant: '<S167>/Constant'
   *  Constant: '<S168>/Constant'
   *  Inport: '<Root>/Flag_rx_suc'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   *  Logic: '<S133>/Logical Operator1'
   *  Logic: '<S133>/Logical Operator2'
   *  Logic: '<S133>/Logical Operator3'
   *  Logic: '<S133>/Logical Operator4'
   *  RelationalOperator: '<S133>/Relational Operator2'
   *  RelationalOperator: '<S133>/Relational Operator3'
   *  RelationalOperator: '<S133>/Relational Operator4'
   *  RelationalOperator: '<S133>/Relational Operator5'
   *  RelationalOperator: '<S164>/Compare'
   *  RelationalOperator: '<S167>/Compare'
   *  RelationalOperator: '<S168>/Compare'
   *  S-Function (sfix_bitop): '<S162>/低4位 '
   *  Switch: '<S159>/Switch'
   *  Switch: '<S165>/Switch'
   *  Switch: '<S166>/Switch'
   *  UnitDelay: '<Root>/Time Delay2'
   */
  if (((16 == rtb_Switch_gc) || (rtb_Switch_gc == 1)) && (*arg_Flag_rx_suc != 0)
      && (CYS_110WP_3_Control_B.EngineState == 0)) {
    CYS_110WP_3_Control_B.Switch_g = 40000.0F;
  } else if (((rtb_Switch_gc == 6) || (rtb_Switch_gc == 15)) &&
             (*arg_Flag_rx_suc != 0)) {
    /* Switch: '<S159>/Switch' incorporates:
     *  Constant: '<S133>/TingCheZhuangDing'
     */
    CYS_110WP_3_Control_B.Switch_g = 0.0F;
  } else {
    if (arg_MyUsart2_Rxdata[2] == 243) {
      /* Switch: '<S166>/Switch' incorporates:
       *  Gain: '<S162>/乘以2'
       *  Gain: '<S162>/乘以256'
       *  Inport: '<Root>/MyUsart2_Rxdata'
       *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
       *  Sum: '<S162>/高字节前'
       *  Switch: '<S159>/Switch'
       */
      CYS_110WP_3_Control_B.Switch_g = (real32_T)((uint32_T)(int32_T)(real32_T)
        fmod((real32_T)(arg_MyUsart2_Rxdata[4] << 8), 4.2949673E+9F) +
        arg_MyUsart2_Rxdata[5]) * 2.0F;
    } else if ((arg_MyUsart2_Rxdata[2] & 15) >= 13) {
      /* Switch: '<S165>/Switch' incorporates:
       *  Constant: '<S162>/档位信息数组'
       *  DataTypeConversion: '<S169>/Extract Desired Bits'
       *  Inport: '<Root>/MyUsart2_Rxdata'
       *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
       *  Selector: '<S162>/档位信息1为起始位'
       *  Switch: '<S159>/Switch'
       *  Switch: '<S166>/Switch'
       */
      CYS_110WP_3_Control_B.Switch_g = CYS_110WP_3_Control_P.PF_Gear_Info
        [(int32_T)((uint32_T)arg_MyUsart2_Rxdata[2] >> 4) - 1];
    } else {
      /* Switch: '<S165>/Switch' incorporates:
       *  Constant: '<S162>/WuMuBiao'
       *  Switch: '<S159>/Switch'
       *  Switch: '<S166>/Switch'
       */
      CYS_110WP_3_Control_B.Switch_g = 0.0F;
    }

    /* Switch: '<S161>/Switch' incorporates:
     *  Constant: '<S133>/BiHuan'
     *  Constant: '<S133>/ZhuangDingShangXian'
     *  Constant: '<S133>/ZhuangDingXiaXian'
     *  Constant: '<S167>/Constant'
     *  Delay: '<S133>/MoRenZhuangDing'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     *  Logic: '<S133>/闭环指令判断 '
     *  RelationalOperator: '<S133>/Relational Operator1'
     *  RelationalOperator: '<S133>/Relational Operator6'
     *  RelationalOperator: '<S133>/Relational Operator7'
     *  RelationalOperator: '<S167>/Compare'
     *  S-Function (sfix_bitop): '<S162>/低4位 '
     *  Switch: '<S159>/Switch'
     *  Switch: '<S165>/Switch'
     *  Switch: '<S166>/Switch'
     */
    if (!((rtb_Switch_gc == 3) && (CYS_110WP_3_Control_B.Switch_g >= 40000.0F) &&
          (CYS_110WP_3_Control_B.Switch_g <= 61000.0F))) {
      CYS_110WP_3_Control_B.Switch_g =
        CYS_110WP_3_Control_DW.MoRenZhuangDing_DSTATE;
    }

    /* End of Switch: '<S161>/Switch' */
  }

  /* End of Switch: '<S160>/Switch' */

  /* Product: '<S134>/Product1' incorporates:
   *  Constant: '<S134>/Constant3'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   */
  CYS_110WP_3_Control_B.SumofElements1_e = (real32_T)arg_MyUsart2_Rxdata[9] *
    2.0F;

  /* Chart: '<S134>/H0_T0_计算' incorporates:
   *  DataTypeConversion: '<S134>/Data Type Conversion2'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   *  Lookup_n-D: '<S134>/Kp Lookup Table1'
   */
  CYS_110WP_3_Control_B.H_GPRS = look1_iflf_binlcapw(arg_MyUsart2_Rxdata[6],
    CYS_110WP_3_Control_ConstP.KpLookupTable1_bp01Data,
    CYS_110WP_3_Control_ConstP.KpLookupTable1_tableData, 1U);

  /* Switch: '<S172>/Switch' incorporates:
   *  DataTypeConversion: '<S170>/Data Type Conversion1'
   *  Inport: '<Root>/Flag_rx_suc'
   *  Product: '<S175>/Product2'
   *  UnitDelay: '<S134>/Time Delay1'
   */
  /* Gateway: COMMRead_ISM/CMMRead/T1t_P1t_Cal/H0_T0_计算 */
  /* During: COMMRead_ISM/CMMRead/T1t_P1t_Cal/H0_T0_计算 */
  /* Entry Internal: COMMRead_ISM/CMMRead/T1t_P1t_Cal/H0_T0_计算 */
  /* Transition: '<S171>:10' */
  /* Transition: '<S171>:28' */
  /* Transition: '<S171>:21' */
  /* Transition: '<S171>:19' */
  /* Transition: '<S171>:32' */
  /* Transition: '<S171>:31' */
  if (*arg_Flag_rx_suc != 0) {
    /* Product: '<S134>/Product5' incorporates:
     *  Constant: '<S134>/constant4'
     */
    CYS_110WP_3_Control_B.Product5_c = CYS_110WP_3_Control_B.H_GPRS / 1000.0F;

    /* RelationalOperator: '<S174>/Relational Operator' incorporates:
     *  Constant: '<S174>/Constant7'
     */
    rtb_u_i = (CYS_110WP_3_Control_B.Product5_c < 11.0F);

    /* Switch: '<S177>/Switch' incorporates:
     *  Constant: '<S174>/Constant11'
     *  Constant: '<S174>/Constant12'
     *  Constant: '<S174>/Constant5'
     *  Math: '<S174>/Math Function1'
     *  Product: '<S174>/Product1'
     *  Product: '<S174>/Product4'
     *  Product: '<S174>/Product5'
     *  Sum: '<S174>/Sum3'
     *
     * About '<S174>/Math Function1':
     *  Operator: exp
     */
    if (rtb_u_i) {
      /* Sum: '<S174>/Sum2' incorporates:
       *  Constant: '<S174>/Constant3'
       *  Constant: '<S174>/Constant4'
       *  Product: '<S174>/Product2'
       */
      CYS_110WP_3_Control_B.MathFunction1_g = 1.0 - 0.022577 *
        CYS_110WP_3_Control_B.Product5_c;

      /* Math: '<S174>/Math Function' incorporates:
       *  Constant: '<S174>/Constant6'
       */
      if (CYS_110WP_3_Control_B.MathFunction1_g < 0.0) {
        CYS_110WP_3_Control_B.MathFunction1_g = -rt_powd_snf
          (-CYS_110WP_3_Control_B.MathFunction1_g, 5.25588);
      } else {
        CYS_110WP_3_Control_B.MathFunction1_g = rt_powd_snf
          (CYS_110WP_3_Control_B.MathFunction1_g, 5.25588);
      }

      /* End of Math: '<S174>/Math Function' */
      CYS_110WP_3_Control_B.MathFunction1_g *= 101.32499694824219;
    } else {
      CYS_110WP_3_Control_B.MathFunction1_g = exp
        ((CYS_110WP_3_Control_B.Product5_c - 11.0) * -0.1576932) * 23.385;
    }

    /* End of Switch: '<S177>/Switch' */

    /* DataTypeConversion: '<S174>/Data Type Conversion1' */
    CYS_110WP_3_Control_B.KpLookupTable1 = (real32_T)
      CYS_110WP_3_Control_B.MathFunction1_g;

    /* Switch: '<S176>/Switch' incorporates:
     *  Constant: '<S174>/Constant1'
     *  Product: '<S174>/Product'
     *  Sum: '<S174>/Sum'
     *  Sum: '<S174>/Sum4'
     */
    if (rtb_u_i) {
      CYS_110WP_3_Control_B.MathFunction1_g = 288.14999389648438 -
        CYS_110WP_3_Control_B.Product5_c * 6.5;
    } else {
      CYS_110WP_3_Control_B.MathFunction1_g = 216.64999389648437;
    }

    /* End of Switch: '<S176>/Switch' */

    /* Product: '<S175>/Product4' incorporates:
     *  Constant: '<S175>/constant5'
     *  Constant: '<S175>/constant6'
     *  DataTypeConversion: '<S174>/Data Type Conversion5'
     *  Product: '<S175>/Product5'
     *  Sqrt: '<S175>/Sqrt'
     */
    CYS_110WP_3_Control_B.SumofElements1_er =
      CYS_110WP_3_Control_B.SumofElements1_e / (real32_T)sqrt((real32_T)
      CYS_110WP_3_Control_B.MathFunction1_g * 1.4F * 287.06F);

    /* Math: '<S175>/Math Function' */
    CYS_110WP_3_Control_B.SumofElements1_er *=
      CYS_110WP_3_Control_B.SumofElements1_er;

    /* Sum: '<S175>/Sum' incorporates:
     *  Constant: '<S175>/Constant1'
     *  Constant: '<S175>/Constant7'
     *  Product: '<S175>/Product1'
     */
    CYS_110WP_3_Control_B.MathFunction1_g = 0.2 *
      CYS_110WP_3_Control_B.SumofElements1_er + 1.0;

    /* Math: '<S175>/Math Function1' */
    if (CYS_110WP_3_Control_B.MathFunction1_g < 0.0) {
      CYS_110WP_3_Control_B.MathFunction1_g = -rt_powd_snf
        (-CYS_110WP_3_Control_B.MathFunction1_g, 3.4999999999999996);
    } else {
      CYS_110WP_3_Control_B.MathFunction1_g = rt_powd_snf
        (CYS_110WP_3_Control_B.MathFunction1_g, 3.4999999999999996);
    }

    /* End of Math: '<S175>/Math Function1' */
    CYS_110WP_3_Control_B.Switch_e = (real32_T)
      (CYS_110WP_3_Control_B.MathFunction1_g *
       CYS_110WP_3_Control_B.KpLookupTable1);
  } else {
    CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_DW.TimeDelay1_DSTATE;
  }

  /* End of Switch: '<S172>/Switch' */

  /* Update for Delay: '<S132>/Delay' */
  CYS_110WP_3_Control_DW.Delay_DSTATE_l = rtb_Switch_it;

  /* Update for Delay: '<S133>/MoRenZhuangDing' */
  CYS_110WP_3_Control_DW.MoRenZhuangDing_DSTATE = CYS_110WP_3_Control_B.Switch_g;

  /* Update for UnitDelay: '<S134>/Time Delay1' */
  CYS_110WP_3_Control_DW.TimeDelay1_DSTATE = CYS_110WP_3_Control_B.Switch_e;

  /* End of Outputs for SubSystem: '<S2>/CMMRead' */

  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* Switch: '<S191>/Switch' incorporates:
   *  Constant: '<S180>/Constant1'
   *  Constant: '<S180>/Constant3'
   *  Constant: '<S180>/N1r_idle1'
   *  RelationalOperator: '<S180>/Relational Operator4'
   *  UnitDelay: '<Root>/Time Delay2'
   */
  if (CYS_110WP_3_Control_B.EngineState == 2) {
    CYS_110WP_3_Control_B.SumofElements1_er = 10000.0F;
  } else {
    CYS_110WP_3_Control_B.SumofElements1_er = 0.0F;
  }

  /* End of Switch: '<S191>/Switch' */

  /* Chart: '<S190>/Xlim_Xdot_Judge' incorporates:
   *  Constant: '<S180>/Constant2'
   *  Constant: '<S180>/Constant4'
   *  Constant: '<S180>/Constant5'
   *  Constant: '<S180>/Constant6'
   *  Constant: '<S190>/Constant3'
   *  Inport: '<Root>/Nc'
   *  Product: '<S190>/Divide1'
   *  UnitDelay: '<S190>/Unit Delay'
   *  UnitDelay: '<S190>/Unit Delay1'
   */
  /* Gateway: COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Xlim_Xdot_Judge */
  /* During: COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Xlim_Xdot_Judge */
  /* Entry Internal: COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Xlim_Xdot_Judge */
  /* Transition: '<S194>:233' */
  if ((arg_Nc > 70000.0F) || (arg_Nc < CYS_110WP_3_Control_B.SumofElements1_er))
  {
    /* Transition: '<S194>:235' */
    /* Transition: '<S194>:242' */
    CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.UnitDelay_DSTATE;
    CYS_110WP_3_Control_B.X_Flag_Locking_p = CYS_110WP_3_Control_DW.true_b;
    CYS_110WP_3_Control_B.Xdot_Flag_Locking = CYS_110WP_3_Control_DW.false_l;
    CYS_110WP_3_Control_DW.CNT_X_p = 0U;

    /* Transition: '<S194>:241' */
    /* Transition: '<S194>:167' */
    /* Transition: '<S194>:210' */
    /* Transition: '<S194>:203' */
    /* Transition: '<S194>:204' */
    /* Transition: '<S194>:36' */
  } else {
    /* Transition: '<S194>:245' */
    if ((CYS_110WP_3_Control_B.X_Flag_Locking_p == CYS_110WP_3_Control_DW.true_b)
        && (arg_Nc <= 70000.0F) && (arg_Nc >=
         CYS_110WP_3_Control_B.SumofElements1_er)) {
      /* Transition: '<S194>:78' */
      /* Transition: '<S194>:147' */
      CYS_110WP_3_Control_DW.CNT_X_p++;
      if (CYS_110WP_3_Control_DW.CNT_X_p > 5U) {
        /* Transition: '<S194>:239' */
        /* Transition: '<S194>:236' */
        CYS_110WP_3_Control_B.X_Out_a = arg_Nc;
        CYS_110WP_3_Control_B.X_Flag_Locking_p = CYS_110WP_3_Control_DW.false_l;
        CYS_110WP_3_Control_B.Xdot_Flag_Locking = CYS_110WP_3_Control_DW.false_l;

        /* Transition: '<S194>:167' */
        /* Transition: '<S194>:210' */
        /* Transition: '<S194>:203' */
        /* Transition: '<S194>:204' */
        /* Transition: '<S194>:36' */
      } else {
        /* Transition: '<S194>:217' */
        CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.UnitDelay_DSTATE;
        CYS_110WP_3_Control_B.X_Flag_Locking_p = CYS_110WP_3_Control_DW.true_b;
        CYS_110WP_3_Control_B.Xdot_Flag_Locking = CYS_110WP_3_Control_DW.false_l;

        /* Transition: '<S194>:210' */
        /* Transition: '<S194>:203' */
        /* Transition: '<S194>:204' */
        /* Transition: '<S194>:36' */
      }
    } else {
      /* Transition: '<S194>:211' */
      if ((arg_Nc - CYS_110WP_3_Control_DW.UnitDelay1_DSTATE > 1200.0F) ||
          (arg_Nc - CYS_110WP_3_Control_DW.UnitDelay1_DSTATE < -1200.0F)) {
        /* Transition: '<S194>:43' */
        /* Transition: '<S194>:188' */
        CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.UnitDelay_DSTATE;
        CYS_110WP_3_Control_B.X_Flag_Locking_p = CYS_110WP_3_Control_DW.false_l;
        CYS_110WP_3_Control_B.Xdot_Flag_Locking = CYS_110WP_3_Control_DW.true_b;
        CYS_110WP_3_Control_DW.CNT_Xdot = 0U;

        /* Transition: '<S194>:203' */
        /* Transition: '<S194>:204' */
        /* Transition: '<S194>:36' */
      } else {
        /* Transition: '<S194>:191' */
        if ((CYS_110WP_3_Control_DW.true_b ==
             CYS_110WP_3_Control_B.Xdot_Flag_Locking) && (arg_Nc -
             CYS_110WP_3_Control_DW.UnitDelay1_DSTATE < 800.0F) && (arg_Nc -
             CYS_110WP_3_Control_DW.UnitDelay1_DSTATE > -800.0F)) {
          /* Transition: '<S194>:193' */
          /* Transition: '<S194>:199' */
          CYS_110WP_3_Control_DW.CNT_Xdot++;
          if (CYS_110WP_3_Control_DW.CNT_Xdot > 5.0F) {
            /* Transition: '<S194>:200' */
            /* Transition: '<S194>:201' */
            CYS_110WP_3_Control_B.X_Out_a = arg_Nc;
            CYS_110WP_3_Control_B.X_Flag_Locking_p =
              CYS_110WP_3_Control_DW.false_l;
            CYS_110WP_3_Control_B.Xdot_Flag_Locking =
              CYS_110WP_3_Control_DW.false_l;

            /* Transition: '<S194>:204' */
            /* Transition: '<S194>:36' */
          } else {
            /* Transition: '<S194>:202' */
            CYS_110WP_3_Control_B.X_Out_a =
              CYS_110WP_3_Control_DW.UnitDelay_DSTATE;
            CYS_110WP_3_Control_B.X_Flag_Locking_p =
              CYS_110WP_3_Control_DW.false_l;
            CYS_110WP_3_Control_B.Xdot_Flag_Locking =
              CYS_110WP_3_Control_DW.true_b;

            /* Transition: '<S194>:36' */
          }
        } else {
          /* Transition: '<S194>:207' */
          CYS_110WP_3_Control_B.X_Out_a = arg_Nc;
          CYS_110WP_3_Control_B.X_Flag_Locking_p =
            CYS_110WP_3_Control_DW.false_l;
          CYS_110WP_3_Control_B.Xdot_Flag_Locking =
            CYS_110WP_3_Control_DW.false_l;
          CYS_110WP_3_Control_DW.CNT_Xdot = 0U;
          CYS_110WP_3_Control_DW.CNT_X_p = 0U;
        }
      }
    }
  }

  /* End of Chart: '<S190>/Xlim_Xdot_Judge' */

  /* Sum: '<S190>/Sum3' incorporates:
   *  Constant: '<S190>/Constant6'
   *  Delay: '<S190>/Integer Delay1'
   *  Product: '<S190>/Product2'
   *  Product: '<S190>/Product3'
   *  Product: '<S192>/Divide'
   *  Product: '<S192>/Product'
   *  Product: '<S192>/Product1'
   *  Product: '<S193>/Divide'
   *  Product: '<S193>/Product'
   *  Product: '<S193>/Product1'
   *  Sum: '<S192>/Sum'
   *  Sum: '<S193>/Sum'
   */
  /* Transition: '<S194>:84' */
  CYS_110WP_3_Control_B.Product5_c = CYS_110WP_3_Control_B.X_Out_a *
    0.229885057F + CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE * 0.770114958F;

  /* Lookup_n-D: '<S183>/Bit2V' incorporates:
   *  Inport: '<Root>/POil'
   */
  CYS_110WP_3_Control_B.Sqrt = look1_iflf_binlcapw(arg_POil,
    CYS_110WP_3_Control_ConstP.pooled32,
    CYS_110WP_3_Control_ConstP.Bit2V_tableData, 1U);

  /* Lookup_n-D: '<S183>/POil_X_Y' */
  CYS_110WP_3_Control_B.Sqrt = look1_iflf_binlcapw(CYS_110WP_3_Control_B.Sqrt,
    CYS_110WP_3_Control_ConstP.POil_X_Y_bp01Data,
    CYS_110WP_3_Control_ConstP.POil_X_Y_tableData, 1U);

  /* Sum: '<S181>/Sum3' incorporates:
   *  Constant: '<S181>/Constant9'
   *  Delay: '<S181>/Integer Delay1'
   *  Product: '<S181>/Product2'
   *  Product: '<S181>/Product3'
   *  Product: '<S195>/Divide'
   *  Product: '<S195>/Product'
   *  Product: '<S195>/Product1'
   *  Product: '<S196>/Divide'
   *  Product: '<S196>/Product'
   *  Product: '<S196>/Product1'
   *  Sum: '<S195>/Sum'
   *  Sum: '<S196>/Sum'
   */
  CYS_110WP_3_Control_B.SumofElements1_er = CYS_110WP_3_Control_B.Sqrt *
    0.229885057F + CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_b * 0.770114958F;

  /* Lookup_n-D: '<S185>/T4_X1_Y1' incorporates:
   *  Inport: '<Root>/T4'
   */
  CYS_110WP_3_Control_B.KpLookupTable1 = look1_iflf_binlcapw(arg_T4,
    CYS_110WP_3_Control_ConstP.pooled32, CYS_110WP_3_Control_ConstP.pooled33, 1U);

  /* Lookup_n-D: '<S185>/T4_X2_Y2' */
  CYS_110WP_3_Control_B.KpLookupTable1 = look1_iflf_binlcapw
    (CYS_110WP_3_Control_B.KpLookupTable1,
     CYS_110WP_3_Control_ConstP.T4_X2_Y2_bp01Data,
     CYS_110WP_3_Control_ConstP.T4_X2_Y2_tableData, 1U);

  /* Lookup_n-D: '<S185>/T4_X3_Y3' */
  CYS_110WP_3_Control_B.T4_X3_Y3 = look1_iflf_binlcapw
    (CYS_110WP_3_Control_B.KpLookupTable1,
     CYS_110WP_3_Control_ConstP.T4_X3_Y3_bp01Data,
     CYS_110WP_3_Control_ConstP.T4_X3_Y3_tableData, 10U);

  /* Sum: '<S182>/Sum3' incorporates:
   *  Constant: '<S182>/Constant9'
   *  Delay: '<S182>/Integer Delay1'
   *  Product: '<S182>/Product2'
   *  Product: '<S182>/Product3'
   *  Product: '<S197>/Divide'
   *  Product: '<S197>/Product'
   *  Product: '<S197>/Product1'
   *  Product: '<S198>/Divide'
   *  Product: '<S198>/Product'
   *  Product: '<S198>/Product1'
   *  Sum: '<S197>/Sum'
   *  Sum: '<S198>/Sum'
   */
  CYS_110WP_3_Control_B.KpLookupTable1 = CYS_110WP_3_Control_B.T4_X3_Y3 *
    0.229885057F + CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_j * 0.770114958F;

  /* Chart: '<S184>/Range' incorporates:
   *  Constant: '<S184>/Constant5'
   *  Constant: '<S184>/Constant6'
   *  Constant: '<S184>/V25'
   *  Inport: '<Root>/T0'
   *  Sum: '<S184>/Sum of Elements'
   */
  CYS_110WP_3_Control_Range(arg_T0 - 80.0F, 175.0F, -70.0F,
    &CYS_110WP_3_Control_B.sf_Range_j0);

  /* Lookup_n-D: '<S186>/Bit2V' incorporates:
   *  Inport: '<Root>/Tecu'
   */
  CYS_110WP_3_Control_B.Sqrt = look1_iflf_binlcapw(arg_Tecu,
    CYS_110WP_3_Control_ConstP.pooled32, CYS_110WP_3_Control_ConstP.pooled33, 1U);

  /* Sum: '<S186>/Sum of Elements1' incorporates:
   *  Constant: '<S186>/ Avg_Slope'
   *  Constant: '<S186>/ Avg_Slope1'
   *  Constant: '<S186>/V25'
   *  Product: '<S186>/Divide'
   *  Sum: '<S186>/Sum of Elements'
   */
  CYS_110WP_3_Control_B.Sqrt = (CYS_110WP_3_Control_B.Sqrt - 0.76F) * 400.0F +
    25.0F;

  /* Sum: '<S188>/Sum3' incorporates:
   *  Constant: '<S188>/Constant6'
   *  Delay: '<S188>/Integer Delay1'
   *  Inport: '<Root>/Nc'
   *  Product: '<S188>/Product2'
   *  Product: '<S188>/Product3'
   *  Product: '<S201>/Divide'
   *  Product: '<S201>/Product'
   *  Product: '<S201>/Product1'
   *  Product: '<S202>/Divide'
   *  Product: '<S202>/Product'
   *  Product: '<S202>/Product1'
   *  Sum: '<S201>/Sum'
   *  Sum: '<S202>/Sum'
   */
  CYS_110WP_3_Control_B.T_S = arg_Nc * 0.229885057F +
    CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_h * 0.770114958F;

  /* Chart: '<S187>/Range' incorporates:
   *  Constant: '<S187>/Constant1'
   *  Constant: '<S187>/Constant2'
   *  Constant: '<S187>/Constant5'
   *  Constant: '<S187>/Constant6'
   *  Product: '<S187>/Divide'
   *  Product: '<S187>/Product'
   *  Sqrt: '<S187>/Sqrt'
   *  Sum: '<S187>/Add'
   */
  CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.T_S * (real32_T)sqrt(288.15F /
    (273.15F + CYS_110WP_3_Control_B.sf_Range_j0.Out)), 75000.0F, 0.0F,
    &CYS_110WP_3_Control_B.sf_Range_da);

  /* Chart: '<S189>/Xlim_Xdot_Judge' incorporates:
   *  Constant: '<S189>/Constant1'
   */
  /* Gateway: COMMRead_ISM/ISM/Subsystem2/Xlim_Xdot_Judge */
  /* During: COMMRead_ISM/ISM/Subsystem2/Xlim_Xdot_Judge */
  /* Entry Internal: COMMRead_ISM/ISM/Subsystem2/Xlim_Xdot_Judge */
  /* Transition: '<S203>:233' */
  if (CYS_110WP_3_Control_B.T4_X3_Y3 > 930.0F) {
    /* Transition: '<S203>:235' */
    /* Transition: '<S203>:242' */
    CYS_110WP_3_Control_B.X_Flag_Locking = CYS_110WP_3_Control_DW.true_n;
    CYS_110WP_3_Control_DW.CNT_X = 0U;

    /* Transition: '<S203>:241' */
    /* Transition: '<S203>:167' */
    /* Transition: '<S203>:36' */
  } else {
    /* Transition: '<S203>:245' */
    if ((CYS_110WP_3_Control_B.X_Flag_Locking == CYS_110WP_3_Control_DW.true_n) &&
        (CYS_110WP_3_Control_B.T4_X3_Y3 <= 930.0F)) {
      /* Transition: '<S203>:78' */
      /* Transition: '<S203>:147' */
      CYS_110WP_3_Control_DW.CNT_X++;
      if (CYS_110WP_3_Control_DW.CNT_X > 5U) {
        /* Update for UnitDelay: '<S189>/Unit Delay1' */
        /* Transition: '<S203>:239' */
        /* Transition: '<S203>:236' */
        CYS_110WP_3_Control_DW.UnitDelay1_DSTATE_e =
          CYS_110WP_3_Control_B.T4_X3_Y3;
        CYS_110WP_3_Control_B.X_Flag_Locking = CYS_110WP_3_Control_DW.false_c;

        /* Transition: '<S203>:167' */
        /* Transition: '<S203>:36' */
      } else {
        /* Transition: '<S203>:217' */
        CYS_110WP_3_Control_B.X_Flag_Locking = CYS_110WP_3_Control_DW.true_n;

        /* Transition: '<S203>:36' */
      }
    } else {
      /* Update for UnitDelay: '<S189>/Unit Delay1' */
      /* Transition: '<S203>:207' */
      CYS_110WP_3_Control_DW.UnitDelay1_DSTATE_e =
        CYS_110WP_3_Control_B.T4_X3_Y3;
      CYS_110WP_3_Control_B.X_Flag_Locking = CYS_110WP_3_Control_DW.false_c;
      CYS_110WP_3_Control_DW.CNT_X = 0U;
    }
  }

  /* End of Chart: '<S189>/Xlim_Xdot_Judge' */

  /* Update for Delay: '<S190>/Integer Delay1' */
  /* Transition: '<S203>:84' */
  CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE = CYS_110WP_3_Control_B.Product5_c;

  /* Update for UnitDelay: '<S190>/Unit Delay1' incorporates:
   *  Update for Inport: '<Root>/Nc'
   */
  CYS_110WP_3_Control_DW.UnitDelay1_DSTATE = arg_Nc;

  /* Update for UnitDelay: '<S190>/Unit Delay' */
  CYS_110WP_3_Control_DW.UnitDelay_DSTATE = CYS_110WP_3_Control_B.X_Out_a;

  /* Update for Delay: '<S181>/Integer Delay1' */
  CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_b =
    CYS_110WP_3_Control_B.SumofElements1_er;

  /* Update for Delay: '<S182>/Integer Delay1' */
  CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_j =
    CYS_110WP_3_Control_B.KpLookupTable1;

  /* Update for Delay: '<S188>/Integer Delay1' */
  CYS_110WP_3_Control_DW.IntegerDelay1_DSTATE_h = CYS_110WP_3_Control_B.T_S;

  /* End of Outputs for SubSystem: '<S2>/ISM' */

  /* Outputs for Atomic SubSystem: '<Root>/ESM' */
  /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
  /* Logic: '<S208>/Logical Operator' incorporates:
   *  Constant: '<S134>/Constant5'
   *  Constant: '<S134>/constant2'
   *  Constant: '<S218>/Constant'
   *  Constant: '<S219>/Constant'
   *  Constant: '<S220>/Constant'
   *  Constant: '<S221>/Constant'
   *  Constant: '<S222>/Constant'
   *  Inport: '<Root>/MyUsart2_Rxdata'
   *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
   *  Logic: '<S208>/Logical Operator1'
   *  Product: '<S134>/Product3'
   *  RelationalOperator: '<S218>/Compare'
   *  RelationalOperator: '<S219>/Compare'
   *  RelationalOperator: '<S220>/Compare'
   *  RelationalOperator: '<S221>/Compare'
   *  RelationalOperator: '<S222>/Compare'
   *  Sum: '<S134>/Sum 1'
   */
  rtb_u_i = ((CYS_110WP_3_Control_B.X_Flag_Locking ||
              (CYS_110WP_3_Control_B.KpLookupTable1 < 300.0F)) &&
             (CYS_110WP_3_Control_B.Product5_c < 40000.0F) &&
             (CYS_110WP_3_Control_B.SumofElements1_e > 90.0F) &&
             ((arg_MyUsart2_Rxdata[11] - 5) * 100 > 300) &&
             (CYS_110WP_3_Control_B.H_GPRS < 6000.0F));

  /* End of Outputs for SubSystem: '<S2>/CMMRead' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

  /* Outputs for Atomic SubSystem: '<S209>/LogicSelection3' */

  /* Logic: '<S209>/Logical Operator1' incorporates:
   *  Constant: '<S209>/Constant1'
   *  Constant: '<S209>/Constant13'
   *  Constant: '<S229>/Constant'
   *  Constant: '<S230>/Constant'
   *  RelationalOperator: '<S229>/Compare'
   *  RelationalOperator: '<S230>/Compare'
   */
  LogicSelF((rtb_Switch_gc == 6) || (rtb_Switch_gc == 15), false, true,
            &CYS_110WP_3_Control_B.LogicSelection3);

  /* End of Outputs for SubSystem: '<S209>/LogicSelection3' */

  /* Logic: '<S209>/Logical Operator' incorporates:
   *  Constant: '<S226>/Constant'
   *  Constant: '<S227>/Constant'
   *  RelationalOperator: '<S226>/Compare'
   *  RelationalOperator: '<S227>/Compare'
   *  UnitDelay: '<S204>/Time Delay8'
   */
  rtb_LogicalOperator_fe = (CYS_110WP_3_Control_B.LogicSelection3.Switch ||
    (CYS_110WP_3_Control_B.Flag_RunState_f == 4) ||
    (CYS_110WP_3_Control_B.Flag_RunState_f == 15));

  /* Logic: '<S210>/Logical Operator' incorporates:
   *  Constant: '<S231>/Constant'
   *  Constant: '<S232>/Constant'
   *  Constant: '<S233>/Constant'
   *  Constant: '<S234>/Constant'
   *  Constant: '<S235>/Constant'
   *  Constant: '<S236>/Constant'
   *  Constant: '<S237>/Constant'
   *  Constant: '<S238>/Constant'
   *  RelationalOperator: '<S231>/Compare'
   *  RelationalOperator: '<S232>/Compare'
   *  RelationalOperator: '<S233>/Compare'
   *  RelationalOperator: '<S234>/Compare'
   *  RelationalOperator: '<S235>/Compare'
   *  RelationalOperator: '<S236>/Compare'
   *  RelationalOperator: '<S237>/Compare'
   *  RelationalOperator: '<S238>/Compare'
   */
  rtb_LogicalOperator_pb = ((rtb_Switch_gc == 4) || (rtb_Switch_gc == 5) ||
    (rtb_Switch_gc == 8) || (rtb_Switch_gc == 10) || (rtb_Switch_gc == 11) ||
    (rtb_Switch_gc == 12) || (rtb_Switch_gc == 13) || (rtb_Switch_gc == 14));

  /* Outputs for Atomic SubSystem: '<S4>/StateTransition' */
  /* Chart: '<S205>/StateTranslation' incorporates:
   *  Constant: '<S207>/Constant4'
   *  Constant: '<S211>/Constant'
   *  Constant: '<S212>/Constant'
   *  Constant: '<S213>/Constant'
   *  Constant: '<S214>/Constant'
   *  Constant: '<S216>/Constant'
   *  Constant: '<S217>/Constant'
   *  Constant: '<S223>/Constant'
   *  Constant: '<S225>/Constant'
   *  Logic: '<S207>/Logical Operator1'
   *  Logic: '<S208>/Logical Operator2'
   *  RelationalOperator: '<S207>/Relational Operator1'
   *  RelationalOperator: '<S211>/Compare'
   *  RelationalOperator: '<S212>/Compare'
   *  RelationalOperator: '<S213>/Compare'
   *  RelationalOperator: '<S214>/Compare'
   *  RelationalOperator: '<S216>/Compare'
   *  RelationalOperator: '<S217>/Compare'
   *  RelationalOperator: '<S223>/Compare'
   *  RelationalOperator: '<S225>/Compare'
   *  UnitDelay: '<S204>/Time Delay1'
   *  UnitDelay: '<S204>/Time Delay2'
   *  UnitDelay: '<S204>/Time Delay3'
   *  UnitDelay: '<S204>/Time Delay4'
   */
  /* Gateway: ESM/StateTransition/StateTranslation */
  /* During: ESM/StateTransition/StateTranslation */
  if (CYS_110WP_3_Control_DW.is_active_c2_CYS_110WP_3_Contro == 0U) {
    /* Entry: ESM/StateTransition/StateTranslation */
    CYS_110WP_3_Control_DW.is_active_c2_CYS_110WP_3_Contro = 1U;

    /* Entry Internal: ESM/StateTransition/StateTranslation */
    /* Transition: '<S239>:4' */
    CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
      CYS_110WP_3_Control_IN_Origin;

    /* Entry 'Origin': '<S239>:1' */
    CYS_110WP_3_Control_B.EngineState = 0U;
  } else {
    switch (CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control) {
     case CYS_110WP_3_Control_IN_AirStart:
      /* During 'AirStart': '<S239>:70' */
      if (CYS_110WP_3_Control_B.Flag_RunState == 2) {
        /* Transition: '<S239>:72' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Con_IN_IdleAndAbove;

        /* Entry 'IdleAndAbove': '<S239>:8' */
        CYS_110WP_3_Control_B.EngineState = 2U;
      } else {
        if (rtb_LogicalOperator_fe) {
          /* Transition: '<S239>:81' */
          /* Transition: '<S239>:14' */
          /* Transition: '<S239>:16' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Control_IN_Stop;

          /* Entry 'Stop': '<S239>:7' */
          CYS_110WP_3_Control_B.EngineState = 4U;
        }
      }
      break;

     case CYS_110WP_3_Cont_IN_BinWanStart:
      /* During 'BinWanStart': '<S239>:93' */
      if (rtb_LogicalOperator_pb) {
        /* Transition: '<S239>:95' */
        /* Transition: '<S239>:115' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Manual;

        /* Entry 'Manual': '<S239>:30' */
        CYS_110WP_3_Control_B.EngineState = 3U;
      } else if (CYS_110WP_3_Control_B.Flag_BWStartState == 2) {
        /* Transition: '<S239>:97' */
        /* Transition: '<S239>:107' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Con_IN_IdleAndAbove;

        /* Entry 'IdleAndAbove': '<S239>:8' */
        CYS_110WP_3_Control_B.EngineState = 2U;
      } else {
        /* Transition: '<S239>:105' */
        if (CYS_110WP_3_Control_B.LogicSelection3.Switch) {
          /* Transition: '<S239>:96' */
          /* Transition: '<S239>:113' */
          /* Transition: '<S239>:14' */
          /* Transition: '<S239>:16' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Control_IN_Stop;

          /* Entry 'Stop': '<S239>:7' */
          CYS_110WP_3_Control_B.EngineState = 4U;
        } else {
          /* Transition: '<S239>:134' */
          if (CYS_110WP_3_Control_B.Flag_BWStartState == 4) {
            /* Transition: '<S239>:135' */
            CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
              CYS_110WP_3_Control_IN_Origin;

            /* Entry 'Origin': '<S239>:1' */
            CYS_110WP_3_Control_B.EngineState = 0U;
          }
        }
      }
      break;

     case CYS_110WP_3_Con_IN_IdleAndAbove:
      /* During 'IdleAndAbove': '<S239>:8' */
      if (CYS_110WP_3_Control_B.LogicSelection3.Switch) {
        /* Transition: '<S239>:15' */
        /* Transition: '<S239>:16' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Stop;

        /* Entry 'Stop': '<S239>:7' */
        CYS_110WP_3_Control_B.EngineState = 4U;
      } else if (rtb_LogicalOperator_pb) {
        /* Transition: '<S239>:39' */
        /* Transition: '<S239>:40' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Manual;

        /* Entry 'Manual': '<S239>:30' */
        CYS_110WP_3_Control_B.EngineState = 3U;
      } else {
        if (rtb_u_i) {
          /* Transition: '<S239>:76' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Control_IN_AirStart;

          /* Entry 'AirStart': '<S239>:70' */
          CYS_110WP_3_Control_B.EngineState = 5U;
        }
      }
      break;

     case CYS_110WP_3_Control_IN_Manual:
      /* During 'Manual': '<S239>:30' */
      if (CYS_110WP_3_Control_B.LogicSelection3.Switch) {
        /* Transition: '<S239>:43' */
        /* Transition: '<S239>:44' */
        /* Transition: '<S239>:45' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Stop;

        /* Entry 'Stop': '<S239>:7' */
        CYS_110WP_3_Control_B.EngineState = 4U;
      } else if (rtb_u_i) {
        /* Transition: '<S239>:75' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_AirStart;

        /* Entry 'AirStart': '<S239>:70' */
        CYS_110WP_3_Control_B.EngineState = 5U;
      } else {
        if (rtb_Switch_gc == 3) {
          /* Transition: '<S239>:36' */
          /* Transition: '<S239>:107' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Con_IN_IdleAndAbove;

          /* Entry 'IdleAndAbove': '<S239>:8' */
          CYS_110WP_3_Control_B.EngineState = 2U;
        }
      }
      break;

     case CYS_110WP_3_Control_IN_Origin:
      /* During 'Origin': '<S239>:1' */
      if ((rtb_Switch_gc == 1) && (CYS_110WP_3_Control_B.Product5_c <= 13000.0F))
      {
        /* Transition: '<S239>:3' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Start;

        /* Entry 'Start': '<S239>:2' */
        CYS_110WP_3_Control_B.EngineState = 1U;
      } else {
        /* Transition: '<S239>:84' */
        /* Transition: '<S239>:86' */
        if (rtb_LogicalOperator_pb) {
          /* Transition: '<S239>:121' */
          /* Transition: '<S239>:82' */
          /* Transition: '<S239>:115' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Control_IN_Manual;

          /* Entry 'Manual': '<S239>:30' */
          CYS_110WP_3_Control_B.EngineState = 3U;
        } else {
          if (rtb_Switch_gc == 16) {
            /* Transition: '<S239>:94' */
            /* Transition: '<S239>:101' */
            CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
              CYS_110WP_3_Cont_IN_BinWanStart;

            /* Entry 'BinWanStart': '<S239>:93' */
            CYS_110WP_3_Control_B.EngineState = 6U;
          }
        }
      }
      break;

     case CYS_110WP_3_Control_IN_Start:
      /* During 'Start': '<S239>:2' */
      if (CYS_110WP_3_Control_B.Flag_RunState_f == 2) {
        /* Transition: '<S239>:9' */
        /* Transition: '<S239>:109' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Con_IN_IdleAndAbove;

        /* Entry 'IdleAndAbove': '<S239>:8' */
        CYS_110WP_3_Control_B.EngineState = 2U;
      } else if (rtb_LogicalOperator_fe) {
        /* Transition: '<S239>:6' */
        /* Transition: '<S239>:113' */
        /* Transition: '<S239>:14' */
        /* Transition: '<S239>:16' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Stop;

        /* Entry 'Stop': '<S239>:7' */
        CYS_110WP_3_Control_B.EngineState = 4U;
      } else {
        if (rtb_LogicalOperator_pb) {
          /* Transition: '<S239>:33' */
          CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
            CYS_110WP_3_Control_IN_Manual;

          /* Entry 'Manual': '<S239>:30' */
          CYS_110WP_3_Control_B.EngineState = 3U;
        }
      }
      break;

     default:
      /* During 'Stop': '<S239>:7' */
      if ((CYS_110WP_3_Control_B.Product5_c <= 20000.0F) &&
          (CYS_110WP_3_Control_B.StopFinish != 0)) {
        /* Transition: '<S239>:17' */
        CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control =
          CYS_110WP_3_Control_IN_Origin;

        /* Entry 'Origin': '<S239>:1' */
        CYS_110WP_3_Control_B.EngineState = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<S205>/StateTranslation' */
  /* End of Outputs for SubSystem: '<S4>/StateTransition' */
  /* End of Outputs for SubSystem: '<Root>/ESM' */

  /* Outputs for Atomic SubSystem: '<Root>/FPM' */
  /* Chart: '<S5>/Up_Hold' incorporates:
   *  Constant: '<S244>/Constant'
   *  Constant: '<S245>/Constant'
   *  Constant: '<S248>/Constant'
   *  Logic: '<S5>/Logical Operator3'
   *  RelationalOperator: '<S244>/Compare'
   *  RelationalOperator: '<S245>/Compare'
   *  RelationalOperator: '<S248>/Compare'
   */
  CYS_110WP_3_Control_Up_Hold((CYS_110WP_3_Control_B.EngineState == 1) ||
    (CYS_110WP_3_Control_B.EngineState == 2) ||
    (CYS_110WP_3_Control_B.EngineState == 3), &CYS_110WP_3_Control_B.sf_Up_Hold);

  /* DataTypeConversion: '<S5>/Data Type Conversion2' incorporates:
   *  Constant: '<S242>/Constant'
   *  Constant: '<S243>/Constant'
   *  Constant: '<S247>/Constant'
   *  Logic: '<S5>/Logical Operator1'
   *  Logic: '<S5>/Logical Operator2'
   *  RelationalOperator: '<S242>/Compare'
   *  RelationalOperator: '<S243>/Compare'
   *  RelationalOperator: '<S247>/Compare'
   */
  rtb_TimeDelay2 = (uint8_T)(CYS_110WP_3_Control_B.sf_Up_Hold.Out &&
    ((CYS_110WP_3_Control_B.EngineState == 0) ||
     (CYS_110WP_3_Control_B.EngineState == 4)) && (rtb_Switch_gc == 9));

  /* Chart: '<S240>/Hold_2000ms' */
  /* Gateway: FPM/Subsystem/Hold_2000ms */
  /* During: FPM/Subsystem/Hold_2000ms */
  /* Entry Internal: FPM/Subsystem/Hold_2000ms */
  /* Transition: '<S251>:1' */
  /* Transition: '<S251>:41' */
  CYS_110WP_3_Control_DW.Cnt_f = 0U;

  /* Outputs for Enabled and Triggered SubSystem: '<S240>/Flag_ECUReset_Reset' incorporates:
   *  EnablePort: '<S250>/Enable'
   *  TriggerPort: '<S250>/Trigger'
   */
  /* Transition: '<S251>:72' */
  if (CYS_110WP_3_Control_DW.Flag_ECUReset_Reset_MODE) {
    /* Disable for Outport: '<S250>/S_Flag_ECUReset_Clear' */
    CYS_110WP_3_Control_B.dthT02885 = 0U;
    CYS_110WP_3_Control_DW.Flag_ECUReset_Reset_MODE = false;
  }

  CYS_110WP_3_Control_PrevZCX.Flag_ECUReset_Reset_Trig_ZCE = 0U;

  /* End of Outputs for SubSystem: '<S240>/Flag_ECUReset_Reset' */

  /* DataTypeConversion: '<S240>/Data Type Conversion2' incorporates:
   *  Logic: '<S240>/Logical Operator1'
   *  RelationalOperator: '<S249>/FixPt Relational Operator'
   *  UnitDelay: '<S249>/Delay Input1'
   */
  rtb_Flag_ECUReset_Clear = (uint8_T)((CYS_110WP_3_Control_B.dthT02885 != 0) ||
    (CYS_110WP_3_Control_B.EngineState !=
     CYS_110WP_3_Control_DW.DelayInput1_DSTATE));

  /* Logic: '<S240>/Logical Operator2' */
  rtb_u_i = (CYS_110WP_3_Control_B.X_Flag_Locking_p ||
             CYS_110WP_3_Control_B.Xdot_Flag_Locking);

  /* Chart: '<S240>/Timmer_ms_Lock' incorporates:
   *  Constant: '<S240>/Constant4'
   *  Constant: '<S254>/Constant'
   *  Logic: '<S240>/Logical Operator4'
   *  RelationalOperator: '<S254>/Compare'
   */
  CYS_110WP_3_Cont_Timmer_ms_Lock((CYS_110WP_3_Control_B.EngineState == 2) &&
    rtb_u_i, 10000.0F, &CYS_110WP_3_Control_B.sf_Timmer_ms_Lock,
    &CYS_110WP_3_Control_DW.sf_Timmer_ms_Lock);

  /* Logic: '<S240>/Logical Operator5' incorporates:
   *  Logic: '<S240>/Logical Operator3'
   */
  rtb_u_i = ((!CYS_110WP_3_Control_B.sf_Timmer_ms_Lock.Out) && rtb_u_i);

  /* DataTypeConversion: '<S240>/Data Type Conversion4' */
  rtb_DataTypeConversion4_f = rtb_u_i;

  /* Chart: '<S240>/Hold_4000ms' incorporates:
   *  Constant: '<S240>/dth = T0-288.1'
   *  Constant: '<S255>/Constant'
   *  RelationalOperator: '<S255>/Compare'
   */
  /* Gateway: FPM/Subsystem/Hold_4000ms */
  /* During: FPM/Subsystem/Hold_4000ms */
  /* Entry Internal: FPM/Subsystem/Hold_4000ms */
  /* Transition: '<S252>:1' */
  if (CYS_110WP_3_Control_B.EngineState == 2) {
    /* Transition: '<S252>:4' */
    if (CYS_110WP_3_Control_DW.Cnt >= 10000U) {
      /* Transition: '<S252>:6' */
      /* Transition: '<S252>:13' */
      CYS_110WP_3_Control_DW.Cnt = 10000U;

      /* Transition: '<S252>:16' */
    } else {
      /* Transition: '<S252>:11' */
      CYS_110WP_3_Control_DW.Cnt++;
    }

    /* Transition: '<S252>:31' */
    if (CYS_110WP_3_Control_DW.Cnt > 200U) {
      /* Transition: '<S252>:34' */
      /* Transition: '<S252>:38' */
      rtb_ECUReset_Save = 1U;
      CYS_110WP_3_Control_DW.Cnt = 0U;

      /* Transition: '<S252>:39' */
    } else {
      /* Transition: '<S252>:40' */
      rtb_ECUReset_Save = 0U;
    }

    /* Transition: '<S252>:56' */
    /* Transition: '<S252>:69' */
  } else {
    /* Transition: '<S252>:41' */
    CYS_110WP_3_Control_DW.Cnt = 0U;
    rtb_ECUReset_Save = 0U;
  }

  /* End of Chart: '<S240>/Hold_4000ms' */

  /* RelationalOperator: '<S246>/Compare' incorporates:
   *  Constant: '<S246>/Constant'
   */
  /* Transition: '<S252>:72' */
  rtb_Compare_pr = (uint8_T)(CYS_110WP_3_Control_B.Product5_c > 62000.0F);

  /* Update for UnitDelay: '<S249>/Delay Input1' */
  CYS_110WP_3_Control_DW.DelayInput1_DSTATE = CYS_110WP_3_Control_B.EngineState;

  /* End of Outputs for SubSystem: '<Root>/FPM' */

  /* Outputs for Atomic SubSystem: '<Root>/CLM' */
  /* UnitDelay: '<S1>/Time Delay1' */
  CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_B.Origin_T4;

  /* UnitDelay: '<S1>/Time Delay4' */
  CYS_110WP_3_Control_B.T4_X3_Y3 = CYS_110WP_3_Control_B.Origin_POil;

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Constant: '<S10>/PG_CtrlMode_Start'
   *  Constant: '<S12>/PG_CtrlMode_Start'
   *  Constant: '<S13>/N1r_idle6'
   *  Constant: '<S15>/N1r_idle6'
   *  Constant: '<S16>/N1r_idle6'
   *  Constant: '<S17>/PG_CtrlMode_Start'
   *  Constant: '<S18>/N1r_idle6'
   */
  rtPrevAction = CYS_110WP_3_Control_DW.SwitchCase_ActiveSubsystem;
  rtAction = -1;
  switch (CYS_110WP_3_Control_B.EngineState) {
   case 0:
    rtAction = 0;
    break;

   case 1:
    rtAction = 1;
    break;

   case 5:
    rtAction = 2;
    break;

   case 2:
    rtAction = 3;
    break;

   case 4:
    rtAction = 4;
    break;

   case 3:
    rtAction = 5;
    break;

   case 6:
    rtAction = 6;
    break;
  }

  CYS_110WP_3_Control_DW.SwitchCase_ActiveSubsystem = rtAction;
  if (rtPrevAction != rtAction) {
    switch (rtPrevAction) {
     case 0:
      /* Disable for Outport: '<S16>/S_Origin' */
      CYS_110WP_3_Control_B.Accelerator_o = 0.0F;
      CYS_110WP_3_Control_B.EValve_Cycle_k = 0U;
      CYS_110WP_3_Control_B.EValve_Open_m = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_f = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_pl = 0U;
      CYS_110WP_3_Control_B.Motor_Cycle_o = 0U;
      CYS_110WP_3_Control_B.Motor_Open_po = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_nf = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_hg = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_pr = 0U;
      CYS_110WP_3_Control_B.SWO_Firework_cz = 0U;
      CYS_110WP_3_Control_B.SWO_BleedAir_a = 0U;
      CYS_110WP_3_Control_B.Origin_T4 = 0.0F;
      CYS_110WP_3_Control_B.Origin_POil = 0.0F;
      break;

     case 1:
     case 2:
     case 5:
     case 6:
      break;

     case 3:
      /* Disable for Outport: '<S13>/S_CloseLoop' */
      CYS_110WP_3_Control_B.CloseLoop_Acclerator = 0.0F;
      CYS_110WP_3_Control_B.CloseLoopMin = 0.0F;
      CYS_110WP_3_Control_B.CloseLoopMax = 0.0F;
      CYS_110WP_3_Control_B.SWO_BleedAir_j = 0U;
      break;

     case 4:
      /* Disable for Outport: '<S18>/S_Stop' */
      CYS_110WP_3_Control_B.Accelerator_p = 0.0F;
      CYS_110WP_3_Control_B.EValve_Cycle_n = 0U;
      CYS_110WP_3_Control_B.EValve_Open_h = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_d = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_d = 0U;
      CYS_110WP_3_Control_B.Motor_Cycle_a = 0U;
      CYS_110WP_3_Control_B.Motor_Open_pl = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_ol = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_ae = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_h = 0U;
      CYS_110WP_3_Control_B.SWO_Firework_a = 0U;
      CYS_110WP_3_Control_B.StopFinish = 0U;
      CYS_110WP_3_Control_B.SWO_BleedAIr = 0U;
      break;
    }
  }

  switch (rtAction) {
   case 0:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Origin' incorporates:
       *  InitializeConditions for ActionPort: '<S16>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S16>/Cool_Control'
       *  InitializeConditions for Delay: '<S16>/Delay'
       *  InitializeConditions for Delay: '<S16>/Delay1'
       *  InitializeConditions for Delay: '<S16>/Delay2'
       *  InitializeConditions for Delay: '<S16>/Delay3'
       *  InitializeConditions for Delay: '<S16>/Delay4'
       *  InitializeConditions for Delay: '<S16>/Delay5'
       *  InitializeConditions for Delay: '<S16>/Delay6'
       *  InitializeConditions for Delay: '<S16>/Delay7'
       */
      CYS_110WP_3_Control_DW.Delay_DSTATE_c = 0.0F;
      CYS_110WP_3_Control_DW.Delay1_DSTATE_og[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay1_DSTATE_og[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[2] = 0.0F;
      CYS_110WP_3_Control_DW.Delay3_DSTATE[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay3_DSTATE[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay3_DSTATE[2] = 0.0F;
      CYS_110WP_3_Control_DW.Delay3_DSTATE[3] = 0.0F;
      CYS_110WP_3_Control_DW.Delay4_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.Delay5_DSTATE[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay5_DSTATE[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay6_DSTATE[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay6_DSTATE[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay6_DSTATE[2] = 0.0F;
      CYS_110WP_3_Control_DW.Delay7_DSTATE[0] = 0.0F;
      CYS_110WP_3_Control_DW.Delay7_DSTATE[1] = 0.0F;
      CYS_110WP_3_Control_DW.Delay7_DSTATE[2] = 0.0F;
      CYS_110WP_3_Control_DW.Delay7_DSTATE[3] = 0.0F;
      CYS_110WP_3_Control_DW.EarthStop = false;
      CYS_110WP_3_Control_DW.CNT_EarthCoolTime = 0U;
      CYS_110WP_3_Control_DW.CNT_Global = 0U;
      CYS_110WP_3_Control_DW.CoolDoneFlag = false;
      CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
      CYS_110WP_3_Control_B.EValve_Open_my = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_b = 0U;

      /* End of InitializeConditions for SubSystem: '<S1>/Origin' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Origin' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 0U;

    /* Chart: '<S16>/Cool_Control' incorporates:
     *  Constant: '<S134>/Constant4'
     *  Constant: '<S134>/constant5'
     *  Constant: '<S16>/N1r_idle6'
     *  Constant: '<S16>/PG_CtrlMode_Start3'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     *  Product: '<S134>/Product2'
     *  Sum: '<S134>/Sum 2'
     *  UnitDelay: '<S1>/Time Delay3'
     */
    /* Gateway: CLM/Origin/Cool_Control */
    /* During: CLM/Origin/Cool_Control */
    /* Entry Internal: CLM/Origin/Cool_Control */
    /* Transition: '<S109>:960' */
    /* Transition: '<S109>:464' */
    /* Transition: '<S109>:966' */
    /* Transition: '<S109>:968' */
    CYS_110WP_3_Control_DW.EarthStop = false;
    CYS_110WP_3_Control_DW.CoolDoneFlag = false;
    CYS_110WP_3_Control_DW.CNT_Global = 0U;

    /* Transition: '<S109>:971' */
    /* Transition: '<S109>:921' */
    /* Transition: '<S109>:970' */
    if (CYS_110WP_3_Control_DW.CNT_Global >= 6000.0F) {
      /* Transition: '<S109>:956' */
      /* Transition: '<S109>:957' */
      CYS_110WP_3_Control_DW.CoolDoneFlag = true;
      CYS_110WP_3_Control_DW.CNT_Global = 0U;

      /* Transition: '<S109>:958' */
    } else {
      /* Transition: '<S109>:952' */
      CYS_110WP_3_Control_DW.CNT_Global++;
    }

    /* Transition: '<S109>:955' */
    if (CYS_110WP_3_Control_DW.EarthStop &&
        (!CYS_110WP_3_Control_DW.CoolDoneFlag)) {
      /* Transition: '<S109>:828' */
      if (CYS_110WP_3_Control_B.Product5_c < 2000.0F) {
        /* Transition: '<S109>:832' */
        /* Transition: '<S109>:836' */
        rtb_Motor_Open_m = 40U;
        rtb_Switch_gc = 1U;

        /* Transition: '<S109>:844' */
      } else {
        /* Transition: '<S109>:838' */
        CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
        CYS_110WP_3_Control_B.EValve_Open_my = 0U;
        rtb_Motor_Open_m = 0U;
        CYS_110WP_3_Control_B.EValve_Enable_b = 0U;
        rtb_Switch_gc = 0U;
      }

      /* Transition: '<S109>:903' */
      if ((CYS_110WP_3_Control_DW.CNT_EarthCoolTime >= 1500.0F) &&
          (CYS_110WP_3_Control_B.Flag_RunState_f != 15)) {
        /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
        /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
        /* Transition: '<S109>:856' */
        /* Transition: '<S109>:858' */
        CYS_110WP_3_Control_B.Accelerator_m = (real32_T)(2.8000000000000003 /
          ((real32_T)arg_MyUsart2_Rxdata[10] * 0.2F + 1.5F));

        /* End of Outputs for SubSystem: '<S2>/CMMRead' */
        /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */
        CYS_110WP_3_Control_B.EValve_Open_my = 30U;
        rtb_Motor_Open_m = 60U;
        CYS_110WP_3_Control_B.EValve_Enable_b = 1U;
        rtb_Switch_gc = 1U;

        /* Transition: '<S109>:862' */
      } else {
        /* Transition: '<S109>:860' */
      }

      /* Transition: '<S109>:863' */
      if (CYS_110WP_3_Control_DW.CNT_EarthCoolTime >= 2000.0F) {
        /* Transition: '<S109>:865' */
        if ((CYS_110WP_3_Control_B.KpLookupTable1 < 110.0F) ||
            (CYS_110WP_3_Control_DW.CNT_EarthCoolTime >= 2500.0F)) {
          /* Transition: '<S109>:867' */
          /* Transition: '<S109>:869' */
          CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
          CYS_110WP_3_Control_B.EValve_Open_my = 0U;
          CYS_110WP_3_Control_B.EValve_Enable_b = 0U;
          rtb_Motor_Open_m = 0U;

          /* Transition: '<S109>:873' */
        } else {
          /* Transition: '<S109>:871' */
          CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
        }

        /* Transition: '<S109>:876' */
      } else {
        /* Transition: '<S109>:874' */
      }

      /* Transition: '<S109>:877' */
      if (CYS_110WP_3_Control_DW.CNT_EarthCoolTime >= 3500.0F) {
        /* Transition: '<S109>:879' */
        /* Transition: '<S109>:773' */
        CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
        CYS_110WP_3_Control_B.EValve_Open_my = 0U;
        rtb_Motor_Open_m = 0U;
        CYS_110WP_3_Control_B.EValve_Enable_b = 0U;
        rtb_Switch_gc = 0U;
        CYS_110WP_3_Control_DW.CNT_EarthCoolTime = 0U;
        CYS_110WP_3_Control_DW.CoolDoneFlag = true;

        /* Transition: '<S109>:962' */
      } else {
        /* Transition: '<S109>:883' */
        CYS_110WP_3_Control_DW.CNT_EarthCoolTime++;
      }

      /* Transition: '<S109>:908' */
    } else {
      /* Transition: '<S109>:909' */
      CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
      CYS_110WP_3_Control_B.EValve_Open_my = 0U;
      rtb_Motor_Open_m = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_b = 0U;
      rtb_Switch_gc = 0U;
    }

    /* End of Chart: '<S16>/Cool_Control' */

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/PG_CtrlMode_Start1'
     *  Product: '<S16>/Divide1'
     */
    /* Transition: '<S109>:911' */
    CYS_110WP_3_Control_B.Accelerator_o = CYS_110WP_3_Control_P.PF_ACCFULLRANGE *
      CYS_110WP_3_Control_B.Accelerator_m;

    /* SignalConversion: '<S16>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Enable_pr = rtb_Switch_gc;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant8'
     */
    CYS_110WP_3_Control_B.SWO_Firework_cz = 0U;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant12'
     */
    CYS_110WP_3_Control_B.SWO_BleedAir_a = 0U;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant11'
     *  Delay: '<S16>/Delay'
     *  Delay: '<S16>/Delay1'
     *  Delay: '<S16>/Delay2'
     *  Delay: '<S16>/Delay3'
     *  Product: '<S16>/Divide'
     *  Sum: '<S16>/Add'
     */
    CYS_110WP_3_Control_B.Origin_T4 = ((((CYS_110WP_3_Control_B.KpLookupTable1 +
      CYS_110WP_3_Control_DW.Delay_DSTATE_c) +
      CYS_110WP_3_Control_DW.Delay1_DSTATE_og[0]) +
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[0]) +
      CYS_110WP_3_Control_DW.Delay3_DSTATE[0]) / 5.0F;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant5'
     *  Delay: '<S16>/Delay4'
     *  Delay: '<S16>/Delay5'
     *  Delay: '<S16>/Delay6'
     *  Delay: '<S16>/Delay7'
     *  Product: '<S16>/Divide2'
     *  Sum: '<S16>/Add1'
     */
    CYS_110WP_3_Control_B.Origin_POil =
      ((((CYS_110WP_3_Control_B.SumofElements1_er +
          CYS_110WP_3_Control_DW.Delay4_DSTATE) +
         CYS_110WP_3_Control_DW.Delay5_DSTATE[0]) +
        CYS_110WP_3_Control_DW.Delay6_DSTATE[0]) +
       CYS_110WP_3_Control_DW.Delay7_DSTATE[0]) / 5.0F;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant1'
     */
    CYS_110WP_3_Control_B.EValve_Cycle_k = 30U;

    /* SignalConversion: '<S16>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Open_m = CYS_110WP_3_Control_B.EValve_Open_my;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant3'
     */
    CYS_110WP_3_Control_B.Eblast_Cycle_f = 30U;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant2'
     */
    CYS_110WP_3_Control_B.Eblast_Open_pl = 0U;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant7'
     */
    CYS_110WP_3_Control_B.Motor_Cycle_o = 100U;

    /* SignalConversion: '<S16>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open_po = rtb_Motor_Open_m;

    /* SignalConversion: '<S16>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Enable_nf =
      CYS_110WP_3_Control_B.EValve_Enable_b;

    /* SignalConversion: '<S16>/Signal Conversion' incorporates:
     *  Constant: '<S16>/Constant4'
     */
    CYS_110WP_3_Control_B.Eblast_Enable_hg = 0U;

    /* Update for Delay: '<S16>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_c = CYS_110WP_3_Control_B.KpLookupTable1;

    /* Update for Delay: '<S16>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_og[0] =
      CYS_110WP_3_Control_DW.Delay1_DSTATE_og[1];
    CYS_110WP_3_Control_DW.Delay1_DSTATE_og[1] =
      CYS_110WP_3_Control_B.KpLookupTable1;

    /* Update for Delay: '<S16>/Delay2' */
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[0] =
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[1];
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[1] =
      CYS_110WP_3_Control_DW.Delay2_DSTATE_n[2];
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[2] =
      CYS_110WP_3_Control_B.KpLookupTable1;

    /* Update for Delay: '<S16>/Delay3' */
    CYS_110WP_3_Control_DW.Delay3_DSTATE[0] =
      CYS_110WP_3_Control_DW.Delay3_DSTATE[1];
    CYS_110WP_3_Control_DW.Delay3_DSTATE[1] =
      CYS_110WP_3_Control_DW.Delay3_DSTATE[2];
    CYS_110WP_3_Control_DW.Delay3_DSTATE[2] =
      CYS_110WP_3_Control_DW.Delay3_DSTATE[3];
    CYS_110WP_3_Control_DW.Delay3_DSTATE[3] =
      CYS_110WP_3_Control_B.KpLookupTable1;

    /* Update for Delay: '<S16>/Delay4' */
    CYS_110WP_3_Control_DW.Delay4_DSTATE =
      CYS_110WP_3_Control_B.SumofElements1_er;

    /* Update for Delay: '<S16>/Delay5' */
    CYS_110WP_3_Control_DW.Delay5_DSTATE[0] =
      CYS_110WP_3_Control_DW.Delay5_DSTATE[1];
    CYS_110WP_3_Control_DW.Delay5_DSTATE[1] =
      CYS_110WP_3_Control_B.SumofElements1_er;

    /* Update for Delay: '<S16>/Delay6' */
    CYS_110WP_3_Control_DW.Delay6_DSTATE[0] =
      CYS_110WP_3_Control_DW.Delay6_DSTATE[1];
    CYS_110WP_3_Control_DW.Delay6_DSTATE[1] =
      CYS_110WP_3_Control_DW.Delay6_DSTATE[2];
    CYS_110WP_3_Control_DW.Delay6_DSTATE[2] =
      CYS_110WP_3_Control_B.SumofElements1_er;

    /* Update for Delay: '<S16>/Delay7' */
    CYS_110WP_3_Control_DW.Delay7_DSTATE[0] =
      CYS_110WP_3_Control_DW.Delay7_DSTATE[1];
    CYS_110WP_3_Control_DW.Delay7_DSTATE[1] =
      CYS_110WP_3_Control_DW.Delay7_DSTATE[2];
    CYS_110WP_3_Control_DW.Delay7_DSTATE[2] =
      CYS_110WP_3_Control_DW.Delay7_DSTATE[3];
    CYS_110WP_3_Control_DW.Delay7_DSTATE[3] =
      CYS_110WP_3_Control_B.SumofElements1_er;

    /* End of Outputs for SubSystem: '<S1>/Origin' */
    break;

   case 1:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Start' incorporates:
       *  InitializeConditions for ActionPort: '<S17>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S111>/Hold'
       *  InitializeConditions for Chart: '<S115>/Hold'
       *  InitializeConditions for Chart: '<S115>/Timmer_ms'
       *  InitializeConditions for Chart: '<S17>/Range'
       *  InitializeConditions for Chart: '<S17>/Start_OpenLoop'
       *  InitializeConditions for Delay: '<S111>/Delay'
       *  InitializeConditions for Delay: '<S111>/Delay1'
       *  InitializeConditions for Delay: '<S115>/Delay'
       *  InitializeConditions for Delay: '<S115>/Delay1'
       *  InitializeConditions for Delay: '<S115>/Delay2'
       *  InitializeConditions for UnitDelay: '<S17>/Time Delay1'
       */
      CYS_110WP_3_Control_DW.Delay_DSTATE_i = 0.0F;
      CYS_110WP_3_Control_DW.Delay1_DSTATE_a = 0.0F;
      CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold,
        &CYS_110WP_3_Control_DW.sf_Hold);
      CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_n,
        &CYS_110WP_3_Control_DW.sf_Hold_n);
      CYS_110WP_3_Control_DW.Delay_DSTATE_p = 0U;
      CYS_110WP_3_Control_DW.Delay1_DSTATE_e = 0.0F;
      CYS_110WP_3_Control_DW.Delay2_DSTATE = 0.0F;
      CYS_110WP_3_Cont_Timmer_ms_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms,
        &CYS_110WP_3_Control_DW.sf_Timmer_ms);
      CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE_f = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE_p = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE_j = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE_c = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_5_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_6_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.CNT_Start_C_o = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_E_o = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_B_a = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_F_d = 0U;
      CYS_110WP_3_Control_DW.Start_A_o = true;
      CYS_110WP_3_Control_DW.Start_B_h = false;
      CYS_110WP_3_Control_DW.Start_C_i = false;
      CYS_110WP_3_Control_DW.Start_D_j = false;
      CYS_110WP_3_Control_DW.Start_E_a = false;
      CYS_110WP_3_Control_DW.Start_F_k = false;
      CYS_110WP_3_Control_DW.CNT_Motor_b = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_D_f = 0U;
      CYS_110WP_3_Control_DW.CNT_EValve_Open_h = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_A_m = 0U;
      CYS_110WP_3_Control_DW.CNT_POilHigh_d = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_C1_g = 0U;
      CYS_110WP_3_Control_DW.Flag_IntoC = false;
      CYS_110WP_3_Control_DW.Motor_OFF_Enable = 0U;
      CYS_110WP_3_Control_B.Accelerator_c = 0.0F;
      CYS_110WP_3_Control_B.EValve_Cycle_e = 0U;
      CYS_110WP_3_Control_B.EValve_Open_e = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_o = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_eu = 0U;
      CYS_110WP_3_Control_B.Motor_Cycle_i = 0U;
      CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;
      CYS_110WP_3_Control_B.EValve_Enable_n = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_h = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_b1 = 0U;
      CYS_110WP_3_Control_B.SWO_Firework_c = 0U;
      CYS_110WP_3_Control_B.Flag_EngineState_h = 0U;
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range);

      /* End of InitializeConditions for SubSystem: '<S1>/Start' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Start' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 1U;

    /* Chart: '<S111>/Hold' incorporates:
     *  Constant: '<S17>/PG_CtrlMode_Start'
     */
    CYS_110WP_3_Control_Hold(&CYS_110WP_3_Control_B.sf_Hold,
      &CYS_110WP_3_Control_DW.sf_Hold);

    /* Switch: '<S117>/Switch' incorporates:
     *  Delay: '<S111>/Delay1'
     *  Switch: '<S118>/Switch'
     */
    if (CYS_110WP_3_Control_B.sf_Hold.Out) {
      /* Update for Delay: '<S111>/Delay' */
      CYS_110WP_3_Control_DW.Delay_DSTATE_i = CYS_110WP_3_Control_B.X_Out_a;
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_B.T4_X3_Y3;
    } else {
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_DW.Delay1_DSTATE_a;
    }

    /* End of Switch: '<S117>/Switch' */

    /* Chart: '<S115>/Hold' */
    CYS_110WP_3_Control_Hold(&CYS_110WP_3_Control_B.sf_Hold_n,
      &CYS_110WP_3_Control_DW.sf_Hold_n);

    /* Switch: '<S122>/Switch' incorporates:
     *  Constant: '<S115>/Constant'
     *  Constant: '<S115>/Constant1'
     *  Delay: '<S115>/Delay'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_n.Out) {
      /* Dynamic Look-Up Table Block: '<S115>/Lookup Table Dynamic'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Integer        U16
       * Output0 Data Type:  Integer        U16
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_U16_real32_T( &(rtb_LookupTableDynamic_h),
        CYS_110WP_3_Control_ConstP.pooled45,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);
      rtb_Motor_Open_m = rtb_LookupTableDynamic_h;
    } else {
      rtb_Motor_Open_m = CYS_110WP_3_Control_DW.Delay_DSTATE_p;
    }

    /* End of Switch: '<S122>/Switch' */

    /* Switch: '<S123>/Switch' incorporates:
     *  Constant: '<S115>/Constant2'
     *  Constant: '<S115>/Constant3'
     *  Delay: '<S115>/Delay1'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_n.Out) {
      /* Dynamic Look-Up Table Block: '<S115>/Lookup Table Dynamic1'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Integer        U16
       * Output0 Data Type:  Integer        U16
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_U16_real32_T( &(rtb_LookupTableDynamic1_p),
        CYS_110WP_3_Control_ConstP.Constant2_Value_l,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);
      CYS_110WP_3_Control_B.X_Out_a = rtb_LookupTableDynamic1_p;
    } else {
      CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.Delay1_DSTATE_e;
    }

    /* End of Switch: '<S123>/Switch' */

    /* Switch: '<S124>/Switch' incorporates:
     *  Constant: '<S115>/Constant4'
     *  Constant: '<S115>/Constant5'
     *  Delay: '<S115>/Delay2'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_n.Out) {
      /* Dynamic Look-Up Table Block: '<S115>/Lookup Table Dynamic2'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Integer        U16
       * Output0 Data Type:  Integer        U16
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_U16_real32_T( &(rtb_LookupTableDynamic2_k),
        CYS_110WP_3_Control_ConstP.Constant4_Value_g,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);
      CYS_110WP_3_Control_B.T4_X3_Y3 = rtb_LookupTableDynamic2_k;
    } else {
      CYS_110WP_3_Control_B.T4_X3_Y3 = CYS_110WP_3_Control_DW.Delay2_DSTATE;
    }

    /* End of Switch: '<S124>/Switch' */

    /* Chart: '<S115>/Timmer_ms' incorporates:
     *  Constant: '<S115>/Constant8'
     *  Constant: '<S115>/Constant9'
     */
    CYS_110WP_3_Control_Timmer_ms(true, 1000.0F,
      &CYS_110WP_3_Control_B.sf_Timmer_ms, &CYS_110WP_3_Control_DW.sf_Timmer_ms);

    /* If: '<S115>/If' incorporates:
     *  Constant: '<S121>/Constant'
     *  Constant: '<S121>/Constant1'
     *  Constant: '<S121>/Constant10'
     *  Constant: '<S121>/Constant2'
     *  Constant: '<S121>/Constant3'
     *  Constant: '<S121>/Constant4'
     *  Constant: '<S121>/Constant5'
     *  Constant: '<S121>/Constant6'
     *  Constant: '<S121>/Constant7'
     *  Constant: '<S121>/Constant8'
     *  Constant: '<S121>/Constant9'
     *  Inport: '<S120>/In1'
     *  Inport: '<S120>/In2'
     *  Inport: '<S120>/In3'
     *  Inport: '<S120>/In4'
     *  Inport: '<S120>/In5'
     *  Inport: '<S120>/In6'
     *  UnitDelay: '<S17>/Time Delay1'
     */
    if (CYS_110WP_3_Control_B.sf_Timmer_ms.Out > 0) {
      /* Outputs for IfAction SubSystem: '<S115>/If Action Subsystem' incorporates:
       *  ActionPort: '<S120>/Action Port'
       */
      CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE_f;
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE_p;
      CYS_110WP_3_Control_B.m3_h = CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE_j;
      CYS_110WP_3_Control_B.m4_ex = CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE_c;
      CYS_110WP_3_Control_B.n1_n = CYS_110WP_3_Control_DW.TimeDelay1_5_DSTATE;
      CYS_110WP_3_Control_B.n2_d = CYS_110WP_3_Control_DW.TimeDelay1_6_DSTATE;

      /* End of Outputs for SubSystem: '<S115>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S115>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S121>/Action Port'
       */
      /* Dynamic Look-Up Table Block: '<S121>/Lookup Table Dynamic'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic_j),
        CYS_110WP_3_Control_ConstP.pooled6,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S121>/Lookup Table Dynamic1'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T
        ( &(CYS_110WP_3_Control_B.LookupTableDynamic1_o),
         CYS_110WP_3_Control_ConstP.Constant2_Value_m,
         CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S121>/Lookup Table Dynamic2'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T
        ( &(CYS_110WP_3_Control_B.LookupTableDynamic2_g),
         CYS_110WP_3_Control_ConstP.Constant4_Value_l,
         CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S121>/Lookup Table Dynamic3'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T
        ( &(CYS_110WP_3_Control_B.LookupTableDynamic3_b),
         CYS_110WP_3_Control_ConstP.Constant6_Value_c,
         CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S121>/Lookup Table Dynamic4'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic4),
        CYS_110WP_3_Control_ConstP.Constant8_Value,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* SignalConversion: '<S121>/OutportBufferForm1' incorporates:
       *  Constant: '<S121>/Constant'
       *  Constant: '<S121>/Constant1'
       *  Constant: '<S121>/Constant2'
       *  Constant: '<S121>/Constant3'
       *  Constant: '<S121>/Constant4'
       *  Constant: '<S121>/Constant5'
       *  Constant: '<S121>/Constant6'
       *  Constant: '<S121>/Constant7'
       *  Constant: '<S121>/Constant8'
       *  Constant: '<S121>/Constant9'
       */
      CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_B.LookupTableDynamic_j;

      /* SignalConversion: '<S121>/OutportBufferForm2' */
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_B.LookupTableDynamic1_o;

      /* SignalConversion: '<S121>/OutportBufferForm3' */
      CYS_110WP_3_Control_B.m3_h = CYS_110WP_3_Control_B.LookupTableDynamic2_g;

      /* SignalConversion: '<S121>/OutportBufferForm4' */
      CYS_110WP_3_Control_B.m4_ex = CYS_110WP_3_Control_B.LookupTableDynamic3_b;

      /* SignalConversion: '<S121>/OutportBufferForn1' */
      CYS_110WP_3_Control_B.n1_n = CYS_110WP_3_Control_B.LookupTableDynamic4;
      CYS_110WP_3_Control_B.n2_d = 20000.0F;

      /* End of Outputs for SubSystem: '<S115>/If Action Subsystem1' */
    }

    /* End of If: '<S115>/If' */

    /* Chart: '<S17>/Start_OpenLoop' incorporates:
     *  Constant: '<S17>/PG_CtrlMode_Start3'
     */
    /* Gateway: CLM/Start/Start_OpenLoop */
    /* During: CLM/Start/Start_OpenLoop */
    /* Entry Internal: CLM/Start/Start_OpenLoop */
    /* Transition: '<S114>:41' */
    if (CYS_110WP_3_Control_DW.Start_A_o) {
      /* Transition: '<S114>:204' */
      if (CYS_110WP_3_Control_DW.CNT_Start_A_m >= 50.0F) {
        /* Transition: '<S114>:1347' */
        /* Transition: '<S114>:1349' */
        CYS_110WP_3_Control_DW.Start_A_o = false;
        CYS_110WP_3_Control_DW.Start_B_h = true;

        /* Transition: '<S114>:1350' */
      } else {
        /* Transition: '<S114>:469' */
        CYS_110WP_3_Control_B.Motor_Cycle_i = 100U;
        CYS_110WP_3_Control_B.Motor_Open_f = rtb_Motor_Open_m;
        CYS_110WP_3_Control_B.Motor_Enable_b1 = 1U;
        CYS_110WP_3_Control_B.Eblast_Cycle_o = 30U;
        CYS_110WP_3_Control_B.Eblast_Open_eu = 30U;
        CYS_110WP_3_Control_B.Eblast_Enable_h = 1U;
        CYS_110WP_3_Control_B.EValve_Cycle_e = 30U;
        CYS_110WP_3_Control_B.EValve_Open_e = 30U;
        CYS_110WP_3_Control_B.EValve_Enable_n = 1U;
      }

      /* Transition: '<S114>:470' */
      CYS_110WP_3_Control_DW.CNT_Start_A_m++;
    } else {
      /* Transition: '<S114>:464' */
    }

    /* Transition: '<S114>:214' */
    if (CYS_110WP_3_Control_DW.Start_B_h) {
      /* Transition: '<S114>:471' */
      if (CYS_110WP_3_Control_B.Product5_c >= 1000.0F) {
        /* Transition: '<S114>:475' */
        /* Transition: '<S114>:480' */
        CYS_110WP_3_Control_DW.Start_B_h = false;
        CYS_110WP_3_Control_DW.Start_C_i = true;
        CYS_110WP_3_Control_B.SWO_Firework_c = 1U;
        CYS_110WP_3_Control_B.Accelerator_c = 5000.0F;

        /* Transition: '<S114>:948' */
        /* Transition: '<S114>:1078' */
      } else {
        /* Transition: '<S114>:1000' */
        if (CYS_110WP_3_Control_DW.CNT_Start_B_a >= 300.0F) {
          /* Transition: '<S114>:999' */
          /* Transition: '<S114>:477' */
          CYS_110WP_3_Control_B.Flag_EngineState_h = 4U;
          CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;

          /* Transition: '<S114>:1078' */
        } else {
          /* Transition: '<S114>:1069' */
        }
      }

      /* Transition: '<S114>:478' */
      CYS_110WP_3_Control_DW.CNT_Start_B_a++;
    } else {
      /* Transition: '<S114>:473' */
    }

    /* Transition: '<S114>:216' */
    if (CYS_110WP_3_Control_DW.Start_C_i) {
      /* Transition: '<S114>:495' */
      if ((CYS_110WP_3_Control_DW.CNT_Start_C_o > 150.0F) ||
          (CYS_110WP_3_Control_B.SumofElements1_er -
           CYS_110WP_3_Control_B.Switch_e >= 50.0F) ||
          CYS_110WP_3_Control_DW.Flag_IntoC) {
        /* Transition: '<S114>:1157' */
        /* Transition: '<S114>:1160' */
        CYS_110WP_3_Control_B.EValve_Cycle_e = 30U;
        CYS_110WP_3_Control_B.EValve_Open_e = 0U;
        CYS_110WP_3_Control_B.EValve_Enable_n = 0U;
        CYS_110WP_3_Control_B.Accelerator_c = CYS_110WP_3_Control_B.m1_h;
        if ((CYS_110WP_3_Control_DW.CNT_Start_C1_g >=
             CYS_110WP_3_Control_B.T4_X3_Y3 * 1000.0F / 20.0F) ||
            (CYS_110WP_3_Control_B.Product5_c >= 6000.0F) ||
            CYS_110WP_3_Control_DW.Flag_IntoC) {
          /* Transition: '<S114>:943' */
          /* Transition: '<S114>:1376' */
          if (CYS_110WP_3_Control_B.Motor_Open_f >= 100.0F) {
            /* Transition: '<S114>:1382' */
            /* Transition: '<S114>:1383' */
            CYS_110WP_3_Control_DW.Start_C_i = false;
            CYS_110WP_3_Control_DW.Start_D_j = true;
            CYS_110WP_3_Control_B.Motor_Open_f = 100.0F;

            /* Transition: '<S114>:1384' */
          } else {
            /* Transition: '<S114>:1377' */
            CYS_110WP_3_Control_B.Motor_Open_f += (real32_T)(100 -
              rtb_Motor_Open_m) / (CYS_110WP_3_Control_B.X_Out_a * 1000.0F /
              20.0F);
            CYS_110WP_3_Control_DW.Flag_IntoC = true;
          }

          /* Transition: '<S114>:1378' */
          /* Transition: '<S114>:1179' */
          /* Transition: '<S114>:1340' */
        } else {
          /* Transition: '<S114>:1338' */
          CYS_110WP_3_Control_DW.CNT_Start_C1_g++;
        }

        /* Transition: '<S114>:1159' */
      } else {
        /* Transition: '<S114>:1335' */
        /* Transition: '<S114>:1184' */
      }

      /* Transition: '<S114>:947' */
      CYS_110WP_3_Control_DW.CNT_Start_C_o++;
    } else {
      /* Transition: '<S114>:578' */
    }

    /* Transition: '<S114>:586' */
    if (CYS_110WP_3_Control_DW.Start_D_j) {
      /* Transition: '<S114>:590' */
      if (CYS_110WP_3_Control_B.Product5_c > CYS_110WP_3_Control_B.n1_n) {
        /* Transition: '<S114>:861' */
        /* Transition: '<S114>:804' */
        CYS_110WP_3_Control_DW.Start_D_j = false;
        CYS_110WP_3_Control_DW.Start_E_a = true;

        /* Transition: '<S114>:1169' */
        /* Transition: '<S114>:1195' */
        /* Transition: '<S114>:950' */
      } else {
        /* Transition: '<S114>:1193' */
        /* Transition: '<S114>:1167' */
        if (CYS_110WP_3_Control_DW.CNT_Start_D_f > 300.0F) {
          /* Transition: '<S114>:1171' */
          /* Transition: '<S114>:1172' */
          CYS_110WP_3_Control_B.SWO_Firework_c = 0U;
          CYS_110WP_3_Control_B.Flag_EngineState_h = 15U;
          CYS_110WP_3_Control_B.Accelerator_c = 0.0F;

          /* Transition: '<S114>:950' */
        } else {
          /* Transition: '<S114>:862' */
        }
      }

      /* Transition: '<S114>:593' */
      CYS_110WP_3_Control_DW.CNT_Start_D_f++;
    } else {
      /* Transition: '<S114>:493' */
    }

    /* Transition: '<S114>:622' */
    if (CYS_110WP_3_Control_DW.Start_E_a) {
      /* Transition: '<S114>:625' */
      if (CYS_110WP_3_Control_B.Product5_c > 20000.0F) {
        /* Transition: '<S114>:1250' */
        /* Transition: '<S114>:1253' */
        CYS_110WP_3_Control_DW.Start_E_a = false;
        CYS_110WP_3_Control_DW.Start_F_k = true;
        CYS_110WP_3_Control_B.Motor_Cycle_i = 100U;
        CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;
        CYS_110WP_3_Control_B.Motor_Enable_b1 = 0U;
        CYS_110WP_3_Control_B.SWO_Firework_c = 0U;
        CYS_110WP_3_Control_B.Accelerator_c = CYS_110WP_3_Control_B.m3_h;

        /* Transition: '<S114>:1245' */
        /* Transition: '<S114>:1241' */
        /* Transition: '<S114>:1258' */
        /* Transition: '<S114>:1320' */
        /* Transition: '<S114>:1230' */
        /* Transition: '<S114>:1223' */
      } else {
        /* Transition: '<S114>:1310' */
        if (CYS_110WP_3_Control_B.SumofElements1_er > 700.0F) {
          /* Transition: '<S114>:1227' */
          /* Transition: '<S114>:1229' */
          if (CYS_110WP_3_Control_DW.CNT_POilHigh_d > 100.0F) {
            /* Transition: '<S114>:1243' */
            /* Transition: '<S114>:1242' */
            CYS_110WP_3_Control_B.Flag_EngineState_h = 15U;
            CYS_110WP_3_Control_B.Accelerator_c = 0.0F;

            /* Transition: '<S114>:1241' */
            /* Transition: '<S114>:1258' */
            /* Transition: '<S114>:1320' */
            /* Transition: '<S114>:1230' */
            /* Transition: '<S114>:1223' */
          } else {
            /* Transition: '<S114>:1238' */
            CYS_110WP_3_Control_DW.CNT_POilHigh_d++;

            /* Transition: '<S114>:1258' */
            /* Transition: '<S114>:1320' */
            /* Transition: '<S114>:1230' */
            /* Transition: '<S114>:1223' */
          }
        } else {
          /* Transition: '<S114>:1232' */
          if (CYS_110WP_3_Control_DW.CNT_Start_E_o > 1500.0F) {
            /* Transition: '<S114>:1260' */
            /* Transition: '<S114>:1261' */
            CYS_110WP_3_Control_B.Flag_EngineState_h = 15U;
            CYS_110WP_3_Control_B.Accelerator_c = 0.0F;

            /* Transition: '<S114>:1320' */
            /* Transition: '<S114>:1230' */
            /* Transition: '<S114>:1223' */
          } else {
            /* Transition: '<S114>:1317' */
            if (CYS_110WP_3_Control_B.Product5_c > 13000.0F) {
              /* Transition: '<S114>:1321' */
              /* Transition: '<S114>:1322' */
              CYS_110WP_3_Control_B.Motor_Cycle_i = 100U;
              CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;
              CYS_110WP_3_Control_B.Motor_Enable_b1 = 0U;
              CYS_110WP_3_Control_B.SWO_Firework_c = 0U;

              /* Transition: '<S114>:1391' */
            } else {
              /* Transition: '<S114>:1256' */
            }

            /* Transition: '<S114>:1324' */
            CYS_110WP_3_Control_B.Accelerator_c = (CYS_110WP_3_Control_B.m2_j -
              CYS_110WP_3_Control_B.m1_h) / (CYS_110WP_3_Control_B.n2_d -
              CYS_110WP_3_Control_B.n1_n) * CYS_110WP_3_Control_B.Product5_c +
              (CYS_110WP_3_Control_B.m1_h * CYS_110WP_3_Control_B.n2_d -
               CYS_110WP_3_Control_B.m2_j * CYS_110WP_3_Control_B.n1_n) /
              (CYS_110WP_3_Control_B.n2_d - CYS_110WP_3_Control_B.n1_n);
          }
        }
      }

      /* Transition: '<S114>:637' */
      CYS_110WP_3_Control_DW.CNT_Start_E_o++;
    } else {
      /* Transition: '<S114>:628' */
    }

    /* Transition: '<S114>:1136' */
    if (CYS_110WP_3_Control_DW.Start_F_k) {
      /* Transition: '<S114>:1269' */
      if ((CYS_110WP_3_Control_B.Product5_c > 28000.0F) ||
          (CYS_110WP_3_Control_DW.CNT_Start_F_d >= 1000.0F)) {
        /* Transition: '<S114>:1234' */
        /* Transition: '<S114>:1246' */
        CYS_110WP_3_Control_B.Eblast_Cycle_o = 30U;
        CYS_110WP_3_Control_B.Eblast_Open_eu = 0U;
        CYS_110WP_3_Control_B.Eblast_Enable_h = 0U;
        if (CYS_110WP_3_Control_DW.CNT_EValve_Open_h > 150.0F) {
          /* Transition: '<S114>:1301' */
          /* Transition: '<S114>:1303' */
          CYS_110WP_3_Control_B.Flag_EngineState_h = 2U;

          /* Transition: '<S114>:1304' */
          /* Transition: '<S114>:1292' */
        } else {
          /* Transition: '<S114>:1300' */
          if (CYS_110WP_3_Control_DW.CNT_EValve_Open_h > 50.0F) {
            /* Transition: '<S114>:1289' */
            /* Transition: '<S114>:1291' */
            CYS_110WP_3_Control_B.EValve_Cycle_e = 30U;
            CYS_110WP_3_Control_B.EValve_Open_e = 30U;
            CYS_110WP_3_Control_B.EValve_Enable_n = 1U;
            CYS_110WP_3_Control_B.Accelerator_c = CYS_110WP_3_Control_B.m4_ex;

            /* Transition: '<S114>:1292' */
          } else {
            /* Transition: '<S114>:1297' */
          }
        }

        /* Transition: '<S114>:1280' */
        CYS_110WP_3_Control_DW.CNT_EValve_Open_h++;

        /* Transition: '<S114>:1279' */
        /* Transition: '<S114>:1278' */
      } else {
        /* Transition: '<S114>:1270' */
        /* Transition: '<S114>:1272' */
        /* Transition: '<S114>:1275' */
      }

      /* Transition: '<S114>:1277' */
      CYS_110WP_3_Control_DW.CNT_Start_F_d++;
    } else {
      /* Transition: '<S114>:1266' */
    }

    /* Transition: '<S114>:1405' */
    if ((CYS_110WP_3_Control_B.Product5_c > 13000.0F) ||
        (CYS_110WP_3_Control_DW.Motor_OFF_Enable == 1)) {
      /* Transition: '<S114>:1406' */
      if (CYS_110WP_3_Control_DW.CNT_Motor_b > 4U) {
        /* Transition: '<S114>:1399' */
        /* Transition: '<S114>:1401' */
        CYS_110WP_3_Control_B.Motor_Cycle_i = 100U;
        CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;
        CYS_110WP_3_Control_DW.Motor_OFF_Enable = 1U;

        /* Transition: '<S114>:1403' */
      } else {
        /* Transition: '<S114>:1407' */
        CYS_110WP_3_Control_DW.CNT_Motor_b++;
      }

      /* Transition: '<S114>:1402' */
    } else {
      /* Transition: '<S114>:1400' */
    }

    /* End of Chart: '<S17>/Start_OpenLoop' */

    /* Chart: '<S17>/Range' incorporates:
     *  Constant: '<S17>/Constant5'
     *  Constant: '<S17>/Constant6'
     */
    /* Transition: '<S114>:1404' */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Accelerator_c, 5000.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range);

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Start_Accelerator = CYS_110WP_3_Control_B.sf_Range.Out;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Enable_b = CYS_110WP_3_Control_B.Motor_Enable_b1;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.SWO_Firework_n = CYS_110WP_3_Control_B.SWO_Firework_c;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Flag_RunState_f =
      CYS_110WP_3_Control_B.Flag_EngineState_h;

    /* SignalConversion: '<S17>/Signal Conversion' incorporates:
     *  Constant: '<S110>/Constant'
     *  RelationalOperator: '<S110>/Compare'
     */
    CYS_110WP_3_Control_B.SWO_BleedAir_jd = (uint8_T)
      (CYS_110WP_3_Control_B.Product5_c >= 5000.0F);

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Cycle_i = CYS_110WP_3_Control_B.EValve_Cycle_e;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Open_jg = CYS_110WP_3_Control_B.EValve_Open_e;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Cycle_gv = CYS_110WP_3_Control_B.Eblast_Cycle_o;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Open_e = CYS_110WP_3_Control_B.Eblast_Open_eu;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Cycle_l = CYS_110WP_3_Control_B.Motor_Cycle_i;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open = CYS_110WP_3_Control_B.Motor_Open_f;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Enable_cr =
      CYS_110WP_3_Control_B.EValve_Enable_n;

    /* SignalConversion: '<S17>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Enable_oj =
      CYS_110WP_3_Control_B.Eblast_Enable_h;

    /* Update for Delay: '<S111>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_a = CYS_110WP_3_Control_B.Switch_e;

    /* Update for Delay: '<S115>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_p = rtb_Motor_Open_m;

    /* Update for Delay: '<S115>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_e = CYS_110WP_3_Control_B.X_Out_a;

    /* Update for Delay: '<S115>/Delay2' */
    CYS_110WP_3_Control_DW.Delay2_DSTATE = CYS_110WP_3_Control_B.T4_X3_Y3;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE_f = CYS_110WP_3_Control_B.m1_h;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE_p = CYS_110WP_3_Control_B.m2_j;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE_j = CYS_110WP_3_Control_B.m3_h;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE_c = CYS_110WP_3_Control_B.m4_ex;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_5_DSTATE = CYS_110WP_3_Control_B.n1_n;

    /* Update for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_6_DSTATE = CYS_110WP_3_Control_B.n2_d;

    /* End of Outputs for SubSystem: '<S1>/Start' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/AirStart' incorporates:
       *  InitializeConditions for ActionPort: '<S10>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S10>/Range'
       *  InitializeConditions for Chart: '<S10>/Start_OpenLoop'
       *  InitializeConditions for Chart: '<S20>/Hold'
       *  InitializeConditions for Chart: '<S24>/Hold'
       *  InitializeConditions for Chart: '<S24>/Hold1'
       *  InitializeConditions for Chart: '<S24>/Timmer_ms'
       *  InitializeConditions for Delay: '<S20>/Delay'
       *  InitializeConditions for Delay: '<S20>/Delay1'
       *  InitializeConditions for Delay: '<S24>/Delay'
       *  InitializeConditions for Delay: '<S24>/Delay1'
       *  InitializeConditions for UnitDelay: '<S10>/Time Delay1'
       */
      CYS_110WP_3_Control_DW.Delay_DSTATE_o = 0.0F;
      CYS_110WP_3_Control_DW.Delay1_DSTATE = 0.0F;
      CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_c,
        &CYS_110WP_3_Control_DW.sf_Hold_c);
      CYS_110WP_3_Control_Hold1_Init(&CYS_110WP_3_Control_B.sf_Hold1,
        &CYS_110WP_3_Control_DW.sf_Hold1);
      CYS_110WP_3_Control_DW.Delay1_DSTATE_o = 0.0F;
      CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_o,
        &CYS_110WP_3_Control_DW.sf_Hold_o);
      CYS_110WP_3_Control_DW.Delay_DSTATE_f = 0U;
      CYS_110WP_3_Cont_Timmer_ms_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms_f,
        &CYS_110WP_3_Control_DW.sf_Timmer_ms_f);
      CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE = 0.0F;
      CYS_110WP_3_Control_DW.CNT_Start_C_l = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_E = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_B_h = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_F = 0U;
      CYS_110WP_3_Control_DW.Start_A_h = true;
      CYS_110WP_3_Control_DW.Start_B_l = false;
      CYS_110WP_3_Control_DW.Start_C_o = false;
      CYS_110WP_3_Control_DW.Start_D = false;
      CYS_110WP_3_Control_DW.Start_E = false;
      CYS_110WP_3_Control_DW.Start_F = false;
      CYS_110WP_3_Control_DW.CNT_Start_D = 0U;
      CYS_110WP_3_Control_DW.CNT_EValve_Open = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_A = 0U;
      CYS_110WP_3_Control_DW.CNT_POilHigh = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_C1_d = 0U;
      CYS_110WP_3_Control_B.Accelerator_e = 0.0F;
      CYS_110WP_3_Control_B.EValve_Cycle_js = 0U;
      CYS_110WP_3_Control_B.EValve_Open_jc = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_b = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_n = 0U;
      CYS_110WP_3_Control_B.Motor_Cycle_c = 0U;
      CYS_110WP_3_Control_B.Motor_Open_nq = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_ot = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_k = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_p = 0U;
      CYS_110WP_3_Control_B.SWO_Firework_p = 0U;
      CYS_110WP_3_Control_B.Flag_EngineState = 0U;
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_j);

      /* End of InitializeConditions for SubSystem: '<S1>/AirStart' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/AirStart' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 5U;

    /* Chart: '<S20>/Hold' incorporates:
     *  Constant: '<S10>/PG_CtrlMode_Start'
     */
    CYS_110WP_3_Control_Hold(&CYS_110WP_3_Control_B.sf_Hold_c,
      &CYS_110WP_3_Control_DW.sf_Hold_c);

    /* Switch: '<S26>/Switch' incorporates:
     *  Delay: '<S20>/Delay1'
     *  Switch: '<S27>/Switch'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_c.Out) {
      /* Update for Delay: '<S20>/Delay' */
      CYS_110WP_3_Control_DW.Delay_DSTATE_o = CYS_110WP_3_Control_B.X_Out_a;
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_B.T4_X3_Y3;
    } else {
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_DW.Delay1_DSTATE;
    }

    /* End of Switch: '<S26>/Switch' */

    /* Chart: '<S24>/Hold1' */
    CYS_110WP_3_Control_Hold1(&CYS_110WP_3_Control_B.sf_Hold1,
      &CYS_110WP_3_Control_DW.sf_Hold1);

    /* Switch: '<S33>/Switch' incorporates:
     *  Delay: '<S24>/Delay1'
     */
    if (CYS_110WP_3_Control_B.sf_Hold1.Out) {
      CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_B.SumofElements1_er;
    } else {
      CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.Delay1_DSTATE_o;
    }

    /* End of Switch: '<S33>/Switch' */

    /* Chart: '<S24>/Hold' */
    CYS_110WP_3_Control_Hold(&CYS_110WP_3_Control_B.sf_Hold_o,
      &CYS_110WP_3_Control_DW.sf_Hold_o);

    /* Switch: '<S32>/Switch' incorporates:
     *  Constant: '<S24>/Constant'
     *  Constant: '<S24>/Constant1'
     *  Delay: '<S24>/Delay'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_o.Out) {
      /* Dynamic Look-Up Table Block: '<S24>/Lookup Table Dynamic'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Integer        U16
       * Output0 Data Type:  Integer        U16
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_U16_real32_T( &(rtb_LookupTableDynamic_o),
        CYS_110WP_3_Control_ConstP.pooled45,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);
      rtb_Motor_Open_m = rtb_LookupTableDynamic_o;
    } else {
      rtb_Motor_Open_m = CYS_110WP_3_Control_DW.Delay_DSTATE_f;
    }

    /* End of Switch: '<S32>/Switch' */

    /* Chart: '<S24>/Timmer_ms' incorporates:
     *  Constant: '<S24>/Constant8'
     *  Constant: '<S24>/Constant9'
     */
    CYS_110WP_3_Control_Timmer_ms(true, 1000.0F,
      &CYS_110WP_3_Control_B.sf_Timmer_ms_f,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms_f);

    /* If: '<S24>/If' incorporates:
     *  Constant: '<S31>/Constant'
     *  Constant: '<S31>/Constant1'
     *  Constant: '<S31>/Constant2'
     *  Constant: '<S31>/Constant3'
     *  Constant: '<S31>/Constant4'
     *  Constant: '<S31>/Constant5'
     *  Constant: '<S31>/Constant6'
     *  Constant: '<S31>/Constant7'
     *  Inport: '<S30>/In1'
     *  Inport: '<S30>/In2'
     *  Inport: '<S30>/In3'
     *  Inport: '<S30>/In4'
     *  UnitDelay: '<S10>/Time Delay1'
     */
    if (CYS_110WP_3_Control_B.sf_Timmer_ms_f.Out > 0) {
      /* Outputs for IfAction SubSystem: '<S24>/If Action Subsystem' incorporates:
       *  ActionPort: '<S30>/Action Port'
       */
      CYS_110WP_3_Control_B.T4_X3_Y3 =
        CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE;
      CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE;
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE;
      CYS_110WP_3_Control_B.m3_h = CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE;

      /* End of Outputs for SubSystem: '<S24>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S24>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S31>/Action Port'
       */
      /* Dynamic Look-Up Table Block: '<S31>/Lookup Table Dynamic'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic),
        CYS_110WP_3_Control_ConstP.pooled6,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S31>/Lookup Table Dynamic1'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic1),
        CYS_110WP_3_Control_ConstP.Constant2_Value_mw,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S31>/Lookup Table Dynamic2'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic2),
        CYS_110WP_3_Control_ConstP.Constant4_Value_ls,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* Dynamic Look-Up Table Block: '<S31>/Lookup Table Dynamic3'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T
        ( &(CYS_110WP_3_Control_B.LookupTableDynamic3_j),
         CYS_110WP_3_Control_ConstP.Constant6_Value_n,
         CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* SignalConversion: '<S31>/OutportBufferForm1' incorporates:
       *  Constant: '<S31>/Constant'
       *  Constant: '<S31>/Constant1'
       *  Constant: '<S31>/Constant2'
       *  Constant: '<S31>/Constant3'
       *  Constant: '<S31>/Constant4'
       *  Constant: '<S31>/Constant5'
       *  Constant: '<S31>/Constant6'
       *  Constant: '<S31>/Constant7'
       */
      CYS_110WP_3_Control_B.T4_X3_Y3 = CYS_110WP_3_Control_B.LookupTableDynamic;

      /* SignalConversion: '<S31>/OutportBufferForm2' */
      CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_B.LookupTableDynamic1;

      /* SignalConversion: '<S31>/OutportBufferForm3' */
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_B.LookupTableDynamic2;

      /* SignalConversion: '<S31>/OutportBufferForm4' */
      CYS_110WP_3_Control_B.m3_h = CYS_110WP_3_Control_B.LookupTableDynamic3_j;

      /* End of Outputs for SubSystem: '<S24>/If Action Subsystem1' */
    }

    /* End of If: '<S24>/If' */

    /* Chart: '<S10>/Start_OpenLoop' incorporates:
     *  Constant: '<S10>/PG_CtrlMode_Start3'
     *  Constant: '<S24>/Constant2'
     *  RelationalOperator: '<S24>/Relational Operator1'
     */
    /* Gateway: CLM/AirStart/Start_OpenLoop */
    /* During: CLM/AirStart/Start_OpenLoop */
    /* Entry Internal: CLM/AirStart/Start_OpenLoop */
    /* Transition: '<S23>:41' */
    if (CYS_110WP_3_Control_DW.Start_A_h) {
      /* Transition: '<S23>:204' */
      if (CYS_110WP_3_Control_DW.CNT_Start_A >= 50.0F) {
        /* Transition: '<S23>:1347' */
        /* Transition: '<S23>:1349' */
        CYS_110WP_3_Control_DW.Start_A_h = false;
        CYS_110WP_3_Control_DW.Start_B_l = true;

        /* Transition: '<S23>:1350' */
      } else {
        /* Transition: '<S23>:469' */
        CYS_110WP_3_Control_B.Motor_Cycle_c = 100U;
        CYS_110WP_3_Control_B.Motor_Open_nq = rtb_Motor_Open_m;
        CYS_110WP_3_Control_B.Motor_Enable_p = 1U;
        CYS_110WP_3_Control_B.Eblast_Cycle_b = 30U;
        CYS_110WP_3_Control_B.Eblast_Open_n = 30U;
        CYS_110WP_3_Control_B.Eblast_Enable_k = 1U;
        CYS_110WP_3_Control_B.EValve_Cycle_js = 30U;
        CYS_110WP_3_Control_B.EValve_Open_jc = 30U;
        CYS_110WP_3_Control_B.EValve_Enable_ot = 1U;
      }

      /* Transition: '<S23>:470' */
      CYS_110WP_3_Control_DW.CNT_Start_A++;
    } else {
      /* Transition: '<S23>:464' */
    }

    /* Transition: '<S23>:214' */
    if (CYS_110WP_3_Control_DW.Start_B_l) {
      /* Transition: '<S23>:471' */
      if (CYS_110WP_3_Control_B.Product5_c >= 1000.0F) {
        /* Transition: '<S23>:475' */
        /* Transition: '<S23>:480' */
        CYS_110WP_3_Control_DW.Start_B_l = false;
        CYS_110WP_3_Control_DW.Start_C_o = true;
        CYS_110WP_3_Control_B.SWO_Firework_p = 1U;
        CYS_110WP_3_Control_B.Accelerator_e = 5000.0F;

        /* Transition: '<S23>:948' */
        /* Transition: '<S23>:1078' */
      } else {
        /* Transition: '<S23>:1000' */
        if (CYS_110WP_3_Control_DW.CNT_Start_B_h >= 300.0F) {
          /* Transition: '<S23>:999' */
          /* Transition: '<S23>:477' */
          CYS_110WP_3_Control_B.Flag_EngineState = 4U;
          CYS_110WP_3_Control_B.Motor_Open_nq = 0U;

          /* Transition: '<S23>:1078' */
        } else {
          /* Transition: '<S23>:1069' */
        }
      }

      /* Transition: '<S23>:478' */
      CYS_110WP_3_Control_DW.CNT_Start_B_h++;
    } else {
      /* Transition: '<S23>:473' */
    }

    /* Transition: '<S23>:216' */
    if (CYS_110WP_3_Control_DW.Start_C_o) {
      /* Transition: '<S23>:495' */
      if ((CYS_110WP_3_Control_DW.CNT_Start_C_l > 150.0F) ||
          (CYS_110WP_3_Control_B.SumofElements1_er -
           CYS_110WP_3_Control_B.Switch_e >= 50.0F)) {
        /* Transition: '<S23>:1157' */
        /* Transition: '<S23>:1160' */
        CYS_110WP_3_Control_B.EValve_Cycle_js = 30U;
        CYS_110WP_3_Control_B.EValve_Open_jc = 0U;
        CYS_110WP_3_Control_B.EValve_Enable_ot = 0U;
        CYS_110WP_3_Control_B.Accelerator_e = CYS_110WP_3_Control_B.T4_X3_Y3;
        if ((CYS_110WP_3_Control_DW.CNT_Start_C1_d >= 500.0F) ||
            ((CYS_110WP_3_Control_B.Product5_c >= 6000.0F) &&
             (CYS_110WP_3_Control_DW.CNT_Start_C1_d > 100.0F))) {
          /* Transition: '<S23>:943' */
          if (CYS_110WP_3_Control_B.X_Out_a <= 70.0F) {
            /* Transition: '<S23>:1376' */
            if (CYS_110WP_3_Control_B.Motor_Open_nq >= 100) {
              /* Transition: '<S23>:1382' */
              /* Transition: '<S23>:1383' */
              CYS_110WP_3_Control_DW.Start_C_o = false;
              CYS_110WP_3_Control_DW.Start_D = true;
              CYS_110WP_3_Control_B.Motor_Open_nq = 100U;

              /* Transition: '<S23>:1384' */
            } else {
              /* Transition: '<S23>:1377' */
              CYS_110WP_3_Control_B.EValve_Cycle_js = 30U;
              CYS_110WP_3_Control_B.EValve_Open_jc = 0U;
              CYS_110WP_3_Control_B.EValve_Enable_ot = 0U;
              CYS_110WP_3_Control_B.Motor_Open_nq = (uint16_T)((real32_T)(100 -
                rtb_Motor_Open_m) / 500.0F + (real32_T)
                CYS_110WP_3_Control_B.Motor_Open_nq);
            }

            /* Transition: '<S23>:1378' */
          } else {
            /* Transition: '<S23>:1144' */
            CYS_110WP_3_Control_DW.Start_C_o = false;
            CYS_110WP_3_Control_DW.Start_D = true;
            CYS_110WP_3_Control_B.EValve_Cycle_js = 30U;
            CYS_110WP_3_Control_B.EValve_Open_jc = 0U;
            CYS_110WP_3_Control_B.EValve_Enable_ot = 0U;
            CYS_110WP_3_Control_B.Motor_Open_nq = 100U;
          }

          /* Transition: '<S23>:1179' */
          /* Transition: '<S23>:1340' */
        } else {
          /* Transition: '<S23>:1338' */
          CYS_110WP_3_Control_DW.CNT_Start_C1_d++;
        }

        /* Transition: '<S23>:1159' */
      } else {
        /* Transition: '<S23>:1335' */
        /* Transition: '<S23>:1184' */
      }

      /* Transition: '<S23>:947' */
      CYS_110WP_3_Control_DW.CNT_Start_C_l++;
    } else {
      /* Transition: '<S23>:578' */
    }

    /* Transition: '<S23>:586' */
    if (CYS_110WP_3_Control_DW.Start_D) {
      /* Transition: '<S23>:590' */
      if (CYS_110WP_3_Control_B.Product5_c > 8000.0F) {
        /* Transition: '<S23>:861' */
        /* Transition: '<S23>:804' */
        CYS_110WP_3_Control_DW.Start_D = false;
        CYS_110WP_3_Control_DW.Start_E = true;

        /* Transition: '<S23>:1169' */
        /* Transition: '<S23>:1195' */
        /* Transition: '<S23>:950' */
      } else {
        /* Transition: '<S23>:1193' */
        /* Transition: '<S23>:1167' */
        if (CYS_110WP_3_Control_DW.CNT_Start_D > 1000.0F) {
          /* Transition: '<S23>:1171' */
          /* Transition: '<S23>:1172' */
          CYS_110WP_3_Control_B.SWO_Firework_p = 0U;
          CYS_110WP_3_Control_B.Flag_EngineState = 15U;
          CYS_110WP_3_Control_B.Accelerator_e = 0.0F;

          /* Transition: '<S23>:950' */
        } else {
          /* Transition: '<S23>:862' */
        }
      }

      /* Transition: '<S23>:593' */
      CYS_110WP_3_Control_DW.CNT_Start_D++;
    } else {
      /* Transition: '<S23>:493' */
    }

    /* Transition: '<S23>:622' */
    if (CYS_110WP_3_Control_DW.Start_E) {
      /* Transition: '<S23>:625' */
      if ((CYS_110WP_3_Control_B.Product5_c > 20000.0F) &&
          (CYS_110WP_3_Control_DW.CNT_Start_E > 50.0F)) {
        /* Transition: '<S23>:1250' */
        /* Transition: '<S23>:1253' */
        CYS_110WP_3_Control_DW.Start_E = false;
        CYS_110WP_3_Control_DW.Start_F = true;
        CYS_110WP_3_Control_B.Motor_Cycle_c = 100U;
        CYS_110WP_3_Control_B.Motor_Open_nq = 0U;
        CYS_110WP_3_Control_B.Motor_Enable_p = 0U;
        CYS_110WP_3_Control_B.SWO_Firework_p = 0U;
        CYS_110WP_3_Control_B.Accelerator_e = CYS_110WP_3_Control_B.m2_j;

        /* Transition: '<S23>:1245' */
        /* Transition: '<S23>:1241' */
        /* Transition: '<S23>:1258' */
        /* Transition: '<S23>:1320' */
        /* Transition: '<S23>:1230' */
        /* Transition: '<S23>:1223' */
      } else {
        /* Transition: '<S23>:1310' */
        if (CYS_110WP_3_Control_B.SumofElements1_er > 700.0F) {
          /* Transition: '<S23>:1227' */
          /* Transition: '<S23>:1229' */
          if (CYS_110WP_3_Control_DW.CNT_POilHigh > 100.0F) {
            /* Transition: '<S23>:1243' */
            /* Transition: '<S23>:1242' */
            CYS_110WP_3_Control_B.Flag_EngineState = 15U;
            CYS_110WP_3_Control_B.Accelerator_e = 0.0F;

            /* Transition: '<S23>:1241' */
            /* Transition: '<S23>:1258' */
            /* Transition: '<S23>:1320' */
            /* Transition: '<S23>:1230' */
            /* Transition: '<S23>:1223' */
          } else {
            /* Transition: '<S23>:1238' */
            CYS_110WP_3_Control_DW.CNT_POilHigh++;

            /* Transition: '<S23>:1258' */
            /* Transition: '<S23>:1320' */
            /* Transition: '<S23>:1230' */
            /* Transition: '<S23>:1223' */
          }
        } else {
          /* Transition: '<S23>:1232' */
          if (CYS_110WP_3_Control_DW.CNT_Start_E > 1000.0F) {
            /* Transition: '<S23>:1260' */
            /* Transition: '<S23>:1261' */
            CYS_110WP_3_Control_B.Flag_EngineState = 15U;
            CYS_110WP_3_Control_B.Accelerator_e = 0.0F;

            /* Transition: '<S23>:1320' */
            /* Transition: '<S23>:1230' */
            /* Transition: '<S23>:1223' */
          } else {
            /* Transition: '<S23>:1317' */
            if (CYS_110WP_3_Control_B.Product5_c > 13000.0F) {
              /* Transition: '<S23>:1321' */
              /* Transition: '<S23>:1322' */
              CYS_110WP_3_Control_B.Motor_Cycle_c = 100U;
              CYS_110WP_3_Control_B.Motor_Open_nq = 0U;
              CYS_110WP_3_Control_B.Motor_Enable_p = 0U;
              CYS_110WP_3_Control_B.SWO_Firework_p = 0U;
            } else {
              /* Transition: '<S23>:1256' */
            }

            /* Transition: '<S23>:1324' */
            CYS_110WP_3_Control_B.Accelerator_e = (CYS_110WP_3_Control_B.m1_h -
              CYS_110WP_3_Control_B.T4_X3_Y3) * CYS_110WP_3_Control_B.Product5_c
              / 12000.0F + (CYS_110WP_3_Control_B.T4_X3_Y3 * 5.0F -
                            CYS_110WP_3_Control_B.m1_h * 2.0F) / 3.0F;
          }
        }
      }

      /* Transition: '<S23>:637' */
      CYS_110WP_3_Control_DW.CNT_Start_E++;
    } else {
      /* Transition: '<S23>:628' */
    }

    /* Transition: '<S23>:1136' */
    if (CYS_110WP_3_Control_DW.Start_F) {
      /* Transition: '<S23>:1269' */
      if ((CYS_110WP_3_Control_B.Product5_c > 28000.0F) ||
          (CYS_110WP_3_Control_DW.CNT_Start_F >= 1000.0F)) {
        /* Transition: '<S23>:1234' */
        /* Transition: '<S23>:1246' */
        CYS_110WP_3_Control_B.Eblast_Cycle_b = 30U;
        CYS_110WP_3_Control_B.Eblast_Open_n = 0U;
        CYS_110WP_3_Control_B.Eblast_Enable_k = 0U;
        if (CYS_110WP_3_Control_DW.CNT_EValve_Open > 150.0F) {
          /* Transition: '<S23>:1301' */
          /* Transition: '<S23>:1303' */
          CYS_110WP_3_Control_B.Flag_EngineState = 2U;

          /* Transition: '<S23>:1304' */
          /* Transition: '<S23>:1292' */
        } else {
          /* Transition: '<S23>:1300' */
          if (CYS_110WP_3_Control_DW.CNT_EValve_Open > 50.0F) {
            /* Transition: '<S23>:1289' */
            /* Transition: '<S23>:1291' */
            CYS_110WP_3_Control_B.EValve_Cycle_js = 30U;
            CYS_110WP_3_Control_B.EValve_Open_jc = 30U;
            CYS_110WP_3_Control_B.EValve_Enable_ot = 1U;
            CYS_110WP_3_Control_B.Accelerator_e = CYS_110WP_3_Control_B.m3_h;

            /* Transition: '<S23>:1292' */
          } else {
            /* Transition: '<S23>:1297' */
          }
        }

        /* Transition: '<S23>:1280' */
        CYS_110WP_3_Control_DW.CNT_EValve_Open++;

        /* Transition: '<S23>:1279' */
        /* Transition: '<S23>:1278' */
      } else {
        /* Transition: '<S23>:1270' */
        /* Transition: '<S23>:1272' */
        /* Transition: '<S23>:1275' */
      }

      /* Transition: '<S23>:1277' */
      CYS_110WP_3_Control_DW.CNT_Start_F++;
    } else {
      /* Transition: '<S23>:1266' */
    }

    /* End of Chart: '<S10>/Start_OpenLoop' */

    /* Chart: '<S10>/Range' incorporates:
     *  Constant: '<S10>/Constant5'
     *  Constant: '<S10>/Constant6'
     */
    /* Transition: '<S23>:1267' */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Accelerator_e, 5000.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_j);

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.AirStart_Accelerator =
      CYS_110WP_3_Control_B.sf_Range_j.Out;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Enable_f = CYS_110WP_3_Control_B.Motor_Enable_p;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.SWO_Firework_h = CYS_110WP_3_Control_B.SWO_Firework_p;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Flag_RunState = CYS_110WP_3_Control_B.Flag_EngineState;

    /* SignalConversion: '<S10>/Signal Conversion' incorporates:
     *  Constant: '<S19>/Constant'
     *  RelationalOperator: '<S19>/Compare'
     */
    CYS_110WP_3_Control_B.SWO_BleedAir_m = (uint8_T)
      (CYS_110WP_3_Control_B.Product5_c >= 5000.0F);

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Cycle_n4 =
      CYS_110WP_3_Control_B.EValve_Cycle_js;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Open_b = CYS_110WP_3_Control_B.EValve_Open_jc;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Cycle_l = CYS_110WP_3_Control_B.Eblast_Cycle_b;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Open_c = CYS_110WP_3_Control_B.Eblast_Open_n;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Cycle_j = CYS_110WP_3_Control_B.Motor_Cycle_c;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open_b = CYS_110WP_3_Control_B.Motor_Open_nq;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Enable_c =
      CYS_110WP_3_Control_B.EValve_Enable_ot;

    /* SignalConversion: '<S10>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Enable_o =
      CYS_110WP_3_Control_B.Eblast_Enable_k;

    /* Update for Delay: '<S20>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE = CYS_110WP_3_Control_B.Switch_e;

    /* Update for Delay: '<S24>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_o = CYS_110WP_3_Control_B.X_Out_a;

    /* Update for Delay: '<S24>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_f = rtb_Motor_Open_m;

    /* Update for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE = CYS_110WP_3_Control_B.T4_X3_Y3;

    /* Update for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE = CYS_110WP_3_Control_B.m1_h;

    /* Update for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE = CYS_110WP_3_Control_B.m2_j;

    /* Update for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE = CYS_110WP_3_Control_B.m3_h;

    /* End of Outputs for SubSystem: '<S1>/AirStart' */
    break;

   case 3:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/ClpControl' incorporates:
       *  InitializeConditions for ActionPort: '<S13>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S51>/Range1'
       *  InitializeConditions for Chart: '<S57>/Hold'
       *  InitializeConditions for Chart: '<S57>/M_Rate_Limiter'
       *  InitializeConditions for Chart: '<S65>/Range'
       *  InitializeConditions for Delay: '<S57>/Delay'
       *  InitializeConditions for UnitDelay: '<S51>/Time Delay8'
       */
      CYS_110WP_3_Control_DW.Delay_DSTATE = 0.0F;
      CYS_110WP_3_Control_Hold_c_Init(&CYS_110WP_3_Control_B.sf_Hold_g,
        &CYS_110WP_3_Control_DW.sf_Hold_g);
      CYS_110WP_3_M_Rate_Limiter_Init(&CYS_110WP_3_Control_B.sf_M_Rate_Limiter,
        &CYS_110WP_3_Control_DW.sf_M_Rate_Limiter);
      CYS_110WP_3_Control_DW.TimeDelay8_DSTATE = 0.0F;
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range1);
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_d);

      /* End of InitializeConditions for SubSystem: '<S1>/ClpControl' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/ClpControl' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 2U;

    /* Chart: '<S57>/Hold' incorporates:
     *  Constant: '<S13>/N1r_idle6'
     */
    CYS_110WP_3_Control_Hold_g(CYS_110WP_3_Control_B.Product5_c,
      &CYS_110WP_3_Control_B.sf_Hold_g, &CYS_110WP_3_Control_DW.sf_Hold_g);

    /* Switch: '<S59>/Switch' incorporates:
     *  Constant: '<S57>/Constant'
     *  Delay: '<S57>/Delay'
     *  RelationalOperator: '<S57>/Relational Operator'
     */
    if (CYS_110WP_3_Control_B.Product5_c > 0.0F) {
      CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_B.sf_Hold_g.Out;
    } else {
      CYS_110WP_3_Control_B.X_Out_a = CYS_110WP_3_Control_DW.Delay_DSTATE;
    }

    /* End of Switch: '<S59>/Switch' */

    /* Chart: '<S57>/M_Rate_Limiter' */
    CYS_110WP_3_Cont_M_Rate_Limiter(CYS_110WP_3_Control_B.X_Out_a,
      CYS_110WP_3_Control_B.Switch_g, &CYS_110WP_3_Control_B.sf_M_Rate_Limiter,
      &CYS_110WP_3_Control_DW.sf_M_Rate_Limiter);

    /* MinMax: '<S55>/MinMax' */
    if (CYS_110WP_3_Control_B.sf_M_Rate_Limiter.S_Dem_SpeedLoad_Limiter >=
        40000.0F) {
      CYS_110WP_3_Control_B.T4_X3_Y3 =
        CYS_110WP_3_Control_B.sf_M_Rate_Limiter.S_Dem_SpeedLoad_Limiter;
    } else {
      CYS_110WP_3_Control_B.T4_X3_Y3 = 40000.0F;
    }

    /* End of MinMax: '<S55>/MinMax' */

    /* Lookup_n-D: '<S56>/Ki Lookup Table' */
    CYS_110WP_3_Control_B.m2_j = look1_iflf_binlcapw
      (CYS_110WP_3_Control_B.Product5_c, CYS_110WP_3_Control_ConstP.pooled16,
       CYS_110WP_3_Control_ConstP.pooled15, 9U);

    /* Lookup_n-D: '<S56>/Ki Lookup Table1' */
    CYS_110WP_3_Control_B.m3_h = look1_iflf_binlcapw
      (CYS_110WP_3_Control_B.T4_X3_Y3, CYS_110WP_3_Control_ConstP.pooled16,
       CYS_110WP_3_Control_ConstP.pooled15, 9U);

    /* Lookup_n-D: '<S56>/Kp Lookup Table' */
    CYS_110WP_3_Control_B.m4_ex = look1_iflf_binlcapw
      (CYS_110WP_3_Control_B.Product5_c, CYS_110WP_3_Control_ConstP.pooled16,
       CYS_110WP_3_Control_ConstP.pooled17, 9U);

    /* Lookup_n-D: '<S56>/Kp Lookup Table1' */
    CYS_110WP_3_Control_B.m1_h = look1_iflf_binlcapw
      (CYS_110WP_3_Control_B.T4_X3_Y3, CYS_110WP_3_Control_ConstP.pooled16,
       CYS_110WP_3_Control_ConstP.pooled17, 9U);

    /* Sum: '<S51>/Sum1' */
    CYS_110WP_3_Control_B.T4_X3_Y3 -= CYS_110WP_3_Control_B.Product5_c;

    /* MinMax: '<S56>/Min1' */
    if ((CYS_110WP_3_Control_B.m4_ex <= CYS_110WP_3_Control_B.m1_h) || rtIsNaNF
        (CYS_110WP_3_Control_B.m1_h)) {
      CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_B.m4_ex;
    }

    /* MinMax: '<S56>/Min2' */
    if ((CYS_110WP_3_Control_B.m2_j <= CYS_110WP_3_Control_B.m3_h) || rtIsNaNF
        (CYS_110WP_3_Control_B.m3_h)) {
      CYS_110WP_3_Control_B.m3_h = CYS_110WP_3_Control_B.m2_j;
    }

    /* Product: '<S51>/Product1' incorporates:
     *  MinMax: '<S56>/Min1'
     *  MinMax: '<S56>/Min2'
     *  Product: '<S51>/Product2'
     *  Product: '<S51>/Product3'
     *  Sum: '<S51>/Sum of Elements'
     *  Sum: '<S51>/Sum3'
     *  UnitDelay: '<S51>/Time Delay8'
     */
    CYS_110WP_3_Control_B.m2_j = (CYS_110WP_3_Control_B.T4_X3_Y3 -
      CYS_110WP_3_Control_DW.TimeDelay8_DSTATE) * CYS_110WP_3_Control_B.m1_h +
      CYS_110WP_3_Control_B.T4_X3_Y3 * CYS_110WP_3_Control_B.m3_h;

    /* Chart: '<S51>/Range1' incorporates:
     *  Constant: '<S51>/dth = T0-288.3'
     *  Constant: '<S51>/dth = T0-288.5'
     */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Switch_e, 100.0F, 30.0F,
      &CYS_110WP_3_Control_B.sf_Range1);

    /* Product: '<S51>/Product4' incorporates:
     *  Constant: '<S51>/dth = T0-288.2'
     */
    CYS_110WP_3_Control_B.m1_h = CYS_110WP_3_Control_B.sf_Range1.Out / 100.0F;

    /* Product: '<S51>/Product11' incorporates:
     *  Constant: '<S51>/dth = T0-288.4'
     */
    CYS_110WP_3_Control_B.Switch_e = 10.0F * CYS_110WP_3_Control_B.m1_h;

    /* Product: '<S51>/Product5' incorporates:
     *  Constant: '<S51>/dth = T0-288.6'
     */
    CYS_110WP_3_Control_B.m1_h *= -10.0F;

    /* Chart: '<S51>/Range' */
    /* Gateway: CLM/ClpControl/CtrlLaw/Range */
    /* During: CLM/ClpControl/CtrlLaw/Range */
    /* Entry Internal: CLM/ClpControl/CtrlLaw/Range */
    /* Transition: '<S62>:5' */
    if (CYS_110WP_3_Control_B.m2_j <= CYS_110WP_3_Control_B.m1_h) {
      /* Transition: '<S62>:8' */
      /* Transition: '<S62>:12' */
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_B.m1_h;

      /* Transition: '<S62>:31' */
    } else {
      /* Transition: '<S62>:14' */
    }

    /* Transition: '<S62>:32' */
    if (CYS_110WP_3_Control_B.m2_j >= CYS_110WP_3_Control_B.Switch_e) {
      /* Transition: '<S62>:16' */
      /* Transition: '<S62>:18' */
      CYS_110WP_3_Control_B.m2_j = CYS_110WP_3_Control_B.Switch_e;

      /* Transition: '<S62>:28' */
    } else {
      /* Transition: '<S62>:21' */
    }

    /* End of Chart: '<S51>/Range' */

    /* Product: '<S53>/Product5' incorporates:
     *  Constant: '<S53>/constant4'
     */
    /* Transition: '<S62>:26' */
    CYS_110WP_3_Control_B.MathFunction1_g = CYS_110WP_3_Control_B.H_GPRS /
      1000.0;

    /* MATLAB Function: '<S53>/D9-Nr-T5r' incorporates:
     *  Constant: '<S53>/N1r_idle1'
     *  Constant: '<S53>/N1r_idle17'
     *  Constant: '<S53>/N1r_idle2'
     *  Constant: '<S53>/N1r_idle3'
     *  Constant: '<S53>/N1r_idle4'
     *  Constant: '<S53>/N1r_idle5'
     *  DataTypeConversion: '<S53>/Data Type Conversion1'
     */
    /* MATLAB Function 'CLM/ClpControl/Fault_Process/D9-Nr-T5r': '<S64>:1' */
    /* 利用转速（u1/rpm）、高度（u2/km）插值 */
    if ((real32_T)CYS_110WP_3_Control_B.MathFunction1_g < 5.0F) {
      /* '<S64>:1:4' */
      /* '<S64>:1:5' */
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_interp1
        (CYS_110WP_3_Control_ConstP.pooled22,
         CYS_110WP_3_Control_ConstP.N1r_idle1_Value,
         CYS_110WP_3_Control_B.Switch_g);

      /* '<S64>:1:6' */
      /* '<S64>:1:7' */
      CYS_110WP_3_Control_B.Switch_e += (CYS_110WP_3_Control_B.Switch_e -
        CYS_110WP_3_Control_interp1(CYS_110WP_3_Control_ConstP.pooled22,
        CYS_110WP_3_Control_ConstP.N1r_idle3_Value,
        CYS_110WP_3_Control_B.Switch_g)) / 5.0F * (0.0F - (real32_T)
        CYS_110WP_3_Control_B.MathFunction1_g);
    } else {
      /* '<S64>:1:10' */
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_interp1
        (CYS_110WP_3_Control_ConstP.pooled22,
         CYS_110WP_3_Control_ConstP.N1r_idle3_Value,
         CYS_110WP_3_Control_B.Switch_g);

      /* '<S64>:1:11' */
      /* '<S64>:1:12' */
      CYS_110WP_3_Control_B.Switch_e += (CYS_110WP_3_Control_B.Switch_e -
        CYS_110WP_3_Control_interp1(CYS_110WP_3_Control_ConstP.pooled22,
        CYS_110WP_3_Control_ConstP.N1r_idle5_Value,
        CYS_110WP_3_Control_B.Switch_g)) / 5.0F * (5.0F - (real32_T)
        CYS_110WP_3_Control_B.MathFunction1_g);
    }

    if ((real32_T)CYS_110WP_3_Control_B.MathFunction1_g < 0.0F) {
      /* '<S64>:1:15' */
      /* '<S64>:1:16' */
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_interp1
        (CYS_110WP_3_Control_ConstP.pooled22,
         CYS_110WP_3_Control_ConstP.N1r_idle1_Value,
         CYS_110WP_3_Control_B.Switch_g);
    }

    if ((real32_T)CYS_110WP_3_Control_B.MathFunction1_g > 11.0F) {
      /* '<S64>:1:18' */
      /* '<S64>:1:19' */
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_interp1
        (CYS_110WP_3_Control_ConstP.pooled22,
         CYS_110WP_3_Control_ConstP.N1r_idle5_Value,
         CYS_110WP_3_Control_B.Switch_g);
    }

    /* Chart: '<S65>/Range' incorporates:
     *  Constant: '<S55>/dth = T0-288.3'
     *  Constant: '<S55>/dth = T0-288.5'
     *  MATLAB Function: '<S53>/D9-Nr-T5r'
     */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Switch_e, 8000.0F, 700.0F,
      &CYS_110WP_3_Control_B.sf_Range_d);

    /* Outputs for Atomic SubSystem: '<Root>/FPM' */
    /* Switch: '<S66>/Switch' incorporates:
     *  Abs: '<S51>/Abs'
     *  Constant: '<S50>/Constant3'
     *  DataTypeConversion: '<S240>/Data Type Conversion3'
     *  DataTypeConversion: '<S240>/Data Type Conversion4'
     *  RelationalOperator: '<S51>/Relational Operator'
     *  Switch: '<S61>/Switch'
     *  Switch: '<S67>/Switch'
     */
    if (CYS_110WP_3_Control_B.sf_Timmer_ms_Lock.Out) {
      /* Switch: '<S69>/Switch' incorporates:
       *  Abs: '<S65>/Abs'
       *  Constant: '<S65>/Constant'
       *  RelationalOperator: '<S65>/Relational Operator'
       *  RelationalOperator: '<S65>/Relational Operator1'
       *  Sum: '<S65>/Sum3'
       *  Switch: '<S68>/Switch'
       *  UnitDelay: '<S1>/Time Delay2'
       */
      if ((real32_T)fabs(CYS_110WP_3_Control_B.sf_Range_d.Out -
                         CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE) < 20.0F) {
        /* SignalConversion: '<S13>/Signal Conversion' */
        CYS_110WP_3_Control_B.CloseLoop_Acclerator =
          CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
      } else if (CYS_110WP_3_Control_B.sf_Range_d.Out <
                 CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE) {
        /* Switch: '<S68>/Switch' incorporates:
         *  Constant: '<S53>/dth = T0-288.9'
         *  SignalConversion: '<S13>/Signal Conversion'
         *  Sum: '<S65>/Sum1'
         */
        CYS_110WP_3_Control_B.CloseLoop_Acclerator =
          CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE - 10.0F;
      } else {
        /* SignalConversion: '<S13>/Signal Conversion' incorporates:
         *  Constant: '<S53>/dth = T0-288.9'
         *  Sum: '<S65>/Sum2'
         *  Switch: '<S68>/Switch'
         */
        CYS_110WP_3_Control_B.CloseLoop_Acclerator =
          CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE + 10.0F;
      }

      /* End of Switch: '<S69>/Switch' */
    } else if (rtb_u_i) {
      /* Switch: '<S67>/Switch' incorporates:
       *  SignalConversion: '<S13>/Signal Conversion'
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.CloseLoop_Acclerator =
        CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
    } else if ((real32_T)fabs(CYS_110WP_3_Control_B.T4_X3_Y3) < 300.0F) {
      /* Switch: '<S61>/Switch' incorporates:
       *  SignalConversion: '<S13>/Signal Conversion'
       *  Switch: '<S67>/Switch'
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.CloseLoop_Acclerator =
        CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
    } else {
      /* SignalConversion: '<S13>/Signal Conversion' incorporates:
       *  Sum: '<S51>/Sum2'
       *  Switch: '<S61>/Switch'
       *  Switch: '<S67>/Switch'
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.CloseLoop_Acclerator =
        CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE + CYS_110WP_3_Control_B.m2_j;
    }

    /* End of Switch: '<S66>/Switch' */
    /* End of Outputs for SubSystem: '<Root>/FPM' */

    /* SignalConversion: '<S13>/Signal Conversion' incorporates:
     *  Constant: '<S55>/dth = T0-288.3'
     */
    CYS_110WP_3_Control_B.CloseLoopMin = 700.0F;

    /* SignalConversion: '<S13>/Signal Conversion' incorporates:
     *  Constant: '<S55>/dth = T0-288.5'
     */
    CYS_110WP_3_Control_B.CloseLoopMax = 8000.0F;

    /* SignalConversion: '<S13>/Signal Conversion' incorporates:
     *  Constant: '<S52>/Constant'
     *  RelationalOperator: '<S52>/Compare'
     */
    CYS_110WP_3_Control_B.SWO_BleedAir_j = (uint8_T)
      (CYS_110WP_3_Control_B.Product5_c >= 5000.0F);

    /* Update for Delay: '<S57>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE = CYS_110WP_3_Control_B.X_Out_a;

    /* Update for UnitDelay: '<S51>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE = CYS_110WP_3_Control_B.T4_X3_Y3;

    /* End of Outputs for SubSystem: '<S1>/ClpControl' */
    break;

   case 4:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Stop' incorporates:
       *  InitializeConditions for ActionPort: '<S18>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S18>/Stop_Control'
       */
      CYS_110WP_3_Control_DW.CNT_Wait = 0U;
      CYS_110WP_3_Control_DW.CNT_Motor = 0U;
      CYS_110WP_3_Control_B.Accelerator_k = 0.0F;
      CYS_110WP_3_Control_B.EValve_Open_j = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_m = 0U;
      CYS_110WP_3_Control_B.Motor_Open_pv = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_d = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_e = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_e = 0U;
      CYS_110WP_3_Control_B.StopFinish_l = 0U;

      /* End of InitializeConditions for SubSystem: '<S1>/Stop' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Stop' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 4U;

    /* Chart: '<S18>/Stop_Control' incorporates:
     *  Constant: '<S127>/Constant'
     *  Constant: '<S18>/N1r_idle6'
     *  Constant: '<S18>/PG_CtrlMode_Start3'
     *  RelationalOperator: '<S127>/Compare'
     *  UnitDelay: '<S1>/Time Delay3'
     */
    /* Gateway: CLM/Stop/Stop_Control */
    /* During: CLM/Stop/Stop_Control */
    /* Entry Internal: CLM/Stop/Stop_Control */
    /* Transition: '<S126>:949' */
    rtb_u_i = false;
    rtb_LogicalOperator_fe = false;
    rtb_LogicalOperator_pb = false;
    if (rtb_Switch_gc == 15) {
      /* Transition: '<S126>:999' */
      /* Transition: '<S126>:1001' */
      CYS_110WP_3_Control_B.StopFinish_l = 1U;
      CYS_110WP_3_Control_B.Motor_Open_pv = 0U;

      /* Transition: '<S126>:1002' */
      guard4 = true;
    } else {
      /* Transition: '<S126>:957' */
      if (CYS_110WP_3_Control_B.Flag_RunState_f != 4) {
        /* Transition: '<S126>:959' */
        if (CYS_110WP_3_Control_DW.CNT_Wait >= 50.0F) {
          /* Transition: '<S126>:965' */
          /* Transition: '<S126>:968' */
          CYS_110WP_3_Control_B.EValve_Enable_d = 0U;
          CYS_110WP_3_Control_B.Eblast_Enable_e = 0U;
          CYS_110WP_3_Control_B.EValve_Open_j = 0U;
          CYS_110WP_3_Control_B.Eblast_Open_m = 0U;
        } else {
          /* Transition: '<S126>:964' */
          CYS_110WP_3_Control_B.Accelerator_k = 0.0F;
          CYS_110WP_3_Control_B.EValve_Enable_d = 1U;
          CYS_110WP_3_Control_B.EValve_Open_j = 30U;
          CYS_110WP_3_Control_B.Eblast_Enable_e = 1U;
          CYS_110WP_3_Control_B.Eblast_Open_m = 30U;
        }

        if ((CYS_110WP_3_Control_B.Product5_c <= 7000.0F) &&
            (CYS_110WP_3_Control_B.KpLookupTable1 >= 100.0F)) {
          /* Transition: '<S126>:980' */
          if (CYS_110WP_3_Control_DW.CNT_Motor >= 750.0F) {
            /* Transition: '<S126>:976' */
            /* Transition: '<S126>:977' */
            CYS_110WP_3_Control_B.StopFinish_l = 1U;
            CYS_110WP_3_Control_B.Motor_Open_pv = 0U;
            guard4 = true;
          } else {
            /* Transition: '<S126>:985' */
            CYS_110WP_3_Control_B.Motor_Open_pv = 50U;
            CYS_110WP_3_Control_DW.CNT_Motor++;
            rtb_LogicalOperator_pb = true;
          }
        } else {
          /* Transition: '<S126>:991' */
          if ((CYS_110WP_3_Control_B.KpLookupTable1 <= 100.0F) ||
              (CYS_110WP_3_Control_B.Product5_c <= 7000.0F)) {
            /* Transition: '<S126>:993' */
            /* Transition: '<S126>:996' */
            CYS_110WP_3_Control_B.StopFinish_l = 1U;
            CYS_110WP_3_Control_B.Motor_Open_pv = 0U;
            rtb_LogicalOperator_fe = true;
          } else {
            /* Transition: '<S126>:982' */
            rtb_u_i = true;
          }
        }
      } else {
        /* Transition: '<S126>:951' */
        CYS_110WP_3_Control_B.StopFinish_l = 1U;
        CYS_110WP_3_Control_B.Motor_Open_pv = 0U;
      }
    }

    if (guard4) {
      /* Transition: '<S126>:988' */
      rtb_LogicalOperator_pb = true;
    }

    if (rtb_LogicalOperator_pb) {
      /* Transition: '<S126>:995' */
      rtb_LogicalOperator_fe = true;
    }

    if (rtb_LogicalOperator_fe) {
      /* Transition: '<S126>:984' */
      rtb_u_i = true;
    }

    if (rtb_u_i) {
      /* Transition: '<S126>:911' */
      CYS_110WP_3_Control_DW.CNT_Wait++;
    }

    /* End of Chart: '<S18>/Stop_Control' */

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/PG_CtrlMode_Start1'
     *  Product: '<S18>/Divide'
     */
    /* Transition: '<S126>:953' */
    CYS_110WP_3_Control_B.Accelerator_p = CYS_110WP_3_Control_P.PF_ACCFULLRANGE *
      CYS_110WP_3_Control_B.Accelerator_k;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Enable_h = CYS_110WP_3_Control_B.Motor_Enable_e;

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/Constant8'
     */
    CYS_110WP_3_Control_B.SWO_Firework_a = 0U;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.StopFinish = CYS_110WP_3_Control_B.StopFinish_l;

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/Constant4'
     */
    CYS_110WP_3_Control_B.SWO_BleedAIr = 0U;

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/Constant1'
     */
    CYS_110WP_3_Control_B.EValve_Cycle_n = 30U;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Open_h = CYS_110WP_3_Control_B.EValve_Open_j;

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/Constant3'
     */
    CYS_110WP_3_Control_B.Eblast_Cycle_d = 30U;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Open_d = CYS_110WP_3_Control_B.Eblast_Open_m;

    /* SignalConversion: '<S18>/Signal Conversion' incorporates:
     *  Constant: '<S18>/Constant7'
     */
    CYS_110WP_3_Control_B.Motor_Cycle_a = 100U;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open_pl = CYS_110WP_3_Control_B.Motor_Open_pv;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Enable_ol =
      CYS_110WP_3_Control_B.EValve_Enable_d;

    /* SignalConversion: '<S18>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Enable_ae =
      CYS_110WP_3_Control_B.Eblast_Enable_e;

    /* End of Outputs for SubSystem: '<S1>/Stop' */
    break;

   case 5:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Manual' incorporates:
       *  InitializeConditions for ActionPort: '<S15>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S83>/Range'
       *  InitializeConditions for Chart: '<S85>/Range'
       *  InitializeConditions for Chart: '<S86>/Range'
       *  InitializeConditions for Chart: '<S87>/Range'
       *  InitializeConditions for Chart: '<S95>/Hold_500ms'
       *  InitializeConditions for Delay: '<S95>/Delay'
       *  InitializeConditions for UnitDelay: '<S83>/Time Delay1'
       *  InitializeConditions for UnitDelay: '<S83>/Time Delay8'
       *  InitializeConditions for UnitDelay: '<S84>/Time Delay8'
       *  InitializeConditions for UnitDelay: '<S87>/Time Delay1'
       *  InitializeConditions for UnitDelay: '<S87>/Time Delay8'
       */
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_h);
      CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_i = false;
      CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_g = 0U;
      CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_p = 0U;
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_jg);
      CYS_110WP_3_Control_DW.Delay_DSTATE_fm = false;
      CYS_110WP_3_Con_Hold_500ms_Init(&CYS_110WP_3_Control_B.sf_Hold_500ms,
        &CYS_110WP_3_Control_DW.sf_Hold_500ms);
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_o);
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_ow);
      CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_j = false;
      CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_gl = 0U;

      /* End of InitializeConditions for SubSystem: '<S1>/Manual' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Manual' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 3U;

    /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
    /* Switch: '<S88>/Switch' incorporates:
     *  Constant: '<S15>/N1r_idle6'
     *  Inport: '<Root>/Flag_rx_suc'
     *  Logic: '<S82>/Logical Operator'
     *  RelationalOperator: '<S82>/Relational Operator1'
     */
    if ((14 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  Constant: '<S82>/Constant8'
       *  DataTypeConversion: '<S82>/Data Type Conversion1'
       *  Inport: '<Root>/MyUsart2_Rxdata'
       *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
       *  RelationalOperator: '<S82>/Relational Operator2'
       */
      CYS_110WP_3_Control_B.SWO_BleedAir_e = (uint8_T)(arg_MyUsart2_Rxdata[5] >=
        1);
    } else {
      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.SWO_BleedAir_e =
        CYS_110WP_3_Control_DW.TimeDelay2_11_DSTATE;
    }

    /* End of Switch: '<S88>/Switch' */

    /* Product: '<S83>/Product3' incorporates:
     *  Constant: '<S83>/Constant2'
     *  Constant: '<S83>/Constant7'
     *  DataTypeConversion: '<S83>/Data Type Conversion2'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     */
    CYS_110WP_3_Control_B.Switch_e = (real32_T)arg_MyUsart2_Rxdata[5] / 100.0F *
      30.0F;

    /* End of Outputs for SubSystem: '<S2>/CMMRead' */
    /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

    /* Chart: '<S83>/Range' incorporates:
     *  Constant: '<S83>/Constant1'
     *  Constant: '<S83>/Constant3'
     */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Switch_e, 30.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_h);

    /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
    /* Switch: '<S90>/Switch' incorporates:
     *  Constant: '<S83>/Constant8'
     *  DataTypeConversion: '<S83>/Data Type Conversion1'
     *  Inport: '<Root>/Flag_rx_suc'
     *  Logic: '<S83>/Logical Operator'
     *  RelationalOperator: '<S83>/Relational Operator1'
     *  RelationalOperator: '<S83>/Relational Operator2'
     *  Switch: '<S89>/Switch'
     *  UnitDelay: '<S83>/Time Delay1'
     *  UnitDelay: '<S83>/Time Delay8'
     */
    if ((12 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      rtb_u_i = (CYS_110WP_3_Control_B.Switch_e >= 1.0F);

      /* DataTypeConversion: '<S83>/Data Type Conversion1' incorporates:
       *  Constant: '<S83>/Constant8'
       *  RelationalOperator: '<S83>/Relational Operator2'
       */
      CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
        (CYS_110WP_3_Control_B.sf_Range_h.Out);
      if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
          (CYS_110WP_3_Control_B.T4_X3_Y3)) {
        CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
      } else {
        CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
          (CYS_110WP_3_Control_B.T4_X3_Y3, 65536.0F);
      }

      rtb_Motor_Open_m = (uint16_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
        (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.T4_X3_Y3 :
        (int32_T)(uint16_T)CYS_110WP_3_Control_B.T4_X3_Y3);
    } else {
      rtb_u_i = CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_i;
      rtb_Motor_Open_m = CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_g;
    }

    /* End of Switch: '<S90>/Switch' */

    /* Switch: '<S92>/Switch' incorporates:
     *  Constant: '<S84>/Constant8'
     *  DataTypeConversion: '<S84>/Data Type Conversion1'
     *  Inport: '<Root>/Flag_rx_suc'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     *  Logic: '<S84>/Logical Operator'
     *  RelationalOperator: '<S84>/Relational Operator1'
     *  RelationalOperator: '<S84>/Relational Operator2'
     *  UnitDelay: '<S84>/Time Delay8'
     */
    if ((10 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      rtb_Flag_RunState = (uint8_T)(arg_MyUsart2_Rxdata[5] >= 1);
    } else {
      rtb_Flag_RunState = CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_p;
    }

    /* End of Switch: '<S92>/Switch' */

    /* Chart: '<S85>/Range' incorporates:
     *  Constant: '<S85>/Constant1'
     *  Constant: '<S85>/Constant3'
     *  DataTypeConversion: '<S85>/Data Type Conversion2'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     */
    CYS_110WP_3_Control_Range((real32_T)arg_MyUsart2_Rxdata[5], 70.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_jg);

    /* End of Outputs for SubSystem: '<S2>/CMMRead' */
    /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

    /* Sum: '<S96>/Sum1' incorporates:
     *  Constant: '<S96>/Constant2'
     *  UnitDelay: '<S1>/Time Delay2'
     */
    CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE
      - 100.0F;

    /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
    /* Logic: '<S95>/Logical Operator2' incorporates:
     *  Inport: '<Root>/Flag_rx_suc'
     *  Logic: '<S95>/Logical Operator'
     *  Logic: '<S95>/Logical Operator1'
     *  RelationalOperator: '<S95>/Relational Operator1'
     *  RelationalOperator: '<S95>/Relational Operator2'
     */
    rtb_LogicalOperator_fe = ((((rtb_Switch_gc == 4) || (rtb_Switch_gc == 5)) &&
      (*arg_Flag_rx_suc != 0)) || (rtb_Compare_pr != 0));

    /* Switch: '<S93>/Switch' incorporates:
     *  Constant: '<S85>/Constant2'
     *  Constant: '<S85>/Constant5'
     *  Delay: '<S95>/Delay'
     *  Inport: '<Root>/Flag_rx_suc'
     *  Logic: '<S85>/Logical Operator'
     *  Product: '<S85>/Product2'
     *  RelationalOperator: '<S85>/Relational Operator1'
     *  Switch: '<S98>/Switch'
     *  Switch: '<S99>/Switch'
     */
    if ((8 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      CYS_110WP_3_Control_B.Switch_e = 10000.0F *
        CYS_110WP_3_Control_B.sf_Range_jg.Out / 100.0F;
    } else if (CYS_110WP_3_Control_DW.Delay_DSTATE_fm) {
      /* Switch: '<S98>/Switch' incorporates:
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.Switch_e =
        CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
    } else if (rtb_LogicalOperator_fe) {
      /* Switch: '<S101>/Switch' incorporates:
       *  Switch: '<S98>/Switch'
       *  Switch: '<S99>/Switch'
       */
      if (rtb_Compare_pr == 0) {
        /* Switch: '<S102>/Switch' incorporates:
         *  Constant: '<S96>/Constant2'
         *  RelationalOperator: '<S96>/Relational Operator1'
         *  RelationalOperator: '<S96>/Relational Operator2'
         *  Sum: '<S96>/Sum'
         *  Switch: '<S100>/Switch'
         *  UnitDelay: '<S1>/Time Delay2'
         */
        if (rtb_Switch_gc == 4) {
          CYS_110WP_3_Control_B.Switch_e =
            CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE + 100.0F;
        } else {
          if (rtb_Switch_gc != 5) {
            CYS_110WP_3_Control_B.Switch_e =
              CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
          }
        }

        /* End of Switch: '<S102>/Switch' */
      }

      /* End of Switch: '<S101>/Switch' */
    } else {
      /* Switch: '<S99>/Switch' incorporates:
       *  Switch: '<S98>/Switch'
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.Switch_e =
        CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE;
    }

    /* End of Switch: '<S93>/Switch' */
    /* End of Outputs for SubSystem: '<S2>/CMMRead' */
    /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

    /* Chart: '<S95>/Hold_500ms' incorporates:
     *  Constant: '<S95>/dth = T0-288.24'
     */
    CYS_110WP_3_Control_Hold_500ms(rtb_LogicalOperator_fe, 500.0F,
      &CYS_110WP_3_Control_B.sf_Hold_500ms,
      &CYS_110WP_3_Control_DW.sf_Hold_500ms);

    /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
    /* Product: '<S86>/Product3' incorporates:
     *  Constant: '<S86>/Constant2'
     *  Constant: '<S86>/Constant7'
     *  DataTypeConversion: '<S86>/Data Type Conversion2'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     */
    CYS_110WP_3_Control_B.X_Out_a = (real32_T)arg_MyUsart2_Rxdata[5] / 100.0F *
      30.0F;

    /* End of Outputs for SubSystem: '<S2>/CMMRead' */
    /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

    /* Chart: '<S86>/Range' incorporates:
     *  Constant: '<S86>/Constant1'
     *  Constant: '<S86>/Constant3'
     */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.X_Out_a, 30.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_o);

    /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* Outputs for Atomic SubSystem: '<S2>/CMMRead' */
    /* Switch: '<S103>/Switch' incorporates:
     *  Inport: '<Root>/Flag_rx_suc'
     *  Logic: '<S86>/Logical Operator'
     *  RelationalOperator: '<S86>/Relational Operator1'
     *  Switch: '<S104>/Switch'
     */
    if ((11 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      /* DataTypeConversion: '<S86>/Data Type Conversion1' */
      CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
        (CYS_110WP_3_Control_B.sf_Range_o.Out);
      if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
          (CYS_110WP_3_Control_B.T4_X3_Y3)) {
        CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
      } else {
        CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
          (CYS_110WP_3_Control_B.T4_X3_Y3, 65536.0F);
      }

      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  DataTypeConversion: '<S86>/Data Type Conversion1'
       */
      CYS_110WP_3_Control_B.EValve_Open_a = (uint16_T)
        (CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ? (int32_T)(uint16_T)-(int16_T)
         (uint16_T)-CYS_110WP_3_Control_B.T4_X3_Y3 : (int32_T)(uint16_T)
         CYS_110WP_3_Control_B.T4_X3_Y3);

      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  Constant: '<S86>/Constant8'
       *  RelationalOperator: '<S86>/Relational Operator2'
       */
      CYS_110WP_3_Control_B.EValve_Enable_k = (uint8_T)
        (CYS_110WP_3_Control_B.X_Out_a >= 1.0F);
    } else {
      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.EValve_Open_a =
        CYS_110WP_3_Control_DW.TimeDelay2_2_DSTATE;

      /* SignalConversion: '<S15>/Signal Conversion' incorporates:
       *  UnitDelay: '<S1>/Time Delay2'
       */
      CYS_110WP_3_Control_B.EValve_Enable_k =
        CYS_110WP_3_Control_DW.TimeDelay2_7_DSTATE;
    }

    /* End of Switch: '<S103>/Switch' */

    /* Chart: '<S87>/Range' incorporates:
     *  Constant: '<S87>/Constant1'
     *  Constant: '<S87>/Constant3'
     *  DataTypeConversion: '<S87>/Data Type Conversion2'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     */
    CYS_110WP_3_Control_Range((real32_T)arg_MyUsart2_Rxdata[5], 100.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_ow);

    /* Switch: '<S107>/Switch' incorporates:
     *  Constant: '<S87>/Constant8'
     *  DataTypeConversion: '<S87>/Data Type Conversion1'
     *  Inport: '<Root>/Flag_rx_suc'
     *  Inport: '<Root>/MyUsart2_Rxdata'
     *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
     *  Logic: '<S87>/Logical Operator'
     *  RelationalOperator: '<S87>/Relational Operator1'
     *  RelationalOperator: '<S87>/Relational Operator2'
     *  Switch: '<S106>/Switch'
     *  UnitDelay: '<S87>/Time Delay1'
     *  UnitDelay: '<S87>/Time Delay8'
     */
    if ((13 == rtb_Switch_gc) && (*arg_Flag_rx_suc != 0)) {
      rtb_LogicalOperator_fe = (arg_MyUsart2_Rxdata[5] >= 1);

      /* DataTypeConversion: '<S87>/Data Type Conversion1' incorporates:
       *  Constant: '<S87>/Constant8'
       *  Inport: '<Root>/MyUsart2_Rxdata'
       *  Inport: '<S128>/S_PF_MyUsart2_Rxdata'
       *  RelationalOperator: '<S87>/Relational Operator2'
       */
      CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
        (CYS_110WP_3_Control_B.sf_Range_ow.Out);
      if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
          (CYS_110WP_3_Control_B.T4_X3_Y3)) {
        CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
      } else {
        CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
          (CYS_110WP_3_Control_B.T4_X3_Y3, 65536.0F);
      }

      rtb_Switch_o3 = (uint16_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
        (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.T4_X3_Y3 :
        (int32_T)(uint16_T)CYS_110WP_3_Control_B.T4_X3_Y3);
    } else {
      rtb_LogicalOperator_fe = CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_j;
      rtb_Switch_o3 = CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_gl;
    }

    /* End of Switch: '<S107>/Switch' */
    /* End of Outputs for SubSystem: '<S2>/CMMRead' */
    /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

    /* SignalConversion: '<S15>/Signal Conversion' */
    CYS_110WP_3_Control_B.Manual_Accelerator = CYS_110WP_3_Control_B.Switch_e;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  Constant: '<S87>/Constant5'
     */
    CYS_110WP_3_Control_B.Motor_Cycle_d = 100U;

    /* SignalConversion: '<S15>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open_p = rtb_Switch_o3;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  DataTypeConversion: '<S87>/Data Type Conversion3'
     */
    CYS_110WP_3_Control_B.Motor_Enable_i = rtb_LogicalOperator_fe;

    /* SignalConversion: '<S15>/Signal Conversion' */
    CYS_110WP_3_Control_B.SWO_Firework_f = rtb_Flag_RunState;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  Constant: '<S85>/Constant4'
     */
    CYS_110WP_3_Control_B.ManualAcc_Min = 0.0F;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  Constant: '<S85>/Constant6'
     */
    CYS_110WP_3_Control_B.ManualAcc_Max = 15000.0F;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  Constant: '<S86>/Constant5'
     */
    CYS_110WP_3_Control_B.EValve_Cycle_g = 30U;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  Constant: '<S83>/Constant5'
     */
    CYS_110WP_3_Control_B.Eblast_Cycle_g = 30U;

    /* SignalConversion: '<S15>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Open_p4 = rtb_Motor_Open_m;

    /* SignalConversion: '<S15>/Signal Conversion' incorporates:
     *  DataTypeConversion: '<S83>/Data Type Conversion3'
     */
    CYS_110WP_3_Control_B.Eblast_Enable_a = rtb_u_i;

    /* Update for UnitDelay: '<S83>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_i = rtb_u_i;

    /* Update for UnitDelay: '<S83>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_g = rtb_Motor_Open_m;

    /* Update for UnitDelay: '<S84>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_p = rtb_Flag_RunState;

    /* Update for Delay: '<S95>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_fm =
      CYS_110WP_3_Control_B.sf_Hold_500ms.Out;

    /* Update for UnitDelay: '<S87>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_j = rtb_LogicalOperator_fe;

    /* Update for UnitDelay: '<S87>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_gl = rtb_Switch_o3;

    /* End of Outputs for SubSystem: '<S1>/Manual' */
    break;

   case 6:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/BWStart' incorporates:
       *  InitializeConditions for ActionPort: '<S12>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  InitializeConditions for Chart: '<S12>/BWStart_OpenLoop'
       *  InitializeConditions for Chart: '<S12>/Range'
       *  InitializeConditions for Chart: '<S46>/Hold'
       *  InitializeConditions for UnitDelay: '<S12>/Time Delay1'
       */
      CYS_110WP_3_Control_Hold_i_Init(&CYS_110WP_3_Control_B.sf_Hold_h,
        &CYS_110WP_3_Control_DW.sf_Hold_h);
      CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_h = 0.0F;
      CYS_110WP_3_Control_DW.CNT_Start_C = 0U;
      CYS_110WP_3_Control_DW.CNT_Start_B = 0U;
      CYS_110WP_3_Control_DW.Start_A = true;
      CYS_110WP_3_Control_DW.Start_B = false;
      CYS_110WP_3_Control_DW.Start_C = false;
      CYS_110WP_3_Control_DW.CNT_Start_C1 = 0U;
      CYS_110WP_3_Control_B.Accelerator = 0.0F;
      CYS_110WP_3_Control_B.EValve_Cycle_j = 0U;
      CYS_110WP_3_Control_B.EValve_Open_c = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_j = 0U;
      CYS_110WP_3_Control_B.Eblast_Open_p = 0U;
      CYS_110WP_3_Control_B.Motor_Cycle_m = 0U;
      CYS_110WP_3_Control_B.Motor_Open_g = 0U;
      CYS_110WP_3_Control_B.EValve_Enable_o = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_j = 0U;
      CYS_110WP_3_Control_B.Motor_Enable_d = 0U;
      CYS_110WP_3_Control_B.SWO_Firework_l = 0U;
      CYS_110WP_3_Control_B.Flag_BWStartState_i = 0U;
      CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_p);

      /* End of InitializeConditions for SubSystem: '<S1>/BWStart' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/BWStart' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    CYS_110WP_3_Control_B.Merge = 6U;

    /* Chart: '<S46>/Hold' incorporates:
     *  Constant: '<S12>/PG_CtrlMode_Start'
     */
    CYS_110WP_3_Control_Hold_h(&CYS_110WP_3_Control_B.sf_Hold_h,
      &CYS_110WP_3_Control_DW.sf_Hold_h);

    /* If: '<S46>/If' incorporates:
     *  Constant: '<S49>/Constant6'
     *  Constant: '<S49>/Constant7'
     *  Inport: '<S48>/In4'
     *  UnitDelay: '<S12>/Time Delay1'
     */
    if (CYS_110WP_3_Control_B.sf_Hold_h.Out > 0) {
      /* Outputs for IfAction SubSystem: '<S46>/If Action Subsystem' incorporates:
       *  ActionPort: '<S48>/Action Port'
       */
      CYS_110WP_3_Control_B.Switch_e =
        CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_h;

      /* End of Outputs for SubSystem: '<S46>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S46>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S49>/Action Port'
       */
      /* Dynamic Look-Up Table Block: '<S49>/Lookup Table Dynamic3'
       * Input0  Data Type:  Floating Point real32_T
       * Input1  Data Type:  Floating Point real32_T
       * Input2  Data Type:  Floating Point real32_T
       * Output0 Data Type:  Floating Point real32_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUpEven_real32_T_real32_T( &(CYS_110WP_3_Control_B.LookupTableDynamic3),
        CYS_110WP_3_Control_ConstP.Constant6_Value_g,
        CYS_110WP_3_Control_B.SumofElements1_er, 50.0F, 1U, 50.0F);

      /* SignalConversion: '<S49>/OutportBufferForm4' incorporates:
       *  Constant: '<S49>/Constant6'
       *  Constant: '<S49>/Constant7'
       */
      CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_B.LookupTableDynamic3;

      /* End of Outputs for SubSystem: '<S46>/If Action Subsystem1' */
    }

    /* End of If: '<S46>/If' */

    /* Chart: '<S12>/BWStart_OpenLoop' incorporates:
     *  Constant: '<S12>/PG_CtrlMode_Start3'
     */
    /* Gateway: CLM/BWStart/BWStart_OpenLoop */
    /* During: CLM/BWStart/BWStart_OpenLoop */
    /* Entry Internal: CLM/BWStart/BWStart_OpenLoop */
    /* Transition: '<S42>:41' */
    if (CYS_110WP_3_Control_DW.Start_A) {
      /* Transition: '<S42>:204' */
      /* Transition: '<S42>:469' */
      CYS_110WP_3_Control_B.Motor_Open_g = 0U;
      CYS_110WP_3_Control_B.Eblast_Cycle_j = 30U;
      CYS_110WP_3_Control_B.Eblast_Open_p = 0U;
      CYS_110WP_3_Control_B.Eblast_Enable_j = 0U;
      CYS_110WP_3_Control_B.EValve_Cycle_j = 30U;
      CYS_110WP_3_Control_B.EValve_Open_c = 30U;
      CYS_110WP_3_Control_B.EValve_Enable_o = 1U;
      CYS_110WP_3_Control_B.SWO_Firework_l = 1U;

      /* Transition: '<S42>:1349' */
      CYS_110WP_3_Control_DW.Start_A = false;
      CYS_110WP_3_Control_DW.Start_B = true;

      /* Transition: '<S42>:1350' */
      /* Transition: '<S42>:470' */
    } else {
      /* Transition: '<S42>:464' */
    }

    /* Transition: '<S42>:214' */
    if (CYS_110WP_3_Control_DW.Start_B) {
      /* Transition: '<S42>:471' */
      if ((CYS_110WP_3_Control_B.Product5_c >= 7000.0F) &&
          (CYS_110WP_3_Control_B.KpLookupTable1 >= 100.0F)) {
        /* Transition: '<S42>:475' */
        /* Transition: '<S42>:480' */
        CYS_110WP_3_Control_DW.Start_B = false;
        CYS_110WP_3_Control_DW.Start_C = true;
        CYS_110WP_3_Control_B.SWO_Firework_l = 0U;
        CYS_110WP_3_Control_B.Accelerator = CYS_110WP_3_Control_B.Switch_e;

        /* Transition: '<S42>:948' */
        /* Transition: '<S42>:1078' */
      } else {
        /* Transition: '<S42>:1000' */
        if (CYS_110WP_3_Control_DW.CNT_Start_B >= 5000.0F) {
          /* Transition: '<S42>:999' */
          /* Transition: '<S42>:477' */
          CYS_110WP_3_Control_DW.CNT_Start_B = 0U;

          /* Transition: '<S42>:1078' */
        } else {
          /* Transition: '<S42>:1069' */
        }
      }

      /* Transition: '<S42>:478' */
      CYS_110WP_3_Control_DW.CNT_Start_B++;
    } else {
      /* Transition: '<S42>:473' */
    }

    /* Transition: '<S42>:216' */
    if (CYS_110WP_3_Control_DW.Start_C) {
      /* Transition: '<S42>:495' */
      if (CYS_110WP_3_Control_B.Product5_c >= 28000.0F) {
        /* Transition: '<S42>:1157' */
        /* Transition: '<S42>:1160' */
        CYS_110WP_3_Control_B.Flag_BWStartState_i = 2U;

        /* Transition: '<S42>:1381' */
        /* Transition: '<S42>:1374' */
        /* Transition: '<S42>:1159' */
      } else {
        /* Transition: '<S42>:1335' */
        if (CYS_110WP_3_Control_DW.CNT_Start_C > 1500.0F) {
          /* Transition: '<S42>:1376' */
          /* Transition: '<S42>:1379' */
          CYS_110WP_3_Control_B.Accelerator = 0.0F;
          if (CYS_110WP_3_Control_DW.CNT_Start_C1 > 100.0F) {
            /* Transition: '<S42>:1383' */
            /* Transition: '<S42>:1384' */
            CYS_110WP_3_Control_B.Accelerator = 0.0F;
            CYS_110WP_3_Control_B.Flag_BWStartState_i = 4U;
            CYS_110WP_3_Control_B.EValve_Open_c = 0U;

            /* Transition: '<S42>:1374' */
            /* Transition: '<S42>:1159' */
          } else {
            /* Transition: '<S42>:1377' */
            CYS_110WP_3_Control_DW.CNT_Start_C1++;

            /* Transition: '<S42>:1159' */
          }
        } else {
          /* Transition: '<S42>:1184' */
        }
      }

      /* Transition: '<S42>:947' */
      CYS_110WP_3_Control_DW.CNT_Start_C++;
    } else {
      /* Transition: '<S42>:578' */
    }

    /* End of Chart: '<S12>/BWStart_OpenLoop' */

    /* Chart: '<S12>/Range' incorporates:
     *  Constant: '<S12>/Constant5'
     *  Constant: '<S12>/Constant6'
     */
    /* Transition: '<S42>:1136' */
    CYS_110WP_3_Control_Range(CYS_110WP_3_Control_B.Accelerator, 5000.0F, 0.0F,
      &CYS_110WP_3_Control_B.sf_Range_p);

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.BWStart_Accelerator =
      CYS_110WP_3_Control_B.sf_Range_p.Out;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Enable = CYS_110WP_3_Control_B.Motor_Enable_d;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.SWO_Firework = CYS_110WP_3_Control_B.SWO_Firework_l;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Flag_BWStartState =
      CYS_110WP_3_Control_B.Flag_BWStartState_i;

    /* SignalConversion: '<S12>/Signal Conversion' incorporates:
     *  Constant: '<S43>/Constant'
     *  RelationalOperator: '<S43>/Compare'
     */
    CYS_110WP_3_Control_B.SWO_BleedAir = (uint8_T)
      (CYS_110WP_3_Control_B.Product5_c >= 5000.0F);

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Cycle = CYS_110WP_3_Control_B.EValve_Cycle_j;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Open = CYS_110WP_3_Control_B.EValve_Open_c;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Cycle = CYS_110WP_3_Control_B.Eblast_Cycle_j;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Open = CYS_110WP_3_Control_B.Eblast_Open_p;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Cycle = CYS_110WP_3_Control_B.Motor_Cycle_m;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Motor_Open_n = CYS_110WP_3_Control_B.Motor_Open_g;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.EValve_Enable = CYS_110WP_3_Control_B.EValve_Enable_o;

    /* SignalConversion: '<S12>/Signal Conversion' */
    CYS_110WP_3_Control_B.Eblast_Enable = CYS_110WP_3_Control_B.Eblast_Enable_j;

    /* Update for UnitDelay: '<S12>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_h = CYS_110WP_3_Control_B.Switch_e;

    /* End of Outputs for SubSystem: '<S1>/BWStart' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* Outputs for Atomic SubSystem: '<S1>/ControlOut_Manage' */
  /* Chart: '<S71>/ServoCtrlOut' */
  /* Gateway: CLM/ControlOut_Manage/Accelerator_Manage/ServoCtrlOut */
  /* During: CLM/ControlOut_Manage/Accelerator_Manage/ServoCtrlOut */
  /* Entry Internal: CLM/ControlOut_Manage/Accelerator_Manage/ServoCtrlOut */
  /* Transition: '<S74>:1' */
  if (1 == CYS_110WP_3_Control_B.Merge) {
    /* Transition: '<S74>:4' */
    /* Transition: '<S74>:33' */
    CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_B.Start_Accelerator;

    /* Transition: '<S74>:133' */
    /* Transition: '<S74>:172' */
    /* Transition: '<S74>:164' */
    /* Transition: '<S74>:134' */
    /* Transition: '<S74>:135' */
    /* Transition: '<S74>:136' */
    /* Transition: '<S74>:137' */
    /* Transition: '<S74>:138' */
    /* Transition: '<S74>:152' */
    /* Transition: '<S74>:153' */
  } else {
    /* Transition: '<S74>:6' */
    if (5 == CYS_110WP_3_Control_B.Merge) {
      /* Transition: '<S74>:168' */
      /* Transition: '<S74>:169' */
      CYS_110WP_3_Control_B.Switch_e =
        CYS_110WP_3_Control_B.AirStart_Accelerator;

      /* Transition: '<S74>:172' */
      /* Transition: '<S74>:164' */
      /* Transition: '<S74>:134' */
      /* Transition: '<S74>:135' */
      /* Transition: '<S74>:136' */
      /* Transition: '<S74>:137' */
      /* Transition: '<S74>:138' */
      /* Transition: '<S74>:152' */
      /* Transition: '<S74>:153' */
    } else {
      /* Transition: '<S74>:158' */
      if (6 == CYS_110WP_3_Control_B.Merge) {
        /* Transition: '<S74>:175' */
        /* Transition: '<S74>:176' */
        CYS_110WP_3_Control_B.Switch_e =
          CYS_110WP_3_Control_B.BWStart_Accelerator;

        /* Transition: '<S74>:164' */
        /* Transition: '<S74>:134' */
        /* Transition: '<S74>:135' */
        /* Transition: '<S74>:136' */
        /* Transition: '<S74>:137' */
        /* Transition: '<S74>:138' */
        /* Transition: '<S74>:152' */
        /* Transition: '<S74>:153' */
      } else {
        /* Transition: '<S74>:174' */
        if (3 == CYS_110WP_3_Control_B.Merge) {
          /* Transition: '<S74>:8' */
          if (CYS_110WP_3_Control_B.Manual_Accelerator >=
              CYS_110WP_3_Control_B.ManualAcc_Max) {
            /* Transition: '<S74>:94' */
            /* Transition: '<S74>:101' */
            CYS_110WP_3_Control_B.Switch_e = CYS_110WP_3_Control_B.ManualAcc_Max;

            /* Transition: '<S74>:134' */
            /* Transition: '<S74>:135' */
            /* Transition: '<S74>:136' */
            /* Transition: '<S74>:137' */
            /* Transition: '<S74>:138' */
            /* Transition: '<S74>:152' */
            /* Transition: '<S74>:153' */
          } else {
            /* Transition: '<S74>:95' */
            if (CYS_110WP_3_Control_B.Manual_Accelerator <=
                CYS_110WP_3_Control_B.ManualAcc_Min) {
              /* Transition: '<S74>:98' */
              /* Transition: '<S74>:103' */
              CYS_110WP_3_Control_B.Switch_e =
                CYS_110WP_3_Control_B.ManualAcc_Min;

              /* Transition: '<S74>:135' */
              /* Transition: '<S74>:136' */
              /* Transition: '<S74>:137' */
              /* Transition: '<S74>:138' */
              /* Transition: '<S74>:152' */
              /* Transition: '<S74>:153' */
            } else {
              /* Transition: '<S74>:99' */
              CYS_110WP_3_Control_B.Switch_e =
                CYS_110WP_3_Control_B.Manual_Accelerator;

              /* Transition: '<S74>:136' */
              /* Transition: '<S74>:137' */
              /* Transition: '<S74>:138' */
              /* Transition: '<S74>:152' */
              /* Transition: '<S74>:153' */
            }
          }
        } else {
          /* Transition: '<S74>:10' */
          if (2 == CYS_110WP_3_Control_B.Merge) {
            /* Transition: '<S74>:12' */
            if (CYS_110WP_3_Control_B.CloseLoop_Acclerator >=
                CYS_110WP_3_Control_B.CloseLoopMax) {
              /* Transition: '<S74>:122' */
              /* Transition: '<S74>:129' */
              CYS_110WP_3_Control_B.Switch_e =
                CYS_110WP_3_Control_B.CloseLoopMax;

              /* Transition: '<S74>:137' */
              /* Transition: '<S74>:138' */
              /* Transition: '<S74>:152' */
              /* Transition: '<S74>:153' */
            } else {
              /* Transition: '<S74>:125' */
              if (CYS_110WP_3_Control_B.CloseLoop_Acclerator <=
                  CYS_110WP_3_Control_B.CloseLoopMin) {
                /* Transition: '<S74>:128' */
                /* Transition: '<S74>:132' */
                CYS_110WP_3_Control_B.Switch_e =
                  CYS_110WP_3_Control_B.CloseLoopMin;

                /* Transition: '<S74>:138' */
                /* Transition: '<S74>:152' */
                /* Transition: '<S74>:153' */
              } else {
                /* Transition: '<S74>:124' */
                CYS_110WP_3_Control_B.Switch_e =
                  CYS_110WP_3_Control_B.CloseLoop_Acclerator;

                /* Transition: '<S74>:152' */
                /* Transition: '<S74>:153' */
              }
            }
          } else {
            /* Transition: '<S74>:147' */
            if (4 == CYS_110WP_3_Control_B.Merge) {
              /* Transition: '<S74>:149' */
              /* Transition: '<S74>:151' */
              CYS_110WP_3_Control_B.Switch_e =
                CYS_110WP_3_Control_B.Accelerator_p;

              /* Transition: '<S74>:153' */
            } else {
              /* Transition: '<S74>:18' */
              CYS_110WP_3_Control_B.Switch_e =
                CYS_110WP_3_Control_B.Accelerator_o;
            }
          }
        }
      }
    }
  }

  /* End of Chart: '<S71>/ServoCtrlOut' */

  /* SwitchCase: '<S72>/Switch Case' incorporates:
   *  Constant: '<S78>/Constant1'
   *  Constant: '<S78>/Constant10'
   *  Constant: '<S78>/Constant2'
   *  Constant: '<S78>/Constant3'
   *  Constant: '<S78>/Constant4'
   *  Constant: '<S78>/Constant5'
   *  Constant: '<S78>/Constant6'
   *  Constant: '<S78>/Constant7'
   *  Constant: '<S78>/Constant8'
   *  Constant: '<S78>/Constant9'
   */
  /* Transition: '<S74>:31' */
  switch (CYS_110WP_3_Control_B.Merge) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S75>/Action Port'
     */
    /* Gain: '<S75>/Gain1' */
    rtb_Motor_Open_m = CYS_110WP_3_Control_B.EValve_Cycle_i;

    /* Gain: '<S75>/Gain10' */
    CYS_110WP_3_Control_B.Merge1[3] = CYS_110WP_3_Control_B.SWO_Firework_n;

    /* Gain: '<S75>/Gain11' */
    CYS_110WP_3_Control_B.Merge1[4] = CYS_110WP_3_Control_B.SWO_BleedAir_jd;

    /* Gain: '<S75>/Gain2' */
    EValve_Open_f = CYS_110WP_3_Control_B.EValve_Open_jg;

    /* Gain: '<S75>/Gain3' */
    Eblast_Cycle_j2 = CYS_110WP_3_Control_B.Eblast_Cycle_gv;

    /* Gain: '<S75>/Gain4' */
    rtb_Switch_o3 = CYS_110WP_3_Control_B.Eblast_Open_e;

    /* Gain: '<S75>/Gain5' */
    Motor_Cycle_cf = CYS_110WP_3_Control_B.Motor_Cycle_l;

    /* Gain: '<S75>/Gain6' */
    CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
      (CYS_110WP_3_Control_B.Motor_Open);
    if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
        (CYS_110WP_3_Control_B.T4_X3_Y3)) {
      CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
    } else {
      CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
        (CYS_110WP_3_Control_B.T4_X3_Y3, 65536.0F);
    }

    Motor_Open_h = (uint16_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ? (int32_T)
      (uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.T4_X3_Y3 : (int32_T)
      (uint16_T)CYS_110WP_3_Control_B.T4_X3_Y3);

    /* End of Gain: '<S75>/Gain6' */

    /* Gain: '<S75>/Gain7' */
    CYS_110WP_3_Control_B.Merge1[0] = CYS_110WP_3_Control_B.EValve_Enable_cr;

    /* Gain: '<S75>/Gain8' */
    CYS_110WP_3_Control_B.Merge1[1] = CYS_110WP_3_Control_B.Eblast_Enable_oj;

    /* Gain: '<S75>/Gain9' */
    CYS_110WP_3_Control_B.Merge1[2] = CYS_110WP_3_Control_B.Motor_Enable_b;

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem' */
    break;

   case 5:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem5' incorporates:
     *  ActionPort: '<S80>/Action Port'
     */
    CYS__SwitchCaseActionSubsystem5(CYS_110WP_3_Control_B.EValve_Cycle_n4,
      CYS_110WP_3_Control_B.SWO_Firework_h, CYS_110WP_3_Control_B.SWO_BleedAir_m,
      CYS_110WP_3_Control_B.EValve_Open_b, CYS_110WP_3_Control_B.Eblast_Cycle_l,
      CYS_110WP_3_Control_B.Eblast_Open_c, CYS_110WP_3_Control_B.Motor_Cycle_j,
      CYS_110WP_3_Control_B.Motor_Open_b, CYS_110WP_3_Control_B.EValve_Enable_c,
      CYS_110WP_3_Control_B.Eblast_Enable_o,
      CYS_110WP_3_Control_B.Motor_Enable_f, &rtb_Motor_Open_m, &EValve_Open_f,
      &Eblast_Cycle_j2, &rtb_Switch_o3, &Motor_Cycle_cf, &Motor_Open_h,
      &CYS_110WP_3_Control_B.Merge1[0], &CYS_110WP_3_Control_B.Merge1[1],
      &CYS_110WP_3_Control_B.Merge1[2], &CYS_110WP_3_Control_B.Merge1[3],
      &CYS_110WP_3_Control_B.Merge1[4]);

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem5' */
    break;

   case 4:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem2' incorporates:
     *  ActionPort: '<S77>/Action Port'
     */
    /* Gain: '<S77>/Gain1' */
    rtb_Motor_Open_m = CYS_110WP_3_Control_B.EValve_Cycle_n;

    /* Gain: '<S77>/Gain10' */
    CYS_110WP_3_Control_B.Merge1[3] = CYS_110WP_3_Control_B.SWO_Firework_a;

    /* Gain: '<S77>/Gain11' */
    CYS_110WP_3_Control_B.Merge1[4] = CYS_110WP_3_Control_B.SWO_BleedAIr;

    /* Gain: '<S77>/Gain2' */
    EValve_Open_f = CYS_110WP_3_Control_B.EValve_Open_h;

    /* Gain: '<S77>/Gain3' */
    Eblast_Cycle_j2 = CYS_110WP_3_Control_B.Eblast_Cycle_d;

    /* Gain: '<S77>/Gain4' */
    rtb_Switch_o3 = CYS_110WP_3_Control_B.Eblast_Open_d;

    /* Gain: '<S77>/Gain5' */
    Motor_Cycle_cf = CYS_110WP_3_Control_B.Motor_Cycle_a;

    /* Gain: '<S77>/Gain6' */
    Motor_Open_h = CYS_110WP_3_Control_B.Motor_Open_pl;

    /* Gain: '<S77>/Gain7' */
    CYS_110WP_3_Control_B.Merge1[0] = CYS_110WP_3_Control_B.EValve_Enable_ol;

    /* Gain: '<S77>/Gain8' */
    CYS_110WP_3_Control_B.Merge1[1] = CYS_110WP_3_Control_B.Eblast_Enable_ae;

    /* Gain: '<S77>/Gain9' */
    CYS_110WP_3_Control_B.Merge1[2] = CYS_110WP_3_Control_B.Motor_Enable_h;

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem2' */
    break;

   case 0:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem1' incorporates:
     *  ActionPort: '<S76>/Action Port'
     */
    CYS__SwitchCaseActionSubsystem5(CYS_110WP_3_Control_B.EValve_Cycle_k,
      CYS_110WP_3_Control_B.SWO_Firework_cz,
      CYS_110WP_3_Control_B.SWO_BleedAir_a, CYS_110WP_3_Control_B.EValve_Open_m,
      CYS_110WP_3_Control_B.Eblast_Cycle_f, CYS_110WP_3_Control_B.Eblast_Open_pl,
      CYS_110WP_3_Control_B.Motor_Cycle_o, CYS_110WP_3_Control_B.Motor_Open_po,
      CYS_110WP_3_Control_B.EValve_Enable_nf,
      CYS_110WP_3_Control_B.Eblast_Enable_hg,
      CYS_110WP_3_Control_B.Motor_Enable_pr, &rtb_Motor_Open_m, &EValve_Open_f,
      &Eblast_Cycle_j2, &rtb_Switch_o3, &Motor_Cycle_cf, &Motor_Open_h,
      &CYS_110WP_3_Control_B.Merge1[0], &CYS_110WP_3_Control_B.Merge1[1],
      &CYS_110WP_3_Control_B.Merge1[2], &CYS_110WP_3_Control_B.Merge1[3],
      &CYS_110WP_3_Control_B.Merge1[4]);

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem1' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem4' incorporates:
     *  ActionPort: '<S79>/Action Port'
     */
    CYS__SwitchCaseActionSubsystem5(CYS_110WP_3_Control_B.EValve_Cycle_g,
      CYS_110WP_3_Control_B.SWO_Firework_f, CYS_110WP_3_Control_B.SWO_BleedAir_e,
      CYS_110WP_3_Control_B.EValve_Open_a, CYS_110WP_3_Control_B.Eblast_Cycle_g,
      CYS_110WP_3_Control_B.Eblast_Open_p4, CYS_110WP_3_Control_B.Motor_Cycle_d,
      CYS_110WP_3_Control_B.Motor_Open_p, CYS_110WP_3_Control_B.EValve_Enable_k,
      CYS_110WP_3_Control_B.Eblast_Enable_a,
      CYS_110WP_3_Control_B.Motor_Enable_i, &rtb_Motor_Open_m, &EValve_Open_f,
      &Eblast_Cycle_j2, &rtb_Switch_o3, &Motor_Cycle_cf, &Motor_Open_h,
      &CYS_110WP_3_Control_B.Merge1[0], &CYS_110WP_3_Control_B.Merge1[1],
      &CYS_110WP_3_Control_B.Merge1[2], &CYS_110WP_3_Control_B.Merge1[3],
      &CYS_110WP_3_Control_B.Merge1[4]);

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem4' */
    break;

   case 6:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem6' incorporates:
     *  ActionPort: '<S81>/Action Port'
     */
    CYS__SwitchCaseActionSubsystem5(CYS_110WP_3_Control_B.EValve_Cycle,
      CYS_110WP_3_Control_B.SWO_Firework, CYS_110WP_3_Control_B.SWO_BleedAir,
      CYS_110WP_3_Control_B.EValve_Open, CYS_110WP_3_Control_B.Eblast_Cycle,
      CYS_110WP_3_Control_B.Eblast_Open, CYS_110WP_3_Control_B.Motor_Cycle,
      CYS_110WP_3_Control_B.Motor_Open_n, CYS_110WP_3_Control_B.EValve_Enable,
      CYS_110WP_3_Control_B.Eblast_Enable, CYS_110WP_3_Control_B.Motor_Enable,
      &rtb_Motor_Open_m, &EValve_Open_f, &Eblast_Cycle_j2, &rtb_Switch_o3,
      &Motor_Cycle_cf, &Motor_Open_h, &CYS_110WP_3_Control_B.Merge1[0],
      &CYS_110WP_3_Control_B.Merge1[1], &CYS_110WP_3_Control_B.Merge1[2],
      &CYS_110WP_3_Control_B.Merge1[3], &CYS_110WP_3_Control_B.Merge1[4]);

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem6' */
    break;

   default:
    /* Outputs for IfAction SubSystem: '<S72>/Switch Case Action Subsystem3' incorporates:
     *  ActionPort: '<S78>/Action Port'
     */
    rtb_Motor_Open_m = 30U;
    rtb_Switch_o3 = 0U;
    Eblast_Cycle_j2 = 30U;
    EValve_Open_f = 30U;
    Motor_Cycle_cf = 100U;
    Motor_Open_h = 0U;
    CYS_110WP_3_Control_B.Merge1[1] = 0U;
    CYS_110WP_3_Control_B.Merge1[0] = 1U;
    CYS_110WP_3_Control_B.Merge1[2] = 0U;
    CYS_110WP_3_Control_B.Merge1[3] = 0U;

    /* Gain: '<S78>/Gain' incorporates:
     *  Constant: '<S78>/Constant1'
     *  Constant: '<S78>/Constant10'
     *  Constant: '<S78>/Constant2'
     *  Constant: '<S78>/Constant3'
     *  Constant: '<S78>/Constant4'
     *  Constant: '<S78>/Constant5'
     *  Constant: '<S78>/Constant6'
     *  Constant: '<S78>/Constant7'
     *  Constant: '<S78>/Constant8'
     *  Constant: '<S78>/Constant9'
     */
    CYS_110WP_3_Control_B.Merge1[4] = CYS_110WP_3_Control_B.SWO_BleedAir_j;

    /* End of Outputs for SubSystem: '<S72>/Switch Case Action Subsystem3' */
    break;
  }

  /* End of SwitchCase: '<S72>/Switch Case' */
  /* End of Outputs for SubSystem: '<S1>/ControlOut_Manage' */

  /* Update for UnitDelay: '<S1>/Time Delay2' */
  CYS_110WP_3_Control_DW.TimeDelay2_13_DSTATE = CYS_110WP_3_Control_B.Switch_e;

  /* Update for UnitDelay: '<S1>/Time Delay2' */
  CYS_110WP_3_Control_DW.TimeDelay2_2_DSTATE = EValve_Open_f;

  /* Update for UnitDelay: '<S1>/Time Delay2' */
  CYS_110WP_3_Control_DW.TimeDelay2_11_DSTATE = CYS_110WP_3_Control_B.Merge1[4];

  /* Update for UnitDelay: '<S1>/Time Delay2' */
  CYS_110WP_3_Control_DW.TimeDelay2_7_DSTATE = CYS_110WP_3_Control_B.Merge1[0];

  /* End of Outputs for SubSystem: '<Root>/CLM' */

  /* Outputs for Atomic SubSystem: '<Root>/ControlOut' */
  /* Outport: '<Root>/Controldata' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion10Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion11Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion12Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion13Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion14Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion15Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion16Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion17Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion18Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion1Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion2Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion3Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion4Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion5Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion6Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion7Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion8Inport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtData Type Conversion9Inport1'
   */
  arg_Controldata->EValve_Cycle = rtb_Motor_Open_m;
  arg_Controldata->EValve_Open = EValve_Open_f;
  arg_Controldata->Eblast_Cycle = Eblast_Cycle_j2;
  arg_Controldata->Eblast_Open = rtb_Switch_o3;
  arg_Controldata->Motor_Cycle = Motor_Cycle_cf;
  arg_Controldata->Motor_Open = Motor_Open_h;
  arg_Controldata->EValve_Enable = CYS_110WP_3_Control_B.Merge1[0];
  arg_Controldata->Eblast_Enable = CYS_110WP_3_Control_B.Merge1[1];
  arg_Controldata->Motor_Enable = CYS_110WP_3_Control_B.Merge1[2];
  arg_Controldata->SWO_Firework = CYS_110WP_3_Control_B.Merge1[3];
  arg_Controldata->SWO_BleedAir = CYS_110WP_3_Control_B.Merge1[4];
  arg_Controldata->EngineState = CYS_110WP_3_Control_B.EngineState;
  arg_Controldata->Flag_ECUReset_Clear = rtb_Flag_ECUReset_Clear;
  arg_Controldata->Flag_ECUReset_Save = rtb_ECUReset_Save;
  arg_Controldata->Flag_Reset_Enable = rtb_TimeDelay2;
  arg_Controldata->Accelerator = CYS_110WP_3_Control_B.Switch_e;
  arg_Controldata->Nc_dem = CYS_110WP_3_Control_B.Switch_g;
  arg_Controldata->Nc = CYS_110WP_3_Control_B.Product5_c;

  /* End of Outputs for SubSystem: '<Root>/ControlOut' */

  /* Outputs for Atomic SubSystem: '<Root>/MAM' */
  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
   *  Constant: '<S6>/dth = T0-288.21'
   *  Inport: '<Root>/S_Vpower'
   *  RelationalOperator: '<S6>/Relational Operator'
   */
  rtb_Switch_gc = (uint8_T)(arg_S_Vpower < 22.0F);

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

  /* Chart: '<S6>/Timmer_ms' incorporates:
   *  Constant: '<S6>/Constant2'
   *  Constant: '<S6>/Constant3'
   *  RelationalOperator: '<S6>/Relational Operator2'
   */
  CYS_110WP_3_Control_Timmer_ms_g(CYS_110WP_3_Control_B.KpLookupTable1 > 850.0F,
    2000.0F, &CYS_110WP_3_Control_B.sf_Timmer_ms_g,
    &CYS_110WP_3_Control_DW.sf_Timmer_ms_g);

  /* Chart: '<S6>/Timmer_ms1' incorporates:
   *  Constant: '<S6>/Constant1'
   *  Constant: '<S6>/Constant4'
   *  RelationalOperator: '<S6>/Relational Operator1'
   */
  CYS_110WP_3_Control_Timmer_ms1(CYS_110WP_3_Control_B.Product5_c > 62000.0F,
    2000.0F, &CYS_110WP_3_Control_B.sf_Timmer_ms1,
    &CYS_110WP_3_Control_DW.sf_Timmer_ms1);

  /* End of Outputs for SubSystem: '<Root>/MAM' */

  /* Outputs for Atomic SubSystem: '<Root>/SaveData' */
  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* DataTypeConversion: '<S8>/Data Type Conversion24' incorporates:
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain2'
   *  Gain: '<S8>/Gain3'
   *  Gain: '<S8>/Gain4'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S8>/Gain6'
   *  Gain: '<S8>/Gain7'
   *  Gain: '<S8>/Gain8'
   *  Inport: '<Root>/SWI_BleedAir'
   *  Inport: '<Root>/SWI_EValve'
   *  Inport: '<Root>/SWI_Eblast'
   *  Inport: '<Root>/SWI_Firework'
   *  Logic: '<S8>/Logical Operator'
   *  Logic: '<S8>/Logical Operator1'
   *  Logic: '<S8>/Logical Operator2'
   *  Logic: '<S8>/Logical Operator3'
   *  Sum: '<S8>/Sum of Elements4'
   */
  arg_savedata->savedata9 = (uint8_T)((((((((uint32_T)(uint8_T)
    (CYS_110WP_3_Control_B.Merge1[0] << 1) + CYS_110WP_3_Control_B.Merge1[3]) +
    (uint8_T)(CYS_110WP_3_Control_B.Merge1[1] << 2)) + (uint8_T)
    (CYS_110WP_3_Control_B.Merge1[4] << 3)) + (!(arg_SWI_Firework != 0) << 4)) +
    (!(arg_SWI_EValve != 0) << 5)) + (!(arg_SWI_Eblast != 0) << 6)) +
    (!(arg_SWI_BleedAir != 0) << 7));

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

  /* Product: '<S8>/Product3' incorporates:
   *  Constant: '<S8>/dth = T0-288.13'
   */
  arg_savedata->savedata7 = (real32_T)EValve_Open_f * 100.0F / (real32_T)
    rtb_Motor_Open_m;

  /* Product: '<S8>/Product7' incorporates:
   *  Constant: '<S8>/dth = T0-288.9'
   */
  arg_savedata->savedata6 = (real32_T)rtb_Switch_o3 * 100.0F / (real32_T)
    Eblast_Cycle_j2;

  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion2Inport1' incorporates:
   *  Inport: '<Root>/S_Vpower'
   */
  arg_savedata->savedata3 = arg_S_Vpower;

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

  /* SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion3Inport1' */
  arg_savedata->savedata4 = CYS_110WP_3_Control_B.KpLookupTable1;

  /* SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion4Inport1' */
  arg_savedata->savedata5 = CYS_110WP_3_Control_B.SumofElements1_er;

  /* SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion5Inport1' */
  arg_savedata->savedata8 = CYS_110WP_3_Control_B.sf_Range_da.Out;

  /* Chart: '<S8>/Hold' */
  CYS_110WP_3_Control_Hold_o(&CYS_110WP_3_Control_B.sf_Hold_oi,
    &CYS_110WP_3_Control_DW.sf_Hold_oi);

  /* BusCreator: '<Root>/Bus Creator1' incorporates:
   *  Constant: '<S8>/dth = T0-288.1'
   *  Constant: '<S8>/dth = T0-288.11'
   *  Constant: '<S8>/dth = T0-288.4'
   *  Constant: '<S8>/dth = T0-288.5'
   *  Constant: '<S8>/dth = T0-288.6'
   *  Constant: '<S8>/dth = T0-288.7'
   *  Constant: '<S8>/dth = T0-288.8'
   *  DataTypeConversion: '<S8>/Data Type Conversion15'
   *  DataTypeConversion: '<S8>/Data Type Conversion16'
   *  DataTypeConversion: '<S8>/Data Type Conversion19'
   *  DataTypeConversion: '<S8>/Data Type Conversion9'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain11'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain9'
   *  Inport: '<Root>/SWI_ValveErr'
   *  Inport: '<S6>/S_FPM'
   *  Product: '<S8>/Product1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion11Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion12Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion13Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion14Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion1Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion6Inport1'
   *  SignalConversion: '<S8>/TmpSignal ConversionAtData Type Conversion7Inport1'
   *  Sum: '<S8>/Sum of Elements1'
   */
  arg_savedata->savedata1 = rtb_Switch_it;
  arg_savedata->savedata2 = CYS_110WP_3_Control_B.sf_Range_j0.Out;
  arg_savedata->savedata10 = CYS_110WP_3_Control_B.T_S;
  arg_savedata->savedata11 = CYS_110WP_3_Control_B.Switch_e;
  arg_savedata->savedata12 = (real32_T)Motor_Open_h * 100.0F / (real32_T)
    Motor_Cycle_cf;
  arg_savedata->savedata13 = CYS_110WP_3_Control_B.EngineState;

  /* Outputs for Atomic SubSystem: '<Root>/MAM' */
  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  arg_savedata->savedata14 = (uint8_T)(((((uint32_T)
    (CYS_110WP_3_Control_B.sf_Timmer_ms1.Out << 1) +
    CYS_110WP_3_Control_B.sf_Timmer_ms_g.Out) + (rtb_DataTypeConversion4_f << 2))
    + (rtb_Switch_gc << 4)) + (uint8_T)(arg_SWI_ValveErr << 5));

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */
  /* End of Outputs for SubSystem: '<Root>/MAM' */
  arg_savedata->savedata15 = CYS_110WP_3_Control_B.sf_Hold_oi.Out;
  arg_savedata->savedata16 = CYS_110WP_3_Control_B.Sqrt;
  arg_savedata->savedata17 = CYS_110WP_3_Control_B.Switch_g;
  arg_savedata->savedata18 = CYS_110WP_3_Control_B.H_GPRS;
  arg_savedata->savedata19 = CYS_110WP_3_Control_B.SumofElements1_e;

  /* End of Outputs for SubSystem: '<Root>/SaveData' */
  arg_savedata->savedata20 = 0.0F;
  arg_savedata->savedata21 = 0.0F;
  arg_savedata->savedata22 = 0.0F;
  arg_savedata->savedata23 = 0.0F;
  arg_savedata->savedata24 = 0.0F;
  arg_savedata->savedata25 = 0.0F;

  /* Outputs for Atomic SubSystem: '<Root>/SendData' */
  /* Product: '<S9>/Product10' incorporates:
   *  Constant: '<S9>/dth = T0-288.30'
   */
  CYS_110WP_3_Control_B.SumofElements1_e = CYS_110WP_3_Control_B.T_S / 2.0F;

  /* DataTypeConversion: '<S9>/Data Type Conversion1' */
  CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
    (CYS_110WP_3_Control_B.SumofElements1_e);
  if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
      (CYS_110WP_3_Control_B.T4_X3_Y3)) {
    CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
  } else {
    CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
      (CYS_110WP_3_Control_B.T4_X3_Y3, 4.2949673E+9F);
  }

  /* Product: '<S9>/Product1' incorporates:
   *  Constant: '<S9>/dth = T0-288.5'
   */
  CYS_110WP_3_Control_B.Product5_c = CYS_110WP_3_Control_B.Switch_g / 2.0F;

  /* DataTypeConversion: '<S9>/Data Type Conversion3' */
  CYS_110WP_3_Control_B.X_Out_a = (real32_T)floor
    (CYS_110WP_3_Control_B.Product5_c);
  if (rtIsNaNF(CYS_110WP_3_Control_B.X_Out_a) || rtIsInfF
      (CYS_110WP_3_Control_B.X_Out_a)) {
    CYS_110WP_3_Control_B.X_Out_a = 0.0F;
  } else {
    CYS_110WP_3_Control_B.X_Out_a = (real32_T)fmod(CYS_110WP_3_Control_B.X_Out_a,
      4.2949673E+9F);
  }

  /* Product: '<S9>/Product11' incorporates:
   *  Constant: '<S9>/dth = T0-288.29'
   */
  CYS_110WP_3_Control_B.SumofElements1_e /= 256.0F;

  /* Product: '<S9>/Product2' incorporates:
   *  Constant: '<S9>/dth = T0-288.4'
   */
  CYS_110WP_3_Control_B.Product5_c /= 256.0F;

  /* DataTypeConversion: '<S9>/Data Type Conversion25' */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.Switch_e);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 65536.0F);
  }

  rtb_DataTypeConversion25 = (uint16_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint16_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion25' */

  /* DataTypeConversion: '<S9>/Data Type Conversion26' */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.Switch_g);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 65536.0F);
  }

  rtb_DataTypeConversion26 = (uint16_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint16_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion26' */

  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* DataTypeConversion: '<S9>/Data Type Conversion4' incorporates:
   *  Constant: '<S9>/dth = T0-288.3'
   *  Inport: '<Root>/S_Vpower'
   *  Product: '<S9>/Product19'
   */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor(5.0F * arg_S_Vpower);

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 256.0F);
  }

  arg_senddata->senddata5 = (uint8_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion4' */

  /* DataTypeConversion: '<S9>/Data Type Conversion5' incorporates:
   *  Constant: '<S9>/dth = T0-288.6'
   *  Sum: '<S9>/Sum of Elements5'
   */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.sf_Range_j0.Out + 80.0F);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 256.0F);
  }

  arg_senddata->senddata4 = (uint8_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion5' */

  /* DataTypeConversion: '<S9>/Data Type Conversion6' incorporates:
   *  Constant: '<S9>/dth = T0-288.2'
   *  Product: '<S9>/Product4'
   */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.sf_Range_da.Out / 2.0F);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 65536.0F);
  }

  rtb_DataTypeConversion6 = (uint16_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint16_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion6' */

  /* DataTypeConversion: '<S9>/Data Type Conversion7' */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.KpLookupTable1);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 65536.0F);
  }

  rtb_DataTypeConversion7 = (uint16_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint16_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion7' */

  /* DataTypeConversion: '<S9>/Data Type Conversion8' */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.SumofElements1_er);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 65536.0F);
  }

  rtb_DataTypeConversion8 = (uint16_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint16_T)CYS_110WP_3_Control_B.Switch_e);

  /* End of DataTypeConversion: '<S9>/Data Type Conversion8' */

  /* DataTypeConversion: '<S263>/Extract Desired Bits' */
  arg_senddata->senddata6 = (uint8_T)((uint32_T)rtb_DataTypeConversion7 >> 8);

  /* DataTypeConversion: '<S265>/Extract Desired Bits' */
  arg_senddata->senddata8 = (uint8_T)((uint32_T)rtb_DataTypeConversion8 >> 8);

  /* DataTypeConversion: '<S266>/Extract Desired Bits' */
  arg_senddata->senddata9 = (uint8_T)rtb_DataTypeConversion8;

  /* DataTypeConversion: '<S267>/Extract Desired Bits' */
  arg_senddata->senddata7 = (uint8_T)rtb_DataTypeConversion7;

  /* SignalConversion: '<S9>/TmpSignal ConversionAtData Type Conversion19Inport1' */
  arg_senddata->senddata3 = rtb_Switch_it;

  /* End of Outputs for SubSystem: '<Root>/SendData' */

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  Constant: '<S9>/dth = T0-288.11'
   *  Constant: '<S9>/dth = T0-288.38'
   */
  arg_senddata->senddata1 = 1U;
  arg_senddata->senddata2 = 25U;

  /* Outputs for Atomic SubSystem: '<Root>/SendData' */
  /* DataTypeConversion: '<S9>/Data Type Conversion22' incorporates:
   *  Constant: '<S9>/dth = T0-288.9'
   *  Product: '<S9>/Product7'
   */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor((real32_T)rtb_Switch_o3 *
    100.0F / (real32_T)Eblast_Cycle_j2);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion22'
   */
  arg_senddata->senddata10 = (uint8_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.Switch_e);

  /* DataTypeConversion: '<S9>/Data Type Conversion20' incorporates:
   *  Constant: '<S9>/dth = T0-288.13'
   *  Product: '<S9>/Product3'
   */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor((real32_T)EValve_Open_f *
    100.0F / (real32_T)rtb_Motor_Open_m);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S262>/Extract Desired Bits'
   *  DataTypeConversion: '<S270>/Extract Desired Bits'
   *  DataTypeConversion: '<S9>/Data Type Conversion20'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain2'
   *  Gain: '<S9>/Gain3'
   *  Gain: '<S9>/Gain4'
   *  Gain: '<S9>/Gain5'
   *  Gain: '<S9>/Gain6'
   *  Gain: '<S9>/Gain7'
   *  Gain: '<S9>/Gain8'
   *  Inport: '<Root>/SWI_BleedAir'
   *  Inport: '<Root>/SWI_EValve'
   *  Inport: '<Root>/SWI_Eblast'
   *  Inport: '<Root>/SWI_Firework'
   *  Logic: '<S9>/Logical Operator'
   *  Logic: '<S9>/Logical Operator1'
   *  Logic: '<S9>/Logical Operator2'
   *  Logic: '<S9>/Logical Operator3'
   *  Sum: '<S9>/Sum of Elements4'
   */
  arg_senddata->senddata11 = (uint8_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.Switch_e);
  arg_senddata->senddata12 = (uint8_T)((uint32_T)rtb_DataTypeConversion6 >> 8);
  arg_senddata->senddata13 = (uint8_T)rtb_DataTypeConversion6;

  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  arg_senddata->senddata14 = (uint8_T)((((((((uint32_T)(uint8_T)
    (CYS_110WP_3_Control_B.Merge1[0] << 1) + CYS_110WP_3_Control_B.Merge1[3]) +
    (uint8_T)(CYS_110WP_3_Control_B.Merge1[1] << 2)) + (uint8_T)
    (CYS_110WP_3_Control_B.Merge1[4] << 3)) + (!(arg_SWI_Firework != 0) << 4)) +
    (!(arg_SWI_EValve != 0) << 5)) + (!(arg_SWI_Eblast != 0) << 6)) +
    (!(arg_SWI_BleedAir != 0) << 7));

  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */

  /* DataTypeConversion: '<S9>/Data Type Conversion12' */
  CYS_110WP_3_Control_B.Switch_e = (real32_T)floor
    (CYS_110WP_3_Control_B.SumofElements1_e);
  if (rtIsNaNF(CYS_110WP_3_Control_B.Switch_e) || rtIsInfF
      (CYS_110WP_3_Control_B.Switch_e)) {
    CYS_110WP_3_Control_B.Switch_e = 0.0F;
  } else {
    CYS_110WP_3_Control_B.Switch_e = (real32_T)fmod
      (CYS_110WP_3_Control_B.Switch_e, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S261>/Extract Desired Bits'
   *  DataTypeConversion: '<S264>/Extract Desired Bits'
   *  DataTypeConversion: '<S9>/Data Type Conversion1'
   *  DataTypeConversion: '<S9>/Data Type Conversion12'
   *  S-Function (sfix_bitop): '<S9>/Bitwise Operator2'
   */
  arg_senddata->senddata15 = (uint8_T)(CYS_110WP_3_Control_B.Switch_e < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.Switch_e :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.Switch_e);
  arg_senddata->senddata16 = (uint8_T)((CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
    (uint32_T)-(int32_T)(uint32_T)-CYS_110WP_3_Control_B.T4_X3_Y3 : (uint32_T)
    CYS_110WP_3_Control_B.T4_X3_Y3) & 255U);
  arg_senddata->senddata17 = (uint8_T)((uint32_T)rtb_DataTypeConversion25 >> 8);
  arg_senddata->senddata18 = (uint8_T)rtb_DataTypeConversion25;

  /* DataTypeConversion: '<S9>/Data Type Conversion23' incorporates:
   *  Constant: '<S9>/dth = T0-288.12'
   *  Product: '<S9>/Product8'
   */
  CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor((real32_T)Motor_Open_h *
    100.0F / (real32_T)Motor_Cycle_cf);
  if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
      (CYS_110WP_3_Control_B.T4_X3_Y3)) {
    CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
  } else {
    CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
      (CYS_110WP_3_Control_B.T4_X3_Y3, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S240>/Data Type Conversion3'
   *  DataTypeConversion: '<S9>/Data Type Conversion23'
   *  Gain: '<S9>/Gain10'
   *  Gain: '<S9>/Gain11'
   *  Gain: '<S9>/Gain12'
   *  Gain: '<S9>/Gain14'
   *  Gain: '<S9>/Gain15'
   *  Gain: '<S9>/Gain9'
   *  Inport: '<Root>/SWI_ValveErr'
   *  Inport: '<S6>/S_FPM'
   *  Logic: '<S9>/Logical Operator4'
   *  SignalConversion: '<S9>/TmpSignal ConversionAtData Type Conversion13Inport1'
   *  Sum: '<S9>/Sum of Elements1'
   */
  arg_senddata->senddata19 = (uint8_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.T4_X3_Y3 :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.T4_X3_Y3);
  arg_senddata->senddata20 = CYS_110WP_3_Control_B.EngineState;

  /* Outputs for Atomic SubSystem: '<Root>/MAM' */
  /* Outputs for Atomic SubSystem: '<Root>/COMMRead_ISM' */
  /* Outputs for Atomic SubSystem: '<S2>/ISM' */
  /* Outputs for Atomic SubSystem: '<Root>/FPM' */
  arg_senddata->senddata21 = (uint8_T)((((((uint32_T)
    (CYS_110WP_3_Control_B.sf_Timmer_ms1.Out << 1) +
    CYS_110WP_3_Control_B.sf_Timmer_ms_g.Out) + (rtb_DataTypeConversion4_f << 2))
    + (rtb_Switch_gc << 4)) + (!(arg_SWI_ValveErr != 0) << 5)) +
    (CYS_110WP_3_Control_B.sf_Timmer_ms_Lock.Out << 6));

  /* End of Outputs for SubSystem: '<Root>/FPM' */
  /* End of Outputs for SubSystem: '<S2>/ISM' */
  /* End of Outputs for SubSystem: '<Root>/COMMRead_ISM' */
  /* End of Outputs for SubSystem: '<Root>/MAM' */
  /* End of Outputs for SubSystem: '<Root>/SendData' */
  arg_senddata->senddata22 = 0U;

  /* Outputs for Atomic SubSystem: '<Root>/SendData' */
  /* DataTypeConversion: '<S9>/Data Type Conversion11' incorporates:
   *  Constant: '<S9>/dth = T0-288.20'
   *  Sum: '<S9>/Sum of Elements2'
   */
  CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor(CYS_110WP_3_Control_B.Sqrt +
    50.0F);
  if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
      (CYS_110WP_3_Control_B.T4_X3_Y3)) {
    CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
  } else {
    CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
      (CYS_110WP_3_Control_B.T4_X3_Y3, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion11'
   */
  arg_senddata->senddata23 = (uint8_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.T4_X3_Y3 :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.T4_X3_Y3);

  /* DataTypeConversion: '<S9>/Data Type Conversion15' */
  CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)floor
    (CYS_110WP_3_Control_B.Product5_c);
  if (rtIsNaNF(CYS_110WP_3_Control_B.T4_X3_Y3) || rtIsInfF
      (CYS_110WP_3_Control_B.T4_X3_Y3)) {
    CYS_110WP_3_Control_B.T4_X3_Y3 = 0.0F;
  } else {
    CYS_110WP_3_Control_B.T4_X3_Y3 = (real32_T)fmod
      (CYS_110WP_3_Control_B.T4_X3_Y3, 256.0F);
  }

  /* BusCreator: '<Root>/Bus Creator3' incorporates:
   *  DataTypeConversion: '<S268>/Extract Desired Bits'
   *  DataTypeConversion: '<S269>/Extract Desired Bits'
   *  DataTypeConversion: '<S9>/Data Type Conversion15'
   *  DataTypeConversion: '<S9>/Data Type Conversion3'
   *  S-Function (sfix_bitop): '<S9>/Bitwise Operator3'
   */
  arg_senddata->senddata24 = (uint8_T)(CYS_110WP_3_Control_B.T4_X3_Y3 < 0.0F ?
    (int32_T)(uint8_T)-(int8_T)(uint8_T)-CYS_110WP_3_Control_B.T4_X3_Y3 :
    (int32_T)(uint8_T)CYS_110WP_3_Control_B.T4_X3_Y3);
  arg_senddata->senddata25 = (uint8_T)((CYS_110WP_3_Control_B.X_Out_a < 0.0F ?
    (uint32_T)-(int32_T)(uint32_T)-CYS_110WP_3_Control_B.X_Out_a : (uint32_T)
    CYS_110WP_3_Control_B.X_Out_a) & 255U);

  /* End of Outputs for SubSystem: '<Root>/SendData' */
  arg_senddata->senddata26 = 0U;
  arg_senddata->senddata27 = 0U;

  /* Outputs for Atomic SubSystem: '<Root>/SendData' */
  arg_senddata->senddata28 = (uint8_T)((uint32_T)rtb_DataTypeConversion26 >> 8);
  arg_senddata->senddata29 = (uint8_T)rtb_DataTypeConversion26;

  /* End of Outputs for SubSystem: '<Root>/SendData' */
}

/* Model initialize function */
void ECU_110WP_C_Control_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(CYS_110WP_3_Control_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &CYS_110WP_3_Control_B), 0,
                sizeof(B_CYS_110WP_3_Control_T));

  /* states (dwork) */
  (void) memset((void *)&CYS_110WP_3_Control_DW, 0,
                sizeof(DW_CYS_110WP_3_Control_T));

  {
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/CLM' */
    /* Start for SwitchCase: '<S1>/Switch Case' */
    CYS_110WP_3_Control_DW.SwitchCase_ActiveSubsystem = -1;

    /* InitializeConditions for IfAction SubSystem: '<S1>/Origin' */
    /* InitializeConditions for Delay: '<S16>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_c = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_og[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay1_DSTATE_og[1] = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay2' */
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[1] = 0.0F;
    CYS_110WP_3_Control_DW.Delay2_DSTATE_n[2] = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay3' */
    CYS_110WP_3_Control_DW.Delay3_DSTATE[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay3_DSTATE[1] = 0.0F;
    CYS_110WP_3_Control_DW.Delay3_DSTATE[2] = 0.0F;
    CYS_110WP_3_Control_DW.Delay3_DSTATE[3] = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay4' */
    CYS_110WP_3_Control_DW.Delay4_DSTATE = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay5' */
    CYS_110WP_3_Control_DW.Delay5_DSTATE[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay5_DSTATE[1] = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay6' */
    CYS_110WP_3_Control_DW.Delay6_DSTATE[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay6_DSTATE[1] = 0.0F;
    CYS_110WP_3_Control_DW.Delay6_DSTATE[2] = 0.0F;

    /* InitializeConditions for Delay: '<S16>/Delay7' */
    CYS_110WP_3_Control_DW.Delay7_DSTATE[0] = 0.0F;
    CYS_110WP_3_Control_DW.Delay7_DSTATE[1] = 0.0F;
    CYS_110WP_3_Control_DW.Delay7_DSTATE[2] = 0.0F;
    CYS_110WP_3_Control_DW.Delay7_DSTATE[3] = 0.0F;

    /* InitializeConditions for Chart: '<S16>/Cool_Control' */
    CYS_110WP_3_Control_DW.EarthStop = false;
    CYS_110WP_3_Control_DW.CNT_EarthCoolTime = 0U;
    CYS_110WP_3_Control_DW.CNT_Global = 0U;
    CYS_110WP_3_Control_DW.CoolDoneFlag = false;
    CYS_110WP_3_Control_B.Accelerator_m = 0.0F;
    CYS_110WP_3_Control_B.EValve_Open_my = 0U;
    CYS_110WP_3_Control_B.EValve_Enable_b = 0U;

    /* End of InitializeConditions for SubSystem: '<S1>/Origin' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/Start' */
    /* InitializeConditions for Delay: '<S111>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_i = 0.0F;

    /* InitializeConditions for Delay: '<S111>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_a = 0.0F;

    /* InitializeConditions for Chart: '<S111>/Hold' */
    CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold,
      &CYS_110WP_3_Control_DW.sf_Hold);

    /* InitializeConditions for Chart: '<S115>/Hold' */
    CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_n,
      &CYS_110WP_3_Control_DW.sf_Hold_n);

    /* InitializeConditions for Delay: '<S115>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_p = 0U;

    /* InitializeConditions for Delay: '<S115>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_e = 0.0F;

    /* InitializeConditions for Delay: '<S115>/Delay2' */
    CYS_110WP_3_Control_DW.Delay2_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S115>/Timmer_ms' */
    CYS_110WP_3_Cont_Timmer_ms_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms);

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE_f = 0.0F;

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE_p = 0.0F;

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE_j = 0.0F;

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE_c = 0.0F;

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_5_DSTATE = 0.0F;

    /* InitializeConditions for UnitDelay: '<S17>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_6_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S17>/Start_OpenLoop' */
    CYS_110WP_3_Control_DW.CNT_Start_C_o = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_E_o = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_B_a = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_F_d = 0U;
    CYS_110WP_3_Control_DW.Start_A_o = true;
    CYS_110WP_3_Control_DW.Start_B_h = false;
    CYS_110WP_3_Control_DW.Start_C_i = false;
    CYS_110WP_3_Control_DW.Start_D_j = false;
    CYS_110WP_3_Control_DW.Start_E_a = false;
    CYS_110WP_3_Control_DW.Start_F_k = false;
    CYS_110WP_3_Control_DW.CNT_Motor_b = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_D_f = 0U;
    CYS_110WP_3_Control_DW.CNT_EValve_Open_h = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_A_m = 0U;
    CYS_110WP_3_Control_DW.CNT_POilHigh_d = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_C1_g = 0U;
    CYS_110WP_3_Control_DW.Flag_IntoC = false;
    CYS_110WP_3_Control_DW.Motor_OFF_Enable = 0U;
    CYS_110WP_3_Control_B.Accelerator_c = 0.0F;
    CYS_110WP_3_Control_B.EValve_Cycle_e = 0U;
    CYS_110WP_3_Control_B.EValve_Open_e = 0U;
    CYS_110WP_3_Control_B.Eblast_Cycle_o = 0U;
    CYS_110WP_3_Control_B.Eblast_Open_eu = 0U;
    CYS_110WP_3_Control_B.Motor_Cycle_i = 0U;
    CYS_110WP_3_Control_B.Motor_Open_f = 0.0F;
    CYS_110WP_3_Control_B.EValve_Enable_n = 0U;
    CYS_110WP_3_Control_B.Eblast_Enable_h = 0U;
    CYS_110WP_3_Control_B.Motor_Enable_b1 = 0U;
    CYS_110WP_3_Control_B.SWO_Firework_c = 0U;
    CYS_110WP_3_Control_B.Flag_EngineState_h = 0U;

    /* InitializeConditions for Chart: '<S17>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range);

    /* End of InitializeConditions for SubSystem: '<S1>/Start' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/AirStart' */
    /* InitializeConditions for Delay: '<S20>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_o = 0.0F;

    /* InitializeConditions for Delay: '<S20>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S20>/Hold' */
    CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_c,
      &CYS_110WP_3_Control_DW.sf_Hold_c);

    /* InitializeConditions for Chart: '<S24>/Hold1' */
    CYS_110WP_3_Control_Hold1_Init(&CYS_110WP_3_Control_B.sf_Hold1,
      &CYS_110WP_3_Control_DW.sf_Hold1);

    /* InitializeConditions for Delay: '<S24>/Delay1' */
    CYS_110WP_3_Control_DW.Delay1_DSTATE_o = 0.0F;

    /* InitializeConditions for Chart: '<S24>/Hold' */
    CYS_110WP_3_Control_Hold_Init(&CYS_110WP_3_Control_B.sf_Hold_o,
      &CYS_110WP_3_Control_DW.sf_Hold_o);

    /* InitializeConditions for Delay: '<S24>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_f = 0U;

    /* InitializeConditions for Chart: '<S24>/Timmer_ms' */
    CYS_110WP_3_Cont_Timmer_ms_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms_f,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms_f);

    /* InitializeConditions for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_1_DSTATE = 0.0F;

    /* InitializeConditions for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_2_DSTATE = 0.0F;

    /* InitializeConditions for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_3_DSTATE = 0.0F;

    /* InitializeConditions for UnitDelay: '<S10>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_4_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S10>/Start_OpenLoop' */
    CYS_110WP_3_Control_DW.CNT_Start_C_l = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_E = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_B_h = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_F = 0U;
    CYS_110WP_3_Control_DW.Start_A_h = true;
    CYS_110WP_3_Control_DW.Start_B_l = false;
    CYS_110WP_3_Control_DW.Start_C_o = false;
    CYS_110WP_3_Control_DW.Start_D = false;
    CYS_110WP_3_Control_DW.Start_E = false;
    CYS_110WP_3_Control_DW.Start_F = false;
    CYS_110WP_3_Control_DW.CNT_Start_D = 0U;
    CYS_110WP_3_Control_DW.CNT_EValve_Open = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_A = 0U;
    CYS_110WP_3_Control_DW.CNT_POilHigh = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_C1_d = 0U;
    CYS_110WP_3_Control_B.Accelerator_e = 0.0F;
    CYS_110WP_3_Control_B.EValve_Cycle_js = 0U;
    CYS_110WP_3_Control_B.EValve_Open_jc = 0U;
    CYS_110WP_3_Control_B.Eblast_Cycle_b = 0U;
    CYS_110WP_3_Control_B.Eblast_Open_n = 0U;
    CYS_110WP_3_Control_B.Motor_Cycle_c = 0U;
    CYS_110WP_3_Control_B.Motor_Open_nq = 0U;
    CYS_110WP_3_Control_B.EValve_Enable_ot = 0U;
    CYS_110WP_3_Control_B.Eblast_Enable_k = 0U;
    CYS_110WP_3_Control_B.Motor_Enable_p = 0U;
    CYS_110WP_3_Control_B.SWO_Firework_p = 0U;
    CYS_110WP_3_Control_B.Flag_EngineState = 0U;

    /* InitializeConditions for Chart: '<S10>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_j);

    /* End of InitializeConditions for SubSystem: '<S1>/AirStart' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/ClpControl' */
    /* InitializeConditions for Delay: '<S57>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S57>/Hold' */
    CYS_110WP_3_Control_Hold_c_Init(&CYS_110WP_3_Control_B.sf_Hold_g,
      &CYS_110WP_3_Control_DW.sf_Hold_g);

    /* InitializeConditions for Chart: '<S57>/M_Rate_Limiter' */
    CYS_110WP_3_M_Rate_Limiter_Init(&CYS_110WP_3_Control_B.sf_M_Rate_Limiter,
      &CYS_110WP_3_Control_DW.sf_M_Rate_Limiter);

    /* InitializeConditions for UnitDelay: '<S51>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE = 0.0F;

    /* InitializeConditions for Chart: '<S51>/Range1' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range1);

    /* InitializeConditions for Chart: '<S65>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_d);

    /* End of InitializeConditions for SubSystem: '<S1>/ClpControl' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/Stop' */
    /* InitializeConditions for Chart: '<S18>/Stop_Control' */
    CYS_110WP_3_Control_DW.CNT_Wait = 0U;
    CYS_110WP_3_Control_DW.CNT_Motor = 0U;
    CYS_110WP_3_Control_B.Accelerator_k = 0.0F;
    CYS_110WP_3_Control_B.EValve_Open_j = 0U;
    CYS_110WP_3_Control_B.Eblast_Open_m = 0U;
    CYS_110WP_3_Control_B.Motor_Open_pv = 0U;
    CYS_110WP_3_Control_B.EValve_Enable_d = 0U;
    CYS_110WP_3_Control_B.Eblast_Enable_e = 0U;
    CYS_110WP_3_Control_B.Motor_Enable_e = 0U;
    CYS_110WP_3_Control_B.StopFinish_l = 0U;

    /* End of InitializeConditions for SubSystem: '<S1>/Stop' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/Manual' */
    /* InitializeConditions for Chart: '<S83>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_h);

    /* InitializeConditions for UnitDelay: '<S83>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_i = false;

    /* InitializeConditions for UnitDelay: '<S83>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_g = 0U;

    /* InitializeConditions for UnitDelay: '<S84>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_p = 0U;

    /* InitializeConditions for Chart: '<S85>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_jg);

    /* InitializeConditions for Delay: '<S95>/Delay' */
    CYS_110WP_3_Control_DW.Delay_DSTATE_fm = false;

    /* InitializeConditions for Chart: '<S95>/Hold_500ms' */
    CYS_110WP_3_Con_Hold_500ms_Init(&CYS_110WP_3_Control_B.sf_Hold_500ms,
      &CYS_110WP_3_Control_DW.sf_Hold_500ms);

    /* InitializeConditions for Chart: '<S86>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_o);

    /* InitializeConditions for Chart: '<S87>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_ow);

    /* InitializeConditions for UnitDelay: '<S87>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_j = false;

    /* InitializeConditions for UnitDelay: '<S87>/Time Delay8' */
    CYS_110WP_3_Control_DW.TimeDelay8_DSTATE_gl = 0U;

    /* End of InitializeConditions for SubSystem: '<S1>/Manual' */

    /* InitializeConditions for IfAction SubSystem: '<S1>/BWStart' */
    /* InitializeConditions for Chart: '<S46>/Hold' */
    CYS_110WP_3_Control_Hold_i_Init(&CYS_110WP_3_Control_B.sf_Hold_h,
      &CYS_110WP_3_Control_DW.sf_Hold_h);

    /* InitializeConditions for UnitDelay: '<S12>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE_h = 0.0F;

    /* InitializeConditions for Chart: '<S12>/BWStart_OpenLoop' */
    CYS_110WP_3_Control_DW.CNT_Start_C = 0U;
    CYS_110WP_3_Control_DW.CNT_Start_B = 0U;
    CYS_110WP_3_Control_DW.Start_A = true;
    CYS_110WP_3_Control_DW.Start_B = false;
    CYS_110WP_3_Control_DW.Start_C = false;
    CYS_110WP_3_Control_DW.CNT_Start_C1 = 0U;
    CYS_110WP_3_Control_B.Accelerator = 0.0F;
    CYS_110WP_3_Control_B.EValve_Cycle_j = 0U;
    CYS_110WP_3_Control_B.EValve_Open_c = 0U;
    CYS_110WP_3_Control_B.Eblast_Cycle_j = 0U;
    CYS_110WP_3_Control_B.Eblast_Open_p = 0U;
    CYS_110WP_3_Control_B.Motor_Cycle_m = 0U;
    CYS_110WP_3_Control_B.Motor_Open_g = 0U;
    CYS_110WP_3_Control_B.EValve_Enable_o = 0U;
    CYS_110WP_3_Control_B.Eblast_Enable_j = 0U;
    CYS_110WP_3_Control_B.Motor_Enable_d = 0U;
    CYS_110WP_3_Control_B.SWO_Firework_l = 0U;
    CYS_110WP_3_Control_B.Flag_BWStartState_i = 0U;

    /* InitializeConditions for Chart: '<S12>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_p);

    /* End of InitializeConditions for SubSystem: '<S1>/BWStart' */

    /* Start for Merge: '<S1>/Merge' */
    CYS_110WP_3_Control_B.Merge = 0U;

    /* Start for Atomic SubSystem: '<S1>/ControlOut_Manage' */
    /* Start for Merge: '<S72>/Merge1' */
    for (i = 0; i < 5; i++) {
      CYS_110WP_3_Control_B.Merge1[i] = 0U;
    }

    /* End of Start for Merge: '<S72>/Merge1' */
    /* End of Start for SubSystem: '<S1>/ControlOut_Manage' */
    /* End of Start for SubSystem: '<Root>/CLM' */
    CYS_110WP_3_Control_PrevZCX.Flag_ECUReset_Reset_Trig_ZCE = ZERO_ZCSIG;

    /* InitializeConditions for Atomic SubSystem: '<Root>/COMMRead_ISM' */
    /* InitializeConditions for Atomic SubSystem: '<S2>/CMMRead' */
    /* InitializeConditions for Chart: '<S134>/H0_T0_计算' */
    CYS_110WP_3_Control_B.H_GPRS = 0.0F;

    /* InitializeConditions for UnitDelay: '<S134>/Time Delay1' */
    CYS_110WP_3_Control_DW.TimeDelay1_DSTATE = 288.15F;

    /* End of InitializeConditions for SubSystem: '<S2>/CMMRead' */

    /* InitializeConditions for Atomic SubSystem: '<S2>/ISM' */
    /* InitializeConditions for Chart: '<S190>/Xlim_Xdot_Judge' */
    CYS_110WP_3_Control_DW.true_b = true;
    CYS_110WP_3_Control_DW.CNT_X_p = 0U;
    CYS_110WP_3_Control_DW.false_l = false;
    CYS_110WP_3_Control_DW.CNT_Xdot = 0U;
    CYS_110WP_3_Control_B.X_Flag_Locking_p = false;
    CYS_110WP_3_Control_B.Xdot_Flag_Locking = false;

    /* InitializeConditions for Chart: '<S184>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_j0);

    /* InitializeConditions for Chart: '<S187>/Range' */
    CYS_110WP_3_Control_Range_Init(&CYS_110WP_3_Control_B.sf_Range_da);

    /* InitializeConditions for Chart: '<S189>/Xlim_Xdot_Judge' */
    CYS_110WP_3_Control_DW.true_n = true;
    CYS_110WP_3_Control_DW.CNT_X = 0U;
    CYS_110WP_3_Control_DW.false_c = false;
    CYS_110WP_3_Control_B.X_Flag_Locking = false;

    /* End of InitializeConditions for SubSystem: '<S2>/ISM' */
    /* End of InitializeConditions for SubSystem: '<Root>/COMMRead_ISM' */

    /* InitializeConditions for Atomic SubSystem: '<Root>/ESM' */
    /* InitializeConditions for Atomic SubSystem: '<S4>/StateTransition' */
    /* InitializeConditions for Chart: '<S205>/StateTranslation' */
    CYS_110WP_3_Control_DW.is_active_c2_CYS_110WP_3_Contro = 0U;
    CYS_110WP_3_Control_DW.is_c2_CYS_110WP_3_Control = 0U;

    /* End of InitializeConditions for SubSystem: '<S4>/StateTransition' */
    /* End of InitializeConditions for SubSystem: '<Root>/ESM' */

    /* InitializeConditions for Atomic SubSystem: '<Root>/FPM' */
    /* InitializeConditions for Chart: '<S5>/Up_Hold' */
    CYS_110WP_3_Contro_Up_Hold_Init(&CYS_110WP_3_Control_B.sf_Up_Hold);

    /* InitializeConditions for Chart: '<S240>/Hold_2000ms' */
    CYS_110WP_3_Control_DW.Cnt_f = 0U;

    /* InitializeConditions for Chart: '<S240>/Timmer_ms_Lock' */
    CYS_110WP_3_Timmer_ms_Lock_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms_Lock,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms_Lock);

    /* InitializeConditions for Chart: '<S240>/Hold_4000ms' */
    CYS_110WP_3_Control_DW.Cnt = 0U;

    /* End of InitializeConditions for SubSystem: '<Root>/FPM' */

    /* InitializeConditions for Atomic SubSystem: '<Root>/MAM' */

    /* InitializeConditions for Chart: '<S6>/Timmer_ms' */
    CYS_110WP_3_Co_Timmer_ms_d_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms_g,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms_g);

    /* InitializeConditions for Chart: '<S6>/Timmer_ms1' */
    CYS_110WP_3_Con_Timmer_ms1_Init(&CYS_110WP_3_Control_B.sf_Timmer_ms1,
      &CYS_110WP_3_Control_DW.sf_Timmer_ms1);

    /* End of InitializeConditions for SubSystem: '<Root>/MAM' */

    /* InitializeConditions for Atomic SubSystem: '<Root>/SaveData' */

    /* InitializeConditions for Chart: '<S8>/Hold' */
    CYS_110WP_3_Control_Hold_g_Init(&CYS_110WP_3_Control_B.sf_Hold_oi,
      &CYS_110WP_3_Control_DW.sf_Hold_oi);

    /* End of InitializeConditions for SubSystem: '<Root>/SaveData' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
