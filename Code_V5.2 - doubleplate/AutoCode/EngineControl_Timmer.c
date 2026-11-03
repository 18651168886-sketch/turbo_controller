/*
 * File: EngineControl_Timmer.c
 *
 * Code generated for Simulink model 'CYS_110WP_3_Control'.
 *
 * Model version                  : 1.388
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Sep 06 14:59:48 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "EngineControl_Timmer.h"

/* Include model header file for global data */
#include "CYS_110WP_3_Control.h"
#include "CYS_110WP_3_Control_private.h"

/*
 * Initial conditions for atomic system:
 *    '<S111>/Hold'
 *    '<S115>/Hold'
 *    '<S20>/Hold'
 *    '<S24>/Hold'
 */
void CYS_110WP_3_Control_Hold_Init(B_Hold_CYS_110WP_3_Control_T *localB,
  DW_Hold_CYS_110WP_3_Control_T *localDW)
{
  localDW->Flag_First = false;
  localB->Out = false;
}

/*
 * Output and update for atomic system:
 *    '<S111>/Hold'
 *    '<S115>/Hold'
 *    '<S20>/Hold'
 *    '<S24>/Hold'
 */
void CYS_110WP_3_Control_Hold(B_Hold_CYS_110WP_3_Control_T *localB,
  DW_Hold_CYS_110WP_3_Control_T *localDW)
{
  /* Gateway: CLM/Start/HoldFirst/Hold */
  /* During: CLM/Start/HoldFirst/Hold */
  /* Entry Internal: CLM/Start/HoldFirst/Hold */
  /* Transition: '<S116>:1' */
  if (localDW->Flag_First) {
    /* Transition: '<S116>:4' */
    /* Transition: '<S116>:31' */
    localB->Out = false;

    /* Transition: '<S116>:69' */
  } else {
    /* Transition: '<S116>:41' */
    localB->Out = true;
    localDW->Flag_First = true;
  }

  /* Transition: '<S116>:72' */
}

/*
 * Initial conditions for atomic system:
 *    '<S115>/Timmer_ms'
 *    '<S24>/Timmer_ms'
 */
void CYS_110WP_3_Cont_Timmer_ms_Init(B_Timmer_ms_CYS_110WP_3_Contr_T *localB,
  DW_Timmer_ms_CYS_110WP_3_Cont_T *localDW)
{
  localDW->Cnt = 0U;
  localB->Out = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S115>/Timmer_ms'
 *    '<S24>/Timmer_ms'
 */
void CYS_110WP_3_Control_Timmer_ms(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Timmer_ms_CYS_110WP_3_Contr_T *localB, DW_Timmer_ms_CYS_110WP_3_Cont_T
  *localDW)
{
  /* Gateway: CLM/Start/Subsystem/Timmer_ms */
  /* During: CLM/Start/Subsystem/Timmer_ms */
  /* Entry Internal: CLM/Start/Subsystem/Timmer_ms */
  /* Transition: '<S125>:1' */
  if (rtu_In) {
    /* Transition: '<S125>:4' */
    if (localDW->Cnt >= 100000U) {
      /* Transition: '<S125>:6' */
      /* Transition: '<S125>:13' */
      localDW->Cnt = 100000U;

      /* Transition: '<S125>:16' */
    } else {
      /* Transition: '<S125>:11' */
      localDW->Cnt++;
    }

    /* Transition: '<S125>:31' */
    if (localDW->Cnt > (uint32_T)(rtu_Time_ms / 20.0F)) {
      /* Transition: '<S125>:34' */
      /* Transition: '<S125>:38' */
      localB->Out = 1U;

      /* Transition: '<S125>:39' */
    } else {
      /* Transition: '<S125>:40' */
      localB->Out = 0U;
    }

    /* Transition: '<S125>:56' */
    /* Transition: '<S125>:69' */
  } else {
    /* Transition: '<S125>:41' */
    localDW->Cnt = 0U;
    localB->Out = 0U;
  }

  /* Transition: '<S125>:72' */
}

/* Initial conditions for atomic system: '<S24>/Hold1' */
void CYS_110WP_3_Control_Hold1_Init(B_Hold1_CYS_110WP_3_Control_T *localB,
  DW_Hold1_CYS_110WP_3_Control_T *localDW)
{
  localDW->Flag_First = false;
  localB->Out = false;
}

/* Output and update for atomic system: '<S24>/Hold1' */
void CYS_110WP_3_Control_Hold1(B_Hold1_CYS_110WP_3_Control_T *localB,
  DW_Hold1_CYS_110WP_3_Control_T *localDW)
{
  /* Gateway: CLM/AirStart/Subsystem/Hold1 */
  /* During: CLM/AirStart/Subsystem/Hold1 */
  /* Entry Internal: CLM/AirStart/Subsystem/Hold1 */
  /* Transition: '<S29>:1' */
  if (localDW->Flag_First) {
    /* Transition: '<S29>:4' */
    /* Transition: '<S29>:31' */
    localB->Out = false;

    /* Transition: '<S29>:69' */
  } else {
    /* Transition: '<S29>:41' */
    localB->Out = true;
    localDW->Flag_First = true;
  }

  /* Transition: '<S29>:72' */
}

/* Initial conditions for atomic system: '<S57>/Hold' */
void CYS_110WP_3_Control_Hold_i_Init(B_Hold_CYS_110WP_3_Control_a_T *localB,
  DW_Hold_CYS_110WP_3_Control_m_T *localDW)
{
  localDW->Flag_First = false;
  localDW->Nc_First_Hold = 0.0F;
  localB->Out = 0.0F;
}

/* Output and update for atomic system: '<S57>/Hold' */
void CYS_110WP_3_Control_Hold_k(real32_T rtu_Nc_First,
  B_Hold_CYS_110WP_3_Control_a_T *localB, DW_Hold_CYS_110WP_3_Control_m_T
  *localDW)
{
  /* Gateway: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/Hold */
  /* During: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/Hold */
  /* Entry Internal: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/Hold */
  /* Transition: '<S58>:1' */
  if (localDW->Flag_First) {
    /* Transition: '<S58>:4' */
    /* Transition: '<S58>:31' */
    localB->Out = localDW->Nc_First_Hold;

    /* Transition: '<S58>:69' */
  } else {
    /* Transition: '<S58>:41' */
    localB->Out = rtu_Nc_First;
    localDW->Nc_First_Hold = rtu_Nc_First;
    localDW->Flag_First = true;
  }

  /* Transition: '<S58>:72' */
}

/* Initial conditions for atomic system: '<S57>/M_Rate_Limiter' */
void CYS_110WP_3_M_Rate_Limiter_Init(B_M_Rate_Limiter_CYS_110WP_3__T *localB,
  DW_M_Rate_Limiter_CYS_110WP_3_T *localDW)
{
  localDW->Start_A = true;
  localDW->Start_B = false;
  localDW->Start_C = false;
  localDW->Start_D = false;
  localB->S_Dem_SpeedLoad_Limiter = 0.0F;
}

/* Output and update for atomic system: '<S57>/M_Rate_Limiter' */
void CYS_110WP_3_Cont_M_Rate_Limiter(real32_T rtu_Nc_Initial, real32_T
  rtu_S_Dem_SpeedLoad, B_M_Rate_Limiter_CYS_110WP_3__T *localB,
  DW_M_Rate_Limiter_CYS_110WP_3_T *localDW)
{
  /* Gateway: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/M_Rate_Limiter */
  /* During: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/M_Rate_Limiter */
  /* Entry Internal: CLM/ClpControl/Aim__Parameter_Calculate/Aim_AccMaxMin_Cal1/HoldFirst/M_Rate_Limiter */
  /* Transition: '<S60>:1' */
  if (localDW->Start_A) {
    /* Transition: '<S60>:4' */
    if (rtu_S_Dem_SpeedLoad >= rtu_Nc_Initial) {
      /* Transition: '<S60>:87' */
      /* Transition: '<S60>:89' */
      localDW->Start_A = false;
      localB->S_Dem_SpeedLoad_Limiter = rtu_Nc_Initial;
      localDW->Start_B = true;

      /* Transition: '<S60>:90' */
    } else {
      /* Transition: '<S60>:31' */
      localDW->Start_A = false;
      localB->S_Dem_SpeedLoad_Limiter = rtu_Nc_Initial;
      localDW->Start_C = true;
    }

    /* Transition: '<S60>:69' */
  } else {
    /* Transition: '<S60>:41' */
  }

  /* Transition: '<S60>:72' */
  if (localDW->Start_B) {
    /* Transition: '<S60>:93' */
    /* Transition: '<S60>:97' */
    localB->S_Dem_SpeedLoad_Limiter = (real32_T)(localB->S_Dem_SpeedLoad_Limiter
      + 140.0);
    if (localB->S_Dem_SpeedLoad_Limiter >= rtu_S_Dem_SpeedLoad) {
      /* Transition: '<S60>:101' */
      /* Transition: '<S60>:102' */
      localDW->Start_B = false;
      localB->S_Dem_SpeedLoad_Limiter = rtu_S_Dem_SpeedLoad;
      localDW->Start_D = true;

      /* Transition: '<S60>:104' */
    } else {
      /* Transition: '<S60>:105' */
    }

    /* Transition: '<S60>:108' */
  } else {
    /* Transition: '<S60>:107' */
  }

  /* Transition: '<S60>:122' */
  if (localDW->Start_C) {
    /* Transition: '<S60>:114' */
    /* Transition: '<S60>:112' */
    localB->S_Dem_SpeedLoad_Limiter = (real32_T)(localB->S_Dem_SpeedLoad_Limiter
      - 100.0);
    if (localB->S_Dem_SpeedLoad_Limiter <= rtu_S_Dem_SpeedLoad) {
      /* Transition: '<S60>:118' */
      /* Transition: '<S60>:109' */
      localDW->Start_C = false;
      localB->S_Dem_SpeedLoad_Limiter = rtu_S_Dem_SpeedLoad;
      localDW->Start_D = true;

      /* Transition: '<S60>:110' */
    } else {
      /* Transition: '<S60>:117' */
    }

    /* Transition: '<S60>:113' */
  } else {
    /* Transition: '<S60>:124' */
  }

  /* Transition: '<S60>:129' */
  if (localDW->Start_D) {
    /* Transition: '<S60>:125' */
    if (rtu_S_Dem_SpeedLoad >= localB->S_Dem_SpeedLoad_Limiter) {
      /* Transition: '<S60>:131' */
      /* Transition: '<S60>:135' */
      localB->S_Dem_SpeedLoad_Limiter = (real32_T)
        (localB->S_Dem_SpeedLoad_Limiter + 140.0);
      if (localB->S_Dem_SpeedLoad_Limiter >= rtu_S_Dem_SpeedLoad) {
        /* Transition: '<S60>:140' */
        /* Transition: '<S60>:141' */
        localB->S_Dem_SpeedLoad_Limiter = rtu_S_Dem_SpeedLoad;

        /* Transition: '<S60>:142' */
      } else {
        /* Transition: '<S60>:139' */
      }

      /* Transition: '<S60>:152' */
      /* Transition: '<S60>:153' */
    } else {
      /* Transition: '<S60>:130' */
      localB->S_Dem_SpeedLoad_Limiter = (real32_T)
        (localB->S_Dem_SpeedLoad_Limiter - 100.0);
      if (localB->S_Dem_SpeedLoad_Limiter <= rtu_S_Dem_SpeedLoad) {
        /* Transition: '<S60>:148' */
        /* Transition: '<S60>:149' */
        localB->S_Dem_SpeedLoad_Limiter = rtu_S_Dem_SpeedLoad;

        /* Transition: '<S60>:153' */
      } else {
        /* Transition: '<S60>:146' */
      }
    }

    /* Transition: '<S60>:154' */
  } else {
    /* Transition: '<S60>:155' */
  }

  /* Transition: '<S60>:157' */
}

/* Initial conditions for atomic system: '<S95>/Hold_500ms' */
void CYS_110WP_3_Con_Hold_500ms_Init(B_Hold_500ms_CYS_110WP_3_Cont_T *localB,
  DW_Hold_500ms_CYS_110WP_3_Con_T *localDW)
{
  localDW->Cnt = 0U;
  localDW->Flag_Stay = false;
  localB->Out = false;
}

/* Output and update for atomic system: '<S95>/Hold_500ms' */
void CYS_110WP_3_Control_Hold_500ms(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Hold_500ms_CYS_110WP_3_Cont_T *localB, DW_Hold_500ms_CYS_110WP_3_Con_T
  *localDW)
{
  /* Gateway: CLM/Manual/ManualAcc_Min_Control/返強紗受/Hold_500ms */
  /* During: CLM/Manual/ManualAcc_Min_Control/返強紗受/Hold_500ms */
  /* Entry Internal: CLM/Manual/ManualAcc_Min_Control/返強紗受/Hold_500ms */
  /* Transition: '<S97>:1' */
  if (rtu_In || localDW->Flag_Stay) {
    /* Transition: '<S97>:4' */
    if (localDW->Cnt >= 1000U) {
      /* Transition: '<S97>:6' */
      /* Transition: '<S97>:13' */
      localDW->Cnt = 1000U;

      /* Transition: '<S97>:16' */
    } else {
      /* Transition: '<S97>:11' */
      localDW->Cnt++;
    }

    /* Transition: '<S97>:31' */
    if (localDW->Cnt < (uint32_T)(rtu_Time_ms / 20.0F)) {
      /* Transition: '<S97>:34' */
      /* Transition: '<S97>:38' */
      localB->Out = true;
      localDW->Flag_Stay = true;

      /* Transition: '<S97>:39' */
    } else {
      /* Transition: '<S97>:40' */
      localDW->Cnt = 0U;
      localB->Out = false;
      localDW->Flag_Stay = false;
    }

    /* Transition: '<S97>:56' */
    /* Transition: '<S97>:69' */
  } else {
    /* Transition: '<S97>:41' */
    localDW->Cnt = 0U;
    localB->Out = false;
  }

  /* Transition: '<S97>:72' */
}

/* Initial conditions for atomic system: '<S46>/Hold' */
void CYS_110WP_3_Control_Hold_n_Init(B_Hold_CYS_110WP_3_Control_l_T *localB,
  DW_Hold_CYS_110WP_3_Control_h_T *localDW)
{
  localDW->Flag_First = false;
  localB->Out = 0U;
}

/* Output and update for atomic system: '<S46>/Hold' */
void CYS_110WP_3_Control_Hold_h(B_Hold_CYS_110WP_3_Control_l_T *localB,
  DW_Hold_CYS_110WP_3_Control_h_T *localDW)
{
  /* Gateway: CLM/BWStart/Subsystem/Hold */
  /* During: CLM/BWStart/Subsystem/Hold */
  /* Entry Internal: CLM/BWStart/Subsystem/Hold */
  /* Transition: '<S47>:1' */
  if (localDW->Flag_First) {
    /* Transition: '<S47>:4' */
    /* Transition: '<S47>:31' */
    localB->Out = 1U;

    /* Transition: '<S47>:69' */
  } else {
    /* Transition: '<S47>:41' */
    localB->Out = 0U;
    localDW->Flag_First = true;
  }

  /* Transition: '<S47>:72' */
}

/* Initial conditions for atomic system: '<S240>/Timmer_ms_Lock' */
void CYS_110WP_3_Timmer_ms_Lock_Init(B_Timmer_ms_Lock_CYS_110WP_3__T *localB,
  DW_Timmer_ms_Lock_CYS_110WP_3_T *localDW)
{
  localDW->Cnt = 0U;
  localDW->Flag_Lock = false;
  localB->Out = false;
}

/* Output and update for atomic system: '<S240>/Timmer_ms_Lock' */
void CYS_110WP_3_Cont_Timmer_ms_Lock(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Timmer_ms_Lock_CYS_110WP_3__T *localB, DW_Timmer_ms_Lock_CYS_110WP_3_T
  *localDW)
{
  /* Gateway: FPM/Subsystem/Timmer_ms_Lock */
  /* During: FPM/Subsystem/Timmer_ms_Lock */
  /* Entry Internal: FPM/Subsystem/Timmer_ms_Lock */
  /* Transition: '<S253>:1' */
  if (rtu_In || localDW->Flag_Lock) {
    /* Transition: '<S253>:4' */
    if (localDW->Cnt >= 100000U) {
      /* Transition: '<S253>:6' */
      /* Transition: '<S253>:13' */
      localDW->Cnt = 100000U;

      /* Transition: '<S253>:16' */
    } else {
      /* Transition: '<S253>:11' */
      localDW->Cnt++;
    }

    /* Transition: '<S253>:31' */
    if (localDW->Cnt > (uint32_T)(rtu_Time_ms / 20.0F)) {
      /* Transition: '<S253>:34' */
      /* Transition: '<S253>:38' */
      localB->Out = true;
      localDW->Flag_Lock = true;

      /* Transition: '<S253>:39' */
    } else {
      /* Transition: '<S253>:40' */
      localB->Out = false;
    }

    /* Transition: '<S253>:56' */
    /* Transition: '<S253>:69' */
  } else {
    /* Transition: '<S253>:41' */
    localDW->Cnt = 0U;
    localB->Out = false;
  }

  /* Transition: '<S253>:72' */
}

/* Initial conditions for atomic system: '<S5>/Up_Hold' */
void CYS_110WP_3_Contro_Up_Hold_Init(B_Up_Hold_CYS_110WP_3_Control_T *localB)
{
  localB->Out = false;
}

/* Output and update for atomic system: '<S5>/Up_Hold' */
void CYS_110WP_3_Control_Up_Hold(boolean_T rtu_In,
  B_Up_Hold_CYS_110WP_3_Control_T *localB)
{
  /* Gateway: FPM/Up_Hold */
  /* During: FPM/Up_Hold */
  /* Entry Internal: FPM/Up_Hold */
  /* Transition: '<S241>:1' */
  if (rtu_In) {
    /* Transition: '<S241>:4' */
    /* Transition: '<S241>:31' */
    localB->Out = true;

    /* Transition: '<S241>:69' */
  } else {
    /* Transition: '<S241>:41' */
  }

  /* Transition: '<S241>:72' */
}

/* Initial conditions for atomic system: '<S6>/Timmer_ms' */
void CYS_110WP_3_Co_Timmer_ms_b_Init(B_Timmer_ms_CYS_110WP_3_Con_d_T *localB,
  DW_Timmer_ms_CYS_110WP_3_Co_i_T *localDW)
{
  localDW->Cnt = 0U;
  localB->Out = false;
}

/* Output and update for atomic system: '<S6>/Timmer_ms' */
void CYS_110WP_3_Control_Timmer_ms_g(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Timmer_ms_CYS_110WP_3_Con_d_T *localB, DW_Timmer_ms_CYS_110WP_3_Co_i_T
  *localDW)
{
  /* Gateway: MAM/Timmer_ms */
  /* During: MAM/Timmer_ms */
  /* Entry Internal: MAM/Timmer_ms */
  /* Transition: '<S256>:1' */
  if (rtu_In) {
    /* Transition: '<S256>:4' */
    if (localDW->Cnt >= 100000U) {
      /* Transition: '<S256>:6' */
      /* Transition: '<S256>:13' */
      localDW->Cnt = 100000U;

      /* Transition: '<S256>:16' */
    } else {
      /* Transition: '<S256>:11' */
      localDW->Cnt++;
    }

    /* Transition: '<S256>:31' */
    if (localDW->Cnt > (uint32_T)(rtu_Time_ms / 20.0F)) {
      /* Transition: '<S256>:34' */
      /* Transition: '<S256>:38' */
      localB->Out = true;

      /* Transition: '<S256>:39' */
    } else {
      /* Transition: '<S256>:40' */
      localB->Out = false;
    }

    /* Transition: '<S256>:56' */
    /* Transition: '<S256>:69' */
  } else {
    /* Transition: '<S256>:41' */
    localDW->Cnt = 0U;
    localB->Out = false;
  }

  /* Transition: '<S256>:72' */
}

/* Initial conditions for atomic system: '<S6>/Timmer_ms1' */
void CYS_110WP_3_Con_Timmer_ms1_Init(B_Timmer_ms1_CYS_110WP_3_Cont_T *localB,
  DW_Timmer_ms1_CYS_110WP_3_Con_T *localDW)
{
  localDW->Cnt = 0U;
  localB->Out = false;
}

/* Output and update for atomic system: '<S6>/Timmer_ms1' */
void CYS_110WP_3_Control_Timmer_ms1(boolean_T rtu_In, real32_T rtu_Time_ms,
  B_Timmer_ms1_CYS_110WP_3_Cont_T *localB, DW_Timmer_ms1_CYS_110WP_3_Con_T
  *localDW)
{
  /* Gateway: MAM/Timmer_ms1 */
  /* During: MAM/Timmer_ms1 */
  /* Entry Internal: MAM/Timmer_ms1 */
  /* Transition: '<S257>:1' */
  if (rtu_In) {
    /* Transition: '<S257>:4' */
    if (localDW->Cnt >= 100000U) {
      /* Transition: '<S257>:6' */
      /* Transition: '<S257>:13' */
      localDW->Cnt = 100000U;

      /* Transition: '<S257>:16' */
    } else {
      /* Transition: '<S257>:11' */
      localDW->Cnt++;
    }

    /* Transition: '<S257>:31' */
    if (localDW->Cnt > (uint32_T)(rtu_Time_ms / 20.0F)) {
      /* Transition: '<S257>:34' */
      /* Transition: '<S257>:38' */
      localB->Out = true;

      /* Transition: '<S257>:39' */
    } else {
      /* Transition: '<S257>:40' */
      localB->Out = false;
    }

    /* Transition: '<S257>:56' */
    /* Transition: '<S257>:69' */
  } else {
    /* Transition: '<S257>:41' */
    localDW->Cnt = 0U;
    localB->Out = false;
  }

  /* Transition: '<S257>:72' */
}

/* Initial conditions for atomic system: '<S8>/Hold' */
void CYS_110WP_3_Contro_Hold_id_Init(B_Hold_CYS_110WP_3_Control_o_T *localB,
  DW_Hold_CYS_110WP_3_Control_e_T *localDW)
{
  localDW->CNT = 0U;
  localB->Out = 0U;
}

/* Output and update for atomic system: '<S8>/Hold' */
void CYS_110WP_3_Control_Hold_o(B_Hold_CYS_110WP_3_Control_o_T *localB,
  DW_Hold_CYS_110WP_3_Control_e_T *localDW)
{
  /* Gateway: SaveData/Hold */
  /* During: SaveData/Hold */
  /* Entry Internal: SaveData/Hold */
  /* Transition: '<S260>:1' */
  if (localDW->CNT >= 255) {
    /* Transition: '<S260>:4' */
    /* Transition: '<S260>:31' */
    localB->Out = 0U;

    /* Transition: '<S260>:69' */
  } else {
    /* Transition: '<S260>:41' */
    localB->Out++;
  }

  /* Transition: '<S260>:72' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
