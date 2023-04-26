/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * massF2.c
 *
 * Code generation for function 'massF2'
 *
 */

/* Include files */
#include "massF2.h"
#include "EOM_eq_data.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void massF2(const real_T in1[34], const real_T in2[18], real_T out1[36],
            creal_T out2[54], creal_T out3[54], real_T out4[6])
{
  creal_T t53;
  creal_T t54;
  creal_T t55;
  real_T t119_im;
  real_T t119_re;
  real_T t120_im;
  real_T t120_re;
  real_T t121_im;
  real_T t121_re;
  real_T t122_im;
  real_T t122_re;
  real_T t123_im;
  real_T t123_re;
  real_T t124_im;
  real_T t124_re;
  real_T t125_im;
  real_T t125_re;
  real_T t126_im;
  real_T t126_re;
  real_T t127_im;
  real_T t127_re;
  real_T t128_im;
  real_T t128_re;
  real_T t129_im;
  real_T t129_re;
  real_T t13;
  real_T t130_im;
  real_T t130_re;
  real_T t134_im;
  real_T t134_re;
  real_T t135_im;
  real_T t135_re;
  real_T t136_im;
  real_T t136_re;
  real_T t137_im;
  real_T t137_re;
  real_T t138_im;
  real_T t138_re;
  real_T t139_im;
  real_T t139_re;
  real_T t14;
  real_T t140_im;
  real_T t140_re;
  real_T t141_im;
  real_T t141_re;
  real_T t142_im;
  real_T t142_re;
  real_T t143_im;
  real_T t143_re;
  real_T t144_im;
  real_T t144_re;
  real_T t145_im;
  real_T t145_re;
  real_T t15;
  real_T t158_im;
  real_T t158_re;
  real_T t159_im;
  real_T t159_re;
  real_T t160_im;
  real_T t160_re;
  real_T t161_im;
  real_T t161_re;
  real_T t162_im;
  real_T t162_re;
  real_T t163_im;
  real_T t163_re;
  real_T t165_im;
  real_T t166_im;
  real_T t166_re;
  real_T t167_re;
  real_T t168_re;
  real_T t17;
  real_T t170_im;
  real_T t170_re;
  real_T t171_im;
  real_T t171_re;
  real_T t172_im;
  real_T t172_re;
  real_T t173_im;
  real_T t173_re;
  real_T t174_im;
  real_T t174_re;
  real_T t175_im;
  real_T t175_re;
  real_T t176_im;
  real_T t176_re;
  real_T t177_im;
  real_T t177_re;
  real_T t178_im;
  real_T t178_re;
  real_T t179_im;
  real_T t179_re;
  real_T t18;
  real_T t180_im;
  real_T t180_re;
  real_T t181_im;
  real_T t181_re;
  real_T t182_im;
  real_T t182_re;
  real_T t183_im;
  real_T t183_re;
  real_T t184_im;
  real_T t184_re;
  real_T t185_im;
  real_T t185_re;
  real_T t186_im;
  real_T t186_re;
  real_T t187_im;
  real_T t187_re;
  real_T t188_im;
  real_T t188_re;
  real_T t189_im;
  real_T t189_re;
  real_T t19;
  real_T t190_im;
  real_T t190_re;
  real_T t191_im;
  real_T t191_re;
  real_T t192_im;
  real_T t192_re;
  real_T t193_im;
  real_T t193_re;
  real_T t194_re;
  real_T t2;
  real_T t27;
  real_T t28;
  real_T t29;
  real_T t3;
  real_T t31;
  real_T t32;
  real_T t33;
  real_T t34;
  real_T t35;
  real_T t36;
  real_T t37;
  real_T t38;
  real_T t39;
  real_T t4;
  real_T t40;
  real_T t41;
  real_T t42;
  real_T t43;
  real_T t48;
  real_T t49;
  real_T t5;
  real_T t50;
  real_T t56_im;
  real_T t56_re;
  real_T t57_im;
  real_T t57_re;
  real_T t58_im;
  real_T t58_re;
  real_T t6;
  real_T t60_im;
  real_T t60_re;
  real_T t61_im;
  real_T t61_re;
  real_T t62_im;
  real_T t62_re;
  real_T t63_im;
  real_T t63_re;
  real_T t64_im;
  real_T t64_re;
  real_T t65_im;
  real_T t65_re;
  real_T t66_im;
  real_T t66_re;
  real_T t67_im;
  real_T t67_re;
  real_T t68_im;
  real_T t68_re;
  real_T t69_im;
  real_T t69_re;
  real_T t69_re_tmp;
  real_T t7;
  real_T t70_im;
  real_T t70_re;
  real_T t71_im;
  real_T t71_re;
  real_T t71_re_tmp;
  real_T t72_im;
  real_T t72_re;
  real_T t72_re_tmp;
  real_T t73_im;
  real_T t73_re;
  real_T t74_im;
  real_T t74_re;
  real_T t74_re_tmp;
  real_T t75_im;
  real_T t75_re;
  real_T t76_im;
  real_T t76_re;
  real_T t77_im;
  real_T t77_re;
  real_T t78_im;
  real_T t78_re;
  real_T t79_im;
  real_T t79_re;
  real_T t8;
  real_T t80_im;
  real_T t80_re;
  real_T t80_re_tmp;
  real_T t81_im;
  real_T t81_re;
  real_T t82_im;
  real_T t82_re;
  real_T t83_im;
  real_T t83_re;
  real_T t83_re_tmp;
  real_T t84_im;
  real_T t84_re;
  real_T t85_im;
  real_T t85_re;
  real_T t85_re_tmp;
  real_T t86_im;
  real_T t86_re;
  real_T t86_re_tmp;
  real_T t9;
  real_T t91_im;
  real_T t91_re;
  real_T t92_im;
  real_T t92_re;
  /* massF2 */
  /*     [OUT1,OUT2,OUT3,OUT4] = massF2(IN1,IN2,S,DS,T_SYM) */
  /*     This function was generated by the Symbolic Math Toolbox version 9.1.
   */
  /*     07-Mar-2023 03:42:23 */
  t2 = in2[3] * in1[4];
  t3 = in1[4] * in2[5];
  t4 = in1[4] * in2[7];
  t5 = in1[16] * in1[16];
  t6 = in1[4] * in1[4];
  t7 = muDoubleScalarPower(in1[4], 3.0);
  t9 = in1[17] * in1[17];
  t8 = t6 * t6;
  t13 = t6 * 2.0;
  t14 = t7 * 2.0;
  t17 = in1[16] * t6;
  t18 = in1[16] * t7;
  t15 = t8 * 2.0;
  t19 = in1[16] * t8;
  t27 = t2 + in2[4] * t6;
  t28 = t3 + in2[6] * t6;
  t29 = t4 + in2[8] * t6;
  t31 = t2 * 2.0 + in2[4] * t13;
  t32 = t3 * 2.0 + in2[6] * t13;
  t33 = t4 * 2.0 + in2[8] * t13;
  t34 = t27 * t27;
  t35 = muDoubleScalarPower(t27, 3.0);
  t36 = t28 * t28;
  t37 = muDoubleScalarPower(t28, 3.0);
  t38 = t29 * t29;
  t167_re = in1[4] * in1[16];
  t39 = t167_re * t29;
  t43 = t17 * t29;
  t40 = in1[4] * t31;
  t41 = in1[4] * t32;
  t42 = in1[4] * t33;
  t48 = t6 * t31;
  t49 = t6 * t32;
  t50 = t6 * t33;
  t2 = in1[15] * t5 / 4.0 + in1[15] * (t5 + t9 * 3.0) / 12.0;
  out1[0] = in1[15];
  out1[1] = 0.0;
  out1[2] = 0.0;
  out1[3] = 0.0;
  out1[4] = 0.0;
  out1[5] = 0.0;
  out1[6] = 0.0;
  out1[7] = in1[15];
  out1[8] = 0.0;
  out1[9] = 0.0;
  out1[10] = 0.0;
  out1[11] = 0.0;
  out1[12] = 0.0;
  out1[13] = 0.0;
  out1[14] = in1[15];
  out1[15] = 0.0;
  out1[16] = 0.0;
  out1[17] = 0.0;
  out1[18] = 0.0;
  out1[19] = 0.0;
  out1[20] = 0.0;
  out1[21] = t2;
  out1[22] = 0.0;
  out1[23] = 0.0;
  out1[24] = 0.0;
  out1[25] = 0.0;
  out1[26] = 0.0;
  out1[27] = 0.0;
  out1[28] = t2;
  out1[29] = 0.0;
  out1[30] = 0.0;
  out1[31] = 0.0;
  out1[32] = 0.0;
  out1[33] = 0.0;
  out1[34] = 0.0;
  out1[35] = in1[15] * t9 / 2.0;
  t53.re = ((-t34 + -t36) + -t38) + 1.0;
  t53.im = 0.0;
  b_sqrt(&t53);
  if (t53.im == 0.0) {
    t54.re = 1.0 / t53.re;
    t54.im = 0.0;
  } else if (t53.re == 0.0) {
    t54.re = 0.0;
    t54.im = -(1.0 / t53.im);
  } else {
    t4 = muDoubleScalarAbs(t53.re);
    t2 = muDoubleScalarAbs(t53.im);
    if (t4 > t2) {
      t2 = t53.im / t53.re;
      t3 = t53.re + t2 * t53.im;
      t54.re = (t2 * 0.0 + 1.0) / t3;
      t54.im = (0.0 - t2) / t3;
    } else if (t2 == t4) {
      if (t53.re > 0.0) {
        t2 = 0.5;
      } else {
        t2 = -0.5;
      }
      if (t53.im > 0.0) {
        t3 = 0.5;
      } else {
        t3 = -0.5;
      }
      t54.re = (t2 + 0.0 * t3) / t4;
      t54.im = (0.0 * t2 - t3) / t4;
    } else {
      t2 = t53.re / t53.im;
      t3 = t53.im + t2 * t53.re;
      t54.re = t2 / t3;
      t54.im = (t2 * 0.0 - 1.0) / t3;
    }
  }
  t56_re = 2.0 * (in1[4] * t53.re);
  t56_im = 2.0 * (in1[4] * t53.im);
  t57_re = t167_re * t53.re;
  t57_im = t167_re * t53.im;
  t58_re = t17 * t53.re;
  t58_im = t17 * t53.im;
  t53.re *= t13;
  t53.im *= t13;
  t55 = power(t54);
  t2 = t13 * t27;
  t60_re = t2 * t54.re;
  t60_im = t2 * t54.im;
  t2 = t14 * t27;
  t61_re = t2 * t54.re;
  t61_im = t2 * t54.im;
  t2 = t15 * t27;
  t62_re = t2 * t54.re;
  t62_im = t2 * t54.im;
  t2 = t13 * t28;
  t63_re = t2 * t54.re;
  t63_im = t2 * t54.im;
  t2 = t14 * t28;
  t64_re = t2 * t54.re;
  t64_im = t2 * t54.im;
  t2 = t15 * t28;
  t65_re = t2 * t54.re;
  t65_im = t2 * t54.im;
  t2 = t13 * t29;
  t66_re = t2 * t54.re;
  t66_im = t2 * t54.im;
  t2 = t14 * t29;
  t67_re = t2 * t54.re;
  t67_im = t2 * t54.im;
  t2 = t15 * t29;
  t68_re = t2 * t54.re;
  t68_im = t2 * t54.im;
  t69_re_tmp = t17 * t27;
  t69_re = t69_re_tmp * t54.re;
  t69_im = t69_re_tmp * t54.im;
  t165_im = t18 * t27;
  t70_re = t165_im * t54.re;
  t70_im = t165_im * t54.im;
  t71_re_tmp = t19 * t27;
  t71_re = t71_re_tmp * t54.re;
  t71_im = t71_re_tmp * t54.im;
  t72_re_tmp = t17 * t28;
  t72_re = t72_re_tmp * t54.re;
  t72_im = t72_re_tmp * t54.im;
  t166_re = t18 * t28;
  t73_re = t166_re * t54.re;
  t73_im = t166_re * t54.im;
  t74_re_tmp = t19 * t28;
  t74_re = t74_re_tmp * t54.re;
  t74_im = t74_re_tmp * t54.im;
  t75_re = t43 * t54.re;
  t75_im = t43 * t54.im;
  t166_im = t18 * t29;
  t76_re = t166_im * t54.re;
  t76_im = t166_im * t54.im;
  t168_re = t19 * t29;
  t77_re = t168_re * t54.re;
  t77_im = t168_re * t54.im;
  t78_re = t48 * t54.re;
  t78_im = t48 * t54.im;
  t192_im = t7 * t31;
  t79_re = t192_im * t54.re;
  t79_im = t192_im * t54.im;
  t80_re_tmp = t8 * t31;
  t80_re = t80_re_tmp * t54.re;
  t80_im = t80_re_tmp * t54.im;
  t81_re = t49 * t54.re;
  t81_im = t49 * t54.im;
  t194_re = t7 * t32;
  t82_re = t194_re * t54.re;
  t82_im = t194_re * t54.im;
  t83_re_tmp = t8 * t32;
  t83_re = t83_re_tmp * t54.re;
  t83_im = t83_re_tmp * t54.im;
  t84_re = t50 * t54.re;
  t84_im = t50 * t54.im;
  t85_re_tmp = t7 * t33;
  t85_re = t85_re_tmp * t54.re;
  t85_im = t85_re_tmp * t54.im;
  t86_re_tmp = t8 * t33;
  t86_re = t86_re_tmp * t54.re;
  t86_im = t86_re_tmp * t54.im;
  t4 = t167_re * t27;
  t2 = t4 * t28;
  t91_re = t2 * t54.re;
  t91_im = t2 * t54.im;
  t92_re = t28 * t69_re;
  t92_im = t28 * t69_im;
  out3[0].re = t6;
  out3[0].im = 0.0;
  out3[1].re = 0.0;
  out3[1].im = 0.0;
  out3[2].re = 0.0;
  out3[2].im = 0.0;
  out3[3].re = 0.0;
  out3[3].im = 0.0;
  out3[4].re = 0.0;
  out3[4].im = 0.0;
  out3[5].re = 0.0;
  out3[5].im = 0.0;
  out3[6].re = 0.0;
  out3[6].im = 0.0;
  out3[7].re = t6;
  out3[7].im = 0.0;
  out3[8].re = 0.0;
  out3[8].im = 0.0;
  out3[9].re = 0.0;
  out3[9].im = 0.0;
  out3[10].re = 0.0;
  out3[10].im = 0.0;
  out3[11].re = 0.0;
  out3[11].im = 0.0;
  out3[12].re = 0.0;
  out3[12].im = 0.0;
  out3[13].re = 0.0;
  out3[13].im = 0.0;
  out3[14].re = t6;
  out3[14].im = 0.0;
  out3[15].re = 0.0;
  out3[15].im = 0.0;
  out3[16].re = 0.0;
  out3[16].im = 0.0;
  out3[17].re = 0.0;
  out3[17].im = 0.0;
  out3[18].re = t39 - t91_re;
  out3[18].im = 0.0 - t91_im;
  t3 = t167_re * t34;
  out3[19].re = -t57_re + t3 * t54.re;
  out3[19].im = -t57_im + t3 * t54.im;
  out3[20].re = t4 * -2.0;
  out3[20].im = 0.0;
  t3 = t27 * t40;
  out3[21].re = t56_re + t3 * t54.re;
  out3[21].im = t56_im + t3 * t54.im;
  t3 = t27 * t41;
  out3[22].re = -t42 + t3 * t54.re;
  out3[22].im = t3 * t54.im;
  t3 = t27 * t42;
  out3[23].re = t41 + t3 * t54.re;
  out3[23].im = t3 * t54.im;
  out3[24].re = t43 - t92_re;
  out3[24].im = 0.0 - t92_im;
  t3 = t17 * t34;
  out3[25].re = -t58_re + t3 * t54.re;
  out3[25].im = -t58_im + t3 * t54.im;
  out3[26].re = t69_re_tmp * -2.0;
  out3[26].im = 0.0;
  out3[27].re = t53.re + t27 * t78_re;
  out3[27].im = t53.im + t27 * t78_im;
  out3[28].re = -t50 + t27 * t81_re;
  out3[28].im = t27 * t81_im;
  out3[29].re = t49 + t27 * t84_re;
  out3[29].im = t27 * t84_im;
  t3 = t167_re * -t36;
  out3[30].re = t57_re + t3 * t54.re;
  out3[30].im = t57_im + t3 * t54.im;
  out3[31].re = t39 + t91_re;
  out3[31].im = t91_im;
  t3 = t167_re * t28;
  out3[32].re = t3 * -2.0;
  out3[32].im = 0.0;
  t2 = t28 * t40;
  out3[33].re = t42 + t2 * t54.re;
  out3[33].im = t2 * t54.im;
  t2 = t28 * t41;
  out3[34].re = t56_re + t2 * t54.re;
  out3[34].im = t56_im + t2 * t54.im;
  t2 = t28 * t42;
  out3[35].re = -t40 + t2 * t54.re;
  out3[35].im = t2 * t54.im;
  t2 = t17 * -t36;
  out3[36].re = t58_re + t2 * t54.re;
  out3[36].im = t58_im + t2 * t54.im;
  out3[37].re = t43 + t92_re;
  out3[37].im = t92_im;
  out3[38].re = t72_re_tmp * -2.0;
  out3[38].im = 0.0;
  out3[39].re = t50 + t28 * t78_re;
  out3[39].im = t28 * t78_im;
  out3[40].re = t53.re + t28 * t81_re;
  out3[40].im = t53.im + t28 * t81_im;
  out3[41].re = -t48 + t28 * t84_re;
  out3[41].im = t28 * t84_im;
  t2 = t28 * t39;
  out3[42].re = t4 - t2 * t54.re;
  out3[42].im = 0.0 - t2 * t54.im;
  t2 = t27 * t39;
  out3[43].re = t3 + t2 * t54.re;
  out3[43].im = t2 * t54.im;
  out3[44].re = 0.0;
  out3[44].im = 0.0;
  t3 = t29 * t40;
  out3[45].re = -t41 + t3 * t54.re;
  out3[45].im = t3 * t54.im;
  t3 = t29 * t41;
  out3[46].re = t40 + t3 * t54.re;
  out3[46].im = t3 * t54.im;
  t3 = t29 * t42;
  out3[47].re = t56_re + t3 * t54.re;
  out3[47].im = t56_im + t3 * t54.im;
  out3[48].re = t69_re_tmp - t28 * t75_re;
  out3[48].im = 0.0 - t28 * t75_im;
  out3[49].re = t72_re_tmp + t27 * t75_re;
  out3[49].im = t27 * t75_im;
  out3[50].re = 0.0;
  out3[50].im = 0.0;
  out3[51].re = -t49 + t29 * t78_re;
  out3[51].im = t29 * t78_im;
  out3[52].re = t48 + t29 * t81_re;
  out3[52].im = t29 * t81_im;
  out3[53].re = t53.re + t29 * t84_re;
  out3[53].im = t53.im + t29 * t84_im;
  memcpy(&out2[0], &out3[0], 54U * sizeof(creal_T));
  t5 = t27 * t28;
  t2 = t5 * t43;
  t53.re = t2 * t55.re;
  t53.im = t2 * t55.im;
  t2 = t165_im * t28 * t29;
  t91_re = t2 * t55.re;
  t91_im = t2 * t55.im;
  t2 = t71_re_tmp * t28 * t29;
  t92_re = t2 * t55.re;
  t92_im = t2 * t55.im;
  t2 = t5 * t48;
  t119_re = t2 * t55.re;
  t119_im = t2 * t55.im;
  t3 = t7 * t27;
  t9 = t3 * t28;
  t2 = t9 * t31;
  t120_re = t2 * t55.re;
  t120_im = t2 * t55.im;
  t4 = t8 * t27;
  t167_re = t4 * t28;
  t2 = t167_re * t31;
  t121_re = t2 * t55.re;
  t121_im = t2 * t55.im;
  t2 = t5 * t49;
  t122_re = t2 * t55.re;
  t122_im = t2 * t55.im;
  t39 = t27 * t29;
  t2 = t39 * t48;
  t123_re = t2 * t55.re;
  t123_im = t2 * t55.im;
  t2 = t9 * t32;
  t124_re = t2 * t55.re;
  t124_im = t2 * t55.im;
  t40 = t3 * t29;
  t2 = t40 * t31;
  t125_re = t2 * t55.re;
  t125_im = t2 * t55.im;
  t2 = t167_re * t32;
  t126_re = t2 * t55.re;
  t126_im = t2 * t55.im;
  t4 *= t29;
  t2 = t4 * t31;
  t127_re = t2 * t55.re;
  t127_im = t2 * t55.im;
  t2 = t5 * t50;
  t128_re = t2 * t55.re;
  t128_im = t2 * t55.im;
  t2 = t39 * t49;
  t129_re = t2 * t55.re;
  t129_im = t2 * t55.im;
  t41 = t28 * t29;
  t2 = t41 * t48;
  t130_re = t2 * t55.re;
  t130_im = t2 * t55.im;
  t2 = t9 * t33;
  t54.re = t2 * t55.re;
  t54.im = t2 * t55.im;
  t2 = t40 * t32;
  t56_re = t2 * t55.re;
  t56_im = t2 * t55.im;
  t5 = t7 * t28 * t29;
  t2 = t5 * t31;
  t57_re = t2 * t55.re;
  t57_im = t2 * t55.im;
  t2 = t167_re * t33;
  t134_re = t2 * t55.re;
  t134_im = t2 * t55.im;
  t2 = t4 * t32;
  t135_re = t2 * t55.re;
  t135_im = t2 * t55.im;
  t3 = t8 * t28 * t29;
  t2 = t3 * t31;
  t136_re = t2 * t55.re;
  t136_im = t2 * t55.im;
  t2 = t39 * t50;
  t137_re = t2 * t55.re;
  t137_im = t2 * t55.im;
  t2 = t41 * t49;
  t138_re = t2 * t55.re;
  t138_im = t2 * t55.im;
  t2 = t40 * t33;
  t139_re = t2 * t55.re;
  t139_im = t2 * t55.im;
  t2 = t5 * t32;
  t140_re = t2 * t55.re;
  t140_im = t2 * t55.im;
  t2 = t4 * t33;
  t141_re = t2 * t55.re;
  t141_im = t2 * t55.im;
  t2 = t3 * t32;
  t142_re = t2 * t55.re;
  t142_im = t2 * t55.im;
  t2 = t41 * t50;
  t143_re = t2 * t55.re;
  t143_im = t2 * t55.im;
  t2 = t5 * t33;
  t144_re = t2 * t55.re;
  t144_im = t2 * t55.im;
  t2 = t3 * t33;
  t145_re = t2 * t55.re;
  t145_im = t2 * t55.im;
  t158_re = t17 + t53.re;
  t158_im = t53.im;
  t159_re = t18 + t91_re;
  t159_im = t91_im;
  t160_re = t19 + t92_re;
  t160_im = t92_im;
  t161_re = t14 + t54.re;
  t161_im = t54.im;
  t162_re = t14 + t56_re;
  t162_im = t56_im;
  t163_re = t14 + t57_re;
  t163_im = t57_im;
  t2 = t18 * t35;
  t170_re = t70_re * 3.0 + t2 * t55.re;
  t170_im = t70_im * 3.0 + t2 * t55.im;
  t2 = t18 * t37;
  t171_re = t73_re * 3.0 + t2 * t55.re;
  t171_im = t73_im * 3.0 + t2 * t55.im;
  t2 = t69_re_tmp * t36;
  t172_re = t69_re + t2 * t55.re;
  t172_im = t69_im + t2 * t55.im;
  t2 = t165_im * t36;
  t173_re = t70_re + t2 * t55.re;
  t173_im = t70_im + t2 * t55.im;
  t2 = t71_re_tmp * t36;
  t174_re = t71_re + t2 * t55.re;
  t174_im = t71_im + t2 * t55.im;
  t2 = t72_re_tmp * t34;
  t175_re = t72_re + t2 * t55.re;
  t175_im = t72_im + t2 * t55.im;
  t2 = t165_im * t38;
  t176_re = t70_re + t2 * t55.re;
  t176_im = t70_im + t2 * t55.im;
  t2 = t166_re * t34;
  t177_re = t73_re + t2 * t55.re;
  t177_im = t73_im + t2 * t55.im;
  t2 = t74_re_tmp * t34;
  t178_re = t74_re + t2 * t55.re;
  t178_im = t74_im + t2 * t55.im;
  t2 = t34 * t43;
  t179_re = t75_re + t2 * t55.re;
  t179_im = t75_im + t2 * t55.im;
  t2 = t166_re * t38;
  t180_re = t73_re + t2 * t55.re;
  t180_im = t73_im + t2 * t55.im;
  t2 = t166_im * t34;
  t181_re = t76_re + t2 * t55.re;
  t181_im = t76_im + t2 * t55.im;
  t2 = t36 * t43;
  t182_re = t75_re + t2 * t55.re;
  t182_im = t75_im + t2 * t55.im;
  t2 = t168_re * t34;
  t183_re = t77_re + t2 * t55.re;
  t183_im = t77_im + t2 * t55.im;
  t2 = t166_im * t36;
  t184_re = t76_re + t2 * t55.re;
  t184_im = t76_im + t2 * t55.im;
  t2 = t168_re * t36;
  t185_re = t77_re + t2 * t55.re;
  t185_im = t77_im + t2 * t55.im;
  t2 = t192_im * t34;
  t186_re = t79_re + t2 * t55.re;
  t186_im = t79_im + t2 * t55.im;
  t2 = t192_im * t36;
  t187_re = t79_re + t2 * t55.re;
  t187_im = t79_im + t2 * t55.im;
  t2 = t192_im * t38;
  t188_re = t79_re + t2 * t55.re;
  t188_im = t79_im + t2 * t55.im;
  t2 = t194_re * t34;
  t189_re = t82_re + t2 * t55.re;
  t189_im = t82_im + t2 * t55.im;
  t2 = t194_re * t36;
  t190_re = t82_re + t2 * t55.re;
  t190_im = t82_im + t2 * t55.im;
  t2 = t194_re * t38;
  t191_re = t82_re + t2 * t55.re;
  t191_im = t82_im + t2 * t55.im;
  t2 = t85_re_tmp * t34;
  t192_re = t85_re + t2 * t55.re;
  t192_im = t85_im + t2 * t55.im;
  t2 = t85_re_tmp * t36;
  t193_re = t85_re + t2 * t55.re;
  t193_im = t85_im + t2 * t55.im;
  t2 = t85_re_tmp * t38;
  t194_re = t85_re + t2 * t55.re;
  t40 = t85_im + t2 * t55.im;
  t41 = t61_re + t124_re;
  t42 = t61_im + t124_im;
  t3 = t64_re + t120_re;
  t4 = t64_im + t120_im;
  t6 = t61_re + t139_re;
  t27 = t61_im + t139_im;
  t5 = t67_re + t125_re;
  t9 = t67_im + t125_im;
  t7 = t64_re + t144_re;
  t8 = t64_im + t144_im;
  t28 = t67_re + t140_re;
  t29 = t67_im + t140_im;
  t31 = t17 + -t53.re;
  t32 = -t53.im;
  t33 = t18 + -t91_re;
  t165_im = -t91_im;
  t166_re = t19 + -t92_re;
  t166_im = -t92_im;
  t167_re = t14 + -t54.re;
  t39 = -t54.im;
  t168_re = t14 + -t56_re;
  t43 = -t56_im;
  t58_re = t14 + -t57_re;
  t58_im = -t57_im;
  t70_re = in2[14] * t172_re;
  t70_im = in2[14] * t172_im;
  t73_re = in2[12] * t175_re;
  t73_im = in2[12] * t175_im;
  t75_re = in2[14] * t173_re;
  t75_im = in2[14] * t173_im;
  t76_re = in2[15] * t173_re;
  t76_im = in2[15] * t173_im;
  t77_re = in2[12] * t177_re;
  t77_im = in2[12] * t177_im;
  t79_re = in2[13] * t177_re;
  t79_im = in2[13] * t177_im;
  t82_re = in2[15] * t174_re;
  t82_im = in2[15] * t174_im;
  t85_re = in2[13] * t178_re;
  t85_im = in2[13] * t178_im;
  t57_re = t61_re + -t124_re;
  t57_im = t61_im + -t124_im;
  t56_re = t64_re + -t120_re;
  t56_im = t64_im + -t120_im;
  t54.re = t61_re + -t139_re;
  t54.im = t61_im + -t139_im;
  t92_re = t67_re + -t125_re;
  t92_im = t67_im + -t125_im;
  t91_re = t64_re + -t144_re;
  t91_im = t64_im + -t144_im;
  t53.re = t67_re + -t140_re;
  t53.im = t67_im + -t140_im;
  memset(&out3[0], 0, 18U * sizeof(creal_T));
  out3[18].re = ((((-t70_re - t73_re) - t76_re) - t79_re) + t31 * in2[16]) +
                t33 * in2[17];
  out3[18].im = ((((-t70_im - t73_im) - t76_im) - t79_im) + t32 * in2[16]) +
                t165_im * in2[17];
  t2 = t17 * t35;
  out3[19].re =
      ((((t170_re * in2[13] + t175_re * in2[14]) + t177_re * in2[15]) +
        t179_re * in2[16]) +
       t181_re * in2[17]) +
      in2[12] * (t69_re * 3.0 + t2 * t55.re);
  out3[19].im =
      ((((t170_im * in2[13] + t175_im * in2[14]) + t177_im * in2[15]) +
        t179_im * in2[16]) +
       t181_im * in2[17]) +
      in2[12] * (t69_im * 3.0 + t2 * t55.im);
  out3[20].re = t17 * in2[12] * -2.0 - t18 * in2[13] * 2.0;
  out3[20].im = 0.0;
  t2 = t34 * t48;
  out3[21].re =
      ((((in2[14] * (t63_re + t119_re) + in2[16] * (t66_re + t123_re)) +
         t186_re * in2[13]) +
        t3 * in2[15]) +
       t5 * in2[17]) +
      in2[12] * (t78_re + t2 * t55.re);
  out3[21].im =
      ((((in2[14] * (t63_im + t119_im) + in2[16] * (t66_im + t123_im)) +
         t186_im * in2[13]) +
        t4 * in2[15]) +
       t9 * in2[17]) +
      in2[12] * (t78_im + t2 * t55.im);
  t2 = t34 * t49;
  out3[22].re =
      ((((in2[16] * (t13 + t129_re) + t162_re * in2[17]) + t189_re * in2[13]) -
        t57_re * in2[15]) +
       in2[12] * (t81_re + t2 * t55.re)) -
      in2[14] * (t60_re - t122_re);
  out3[22].im =
      ((((in2[16] * t129_im + t162_im * in2[17]) + t189_im * in2[13]) -
        t57_im * in2[15]) +
       in2[12] * (t81_im + t2 * t55.im)) -
      in2[14] * (t60_im - t122_im);
  t2 = t34 * t50;
  out3[23].re =
      ((((-t167_re * in2[15] + t192_re * in2[13]) - t54.re * in2[17]) +
        in2[12] * (t84_re + t2 * t55.re)) -
       in2[14] * (t13 - t128_re)) -
      in2[16] * (t60_re - t137_re);
  out3[23].im = ((((-t39 * in2[15] + t192_im * in2[13]) - t54.im * in2[17]) +
                  in2[12] * (t84_im + t2 * t55.im)) -
                 in2[14] * (0.0 - t128_im)) -
                in2[16] * (t60_im - t137_im);
  out3[24].re = ((((-t75_re - t77_re) - t82_re) - t85_re) + t33 * in2[16]) +
                t166_re * in2[17];
  out3[24].im = ((((-t75_im - t77_im) - t82_im) - t85_im) + t165_im * in2[16]) +
                t166_im * in2[17];
  t2 = t19 * t35;
  out3[25].re =
      ((((t170_re * in2[12] + t177_re * in2[14]) + t178_re * in2[15]) +
        t181_re * in2[16]) +
       t183_re * in2[17]) +
      in2[13] * (t71_re * 3.0 + t2 * t55.re);
  out3[25].im =
      ((((t170_im * in2[12] + t177_im * in2[14]) + t178_im * in2[15]) +
        t181_im * in2[16]) +
       t183_im * in2[17]) +
      in2[13] * (t71_im * 3.0 + t2 * t55.im);
  out3[26].re = t18 * in2[12] * -2.0 - t19 * in2[13] * 2.0;
  out3[26].im = 0.0;
  t2 = t80_re_tmp * t34;
  out3[27].re =
      ((((in2[15] * (t65_re + t121_re) + in2[17] * (t68_re + t127_re)) +
         t186_re * in2[12]) +
        t3 * in2[14]) +
       t5 * in2[16]) +
      in2[13] * (t80_re + t2 * t55.re);
  out3[27].im =
      ((((in2[15] * (t65_im + t121_im) + in2[17] * (t68_im + t127_im)) +
         t186_im * in2[12]) +
        t4 * in2[14]) +
       t9 * in2[16]) +
      in2[13] * (t80_im + t2 * t55.im);
  t2 = t83_re_tmp * t34;
  out3[28].re =
      ((((in2[17] * (t15 + t135_re) + t162_re * in2[16]) + t189_re * in2[12]) -
        t57_re * in2[14]) -
       in2[15] * (t62_re - t126_re)) +
      in2[13] * (t83_re + t2 * t55.re);
  out3[28].im =
      ((((in2[17] * t135_im + t162_im * in2[16]) + t189_im * in2[12]) -
        t57_im * in2[14]) -
       in2[15] * (t62_im - t126_im)) +
      in2[13] * (t83_im + t2 * t55.im);
  t2 = t86_re_tmp * t34;
  out3[29].re =
      ((((-t167_re * in2[14] + t192_re * in2[12]) - t54.re * in2[16]) -
        in2[15] * (t15 - t134_re)) -
       in2[17] * (t62_re - t141_re)) +
      in2[13] * (t86_re + t2 * t55.re);
  out3[29].im = ((((-t39 * in2[14] + t192_im * in2[12]) - t54.im * in2[16]) -
                  in2[15] * (0.0 - t134_im)) -
                 in2[17] * (t62_im - t141_im)) +
                in2[13] * (t86_im + t2 * t55.im);
  t2 = t17 * t37;
  out3[30].re =
      ((((-t172_re * in2[12] - t171_re * in2[15]) - t173_re * in2[13]) -
        t182_re * in2[16]) -
       t184_re * in2[17]) -
      in2[14] * (t72_re * 3.0 + t2 * t55.re);
  out3[30].im =
      ((((-t172_im * in2[12] - t171_im * in2[15]) - t173_im * in2[13]) -
        t182_im * in2[16]) -
       t184_im * in2[17]) -
      in2[14] * (t72_im * 3.0 + t2 * t55.im);
  out3[31].re = ((((t70_re + t73_re) + t76_re) + t79_re) + t158_re * in2[16]) +
                t159_re * in2[17];
  out3[31].im = ((((t70_im + t73_im) + t76_im) + t79_im) + t158_im * in2[16]) +
                t159_im * in2[17];
  out3[32].re = t17 * in2[14] * -2.0 - t18 * in2[15] * 2.0;
  out3[32].im = 0.0;
  t2 = t36 * t48;
  out3[33].re = ((((-t58_re * in2[17] + t187_re * in2[15]) - t56_re * in2[13]) +
                  in2[14] * (t78_re + t2 * t55.re)) -
                 in2[16] * (t13 - t130_re)) -
                in2[12] * (t63_re - t119_re);
  out3[33].im = ((((-t58_im * in2[17] + t187_im * in2[15]) - t56_im * in2[13]) +
                  in2[14] * (t78_im + t2 * t55.im)) -
                 in2[16] * (0.0 - t130_im)) -
                in2[12] * (t63_im - t119_im);
  t2 = t36 * t49;
  out3[34].re =
      ((((in2[12] * (t60_re + t122_re) + in2[16] * (t66_re + t138_re)) +
         t190_re * in2[15]) +
        t41 * in2[13]) +
       t28 * in2[17]) +
      in2[14] * (t81_re + t2 * t55.re);
  out3[34].im =
      ((((in2[12] * (t60_im + t122_im) + in2[16] * (t66_im + t138_im)) +
         t190_im * in2[15]) +
        t42 * in2[13]) +
       t29 * in2[17]) +
      in2[14] * (t81_im + t2 * t55.im);
  t2 = t36 * t50;
  out3[35].re =
      ((((in2[12] * (t13 + t128_re) + t161_re * in2[13]) + t193_re * in2[15]) -
        t91_re * in2[17]) +
       in2[14] * (t84_re + t2 * t55.re)) -
      in2[16] * (t63_re - t143_re);
  out3[35].im =
      ((((in2[12] * t128_im + t161_im * in2[13]) + t193_im * in2[15]) -
        t91_im * in2[17]) +
       in2[14] * (t84_im + t2 * t55.im)) -
      in2[16] * (t63_im - t143_im);
  t2 = t19 * t37;
  out3[36].re =
      ((((-t171_re * in2[14] - t173_re * in2[12]) - t174_re * in2[13]) -
        t184_re * in2[16]) -
       t185_re * in2[17]) -
      in2[15] * (t74_re * 3.0 + t2 * t55.re);
  out3[36].im =
      ((((-t171_im * in2[14] - t173_im * in2[12]) - t174_im * in2[13]) -
        t184_im * in2[16]) -
       t185_im * in2[17]) -
      in2[15] * (t74_im * 3.0 + t2 * t55.im);
  out3[37].re = ((((t75_re + t77_re) + t82_re) + t85_re) + t159_re * in2[16]) +
                t160_re * in2[17];
  out3[37].im = ((((t75_im + t77_im) + t82_im) + t85_im) + t159_im * in2[16]) +
                t160_im * in2[17];
  out3[38].re = t18 * in2[14] * -2.0 - t19 * in2[15] * 2.0;
  out3[38].im = 0.0;
  t2 = t80_re_tmp * t36;
  out3[39].re = ((((-t58_re * in2[16] + t187_re * in2[14]) - t56_re * in2[12]) -
                  in2[17] * (t15 - t136_re)) -
                 in2[13] * (t65_re - t121_re)) +
                in2[15] * (t80_re + t2 * t55.re);
  out3[39].im = ((((-t58_im * in2[16] + t187_im * in2[14]) - t56_im * in2[12]) -
                  in2[17] * (0.0 - t136_im)) -
                 in2[13] * (t65_im - t121_im)) +
                in2[15] * (t80_im + t2 * t55.im);
  t2 = t83_re_tmp * t36;
  out3[40].re =
      ((((in2[13] * (t62_re + t126_re) + in2[17] * (t68_re + t142_re)) +
         t190_re * in2[14]) +
        t41 * in2[12]) +
       t28 * in2[16]) +
      in2[15] * (t83_re + t2 * t55.re);
  out3[40].im =
      ((((in2[13] * (t62_im + t126_im) + in2[17] * (t68_im + t142_im)) +
         t190_im * in2[14]) +
        t42 * in2[12]) +
       t29 * in2[16]) +
      in2[15] * (t83_im + t2 * t55.im);
  t2 = t86_re_tmp * t36;
  out3[41].re =
      ((((in2[13] * (t15 + t134_re) + t161_re * in2[12]) + t193_re * in2[14]) -
        t91_re * in2[16]) -
       in2[17] * (t65_re - t145_re)) +
      in2[15] * (t86_re + t2 * t55.re);
  out3[41].im =
      ((((in2[13] * t134_im + t161_im * in2[12]) + t193_im * in2[14]) -
        t91_im * in2[16]) -
       in2[17] * (t65_im - t145_im)) +
      in2[15] * (t86_im + t2 * t55.im);
  t72_re_tmp *= t38;
  out3[42].re = ((((t31 * in2[12] + t33 * in2[13]) - t182_re * in2[14]) -
                  t180_re * in2[17]) -
                 t184_re * in2[15]) -
                in2[16] * (t72_re + t72_re_tmp * t55.re);
  out3[42].im = ((((t32 * in2[12] + t165_im * in2[13]) - t182_im * in2[14]) -
                  t180_im * in2[17]) -
                 t184_im * in2[15]) -
                in2[16] * (t72_im + t72_re_tmp * t55.im);
  t69_re_tmp *= t38;
  out3[43].re =
      ((((t158_re * in2[14] + t159_re * in2[15]) + t179_re * in2[12]) +
        t176_re * in2[17]) +
       t181_re * in2[13]) +
      in2[16] * (t69_re + t69_re_tmp * t55.re);
  out3[43].im =
      ((((t158_im * in2[14] + t159_im * in2[15]) + t179_im * in2[12]) +
        t176_im * in2[17]) +
       t181_im * in2[13]) +
      in2[16] * (t69_im + t69_re_tmp * t55.im);
  out3[44].re = 0.0;
  out3[44].im = 0.0;
  t2 = t38 * t48;
  out3[45].re =
      ((((in2[14] * (t13 + t130_re) + t163_re * in2[15]) + t188_re * in2[17]) -
        t92_re * in2[13]) +
       in2[16] * (t78_re + t2 * t55.re)) -
      in2[12] * (t66_re - t123_re);
  out3[45].im =
      ((((in2[14] * t130_im + t163_im * in2[15]) + t188_im * in2[17]) -
        t92_im * in2[13]) +
       in2[16] * (t78_im + t2 * t55.im)) -
      in2[12] * (t66_im - t123_im);
  t2 = t38 * t49;
  out3[46].re =
      ((((-t168_re * in2[13] + t191_re * in2[17]) - t53.re * in2[15]) +
        in2[16] * (t81_re + t2 * t55.re)) -
       in2[12] * (t13 - t129_re)) -
      in2[14] * (t66_re - t138_re);
  out3[46].im = ((((-t43 * in2[13] + t191_im * in2[17]) - t53.im * in2[15]) +
                  in2[16] * (t81_im + t2 * t55.im)) -
                 in2[12] * (0.0 - t129_im)) -
                in2[14] * (t66_im - t138_im);
  t2 = t38 * t50;
  out3[47].re =
      ((((in2[12] * (t60_re + t137_re) + in2[14] * (t63_re + t143_re)) +
         t194_re * in2[17]) +
        t6 * in2[13]) +
       t7 * in2[15]) +
      in2[16] * (t84_re + t2 * t55.re);
  out3[47].im =
      ((((in2[12] * (t60_im + t137_im) + in2[14] * (t63_im + t143_im)) +
         t40 * in2[17]) +
        t27 * in2[13]) +
       t8 * in2[15]) +
      in2[16] * (t84_im + t2 * t55.im);
  t74_re_tmp *= t38;
  out3[48].re = ((((t33 * in2[12] + t166_re * in2[13]) - t180_re * in2[16]) -
                  t184_re * in2[14]) -
                 t185_re * in2[15]) -
                in2[17] * (t74_re + t74_re_tmp * t55.re);
  out3[48].im =
      ((((t165_im * in2[12] + t166_im * in2[13]) - t180_im * in2[16]) -
        t184_im * in2[14]) -
       t185_im * in2[15]) -
      in2[17] * (t74_im + t74_re_tmp * t55.im);
  t71_re_tmp *= t38;
  out3[49].re =
      ((((t159_re * in2[14] + t160_re * in2[15]) + t176_re * in2[16]) +
        t181_re * in2[12]) +
       t183_re * in2[13]) +
      in2[17] * (t71_re + t71_re_tmp * t55.re);
  out3[49].im =
      ((((t159_im * in2[14] + t160_im * in2[15]) + t176_im * in2[16]) +
        t181_im * in2[12]) +
       t183_im * in2[13]) +
      in2[17] * (t71_im + t71_re_tmp * t55.im);
  out3[50].re = 0.0;
  out3[50].im = 0.0;
  t80_re_tmp *= t38;
  out3[51].re =
      ((((in2[15] * (t15 + t136_re) + t163_re * in2[14]) + t188_re * in2[16]) -
        t92_re * in2[12]) -
       in2[13] * (t68_re - t127_re)) +
      in2[17] * (t80_re + t80_re_tmp * t55.re);
  out3[51].im =
      ((((in2[15] * t136_im + t163_im * in2[14]) + t188_im * in2[16]) -
        t92_im * in2[12]) -
       in2[13] * (t68_im - t127_im)) +
      in2[17] * (t80_im + t80_re_tmp * t55.im);
  t83_re_tmp *= t38;
  out3[52].re =
      ((((-t168_re * in2[12] + t191_re * in2[16]) - t53.re * in2[14]) -
        in2[13] * (t15 - t135_re)) -
       in2[15] * (t68_re - t142_re)) +
      in2[17] * (t83_re + t83_re_tmp * t55.re);
  out3[52].im = ((((-t43 * in2[12] + t191_im * in2[16]) - t53.im * in2[14]) -
                  in2[13] * (0.0 - t135_im)) -
                 in2[15] * (t68_im - t142_im)) +
                in2[17] * (t83_im + t83_re_tmp * t55.im);
  t86_re_tmp *= t38;
  out3[53].re =
      ((((in2[13] * (t62_re + t141_re) + in2[15] * (t65_re + t145_re)) +
         t194_re * in2[16]) +
        t6 * in2[12]) +
       t7 * in2[14]) +
      in2[17] * (t86_re + t86_re_tmp * t55.re);
  out3[53].im =
      ((((in2[13] * (t62_im + t141_im) + in2[15] * (t65_im + t145_im)) +
         t40 * in2[16]) +
        t27 * in2[12]) +
       t8 * in2[14]) +
      in2[17] * (t86_im + t86_re_tmp * t55.im);
  out4[0] = in1[12];
  out4[1] = in1[13];
  out4[2] = in1[14];
  out4[3] = 0.0;
  out4[4] = 0.0;
  out4[5] = 0.0;
}

/* End of code generation (massF2.c) */