function [out1,out2,out3,out4,out5,out6,out7] = sprdmpF7(in1,in2,s,ds,t_sym)
%sprdmpF7
%    [OUT1,OUT2,OUT3,OUT4,OUT5,OUT6,OUT7] = sprdmpF7(IN1,IN2,S,DS,T_SYM)

%    This function was generated by the Symbolic Math Toolbox version 9.1.
%    24-Nov-2022 02:51:25

E_s_ = in1(:,2);
gamma_ = in1(:,21);
l_s_ = in1(:,5);
lambda_ = in1(:,34);
mu_x_ = in1(:,6);
q7 = in2(7,:);
r_p1_ = in1(:,19);
r_s1_ = in1(:,3);
r_s2_ = in1(:,4);
u7 = in2(31,:);
out1 = [0.0;0.0;0.0;0.0;0.0;0.0;1.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0;0.0];
if nargout > 1
    t2 = 1.0./lambda_;
    out2 = (E_s_.*q7.*t2.*pi.*(t2.*(r_s1_.^2-r_s2_.^2)-r_p1_.^2.*1.0./sin(gamma_).^2.*(1.0./t2.^2.*cos(gamma_).^2-1.0).*6.0).*(4.0./3.0))./l_s_;
end
if nargout > 2
    out3 = -mu_x_.*u7;
end
if nargout > 3
    out4 = 0.0;
end
if nargout > 4
    out5 = zeros(0,0);
end
if nargout > 5
    out6 = 1.0;
end
if nargout > 6
    out7 = q7;
end
