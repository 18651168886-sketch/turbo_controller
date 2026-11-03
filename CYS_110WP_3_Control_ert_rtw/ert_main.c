/*
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "CYS_110WP_3_Control.h"       /* Model's header file */
#include "rtwtypes.h"
#include "zero_crossing_types.h"

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* '<Root>/Flag_rx_suc' */
  static uint8_T arg_Flag_rx_suc = 0U;

  /* '<Root>/MyUsart2_Rxdata' */
  static uint8_T arg_MyUsart2_Rxdata[50] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U };

  /* '<Root>/Flag_ECUReset' */
  static uint8_T arg_Flag_ECUReset = 0U;

  /* '<Root>/ECUReset_Information' */
  static uint8_T arg_ECUReset_Information[20] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

  /* '<Root>/MySet_Rxdata' */
  static uint8_T arg_MySet_Rxdata[50] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U };

  /* '<Root>/Nc' */
  static real32_T arg_Nc = 0.0F;

  /* '<Root>/T4' */
  static real32_T arg_T4 = 0.0F;

  /* '<Root>/S_Vpower' */
  static real32_T arg_S_Vpower = 0.0F;

  /* '<Root>/Tecu' */
  static real32_T arg_Tecu = 0.0F;

  /* '<Root>/SWI_Firework' */
  static uint8_T arg_SWI_Firework = 0U;

  /* '<Root>/SWI_EValve' */
  static uint8_T arg_SWI_EValve = 0U;

  /* '<Root>/SWI_Eblast' */
  static uint8_T arg_SWI_Eblast = 0U;

  /* '<Root>/SWI_ValveErr' */
  static uint8_T arg_SWI_ValveErr = 0U;

  /* '<Root>/SWI_BleedAir' */
  static uint8_T arg_SWI_BleedAir = 0U;

  /* '<Root>/POil' */
  static real32_T arg_POil = 0.0F;

  /* '<Root>/T0' */
  static real32_T arg_T0 = 0.0F;

  /* '<Root>/Controldata' */
  static EngineControl_Out arg_Controldata;

  /* '<Root>/savedata' */
  static SaveData_Out arg_savedata;

  /* '<Root>/senddata' */
  static SendData_Out arg_senddata;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(CYS_110WP_3_Control_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  ECU_110WP_C_Control_Run(&arg_Flag_rx_suc, arg_MyUsart2_Rxdata,
    &arg_Flag_ECUReset, arg_ECUReset_Information, arg_MySet_Rxdata, arg_Nc,
    arg_T4, arg_S_Vpower, arg_Tecu, arg_SWI_Firework, arg_SWI_EValve,
    arg_SWI_Eblast, arg_SWI_ValveErr, arg_SWI_BleedAir, arg_POil, arg_T0,
    &arg_Controldata, &arg_savedata, &arg_senddata);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  ECU_110WP_C_Control_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.02 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(CYS_110WP_3_Control_M) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
