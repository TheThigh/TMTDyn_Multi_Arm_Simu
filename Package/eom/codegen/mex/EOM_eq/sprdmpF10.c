/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sprdmpF10.c
 *
 * Code generation for function 'sprdmpF10'
 *
 */

/* Include files */
#include "sprdmpF10.h"
#include "EOM_eq_data.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo fb_emlrtRSI = {
    63,          /* lineNo */
    "sprdmpF10", /* fcnName */
    "D:\\R - Clemson\\SRA Program\\Simulation "
    "Package\\TMTDyn_2_Arm_Backpack\\V002\\eom\\sprdmpF10.m" /* pathName */
};

static emlrtRTEInfo emlrtRTEI = {
    13,     /* lineNo */
    9,      /* colNo */
    "sqrt", /* fName */
    "E:\\SOFTWARE\\DARK "
    "TECH\\MathWorks\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m" /* pName */
};

/* Function Definitions */
void sprdmpF10(const emlrtStack *sp, const real_T in1[34], const real_T in2[18],
               real_T s, creal_T out1[54], creal_T out2[6], creal_T out3[6],
               real_T out4[6])
{
  emlrtStack st;
  creal_T t144;
  creal_T t145;
  creal_T t146;
  real_T ai;
  real_T ar;
  real_T b_in2_re_tmp;
  real_T c_in2_re_tmp;
  real_T d_in2_re_tmp;
  real_T in2_re_tmp;
  real_T t103;
  real_T t104;
  real_T t105;
  real_T t106;
  real_T t107;
  real_T t108;
  real_T t109;
  real_T t11;
  real_T t110;
  real_T t117;
  real_T t118;
  real_T t12;
  real_T t120;
  real_T t121;
  real_T t122;
  real_T t123;
  real_T t124;
  real_T t126;
  real_T t127;
  real_T t128;
  real_T t131;
  real_T t132;
  real_T t133;
  real_T t136;
  real_T t137;
  real_T t139;
  real_T t142;
  real_T t143;
  real_T t147_im;
  real_T t147_re;
  real_T t148_im;
  real_T t148_re;
  real_T t15;
  real_T t151;
  real_T t153_im;
  real_T t153_re;
  real_T t154_im;
  real_T t154_re;
  real_T t155_im;
  real_T t155_re;
  real_T t16;
  real_T t161_im;
  real_T t161_re;
  real_T t162_im;
  real_T t162_re;
  real_T t165_im;
  real_T t165_re;
  real_T t166_im;
  real_T t166_re;
  real_T t171_im;
  real_T t171_re;
  real_T t172_im;
  real_T t172_re;
  real_T t183_im;
  real_T t183_re;
  real_T t184_im;
  real_T t184_re;
  real_T t210_re;
  real_T t211_re;
  real_T t212_im;
  real_T t212_re;
  real_T t213_im;
  real_T t213_re;
  real_T t214_re;
  real_T t215_re;
  real_T t224_im;
  real_T t224_re;
  real_T t226_im;
  real_T t226_re;
  real_T t228_re;
  real_T t229_re;
  real_T t230_im;
  real_T t230_re;
  real_T t231_im;
  real_T t231_re;
  real_T t240_im;
  real_T t240_re;
  real_T t241_im;
  real_T t241_re;
  real_T t242_re;
  real_T t243_re;
  real_T t244_re;
  real_T t249_im;
  real_T t249_re;
  real_T t25;
  real_T t250_im;
  real_T t250_re;
  real_T t256_im;
  real_T t256_re;
  real_T t258_im;
  real_T t258_re;
  real_T t260_im;
  real_T t260_re;
  real_T t264_im;
  real_T t264_re;
  real_T t265_im;
  real_T t265_re;
  real_T t268_im;
  real_T t268_re;
  real_T t269_im;
  real_T t269_re;
  real_T t27;
  real_T t278_im;
  real_T t278_re;
  real_T t279_im;
  real_T t279_re;
  real_T t281_im;
  real_T t281_re;
  real_T t282_im;
  real_T t282_re;
  real_T t285_re;
  real_T t296_im;
  real_T t296_re;
  real_T t297_im;
  real_T t297_re;
  real_T t298_im;
  real_T t298_re;
  real_T t299_im;
  real_T t299_re;
  real_T t30;
  real_T t300_im;
  real_T t300_re;
  real_T t303_im;
  real_T t303_re;
  real_T t304_im;
  real_T t304_re;
  real_T t306_im;
  real_T t306_re;
  real_T t307_im;
  real_T t307_re;
  real_T t31;
  real_T t312_im;
  real_T t312_re;
  real_T t316_im;
  real_T t316_re;
  real_T t317_im;
  real_T t317_re;
  real_T t32;
  real_T t329_im;
  real_T t329_re;
  real_T t33;
  real_T t34;
  real_T t342_im;
  real_T t342_re;
  real_T t35;
  real_T t359_im;
  real_T t359_re;
  real_T t359_re_tmp;
  real_T t360_im;
  real_T t360_re;
  real_T t360_re_tmp;
  real_T t361_im;
  real_T t361_re;
  real_T t361_re_tmp;
  real_T t362_im;
  real_T t362_re;
  real_T t363_im;
  real_T t363_re;
  real_T t364_im;
  real_T t364_re;
  real_T t365_im;
  real_T t365_re;
  real_T t366_im;
  real_T t366_re;
  real_T t367_im;
  real_T t367_re;
  real_T t374_im;
  real_T t374_re;
  real_T t375_im;
  real_T t375_re;
  real_T t376_im;
  real_T t376_re;
  real_T t377_im;
  real_T t377_re;
  real_T t378_im;
  real_T t378_re;
  real_T t39;
  real_T t39_tmp;
  real_T t4;
  real_T t40;
  real_T t40_tmp;
  real_T t41;
  real_T t41_tmp;
  real_T t42;
  real_T t42_tmp;
  real_T t46;
  real_T t47_tmp;
  real_T t48;
  real_T t49;
  real_T t49_im_tmp;
  real_T t49_re_tmp;
  real_T t5;
  real_T t50;
  real_T t51;
  real_T t52;
  real_T t52_tmp;
  real_T t53;
  real_T t53_tmp;
  real_T t54;
  real_T t54_tmp;
  real_T t57;
  real_T t6;
  real_T t61;
  real_T t62;
  real_T t63;
  real_T t64;
  real_T t65;
  real_T t65_im;
  real_T t65_re;
  real_T t66;
  real_T t66_tmp;
  real_T t68;
  real_T t7;
  real_T t71_tmp;
  real_T t72_tmp;
  real_T t73_tmp;
  real_T t8;
  real_T t87;
  real_T t88;
  real_T t89;
  real_T t9;
  real_T t90;
  real_T t91;
  real_T t92;
  st.prev = sp;
  st.tls = sp->tls;
  /* sprdmpF10 */
  /*     [OUT1,OUT2,OUT3,OUT4,OUT5,OUT6,OUT7] = sprdmpF10(IN1,IN2,S,DS,T_SYM) */
  /*     This function was generated by the Symbolic Math Toolbox version 9.1.
   */
  /*     07-Mar-2023 03:42:29 */
  t68 = muDoubleScalarCos(in1[20]);
  t30 = muDoubleScalarSin(in1[20]);
  t4 = in2[3] * s;
  t5 = in2[5] * s;
  t6 = in2[7] * s;
  t7 = in1[33] * in1[33];
  t8 = in1[19] * in1[19];
  t9 = in1[18] * in1[18];
  t11 = in1[2] * in1[2];
  t12 = in1[3] * in1[3];
  t15 = s * s;
  t16 = muDoubleScalarPower(s, 3.0);
  t285_re = in2[2] * s * 2.0;
  t25 = 1.0 / in1[33];
  st.site = &fb_emlrtRSI;
  if (in1[33] < 0.0) {
    emlrtErrorWithMessageIdR2018a(
        &st, &emlrtRTEI, "Coder:toolbox:ElFunDomainError",
        "Coder:toolbox:ElFunDomainError", 3, 4, 4, "sqrt");
  }
  t46 = 1.0 / muDoubleScalarSqrt(in1[33]);
  t27 = 1.0 / (t30 * t30);
  t30 = in2[4] * t15;
  t31 = in2[6] * t15;
  t32 = in2[8] * t15;
  t33 = in2[3] + in2[4] * s * 2.0;
  t34 = in2[5] + in2[6] * s * 2.0;
  t35 = in2[7] + in2[8] * s * 2.0;
  t39_tmp = in2[0] * t15;
  t39 = t39_tmp * 2.0;
  t40_tmp = in2[0] * t16;
  t40 = t40_tmp * 2.0;
  t41_tmp = in2[1] * t15;
  t41 = t41_tmp * 2.0;
  t42_tmp = in2[1] * t16;
  t42 = t42_tmp * 2.0;
  t47_tmp = t7 * (t68 * t68);
  t48 = s * (t285_re + 1.0);
  t49 = t4 + t30;
  t50 = t5 + t31;
  t51 = t6 + t32;
  t52_tmp = s * t33;
  t52 = t52_tmp * 2.0;
  t53_tmp = s * t34;
  t53 = t53_tmp * 2.0;
  t54_tmp = s * t35;
  t54 = t54_tmp * 2.0;
  t57 = t15 * (t285_re + 1.0);
  t378_re = t15 * t33;
  t62 = t378_re * 2.0;
  t378_im = t15 * t34;
  t64 = t378_im * 2.0;
  t66_tmp = t15 * t35;
  t66 = t66_tmp * 2.0;
  t61 = t4 * 2.0 + t30 * 2.0;
  t63 = t5 * 2.0 + t31 * 2.0;
  t65 = t6 * 2.0 + t32 * 2.0;
  t16 = t49 * t49;
  t68 = t50 * t50;
  t30 = t51 * t51;
  t71_tmp = s * t49;
  t4 = t71_tmp * 4.0;
  t72_tmp = s * t50;
  t31 = t72_tmp * 4.0;
  t73_tmp = s * t51;
  t5 = t73_tmp * 4.0;
  t103 = t41 * t49;
  t104 = t42 * t49;
  t105 = t39 * t50;
  t106 = t40 * t50;
  t107 = t39 * t51;
  t108 = t40 * t51;
  t109 = t41 * t51;
  t110 = t42 * t51;
  t117 = t48 * t49;
  t118 = t48 * t50;
  t120 = t49 * t57;
  t121 = t50 * t57;
  t87 = s * t61 * 2.0;
  t88 = s * t63 * 2.0;
  t89 = s * t65 * 2.0;
  t90 = s * t16 * 2.0;
  t91 = s * t68 * 2.0;
  t92 = s * t30 * 2.0;
  t122 = t52 + t61;
  t123 = t53 + t63;
  t124 = t54 + t65;
  t126 = t50 * t4;
  t127 = t51 * t4;
  t128 = t51 * t31;
  t131 = t62 + t4;
  t132 = t64 + t31;
  t133 = t66 + t5;
  t6 = in2[0] * s;
  t32 = in2[1] * s;
  t139 = (t6 * t49 * 2.0 + t32 * t50 * 2.0) + (t285_re + 1.0) * t51;
  t151 = (t33 * t49 * 2.0 + t34 * t50 * 2.0) + t35 * t51 * 2.0;
  t136 = s * (((t16 + t68) + t30) - 1.0) * 2.0;
  t142 = s * t139;
  t143 = t15 * t139;
  t137 = 1.0 / t7 * (t11 * t11 + -(t12 * t12)) +
         t9 * t9 * (t27 * t27) * ((t47_tmp - 1.0) * (t47_tmp - 1.0)) * 6.0;
  t144.re = ((-t16 + -t68) + -t30) + 1.0;
  t144.im = 0.0;
  b_sqrt(&t144);
  if (t144.im == 0.0) {
    t145.re = 1.0 / t144.re;
    t145.im = 0.0;
  } else if (t144.re == 0.0) {
    t145.re = 0.0;
    t145.im = -(1.0 / t144.im);
  } else {
    t30 = muDoubleScalarAbs(t144.re);
    t16 = muDoubleScalarAbs(t144.im);
    if (t30 > t16) {
      t16 = t144.im / t144.re;
      t68 = t144.re + t16 * t144.im;
      t145.re = (t16 * 0.0 + 1.0) / t68;
      t145.im = (0.0 - t16) / t68;
    } else if (t16 == t30) {
      if (t144.re > 0.0) {
        t16 = 0.5;
      } else {
        t16 = -0.5;
      }
      if (t144.im > 0.0) {
        t68 = 0.5;
      } else {
        t68 = -0.5;
      }
      t145.re = (t16 + 0.0 * t68) / t30;
      t145.im = (0.0 * t16 - t68) / t30;
    } else {
      t16 = t144.re / t144.im;
      t68 = t144.im + t16 * t144.re;
      t145.re = t16 / t68;
      t145.im = (t16 * 0.0 - 1.0) / t68;
    }
  }
  t147_re = 2.0 * t144.re;
  t147_im = 2.0 * t144.im;
  t148_re = 4.0 * (s * t144.re);
  t148_im = 4.0 * (s * t144.im);
  t153_re = t4 * t144.re;
  t153_im = t4 * t144.im;
  t154_re = t31 * t144.re;
  t154_im = t31 * t144.im;
  t155_re = t5 * t144.re;
  t155_im = t5 * t144.im;
  t146 = power(t145);
  t161_re = t105 * t145.re;
  t161_im = t105 * t145.im;
  t162_re = t106 * t145.re;
  t162_im = t106 * t145.im;
  t165_re = t109 * t145.re;
  t165_im = t109 * t145.im;
  t166_re = t110 * t145.re;
  t166_im = t110 * t145.im;
  t171_re = t117 * t145.re;
  t171_im = t117 * t145.im;
  t172_re = t118 * t145.re;
  t172_im = t118 * t145.im;
  t183_re = t120 * t145.re;
  t183_im = t120 * t145.im;
  t184_re = t121 * t145.re;
  t184_im = t121 * t145.im;
  t242_re = t126 + t155_re;
  t243_re = t127 + t154_re;
  t244_re = t128 + t153_re;
  t249_re = (t6 * t50 * 2.0 + -(t32 * t49 * 2.0)) + (t285_re + 1.0) * t144.re;
  t249_im = (t285_re + 1.0) * t144.im;
  t16 = t63 * t122;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t260_re = ar / 2.0;
    t260_im = 0.0;
  } else if (ar == 0.0) {
    t260_re = 0.0;
    t260_im = ai / 2.0;
  } else {
    t260_re = ar / 2.0;
    t260_im = ai / 2.0;
  }
  t16 = t61 * t124;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t264_re = ar / 2.0;
    t264_im = 0.0;
  } else if (ar == 0.0) {
    t264_re = 0.0;
    t264_im = ai / 2.0;
  } else {
    t264_re = ar / 2.0;
    t264_im = ai / 2.0;
  }
  t16 = t65 * t123;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t265_re = ar / 2.0;
    t265_im = 0.0;
  } else if (ar == 0.0) {
    t265_re = 0.0;
    t265_im = ai / 2.0;
  } else {
    t265_re = ar / 2.0;
    t265_im = ai / 2.0;
  }
  t297_re = t151 * (s * t145.re);
  t297_im = t151 * (s * t145.im);
  t298_re = t151 * (t15 * t145.re);
  t298_im = t151 * (t15 * t145.im);
  t210_re = t39 + t165_re;
  t211_re = t40 + t166_re;
  in2_re_tmp = t39_tmp * t51;
  t212_re = t41 + in2_re_tmp * t145.re * -2.0;
  t212_im = in2_re_tmp * t145.im * -2.0;
  b_in2_re_tmp = t40_tmp * t51;
  t213_re = t42 + b_in2_re_tmp * t145.re * -2.0;
  t213_im = b_in2_re_tmp * t145.im * -2.0;
  t214_re = t41 + t171_re;
  t215_re = t48 + t161_re;
  c_in2_re_tmp = t41_tmp * t49;
  t224_re = t48 + c_in2_re_tmp * t145.re * -2.0;
  t224_im = c_in2_re_tmp * t145.im * -2.0;
  t226_re = t51 * t171_re;
  t226_im = t51 * t171_im;
  t228_re = t42 + t183_re;
  t229_re = t57 + t162_re;
  d_in2_re_tmp = t42_tmp * t49;
  t230_re = t57 + d_in2_re_tmp * t145.re * -2.0;
  t230_im = d_in2_re_tmp * t145.im * -2.0;
  t231_re = t51 * t183_re;
  t231_im = t51 * t183_im;
  t250_re = (-(t6 * t51 * 2.0) + (t285_re + 1.0) * t49) + t32 * t147_re;
  t250_im = t32 * t147_im;
  t258_re = (t32 * t51 * 2.0 + -((t285_re + 1.0) * t50)) + t6 * t147_re;
  t258_im = t6 * t147_im;
  t268_re = s * t249_re;
  t268_im = s * t249_im;
  t281_re = t15 * t249_re;
  t281_im = t15 * t249_im;
  t31 = t71_tmp * t63;
  ar = t31 * t146.re * t151;
  ai = t31 * t146.im * t151;
  if (ai == 0.0) {
    t312_re = ar / 2.0;
    t312_im = 0.0;
  } else if (ar == 0.0) {
    t312_re = 0.0;
    t312_im = ai / 2.0;
  } else {
    t312_re = ar / 2.0;
    t312_im = ai / 2.0;
  }
  t31 = t73_tmp * t61;
  ar = t31 * t146.re * t151;
  ai = t31 * t146.im * t151;
  if (ai == 0.0) {
    t316_re = ar / 2.0;
    t316_im = 0.0;
  } else if (ar == 0.0) {
    t316_re = 0.0;
    t316_im = ai / 2.0;
  } else {
    t316_re = ar / 2.0;
    t316_im = ai / 2.0;
  }
  t31 = t72_tmp * t65;
  ar = t31 * t146.re * t151;
  ai = t31 * t146.im * t151;
  if (ai == 0.0) {
    t317_re = ar / 2.0;
    t317_im = 0.0;
  } else if (ar == 0.0) {
    t317_re = 0.0;
    t317_im = ai / 2.0;
  } else {
    t317_re = ar / 2.0;
    t317_im = ai / 2.0;
  }
  t171_re = t39 + -t172_re;
  t183_re = t40 + -t184_re;
  t240_re = t51 * t212_re;
  t240_im = t51 * t212_im;
  t241_re = t51 * t213_re;
  t241_im = t51 * t213_im;
  t256_re = t49 * t224_re;
  t256_im = t49 * t224_im;
  t269_re = s * t250_re;
  t269_im = s * t250_im;
  t278_re = s * t258_re;
  t278_im = s * t258_im;
  t279_re = t49 * t230_re;
  t279_im = t49 * t230_im;
  t282_re = t15 * t250_re;
  t282_im = t15 * t250_im;
  t296_re = t15 * t258_re;
  t296_im = t15 * t258_im;
  t299_re = t144.re * t210_re - t144.im * t165_im;
  t299_im = t144.re * t165_im + t144.im * t210_re;
  t300_re = t144.re * t211_re - t144.im * t166_im;
  t300_im = t144.re * t166_im + t144.im * t211_re;
  t303_re = t144.re * t214_re - t144.im * t171_im;
  t303_im = t144.re * t171_im + t144.im * t214_re;
  t304_re = t144.re * t215_re - t144.im * t161_im;
  t304_im = t144.re * t161_im + t144.im * t215_re;
  t306_re = t144.re * t228_re - t144.im * t183_im;
  t306_im = t144.re * t183_im + t144.im * t228_re;
  t307_re = t144.re * t229_re - t144.im * t162_im;
  t307_im = t144.re * t162_im + t144.im * t229_re;
  t49_re_tmp = t49 * t145.re;
  t49_im_tmp = t49 * t145.im;
  t329_re = t49_re_tmp * t268_re - t49_im_tmp * t268_im;
  t329_im = t49_re_tmp * t268_im + t49_im_tmp * t268_re;
  t342_re = t49_re_tmp * t281_re - t49_im_tmp * t281_im;
  t342_im = t49_re_tmp * t281_im + t49_im_tmp * t281_re;
  t31 = t54_tmp * t49;
  t16 = t65 * t122;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t71_tmp * t65;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t359_re_tmp = -t53 + t63;
  t359_re = ((t359_re_tmp + t31 * t145.re * -2.0) + t65_re) + t16;
  t359_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t52_tmp * t50;
  t16 = t61 * t123;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t72_tmp * t61;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t360_re_tmp = -t54 + t65;
  t360_re = ((t360_re_tmp + t31 * t145.re * -2.0) + t65_re) + t16;
  t360_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t53_tmp * t51;
  t16 = t63 * t124;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t73_tmp * t63;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t361_re_tmp = -t52 + t61;
  t361_re = ((t361_re_tmp + t31 * t145.re * -2.0) + t65_re) + t16;
  t361_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t378_im * t49;
  t16 = t63 * t131;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t4 = t15 * t49;
  t16 = t4 * t63;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t362_re = (((t66 + -t89) + t31 * t145.re * -2.0) + t65_re) + t16;
  t362_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t66_tmp * t49;
  t16 = t65 * t131;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t4 * t65;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t363_re = (((-t64 + t88) + t31 * t145.re * -2.0) + t65_re) + t16;
  t363_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t378_re * t50;
  t16 = t61 * t132;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t32 = t15 * t50;
  t16 = t32 * t61;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t364_re = (((-t66 + t89) + t31 * t145.re * -2.0) + t65_re) + t16;
  t364_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t66_tmp * t50;
  t16 = t65 * t132;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t32 * t65;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t365_re = (((t62 + -t87) + t31 * t145.re * -2.0) + t65_re) + t16;
  t365_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t378_re * t51;
  t16 = t61 * t133;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t5 = t15 * t51;
  t16 = t5 * t61;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t366_re = (((t64 + -t88) + t31 * t145.re * -2.0) + t65_re) + t16;
  t366_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t378_im * t51;
  t16 = t63 * t133;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t5 * t63;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t367_re = (((-t62 + t87) + t31 * t145.re * -2.0) + t65_re) + t16;
  t367_im = (t31 * t145.im * -2.0 + t65_im) + t30;
  t31 = t52_tmp * t49;
  t16 = t61 * t122;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t71_tmp * t61;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t374_re = (((t147_re + t31 * t145.re * -2.0) + t65_re) + t297_re) + t16;
  t374_im = (((t147_im + t31 * t145.im * -2.0) + t65_im) + t297_im) + t30;
  t31 = t53_tmp * t50;
  t16 = t63 * t123;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t72_tmp * t63;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t375_re = (((t147_re + t31 * t145.re * -2.0) + t65_re) + t297_re) + t16;
  t375_im = (((t147_im + t31 * t145.im * -2.0) + t65_im) + t297_im) + t30;
  t31 = t54_tmp * t51;
  t16 = t65 * t124;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t73_tmp * t65;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t376_re = (((t147_re + t31 * t145.re * -2.0) + t65_re) + t297_re) + t16;
  t376_im = (((t147_im + t31 * t145.im * -2.0) + t65_im) + t297_im) + t30;
  t31 = t378_re * t49;
  t16 = t61 * t131;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t4 * t61;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t377_re = (((t148_re + t31 * t145.re * -2.0) + t65_re) + t298_re) + t16;
  t377_im = (((t148_im + t31 * t145.im * -2.0) + t65_im) + t298_im) + t30;
  t31 = t378_im * t50;
  t16 = t63 * t132;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t32 * t63;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t378_re = (((t148_re + t31 * t145.re * -2.0) + t65_re) + t298_re) + t16;
  t378_im = (((t148_im + t31 * t145.im * -2.0) + t65_im) + t298_im) + t30;
  t31 = t66_tmp * t51;
  t16 = t65 * t133;
  ar = t16 * t145.re;
  ai = t16 * t145.im;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t5 * t65;
  ar = t16 * t146.re * t151;
  ai = t16 * t146.im * t151;
  if (ai == 0.0) {
    t16 = ar / 2.0;
    t30 = 0.0;
  } else if (ar == 0.0) {
    t16 = 0.0;
    t30 = ai / 2.0;
  } else {
    t16 = ar / 2.0;
    t30 = ai / 2.0;
  }
  t133 = (((t148_re + t31 * t145.re * -2.0) + t65_re) + t298_re) + t16;
  t132 = (((t148_im + t31 * t145.im * -2.0) + t65_im) + t298_im) + t30;
  t42 = t50 * t171_re;
  t57 = t50 * -t172_im;
  t285_re = t50 * t183_re;
  t39 = t50 * -t184_im;
  t4 = t51 * t145.re;
  t31 = t51 * t145.im;
  t40 = t4 * t269_re - t31 * t269_im;
  t89 = t4 * t269_im + t31 * t269_re;
  t16 = t50 * t145.re;
  t30 = t50 * t145.im;
  t88 = t16 * t278_re - t30 * t278_im;
  t66 = t16 * t278_im + t30 * t278_re;
  t87 = t4 * t282_re - t31 * t282_im;
  t122 = t4 * t282_im + t31 * t282_re;
  t64 = t16 * t296_re - t30 * t296_im;
  t123 = t16 * t296_im + t30 * t296_re;
  t15 = ((t142 + t49 * t210_re) + t50 * t212_re) +
        -(t4 * t268_re - t31 * t268_im);
  t62 = (t49 * t165_im + t50 * t212_im) + -(t4 * t268_im + t31 * t268_re);
  t124 = ((t143 + t49 * t211_re) + t50 * t213_re) +
         -(t4 * t281_re - t31 * t281_im);
  t131 = (t49 * t166_im + t50 * t213_im) + -(t4 * t281_im + t31 * t281_re);
  t41 = ((((t109 + t50 * (t103 * t145.re)) + -(t50 * t215_re)) + t278_re) +
         (t144.re * t171_re - t144.im * -t172_im)) +
        -(t16 * t268_re - t30 * t268_im);
  t48 = (((t50 * (t103 * t145.im) + -(t50 * t161_im)) + t278_im) +
         (t144.re * -t172_im + t144.im * t171_re)) +
        -(t16 * t268_im + t30 * t268_re);
  t32 = ((((t110 + t50 * (t104 * t145.re)) + -(t50 * t229_re)) + t296_re) +
         (t144.re * t183_re - t144.im * -t184_im)) +
        -(t16 * t281_re - t30 * t281_im);
  t6 = (((t50 * (t104 * t145.im) + -(t50 * t162_im)) + t296_im) +
        (t144.re * -t184_im + t144.im * t183_re)) +
       -(t16 * t281_im + t30 * t281_re);
  t68 = ((t142 + t50 * t214_re) + t51 * t224_re) +
        -(t49_re_tmp * t278_re - t49_im_tmp * t278_im);
  t7 = (t50 * t171_im + t51 * t224_im) +
       -(t49_re_tmp * t278_im + t49_im_tmp * t278_re);
  t298_re = ((t142 + t51 * t215_re) + t49 * t171_re) +
            -(t16 * t269_re - t30 * t269_im);
  t298_im = (t51 * t161_im + t49 * -t172_im) + -(t16 * t269_im + t30 * t269_re);
  t215_re = ((t143 + t50 * t228_re) + t51 * t230_re) +
            -(t49_re_tmp * t296_re - t49_im_tmp * t296_im);
  t5 = (t50 * t183_im + t51 * t230_im) +
       -(t49_re_tmp * t296_im + t49_im_tmp * t296_re);
  t146.re = ((t143 + t51 * t229_re) + t49 * t183_re) +
            -(t16 * t282_re - t30 * t282_im);
  t146.im = (t51 * t162_im + t49 * -t184_im) + -(t16 * t282_im + t30 * t282_re);
  t148_re = ((((t105 + t49 * (t107 * t145.re)) + t268_re) + -(t49 * t214_re)) +
             (t144.re * t224_re - t144.im * t224_im)) +
            -(t49_re_tmp * t269_re - t49_im_tmp * t269_im);
  t148_im = (((t49 * (t107 * t145.im) + t268_im) + -(t49 * t171_im)) +
             (t144.re * t224_im + t144.im * t224_re)) +
            -(t49_re_tmp * t269_im + t49_im_tmp * t269_re);
  t297_re = ((((t117 + t51 * t172_re) + -(t51 * t210_re)) + t269_re) +
             (t144.re * t212_re - t144.im * t212_im)) +
            -(t4 * t278_re - t31 * t278_im);
  t297_im = (((t51 * t172_im + -(t51 * t165_im)) + t269_im) +
             (t144.re * t212_im + t144.im * t212_re)) +
            -(t4 * t278_im + t31 * t278_re);
  t183_re = ((((t106 + t49 * (t108 * t145.re)) + t281_re) + -(t49 * t228_re)) +
             (t144.re * t230_re - t144.im * t230_im)) +
            -(t49_re_tmp * t282_re - t49_im_tmp * t282_im);
  t183_im = (((t49 * (t108 * t145.im) + t281_im) + -(t49 * t183_im)) +
             (t144.re * t230_im + t144.im * t230_re)) +
            -(t49_re_tmp * t282_im + t49_im_tmp * t282_re);
  t171_re = ((((t120 + t51 * t184_re) + -(t51 * t211_re)) + t282_re) +
             (t144.re * t213_re - t144.im * t213_im)) +
            -(t4 * t296_re - t31 * t296_im);
  t171_im = (((t51 * t184_im + -(t51 * t166_im)) + t282_im) +
             (t144.re * t213_im + t144.im * t213_re)) +
            -(t4 * t296_im + t31 * t296_re);
  out1[0].re = ((t90 + -t91) + -t92) + -t136;
  out1[0].im = 0.0;
  out1[1].re = t242_re;
  out1[1].im = t155_im;
  out1[2].re = t127 + t72_tmp * t144.re * -4.0;
  out1[2].im = t72_tmp * t144.im * -4.0;
  out1[3].re = t68;
  out1[3].im = t7;
  out1[4].re = t215_re;
  out1[4].im = t5;
  t16 = t41_tmp * t50 * t51;
  out1[5].re =
      ((((t103 - t268_re) - t42) - t304_re) - t88) - t16 * t145.re * 2.0;
  out1[5].im =
      ((((0.0 - t268_im) - t57) - t304_im) - t66) - t16 * t145.im * 2.0;
  t16 = t42_tmp * t50 * t51;
  out1[6].re =
      ((((t104 - t281_re) - t285_re) - t307_re) - t64) - t16 * t145.re * 2.0;
  out1[6].im =
      ((((0.0 - t281_im) - t39) - t307_im) - t123) - t16 * t145.im * 2.0;
  out1[7].re = t297_re;
  out1[7].im = t297_im;
  out1[8].re = t171_re;
  out1[8].im = t171_im;
  out1[9].re = t126 + t73_tmp * t144.re * -4.0;
  out1[9].im = t73_tmp * t144.im * -4.0;
  out1[10].re = ((t91 + -t90) + -t92) + -t136;
  out1[10].im = 0.0;
  out1[11].re = t244_re;
  out1[11].im = t153_im;
  out1[12].re = t148_re;
  out1[12].im = t148_im;
  out1[13].re = t183_re;
  out1[13].im = t183_im;
  out1[14].re = t298_re;
  out1[14].im = t298_im;
  out1[15] = t146;
  out1[16].re = ((((t118 - t226_re) - t240_re) - t278_re) - t299_re) - t40;
  out1[16].im = ((((0.0 - t226_im) - t240_im) - t278_im) - t299_im) - t89;
  out1[17].re = ((((t121 - t231_re) - t241_re) - t296_re) - t300_re) - t87;
  out1[17].im = ((((0.0 - t231_im) - t241_im) - t296_im) - t300_im) - t122;
  out1[18].re = t243_re;
  out1[18].im = t154_im;
  out1[19].re = t128 + t71_tmp * t144.re * -4.0;
  out1[19].im = t71_tmp * t144.im * -4.0;
  out1[20].re = ((t92 + -t90) + -t91) + -t136;
  out1[20].im = 0.0;
  t16 = t39_tmp * t49 * t50;
  out1[21].re = ((((t107 - t256_re) - t269_re) - t303_re) - t329_re) -
                t16 * t145.re * 2.0;
  out1[21].im =
      ((((0.0 - t256_im) - t269_im) - t303_im) - t329_im) - t16 * t145.im * 2.0;
  t16 = t40_tmp * t49 * t50;
  out1[22].re = ((((t108 - t279_re) - t282_re) - t306_re) - t342_re) -
                t16 * t145.re * 2.0;
  out1[22].im =
      ((((0.0 - t279_im) - t282_im) - t306_im) - t342_im) - t16 * t145.im * 2.0;
  out1[23].re = t41;
  out1[23].im = t48;
  out1[24].re = t32;
  out1[24].im = t6;
  out1[25].re = t15;
  out1[25].im = t62;
  out1[26].re = t124;
  out1[26].im = t131;
  out1[27].re = 0.0;
  out1[27].im = 0.0;
  out1[28].re = 0.0;
  out1[28].im = 0.0;
  out1[29].re = 0.0;
  out1[29].im = 0.0;
  out1[30].re = t374_re;
  out1[30].im = t374_im;
  out1[31].re = t377_re;
  out1[31].im = t377_im;
  out1[32].re = t360_re;
  out1[32].im = t360_im;
  out1[33].re = t364_re;
  out1[33].im = t364_im;
  t31 = t52_tmp * t51;
  out1[34].re = (((t53 - t63) + t264_re) + t316_re) - t31 * t145.re * 2.0;
  out1[34].im = (t264_im + t316_im) - t31 * t145.im * 2.0;
  out1[35].re = t366_re;
  out1[35].im = t366_im;
  out1[36].re = 0.0;
  out1[36].im = 0.0;
  out1[37].re = 0.0;
  out1[37].im = 0.0;
  out1[38].re = 0.0;
  out1[38].im = 0.0;
  t31 = t53_tmp * t49;
  out1[39].re = (((t54 - t65) + t260_re) + t312_re) - t31 * t145.re * 2.0;
  out1[39].im = (t260_im + t312_im) - t31 * t145.im * 2.0;
  out1[40].re = t362_re;
  out1[40].im = t362_im;
  out1[41].re = t375_re;
  out1[41].im = t375_im;
  out1[42].re = t378_re;
  out1[42].im = t378_im;
  out1[43].re = t361_re;
  out1[43].im = t361_im;
  out1[44].re = t367_re;
  out1[44].im = t367_im;
  out1[45].re = 0.0;
  out1[45].im = 0.0;
  out1[46].re = 0.0;
  out1[46].im = 0.0;
  out1[47].re = 0.0;
  out1[47].im = 0.0;
  out1[48].re = t359_re;
  out1[48].im = t359_im;
  out1[49].re = t363_re;
  out1[49].im = t363_im;
  t31 = t54_tmp * t50;
  out1[50].re = (((t52 - t61) + t265_re) + t317_re) - t31 * t145.re * 2.0;
  out1[50].im = (t265_im + t317_im) - t31 * t145.im * 2.0;
  out1[51].re = t365_re;
  out1[51].im = t365_im;
  out1[52].re = t376_re;
  out1[52].im = t376_im;
  out1[53].re = t133;
  out1[53].im = t132;
  t30 = in1[1] * t25;
  t16 = t30 * (t25 * (t11 + -t12) + -(t9 * t27 * (t47_tmp - 1.0) * 6.0)) *
        3.1415926535897931;
  ar = t16 * (((t49 * t139 - t50 * t249_re) + t51 * t250_re) +
              (t144.re * t258_re - t144.im * t258_im));
  ai = t16 * (((0.0 - t50 * t249_im) + t51 * t250_im) +
              (t144.re * t258_im + t144.im * t258_re));
  if (ai == 0.0) {
    out2[0].re = ar / 3.0;
    out2[0].im = 0.0;
  } else if (ar == 0.0) {
    out2[0].re = 0.0;
    out2[0].im = ai / 3.0;
  } else {
    out2[0].re = ar / 3.0;
    out2[0].im = ai / 3.0;
  }
  ar = t16 * (((t50 * t139 + t49 * t249_re) - t51 * t258_re) +
              (t144.re * t250_re - t144.im * t250_im));
  ai = t16 * ((t49 * t249_im - t51 * t258_im) +
              (t144.re * t250_im + t144.im * t250_re));
  if (ai == 0.0) {
    out2[1].re = ar / 3.0;
    out2[1].im = 0.0;
  } else if (ar == 0.0) {
    out2[1].re = 0.0;
    out2[1].im = ai / 3.0;
  } else {
    out2[1].re = ar / 3.0;
    out2[1].im = ai / 3.0;
  }
  out2[2].re = t16 * ((((t51 * t139 - t49 * t250_re) + t50 * t258_re) +
                       (t144.re * t249_re - t144.im * t249_im)) -
                      1.0);
  out2[2].im = t16 * (((0.0 - t49 * t250_im) + t50 * t258_im) +
                      (t144.re * t249_im + t144.im * t249_re));
  ar = t61 * t145.re * t151;
  ai = t61 * t145.im * t151;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 =
      t30 * (t137 * 3.1415926535897931 / 4.0 -
             t8 * t9 * t25 * t27 * (t47_tmp - 1.0) * 3.1415926535897931 * 3.0);
  out2[3].re = t16 * (((-t35 * t63 + t34 * t65) + t33 * t147_re) + t65_re);
  out2[3].im = t16 * (t33 * t147_im + t65_im);
  ar = t63 * t145.re * t151;
  ai = t63 * t145.im * t151;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  out2[4].re = t16 * (((t35 * t61 - t33 * t65) + t34 * t147_re) + t65_re);
  out2[4].im = t16 * (t34 * t147_im + t65_im);
  ar = t65 * t145.re * t151;
  ai = t65 * t145.im * t151;
  if (ai == 0.0) {
    t65_re = ar / 2.0;
    t65_im = 0.0;
  } else if (ar == 0.0) {
    t65_re = 0.0;
    t65_im = ai / 2.0;
  } else {
    t65_re = ar / 2.0;
    t65_im = ai / 2.0;
  }
  t16 = t30 * (t137 * 3.1415926535897931 / 2.0 -
               in1[33] * t8 * t9 * t27 * (t47_tmp - 1.0) * 3.1415926535897931);
  ar = t16 * (((-t34 * t61 + t33 * t63) + t35 * t147_re) + t65_re);
  ai = t16 * (t35 * t147_im + t65_im);
  if (ai == 0.0) {
    out2[5].re = ar / 3.0;
    out2[5].im = 0.0;
  } else if (ar == 0.0) {
    out2[5].re = 0.0;
    out2[5].im = ai / 3.0;
  } else {
    out2[5].re = ar / 3.0;
    out2[5].im = ai / 3.0;
  }
  out3[0].re =
      -in1[5] *
      ((((((((-in2[9] * (((t91 + t92) + -t90) + t136) -
              in2[14] * (((((t50 * t165_re + t268_re) + t42) + t304_re) + t88) -
                         c_in2_re_tmp * 2.0)) -
             in2[15] *
                 (((((t50 * t166_re + t281_re) + t285_re) + t307_re) + t64) -
                  d_in2_re_tmp * 2.0)) +
            t242_re * in2[10]) +
           t68 * in2[12]) +
          t215_re * in2[13]) +
         t297_re * in2[16]) +
        t171_re * in2[17]) -
       in2[11] * (t154_re - t71_tmp * t51 * 4.0));
  out3[0].im =
      -in1[5] *
      ((((((((0.0 -
              in2[14] * ((((t50 * t165_im + t268_im) + t57) + t304_im) + t66)) -
             in2[15] * ((((t50 * t166_im + t281_im) + t39) + t307_im) + t123)) +
            t155_im * in2[10]) +
           t7 * in2[12]) +
          t5 * in2[13]) +
         t297_im * in2[16]) +
        t171_im * in2[17]) -
       in2[11] * t154_im);
  out3[1].re =
      -in1[6] *
      ((((((((-in2[10] * (((t90 + t92) + -t91) + t136) + t244_re * in2[11]) +
             t298_re * in2[14]) +
            t146.re * in2[15]) +
           t148_re * in2[12]) +
          t183_re * in2[13]) -
         in2[16] *
             (((((-t118 + t226_re) + t240_re) + t278_re) + t299_re) + t40)) -
        in2[17] *
            (((((-t121 + t231_re) + t241_re) + t296_re) + t300_re) + t87)) -
       in2[9] * (t155_re - t71_tmp * t50 * 4.0));
  out3[1].im =
      -in1[6] *
      (((((((t153_im * in2[11] + t298_im * in2[14]) + t146.im * in2[15]) +
           t148_im * in2[12]) +
          t183_im * in2[13]) -
         in2[16] * ((((t226_im + t240_im) + t278_im) + t299_im) + t89)) -
        in2[17] * ((((t231_im + t241_im) + t296_im) + t300_im) + t122)) -
       in2[9] * t155_im);
  out3[2].re =
      -in1[7] *
      ((((((((-in2[11] * (((t90 + t91) + -t92) + t136) -
              in2[12] * (((((t49 * t161_re + t256_re) + t269_re) + t303_re) +
                          t329_re) -
                         in2_re_tmp * 2.0)) -
             in2[13] * (((((t49 * t162_re + t279_re) + t282_re) + t306_re) +
                         t342_re) -
                        b_in2_re_tmp * 2.0)) +
            t243_re * in2[9]) +
           t15 * in2[16]) +
          t124 * in2[17]) +
         t41 * in2[14]) +
        t32 * in2[15]) -
       in2[10] * (t153_re - t72_tmp * t51 * 4.0));
  out3[2].im =
      -in1[7] *
      ((((((((0.0 -
              in2[12] * ((((t49 * t161_im + t256_im) + t269_im) + t303_im) +
                         t329_im)) -
             in2[13] * ((((t49 * t162_im + t279_im) + t282_im) + t306_im) +
                        t342_im)) +
            t154_im * in2[9]) +
           t62 * in2[16]) +
          t131 * in2[17]) +
         t48 * in2[14]) +
        t6 * in2[15]) -
       in2[10] * t153_im);
  t16 = t51 * t52;
  out3[3].re =
      -in1[8] *
      (((((-in2[16] * (((t359_re_tmp + t16 * t145.re) - t264_re) - t316_re) +
           t360_re * in2[14]) +
          t364_re * in2[15]) +
         t366_re * in2[17]) +
        t374_re * in2[12]) +
       t377_re * in2[13]);
  out3[3].im = -in1[8] * (((((-in2[16] * ((t16 * t145.im - t264_im) - t316_im) +
                              t360_im * in2[14]) +
                             t364_im * in2[15]) +
                            t366_im * in2[17]) +
                           t374_im * in2[12]) +
                          t377_im * in2[13]);
  t31 = t49 * t53;
  out3[4].re =
      -in1[9] *
      (((((-in2[12] * (((t360_re_tmp + t31 * t145.re) - t260_re) - t312_re) +
           t362_re * in2[13]) +
          t361_re * in2[16]) +
         t367_re * in2[17]) +
        t375_re * in2[14]) +
       t378_re * in2[15]);
  out3[4].im = -in1[9] * (((((-in2[12] * ((t31 * t145.im - t260_im) - t312_im) +
                              t362_im * in2[13]) +
                             t361_im * in2[16]) +
                            t367_im * in2[17]) +
                           t375_im * in2[14]) +
                          t378_im * in2[15]);
  t4 = t50 * t54;
  out3[5].re =
      -in1[10] *
      (((((-in2[14] * (((t361_re_tmp + t4 * t145.re) - t265_re) - t317_re) +
           t359_re * in2[12]) +
          t363_re * in2[13]) +
         t365_re * in2[15]) +
        t376_re * in2[16]) +
       t133 * in2[17]);
  out3[5].im = -in1[10] * (((((-in2[14] * ((t4 * t145.im - t265_im) - t317_im) +
                               t359_im * in2[12]) +
                              t363_im * in2[13]) +
                             t365_im * in2[15]) +
                            t376_im * in2[16]) +
                           t132 * in2[17]);
  out4[0] = 0.0;
  out4[1] = 0.0;
  out4[2] = -t9 * t27 * (t47_tmp - 1.0) * 3.1415926535897931 *
            (((((in1[21] + in1[22]) + in1[23]) + in1[24]) + in1[25]) + in1[26]);
  t30 =
      in1[19] * in1[22] * t9 * t27 * t46 * (t47_tmp - 1.0) * 3.1415926535897931;
  t4 = in1[19] * in1[23] * t9 * t27;
  t16 = in1[19] * in1[24] * t9 * t27;
  t68 = in1[19] * in1[25] * t9 * t27;
  t31 = in1[19] * in1[26] * t9 * t27;
  out4[3] = ((((-in1[21] * in1[19] * t9 * t27 * t46 * (t47_tmp - 1.0) *
                    3.1415926535897931 -
                t30) +
               t4 * t46 * (t47_tmp - 1.0) * 3.1415926535897931 / 2.0) +
              t16 * t46 * (t47_tmp - 1.0) * 3.1415926535897931 / 2.0) +
             t68 * t46 * (t47_tmp - 1.0) * 3.1415926535897931 / 2.0) +
            t31 * t46 * (t47_tmp - 1.0) * 3.1415926535897931 / 2.0;
  out4[4] = ((((in1[19] * in1[21] * t9 * t27 * t46 * (t47_tmp - 1.0) *
                    3.1415926535897931 * 6.123233995736766E-17 +
                t30 * 6.123233995736766E-17) +
               t4 * 1.7320508075688772 * t46 * (t47_tmp - 1.0) *
                   3.1415926535897931 / 2.0) +
              t16 * 1.7320508075688772 * t46 * (t47_tmp - 1.0) *
                  3.1415926535897931 / 2.0) -
             t68 * 1.7320508075688772 * t46 * (t47_tmp - 1.0) *
                 3.1415926535897931 / 2.0) -
            t31 * 1.7320508075688772 * t46 * (t47_tmp - 1.0) *
                3.1415926535897931 / 2.0;
  out4[5] = 0.0;
}

/* End of code generation (sprdmpF10.c) */
