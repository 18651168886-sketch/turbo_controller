/*
 * File: EngineControl_GeneralModule.c
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

#include "EngineControl_GeneralModule.h"

/* Include model header file for global data */
#include "CYS_110WP_3_Control.h"
#include "CYS_110WP_3_Control_private.h"

/* Output and update for atomic system: '<S209>/LogicSelection3' */
void LogicSelF(boolean_T rtu_C, boolean_T rtu_F, boolean_T rtu_T, B_LogicSelF_T *
               localB)
{
  /* Switch: '<S228>/Switch' */
  if (rtu_C) {
    localB->Switch = rtu_T;
  } else {
    localB->Switch = rtu_F;
  }

  /* End of Switch: '<S228>/Switch' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
