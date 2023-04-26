/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_rjtipF_mex.c
 *
 * Code generation for function '_coder_rjtipF_mex'
 *
 */

/* Include files */
#include "_coder_rjtipF_mex.h"
#include "_coder_rjtipF_api.h"
#include "rjtipF_data.h"
#include "rjtipF_initialize.h"
#include "rjtipF_terminate.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&rjtipF_atexit);
  /* Module initialization. */
  rjtipF_initialize();
  /* Dispatch the entry-point. */
  rjtipF_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  rjtipF_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, (const char_T *)"GBK", true);
  return emlrtRootTLSGlobal;
}

void rjtipF_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                        const mxArray *prhs[5])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4,
                        6, "rjtipF");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 6,
                        "rjtipF");
  }
  /* Call the function. */
  rjtipF_api(prhs, &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

/* End of code generation (_coder_rjtipF_mex.c) */
