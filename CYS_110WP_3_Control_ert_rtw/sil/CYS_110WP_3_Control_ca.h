/*
 * File: CYS_110WP_3_Control_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef CYS_110WP_3_CONTROL_CA_H
#define CYS_110WP_3_CONTROL_CA_H

/* preprocessor validation checks */
#include "CYS_110WP_3_Control_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_HWImpl_TestResults CA_CYS_110WP_3_Control_HWRes;
extern CA_PWS_TestResults CA_CYS_110WP_3_Control_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_HWImpl CA_CYS_110WP_3_Control_ExpHW;
extern CA_HWImpl CA_CYS_110WP_3_Control_ActHW;

/* entry point function to run tests */
void CYS_110WP_3_Control_caRunTests(void);

#endif                                 /* CYS_110WP_3_CONTROL_CA_H */
