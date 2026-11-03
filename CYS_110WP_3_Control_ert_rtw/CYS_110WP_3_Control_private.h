/*
 * File: CYS_110WP_3_Control_private.h
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

#ifndef RTW_HEADER_CYS_110WP_3_Control_private_h_
#define RTW_HEADER_CYS_110WP_3_Control_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#ifndef PORTABLE_WORDSIZES
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif
#endif                                 /* PORTABLE_WORDSIZES */

extern real_T rt_powd_snf(real_T u0, real_T u1);
void LookUpEven_U16_real32_T(uint16_T *pY, const uint16_T *pYData, real32_T u,
  real32_T valueLo, uint32_T iHi, real32_T uSpacing);
void LookUpEven_real32_T_real32_T(real32_T *pY, const real32_T *pYData, real32_T
  u, real32_T valueLo, uint32_T iHi, real32_T uSpacing);
extern real32_T look1_iflf_binlcapw(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T maxIndex);
extern void CYS__SwitchCaseActionSubsystem5(uint16_T rtu_In1, uint8_T rtu_In1_k,
  uint8_T rtu_In1_g, uint16_T rtu_In1_f, uint16_T rtu_In1_d, uint16_T rtu_In1_o,
  uint16_T rtu_In1_b, uint16_T rtu_In1_h, uint8_T rtu_In1_e, uint8_T rtu_In1_p,
  uint8_T rtu_In1_bp, uint16_T *rty_Out1, uint16_T *rty_Out1_k, uint16_T
  *rty_Out1_g, uint16_T *rty_Out1_f, uint16_T *rty_Out1_d, uint16_T *rty_Out1_o,
  uint8_T *rty_Out2, uint8_T *rty_Out2_h, uint8_T *rty_Out2_e, uint8_T
  *rty_Out2_p, uint8_T *rty_Out2_b);
extern void CYS_110WP_3_Control_Range_Init(B_Range_CYS_110WP_3_Control_T *localB);
extern void CYS_110WP_3_Control_Range(real32_T rtu_In, real32_T rtu_Max,
  real32_T rtu_Min, B_Range_CYS_110WP_3_Control_T *localB);

#endif                                 /* RTW_HEADER_CYS_110WP_3_Control_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
