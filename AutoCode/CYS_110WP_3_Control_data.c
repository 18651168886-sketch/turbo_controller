/*
 * File: CYS_110WP_3_Control_data.c
 *
 * Code generated for Simulink model 'CYS_110WP_3_Control'.
 *
 * Model version                  : 1.390
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Sep 08 10:16:01 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CYS_110WP_3_Control.h"
#include "CYS_110WP_3_Control_private.h"

/* Block parameters (auto storage) */
P_CYS_110WP_3_Control_T CYS_110WP_3_Control_P = {
  3360.0F,                             /* Variable: PF_ACCFULLRANGE
                                        * Referenced by:
                                        *   '<S16>/PG_CtrlMode_Start1'
                                        *   '<S18>/PG_CtrlMode_Start1'
                                        */

  /*  Variable: PF_Gear_Info
   * Referenced by: '<S162>/档位信息数组'
   */
  { 40000.0F, 45000.0F, 50000.0F, 55000.0F, 57000.0F, 59000.0F, 60000.0F,
    61000.0F, 61000.0F, 61000.0F, 61000.0F, 61000.0F }
};

/* Constant parameters (auto storage) */
const ConstP_CYS_110WP_3_Control_T CYS_110WP_3_Control_ConstP = {
  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S121>/Constant2'
   */
  { 1700.0F, 2500.0F },

  /* Computed Parameter: Constant4_Value_c
   * Referenced by: '<S121>/Constant4'
   */
  { 1900.0F, 2700.0F },

  /* Computed Parameter: Constant6_Value_k
   * Referenced by: '<S121>/Constant6'
   */
  { 1500.0F, 2300.0F },

  /* Computed Parameter: Constant8_Value
   * Referenced by: '<S121>/Constant8'
   */
  { 8800.0F, 7000.0F },

  /* Pooled Parameter (Expression: [1600 1900])
   * Referenced by:
   *   '<S31>/Constant'
   *   '<S121>/Constant'
   */
  { 1600.0F, 1900.0F },

  /* Computed Parameter: Constant2_Value_e
   * Referenced by: '<S31>/Constant2'
   */
  { 1600.0F, 2500.0F },

  /* Computed Parameter: Constant4_Value_f
   * Referenced by: '<S31>/Constant4'
   */
  { 1700.0F, 2700.0F },

  /* Computed Parameter: Constant6_Value_d
   * Referenced by: '<S31>/Constant6'
   */
  { 1300.0F, 2300.0F },

  /* Pooled Parameter (Expression: [0.00058 0.00008 0.00167 0.00156 0.00215 0.00369 0.00575 0.00684 0.00779 0.008])
   * Referenced by:
   *   '<S56>/Ki Lookup Table'
   *   '<S56>/Ki Lookup Table1'
   */
  { 0.00058F, 8.0E-5F, 0.00167F, 0.00156F, 0.00215F, 0.00369F, 0.00575F,
    0.00684F, 0.00779F, 0.008F },

  /* Pooled Parameter (Expression: [20654 25856 30525 36143 41286 46305 51127 56000 58302 60355])
   * Referenced by:
   *   '<S56>/Ki Lookup Table'
   *   '<S56>/Ki Lookup Table1'
   *   '<S56>/Kp Lookup Table'
   *   '<S56>/Kp Lookup Table1'
   */
  { 20654.0F, 25856.0F, 30525.0F, 36143.0F, 41286.0F, 46305.0F, 51127.0F,
    56000.0F, 58302.0F, 60355.0F },

  /* Pooled Parameter (Expression: [0.0058 0.0006 0.0119 0.0097 0.012 0.0185 0.0287 0.0342 0.039 0.04])
   * Referenced by:
   *   '<S56>/Kp Lookup Table'
   *   '<S56>/Kp Lookup Table1'
   */
  { 0.0058F, 0.0006F, 0.0119F, 0.0097F, 0.012F, 0.0185F, 0.0287F, 0.0342F,
    0.039F, 0.04F },

  /* Pooled Parameter (Expression: [40000 62000])
   * Referenced by:
   *   '<S53>/N1r_idle17'
   *   '<S53>/N1r_idle2'
   *   '<S53>/N1r_idle4'
   */
  { 40000.0F, 62000.0F },

  /* Computed Parameter: N1r_idle1_Value
   * Referenced by: '<S53>/N1r_idle1'
   */
  { 2028.0F, 7342.0F },

  /* Computed Parameter: N1r_idle3_Value
   * Referenced by: '<S53>/N1r_idle3'
   */
  { 1317.0F, 4148.0F },

  /* Computed Parameter: N1r_idle5_Value
   * Referenced by: '<S53>/N1r_idle5'
   */
  { 702.0F, 1929.0F },

  /* Computed Parameter: Constant6_Value_e
   * Referenced by: '<S49>/Constant6'
   */
  { 1800.0F, 2300.0F },

  /* Computed Parameter: KpLookupTable1_tableData
   * Referenced by: '<S134>/Kp Lookup Table1'
   */
  { -500.0F, 20000.0F },

  /* Computed Parameter: KpLookupTable1_bp01Data
   * Referenced by: '<S134>/Kp Lookup Table1'
   */
  { 0.0F, 205.0F },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S183>/Bit2V'
   *   '<S185>/T4_X1_Y1'
   *   '<S187>/Bit2V'
   */
  { 0.0F, 3.3F },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S183>/Bit2V'
   *   '<S185>/T4_X1_Y1'
   *   '<S187>/Bit2V'
   */
  { 0.0F, 4095.0F },

  /* Expression: PF_Sensor_Y_Poil
   * Referenced by: '<S183>/POil_X_Y'
   */
  { 0.0F, 1000.0F },

  /* Expression: PF_Sensor_X_Poil
   * Referenced by: '<S183>/POil_X_Y'
   */
  { 0.5F, 3.0F },

  /* Expression: PF_Sensor_Y2_T4
   * Referenced by: '<S185>/T4_X2_Y2'
   */
  { 0.0F, 5000.0F },

  /* Expression: PF_Sensor_X2_T4
   * Referenced by: '<S185>/T4_X2_Y2'
   */
  { 0.0F, 3.0F },

  /* Expression: PF_Sensor_Y3_T4
   * Referenced by: '<S185>/T4_X3_Y3'
   */
  { 0.0F, 100.0F, 200.0F, 300.0F, 400.0F, 500.0F, 600.0F, 700.0F, 800.0F, 900.0F,
    980.0F },

  /* Expression: PF_Sensor_X3_T4
   * Referenced by: '<S185>/T4_X3_Y3'
   */
  { 0.0F, 504.0F, 999.0F, 1497.0F, 2010.0F, 2529.0F, 3051.0F, 3568.0F, 4076.0F,
    4571.0F, 4959.0F },

  /* Computed Parameter: Constant2_Value_c
   * Referenced by: '<S115>/Constant2'
   */
  { 10U, 8U },

  /* Computed Parameter: Constant4_Value_k
   * Referenced by: '<S115>/Constant4'
   */
  { 10U, 5U },

  /* Pooled Parameter (Expression: [30 50])
   * Referenced by:
   *   '<S24>/Constant'
   *   '<S115>/Constant'
   */
  { 30U, 50U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
