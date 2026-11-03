/*
 * File: EngineControl_GeneralModule.h
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

#ifndef RTW_HEADER_EngineControl_GeneralModule_h_
#define RTW_HEADER_EngineControl_GeneralModule_h_
#ifndef CYS_110WP_3_Control_COMMON_INCLUDES_
# define CYS_110WP_3_Control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* CYS_110WP_3_Control_COMMON_INCLUDES_ */

#include "CYS_110WP_3_Control_types.h"

/* Block signals for system '<S209>/LogicSelection3' */
typedef struct {
  boolean_T Switch;                    /* '<S228>/Switch' */
} B_LogicSelF_T;

extern void LogicSelF(boolean_T rtu_C, boolean_T rtu_F, boolean_T rtu_T,
                      B_LogicSelF_T *localB);

#endif                                 /* RTW_HEADER_EngineControl_GeneralModule_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
