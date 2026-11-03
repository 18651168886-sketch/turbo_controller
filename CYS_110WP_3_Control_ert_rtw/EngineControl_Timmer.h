/*
 * File: EngineControl_Timmer.h
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

#ifndef RTW_HEADER_EngineControl_Timmer_h_
#define RTW_HEADER_EngineControl_Timmer_h_
#ifndef CYS_110WP_3_Control_COMMON_INCLUDES_
# define CYS_110WP_3_Control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* CYS_110WP_3_Control_COMMON_INCLUDES_ */

#include "CYS_110WP_3_Control_types.h"

/* Block signals for system '<S111>/Hold' */
typedef struct {
  boolean_T Out;                       /* '<S111>/Hold' */
} B_Hold_CYS_110WP_3_Control_T;

/* Block states (auto storage) for system '<S111>/Hold' */
typedef struct {
  boolean_T Flag_First;                /* '<S111>/Hold' */
} DW_Hold_CYS_110WP_3_Control_T;

/* Block signals for system '<S115>/Timmer_ms' */
typedef struct {
  uint8_T Out;                         /* '<S115>/Timmer_ms' */
} B_Timmer_ms_CYS_110WP_3_Contr_T;

/* Block states (auto storage) for system '<S115>/Timmer_ms' */
typedef struct {
  uint32_T Cnt;                        /* '<S115>/Timmer_ms' */
} DW_Timmer_ms_CYS_110WP_3_Cont_T;

/* Block signals for system '<S24>/Hold1' */
typedef struct {
  boolean_T Out;                       /* '<S24>/Hold1' */
} B_Hold1_CYS_110WP_3_Control_T;

/* Block states (auto storage) for system '<S24>/Hold1' */
typedef struct {
  boolean_T Flag_First;                /* '<S24>/Hold1' */
} DW_Hold1_CYS_110WP_3_Control_T;

/* Block signals for system '<S57>/Hold' */
typedef struct {
  real32_T Out;                        /* '<S57>/Hold' */
} B_Hold_CYS_110WP_3_Control_a_T;

/* Block states (auto storage) for system '<S57>/Hold' */
typedef struct {
  real32_T Nc_First_Hold;              /* '<S57>/Hold' */
  boolean_T Flag_First;                /* '<S57>/Hold' */
} DW_Hold_CYS_110WP_3_Control_f_T;

/* Block signals for system '<S57>/M_Rate_Limiter' */
typedef struct {
  real32_T S_Dem_SpeedLoad_Limiter;    /* '<S57>/M_Rate_Limiter' */
} B_M_Rate_Limiter_CYS_110WP_3__T;

/* Block states (auto storage) for system '<S57>/M_Rate_Limiter' */
typedef struct {
  boolean_T Start_A;                   /* '<S57>/M_Rate_Limiter' */
  boolean_T Start_B;                   /* '<S57>/M_Rate_Limiter' */
  boolean_T Start_C;                   /* '<S57>/M_Rate_Limiter' */
  boolean_T Start_D;                   /* '<S57>/M_Rate_Limiter' */
} DW_M_Rate_Limiter_CYS_110WP_3_T;

/* Block signals for system '<S95>/Hold_500ms' */
typedef struct {
  boolean_T Out;                       /* '<S95>/Hold_500ms' */
} B_Hold_500ms_CYS_110WP_3_Cont_T;

/* Block states (auto storage) for system '<S95>/Hold_500ms' */
typedef struct {
  uint32_T Cnt;                        /* '<S95>/Hold_500ms' */
  boolean_T Flag_Stay;                 /* '<S95>/Hold_500ms' */
} DW_Hold_500ms_CYS_110WP_3_Con_T;

/* Block signals for system '<S46>/Hold' */
typedef struct {
  uint8_T Out;                         /* '<S46>/Hold' */
} B_Hold_CYS_110WP_3_Control_ac_T;

/* Block states (auto storage) for system '<S46>/Hold' */
typedef struct {
  boolean_T Flag_First;                /* '<S46>/Hold' */
} DW_Hold_CYS_110WP_3_Control_o_T;

/* Block signals for system '<S240>/Timmer_ms_Lock' */
typedef struct {
  boolean_T Out;                       /* '<S240>/Timmer_ms_Lock' */
} B_Timmer_ms_Lock_CYS_110WP_3__T;

/* Block states (auto storage) for system '<S240>/Timmer_ms_Lock' */
typedef struct {
  uint32_T Cnt;                        /* '<S240>/Timmer_ms_Lock' */
  boolean_T Flag_Lock;                 /* '<S240>/Timmer_ms_Lock' */
} DW_Timmer_ms_Lock_CYS_110WP_3_T;

/* Block signals for system '<S5>/Up_Hold' */
typedef struct {
  boolean_T Out;                       /* '<S5>/Up_Hold' */
} B_Up_Hold_CYS_110WP_3_Control_T;

/* Block signals for system '<S6>/Timmer_ms' */
typedef struct {
  boolean_T Out;                       /* '<S6>/Timmer_ms' */
} B_Timmer_ms_CYS_110WP_3_Con_p_T;

/* Block states (auto storage) for system '<S6>/Timmer_ms' */
typedef struct {
  uint32_T Cnt;                        /* '<S6>/Timmer_ms' */
} DW_Timmer_ms_CYS_110WP_3_Co_p_T;

/* Block signals for system '<S6>/Timmer_ms1' */
typedef struct {
  boolean_T Out;                       /* '<S6>/Timmer_ms1' */
} B_Timmer_ms1_CYS_110WP_3_Cont_T;

/* Block states (auto storage) for system '<S6>/Timmer_ms1' */
typedef struct {
  uint32_T Cnt;                        /* '<S6>/Timmer_ms1' */
} DW_Timmer_ms1_CYS_110WP_3_Con_T;

/* Block signals for system '<S8>/Hold' */
typedef struct {
  uint8_T Out;                         /* '<S8>/Hold' */
} B_Hold_CYS_110WP_3_Control_d_T;

/* Block states (auto storage) for system '<S8>/Hold' */
typedef struct {
  uint8_T CNT;                         /* '<S8>/Hold' */
} DW_Hold_CYS_110WP_3_Control_b_T;

extern void CYS_110WP_3_Control_Hold_Init(B_Hold_CYS_110WP_3_Control_T *localB,
  DW_Hold_CYS_110WP_3_Control_T *localDW);
extern void CYS_110WP_3_Control_Hold(B_Hold_CYS_110WP_3_Control_T *localB,
  DW_Hold_CYS_110WP_3_Control_T *localDW);
extern void CYS_110WP_3_Cont_Timmer_ms_Init(B_Timmer_ms_CYS_110WP_3_Contr_T
  *localB, DW_Timmer_ms_CYS_110WP_3_Cont_T *localDW);
extern void CYS_110WP_3_Control_Timmer_ms(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Timmer_ms_CYS_110WP_3_Contr_T *localB, DW_Timmer_ms_CYS_110WP_3_Cont_T
  *localDW);
extern void CYS_110WP_3_Control_Hold1_Init(B_Hold1_CYS_110WP_3_Control_T *localB,
  DW_Hold1_CYS_110WP_3_Control_T *localDW);
extern void CYS_110WP_3_Control_Hold1(B_Hold1_CYS_110WP_3_Control_T *localB,
  DW_Hold1_CYS_110WP_3_Control_T *localDW);
extern void CYS_110WP_3_Control_Hold_c_Init(B_Hold_CYS_110WP_3_Control_a_T
  *localB, DW_Hold_CYS_110WP_3_Control_f_T *localDW);
extern void CYS_110WP_3_Control_Hold_g(real32_T rtu_Nc_First,
  B_Hold_CYS_110WP_3_Control_a_T *localB, DW_Hold_CYS_110WP_3_Control_f_T
  *localDW);
extern void CYS_110WP_3_M_Rate_Limiter_Init(B_M_Rate_Limiter_CYS_110WP_3__T
  *localB, DW_M_Rate_Limiter_CYS_110WP_3_T *localDW);
extern void CYS_110WP_3_Cont_M_Rate_Limiter(real32_T rtu_Nc_Initial, real32_T
  rtu_S_Dem_SpeedLoad, B_M_Rate_Limiter_CYS_110WP_3__T *localB,
  DW_M_Rate_Limiter_CYS_110WP_3_T *localDW);
extern void CYS_110WP_3_Con_Hold_500ms_Init(B_Hold_500ms_CYS_110WP_3_Cont_T
  *localB, DW_Hold_500ms_CYS_110WP_3_Con_T *localDW);
extern void CYS_110WP_3_Control_Hold_500ms(boolean_T rtu_In, real32_T
  rtu_Time_ms, B_Hold_500ms_CYS_110WP_3_Cont_T *localB,
  DW_Hold_500ms_CYS_110WP_3_Con_T *localDW);
extern void CYS_110WP_3_Control_Hold_i_Init(B_Hold_CYS_110WP_3_Control_ac_T
  *localB, DW_Hold_CYS_110WP_3_Control_o_T *localDW);
extern void CYS_110WP_3_Control_Hold_h(B_Hold_CYS_110WP_3_Control_ac_T *localB,
  DW_Hold_CYS_110WP_3_Control_o_T *localDW);
extern void CYS_110WP_3_Timmer_ms_Lock_Init(B_Timmer_ms_Lock_CYS_110WP_3__T
  *localB, DW_Timmer_ms_Lock_CYS_110WP_3_T *localDW);
extern void CYS_110WP_3_Cont_Timmer_ms_Lock(boolean_T rtu_In, real32_T
  rtu_Time_ms, B_Timmer_ms_Lock_CYS_110WP_3__T *localB,
  DW_Timmer_ms_Lock_CYS_110WP_3_T *localDW);
extern void CYS_110WP_3_Contro_Up_Hold_Init(B_Up_Hold_CYS_110WP_3_Control_T
  *localB);
extern void CYS_110WP_3_Control_Up_Hold(boolean_T rtu_In,
  B_Up_Hold_CYS_110WP_3_Control_T *localB);
extern void CYS_110WP_3_Co_Timmer_ms_d_Init(B_Timmer_ms_CYS_110WP_3_Con_p_T
  *localB, DW_Timmer_ms_CYS_110WP_3_Co_p_T *localDW);
extern void CYS_110WP_3_Control_Timmer_ms_g(boolean_T rtu_In, real32_T
  rtu_Time_ms, B_Timmer_ms_CYS_110WP_3_Con_p_T *localB,
  DW_Timmer_ms_CYS_110WP_3_Co_p_T *localDW);
extern void CYS_110WP_3_Con_Timmer_ms1_Init(B_Timmer_ms1_CYS_110WP_3_Cont_T
  *localB, DW_Timmer_ms1_CYS_110WP_3_Con_T *localDW);
extern void CYS_110WP_3_Control_Timmer_ms1(boolean_T rtu_In, real32_T
  rtu_Time_ms, B_Timmer_ms1_CYS_110WP_3_Cont_T *localB,
  DW_Timmer_ms1_CYS_110WP_3_Con_T *localDW);
extern void CYS_110WP_3_Control_Hold_g_Init(B_Hold_CYS_110WP_3_Control_d_T
  *localB, DW_Hold_CYS_110WP_3_Control_b_T *localDW);
extern void CYS_110WP_3_Control_Hold_o(B_Hold_CYS_110WP_3_Control_d_T *localB,
  DW_Hold_CYS_110WP_3_Control_b_T *localDW);

#endif                                 /* RTW_HEADER_EngineControl_Timmer_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
