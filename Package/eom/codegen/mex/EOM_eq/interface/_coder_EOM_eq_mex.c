/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_EOM_eq_mex.c
 *
 * Code generation for function '_coder_EOM_eq_mex'
 *
 */

/* Include files */
#include "_coder_EOM_eq_mex.h"
#include "EOM_eq_data.h"
#include "EOM_eq_initialize.h"
#include "EOM_eq_terminate.h"
#include "_coder_EOM_eq_api.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void EOM_eq_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                        const mxArray *prhs[1])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        6, "EOM_eq");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 6,
                        "EOM_eq");
  }
  /* Call the function. */
  EOM_eq_api(prhs[0], &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&EOM_eq_atexit);
  /* Module initialization. */
  EOM_eq_initialize();
  /* Dispatch the entry-point. */
  EOM_eq_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  EOM_eq_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, (const char_T *)"GBK", true);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_EOM_eq_mex.c) */
