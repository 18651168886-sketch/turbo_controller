/*
 * File: EngineControl_Out.h
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

#ifndef RTW_HEADER_EngineControl_Out_h_
#define RTW_HEADER_EngineControl_Out_h_
#include "rtwtypes.h"

typedef struct {
  uint16_T EValve_Cycle;
  uint16_T EValve_Open;
  uint16_T Eblast_Cycle;
  uint16_T Eblast_Open;
  uint16_T Motor_Cycle;
  uint16_T Motor_Open;
  uint8_T EValve_Enable;
  uint8_T Eblast_Enable;
  uint8_T Motor_Enable;
  uint8_T SWO_Firework;
  uint8_T SWO_BleedAir;
  uint8_T EngineState;
  uint8_T Flag_ECUReset_Clear;
  uint8_T Flag_ECUReset_Save;
  uint8_T Flag_Reset_Enable;
  real32_T Accelerator;
  real32_T Nc_dem;
  real32_T Nc;
} EngineControl_Out;

#endif                                 /* RTW_HEADER_EngineControl_Out_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
