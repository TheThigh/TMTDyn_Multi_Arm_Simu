/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_EOM_eq_api.c
 *
 * Code generation for function '_coder_EOM_eq_api'
 *
 */

/* Include files */
#include "_coder_EOM_eq_api.h"
#include "EOM_eq.h"
#include "EOM_eq_data.h"
#include "EOM_eq_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               b_struct_T *y);

static const mxArray *b_emlrt_marshallOut(const real_T u[4436]);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[34]);

static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp,
                                          const creal_T u[9]);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct_T *y);

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_par_mex,
                             const char_T *identifier, b_struct_T *y);

static const mxArray *emlrt_marshallOut(const b_struct_T *u);

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[4436]);

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[5545]);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[7763]);

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z,
                                   const char_T *identifier))[9];

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[9];

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[34]);

static real_T l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[4436]);

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[5545]);

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[7763]);

static real_T (*p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[9];

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               b_struct_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[3] = {"var", "user_pars", "t_equil_i"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 3,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "var";
  c_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                                    (const char_T *)"var")),
                     &thisId, y->var);
  thisId.fIdentifier = "user_pars";
  d_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b(
                         (emlrtCTX)sp, u, 0, 1, (const char_T *)"user_pars")),
                     &thisId, &y->user_pars);
  thisId.fIdentifier = "t_equil_i";
  y->t_equil_i = e_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 2,
                                     (const char_T *)"t_equil_i")),
      &thisId);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u[4436])
{
  static const int32_T iv[2] = {1109, 4};
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < 4; b_i++) {
    for (c_i = 0; c_i < 1109; c_i++) {
      pData[i + c_i] = u[c_i + 1109 * b_i];
    }
    i += 1109;
  }
  emlrtAssign(&y, m);
  return y;
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[34])
{
  k_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp,
                                          const creal_T u[9])
{
  static const int32_T i = 9;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b((emlrtCTX)sp, m, (void *)&u[0], 8);
  emlrtAssign(&y, m);
  return y;
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[8] = {"exp_case", "n_SRA", "i",    "tip_pos",
                                        "tip_RQ",   "p",     "f_ex", "n_l"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b((emlrtCTX)sp, parentId, u, 8,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "exp_case";
  y->exp_case = e_emlrt_marshallIn(
      sp,
      emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 0,
                                     (const char_T *)"exp_case")),
      &thisId);
  thisId.fIdentifier = "n_SRA";
  y->n_SRA =
      e_emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b(
                             (emlrtCTX)sp, u, 0, 1, (const char_T *)"n_SRA")),
                         &thisId);
  thisId.fIdentifier = "i";
  y->i = e_emlrt_marshallIn(sp,
                            emlrtAlias(emlrtGetFieldR2017b(
                                (emlrtCTX)sp, u, 0, 2, (const char_T *)"i")),
                            &thisId);
  thisId.fIdentifier = "tip_pos";
  f_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 3,
                                                    (const char_T *)"tip_pos")),
                     &thisId, y->tip_pos);
  thisId.fIdentifier = "tip_RQ";
  g_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 4,
                                                    (const char_T *)"tip_RQ")),
                     &thisId, y->tip_RQ);
  thisId.fIdentifier = "p";
  f_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 5,
                                                    (const char_T *)"p")),
                     &thisId, y->p);
  thisId.fIdentifier = "f_ex";
  h_emlrt_marshallIn(sp,
                     emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 6,
                                                    (const char_T *)"f_ex")),
                     &thisId, y->f_ex);
  thisId.fIdentifier = "n_l";
  y->n_l =
      e_emlrt_marshallIn(sp,
                         emlrtAlias(emlrtGetFieldR2017b((emlrtCTX)sp, u, 0, 7,
                                                        (const char_T *)"n_l")),
                         &thisId);
  emlrtDestroyArray(&u);
}

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_par_mex,
                             const char_T *identifier, b_struct_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(b_par_mex), &thisId, y);
  emlrtDestroyArray(&b_par_mex);
}

static const mxArray *emlrt_marshallOut(const b_struct_T *u)
{
  static const int32_T iv[2] = {1, 34};
  static const int32_T iv1[2] = {1109, 5};
  static const int32_T iv2[2] = {1109, 7};
  static const char_T *sv1[8] = {"exp_case", "n_SRA", "i",    "tip_pos",
                                 "tip_RQ",   "p",     "f_ex", "n_l"};
  static const char_T *sv[3] = {"var", "user_pars", "t_equil_i"};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *j_y;
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 3, (const char_T **)&sv[0]));
  b_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (i = 0; i < 34; i++) {
    pData[i] = u->var[i];
  }
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"var", b_y, 0);
  c_y = NULL;
  emlrtAssign(&c_y, emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&sv1[0]));
  d_y = NULL;
  m = emlrtCreateDoubleScalar(u->user_pars.exp_case);
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"exp_case", d_y, 0);
  e_y = NULL;
  m = emlrtCreateDoubleScalar(u->user_pars.n_SRA);
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"n_SRA", e_y, 1);
  f_y = NULL;
  m = emlrtCreateDoubleScalar(u->user_pars.i);
  emlrtAssign(&f_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"i", f_y, 2);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"tip_pos",
                      b_emlrt_marshallOut(u->user_pars.tip_pos), 3);
  g_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv1[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  b_i = 0;
  for (i = 0; i < 5; i++) {
    for (c_i = 0; c_i < 1109; c_i++) {
      pData[b_i + c_i] = u->user_pars.tip_RQ[c_i + 1109 * i];
    }
    b_i += 1109;
  }
  emlrtAssign(&g_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"tip_RQ", g_y, 4);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"p",
                      b_emlrt_marshallOut(u->user_pars.p), 5);
  h_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv2[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  b_i = 0;
  for (i = 0; i < 7; i++) {
    for (c_i = 0; c_i < 1109; c_i++) {
      pData[b_i + c_i] = u->user_pars.f_ex[c_i + 1109 * i];
    }
    b_i += 1109;
  }
  emlrtAssign(&h_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"f_ex", h_y, 6);
  i_y = NULL;
  m = emlrtCreateDoubleScalar(u->user_pars.n_l);
  emlrtAssign(&i_y, m);
  emlrtSetFieldR2017b(c_y, 0, (const char_T *)"n_l", i_y, 7);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"user_pars", c_y, 1);
  j_y = NULL;
  m = emlrtCreateDoubleScalar(u->t_equil_i);
  emlrtAssign(&j_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"t_equil_i", j_y, 2);
  return y;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[4436])
{
  m_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[5545])
{
  n_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[7763])
{
  o_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *z,
                                   const char_T *identifier))[9]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[9];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(sp, emlrtAlias(z), &thisId);
  emlrtDestroyArray(&z);
  return y;
}

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[9]
{
  real_T(*y)[9];
  y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[34])
{
  static const int32_T dims[2] = {1, 34};
  real_T(*r)[34];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[34])emlrtMxGetData(src);
  for (i = 0; i < 34; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static real_T l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
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

static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[4436])
{
  static const int32_T dims[2] = {1109, 4};
  real_T(*r)[4436];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[4436])emlrtMxGetData(src);
  for (i = 0; i < 4436; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[5545])
{
  static const int32_T dims[2] = {1109, 5};
  real_T(*r)[5545];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[5545])emlrtMxGetData(src);
  for (i = 0; i < 5545; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real_T ret[7763])
{
  static const int32_T dims[2] = {1109, 7};
  real_T(*r)[7763];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  r = (real_T(*)[7763])emlrtMxGetData(src);
  for (i = 0; i < 7763; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static real_T (*p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[9]
{
  static const int32_T dims[2] = {1, 9};
  real_T(*ret)[9];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[9])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void EOM_eq_api(const mxArray *prhs, const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  creal_T res[9];
  real_T(*z)[9];
  st.tls = emlrtRootTLSGlobal;
  /* Marshall function inputs */
  z = i_emlrt_marshallIn(&st, emlrtAlias(prhs), "z");
  /* Marshall in global variables */
  MEXGlobalSyncInFunction(&st);
  /* Invoke the target function */
  EOM_eq(&st, *z, res);
  /* Marshall out global variables */
  MEXGlobalSyncOutFunction(true);
  /* Marshall function outputs */
  *plhs = c_emlrt_marshallOut(&st, res);
}

void MEXGlobalSyncInFunction(const emlrtStack *sp)
{
  const mxArray *tmp;
  /* Marshall in global variables */
  tmp = emlrtGetGlobalVariable((const char_T *)"par_mex");
  if (tmp != NULL) {
    emlrt_marshallIn(sp, tmp, "par_mex", &par_mex);
    par_mex_dirty = 0U;
  }
}

void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck)
{
  /* Marshall out global variables */
  if (skipDirtyCheck || (par_mex_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"par_mex",
                           emlrt_marshallOut(&par_mex));
  }
}

void emlrt_synchGlobalsFromML(const emlrtStack *sp)
{
  MEXGlobalSyncInFunction(sp);
  par_mex_dirty = 0U;
}

void emlrt_synchGlobalsToML(const emlrtStack *sp)
{
  (void)sp;
  MEXGlobalSyncOutFunction(false);
}

/* End of code generation (_coder_EOM_eq_api.c) */
