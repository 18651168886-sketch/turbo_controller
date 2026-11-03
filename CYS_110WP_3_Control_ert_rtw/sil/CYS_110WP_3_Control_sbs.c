/*
 * CYS_110WP_3_Control_sbs.c
 *
 * Automatically generated s-function with I/O interface for:
 * Component: CYS_110WP_3_Control
 * Component Simulink Path: CYS_110WP_3_Control
 * Simulation Mode: SIL
 *
 */

#define S_FUNCTION_NAME                CYS_110WP_3_Control_sbs
#define S_FUNCTION_LEVEL               2
#if !defined(RTW_GENERATED_S_FUNCTION)
#define RTW_GENERATED_S_FUNCTION
#endif

#include <stdio.h>
#include <string.h>
#include "simstruc.h"
#include "simtarget/slMdlrefSimTargetHeaders.h"
#include "fixedpoint.h"
#include "coder/connectivity_core/xilutils/xilutils.h"
#include "coder/connectivity/xilutils_sl/xilutils_sl.h"
#include "rtiostream_utils.h"
#include "coder/connectivity/xilcomms_rtiostream/xilcomms_rtiostream.h"
#include "coder/connectivity/xilservice/host/CInterface.h"
#include "coder/connectivity_core/coderassumptionsapp/host/CInterface.h"

/* Response case labels */
enum ResponseIDs {
  RESPONSE_ERROR = 0,
  RESPONSE_OUTPUT_DATA = 1,
  RESPONSE_PRINTF = 2,
  RESPONSE_FOPEN = 3,
  RESPONSE_FPRINTF = 4,
  RESPONSE_SIGNAL_RAISED = 5
};

typedef struct {
  FILE ** Fd;
  mwSize size;
  int32_T fidOffset;
} targetIOFd_T;

static void callStopHookAndFreeSFcnMemory(SimStruct *S);

/* grow the buffer for target I/O Fd array
 * targetIOFd->Fd is NULL on failure */
static void growTargetIOFd(SimStruct *S, targetIOFd_T * IOFd, mwSize
  requiredSize)
{
  if (IOFd->size < requiredSize) {
    IOFd->Fd = mxRealloc(IOFd->Fd, requiredSize * sizeof(FILE*));
    if (IOFd->Fd == NULL) {
      ssSetErrorStatus( S,"growTargetIOFd: mxRealloc failed.");
    } else {
      mexMakeMemoryPersistent(IOFd->Fd);
      IOFd->size = requiredSize;
    }                                  /* if */
  }                                    /* if */
}

static void closeAndFreeTargetIOFd(SimStruct *S)
{
  int i;
  if (ssGetPWork(S) != NULL) {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
    if (targetIOFdPtr != NULL) {
      if (targetIOFdPtr->Fd != NULL) {
        for (i=0; i<targetIOFdPtr->size; i++) {
          if (targetIOFdPtr->Fd[i] != NULL) {
            fclose(targetIOFdPtr->Fd[i]);
          }                            /* if */
        }                              /* for */

        mxFree(targetIOFdPtr->Fd);
      }                                /* if */

      mxFree(targetIOFdPtr);
    }                                  /* if */

    ssSetPWorkValue(S, 3, NULL);
  }                                    /* if */
}

/* receive one packet of data and dispatch to owning application */
static boolean_T recvData(SimStruct *S, void* pComms)
{
  int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
  void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
  if (pCommErrorOccurred == NULL) {
    ssSetErrorStatus( S,"pCommErrorOccurred is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  if (pXILUtils == NULL) {
    ssSetErrorStatus( S,"pXILUtils is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  *pCommErrorOccurred = (xilCommsRun(pComms, pXILUtils) !=
    XILCOMMS_RTIOSTREAM_SUCCESS);
  return (*pCommErrorOccurred?XILSERVICE_ERROR:XILSERVICE_SUCCESS);
}

/* send data via xil comms */
static boolean_T sendData(SimStruct *S, void* pXILService, XIL_IOBuffer_T
  * IOBuffer, mwSize sendSize)
{
  int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
  if (pCommErrorOccurred == NULL) {
    ssSetErrorStatus( S,"pCommErrorOccurred is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  *pCommErrorOccurred = (xilServiceSend(pXILService, IOBuffer->data, sendSize)
    != XILSERVICE_SUCCESS);
  return (*pCommErrorOccurred?XILSERVICE_ERROR:XILSERVICE_SUCCESS);
}

/* implements command dispatch */
static boolean_T commandDispatch(SimStruct *S, XIL_IOBuffer_T* IOBuffer, mwSize
  dataOutSize)
{
  void * pXILService = (void *) ssGetPWorkValue(S, 8);
  if (pXILService == NULL) {
    ssSetErrorStatus( S,"pXILService is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  /* send the data */
  if (sendData(S, pXILService, IOBuffer, dataOutSize) != XILSERVICE_SUCCESS) {
    return XILSERVICE_ERROR;
  }                                    /* if */

  return XILSERVICE_SUCCESS;
}

/* implements command response */
static boolean_T commandResponse(SimStruct *S, mwSize * dataInSize,
  XILCommandResponseType* commandType)
{
  void * pComms = (void *) ssGetPWorkValue(S, 7);
  void * pXILService = (void *) ssGetPWorkValue(S, 8);
  if (pComms == NULL) {
    ssSetErrorStatus( S,"pComms is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  if (pXILService == NULL) {
    ssSetErrorStatus( S,"pXILService is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  {
    /* receive the response data */
    uint8_T COMMAND_COMPLETE = 0;
    while (!COMMAND_COMPLETE) {
      xilServiceSetIsResponseComplete(pXILService, 0);
      if (recvData(S, pComms) != XILSERVICE_SUCCESS) {
        return XILSERVICE_ERROR;
      }                                /* if */

      COMMAND_COMPLETE = xilServiceGetIsResponseComplete(pXILService);
    }                                  /* while */

    /* determine command response type */
    *commandType = (XILCommandResponseType) COMMAND_COMPLETE;
    *dataInSize = xilServiceGetPayloadSizeForOneStep(pXILService);
    return XILSERVICE_SUCCESS;
  }
}

static void copyIOData(void * const dstPtr, void * const srcPtr, uint8_T **
  const tgtPtrPtr, size_t numElements, size_t cTypeSize)
{
  size_t maxBytesConsumed = numElements * cTypeSize;
  memcpy(dstPtr, srcPtr, maxBytesConsumed);
  (*tgtPtrPtr)+=(maxBytesConsumed/sizeof(**tgtPtrPtr));
}

static void callStopHookAndFreeSFcnMemory(SimStruct *S)
{
  closeAndFreeTargetIOFd(S);

  {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      if (pXILUtils) {
        mxArray *rhs[3];
        const char * simulinkBlockPath = ssGetPath(S);
        rhs[ 0 ] = mxCreateString(
          "@coder.connectivity.SimulinkInterface.getSILPILInterface");
        rhs[ 1 ] = mxCreateDoubleScalar( 2 );
        rhs[ 2 ] = mxCreateString(simulinkBlockPath);
        if (xilUtilsCallMATLAB(pXILUtils, 0, NULL, 3, rhs,
                               "rtw.pil.SILPILInterface.sfunctionPILStopHook")!=
            XIL_UTILS_SUCCESS) {
        }                              /* if */
      }                                /* if */
    }
  }

  if (ssGetPWork(S) != NULL) {
    int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
    int * pIsXILApplicationStarted = (int *) ssGetPWorkValue(S, 5);
    if (pIsXILApplicationStarted != NULL) {
      mxFree(pIsXILApplicationStarted);
      ssSetPWorkValue(S, 5, NULL);
    }                                  /* if */

    if (pCommErrorOccurred != NULL) {
      mxFree(pCommErrorOccurred);
      ssSetPWorkValue(S, 4, NULL);
    }                                  /* if */
  }                                    /* if */

  if (ssGetPWork(S) != NULL) {
    XIL_IOBuffer_T* IOBufferPtr;
    XIL_RtIOStreamData_T * rtIOStreamDataPtr = (XIL_RtIOStreamData_T *)
      ssGetPWorkValue(S, 0);
    SIL_DEBUGGING_DATA_T * silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T *)
      ssGetPWorkValue(S, 2);
    if (rtIOStreamDataPtr != NULL) {
      {
        int errorStatus = rtIOStreamUnloadLib(&rtIOStreamDataPtr->libH);
        if (errorStatus) {
          ssSetErrorStatus( S,"rtIOStreamUnloadLib failed.");
        }                              /* if */
      }

      mxFree(rtIOStreamDataPtr->lib);
      mxDestroyArray(rtIOStreamDataPtr->MATLABObject);
      mxFree(rtIOStreamDataPtr);
      ssSetPWorkValue(S, 0, NULL);
    }                                  /* if */

    if (silDebuggingDataPtr != NULL) {
      mxFree(silDebuggingDataPtr->componentBlockPath);
      mxFree(silDebuggingDataPtr->SILPILInterfaceFcnStr);
      mxFree(silDebuggingDataPtr);
      ssSetPWorkValue(S, 2, NULL);
    }                                  /* if */

    IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      mxFree(IOBufferPtr->data);
      mxFree(IOBufferPtr);
      ssSetPWorkValue(S, 1, NULL);
    }                                  /* if */

    closeAndFreeTargetIOFd(S);
    if (ssGetPWork(S) != NULL) {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      void * pComms = (void *) ssGetPWorkValue(S, 7);
      void * pXILService = (void *) ssGetPWorkValue(S, 8);
      void * pCoderAssumptionsApp = (void *) ssGetPWorkValue(S, 9);
      if (pCoderAssumptionsApp != NULL) {
        coderAssumptionsAppDestroy(pCoderAssumptionsApp);
        ssSetPWorkValue(S, 9, NULL);
      }                                /* if */

      if (pXILUtils != NULL) {
        xilUtilsDestroy(pXILUtils);
      }                                /* if */

      ssSetPWorkValue(S, 6, NULL);
      if (pComms != NULL) {
        xilCommsDestroy(pComms);
      }                                /* if */

      ssSetPWorkValue(S, 7, NULL);
      if (pXILService != NULL) {
        xilServiceDestroy(pXILService);
      }                                /* if */

      ssSetPWorkValue(S, 8, NULL);
    }                                  /* if */
  }                                    /* if */
}

static boolean_T processResponseError(SimStruct * S, uint8_T ** mxMemUnitPtrPtr)
{
  uint8_T errorId = **mxMemUnitPtrPtr;
  (*mxMemUnitPtrPtr)++;
  if (errorId) {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      mxArray * rhs[ 2 ];
      rhs[0] = mxCreateString("PIL:pilverification:PILError");
      rhs[1] = mxCreateDoubleScalar(errorId);
      xilUtilsHandleError(pXILUtils, 2 , rhs );
      return XILSERVICE_ERROR;
    }
  }                                    /* if */

  return XILSERVICE_SUCCESS;
}

static boolean_T processResponsePrintf(SimStruct * S, uint8_T ** mxMemUnitPtrPtr)
{
  const int TARGET_IO_SUCCESS = 0;
  uint8_T PRINTF_ERROR;
  uint16_T PRINTF_SIZE;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &PRINTF_ERROR;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint8_T));
      }
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &PRINTF_SIZE;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint16_T));
      }
    }
  }

  if (PRINTF_ERROR != TARGET_IO_SUCCESS) {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      mxArray * rhs[ 2 ];
      rhs[0] = mxCreateString("PIL:pil:TargetIOError");
      rhs[1] = mxCreateDoubleScalar(PRINTF_ERROR);
      xilUtilsHandleError(pXILUtils, 2 , rhs );
      return XILSERVICE_ERROR;
    }
  } else {
    uint8_T *pPrintBuff;
    pPrintBuff = *mxMemUnitPtrPtr;
    if (pPrintBuff[PRINTF_SIZE-1] == '\0') {
      mexPrintf("%s", pPrintBuff);
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + PRINTF_SIZE;
  return XILSERVICE_SUCCESS;
}

static boolean_T processResponseFopen(SimStruct * S, uint8_T ** mxMemUnitPtrPtr)
{
  uint16_T FOPEN_FID;
  uint16_T FOPEN_NAME_SIZE;
  targetIOFd_T *targetIOFdPtr;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FOPEN_FID;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint16_T));
      }
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FOPEN_NAME_SIZE;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint16_T));
      }
    }
  }

  targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
  if (targetIOFdPtr != NULL) {
    /* check fid increments by 1 */
    if (targetIOFdPtr->fidOffset + 1 == FOPEN_FID) {
      targetIOFdPtr->fidOffset = FOPEN_FID;
      growTargetIOFd(S, targetIOFdPtr, targetIOFdPtr->fidOffset + 1);
      if (targetIOFdPtr->Fd != NULL) {
        uint8_T *pFopenBuff;
        targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = NULL;
        pFopenBuff = (*mxMemUnitPtrPtr);
        if (pFopenBuff[FOPEN_NAME_SIZE-1] == '\0') {
          FILE * tmpFd = NULL;
          tmpFd = fopen((char *) pFopenBuff,"w");
          if (tmpFd != NULL) {
            /* save the file descriptor */
            targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = tmpFd;
          } else {
            {
              void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
              mxArray * rhs[ 2 ];
              rhs[0] = mxCreateString("PIL:pil:TargetIOFopenError");
              rhs[1] = mxCreateString((char *) pFopenBuff);
              xilUtilsHandleError(pXILUtils, 2 , rhs );
              return XILSERVICE_ERROR;
            }
          }                            /* if */
        }                              /* if */
      }                                /* if */
    } else {
      {
        void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
        mxArray * rhs[ 2 ];
        rhs[0] = mxCreateString("PIL:pil:TargetIOFopenFidError");
        rhs[1] = mxCreateDoubleScalar(FOPEN_FID);
        xilUtilsHandleError(pXILUtils, 2 , rhs );
        return XILSERVICE_ERROR;
      }
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + FOPEN_NAME_SIZE;
  return XILSERVICE_SUCCESS;
}

static boolean_T processResponseFprintf(SimStruct * S, uint8_T
  ** mxMemUnitPtrPtr)
{
  const int TARGET_IO_SUCCESS = 0;
  uint8_T FPRINTF_ERROR;
  uint16_T FPRINTF_FID;
  uint16_T FPRINTF_SIZE;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_ERROR;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint8_T));
      }
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_FID;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint16_T));
      }
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_SIZE;

    {
      size_t num_elements = 1;

      {
        copyIOData(simDataMemUnitPtr, *mxMemUnitPtrPtr, &*mxMemUnitPtrPtr,
                   num_elements, sizeof(uint16_T));
      }
    }
  }

  if (FPRINTF_ERROR != TARGET_IO_SUCCESS) {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      mxArray * rhs[ 2 ];
      rhs[0] = mxCreateString("PIL:pil:TargetIOError");
      rhs[1] = mxCreateDoubleScalar(FPRINTF_ERROR);
      xilUtilsHandleError(pXILUtils, 2 , rhs );
      return XILSERVICE_ERROR;
    }
  } else {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
    if (targetIOFdPtr != NULL) {
      if (targetIOFdPtr->size > FPRINTF_FID) {
        if (targetIOFdPtr->Fd[FPRINTF_FID] != NULL) {
          uint8_T *pFprintfBuff;
          pFprintfBuff = (*mxMemUnitPtrPtr);
          if (pFprintfBuff[FPRINTF_SIZE-1] == '\0') {
            fprintf(targetIOFdPtr->Fd[FPRINTF_FID], "%s", pFprintfBuff);
          }                            /* if */
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + FPRINTF_SIZE ;
  return XILSERVICE_SUCCESS;
}

static boolean_T processResponseSignalRaised(SimStruct * S, uint8_T
  ** mxMemUnitPtrPtr)
{
  const char *signalStr[5] = { "SIGFPE", "SIGILL", "SIGABRT", "SIGSEGV",
    "Unknown Signal" };

  uint8_T errorId = **mxMemUnitPtrPtr;
  (*mxMemUnitPtrPtr)++;

  {
    void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
    mxArray * rhs[ 3 ];
    rhs[0] = mxCreateString("Connectivity:target:CaughtTargetSignalWithStderr");
    rhs[1] = mxCreateString(signalStr[errorId]);
    rhs[2] = mxCreateDoubleScalar(ssGetT(S));
    xilUtilsHandleError(pXILUtils, 3 , rhs );
    return XILSERVICE_ERROR;
  }

  return XILSERVICE_SUCCESS;
}

static boolean_T processErrorAndTargetIOResponseCases(SimStruct * S, const int
  responseId, uint8_T ** mxMemUnitPtrPtr)
{
  switch (responseId) {
   case RESPONSE_ERROR:
    {
      return processResponseError(S, mxMemUnitPtrPtr);
    }

   case RESPONSE_PRINTF:
    {
      return processResponsePrintf(S, mxMemUnitPtrPtr);
    }

   case RESPONSE_FOPEN:
    {
      return processResponseFopen(S, mxMemUnitPtrPtr);
    }

   case RESPONSE_FPRINTF:
    {
      return processResponseFprintf(S, mxMemUnitPtrPtr);
    }

   case RESPONSE_SIGNAL_RAISED:
    {
      return processResponseSignalRaised(S, mxMemUnitPtrPtr);
    }

   default:
    {
      {
        void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
        mxArray * rhs[ 2 ];
        rhs[0] = mxCreateString("PIL:pilverification:UnknownResponseId");
        rhs[1] = mxCreateDoubleScalar(responseId);
        xilUtilsHandleError(pXILUtils, 2 , rhs );
        return XILSERVICE_ERROR;
      }
    }
  }                                    /* switch */
}

static size_t getBusElementDimension(SimStruct * S, DTypeId dType, int_T
  offsetIdx)
{
  int_T numDimension = ssGetBusElementNumDimensions(S, dType, offsetIdx);
  const int_T *dims = ssGetBusElementDimensions(S, dType, offsetIdx);
  size_t numElements = 1;
  int j = 0;
  for (j = 0; j< numDimension; j++) {
    numElements *= dims[j];
  }                                    /* for */

  return numElements;
}

/* Process params function shared between mdlStart and mdlProcessParams */
static void processParams(SimStruct * S, boolean_T isMdlStartCall)
{
  if (ssGetPWork(S) != NULL) {
    int * pIsXILApplicationStarted = (int *) ssGetPWorkValue(S, 5);
    if ((pIsXILApplicationStarted!=NULL) && (*pIsXILApplicationStarted==1)) {
      if (!isMdlStartCall) {
        /* update run time params */
        ssUpdateAllTunableParamsAsRunTimeParams(S);
      }                                /* if */

      {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
        if (IOBufferPtr != NULL) {
          void * pXILService = (void *) ssGetPWorkValue(S, 8);
          if (pXILService != NULL) {
            if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 57, 0)!=
                XILSERVICE_SUCCESS) {
              return;
            }                          /* if */

            if (IOBufferPtr->data != NULL) {
              mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

              /* write command id */
              *mxMemUnitPtr = 8;
              mxMemUnitPtr++;

              {
                uint8_T * simDataMemUnitPtr;
                uint32_T commandDataFcnid = 0;
                simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

                {
                  size_t num_elements = 1;

                  {
                    copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                               num_elements, sizeof(uint32_T));
                  }
                }
              }

              {
                uint8_T * simDataMemUnitPtr;
                simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 0)
                  ->data;

                {
                  size_t num_elements = 1;

                  {
                    copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                               num_elements, sizeof(real32_T));
                  }
                }
              }

              {
                uint8_T * simDataMemUnitPtr;
                simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 1)
                  ->data;

                {
                  size_t num_elements = 12;

                  {
                    copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                               num_elements, sizeof(real32_T));
                  }
                }
              }

              /* dispatch command to the target */
              if (commandDispatch(S, IOBufferPtr, 57)!=XILSERVICE_SUCCESS) {
                return;
              }                        /* if */

              {
                XILCommandResponseType commandResponseType =
                  XIL_COMMAND_NOT_COMPLETE;
                while (commandResponseType != XIL_STEP_COMPLETE) {
                  /* receive command from the target */
                  mwSize dataInSize = 0;
                  if (commandResponse(S, &dataInSize, &commandResponseType) !=
                      XILSERVICE_SUCCESS) {
                    return;
                  }                    /* if */

                  if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId = 0;
                    uint8_T * mxMemUnitPtrEnd;
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                      /* read response id */
                      responseId = *mxMemUnitPtr;
                      mxMemUnitPtr++;
                      switch (responseId) {
                       case RESPONSE_ERROR:
                       case RESPONSE_PRINTF:
                       case RESPONSE_FOPEN:
                       case RESPONSE_FPRINTF:
                       case RESPONSE_SIGNAL_RAISED:
                        {
                          if (processErrorAndTargetIOResponseCases(S, responseId,
                               &mxMemUnitPtr)== XILSERVICE_ERROR) {
                            return;
                          }            /* if */
                          break;
                        }

                       default:
                        {
                          {
                            void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                            mxArray * rhs[ 2 ];
                            rhs[0] = mxCreateString(
                              "PIL:pilverification:UnknownResponseId");
                            rhs[1] = mxCreateDoubleScalar(responseId);
                            xilUtilsHandleError(pXILUtils, 2 , rhs );
                            return;
                          }
                          break;
                        }
                      }                /* switch */
                    }                  /* while */
                  }                    /* if */
                }                      /* while */
              }
            }                          /* if */
          }                            /* if */
        }                              /* if */
      }
    }                                  /* if */
  }                                    /* if */
}

/* This function checks the attributes of tunable parameters. */
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{
  {
    /* PF_ACCFULLRANGE */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 0, "PF_ACCFULLRANGE", DYNAMICALLY_TYPED, 2,
      dims, 0);
  }

  {
    /* PF_Gear_Info */
    int_T dims[2];
    dims[0] = 12;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 1, "PF_Gear_Info", DYNAMICALLY_TYPED, 2,
      dims, 0);
  }
}

#endif                                 /* MDL_CHECK_PARAMETERS */

static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSFcnParams(S, 2);            /* Number of expected parameters */
  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif

    if (ssGetErrorStatus(S) != (NULL))
      return;
  } else {
    /* Parameter mismatch will be reported by Simulink */
    return;
  }

  ssSetNumContStates(S, 0);
  ssSetNumDiscStates(S, 0);

  /* no support for SimState */
  ssSetSimStateCompliance(S, DISALLOW_SIM_STATE);

  /* Allow signal dimensions greater than 2 */
  ssAllowSignalsWithMoreThan2D(S);

  /* Allow fixed-point data types with 33 or more bits */
  ssFxpSetU32BitRegionCompliant(S,1);

  {
    mxArray * lhs[1];
    mxArray * error = NULL;
    char * installVersion;
    error = mexCallMATLABWithTrap(1, lhs, 0, NULL, "rtw.pil.getPILVersion");
    if (error != NULL) {
      mxDestroyArray(error);
      ssSetErrorStatus( S,
                       "Failed to determine the installed In-the-Loop version for comparison against the In-the-Loop s-function version (release 6.9 (R2015b)_12). To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory).");
      return;
    }                                  /* if */

    if (mxIsEmpty(lhs[0])) {
      ssSetErrorStatus( S,"rtw.pil.getPILVersion returned empty!");
      return;
    }                                  /* if */

    installVersion = mxArrayToString(lhs[0]);
    mxDestroyArray(lhs[0]);
    if (installVersion == NULL) {
      ssSetErrorStatus( S,"Failed to determine installed In-the-Loop version.");
      return;
    }                                  /* if */

    if (strcmp(installVersion, "6.9 (R2015b)_12") != 0) {
      ssSetErrorStatus( S,
                       "The In-the-Loop s-function is incompatible with the installed In-the-Loop version (see ver('ecoder')); it was generated for release 6.9 (R2015b)_12. To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory)");
      return;
    }                                  /* if */

    mxFree(installVersion);
  }

  ssSetRTWGeneratedSFcn(S, 4);
  if (!ssSetNumInputPorts(S, 16))
    return;

  /* Input Port 0 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 0, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 0, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 0, &di);
  }

  ssSetInputPortDimensionsMode(S, 0, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 0, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 0, 0.02);
  ssSetInputPortOffsetTime(S, 0, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 0, FRAME_NO);

  /* Input Port 1 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 1, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 1, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 50 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 50;
    ssSetInputPortDimensionInfo(S, 1, &di);
  }

  ssSetInputPortDimensionsMode(S, 1, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 1, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 1, 0.02);
  ssSetInputPortOffsetTime(S, 1, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 1, FRAME_NO);

  /* Input Port 2 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 2, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 2, 0);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 2, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 2, &di);
  }

  ssSetInputPortDimensionsMode(S, 2, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 2, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 2, 0.02);
  ssSetInputPortOffsetTime(S, 2, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 2, FRAME_NO);

  /* Input Port 3 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 3, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 3, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 20 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 20;
    ssSetInputPortDimensionInfo(S, 3, &di);
  }

  ssSetInputPortDimensionsMode(S, 3, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 3, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 3, 0.02);
  ssSetInputPortOffsetTime(S, 3, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 3, FRAME_NO);

  /* Input Port 4 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 4, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 4, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 50 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 50;
    ssSetInputPortDimensionInfo(S, 4, &di);
  }

  ssSetInputPortDimensionsMode(S, 4, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 4, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 4, 0.02);
  ssSetInputPortOffsetTime(S, 4, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 4, FRAME_NO);

  /* Input Port 5 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 5, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 5, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 5, &di);
  }

  ssSetInputPortDimensionsMode(S, 5, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 5, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 5, 0.02);
  ssSetInputPortOffsetTime(S, 5, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 5, FRAME_NO);

  /* Input Port 6 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 6, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 6, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 6, &di);
  }

  ssSetInputPortDimensionsMode(S, 6, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 6, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 6, 0.02);
  ssSetInputPortOffsetTime(S, 6, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 6, FRAME_NO);

  /* Input Port 7 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 7, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 7, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 7, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 7, &di);
  }

  ssSetInputPortDimensionsMode(S, 7, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 7, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 7, 0.02);
  ssSetInputPortOffsetTime(S, 7, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 7, FRAME_NO);

  /* Input Port 8 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 8, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 8, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 8, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 8, &di);
  }

  ssSetInputPortDimensionsMode(S, 8, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 8, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 8, 0.02);
  ssSetInputPortOffsetTime(S, 8, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 8, FRAME_NO);

  /* Input Port 9 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 9, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 9, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 9, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 9, &di);
  }

  ssSetInputPortDimensionsMode(S, 9, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 9, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 9, 0.02);
  ssSetInputPortOffsetTime(S, 9, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 9, FRAME_NO);

  /* Input Port 10 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 10, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 10, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 10, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 10, &di);
  }

  ssSetInputPortDimensionsMode(S, 10, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 10, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 10, 0.02);
  ssSetInputPortOffsetTime(S, 10, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 10, FRAME_NO);

  /* Input Port 11 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 11, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 11, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 11, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 11, &di);
  }

  ssSetInputPortDimensionsMode(S, 11, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 11, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 11, 0.02);
  ssSetInputPortOffsetTime(S, 11, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 11, FRAME_NO);

  /* Input Port 12 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 12, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 12, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 12, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 12, &di);
  }

  ssSetInputPortDimensionsMode(S, 12, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 12, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 12, 0.02);
  ssSetInputPortOffsetTime(S, 12, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 12, FRAME_NO);

  /* Input Port 13 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 13, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 13, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 3;
    ssSetInputPortDataType(S, 13, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 13, &di);
  }

  ssSetInputPortDimensionsMode(S, 13, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 13, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 13, 0.02);
  ssSetInputPortOffsetTime(S, 13, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 13, FRAME_NO);

  /* Input Port 14 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 14, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 14, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 14, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 14, &di);
  }

  ssSetInputPortDimensionsMode(S, 14, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 14, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 14, 0.02);
  ssSetInputPortOffsetTime(S, 14, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 14, FRAME_NO);

  /* Input Port 15 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 15, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 15, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 15, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 15, &di);
  }

  ssSetInputPortDimensionsMode(S, 15, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 15, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 15, 0.02);
  ssSetInputPortOffsetTime(S, 15, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 15, FRAME_NO);
  if (!ssSetNumOutputPorts(S, 3))
    return;

  /* Output Port 0 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;
    ssRegisterTypeFromNamedObject(S, "EngineControl_Out", &dataTypeId);
    if (dataTypeId == INVALID_DTYPE_ID)
      return;
    ssSetOutputPortDataType(S, 0, dataTypeId);
  }

  ssSetBusOutputAsStruct(S, 0, 1);
  ssSetBusOutputObjectName(S, 0, (void *) "EngineControl_Out");

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 0, &di);
  }

  ssSetOutputPortDimensionsMode(S, 0, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 0, 0.02);
  ssSetOutputPortOffsetTime(S, 0, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 0, FRAME_NO);

  /* Output Port 1 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;
    ssRegisterTypeFromNamedObject(S, "SaveData_Out", &dataTypeId);
    if (dataTypeId == INVALID_DTYPE_ID)
      return;
    ssSetOutputPortDataType(S, 1, dataTypeId);
  }

  ssSetBusOutputAsStruct(S, 1, 1);
  ssSetBusOutputObjectName(S, 1, (void *) "SaveData_Out");

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 1, &di);
  }

  ssSetOutputPortDimensionsMode(S, 1, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 1, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 1, 0.02);
  ssSetOutputPortOffsetTime(S, 1, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 1, FRAME_NO);

  /* Output Port 2 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;
    ssRegisterTypeFromNamedObject(S, "SendData_Out", &dataTypeId);
    if (dataTypeId == INVALID_DTYPE_ID)
      return;
    ssSetOutputPortDataType(S, 2, dataTypeId);
  }

  ssSetBusOutputAsStruct(S, 2, 1);
  ssSetBusOutputObjectName(S, 2, (void *) "SendData_Out");

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 2, &di);
  }

  ssSetOutputPortDimensionsMode(S, 2, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 2, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 2, 0.02);
  ssSetOutputPortOffsetTime(S, 2, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 2, FRAME_NO);

  /* using port based sample times */
  ssSetNumSampleTimes(S, PORT_BASED_SAMPLE_TIMES);

  /* this s-function is sample time dependent: do not allow sub-models containing it to inherit sample times */
  ssSetModelReferenceSampleTimeInheritanceRule(S,
    DISALLOW_SAMPLE_TIME_INHERITANCE);
  ssSetNumPWork(S, 10);
  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumModes(S, 0);
  ssSetNumNonsampledZCs(S, 0);

  {
    uint_T options = 0;

    /* do not allow (including inheritance of) constant block-based sample times*/
    options |= SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME;
    options |= SS_OPTION_SUPPORTS_ALIAS_DATA_TYPES;
    options |= SS_OPTION_CALL_TERMINATE_ON_EXIT;
    ssSetOptions(S, options);
  }

  ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);
}

#define MDL_SET_INPUT_PORT_SAMPLE_TIME                           /* Change to #undef to remove function */
#if defined(MDL_SET_INPUT_PORT_SAMPLE_TIME) && defined(MATLAB_MEX_FILE)

static void mdlSetInputPortSampleTime(SimStruct *S, int_T portIdx, real_T
  sampleTime, real_T offsetTime)
{
  /* sample times are fully specified */
}

#endif                                 /* MDL_SET_INPUT_PORT_SAMPLE_TIME */

#define MDL_SET_OUTPUT_PORT_SAMPLE_TIME                          /* Change to #undef to remove function */
#if defined(MDL_SET_OUTPUT_PORT_SAMPLE_TIME) && defined(MATLAB_MEX_FILE)

static void mdlSetOutputPortSampleTime(SimStruct *S, int_T portIdx, real_T
  sampleTime, real_T offsetTime)
{
  /* sample times are fully specified */
}

#endif                                 /* MDL_SET_OUTPUT_PORT_SAMPLE_TIME */

static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* using port based sample times */
}

#define MDL_START                                                /* Change to #undef to remove function */
#if defined(MDL_START)

static void mdlStart(SimStruct *S)
{
  {
    int retValXILUtils = XIL_UTILS_SUCCESS;
    void* pXILUtils = NULL;
    retValXILUtils = xilSimulinkUtilsCreate(&pXILUtils, S);
    if (retValXILUtils!=XIL_UTILS_SUCCESS) {
      ssSetErrorStatus( S,"Error instantiating XIL Utils!");
      return;
    }                                  /* if */

    ssSetPWorkValue(S, 6, pXILUtils);
  }

  /* no solver check required for singlerate (singletasking) scheduling */
  /* Check current start time is consistent with the generated code */
  if (ssGetTStart(S) != 0.0) {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      mxArray * rhs[ 2 ];
      rhs[0] = mxCreateString("PIL:pil:XILBlockStartTimeError");
      rhs[1] = mxCreateString("0.0");
      xilUtilsHandleError(pXILUtils, 2 , rhs );
      return;
    }
  }                                    /* if */

  {
    mxArray *rhs[4];
    mxArray *lhs[1];
    char * rootLoggingPath;
    const char * simulinkBlockPath = ssGetPath(S);
    rhs[ 0 ] = mxCreateString(
      "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    rhs[ 1 ] = mxCreateDoubleScalar( 2 );
    rhs[ 2 ] = mxCreateString(simulinkBlockPath);
    rhs[3] = mxCreateString(ssGetPath(ssGetRootSS(S)));

    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      if (xilUtilsCallMATLAB(pXILUtils, 1, lhs, 4, rhs,
                             "rtw.pil.SILPILInterface.sfunctionInitializeHook")
          !=XIL_UTILS_SUCCESS) {
        return;
      }                                /* if */
    }

    rootLoggingPath = mxArrayToString(lhs[0]);
    mxDestroyArray(lhs[0]);

    {
      int * pCommErrorOccurred = (int *) mxCalloc(1, sizeof(int));
      if (pCommErrorOccurred == NULL) {
        ssSetErrorStatus( S,
                         "Error in allocating memory for pCommErrorOccurred through mxCalloc.");
        return;
      }                                /* if */

      *pCommErrorOccurred = 0;
      mexMakeMemoryPersistent(pCommErrorOccurred);
      ssSetPWorkValue(S, 4, pCommErrorOccurred);
    }

    mxFree(rootLoggingPath);
  }

  {
    int * pIsXILApplicationStarted = (int *) mxCalloc(1, sizeof(int));
    if (pIsXILApplicationStarted == NULL) {
      ssSetErrorStatus( S,
                       "Error in allocating memory for pIsXILApplicationStarted through mxCalloc.");
      return;
    }                                  /* if */

    *pIsXILApplicationStarted = 0;
    mexMakeMemoryPersistent(pIsXILApplicationStarted);
    ssSetPWorkValue(S, 5, pIsXILApplicationStarted);
  }

  {
    {
      mxArray *rhs[4];
      const char * simulinkBlockPath = ssGetPath(S);
      rhs[ 0 ] = mxCreateString(
        "@coder.connectivity.SimulinkInterface.getSILPILInterface");
      rhs[ 1 ] = mxCreateDoubleScalar( 2 );
      rhs[ 2 ] = mxCreateString(simulinkBlockPath);
      rhs[3] = mxCreateString("uint8");

      {
        void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
        if (xilUtilsCallMATLAB(pXILUtils, 0, 0, 4, rhs,
                               "rtw.pil.SILPILInterface.sfunctionPILStartHook")
            !=XIL_UTILS_SUCCESS) {
          return;
        }                              /* if */
      }
    }

    {                                  /* record that the XIL application has started */
      int * pIsXILApplicationStarted = (int *) ssGetPWorkValue(S, 5);
      *pIsXILApplicationStarted = 1;
      ssSetPWorkValue(S, 5, pIsXILApplicationStarted);
    }
  }

  {
    mxArray *rhs[3];
    mxArray *lhs[5];
    const char * simulinkBlockPath = ssGetPath(S);
    rhs[ 0 ] = mxCreateString(
      "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    rhs[ 1 ] = mxCreateDoubleScalar( 2 );
    rhs[ 2 ] = mxCreateString(simulinkBlockPath);

    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      if (xilUtilsCallMATLAB(pXILUtils, 5, lhs, 3, rhs,
                             "rtw.pil.SILPILInterface.sfunctionGetRtIOStreamInfoHook")
          !=XIL_UTILS_SUCCESS) {
        return;
      }                                /* if */
    }

    {
      XIL_RtIOStreamData_T* rtIOStreamDataPtr = (XIL_RtIOStreamData_T*) mxCalloc
        (1, sizeof(XIL_RtIOStreamData_T));
      if (rtIOStreamDataPtr == NULL) {
        ssSetErrorStatus( S,"Error in allocating memory through mxCalloc.");
        return;
      }                                /* if */

      rtIOStreamDataPtr->lib = mxArrayToString(lhs[0]);
      rtIOStreamDataPtr->MATLABObject = mxDuplicateArray(lhs[1]);
      mexMakeMemoryPersistent(rtIOStreamDataPtr);
      mexMakeMemoryPersistent(rtIOStreamDataPtr->lib);
      mexMakeArrayPersistent(rtIOStreamDataPtr->MATLABObject);
      rtIOStreamDataPtr->streamID = *mxGetPr(lhs[2]);
      rtIOStreamDataPtr->recvTimeout = *mxGetPr(lhs[3]);
      rtIOStreamDataPtr->sendTimeout = *mxGetPr(lhs[4]);
      rtIOStreamDataPtr->isRtIOStreamCCall = 1;
      rtIOStreamDataPtr->ioMxClassID = mxUINT8_CLASS;
      rtIOStreamDataPtr->ioDataSize = sizeof(uint8_T);
      rtIOStreamDataPtr->targetRecvBufferSizeBytes = 50000;
      rtIOStreamDataPtr->targetSendBufferSizeBytes = 50000;

      {
        int errorStatus = rtIOStreamLoadLib(&rtIOStreamDataPtr->libH,
          rtIOStreamDataPtr->lib);
        if (errorStatus) {
          ssSetErrorStatus( S,"rtIOStreamLoadLib failed.");
          return;
        }                              /* if */
      }

      ssSetPWorkValue(S, 0, rtIOStreamDataPtr);
    }

    {
      int i;
      for (i=0; i<5; i++) {
        mxDestroyArray(lhs[i]);
      }                                /* for */
    }
  }

  {
    XIL_IOBuffer_T* IOBufferPtr = (XIL_IOBuffer_T *) mxCalloc(1, sizeof
      (XIL_IOBuffer_T));
    if (IOBufferPtr == NULL) {
      ssSetErrorStatus( S,"Error in allocating memory through mxCalloc.");
      return;
    }                                  /* if */

    mexMakeMemoryPersistent(IOBufferPtr);
    ssSetPWorkValue(S, 1, IOBufferPtr);
  }

  {
    SIL_DEBUGGING_DATA_T* silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T*) mxCalloc
      (1, sizeof(SIL_DEBUGGING_DATA_T));
    const char * simulinkBlockPath = ssGetPath(S);
    if (silDebuggingDataPtr == NULL) {
      ssSetErrorStatus( S,
                       "Error in allocating memory through mxCalloc for SIL_DEBUGGING_DATA_T.");
      return;
    }                                  /* if */

    silDebuggingDataPtr->componentBlockPath = strcpy((char *) mxCalloc(strlen
      (simulinkBlockPath)+1, sizeof(char)), simulinkBlockPath);
    silDebuggingDataPtr->SILPILInterfaceFcnStr = strcpy((char*) mxCalloc(57,
      sizeof(char)), "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    silDebuggingDataPtr->inTheLoopType = 2;
    mexMakeMemoryPersistent(silDebuggingDataPtr);
    mexMakeMemoryPersistent(silDebuggingDataPtr->componentBlockPath);
    mexMakeMemoryPersistent(silDebuggingDataPtr->SILPILInterfaceFcnStr);
    ssSetPWorkValue(S, 2, silDebuggingDataPtr);
  }

  {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) mxCalloc(1, sizeof
      (targetIOFd_T));
    if (targetIOFdPtr == NULL) {
      return;
    }                                  /* if */

    mexMakeMemoryPersistent(targetIOFdPtr);
    targetIOFdPtr->size = 0;
    targetIOFdPtr->Fd = NULL;
    targetIOFdPtr->fidOffset = -1;
    ssSetPWorkValue(S, 3, targetIOFdPtr);
  }

  {
    void* pComms = NULL;
    void* pXILService = NULL;
    void* pMemUnitTransformer = NULL;
    void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
    uint8_T memUnitSizeBytes = 1;
    uint8_T ioDataTypeSizeBytes = sizeof(uint8_T);
    XIL_RtIOStreamData_T * rtIOStreamDataPtr = (XIL_RtIOStreamData_T *)
      ssGetPWorkValue(S, 0);
    SIL_DEBUGGING_DATA_T * silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T *)
      ssGetPWorkValue(S, 2);
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    void * pCoderAssumptionsApp = NULL;
    if (xilCommsCreate(&pComms, rtIOStreamDataPtr, silDebuggingDataPtr,
                       memUnitSizeBytes, pMemUnitTransformer, pXILUtils) !=
        XILCOMMS_RTIOSTREAM_SUCCESS) {
      return;
    }                                  /* if */

    if (xilServiceCreate(&pXILService, pComms, pXILUtils, IOBufferPtr,
                         memUnitSizeBytes, ioDataTypeSizeBytes, 0) !=
        XILSERVICE_SUCCESS) {
      return;
    }                                  /* if */

    {
      mxArray * codeGenComponent = mxCreateString("CYS_110WP_3_Control");
      if (coderAssumptionsAppCreate(&pCoderAssumptionsApp, pXILUtils, 0, 1,
           codeGenComponent, 1) != CODERASSUMPTIONS_SUCCESS) {
        return;
      }                                /* if */
    }

    xilCommsRegisterApplication(pComms, pXILService);
    xilCommsRegisterApplication(pComms, pCoderAssumptionsApp);
    ssSetPWorkValue(S, 8, pXILService);
    ssSetPWorkValue(S, 7, pComms);
    ssSetPWorkValue(S, 9, pCoderAssumptionsApp);
  }

  {
    uint8_T * mxMemUnitPtr;
    mwSize dataInSize = 0;
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      void * pXILService = (void *) ssGetPWorkValue(S, 8);
      if (pXILService != NULL) {
        if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
            XILSERVICE_SUCCESS) {
          return;
        }                              /* if */

        if (IOBufferPtr->data != NULL) {
          mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

          /* write command id */
          *mxMemUnitPtr = 0;
          mxMemUnitPtr++;

          {
            uint8_T * simDataMemUnitPtr;
            uint32_T commandDataFcnid = 0;
            simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

            {
              size_t num_elements = 1;

              {
                copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                           num_elements, sizeof(uint32_T));
              }
            }
          }

          /* dispatch command to the target */
          if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          {
            XILCommandResponseType commandResponseType =
              XIL_COMMAND_NOT_COMPLETE;
            while (commandResponseType != XIL_STEP_COMPLETE) {
              /* receive command from the target */
              mwSize dataInSize = 0;
              if (commandResponse(S, &dataInSize, &commandResponseType) !=
                  XILSERVICE_SUCCESS) {
                return;
              }                        /* if */

              if (dataInSize > 0) {
                size_t dataInMemUnitSize = dataInSize;
                uint8_T responseId = 0;
                uint8_T * mxMemUnitPtrEnd;

#define RESPONSE_TYPE_SIZE             6

                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                  /* read response id */
                  responseId = *mxMemUnitPtr;
                  mxMemUnitPtr++;
                  switch (responseId) {
                   case RESPONSE_ERROR:
                   case RESPONSE_PRINTF:
                   case RESPONSE_FOPEN:
                   case RESPONSE_FPRINTF:
                   case RESPONSE_SIGNAL_RAISED:
                    {
                      if (processErrorAndTargetIOResponseCases(S, responseId,
                           &mxMemUnitPtr)== XILSERVICE_ERROR) {
                        return;
                      }                /* if */
                      break;
                    }

                   case RESPONSE_TYPE_SIZE:
                    {
                      uint8_T typeId = *mxMemUnitPtr;
                      uint8_T typeBytes;
                      mxMemUnitPtr++;
                      typeBytes = *mxMemUnitPtr;
                      mxMemUnitPtr++;
                      switch (typeId) {
                       case SS_SINGLE:
                        {
                          if (typeBytes != 4) {
                            {
                              void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                              mxArray * rhs[ 3 ];
                              rhs[0] = mxCreateString(
                                "PIL:pilverification:SingleUnsupported");
                              rhs[1] = mxCreateDoubleScalar(4);
                              rhs[2] = mxCreateDoubleScalar(typeBytes);
                              xilUtilsHandleError(pXILUtils, 3 , rhs );
                              return;
                            }
                          }            /* if */
                          break;
                        }

                       case SS_DOUBLE:
                        {
                          if (typeBytes != 8) {
                            {
                              void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                              mxArray * rhs[ 3 ];
                              rhs[0] = mxCreateString(
                                "PIL:pilverification:DoubleUnsupported");
                              rhs[1] = mxCreateDoubleScalar(8);
                              rhs[2] = mxCreateDoubleScalar(typeBytes);
                              xilUtilsHandleError(pXILUtils, 3 , rhs );
                              return;
                            }
                          }            /* if */
                          break;
                        }

                       default:
                        {
                          {
                            void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                            mxArray * rhs[ 2 ];
                            rhs[0] = mxCreateString(
                              "PIL:pilverification:UnknownTypeId");
                            rhs[1] = mxCreateDoubleScalar(typeId);
                            xilUtilsHandleError(pXILUtils, 2 , rhs );
                            return;
                          }
                          break;
                        }
                      }                /* switch */
                      break;
                    }

                   default:
                    {
                      {
                        void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                        mxArray * rhs[ 2 ];
                        rhs[0] = mxCreateString(
                          "PIL:pilverification:UnknownResponseId");
                        rhs[1] = mxCreateDoubleScalar(responseId);
                        xilUtilsHandleError(pXILUtils, 2 , rhs );
                        return;
                      }
                      break;
                    }
                  }                    /* switch */
                }                      /* while */
              }                        /* if */
            }                          /* while */
          }
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }

  /* initialize parameters */
  processParams(S, true);

  {
    uint8_T * mxMemUnitPtr;
    mwSize dataInSize = 0;
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      void * pXILService = (void *) ssGetPWorkValue(S, 8);
      if (pXILService != NULL) {
        if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
            XILSERVICE_SUCCESS) {
          return;
        }                              /* if */

        if (IOBufferPtr->data != NULL) {
          mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

          /* write command id */
          *mxMemUnitPtr = 1;
          mxMemUnitPtr++;

          {
            uint8_T * simDataMemUnitPtr;
            uint32_T commandDataFcnid = 0;
            simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

            {
              size_t num_elements = 1;

              {
                copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                           num_elements, sizeof(uint32_T));
              }
            }
          }

          /* dispatch command to the target */
          if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          {
            XILCommandResponseType commandResponseType =
              XIL_COMMAND_NOT_COMPLETE;
            while (commandResponseType != XIL_STEP_COMPLETE) {
              /* receive command from the target */
              mwSize dataInSize = 0;
              if (commandResponse(S, &dataInSize, &commandResponseType) !=
                  XILSERVICE_SUCCESS) {
                return;
              }                        /* if */

              if (dataInSize > 0) {
                size_t dataInMemUnitSize = dataInSize;
                uint8_T responseId = 0;
                uint8_T * mxMemUnitPtrEnd;
                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                  /* read response id */
                  responseId = *mxMemUnitPtr;
                  mxMemUnitPtr++;
                  switch (responseId) {
                   case RESPONSE_ERROR:
                   case RESPONSE_PRINTF:
                   case RESPONSE_FOPEN:
                   case RESPONSE_FPRINTF:
                   case RESPONSE_SIGNAL_RAISED:
                    {
                      if (processErrorAndTargetIOResponseCases(S, responseId,
                           &mxMemUnitPtr)== XILSERVICE_ERROR) {
                        return;
                      }                /* if */
                      break;
                    }

                   case RESPONSE_OUTPUT_DATA:
                    {
                      {
                        uint8_T * simDataMemUnitPtr;
                        uint32_T offsetIdx;
                        for (offsetIdx=0; offsetIdx< 18; offsetIdx++) {
                          slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                          const char * bpath = ssGetPath(S);

                          {
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 0);
                            simDataMemUnitPtr = (uint8_T*) (((char *)
                              simDataMemUnitPtr) +
                              dtaGetDataTypeElementOffset(dta, bpath,
                              ssGetDataTypeId(S, "EngineControl_Out"), offsetIdx));

                            {
                              DTypeId dType = ssGetDataTypeId(S,
                                "EngineControl_Out");
                              size_t num_elements = 1;
                              num_elements = getBusElementDimension(S, dType,
                                offsetIdx);

                              {
                                copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                           &mxMemUnitPtr,num_elements,
                                           ssGetDataTypeSize(S,
                                            ssGetBusElementDataType(S, dType,
                                  offsetIdx)));
                              }
                            }
                          }
                        }              /* for */
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        uint32_T offsetIdx;
                        for (offsetIdx=0; offsetIdx< 25; offsetIdx++) {
                          slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                          const char * bpath = ssGetPath(S);

                          {
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 1);
                            simDataMemUnitPtr = (uint8_T*) (((char *)
                              simDataMemUnitPtr) +
                              dtaGetDataTypeElementOffset(dta, bpath,
                              ssGetDataTypeId(S, "SaveData_Out"), offsetIdx));

                            {
                              DTypeId dType = ssGetDataTypeId(S, "SaveData_Out");
                              size_t num_elements = 1;
                              num_elements = getBusElementDimension(S, dType,
                                offsetIdx);

                              {
                                copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                           &mxMemUnitPtr,num_elements,
                                           ssGetDataTypeSize(S,
                                            ssGetBusElementDataType(S, dType,
                                  offsetIdx)));
                              }
                            }
                          }
                        }              /* for */
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        uint32_T offsetIdx;
                        for (offsetIdx=0; offsetIdx< 29; offsetIdx++) {
                          slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                          const char * bpath = ssGetPath(S);

                          {
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 2);
                            simDataMemUnitPtr = (uint8_T*) (((char *)
                              simDataMemUnitPtr) +
                              dtaGetDataTypeElementOffset(dta, bpath,
                              ssGetDataTypeId(S, "SendData_Out"), offsetIdx));

                            {
                              DTypeId dType = ssGetDataTypeId(S, "SendData_Out");
                              size_t num_elements = 1;
                              num_elements = getBusElementDimension(S, dType,
                                offsetIdx);

                              {
                                copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                           &mxMemUnitPtr,num_elements,
                                           ssGetDataTypeSize(S,
                                            ssGetBusElementDataType(S, dType,
                                  offsetIdx)));
                              }
                            }
                          }
                        }              /* for */
                      }
                      break;
                    }

                   default:
                    {
                      {
                        void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                        mxArray * rhs[ 2 ];
                        rhs[0] = mxCreateString(
                          "PIL:pilverification:UnknownResponseId");
                        rhs[1] = mxCreateDoubleScalar(responseId);
                        xilUtilsHandleError(pXILUtils, 2 , rhs );
                        return;
                      }
                      break;
                    }
                  }                    /* switch */
                }                      /* while */
              }                        /* if */
            }                          /* while */
          }
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }
}

#endif                                 /* MDL_START */

#define MDL_PROCESS_PARAMETERS
#if defined(MDL_PROCESS_PARAMETERS)

static void mdlProcessParameters(SimStruct *S)
{
  processParams(S, false);
}

#endif                                 /* MDL_PROCESS_PARAMETERS */

#define MDL_INITIALIZE_CONDITIONS                                /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    if (ssGetPWork(S) != NULL) {
      int * pIsXILApplicationStarted = (int *) ssGetPWorkValue(S, 5);
      if (!pIsXILApplicationStarted) {
        /* update run time params */
        ssUpdateAllTunableParamsAsRunTimeParams(S);
        mdlStart(S);
      }                                /* if */
    }                                  /* if */
  }                                    /* if */

  if (!ssIsFirstInitCond(S)) {
    ssSetErrorStatus(S,
                     "This In-the-Loop block cannot be called from within a subsystem that can reset its states because the target code does not contain an 'InitializeConditions' function for In-the-Loop to invoke.\n");
    return;
  }
}

#endif                                 /* MDL_INITIALIZE_CONDITIONS */

#define MDL_SET_WORK_WIDTHS                                      /* Change to #undef to remove function */
#if defined(MDL_SET_WORK_WIDTHS)

static void mdlSetWorkWidths(SimStruct *S)
{
  {
    const uint32_T *currChecksumVals;
    ssCallGetDataTypeChecksum(S, "EngineControl_Out", &currChecksumVals);
    if ((currChecksumVals != NULL) && (currChecksumVals[0] != 3025171148U ||
         currChecksumVals[1] != 3071653630U ||
         currChecksumVals[2] != 3716428989U ||
         currChecksumVals[3] != 2504237971U)) {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:DataTypeChecksumError");
      prhs[1] = mxCreateString("EngineControl_Out");
      xilSimulinkUtilsStaticErrorHandle(2, prhs, S);
      return;
    }                                  /* if */
  }

  {
    const uint32_T *currChecksumVals;
    ssCallGetDataTypeChecksum(S, "SaveData_Out", &currChecksumVals);
    if ((currChecksumVals != NULL) && (currChecksumVals[0] != 1094642646U ||
         currChecksumVals[1] != 2825418231U ||
         currChecksumVals[2] != 2289592657U ||
         currChecksumVals[3] != 1889361422U)) {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:DataTypeChecksumError");
      prhs[1] = mxCreateString("SaveData_Out");
      xilSimulinkUtilsStaticErrorHandle(2, prhs, S);
      return;
    }                                  /* if */
  }

  {
    const uint32_T *currChecksumVals;
    ssCallGetDataTypeChecksum(S, "SendData_Out", &currChecksumVals);
    if ((currChecksumVals != NULL) && (currChecksumVals[0] != 3897534106U ||
         currChecksumVals[1] != 3915110340U ||
         currChecksumVals[2] != 1731751325U ||
         currChecksumVals[3] != 3202265679U)) {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:DataTypeChecksumError");
      prhs[1] = mxCreateString("SendData_Out");
      xilSimulinkUtilsStaticErrorHandle(2, prhs, S);
      return;
    }                                  /* if */
  }

  /* Set number of run-time parameters */
  if (!ssSetNumRunTimeParams(S, 2))
    return;

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssRegDlgParamAsRunTimeParam(S, 0, 0, "P0_PF_ACCFULLRANGE", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssRegDlgParamAsRunTimeParam(S, 1, 1, "P1_PF_Gear_Info", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }
}

#endif                                 /* MDL_SET_WORK_WIDTHS */

static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* Singlerate scheduling */
  /* check for sample time hit associated with task 1 */
  if (ssIsSampleHit(S, ssGetInputPortSampleTimeIndex(S, 0), tid)) {
    {
      uint8_T * mxMemUnitPtr;
      mwSize dataInSize = 0;
      XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
      if (IOBufferPtr != NULL) {
        void * pXILService = (void *) ssGetPWorkValue(S, 8);
        if (pXILService != NULL) {
          if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 159, 0)!=
              XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          if (IOBufferPtr->data != NULL) {
            mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

            /* write command id */
            *mxMemUnitPtr = 3;
            mxMemUnitPtr++;

            {
              uint8_T * simDataMemUnitPtr;
              uint32_T commandDataFcnidTID[2] = { 0, 1 };

              simDataMemUnitPtr = (uint8_T *) &commandDataFcnidTID[0];

              {
                size_t num_elements = 2;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 0);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 1);

              {
                size_t num_elements = 50;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 3);

              {
                size_t num_elements = 20;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 4);

              {
                size_t num_elements = 50;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 5);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 6);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 7);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 8);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 9);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 10);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 11);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 12);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 13);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(uint8_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 14);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 15);

              {
                size_t num_elements = 1;

                {
                  copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                             num_elements, sizeof(real32_T));
                }
              }
            }

            /* dispatch command to the target */
            if (commandDispatch(S, IOBufferPtr, 159)!=XILSERVICE_SUCCESS) {
              return;
            }                          /* if */

            {
              XILCommandResponseType commandResponseType =
                XIL_COMMAND_NOT_COMPLETE;
              while (commandResponseType != XIL_STEP_COMPLETE) {
                /* receive command from the target */
                mwSize dataInSize = 0;
                if (commandResponse(S, &dataInSize, &commandResponseType) !=
                    XILSERVICE_SUCCESS) {
                  return;
                }                      /* if */

                if (dataInSize > 0) {
                  size_t dataInMemUnitSize = dataInSize;
                  uint8_T responseId = 0;
                  uint8_T * mxMemUnitPtrEnd;
                  mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                  mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                  while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                    /* read response id */
                    responseId = *mxMemUnitPtr;
                    mxMemUnitPtr++;
                    switch (responseId) {
                     case RESPONSE_ERROR:
                     case RESPONSE_PRINTF:
                     case RESPONSE_FOPEN:
                     case RESPONSE_FPRINTF:
                     case RESPONSE_SIGNAL_RAISED:
                      {
                        if (processErrorAndTargetIOResponseCases(S, responseId,
                             &mxMemUnitPtr)== XILSERVICE_ERROR) {
                          return;
                        }              /* if */
                        break;
                      }

                     case RESPONSE_OUTPUT_DATA:
                      {
                        {
                          uint8_T * simDataMemUnitPtr;
                          uint32_T offsetIdx;
                          for (offsetIdx=0; offsetIdx< 18; offsetIdx++) {
                            slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                            const char * bpath = ssGetPath(S);

                            {
                              simDataMemUnitPtr = ( uint8_T *)
                                ssGetOutputPortSignal(S, 0);
                              simDataMemUnitPtr = (uint8_T*) (((char *)
                                simDataMemUnitPtr) +
                                dtaGetDataTypeElementOffset(dta, bpath,
                                ssGetDataTypeId(S, "EngineControl_Out"),
                                offsetIdx));

                              {
                                DTypeId dType = ssGetDataTypeId(S,
                                  "EngineControl_Out");
                                size_t num_elements = 1;
                                num_elements = getBusElementDimension(S, dType,
                                  offsetIdx);

                                {
                                  copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                             &mxMemUnitPtr,num_elements,
                                             ssGetDataTypeSize(S,
                                              ssGetBusElementDataType(S, dType,
                                    offsetIdx)));
                                }
                              }
                            }
                          }            /* for */
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          uint32_T offsetIdx;
                          for (offsetIdx=0; offsetIdx< 25; offsetIdx++) {
                            slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                            const char * bpath = ssGetPath(S);

                            {
                              simDataMemUnitPtr = ( uint8_T *)
                                ssGetOutputPortSignal(S, 1);
                              simDataMemUnitPtr = (uint8_T*) (((char *)
                                simDataMemUnitPtr) +
                                dtaGetDataTypeElementOffset(dta, bpath,
                                ssGetDataTypeId(S, "SaveData_Out"), offsetIdx));

                              {
                                DTypeId dType = ssGetDataTypeId(S,
                                  "SaveData_Out");
                                size_t num_elements = 1;
                                num_elements = getBusElementDimension(S, dType,
                                  offsetIdx);

                                {
                                  copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                             &mxMemUnitPtr,num_elements,
                                             ssGetDataTypeSize(S,
                                              ssGetBusElementDataType(S, dType,
                                    offsetIdx)));
                                }
                              }
                            }
                          }            /* for */
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          uint32_T offsetIdx;
                          for (offsetIdx=0; offsetIdx< 29; offsetIdx++) {
                            slDataTypeAccess * dta = ssGetDataTypeAccess(S);
                            const char * bpath = ssGetPath(S);

                            {
                              simDataMemUnitPtr = ( uint8_T *)
                                ssGetOutputPortSignal(S, 2);
                              simDataMemUnitPtr = (uint8_T*) (((char *)
                                simDataMemUnitPtr) +
                                dtaGetDataTypeElementOffset(dta, bpath,
                                ssGetDataTypeId(S, "SendData_Out"), offsetIdx));

                              {
                                DTypeId dType = ssGetDataTypeId(S,
                                  "SendData_Out");
                                size_t num_elements = 1;
                                num_elements = getBusElementDimension(S, dType,
                                  offsetIdx);

                                {
                                  copyIOData(simDataMemUnitPtr, mxMemUnitPtr,
                                             &mxMemUnitPtr,num_elements,
                                             ssGetDataTypeSize(S,
                                              ssGetBusElementDataType(S, dType,
                                    offsetIdx)));
                                }
                              }
                            }
                          }            /* for */
                        }
                        break;
                      }

                     default:
                      {
                        {
                          void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                          mxArray * rhs[ 2 ];
                          rhs[0] = mxCreateString(
                            "PIL:pilverification:UnknownResponseId");
                          rhs[1] = mxCreateDoubleScalar(responseId);
                          xilUtilsHandleError(pXILUtils, 2 , rhs );
                          return;
                        }
                        break;
                      }
                    }                  /* switch */
                  }                    /* while */
                }                      /* if */
              }                        /* while */
            }
          }                            /* if */
        }                              /* if */
      }                                /* if */
    }
  }                                    /* if */
}

#define MDL_UPDATE
#if defined(MDL_UPDATE)

static void mdlUpdate(SimStruct *S, int_T tid)
{
}

#endif

static void mdlTerminate(SimStruct *S)
{
  int commErrorOccurred = 0;
  int isXILApplicationStarted = 0;

  {
    if (ssGetPWork(S) != NULL) {
      int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
      int * pIsXILApplicationStarted = (int *) ssGetPWorkValue(S, 5);
      if (pCommErrorOccurred != NULL) {
        commErrorOccurred = *pCommErrorOccurred;
      }                                /* if */

      if (pIsXILApplicationStarted != NULL) {
        isXILApplicationStarted = *pIsXILApplicationStarted;
      }                                /* if */
    }                                  /* if */
  }

  if (isXILApplicationStarted) {
    if (!commErrorOccurred) {
      {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
        if (IOBufferPtr != NULL) {
          void * pXILService = (void *) ssGetPWorkValue(S, 8);
          if (pXILService != NULL) {
            if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
                XILSERVICE_SUCCESS) {
              callStopHookAndFreeSFcnMemory(S);
              return;
            }                          /* if */

            if (IOBufferPtr->data != NULL) {
              mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

              /* write command id */
              *mxMemUnitPtr = 4;
              mxMemUnitPtr++;

              {
                uint8_T * simDataMemUnitPtr;
                uint32_T commandDataFcnid = 0;
                simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

                {
                  size_t num_elements = 1;

                  {
                    copyIOData(mxMemUnitPtr, simDataMemUnitPtr, &mxMemUnitPtr,
                               num_elements, sizeof(uint32_T));
                  }
                }
              }

              /* dispatch command to the target */
              if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
                callStopHookAndFreeSFcnMemory(S);
                return;
              }                        /* if */

              {
                XILCommandResponseType commandResponseType =
                  XIL_COMMAND_NOT_COMPLETE;
                while (commandResponseType != XIL_STEP_COMPLETE) {
                  /* receive command from the target */
                  mwSize dataInSize = 0;
                  if (commandResponse(S, &dataInSize, &commandResponseType) !=
                      XILSERVICE_SUCCESS) {
                    callStopHookAndFreeSFcnMemory(S);
                    return;
                  }                    /* if */

                  if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId = 0;
                    uint8_T * mxMemUnitPtrEnd;
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                      /* read response id */
                      responseId = *mxMemUnitPtr;
                      mxMemUnitPtr++;
                      switch (responseId) {
                       case RESPONSE_ERROR:
                       case RESPONSE_PRINTF:
                       case RESPONSE_FOPEN:
                       case RESPONSE_FPRINTF:
                       case RESPONSE_SIGNAL_RAISED:
                        {
                          if (processErrorAndTargetIOResponseCases(S, responseId,
                               &mxMemUnitPtr)== XILSERVICE_ERROR) {
                            callStopHookAndFreeSFcnMemory(S);
                            return;
                          }            /* if */
                          break;
                        }

                       default:
                        {
                          {
                            void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
                            mxArray * rhs[ 2 ];
                            rhs[0] = mxCreateString(
                              "PIL:pilverification:UnknownResponseId");
                            rhs[1] = mxCreateDoubleScalar(responseId);
                            xilUtilsHandleError(pXILUtils, 2 , rhs );
                            callStopHookAndFreeSFcnMemory(S);
                            return;
                          }
                          break;
                        }
                      }                /* switch */
                    }                  /* while */
                  }                    /* if */
                }                      /* while */
              }
            }                          /* if */
          }                            /* if */
        }                              /* if */
      }

      {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
        if (IOBufferPtr != NULL) {
          void * pXILService = (void *) ssGetPWorkValue(S, 8);
          if (pXILService != NULL) {
            if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 1, 0)!=
                XILSERVICE_SUCCESS) {
              callStopHookAndFreeSFcnMemory(S);
              return;
            }                          /* if */

            if (IOBufferPtr->data != NULL) {
              mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

              /* write command id */
              *mxMemUnitPtr = 10;
              mxMemUnitPtr++;

              /* dispatch command to the target */
              if (commandDispatch(S, IOBufferPtr, 1)!=XILSERVICE_SUCCESS) {
                callStopHookAndFreeSFcnMemory(S);
                return;
              }                        /* if */
            }                          /* if */
          }                            /* if */
        }                              /* if */
      }
    }                                  /* if */

    callStopHookAndFreeSFcnMemory(S);
  }                                    /* if */
}

#define MDL_FINALIZE                                             /* Change to #undef to remove function */
#if defined(MDL_FINALIZE)

static void mdlFinalize(SimStruct *S)
{
  if (ssGetPWork(S) != NULL) {
    int callMdlTerminate = 0;

    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      if (pXILUtils) {
        mxArray *rhs[1];
        mxArray *lhs[1];
        rhs[0] = mxCreateString(ssGetPath(ssGetRootSS(S)));
        if (xilUtilsCallMATLAB(pXILUtils, 1, lhs, 1, rhs,
                               "rtw.pil.SILPILInterface.sfunctionIsFastRestartEnabled")
            !=XIL_UTILS_SUCCESS) {
          callMdlTerminate = 1;
        } else {
          callMdlTerminate = (int) (mxGetLogicals(lhs[0])[0]);
        }                              /* if */

        mxDestroyArray(lhs[0]);
      }                                /* if */
    }

    if (callMdlTerminate) {
      mdlTerminate(S);
    }                                  /* if */
  }                                    /* if */
}

#endif                                 /* MDL_FINALIZE */

#define MDL_ENABLE
#if defined(MDL_ENABLE)

static void mdlEnable(SimStruct *S)
{
  if (ssGetT(S) != ssGetTStart(S)) {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
      mxArray * rhs[ 3 ];
      rhs[0] = mxCreateString("PIL:pil:EnableDisableCallbackError");
      rhs[1] = mxCreateString("enable");
      rhs[2] = mxCreateString("enable");
      xilUtilsHandleError(pXILUtils, 3 , rhs );
      return;
    }
  }                                    /* if */
}

#endif                                 /* MDL_ENABLE */

#define MDL_DISABLE
#if defined(MDL_DISABLE)

static void mdlDisable(SimStruct *S)
{
  {
    void * pXILUtils = (void *) ssGetPWorkValue(S, 6);
    mxArray * rhs[ 3 ];
    rhs[0] = mxCreateString("PIL:pil:EnableDisableCallbackError");
    rhs[1] = mxCreateString("disable");
    rhs[2] = mxCreateString("disable");
    xilUtilsHandleError(pXILUtils, 3 , rhs );
    return;
  }
}

#endif                                 /* MDL_DISABLE */

/* Required S-function trailer */
#ifdef MATLAB_MEX_FILE                 /* Is this file being compiled as a MEX-file? */
#include "simulink.c"                  /* MEX-file interface mechanism */
#include "fixedpoint.c"
#else
#error Assertion failed: file must be compiled as a MEX-file
#endif
