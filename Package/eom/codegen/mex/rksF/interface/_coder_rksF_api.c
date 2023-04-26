/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_rksF_api.c
 *
 * Code generation for function '_coder_rksF_api'
 *
 */

/* Include files */
#include "_coder_rksF_api.h"
#include "rksF_data.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[34];

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in2,
                                   const char_T *identifier))[18];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[18];

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *s,
                                 const char_T *identifier);

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *in1,
                                 const char_T *identifier))[34];

static const mxArray *emlrt_marshallOut(void);

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[34];

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[18];

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[34]
{
  real_T(*y)[34];
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *in2,
                                   const char_T *identifier))[18]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[18];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(in2), &thisId);
  emlrtDestroyArray(&in2);
  return y;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[18]
{
  real_T(*y)[18];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *s,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(s), &thisId);
  emlrtDestroyArray(&s);
  return y;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *in1,
                                 const char_T *identifier))[34]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[34];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(in1), &thisId);
  emlrtDestroyArray(&in1);
  return y;
}

static const mxArray *emlrt_marshallOut(void)
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, NULL);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[34]
{
  static const int32_T dims[2] = {1, 34};
  real_T(*ret)[34];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[34])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[18]
{
  static const int32_T dims = 18;
  real_T(*ret)[18];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[18])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void rksF_api(const mxArray *const prhs[5], const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  mxMalloc(0U);
  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "in1");
  c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "in2");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "s");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "ds");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "t_sym");
  /* Invoke the target function */
  /* Marshall function outputs */
  *plhs = emlrt_marshallOut();
}

/* End of code generation (_coder_rksF_api.c) */
