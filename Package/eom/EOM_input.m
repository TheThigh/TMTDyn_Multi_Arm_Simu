function [tspan, nz, z0, par_mex] = EOM_input()
tspan = [ 0.1         0.01           33 ] ;
nz = 18 ;
z0 = [ 0.0011271  1.1781e-06  0.00055182  8.0217e-07  1.0645e-06   0.0012516 -0.00040661       1e-06       1e-06           0           0           0           0           0           0           0           0           0 ]' ;
temp = coder.load( 'user_pars.mat' );
par_mex.user_pars = temp.user_pars ;
par_mex.var = [ 253.51266313           2500000             0.032              0.04               0.6               0.1               0.1               0.1             1e-05             1e-05             1e-05                 1                 0                 0              9.81           0.01347            0.0145            0.0075            0.0085            0.0085      1.5517484198                 0                 0                 0                 0                 0                 0                 0                 0                 0                 0                 0                 0                 1 ] ;
par_mex.t_equil_i = [ 55 ] ;