/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * EOM_input_types.h
 *
 * Code generation for function 'EOM_input'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_struct1_T
#define typedef_struct1_T
typedef struct {
  real_T exp_case;
  real_T n_SRA;
  real_T i;
  real_T tip_pos[4436];
  real_T tip_RQ[5545];
  real_T p[4436];
  real_T f_ex[7763];
  real_T n_l;
} struct1_T;
#endif /* typedef_struct1_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  struct1_T user_pars;
  real_T var[34];
  real_T t_equil_i;
} struct0_T;
#endif /* typedef_struct0_T */

/* End of code generation (EOM_input_types.h) */
