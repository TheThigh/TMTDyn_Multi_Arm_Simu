% 2023.01.30
% This subscript is just for test the anim.m function with cell input, we
% can delete this file at any time after the main function has been
% completed.

clear all;
clc;
close all;
addpath('results');
load('fresults.mat');
addpath('./tmtdyn');
addpath('./eom');
z=cell(user_pars.n_SRA,1);
par=cell(user_pars.n_SRA,1);
for i=1:fresults{1,1}.par.user_pars.n_SRA
    z{i,1}=fresults{i,1}.z;
    par{i,1}=fresults{i,1}.par;
end
t=fresults{1,1}.t;
for i=1:fresults{1,1}.par.user_pars.n_SRA
    par{i,1}.anim=1;
    par{i,1}.anim_frame=1;
    par{i,1}.anim_line=1;
    par{i,1}.movie=1;
end

date=datestr(now);
date=replace(date,'-','_');
date=replace(date,':','_');
date=replace(date,' ','_');
par{1,1}.vid=VideoWriter(['results/',num2str(par{1,1}.user_pars.n_SRA),'_Arm_Simu_',date,'.avi']);
v=par{1,1}.vid;
open(v);

[ r_anim , rjtip , rks , Qjtip , Qks , par ] = anim( t , z , par );
for i=1:fresults{1,1}.par.user_pars.n_SRA
    t_equil{i,1}=fresults{i,1}.t_equil;
    z_equil{i,1}=fresults{i,1}.z_equil;
    rjtip{i,1}=fresults{i,1}.rjtip;
    rjtip_equil{i,1}=fresults{i,1}.rjtip_equil;
    Qjtip_all{i,1}=fresults{i,1}.Qjtip;
    Qjtip_equil_all{i,1}=fresults{i,1}.Qjtip_equil;
    Phi_modal{i,1}=fresults{i,1}.Phi_modal;
    M_modal{i,1}=fresults{i,1}.M_modal;
    K_modal{i,1}=fresults{i,1}.K_modal;
    V_modal{i,1}=fresults{i,1}.V_modal;
    omega{i,1}=fresults{i,1}.omega;
    xi{i,1}=fresults{i,1}.xi;
end

par=post_proc( t , t_equil , z , z_equil , rjtip , rjtip_equil , Qjtip_all , Qjtip_equil_all , ...
    Phi_modal , M_modal , K_modal , V_modal , omega , xi , ...
    par );
