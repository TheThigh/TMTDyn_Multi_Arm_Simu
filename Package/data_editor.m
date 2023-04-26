function [tip_pos , tip_RQ ,p, f_ex, t_exp , t_exp_equil ] = data_editor( var_vals , user_pars)
fprintf( 'exp. data... \n' );

l_s = var_vals(5) ;
l_f = var_vals(17) ;

% 2022.12.06 %
% This lines of code is to erase the origianl experimental data, we do not
% have to display it every time, since the simulation environment will not
% be exactly the same in the paper published by the author, who is also the
% author of this package.

test_mode=1; % Selection: 1: self or 0: original.

% extract
switch user_pars.exp_case(1) % exp. cases
    case 1 % simple actuation
        % time	Pres0	Pres1	Pres2	X_val	Y_val	Z_val	Q0_val 	Qx_val	Qy_val	Qz_val	X1_val	Y1_val	Z1_val	Q01_val Qx1_val	Qy1_val	Qz1_val
       %%   1          2          3          4         5         6        7        8              9            10           11           12          13            14           15           16           17           18
        load ('exp/NoLoad.mat' ) ;
       
        % 2022.11.29
        % The pressure input for all three chambers are set to be zero.
%         NoLoad(1:end,2:4)=0;
        % Test End
%         NoLoad(1:end,2:4)=2*NoLoad(1:end,2:4);

        p = NoLoad(1:end,1) ; p(:,2:4) = 1e5 * smoothV( NoLoad(1:end,2:4) - NoLoad(1,2:4) ) ;
        f_ex= NoLoad(1:end,1) ; f_ex(:,2:7) = 0 ;
        tip_pos = NoLoad(1:end,1) ; tip_pos(:,2:4) = 1e-3 * smoothV( NoLoad(1:end,12:14) - NoLoad(1:end,5:7) , 1 ) ;
        tip_RQ = NoLoad(1:end,1) ; tip_RQ(:,2:5) = smoothV( NoLoad(1:end,15:18) , 1 ) ;
        t_exp = [ 7 13.45 20 24.5 29.4 33.4 37.5 42.9 49.2 54 ] ; % exp steps
        t_exp_equil = t_exp(1:end-1) + 1.7 ; % exp steps
        


    case 2  % Actuation and Ext. force 1

        %   Fx_in   Fy_in   Fz_in   Mx_in   My_in   Mz_in   Time    Pres1   Pres2   Pres3
        %%  1           2           3           4           5           6           7           8           9           10
        %   X_val   Y_val   Z_val   Q0_val  Qx_val  Qy_val  Qz_val  X1_val  Y1_val  Z1_val  Q01_val Qx1_val Qy1_val Qz1_val
        %%  11          12      13          14          15          16          17          18          19      20          21          22              23          24
        %   Fx_ex   Fy_ex   Fz_ex   Mx_ex   My_ex   Mz_ex
        %%  25          26          27      28          29          30
        
        load('exp/Load1.mat' );
        atmos_p=1.013;

        % 2023.01.18
        % These two ouputs below were put forward to better control the
        % input force or pressure with respect to the total simulation
        % time.
        t_exp = [ 0.1 8.8 13.2 15 17.5 33 ] ;
        t_exp_equil = [ 8.9 15.7 18.1 26.7 30 33 36.3 42.4 44.8 52.4 55 ] ;

        %% Test Section %%

        backup_data=load('exp/Load1.mat');
        Load1(:,1:3)=0;
        Load1(:,4:6)=0;
        Load1(:,8:10)=0;
        Load1(:,28:30)=0;
        Load1(:,25:27)=0;
        n_test=floor((t_exp(end)-t_exp(1))/((Load1(end,7)-Load1(1,7))/length(Load1(:,7))));
        l_section=floor(n_test/4);

        % Test Input %
        if test_mode==0
            test_switch.force=0; % 1=on, 0=off
            test_switch.pressure=0;
%             Load1(:,8:10)=-10*backup_data.Load1(:,8:10);
        elseif test_mode==1

            test_switch.force=1; % 1=on, 0=off

            if test_switch.force==1
                test_switch.pressure=0;
            elseif test_switch.force==0
                test_switch.pressure=1;
            end
        end

        %% %% %% %% %% %%
        force_test=3; % Unit: N
        pressure_test=4.5; % Unit: bar/10e5 Pa, absolute pressure
        %% %% %% %% %% %%
        
        if test_switch.force==1&&test_switch.pressure==0
            %% Force exerted on the SRA tip test for different axis directions %%
            
            test_axis='x'; % This parameter could be 'x', 'y' or 'z'.
            
            for i=1:l_section
                if test_axis=='x'
                    Load1(i,25)=Load1(i,25)+force_test/l_section*(i-1); % x
                elseif test_axis=='y'
                    Load1(i,26)=Load1(i,25)+force_test/l_section*(i-1); % y
                elseif test_axis=='z'
                    Load1(i,27)=Load1(i,25)+force_test/l_section*(i-1); % z
                end
            end

            for i=2*l_section+1:3*l_section
                if test_axis=='x'
                    Load1(i,25)=-Load1(i-2*l_section,25); %x
                elseif test_axis=='y'
                    Load1(i,26)=-Load1(i-2*l_section,26); % y
                elseif test_axis=='z'
                    Load1(i,27)=-Load1(i-2*l_section,27); % z
                end
            end
            
% 2023.03.19
for i=1:l_section
    Load1(i,27)=Load1(i,25)+20/l_section*(i-1);
end
for i=2*l_section+1:3*l_section
    Load1(i,27)=-Load1(i-2*l_section,27);
end

            %% Test End %%
            
            %% Acutuator pressure input test for different chambers %%
        elseif test_switch.force==0&&test_switch.pressure==1
            
            test_chamber=1; % This parameter could be 1, 2 and 3
            
            if test_chamber==1
                Load1(:,8)=atmos_p;
                % Important: the initial pressure inside each chamber should be
                % set as 1 bar which is equal to the atmosphere pressure.
                for i=1:l_section
                    Load1(i,8)=Load1(i,8)+pressure_test/l_section*(i-1); % Chamber 1
                end
            elseif test_chamber==2
                Load1(:,9)=atmos_p;
                for i=1:l_section
                    Load1(i,9)=Load1(i,9)+pressure_test/l_section*(i-1); % Chamber 2
                end
            elseif test_chamber==3
                Load1(:,10)=atmos_p;
                for i=1:l_section
                    Load1(i,10)=Load1(i,10)+pressure_test/l_section*(i-1); % Chamber 3
                end
            end
            for i=(2*l_section+1):(3*l_section)
                if test_chamber==1
                    Load1(i,8)=-Load1(i-2*l_section,8); % Chamber 1
                elseif test_chamber==2
                    Load1(i,9)=-Load1(i-2*l_section,9); % Chamber 2
                elseif test_chamber==3
                    Load1(i,10)=-Load1(i-2*l_section,10); % Chamber 3
                end
            end
        end

        % 2023.03.06
        % Test for pressurizing multiple chambers
%         Load1(:,8)=Load1(:,10)/2;

        %% Test End %%
        
        % 2023.01.18
        % Since there are some offset between the desired input and the exact input
        % pressure, we are going to use the direct data input method rather than
        % the smooth function.
        % - - - It turned out to be failed, it's even worse. p=Load1(:,7); must be
        % kept.
        
        p = Load1(:,7) ;
        abs_p=zeros(length(Load1(:,7)),3);
        for i=1:length(Load1(:,7))
            if Load1(i,8)<0
                abs_p(i,1)=Load1(i,8)+Load1(1,8);
            elseif Load1(i,8)>0
                abs_p(i,1)=Load1(i,8)-Load1(1,8);
            end
            if Load1(i,9)<0
                abs_p(i,2)=Load1(i,9)+Load1(1,9);
            elseif Load1(i,9)>0
                abs_p(i,2)=Load1(i,9)-Load1(1,9);
            end
            if Load1(i,10)<0
                abs_p(i,3)=Load1(i,10)+Load1(1,10);
            elseif Load1(i,10)>0
                abs_p(i,3)=Load1(i,10)-Load1(1,10);
            end
        end

        intm(1).p=1e5*smoothV(abs_p(:,1:3));
        intm(2).p=-intm(1).p; % temporarily we can write the input like this to guarantee the code could run without error.
        p(:,2:4)=intm(user_pars.i).p;

        f_ex= Load1(:,7) ; % time
        intm(1).f_ex(:,1:3) = smoothV( Load1(:,25:27) - Load1(1,25:27) ) ; % force input
        intm(1).f_ex(:,4:6) = smoothV( Load1(:,28:30) - Load1(1,28:30) ) ; % torque input
        intm(2).f_ex=-intm(1).f_ex;
        f_ex(:,2:7)=intm(user_pars.i).f_ex;

        tip_pos = Load1(:,7) ; tip_pos(:,2:4) = 1e-3 * smoothV( Load1(:,18:20) - Load1(:,11:13) ) ;
        tip_RQ = Load1(:,7) ; tip_RQ(:,2:5) = smoothV( Load1(:,21:24) ) ;



    case 3 % actuation and ext. force 2 (Wrong)
        % time	Pres0	Pres1	Pres2	X_val	Y_val	Z_val	Q0_val 	Qx_val	Qy_val	Qz_val	X1_val	Y1_val	Z1_val	Q01_val Qx1_val	Qy1_val	Qz1_val	Fx	Fy	Fz	Mx	My	Mz
   %%    1         2          3         4         5          6         7           8             9              10          11          12             13         14         15              16          17          18        19   20  21  22    23   24
        load ('exp/Load2.mat' ) ;
        p= Load2(:,7) ; p(:,2:4) = 1e5 * smoothV( Load2(:,8:10) - Load2(1,8:10) ) ;
        f_ex= Load2(:,7) ; f_ex(:,2:4) = smoothV( Load2(:,25:27) - Load2(1,25:27) ) ; f_ex(:,5:7) = smoothV( Load2(:,28:30) - Load2(1,28:30) ) ;
        tip_pos = Load2(:,7) ; tip_pos(:,2:4) = 1e-3 * smoothV( Load2(:,18:20) - Load2(:,11:13) ) ;
        tip_RQ = Load2(:,7) ; tip_RQ(:,2:5) = smoothV( Load2(:,21:24) ) ;
        t_exp = [ 5 7.8 9.7 ] ;
        t_exp_equil = [ 7.6 9.7 17.3 19.6 30 32.9 39 ] ;
end
% p(:,2:4) = 5 / 4 * ( p(:,2:4) - 0 * p(1,2:4) ) ; % comment for considering atmospheric pressure

% conditioning
% r_fo = [ 15-0.486 -0.657 157.20-12 ] * 1e-3 ;
r_fo = 1*[ 15-0.486 0 0*23 ] * 1e-3 ; % sensor offset in corrected local frame
phi_b = 0 * pi / 180 ; Q_b = [ cos( phi_b / 2 ) sin( phi_b / 2 )*[ 0 0 1 ] ] ; % base polar offset
tip_RQ0 = Q_conj( tip_RQ(1,2:end) ) ;
tip_pos0 = tip_pos(1,2:4) ;
for i = 1 : numel( tip_RQ(:,1) )
%     tip_RQ(i,2:end) = Q_mult( tip_RQ0 , tip_RQ(i,2:end) ) ; % corrected local frame after cancelling sensor intial rotation
    tip_RQ(i,2:end) = Q_mult( tip_RQ(i,2:end) , tip_RQ0 ) ; % corrected local frame after cancelling sensor intial rotation
    tip_pos(i,2:4) = tip_pos(i,2:4) - Q_rot( tip_RQ(i,2:end) , r_fo ) ; % tip sensor offset
    tip_pos(i,2:4) = tip_pos(i,2:4) - ( tip_pos0 - r_fo ) + [ 0 0 l_s+l_f ]; % init. lenght
    tip_pos(i,2:4) = Q_rot( Q_b , tip_pos(i,2:4) ) ;
    f_ex(i,2:4) = Q_rot( tip_RQ(i,2:end) , f_ex(i,2:4) ) * diag( 1 * ones(1,3) ) ;
    f_ex(i,5:7) = Q_rot( tip_RQ(i,2:end) , f_ex(i,5:7) )  * diag( 1e-3 * ones(1,3) ) ;
end



mode=1; % 0: to display the origianl experimental data; 1: not display the experimental data

if user_pars.i==user_pars.n_SRA
    % plot
    figure(1);
    if mode==0
        subplot(2,2,1) ; plot( p(:,1) , intm(1).p , 'LineWidth' , 2 ) ; title( 'p' ) ;
        subplot(2,2,2) ; plot( tip_pos(1:end,1) , tip_pos(1:end,2:4) , 'LineWidth' , 2 ) ; title( '\rho_{tip}' ) ;  % Record the tip position in the real experiment
        subplot(2,2,3) ; plot( f_ex(:,1) , intm(1).f_ex(:,2:4) , 'LineWidth' , 2 ) ; title( 'F_{tip}' ) ;
        subplot(2,2,4) ; plot( f_ex(:,1) , intm(1).f_ex(:,5:7) , 'LineWidth' , 2 ) ; title( '\tau_{tip}' ) ;
    elseif mode ==1
        for i=1:user_pars.n_SRA
            subplot(user_pars.n_SRA,3,3*(i-1)+1); plot( p(:,1) , intm(i).p , 'LineWidth' , 1 ) ;
            grid on;
            xlim([0,t_exp(end)]);
            title( ['P - Arm ',num2str(i)] ) ; xlabel('Time (s)'); ylabel('Abs. Pressure (Pa)');
            legend('Chamber 1 @ \pi/2','Chamber 2 @ -\pi/3','Chamber 3 @ 7\pi/6','location','northeast');
            subplot(user_pars.n_SRA,3,3*(i-1)+2); plot( f_ex(:,1) ,intm(i).f_ex(:,1:3) , 'LineWidth' , 1 ) ;
            grid on;
            xlim([0,t_exp(end)]);
            title( ['F_{tip} - Arm ',num2str(i)] ) ; xlabel('Time (s)'); ylabel('Force (N)');
            legend('x','y','z','location','northeast');
            subplot(user_pars.n_SRA,3,3*(i-1)+3); plot( f_ex(:,1) , intm(i).f_ex(:,4:6) , 'LineWidth' , 1 ) ;
            grid on;
            xlim([0,t_exp(end)]);
            title( ['\tau_{tip} - Arm ',num2str(i)] ) ; xlabel('Time (s)'); ylabel('Torque (N·m)');
            legend('x','y','z','location','northeast');
        end
    end
    graph_border.lower.x.input=50;
    graph_border.upper.x.input=1450;
    graph_border.lower.y.input=325-(400-325)*user_pars.n_SRA;
    graph_border.upper.y.input=325+(400-325)*user_pars.n_SRA;
    set(gcf,'position',[graph_border.lower.x.input,graph_border.lower.y.input,...
        graph_border.upper.x.input,graph_border.upper.y.input]);
end

function Qo = Q_mult( Q1 , Q2 )
% Q = [ q0 r1 r2 r3 ] ; % quaternion format
% Q1 & Q2 are cloumn vectors
Qo = [ Q1(1) -Q1(2) -Q1(3) -Q1(4) ;
       Q1(2)  Q1(1) -Q1(4)  Q1(3) ;
       Q1(3)  Q1(4)  Q1(1) -Q1(2) ;
       Q1(4) -Q1(3)  Q1(2)  Q1(1) ] * Q2' ;
Qo = Qo' ;

function r_rot = Q_rot( Q , rQ )
% rQ = [ 0 r ].' ;
r_rot = Q_mult( Q_mult( Q , [ 0 rQ ] ) , Q_conj( Q ) ) ; % 4x1 vector
r_rot = r_rot(2:end) ;

function Qo = Q_conj( Q )
Qo = [ Q(1) -Q(2:4) ] ;

function y = smoothV( x , step )
% y = x ; return
if nargin < 2
    step = 10 ;
end
[ ~ , n ] = size( x ) ;
for i = 1 : n
    y(:,i) = smooth( x(:,i) , step , 'moving' ) ;
end


