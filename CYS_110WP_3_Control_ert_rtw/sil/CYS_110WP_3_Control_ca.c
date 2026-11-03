/*
 * File: CYS_110WP_3_Control_ca.c
 *
 * Abstract: Tests assumptions in the generated code.
 */

#include "CYS_110WP_3_Control_ca.h"

CA_HWImpl_TestResults CA_CYS_110WP_3_Control_HWRes;
CA_PWS_TestResults CA_CYS_110WP_3_Control_PWSRes;
const CA_HWImpl CA_CYS_110WP_3_Control_ExpHW = {
  8,                                   /* BitPerChar */
  16,                                  /* BitPerShort */
  32,                                  /* BitPerInt */
  32,                                  /* BitPerLong */
  64,                                  /* BitPerLongLong */
  32,                                  /* BitPerFloat */
  64,                                  /* BitPerDouble */
  32,                                  /* BitPerPointer */
  CA_UNSPECIFIED,                      /* Endianess */
  CA_UNDEFINED,                        /* IntDivRoundTo */
  1,                                   /* ShiftRightIntArith */
  0,                                   /* LongLongMode */
  1,                                   /* PortableWordSizes */
  (char *) "Generic->Unspecified (assume 32-bit Generic)"/* HWDeviceType */
};

CA_HWImpl CA_CYS_110WP_3_Control_ActHW;
void CYS_110WP_3_Control_caRunTests(void)
{
  /* verify hardware implementation */
  caVerifyPortableWordSizes(&CA_CYS_110WP_3_Control_ActHW,
    &CA_CYS_110WP_3_Control_ExpHW, &CA_CYS_110WP_3_Control_PWSRes);
  if (!CA_CYS_110WP_3_Control_ActHW.portableWordSizes) {
    caVerifyHWImpl(&CA_CYS_110WP_3_Control_ActHW, &CA_CYS_110WP_3_Control_ExpHW,
                   &CA_CYS_110WP_3_Control_HWRes);
  }                                    /* if */
}
