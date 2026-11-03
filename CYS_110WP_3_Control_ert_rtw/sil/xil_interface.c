/*
 * File: xil_interface.c
 *
 * SIL generated interface for code: "CYS_110WP_3_Control"
 *
 */

#include "xil_interface.h"
#include "CYS_110WP_3_Control.h"

/* Functions with a C call interface */
#ifdef __cplusplus

extern "C" {

#endif

#include "xil_data_stream.h"
#ifdef __cplusplus

}
#endif

/* interface data */
uint8_T arg_Flag_rx_suc;

/* interface data */
uint8_T arg_MyUsart2_Rxdata[50];

/* interface data */
uint8_T arg_Flag_ECUReset;

/* interface data */
uint8_T arg_ECUReset_Information[20];

/* interface data */
uint8_T arg_MySet_Rxdata[50];

/* interface data */
real32_T arg_Nc;

/* interface data */
real32_T arg_T4;

/* interface data */
real32_T arg_S_Vpower;

/* interface data */
real32_T arg_Tecu;

/* interface data */
uint8_T arg_SWI_Firework;

/* interface data */
uint8_T arg_SWI_EValve;

/* interface data */
uint8_T arg_SWI_Eblast;

/* interface data */
uint8_T arg_SWI_ValveErr;

/* interface data */
uint8_T arg_SWI_BleedAir;

/* interface data */
real32_T arg_POil;

/* interface data */
real32_T arg_T0;

/* interface data */
EngineControl_Out arg_Controldata;

/* interface data */
SaveData_Out arg_savedata;

/* interface data */
SendData_Out arg_senddata;
static XILIOData xil_fcnid0_task1_output_u[16];
static XILIOData xil_fcnid0_task1_y[73];
static XILIOData xil_fcnid0_init_y[73];
static XILIOData xil_fcnid0_ws_params[3];

/* In-the-Loop Interface functions - see xil_interface.h */
XIL_INTERFACE_ERROR_CODE xilProcessParams(uint32_T xilFcnId)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetDataTypeInfo(void)
{
  {
    /* send response id code */
    MemUnit_T memUnitData = XIL_RESPONSE_TYPE_SIZE;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* send type id */
    memUnitData = 1;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* PIL_FLOAT_SIZE should only be already defined for MathWorks testing */
#ifndef PIL_FLOAT_SIZE
#define PIL_FLOAT_SIZE                 sizeof(float)
#endif

    /* send size in bytes */
    memUnitData = (MemUnit_T) PIL_FLOAT_SIZE;

#ifndef HOST_WORD_ADDRESSABLE_TESTING

    /* convert MemUnits to bytes */
    memUnitData *= MEM_UNIT_BYTES;

#endif

    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilInitialize(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* initialize output storage owned by In-the-Loop */
  /* Call all Get class methods */
  {
    arg_Controldata.EValve_Cycle = 0;
  }

  {
    arg_Controldata.EValve_Open = 0;
  }

  {
    arg_Controldata.Eblast_Cycle = 0;
  }

  {
    arg_Controldata.Eblast_Open = 0;
  }

  {
    arg_Controldata.Motor_Cycle = 0;
  }

  {
    arg_Controldata.Motor_Open = 0;
  }

  {
    arg_Controldata.EValve_Enable = 0;
  }

  {
    arg_Controldata.Eblast_Enable = 0;
  }

  {
    arg_Controldata.Motor_Enable = 0;
  }

  {
    arg_Controldata.SWO_Firework = 0;
  }

  {
    arg_Controldata.SWO_BleedAir = 0;
  }

  {
    arg_Controldata.EngineState = 0;
  }

  {
    arg_Controldata.Flag_ECUReset_Clear = 0;
  }

  {
    arg_Controldata.Flag_ECUReset_Save = 0;
  }

  {
    arg_Controldata.Flag_Reset_Enable = 0;
  }

  {
    arg_Controldata.Accelerator = 0;
  }

  {
    arg_Controldata.Nc_dem = 0;
  }

  {
    arg_Controldata.Nc = 0;
  }

  {
    arg_savedata.savedata1 = 0;
  }

  {
    arg_savedata.savedata2 = 0;
  }

  {
    arg_savedata.savedata3 = 0;
  }

  {
    arg_savedata.savedata4 = 0;
  }

  {
    arg_savedata.savedata5 = 0;
  }

  {
    arg_savedata.savedata6 = 0;
  }

  {
    arg_savedata.savedata7 = 0;
  }

  {
    arg_savedata.savedata8 = 0;
  }

  {
    arg_savedata.savedata9 = 0;
  }

  {
    arg_savedata.savedata10 = 0;
  }

  {
    arg_savedata.savedata11 = 0;
  }

  {
    arg_savedata.savedata12 = 0;
  }

  {
    arg_savedata.savedata13 = 0;
  }

  {
    arg_savedata.savedata14 = 0;
  }

  {
    arg_savedata.savedata15 = 0;
  }

  {
    arg_savedata.savedata16 = 0;
  }

  {
    arg_savedata.savedata17 = 0;
  }

  {
    arg_savedata.savedata18 = 0;
  }

  {
    arg_savedata.savedata19 = 0;
  }

  {
    arg_savedata.savedata20 = 0;
  }

  {
    arg_savedata.savedata21 = 0;
  }

  {
    arg_savedata.savedata22 = 0;
  }

  {
    arg_savedata.savedata23 = 0;
  }

  {
    arg_savedata.savedata24 = 0;
  }

  {
    arg_savedata.savedata25 = 0;
  }

  {
    arg_senddata.senddata1 = 0;
  }

  {
    arg_senddata.senddata2 = 0;
  }

  {
    arg_senddata.senddata3 = 0;
  }

  {
    arg_senddata.senddata4 = 0;
  }

  {
    arg_senddata.senddata5 = 0;
  }

  {
    arg_senddata.senddata6 = 0;
  }

  {
    arg_senddata.senddata7 = 0;
  }

  {
    arg_senddata.senddata8 = 0;
  }

  {
    arg_senddata.senddata9 = 0;
  }

  {
    arg_senddata.senddata10 = 0;
  }

  {
    arg_senddata.senddata11 = 0;
  }

  {
    arg_senddata.senddata12 = 0;
  }

  {
    arg_senddata.senddata13 = 0;
  }

  {
    arg_senddata.senddata14 = 0;
  }

  {
    arg_senddata.senddata15 = 0;
  }

  {
    arg_senddata.senddata16 = 0;
  }

  {
    arg_senddata.senddata17 = 0;
  }

  {
    arg_senddata.senddata18 = 0;
  }

  {
    arg_senddata.senddata19 = 0;
  }

  {
    arg_senddata.senddata20 = 0;
  }

  {
    arg_senddata.senddata21 = 0;
  }

  {
    arg_senddata.senddata22 = 0;
  }

  {
    arg_senddata.senddata23 = 0;
  }

  {
    arg_senddata.senddata24 = 0;
  }

  {
    arg_senddata.senddata25 = 0;
  }

  {
    arg_senddata.senddata26 = 0;
  }

  {
    arg_senddata.senddata27 = 0;
  }

  {
    arg_senddata.senddata28 = 0;
  }

  {
    arg_senddata.senddata29 = 0;
  }

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    ECU_110WP_C_Control_initialize();
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilSystemInitialize(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    /* No Function to Call */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilSystemReset(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    /* No Function to Call */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilGetHostToTargetData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
  *xilIOData = 0;

  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_PROCESS_PARAMS_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(CYS_110WP_3_Control_P.PF_ACCFULLRANGE);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(CYS_110WP_3_Control_P.PF_Gear_Info[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 12 * sizeof(real32_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_ws_params[tableIdx].memUnitLength = 0;
        xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_ws_params[0];
      break;
    }

   case XIL_OUTPUT_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(arg_Flag_rx_suc);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_MyUsart2_Rxdata[0]);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 50 * sizeof
            (uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_ECUReset_Information[0]);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 20 * sizeof
            (uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_MySet_Rxdata[0]);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 50 * sizeof
            (uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Nc);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_T4);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_S_Vpower);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Tecu);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_SWI_Firework);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_SWI_EValve);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_SWI_Eblast);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_SWI_ValveErr);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_SWI_BleedAir);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_POil);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_T0);
          xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 1 * sizeof
            (real32_T);
          xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *)
            dataAddress;
        }

        xil_fcnid0_task1_output_u[tableIdx].memUnitLength = 0;
        xil_fcnid0_task1_output_u[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_task1_output_u[0];
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  UNUSED_PARAMETER(xilCommandIdx);
  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilOutput(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  switch (xilTID) {
   case 1:
    /* Call all Set class methods */
    ECU_110WP_C_Control_Run(&(arg_Flag_rx_suc), arg_MyUsart2_Rxdata,
      &(arg_Flag_ECUReset), arg_ECUReset_Information, arg_MySet_Rxdata, arg_Nc,
      arg_T4, arg_S_Vpower, arg_Tecu, arg_SWI_Firework, arg_SWI_EValve,
      arg_SWI_Eblast, arg_SWI_ValveErr, arg_SWI_BleedAir, arg_POil, arg_T0,
      &(arg_Controldata), &(arg_savedata), &(arg_senddata));

    /* Call all Get class methods */
    break;

   default:
    return XIL_INTERFACE_UNKNOWN_TID;
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilUpdate(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  /* No Update Function */
  UNUSED_PARAMETER(xilTID);
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetTargetToHostData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  *xilIOData = 0;
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_INITIALIZE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Cycle);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Open);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Cycle);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Open);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Cycle);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Open);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Enable);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Enable);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Enable);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.SWO_Firework);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.SWO_BleedAir);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EngineState);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_ECUReset_Clear);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_ECUReset_Save);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_Reset_Enable);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Accelerator);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Nc_dem);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Nc);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata1);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata2);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata3);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata4);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata5);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata6);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata7);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata8);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata9);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata10);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata11);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata12);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata13);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata14);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata15);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata16);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata17);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata18);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata19);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata20);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata21);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata22);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata23);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata24);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata25);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata1);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata2);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata3);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata4);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata5);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata6);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata7);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata8);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata9);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata10);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata11);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata12);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata13);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata14);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata15);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata16);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata17);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata18);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata19);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata20);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata21);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata22);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata23);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata24);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata25);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata26);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata27);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata28);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata29);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_init_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_init_y[0];
      break;
    }

   case XIL_OUTPUT_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Cycle);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Open);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Cycle);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Open);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Cycle);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Open);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint16_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EValve_Enable);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Eblast_Enable);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Motor_Enable);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.SWO_Firework);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.SWO_BleedAir);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.EngineState);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_ECUReset_Clear);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_ECUReset_Save);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Flag_Reset_Enable);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Accelerator);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Nc_dem);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_Controldata.Nc);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata1);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata2);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata3);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata4);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata5);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata6);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata7);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata8);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata9);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata10);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata11);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata12);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata13);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata14);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata15);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata16);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata17);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata18);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata19);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata20);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata21);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata22);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata23);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata24);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_savedata.savedata25);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata1);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata2);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata3);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata4);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata5);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata6);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata7);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata8);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata9);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata10);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata11);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata12);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata13);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata14);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata15);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata16);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata17);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata18);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata19);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata20);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata21);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata22);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata23);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata24);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata25);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata26);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata27);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata28);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(arg_senddata.senddata29);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(uint8_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_task1_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_task1_y[0];
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  UNUSED_PARAMETER(xilCommandIdx);
  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilTerminate(uint32_T xilFcnId)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  /* No Function to Call */
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilEnable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  UNUSED_PARAMETER(xilTID);

  /* No Enable Function - this function should never be called */
  return XIL_INTERFACE_UNKNOWN_TID;
}

XIL_INTERFACE_ERROR_CODE xilDisable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  UNUSED_PARAMETER(xilTID);

  /* No Disable Function - this function should never be called */
  return XIL_INTERFACE_UNKNOWN_TID;
}
