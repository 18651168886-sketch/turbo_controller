/*
 * File: CYS_110WP_3_Control.h
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

#ifndef RTW_HEADER_CYS_110WP_3_Control_h_
#define RTW_HEADER_CYS_110WP_3_Control_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef CYS_110WP_3_Control_COMMON_INCLUDES_
# define CYS_110WP_3_Control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* CYS_110WP_3_Control_COMMON_INCLUDES_ */

#include "CYS_110WP_3_Control_types.h"

/* Child system includes */
#include "EngineControl_GeneralModule.h"
#include "EngineControl_Timmer.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S17>/Range' */
typedef struct {
  real32_T Out;                        /* '<S17>/Range' */
} B_Range_CYS_110WP_3_Control_T;

/* Block signals (auto storage) */
typedef struct {
  real_T MathFunction1_g;              /* '<S175>/Math Function1' */
  real32_T H_GPRS;                     /* '<S134>/H0_T0_计算' */
  real32_T BWStart_Accelerator;        /* '<S12>/Signal Conversion' */
  real32_T Accelerator;                /* '<S12>/BWStart_OpenLoop' */
  real32_T Manual_Accelerator;         /* '<S15>/Signal Conversion' */
  real32_T ManualAcc_Min;              /* '<S15>/Signal Conversion' */
  real32_T ManualAcc_Max;              /* '<S15>/Signal Conversion' */
  real32_T Accelerator_p;              /* '<S18>/Signal Conversion' */
  real32_T Accelerator_k;              /* '<S18>/Stop_Control' */
  real32_T CloseLoop_Acclerator;       /* '<S13>/Signal Conversion' */
  real32_T CloseLoopMin;               /* '<S13>/Signal Conversion' */
  real32_T CloseLoopMax;               /* '<S13>/Signal Conversion' */
  real32_T AirStart_Accelerator;       /* '<S10>/Signal Conversion' */
  real32_T Accelerator_e;              /* '<S10>/Start_OpenLoop' */
  real32_T Start_Accelerator;          /* '<S17>/Signal Conversion' */
  real32_T Motor_Open;                 /* '<S17>/Signal Conversion' */
  real32_T Accelerator_c;              /* '<S17>/Start_OpenLoop' */
  real32_T Motor_Open_f;               /* '<S17>/Start_OpenLoop' */
  real32_T Accelerator_o;              /* '<S16>/Signal Conversion' */
  real32_T Origin_T4;                  /* '<S16>/Signal Conversion' */
  real32_T Origin_POil;                /* '<S16>/Signal Conversion' */
  real32_T Accelerator_m;              /* '<S16>/Cool_Control' */
  real32_T SumofElements1_e;           /* '<S179>/Sum of Elements1' */
  real32_T X_Out_a;                    /* '<S190>/Xlim_Xdot_Judge' */
  real32_T T_S;                        /* '<S188>/Divide' */
  real32_T Sqrt;                       /* '<S187>/Sqrt' */
  real32_T T4_X3_Y3;                   /* '<S185>/T4_X3_Y3' */
  real32_T Switch_e;                   /* '<S172>/Switch' */
  real32_T m1_h;                       /* '<S115>/Merge' */
  real32_T m2_j;                       /* '<S115>/Merge1' */
  real32_T m3_h;                       /* '<S115>/Merge2' */
  real32_T m4_ex;                      /* '<S115>/Merge3' */
  real32_T n1_n;                       /* '<S115>/Merge4' */
  real32_T n2_d;                       /* '<S115>/Merge5' */
  real32_T KpLookupTable1;             /* '<S134>/Kp Lookup Table1' */
  real32_T Product5_c;                 /* '<S134>/Product5' */
  real32_T SumofElements1_er;          /* '<S134>/Sum of Elements1' */
  real32_T Switch_g;                   /* '<S165>/Switch' */
  real32_T LookupTableDynamic3;        /* '<S49>/Lookup Table Dynamic3' */
  real32_T LookupTableDynamic3_j;      /* '<S31>/Lookup Table Dynamic3' */
  real32_T LookupTableDynamic2;        /* '<S31>/Lookup Table Dynamic2' */
  real32_T LookupTableDynamic1;        /* '<S31>/Lookup Table Dynamic1' */
  real32_T LookupTableDynamic;         /* '<S31>/Lookup Table Dynamic' */
  real32_T LookupTableDynamic4;        /* '<S121>/Lookup Table Dynamic4' */
  real32_T LookupTableDynamic3_b;      /* '<S121>/Lookup Table Dynamic3' */
  real32_T LookupTableDynamic2_g;      /* '<S121>/Lookup Table Dynamic2' */
  real32_T LookupTableDynamic1_o;      /* '<S121>/Lookup Table Dynamic1' */
  real32_T LookupTableDynamic_j;       /* '<S121>/Lookup Table Dynamic' */
  real32_T r;
  int32_T k;
  uint16_T EValve_Cycle;               /* '<S12>/Signal Conversion' */
  uint16_T EValve_Open;                /* '<S12>/Signal Conversion' */
  uint16_T Eblast_Cycle;               /* '<S12>/Signal Conversion' */
  uint16_T Eblast_Open;                /* '<S12>/Signal Conversion' */
  uint16_T Motor_Cycle;                /* '<S12>/Signal Conversion' */
  uint16_T Motor_Open_n;               /* '<S12>/Signal Conversion' */
  uint16_T EValve_Cycle_j;             /* '<S12>/BWStart_OpenLoop' */
  uint16_T EValve_Open_c;              /* '<S12>/BWStart_OpenLoop' */
  uint16_T Eblast_Cycle_j;             /* '<S12>/BWStart_OpenLoop' */
  uint16_T Eblast_Open_p;              /* '<S12>/BWStart_OpenLoop' */
  uint16_T Motor_Cycle_m;              /* '<S12>/BWStart_OpenLoop' */
  uint16_T Motor_Open_g;               /* '<S12>/BWStart_OpenLoop' */
  uint16_T Motor_Cycle_d;              /* '<S15>/Signal Conversion' */
  uint16_T Motor_Open_p;               /* '<S15>/Signal Conversion' */
  uint16_T EValve_Cycle_g;             /* '<S15>/Signal Conversion' */
  uint16_T EValve_Open_a;              /* '<S15>/Signal Conversion' */
  uint16_T Eblast_Cycle_g;             /* '<S15>/Signal Conversion' */
  uint16_T Eblast_Open_p4;             /* '<S15>/Signal Conversion' */
  uint16_T EValve_Cycle_n;             /* '<S18>/Signal Conversion' */
  uint16_T EValve_Open_h;              /* '<S18>/Signal Conversion' */
  uint16_T Eblast_Cycle_d;             /* '<S18>/Signal Conversion' */
  uint16_T Eblast_Open_d;              /* '<S18>/Signal Conversion' */
  uint16_T Motor_Cycle_a;              /* '<S18>/Signal Conversion' */
  uint16_T Motor_Open_pl;              /* '<S18>/Signal Conversion' */
  uint16_T EValve_Open_j;              /* '<S18>/Stop_Control' */
  uint16_T Eblast_Open_m;              /* '<S18>/Stop_Control' */
  uint16_T Motor_Open_pv;              /* '<S18>/Stop_Control' */
  uint16_T EValve_Cycle_n4;            /* '<S10>/Signal Conversion' */
  uint16_T EValve_Open_b;              /* '<S10>/Signal Conversion' */
  uint16_T Eblast_Cycle_l;             /* '<S10>/Signal Conversion' */
  uint16_T Eblast_Open_c;              /* '<S10>/Signal Conversion' */
  uint16_T Motor_Cycle_j;              /* '<S10>/Signal Conversion' */
  uint16_T Motor_Open_b;               /* '<S10>/Signal Conversion' */
  uint16_T EValve_Cycle_js;            /* '<S10>/Start_OpenLoop' */
  uint16_T EValve_Open_jc;             /* '<S10>/Start_OpenLoop' */
  uint16_T Eblast_Cycle_b;             /* '<S10>/Start_OpenLoop' */
  uint16_T Eblast_Open_n;              /* '<S10>/Start_OpenLoop' */
  uint16_T Motor_Cycle_c;              /* '<S10>/Start_OpenLoop' */
  uint16_T Motor_Open_nq;              /* '<S10>/Start_OpenLoop' */
  uint16_T EValve_Cycle_i;             /* '<S17>/Signal Conversion' */
  uint16_T EValve_Open_jg;             /* '<S17>/Signal Conversion' */
  uint16_T Eblast_Cycle_gv;            /* '<S17>/Signal Conversion' */
  uint16_T Eblast_Open_e;              /* '<S17>/Signal Conversion' */
  uint16_T Motor_Cycle_l;              /* '<S17>/Signal Conversion' */
  uint16_T EValve_Cycle_e;             /* '<S17>/Start_OpenLoop' */
  uint16_T EValve_Open_e;              /* '<S17>/Start_OpenLoop' */
  uint16_T Eblast_Cycle_o;             /* '<S17>/Start_OpenLoop' */
  uint16_T Eblast_Open_eu;             /* '<S17>/Start_OpenLoop' */
  uint16_T Motor_Cycle_i;              /* '<S17>/Start_OpenLoop' */
  uint16_T EValve_Cycle_k;             /* '<S16>/Signal Conversion' */
  uint16_T EValve_Open_m;              /* '<S16>/Signal Conversion' */
  uint16_T Eblast_Cycle_f;             /* '<S16>/Signal Conversion' */
  uint16_T Eblast_Open_pl;             /* '<S16>/Signal Conversion' */
  uint16_T Motor_Cycle_o;              /* '<S16>/Signal Conversion' */
  uint16_T Motor_Open_po;              /* '<S16>/Signal Conversion' */
  uint16_T EValve_Open_my;             /* '<S16>/Cool_Control' */
  uint8_T dthT02885;                   /* '<S250>/dth = T0-288.5' */
  uint8_T EngineState;                 /* '<S205>/StateTranslation' */
  uint8_T Merge;                       /* '<S1>/Merge' */
  uint8_T Motor_Enable;                /* '<S12>/Signal Conversion' */
  uint8_T SWO_Firework;                /* '<S12>/Signal Conversion' */
  uint8_T Flag_BWStartState;           /* '<S12>/Signal Conversion' */
  uint8_T SWO_BleedAir;                /* '<S12>/Signal Conversion' */
  uint8_T EValve_Enable;               /* '<S12>/Signal Conversion' */
  uint8_T Eblast_Enable;               /* '<S12>/Signal Conversion' */
  uint8_T EValve_Enable_o;             /* '<S12>/BWStart_OpenLoop' */
  uint8_T Eblast_Enable_j;             /* '<S12>/BWStart_OpenLoop' */
  uint8_T Motor_Enable_d;              /* '<S12>/BWStart_OpenLoop' */
  uint8_T SWO_Firework_l;              /* '<S12>/BWStart_OpenLoop' */
  uint8_T Flag_BWStartState_i;         /* '<S12>/BWStart_OpenLoop' */
  uint8_T Motor_Enable_i;              /* '<S15>/Signal Conversion' */
  uint8_T SWO_Firework_f;              /* '<S15>/Signal Conversion' */
  uint8_T SWO_BleedAir_e;              /* '<S15>/Signal Conversion' */
  uint8_T EValve_Enable_k;             /* '<S15>/Signal Conversion' */
  uint8_T Eblast_Enable_a;             /* '<S15>/Signal Conversion' */
  uint8_T Motor_Enable_h;              /* '<S18>/Signal Conversion' */
  uint8_T SWO_Firework_a;              /* '<S18>/Signal Conversion' */
  uint8_T StopFinish;                  /* '<S18>/Signal Conversion' */
  uint8_T SWO_BleedAIr;                /* '<S18>/Signal Conversion' */
  uint8_T EValve_Enable_ol;            /* '<S18>/Signal Conversion' */
  uint8_T Eblast_Enable_ae;            /* '<S18>/Signal Conversion' */
  uint8_T EValve_Enable_d;             /* '<S18>/Stop_Control' */
  uint8_T Eblast_Enable_e;             /* '<S18>/Stop_Control' */
  uint8_T Motor_Enable_e;              /* '<S18>/Stop_Control' */
  uint8_T StopFinish_l;                /* '<S18>/Stop_Control' */
  uint8_T SWO_BleedAir_j;              /* '<S13>/Signal Conversion' */
  uint8_T Motor_Enable_f;              /* '<S10>/Signal Conversion' */
  uint8_T SWO_Firework_h;              /* '<S10>/Signal Conversion' */
  uint8_T Flag_RunState;               /* '<S10>/Signal Conversion' */
  uint8_T SWO_BleedAir_m;              /* '<S10>/Signal Conversion' */
  uint8_T EValve_Enable_c;             /* '<S10>/Signal Conversion' */
  uint8_T Eblast_Enable_o;             /* '<S10>/Signal Conversion' */
  uint8_T EValve_Enable_ot;            /* '<S10>/Start_OpenLoop' */
  uint8_T Eblast_Enable_k;             /* '<S10>/Start_OpenLoop' */
  uint8_T Motor_Enable_p;              /* '<S10>/Start_OpenLoop' */
  uint8_T SWO_Firework_p;              /* '<S10>/Start_OpenLoop' */
  uint8_T Flag_EngineState;            /* '<S10>/Start_OpenLoop' */
  uint8_T Motor_Enable_b;              /* '<S17>/Signal Conversion' */
  uint8_T SWO_Firework_n;              /* '<S17>/Signal Conversion' */
  uint8_T Flag_RunState_f;             /* '<S17>/Signal Conversion' */
  uint8_T SWO_BleedAir_jd;             /* '<S17>/Signal Conversion' */
  uint8_T EValve_Enable_cr;            /* '<S17>/Signal Conversion' */
  uint8_T Eblast_Enable_oj;            /* '<S17>/Signal Conversion' */
  uint8_T EValve_Enable_n;             /* '<S17>/Start_OpenLoop' */
  uint8_T Eblast_Enable_h;             /* '<S17>/Start_OpenLoop' */
  uint8_T Motor_Enable_b1;             /* '<S17>/Start_OpenLoop' */
  uint8_T SWO_Firework_c;              /* '<S17>/Start_OpenLoop' */
  uint8_T Flag_EngineState_h;          /* '<S17>/Start_OpenLoop' */
  uint8_T Motor_Enable_pr;             /* '<S16>/Signal Conversion' */
  uint8_T SWO_Firework_cz;             /* '<S16>/Signal Conversion' */
  uint8_T SWO_BleedAir_a;              /* '<S16>/Signal Conversion' */
  uint8_T EValve_Enable_nf;            /* '<S16>/Signal Conversion' */
  uint8_T Eblast_Enable_hg;            /* '<S16>/Signal Conversion' */
  uint8_T EValve_Enable_b;             /* '<S16>/Cool_Control' */
  uint8_T Merge1[5];                   /* '<S72>/Merge1' */
  boolean_T X_Flag_Locking;            /* '<S189>/Xlim_Xdot_Judge' */
  boolean_T X_Flag_Locking_p;          /* '<S190>/Xlim_Xdot_Judge' */
  boolean_T Xdot_Flag_Locking;         /* '<S190>/Xlim_Xdot_Judge' */
  B_Hold_CYS_110WP_3_Control_d_T sf_Hold_oi;/* '<S8>/Hold' */
  B_Timmer_ms1_CYS_110WP_3_Cont_T sf_Timmer_ms1;/* '<S6>/Timmer_ms1' */
  B_Timmer_ms_CYS_110WP_3_Con_p_T sf_Timmer_ms_g;/* '<S6>/Timmer_ms' */
  B_Up_Hold_CYS_110WP_3_Control_T sf_Up_Hold;/* '<S5>/Up_Hold' */
  B_Timmer_ms_Lock_CYS_110WP_3__T sf_Timmer_ms_Lock;/* '<S240>/Timmer_ms_Lock' */
  B_LogicSelF_T LogicSelection3;       /* '<S209>/LogicSelection3' */
  B_Range_CYS_110WP_3_Control_T sf_Range_da;/* '<S187>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range_j0;/* '<S184>/Range' */
  B_Hold_CYS_110WP_3_Control_ac_T sf_Hold_h;/* '<S46>/Hold' */
  B_Range_CYS_110WP_3_Control_T sf_Range_p;/* '<S12>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range_ow;/* '<S87>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range_o;/* '<S86>/Range' */
  B_Hold_500ms_CYS_110WP_3_Cont_T sf_Hold_500ms;/* '<S95>/Hold_500ms' */
  B_Range_CYS_110WP_3_Control_T sf_Range_jg;/* '<S85>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range_h;/* '<S83>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range_d;/* '<S65>/Range' */
  B_Range_CYS_110WP_3_Control_T sf_Range1;/* '<S51>/Range1' */
  B_M_Rate_Limiter_CYS_110WP_3__T sf_M_Rate_Limiter;/* '<S57>/M_Rate_Limiter' */
  B_Hold_CYS_110WP_3_Control_a_T sf_Hold_g;/* '<S57>/Hold' */
  B_Timmer_ms_CYS_110WP_3_Contr_T sf_Timmer_ms_f;/* '<S24>/Timmer_ms' */
  B_Hold1_CYS_110WP_3_Control_T sf_Hold1;/* '<S24>/Hold1' */
  B_Hold_CYS_110WP_3_Control_T sf_Hold_o;/* '<S24>/Hold' */
  B_Range_CYS_110WP_3_Control_T sf_Range_j;/* '<S10>/Range' */
  B_Hold_CYS_110WP_3_Control_T sf_Hold_c;/* '<S20>/Hold' */
  B_Timmer_ms_CYS_110WP_3_Contr_T sf_Timmer_ms;/* '<S115>/Timmer_ms' */
  B_Hold_CYS_110WP_3_Control_T sf_Hold_n;/* '<S115>/Hold' */
  B_Range_CYS_110WP_3_Control_T sf_Range;/* '<S17>/Range' */
  B_Hold_CYS_110WP_3_Control_T sf_Hold;/* '<S111>/Hold' */
} B_CYS_110WP_3_Control_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T IntegerDelay1_DSTATE;       /* '<S190>/Integer Delay1' */
  real32_T UnitDelay1_DSTATE;          /* '<S190>/Unit Delay1' */
  real32_T UnitDelay_DSTATE;           /* '<S190>/Unit Delay' */
  real32_T IntegerDelay1_DSTATE_b;     /* '<S181>/Integer Delay1' */
  real32_T IntegerDelay1_DSTATE_j;     /* '<S182>/Integer Delay1' */
  real32_T IntegerDelay1_DSTATE_h;     /* '<S188>/Integer Delay1' */
  real32_T UnitDelay1_DSTATE_e;        /* '<S189>/Unit Delay1' */
  real32_T MoRenZhuangDing_DSTATE;     /* '<S133>/MoRenZhuangDing' */
  real32_T TimeDelay1_DSTATE;          /* '<S134>/Time Delay1' */
  real32_T TimeDelay2_13_DSTATE;       /* '<S1>/Time Delay2' */
  real32_T TimeDelay1_DSTATE_h;        /* '<S12>/Time Delay1' */
  real32_T Delay_DSTATE;               /* '<S57>/Delay' */
  real32_T TimeDelay8_DSTATE;          /* '<S51>/Time Delay8' */
  real32_T Delay_DSTATE_o;             /* '<S20>/Delay' */
  real32_T Delay1_DSTATE;              /* '<S20>/Delay1' */
  real32_T Delay1_DSTATE_o;            /* '<S24>/Delay1' */
  real32_T TimeDelay1_1_DSTATE;        /* '<S10>/Time Delay1' */
  real32_T TimeDelay1_2_DSTATE;        /* '<S10>/Time Delay1' */
  real32_T TimeDelay1_3_DSTATE;        /* '<S10>/Time Delay1' */
  real32_T TimeDelay1_4_DSTATE;        /* '<S10>/Time Delay1' */
  real32_T Delay_DSTATE_i;             /* '<S111>/Delay' */
  real32_T Delay1_DSTATE_a;            /* '<S111>/Delay1' */
  real32_T Delay1_DSTATE_e;            /* '<S115>/Delay1' */
  real32_T Delay2_DSTATE;              /* '<S115>/Delay2' */
  real32_T TimeDelay1_1_DSTATE_f;      /* '<S17>/Time Delay1' */
  real32_T TimeDelay1_2_DSTATE_p;      /* '<S17>/Time Delay1' */
  real32_T TimeDelay1_3_DSTATE_j;      /* '<S17>/Time Delay1' */
  real32_T TimeDelay1_4_DSTATE_c;      /* '<S17>/Time Delay1' */
  real32_T TimeDelay1_5_DSTATE;        /* '<S17>/Time Delay1' */
  real32_T TimeDelay1_6_DSTATE;        /* '<S17>/Time Delay1' */
  real32_T Delay_DSTATE_c;             /* '<S16>/Delay' */
  real32_T Delay1_DSTATE_og[2];        /* '<S16>/Delay1' */
  real32_T Delay2_DSTATE_n[3];         /* '<S16>/Delay2' */
  real32_T Delay3_DSTATE[4];           /* '<S16>/Delay3' */
  real32_T Delay4_DSTATE;              /* '<S16>/Delay4' */
  real32_T Delay5_DSTATE[2];           /* '<S16>/Delay5' */
  real32_T Delay6_DSTATE[3];           /* '<S16>/Delay6' */
  real32_T Delay7_DSTATE[4];           /* '<S16>/Delay7' */
  uint32_T Cnt;                        /* '<S240>/Hold_4000ms' */
  uint32_T Cnt_f;                      /* '<S240>/Hold_2000ms' */
  uint32_T CNT_X;                      /* '<S189>/Xlim_Xdot_Judge' */
  uint32_T CNT_X_p;                    /* '<S190>/Xlim_Xdot_Judge' */
  uint32_T CNT_Xdot;                   /* '<S190>/Xlim_Xdot_Judge' */
  uint32_T CNT_Start_C;                /* '<S12>/BWStart_OpenLoop' */
  uint32_T CNT_Start_B;                /* '<S12>/BWStart_OpenLoop' */
  uint32_T CNT_Start_C1;               /* '<S12>/BWStart_OpenLoop' */
  uint32_T CNT_Wait;                   /* '<S18>/Stop_Control' */
  uint32_T CNT_Motor;                  /* '<S18>/Stop_Control' */
  uint32_T CNT_Start_C_l;              /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_E;                /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_B_h;              /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_F;                /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_D;                /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_EValve_Open;            /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_A;                /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_POilHigh;               /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_C1_d;             /* '<S10>/Start_OpenLoop' */
  uint32_T CNT_Start_C_o;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_E_o;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_B_a;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_F_d;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Motor_b;                /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_D_f;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_EValve_Open_h;          /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_A_m;              /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_POilHigh_d;             /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_Start_C1_g;             /* '<S17>/Start_OpenLoop' */
  uint32_T CNT_EarthCoolTime;          /* '<S16>/Cool_Control' */
  uint32_T CNT_Global;                 /* '<S16>/Cool_Control' */
  uint16_T TimeDelay2_2_DSTATE;        /* '<S1>/Time Delay2' */
  uint16_T TimeDelay8_DSTATE_g;        /* '<S83>/Time Delay8' */
  uint16_T TimeDelay8_DSTATE_gl;       /* '<S87>/Time Delay8' */
  uint16_T Delay_DSTATE_f;             /* '<S24>/Delay' */
  uint16_T Delay_DSTATE_p;             /* '<S115>/Delay' */
  uint8_T DelayInput1_DSTATE;          /* '<S249>/Delay Input1' */
  uint8_T Delay_DSTATE_l;              /* '<S132>/Delay' */
  uint8_T TimeDelay2_11_DSTATE;        /* '<S1>/Time Delay2' */
  uint8_T TimeDelay2_7_DSTATE;         /* '<S1>/Time Delay2' */
  uint8_T TimeDelay8_DSTATE_p;         /* '<S84>/Time Delay8' */
  boolean_T TimeDelay1_DSTATE_i;       /* '<S83>/Time Delay1' */
  boolean_T Delay_DSTATE_fm;           /* '<S95>/Delay' */
  boolean_T TimeDelay1_DSTATE_j;       /* '<S87>/Time Delay1' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
  uint8_T is_active_c2_CYS_110WP_3_Contro;/* '<S205>/StateTranslation' */
  uint8_T is_c2_CYS_110WP_3_Control;   /* '<S205>/StateTranslation' */
  uint8_T Motor_OFF_Enable;            /* '<S17>/Start_OpenLoop' */
  boolean_T true_n;                    /* '<S189>/Xlim_Xdot_Judge' */
  boolean_T false_c;                   /* '<S189>/Xlim_Xdot_Judge' */
  boolean_T true_b;                    /* '<S190>/Xlim_Xdot_Judge' */
  boolean_T false_l;                   /* '<S190>/Xlim_Xdot_Judge' */
  boolean_T Start_A;                   /* '<S12>/BWStart_OpenLoop' */
  boolean_T Start_B;                   /* '<S12>/BWStart_OpenLoop' */
  boolean_T Start_C;                   /* '<S12>/BWStart_OpenLoop' */
  boolean_T Start_A_h;                 /* '<S10>/Start_OpenLoop' */
  boolean_T Start_B_l;                 /* '<S10>/Start_OpenLoop' */
  boolean_T Start_C_o;                 /* '<S10>/Start_OpenLoop' */
  boolean_T Start_D;                   /* '<S10>/Start_OpenLoop' */
  boolean_T Start_E;                   /* '<S10>/Start_OpenLoop' */
  boolean_T Start_F;                   /* '<S10>/Start_OpenLoop' */
  boolean_T Start_A_o;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Start_B_h;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Start_C_i;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Start_D_j;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Start_E_a;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Start_F_k;                 /* '<S17>/Start_OpenLoop' */
  boolean_T Flag_IntoC;                /* '<S17>/Start_OpenLoop' */
  boolean_T EarthStop;                 /* '<S16>/Cool_Control' */
  boolean_T CoolDoneFlag;              /* '<S16>/Cool_Control' */
  boolean_T Flag_ECUReset_Reset_MODE;  /* '<S240>/Flag_ECUReset_Reset' */
  DW_Hold_CYS_110WP_3_Control_b_T sf_Hold_oi;/* '<S8>/Hold' */
  DW_Timmer_ms1_CYS_110WP_3_Con_T sf_Timmer_ms1;/* '<S6>/Timmer_ms1' */
  DW_Timmer_ms_CYS_110WP_3_Co_p_T sf_Timmer_ms_g;/* '<S6>/Timmer_ms' */
  DW_Timmer_ms_Lock_CYS_110WP_3_T sf_Timmer_ms_Lock;/* '<S240>/Timmer_ms_Lock' */
  DW_Hold_CYS_110WP_3_Control_o_T sf_Hold_h;/* '<S46>/Hold' */
  DW_Hold_500ms_CYS_110WP_3_Con_T sf_Hold_500ms;/* '<S95>/Hold_500ms' */
  DW_M_Rate_Limiter_CYS_110WP_3_T sf_M_Rate_Limiter;/* '<S57>/M_Rate_Limiter' */
  DW_Hold_CYS_110WP_3_Control_f_T sf_Hold_g;/* '<S57>/Hold' */
  DW_Timmer_ms_CYS_110WP_3_Cont_T sf_Timmer_ms_f;/* '<S24>/Timmer_ms' */
  DW_Hold1_CYS_110WP_3_Control_T sf_Hold1;/* '<S24>/Hold1' */
  DW_Hold_CYS_110WP_3_Control_T sf_Hold_o;/* '<S24>/Hold' */
  DW_Hold_CYS_110WP_3_Control_T sf_Hold_c;/* '<S20>/Hold' */
  DW_Timmer_ms_CYS_110WP_3_Cont_T sf_Timmer_ms;/* '<S115>/Timmer_ms' */
  DW_Hold_CYS_110WP_3_Control_T sf_Hold_n;/* '<S115>/Hold' */
  DW_Hold_CYS_110WP_3_Control_T sf_Hold;/* '<S111>/Hold' */
} DW_CYS_110WP_3_Control_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Flag_ECUReset_Reset_Trig_ZCE;/* '<S240>/Flag_ECUReset_Reset' */
} PrevZCX_CYS_110WP_3_Control_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: Constant2_Value_m
   * Referenced by: '<S121>/Constant2'
   */
  real32_T Constant2_Value_m[2];

  /* Computed Parameter: Constant4_Value_l
   * Referenced by: '<S121>/Constant4'
   */
  real32_T Constant4_Value_l[2];

  /* Computed Parameter: Constant6_Value_c
   * Referenced by: '<S121>/Constant6'
   */
  real32_T Constant6_Value_c[2];

  /* Computed Parameter: Constant8_Value
   * Referenced by: '<S121>/Constant8'
   */
  real32_T Constant8_Value[2];

  /* Pooled Parameter (Expression: [1600 1900])
   * Referenced by:
   *   '<S31>/Constant'
   *   '<S121>/Constant'
   */
  real32_T pooled6[2];

  /* Computed Parameter: Constant2_Value_mw
   * Referenced by: '<S31>/Constant2'
   */
  real32_T Constant2_Value_mw[2];

  /* Computed Parameter: Constant4_Value_ls
   * Referenced by: '<S31>/Constant4'
   */
  real32_T Constant4_Value_ls[2];

  /* Computed Parameter: Constant6_Value_n
   * Referenced by: '<S31>/Constant6'
   */
  real32_T Constant6_Value_n[2];

  /* Pooled Parameter (Expression: [0.00058 0.00008 0.00167 0.00156 0.00215 0.00369 0.00575 0.00684 0.00779 0.008])
   * Referenced by:
   *   '<S56>/Ki Lookup Table'
   *   '<S56>/Ki Lookup Table1'
   */
  real32_T pooled15[10];

  /* Pooled Parameter (Expression: [20654 25856 30525 36143 41286 46305 51127 56000 58302 60355])
   * Referenced by:
   *   '<S56>/Ki Lookup Table'
   *   '<S56>/Ki Lookup Table1'
   *   '<S56>/Kp Lookup Table'
   *   '<S56>/Kp Lookup Table1'
   */
  real32_T pooled16[10];

  /* Pooled Parameter (Expression: [0.0058 0.0006 0.0119 0.0097 0.012 0.0185 0.0287 0.0342 0.039 0.04])
   * Referenced by:
   *   '<S56>/Kp Lookup Table'
   *   '<S56>/Kp Lookup Table1'
   */
  real32_T pooled17[10];

  /* Pooled Parameter (Expression: [40000 62000])
   * Referenced by:
   *   '<S53>/N1r_idle17'
   *   '<S53>/N1r_idle2'
   *   '<S53>/N1r_idle4'
   */
  real32_T pooled22[2];

  /* Computed Parameter: N1r_idle1_Value
   * Referenced by: '<S53>/N1r_idle1'
   */
  real32_T N1r_idle1_Value[2];

  /* Computed Parameter: N1r_idle3_Value
   * Referenced by: '<S53>/N1r_idle3'
   */
  real32_T N1r_idle3_Value[2];

  /* Computed Parameter: N1r_idle5_Value
   * Referenced by: '<S53>/N1r_idle5'
   */
  real32_T N1r_idle5_Value[2];

  /* Computed Parameter: Constant6_Value_g
   * Referenced by: '<S49>/Constant6'
   */
  real32_T Constant6_Value_g[2];

  /* Computed Parameter: KpLookupTable1_tableData
   * Referenced by: '<S134>/Kp Lookup Table1'
   */
  real32_T KpLookupTable1_tableData[2];

  /* Computed Parameter: KpLookupTable1_bp01Data
   * Referenced by: '<S134>/Kp Lookup Table1'
   */
  real32_T KpLookupTable1_bp01Data[2];

  /* Computed Parameter: Bit2V_tableData
   * Referenced by: '<S183>/Bit2V'
   */
  real32_T Bit2V_tableData[2];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S183>/Bit2V'
   *   '<S185>/T4_X1_Y1'
   *   '<S186>/Bit2V'
   */
  real32_T pooled32[2];

  /* Expression: PF_Sensor_Y_Poil
   * Referenced by: '<S183>/POil_X_Y'
   */
  real32_T POil_X_Y_tableData[2];

  /* Expression: PF_Sensor_X_Poil
   * Referenced by: '<S183>/POil_X_Y'
   */
  real32_T POil_X_Y_bp01Data[2];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S185>/T4_X1_Y1'
   *   '<S186>/Bit2V'
   */
  real32_T pooled33[2];

  /* Expression: PF_Sensor_Y2_T4
   * Referenced by: '<S185>/T4_X2_Y2'
   */
  real32_T T4_X2_Y2_tableData[2];

  /* Expression: PF_Sensor_X2_T4
   * Referenced by: '<S185>/T4_X2_Y2'
   */
  real32_T T4_X2_Y2_bp01Data[2];

  /* Expression: PF_Sensor_Y3_T4
   * Referenced by: '<S185>/T4_X3_Y3'
   */
  real32_T T4_X3_Y3_tableData[11];

  /* Expression: PF_Sensor_X3_T4
   * Referenced by: '<S185>/T4_X3_Y3'
   */
  real32_T T4_X3_Y3_bp01Data[11];

  /* Computed Parameter: Constant2_Value_l
   * Referenced by: '<S115>/Constant2'
   */
  uint16_T Constant2_Value_l[2];

  /* Computed Parameter: Constant4_Value_g
   * Referenced by: '<S115>/Constant4'
   */
  uint16_T Constant4_Value_g[2];

  /* Pooled Parameter (Expression: [30 50])
   * Referenced by:
   *   '<S24>/Constant'
   *   '<S115>/Constant'
   */
  uint16_T pooled45[2];
} ConstP_CYS_110WP_3_Control_T;

/* Parameters (auto storage) */
struct P_CYS_110WP_3_Control_T_ {
  real32_T PF_ACCFULLRANGE;            /* Variable: PF_ACCFULLRANGE
                                        * Referenced by:
                                        *   '<S16>/PG_CtrlMode_Start1'
                                        *   '<S18>/PG_CtrlMode_Start1'
                                        */
  real32_T PF_Gear_Info[12];           /* Variable: PF_Gear_Info
                                        * Referenced by: '<S162>/档位信息数组'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_CYS_110WP_3_Control_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_CYS_110WP_3_Control_T CYS_110WP_3_Control_P;

/* Block signals (auto storage) */
extern B_CYS_110WP_3_Control_T CYS_110WP_3_Control_B;

/* Block states (auto storage) */
extern DW_CYS_110WP_3_Control_T CYS_110WP_3_Control_DW;

/* Constant parameters (auto storage) */
extern const ConstP_CYS_110WP_3_Control_T CYS_110WP_3_Control_ConstP;

/* External data declarations for dependent source files */

/* Zero-crossing (trigger) state */
extern PrevZCX_CYS_110WP_3_Control_T CYS_110WP_3_Control_PrevZCX;

/* Model entry point functions */
extern void ECU_110WP_C_Control_initialize(void);

/* Customized model step function */
extern void ECU_110WP_C_Control_Run(uint8_T *arg_Flag_rx_suc, uint8_T
  arg_MyUsart2_Rxdata[50], uint8_T *arg_Flag_ECUReset, uint8_T
  arg_ECUReset_Information[20], uint8_T arg_MySet_Rxdata[50], real32_T arg_Nc,
  real32_T arg_T4, real32_T arg_S_Vpower, real32_T arg_Tecu, uint8_T
  arg_SWI_Firework, uint8_T arg_SWI_EValve, uint8_T arg_SWI_Eblast, uint8_T
  arg_SWI_ValveErr, uint8_T arg_SWI_BleedAir, real32_T arg_POil, real32_T arg_T0,
  EngineControl_Out *arg_Controldata, SaveData_Out *arg_savedata, SendData_Out
  *arg_senddata);

/* Real-time Model object */
extern RT_MODEL_CYS_110WP_3_Control_T *const CYS_110WP_3_Control_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CYS_110WP_3_Control'
 * '<S1>'   : 'CYS_110WP_3_Control/CLM'
 * '<S2>'   : 'CYS_110WP_3_Control/COMMRead_ISM'
 * '<S3>'   : 'CYS_110WP_3_Control/ControlOut'
 * '<S4>'   : 'CYS_110WP_3_Control/ESM'
 * '<S5>'   : 'CYS_110WP_3_Control/FPM'
 * '<S6>'   : 'CYS_110WP_3_Control/MAM'
 * '<S7>'   : 'CYS_110WP_3_Control/SDM'
 * '<S8>'   : 'CYS_110WP_3_Control/SaveData'
 * '<S9>'   : 'CYS_110WP_3_Control/SendData'
 * '<S10>'  : 'CYS_110WP_3_Control/CLM/AirStart'
 * '<S11>'  : 'CYS_110WP_3_Control/CLM/AirStart1'
 * '<S12>'  : 'CYS_110WP_3_Control/CLM/BWStart'
 * '<S13>'  : 'CYS_110WP_3_Control/CLM/ClpControl'
 * '<S14>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage'
 * '<S15>'  : 'CYS_110WP_3_Control/CLM/Manual'
 * '<S16>'  : 'CYS_110WP_3_Control/CLM/Origin'
 * '<S17>'  : 'CYS_110WP_3_Control/CLM/Start'
 * '<S18>'  : 'CYS_110WP_3_Control/CLM/Stop'
 * '<S19>'  : 'CYS_110WP_3_Control/CLM/AirStart/DaYu5000'
 * '<S20>'  : 'CYS_110WP_3_Control/CLM/AirStart/HoldFirst'
 * '<S21>'  : 'CYS_110WP_3_Control/CLM/AirStart/LogicSelection2'
 * '<S22>'  : 'CYS_110WP_3_Control/CLM/AirStart/Range'
 * '<S23>'  : 'CYS_110WP_3_Control/CLM/AirStart/Start_OpenLoop'
 * '<S24>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem'
 * '<S25>'  : 'CYS_110WP_3_Control/CLM/AirStart/HoldFirst/Hold'
 * '<S26>'  : 'CYS_110WP_3_Control/CLM/AirStart/HoldFirst/LogicSelection1'
 * '<S27>'  : 'CYS_110WP_3_Control/CLM/AirStart/HoldFirst/LogicSelection2'
 * '<S28>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/Hold'
 * '<S29>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/Hold1'
 * '<S30>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/If Action Subsystem'
 * '<S31>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/If Action Subsystem1'
 * '<S32>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/LogicSelection1'
 * '<S33>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/LogicSelection2'
 * '<S34>'  : 'CYS_110WP_3_Control/CLM/AirStart/Subsystem/Timmer_ms'
 * '<S35>'  : 'CYS_110WP_3_Control/CLM/AirStart1/DaYu5000'
 * '<S36>'  : 'CYS_110WP_3_Control/CLM/AirStart1/HoldFirst'
 * '<S37>'  : 'CYS_110WP_3_Control/CLM/AirStart1/LogicSelection2'
 * '<S38>'  : 'CYS_110WP_3_Control/CLM/AirStart1/Range'
 * '<S39>'  : 'CYS_110WP_3_Control/CLM/AirStart1/Start_OpenLoop'
 * '<S40>'  : 'CYS_110WP_3_Control/CLM/AirStart1/HoldFirst/Hold'
 * '<S41>'  : 'CYS_110WP_3_Control/CLM/AirStart1/HoldFirst/LogicSelection1'
 * '<S42>'  : 'CYS_110WP_3_Control/CLM/BWStart/BWStart_OpenLoop'
 * '<S43>'  : 'CYS_110WP_3_Control/CLM/BWStart/DaYu5000'
 * '<S44>'  : 'CYS_110WP_3_Control/CLM/BWStart/LogicSelection2'
 * '<S45>'  : 'CYS_110WP_3_Control/CLM/BWStart/Range'
 * '<S46>'  : 'CYS_110WP_3_Control/CLM/BWStart/Subsystem'
 * '<S47>'  : 'CYS_110WP_3_Control/CLM/BWStart/Subsystem/Hold'
 * '<S48>'  : 'CYS_110WP_3_Control/CLM/BWStart/Subsystem/If Action Subsystem'
 * '<S49>'  : 'CYS_110WP_3_Control/CLM/BWStart/Subsystem/If Action Subsystem1'
 * '<S50>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate'
 * '<S51>'  : 'CYS_110WP_3_Control/CLM/ClpControl/CtrlLaw'
 * '<S52>'  : 'CYS_110WP_3_Control/CLM/ClpControl/DaYu5000'
 * '<S53>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process'
 * '<S54>'  : 'CYS_110WP_3_Control/CLM/ClpControl/LogicSelection1'
 * '<S55>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1'
 * '<S56>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/PIParameter_Cal'
 * '<S57>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst'
 * '<S58>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/Hold'
 * '<S59>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/LogicSelection1'
 * '<S60>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/M_Rate_Limiter'
 * '<S61>'  : 'CYS_110WP_3_Control/CLM/ClpControl/CtrlLaw/LogicSelection1'
 * '<S62>'  : 'CYS_110WP_3_Control/CLM/ClpControl/CtrlLaw/Range'
 * '<S63>'  : 'CYS_110WP_3_Control/CLM/ClpControl/CtrlLaw/Range1'
 * '<S64>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/D9-Nr-T5r'
 * '<S65>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/GeneralFilter'
 * '<S66>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/LogicSelection1'
 * '<S67>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/LogicSelection2'
 * '<S68>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/GeneralFilter/LogicSelection1'
 * '<S69>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/GeneralFilter/LogicSelection2'
 * '<S70>'  : 'CYS_110WP_3_Control/CLM/ClpControl/Fault_Process/GeneralFilter/Range'
 * '<S71>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/Accelerator_Manage'
 * '<S72>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage'
 * '<S73>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/Accelerator_Manage/LogicSelection3'
 * '<S74>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/Accelerator_Manage/ServoCtrlOut'
 * '<S75>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem'
 * '<S76>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem1'
 * '<S77>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem2'
 * '<S78>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem3'
 * '<S79>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem4'
 * '<S80>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem5'
 * '<S81>'  : 'CYS_110WP_3_Control/CLM/ControlOut_Manage/SWO_Manage/Switch Case Action Subsystem6'
 * '<S82>'  : 'CYS_110WP_3_Control/CLM/Manual/BleedAir_Control'
 * '<S83>'  : 'CYS_110WP_3_Control/CLM/Manual/Eblast_Control'
 * '<S84>'  : 'CYS_110WP_3_Control/CLM/Manual/Firework_Control'
 * '<S85>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control'
 * '<S86>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualEValve_Control'
 * '<S87>'  : 'CYS_110WP_3_Control/CLM/Manual/Motor_Control'
 * '<S88>'  : 'CYS_110WP_3_Control/CLM/Manual/BleedAir_Control/LogicSelection1'
 * '<S89>'  : 'CYS_110WP_3_Control/CLM/Manual/Eblast_Control/LogicSelection1'
 * '<S90>'  : 'CYS_110WP_3_Control/CLM/Manual/Eblast_Control/LogicSelection2'
 * '<S91>'  : 'CYS_110WP_3_Control/CLM/Manual/Eblast_Control/Range'
 * '<S92>'  : 'CYS_110WP_3_Control/CLM/Manual/Firework_Control/LogicSelection1'
 * '<S93>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/LogicSelection1'
 * '<S94>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/Range'
 * '<S95>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减'
 * '<S96>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/ '
 * '<S97>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/Hold_500ms'
 * '<S98>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/LogicSelection1'
 * '<S99>'  : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/LogicSelection3'
 * '<S100>' : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/ /LogicSelection1'
 * '<S101>' : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/ /LogicSelection2'
 * '<S102>' : 'CYS_110WP_3_Control/CLM/Manual/ManualAcc_Min_Control/手动加减/ /LogicSelection3'
 * '<S103>' : 'CYS_110WP_3_Control/CLM/Manual/ManualEValve_Control/LogicSelection1'
 * '<S104>' : 'CYS_110WP_3_Control/CLM/Manual/ManualEValve_Control/LogicSelection2'
 * '<S105>' : 'CYS_110WP_3_Control/CLM/Manual/ManualEValve_Control/Range'
 * '<S106>' : 'CYS_110WP_3_Control/CLM/Manual/Motor_Control/LogicSelection1'
 * '<S107>' : 'CYS_110WP_3_Control/CLM/Manual/Motor_Control/LogicSelection2'
 * '<S108>' : 'CYS_110WP_3_Control/CLM/Manual/Motor_Control/Range'
 * '<S109>' : 'CYS_110WP_3_Control/CLM/Origin/Cool_Control'
 * '<S110>' : 'CYS_110WP_3_Control/CLM/Start/DaYu5000'
 * '<S111>' : 'CYS_110WP_3_Control/CLM/Start/HoldFirst'
 * '<S112>' : 'CYS_110WP_3_Control/CLM/Start/LogicSelection2'
 * '<S113>' : 'CYS_110WP_3_Control/CLM/Start/Range'
 * '<S114>' : 'CYS_110WP_3_Control/CLM/Start/Start_OpenLoop'
 * '<S115>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem'
 * '<S116>' : 'CYS_110WP_3_Control/CLM/Start/HoldFirst/Hold'
 * '<S117>' : 'CYS_110WP_3_Control/CLM/Start/HoldFirst/LogicSelection1'
 * '<S118>' : 'CYS_110WP_3_Control/CLM/Start/HoldFirst/LogicSelection2'
 * '<S119>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/Hold'
 * '<S120>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/If Action Subsystem'
 * '<S121>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/If Action Subsystem1'
 * '<S122>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/LogicSelection1'
 * '<S123>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/LogicSelection2'
 * '<S124>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/LogicSelection3'
 * '<S125>' : 'CYS_110WP_3_Control/CLM/Start/Subsystem/Timmer_ms'
 * '<S126>' : 'CYS_110WP_3_Control/CLM/Stop/Stop_Control'
 * '<S127>' : 'CYS_110WP_3_Control/CLM/Stop/TingCheZhiLing1'
 * '<S128>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead'
 * '<S129>' : 'CYS_110WP_3_Control/COMMRead_ISM/ECUReset_Information_Read'
 * '<S130>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM'
 * '<S131>' : 'CYS_110WP_3_Control/COMMRead_ISM/MySet_Rxdatan_Read'
 * '<S132>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse'
 * '<S133>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse'
 * '<S134>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal'
 * '<S135>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/LogicSelection1'
 * '<S136>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/LogicSelection3'
 * '<S137>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/ShouDongJia'
 * '<S138>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/binwanstart'
 * '<S139>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/cachu'
 * '<S140>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/chongzhi'
 * '<S141>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/jinjitingche'
 * '<S142>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/kongzhongqidong'
 * '<S143>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/qidong'
 * '<S144>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingDianHuoQi'
 * '<S145>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingDianJi'
 * '<S146>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingFuFa'
 * '<S147>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingZhuFa'
 * '<S148>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingyingqi'
 * '<S149>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shedingyoumen'
 * '<S150>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/shoudongjian'
 * '<S151>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/tingche'
 * '<S152>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/zijian'
 * '<S153>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/装订和档位控制'
 * '<S154>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/装订和档位控制/dangwei'
 * '<S155>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/装订和档位控制/zhuangding'
 * '<S156>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/装订和档位控制/取高8位'
 * '<S157>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/Instr_Analyse/装订和档位控制/最大档位'
 * '<S158>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/LogicSelection1'
 * '<S159>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/LogicSelection2'
 * '<S160>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/LogicSelection4'
 * '<S161>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/LogicSelection5'
 * '<S162>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal'
 * '<S163>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/初始状态1'
 * '<S164>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/初始状态2'
 * '<S165>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal/LogicSelection1'
 * '<S166>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal/LogicSelection5'
 * '<S167>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal/dangwei'
 * '<S168>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal/zhuangding'
 * '<S169>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/SpeedLoad_Analyse/Speed_Load_Cal/取高4位'
 * '<S170>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/Dynamic_Cal'
 * '<S171>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/H0_T0_计算'
 * '<S172>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/LogicSelection1'
 * '<S173>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/LogicSelection5'
 * '<S174>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/Dynamic_Cal/P1H_T1H'
 * '<S175>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/Dynamic_Cal/dynamic '
 * '<S176>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/Dynamic_Cal/P1H_T1H/LogicSelection1'
 * '<S177>' : 'CYS_110WP_3_Control/COMMRead_ISM/CMMRead/T1t_P1t_Cal/Dynamic_Cal/P1H_T1H/LogicSelection2'
 * '<S178>' : 'CYS_110WP_3_Control/COMMRead_ISM/ECUReset_Information_Read/ECUReset_Acclerator_Cal'
 * '<S179>' : 'CYS_110WP_3_Control/COMMRead_ISM/ECUReset_Information_Read/Flag_ECUReset_Manage'
 * '<S180>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc'
 * '<S181>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Poil'
 * '<S182>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_T4'
 * '<S183>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Calibrating_Poil'
 * '<S184>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Calibrating_T0'
 * '<S185>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Calibrating_T4'
 * '<S186>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Calibrating_Tecu'
 * '<S187>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/HuanSuanN'
 * '<S188>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Origin_Nc_Filter'
 * '<S189>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Subsystem2'
 * '<S190>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter'
 * '<S191>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc/LogicSelection3'
 * '<S192>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Subsystem1'
 * '<S193>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Subsystem2'
 * '<S194>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Nc/GeneralFilter/Xlim_Xdot_Judge'
 * '<S195>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Poil/Subsystem1'
 * '<S196>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_Poil/Subsystem2'
 * '<S197>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_T4/Subsystem1'
 * '<S198>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/AnalogFilter_T4/Subsystem2'
 * '<S199>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Calibrating_T0/Range'
 * '<S200>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/HuanSuanN/Range'
 * '<S201>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Origin_Nc_Filter/Subsystem1'
 * '<S202>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Origin_Nc_Filter/Subsystem2'
 * '<S203>' : 'CYS_110WP_3_Control/COMMRead_ISM/ISM/Subsystem2/Xlim_Xdot_Judge'
 * '<S204>' : 'CYS_110WP_3_Control/ESM/Flags'
 * '<S205>' : 'CYS_110WP_3_Control/ESM/StateTransition'
 * '<S206>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp'
 * '<S207>' : 'CYS_110WP_3_Control/ESM/Flags/EngineOrigin'
 * '<S208>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart'
 * '<S209>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop'
 * '<S210>' : 'CYS_110WP_3_Control/ESM/Flags/Manual'
 * '<S211>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp/BiHuanZhiLing'
 * '<S212>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp/Compare To Constant'
 * '<S213>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp/Compare To Constant1'
 * '<S214>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp/Compare To Constant2'
 * '<S215>' : 'CYS_110WP_3_Control/ESM/Flags/EngineClp/LogicSelection1'
 * '<S216>' : 'CYS_110WP_3_Control/ESM/Flags/EngineOrigin/Compare To Constant2'
 * '<S217>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/BinWanQiDongZhiLing'
 * '<S218>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant'
 * '<S219>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant1'
 * '<S220>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant2'
 * '<S221>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant3'
 * '<S222>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant4'
 * '<S223>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant5'
 * '<S224>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/Compare To Constant6'
 * '<S225>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStart/QiDongZhiLing'
 * '<S226>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop/Compare To Constant1'
 * '<S227>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop/Compare To Constant2'
 * '<S228>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop/LogicSelection3'
 * '<S229>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop/TingCheZhiLing'
 * '<S230>' : 'CYS_110WP_3_Control/ESM/Flags/EngineStop/TingCheZhiLing1'
 * '<S231>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongBeiFa'
 * '<S232>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongDianHuo'
 * '<S233>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongDianJi'
 * '<S234>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongJia'
 * '<S235>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongJian'
 * '<S236>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongYinQi'
 * '<S237>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongYouMen'
 * '<S238>' : 'CYS_110WP_3_Control/ESM/Flags/Manual/ShouDongZhuFa'
 * '<S239>' : 'CYS_110WP_3_Control/ESM/StateTransition/StateTranslation'
 * '<S240>' : 'CYS_110WP_3_Control/FPM/Subsystem'
 * '<S241>' : 'CYS_110WP_3_Control/FPM/Up_Hold'
 * '<S242>' : 'CYS_110WP_3_Control/FPM/停车状态'
 * '<S243>' : 'CYS_110WP_3_Control/FPM/初始状态'
 * '<S244>' : 'CYS_110WP_3_Control/FPM/手动'
 * '<S245>' : 'CYS_110WP_3_Control/FPM/起动'
 * '<S246>' : 'CYS_110WP_3_Control/FPM/超转保护'
 * '<S247>' : 'CYS_110WP_3_Control/FPM/重置指令'
 * '<S248>' : 'CYS_110WP_3_Control/FPM/闭环'
 * '<S249>' : 'CYS_110WP_3_Control/FPM/Subsystem/Detect Change'
 * '<S250>' : 'CYS_110WP_3_Control/FPM/Subsystem/Flag_ECUReset_Reset'
 * '<S251>' : 'CYS_110WP_3_Control/FPM/Subsystem/Hold_2000ms'
 * '<S252>' : 'CYS_110WP_3_Control/FPM/Subsystem/Hold_4000ms'
 * '<S253>' : 'CYS_110WP_3_Control/FPM/Subsystem/Timmer_ms_Lock'
 * '<S254>' : 'CYS_110WP_3_Control/FPM/Subsystem/运行状态'
 * '<S255>' : 'CYS_110WP_3_Control/FPM/Subsystem/闭环状态'
 * '<S256>' : 'CYS_110WP_3_Control/MAM/Timmer_ms'
 * '<S257>' : 'CYS_110WP_3_Control/MAM/Timmer_ms1'
 * '<S258>' : 'CYS_110WP_3_Control/SDM/LogicSelection3'
 * '<S259>' : 'CYS_110WP_3_Control/SDM/T4_Check'
 * '<S260>' : 'CYS_110WP_3_Control/SaveData/Hold'
 * '<S261>' : 'CYS_110WP_3_Control/SendData/Extract Bits1'
 * '<S262>' : 'CYS_110WP_3_Control/SendData/Extract Bits10'
 * '<S263>' : 'CYS_110WP_3_Control/SendData/Extract Bits2'
 * '<S264>' : 'CYS_110WP_3_Control/SendData/Extract Bits3'
 * '<S265>' : 'CYS_110WP_3_Control/SendData/Extract Bits4'
 * '<S266>' : 'CYS_110WP_3_Control/SendData/Extract Bits5'
 * '<S267>' : 'CYS_110WP_3_Control/SendData/Extract Bits6'
 * '<S268>' : 'CYS_110WP_3_Control/SendData/Extract Bits7'
 * '<S269>' : 'CYS_110WP_3_Control/SendData/Extract Bits8'
 * '<S270>' : 'CYS_110WP_3_Control/SendData/Extract Bits9'
 * '<S271>' : 'CYS_110WP_3_Control/SendData/ZhuangTaiJiSuan'
 */
#endif                                 /* RTW_HEADER_CYS_110WP_3_Control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
