function out1 = fj_vdF(in1,in2,s,ds,t_sym)
%fj_vdF
%    OUT1 = fj_vdF(IN1,IN2,S,DS,T_SYM)

%    This function was generated by the Symbolic Math Toolbox version 9.1.
%    24-Nov-2022 02:52:09

mu_x_ = in1(:,6);
mu_y_ = in1(:,7);
mu_z_ = in1(:,8);
mu_xx_ = in1(:,9);
mu_yy_ = in1(:,10);
mu_zz_ = in1(:,11);
u1 = in2(25,:);
u2 = in2(26,:);
u3 = in2(27,:);
u4 = in2(28,:);
u5 = in2(29,:);
u6 = in2(30,:);
u7 = in2(31,:);
u8 = in2(32,:);
u9 = in2(33,:);
u10 = in2(34,:);
u11 = in2(35,:);
u12 = in2(36,:);
u13 = in2(37,:);
u14 = in2(38,:);
u15 = in2(39,:);
u16 = in2(40,:);
u17 = in2(41,:);
u18 = in2(42,:);
u19 = in2(43,:);
u20 = in2(44,:);
u21 = in2(45,:);
u22 = in2(46,:);
u23 = in2(47,:);
u24 = in2(48,:);
out1 = [-mu_x_.*u1;-mu_y_.*u2;-mu_z_.*u3;-mu_xx_.*u4;-mu_yy_.*u5;-mu_zz_.*u6;-mu_x_.*u7;-mu_y_.*u8;-mu_z_.*u9;-mu_xx_.*u10;-mu_yy_.*u11;-mu_zz_.*u12;-mu_x_.*u13;-mu_y_.*u14;-mu_z_.*u15;-mu_xx_.*u16;-mu_yy_.*u17;-mu_zz_.*u18;-mu_x_.*u19;-mu_y_.*u20;-mu_z_.*u21;-mu_xx_.*u22;-mu_yy_.*u23;-mu_zz_.*u24];
