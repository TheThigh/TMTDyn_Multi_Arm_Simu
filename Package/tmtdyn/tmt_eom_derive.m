%% TMT EOM Derivator for Single Elements:
% ===========================================
% [ q , u , lambda , par ] = tmt_eom_derive( par , world , body , joint , exload , mesh )
%
% ===========================================
% Author:
% S.M.Hadi Sadati, PhD in Robotics
% Research Associate in Morphological Computation with Spiders' Web
% University of Bristol
% smh_sadati@kcl.ac.uk
% 2021
%
% ============================================

%% TMTDyn derivating function
function [ q , u , lambda , par ] = ...
    tmt_eom_derive( par , world , body , joint , exload , mesh )
fprintf( 'TMT derive... \n' )
par.elapsed_time = [ par.elapsed_time toc( par.timer ) ] ;
toc( par.timer )

%% check elements and set the default values
if ~isempty( mesh.file_name ) % assemble default mesh body and joint elements  
    [ ~ , ~ , body , joint , ~ , mesh ] = check( par , [] , body , joint , [] , mesh ) ; % check individual (not mesh) body/joint
    [ body_mesh , joint_mesh ] = mesh_import( body , joint , mesh , par ) ; % mesh import: extract the mesh body & joints
    body = [ body body_mesh ] ; % assemble all bodies including mesh bodies: first indvidual bodies
    joint = [ joint_mesh joint ] ; % assemble all joint including mesh bodies: first mesh joints
end
[ s , world , body , joint , exload , mesh , par , symbols ] = check( par , world , body , joint , exload , mesh ) ; % final check of all elements

%% Initialization
global par_simplify par_sparse
par_simplify = par.simplify ; % simplify the derivations
par_sparse = par.sparse ; % use sparse matrices

syms sw ... % unit length for logistic or piecewise function conditions (switches) to avoid issues with diff.s w.r.t. s
     ds ... % delta_s (axial length spacing) for discretized differential kinematics
     t_sym % time dependant terms are passed with t_sym as time parameter

[ ~ , n_bodies ] = size( body ) ; % extract number of bodies
[ ~ , n_extLoads ] = size( exload ) ; % extract number of ext. forces/torques
[ ~ , n_jonts ] = size( joint ) ; % extract number of joints

sym_empty = sym( [] ) ; % definition for initialization of empty sympolic values
sym_zero = sym( 0 ) ;

M = sym_empty ; % mass matrix for entire system
fgv = sym_empty ; % gravitional force vector for entire system
T = sym_empty ; % Cartesian-joint space Jacobian transformation for inertial terms for entire system
Dd = sym_empty ; % inertial nonlinear terms for entire system
Dcn = sym_empty ; % constraint nonlinear terms for entire system
Tcn = sym_empty ; % Cartesian-joint space Jacobian transformation for constraints for entire system
C_constrainT = sym_empty ; % constraint input for entire system
Tcu = sym_empty ; % Cartesian-joint space Jacobian transformation for inputs for entire system

q = sym_empty ; % system state vector for entire system
u = sym_empty ; % system state time-derivative (velocity) vector for entire system
q0 = sym_empty ; % state IC vector for entire system
lambda = sym_empty ; % lagrangian multiplier vector for entire system
dlambda = sym_empty ; % lagrangian multiplier time-derivative vector for entire system
gamma = sym_empty ; % unknown input vector for entire system
dgamma = sym_empty ; % unknown inout time-derivative vector for entire system

rho_coM = sym_empty ; % COM location vector for entire system masses
ref = sym_empty ; % externa load location vector for entire system
rcn = sym_empty ; % constraint kinematic relation for entire system

r_jtips = sym_empty ; % bodys' base and tip location/orientation for entire system [base_rho tip_rho base_Q tip_rho]:n_joints by 14
r_ks = sym_empty ; % springs' base and tip location/orientation for entire system [base_rho tip_rho base_Q tip_rho]:n_springs by 14

mass.M = sym_empty ; % mass matrix for single mass
mass.T = sym_empty ; % T matrix for single mass
mass.Dd = sym_empty ; % D matrix for single mass
mass.fg = sym_empty ; % fg matrix for single mass

sprdmp.Tt = sym_empty ; % T transpose matrix for single spring/damper element
sprdmp.kx = sym_empty ; % stiffness action vector (position and orientation) for single spring/damper element
sprdmp.vd = sym_empty ; % nonlinear viscous damping action vector (position and orientation) for single spring/damper element
sprdmp.dl = sym_empty ; % displacement value (position) for single spring/damper element
sprdmp.in = sym_empty ; % direct input vector (position and orientation) for single spring/damper element
sprdmp.k_mat = sym_empty ; % stiffness coefficient matrix (position and orientation) for linear analysis for single spring/damper element
sprdmp.vd_mat= sym_empty ;  % stiffness coefficient matrix (position and orientation) for linear analysis for single spring/damper element
sprdmp.dir = sym_empty ; % stiffness coefficient matrix (position and orientation) for linear analysis for single spring/damper element
sprdmp.Tt_u = sym_empty ; % T transpose matrix for direct inputs for single spring/damper element

cnst.rho = sym_empty ; % position vector for a constraint location
cnst.T = sym_empty ; % T matrix for a constraint
cnst.Tt = sym_empty ;  % T transpose matrix for a constraint
cnst.D = sym_empty ;  % nonlinear terms vector for a constraint
cnst.in = sym_empty ;  % direct input vector along a constraint director

loads.Tt = sym_empty ; % T transpose matrix for an external load
loads.ftau = sym_empty ; % force/torque vector of an external load
loads.Tt_o = sym_empty ; % T transpose matrix for an unknown external load

fj_k = sym_zero ; % action vector for all springs acting directly on the q states
fj_vd = sym_zero ; % action vector for all visous damping acting directly on the q states
fj_in = sym_zero ; % action vector for all inputs acting directly on the q states
fj_k_mat = sym_zero ; % stiffness coefficient matrix for linear analysis for spring element directly acting on q states
fj_sdi = sym_zero ; % vector of all actions on a single q sates: spring, damper, input
fj_vd_mat = sym_zero ;  % viscous damping coefficient matrix for linear analysis for damper element directly acting on q states
Tj_u = sym_empty ;  % T matrix for all unknown direct inputs on q states

rom.sprdmp = [] ; % [l_start l_end isDiscrete] Reduced-Order Model indicator and integration range

if par.plotIC > 0 ; figure_states = figure ; else ; figure_states = [] ; end % initialize a figure if plotting DOF ICs is needed, e.g. IC spline fit

%% Enumarators
n_sprdmps = 0 ; % number of spring/dampers
n_q_states = 0 ; % number of system states
n_constraints = 0 ; % number of constraints
n_control_inputs = 0 ; % number of control input/observer

%% Analysing the joints
fprintf( 'Deriving joint transformations for joint... \n' )

for i_joint = 1 : n_jonts % look into all joints
    
    i_joint % prints out current joint number on terminal    
    joint(i_joint).n_copies = ... % number of copies out of this joint based on the elements in the joint.first and joint.second
        max( [ numel( joint(i_joint).first(1,:) ) , numel( joint(i_joint).second(1,:) ) ] ) - 1;
    
    for i_copies = 1 : joint(i_joint).n_copies % iterate over the copies of each joint
        
        joint(i_joint).Q{i_copies}.loc = sym( [ 1 0 0 0 ].' ); % joint Quaternion 
        joint(i_joint).TQ{i_copies}.loc = sym( [ 1 0 0 0 ; 0 0 0 0 ].' ); % [Quaternion_rotation; 0 joint_translation ]'
        joint(i_joint).spring.Q{i_copies}.loc = sym( [ 1 0 0 0 ].' ); % compliance relaxed state Quaternion 
        joint(i_joint).spring.TQ{i_copies}.loc = sym( [ 1 0 0 0 ; 0 0 0 0 ].' ); % compliance relaxed state [1 joint_translation ; Quaternion_rotation ] 
        joint(i_joint).rom.delta_s{i_copies} = sym_zero; % axial (tangent) sliding of a rom beam
                     
        i_dofAxsAngl = 0 ; % dof counter in each joint copy
        [ ~ , n_joint_transfs ] = size( joint(i_joint).tr ) ; % number of transforamtions in a joint

        for i_transfs = 1 : n_joint_transfs % iterate all transfomations in a joint
            
            % initialize
            transl_rot = ... % original transl_rot as defined by the user, will not change
                sym( [ joint(i_joint).tr(i_transfs).trans , joint(i_joint).tr(i_transfs).rot ] ) ;
            transl_rot_springIC = transl_rot ; % same as above but for system relaxed state
            
            for i_axsAngl = 1 : numel( transl_rot ) % iterate all elements (axis or angle) in a transl_rot
                
                if isinf( transl_rot(i_axsAngl) ) % transformation axis is a dof
                                        
                    i_dofAxsAngl = i_dofAxsAngl + 1; % number of the joint dof + 1
                    joint(i_joint).dof(i_dofAxsAngl).qs{i_copies} = sym_empty ; % states in current dof axis/angle
                    
                    joint = ... % fit spline to the dof axis/angle
                        spline_fit( s, sw, q, q0, par, joint, i_joint, i_dofAxsAngl, i_copies, figure_states );
                    n_coeffs = numel ( joint(i_joint).dof(i_dofAxsAngl).qCs{i_copies} ) ; % number of q_state (time variant) coeff.s
                                            
                    % assign q-states
                    for i_coeffs = 1 : n_coeffs % itterate over the dof axis/angle coeff.s (q_states)

                        coeff_order = joint(i_joint).dof(i_dofAxsAngl).index_qCs{i_copies}(2,i_coeffs) ; % coeff index (order)
                        coeff_segm = joint(i_joint).dof(i_dofAxsAngl).index_qCs{i_copies}(1,i_coeffs) ; % coeff segment
                                                
                        n_sprdmps = n_sprdmps + 1 ; % update number of spring/dampers
                        n_q_states = n_q_states + 1 ; % update number od states

                        joint(i_joint).dof(i_dofAxsAngl).qs{i_copies}(i_coeffs) = sym( [ 'q' num2str( n_q_states ) ] , 'real' ) ; % states for this dof axis/angle
                        q = [ q , joint(i_joint).dof(i_dofAxsAngl).qs{i_copies}(i_coeffs) ]; % build-up q_states vector
                        q0 = [ q0 , joint(i_joint).dof(i_dofAxsAngl).init_qs{i_copies}(i_coeffs) ] ; % only all element ICs in an array
                        u = [ u , sym( [ 'u' num2str( n_q_states ) ] , 'real' ) ]; % build-up state velocity vector
                        
                        fj_k(n_q_states,1) = 0 ; % initilize actions directly acting on the states
                        fj_vd(n_q_states,1) = 0 ;
                        fj_in(n_q_states,1) = 0 ;
                        fj_k_mat(n_q_states,n_q_states) = 0 ;
                        fj_vd_mat(n_q_states,n_q_states) = 0 ;
                        
                        % form the derivation output for each spring
                        rom.sprdmp = [ rom.sprdmp; 0, 0, 0 ] ; % no integration range and continous form for this spring/damper
                        
                        sprdmp(n_sprdmps).Tt(n_q_states,1) = 1 ; % T transpose matrix           
                                                
                        if isinf( joint(i_joint).dof(i_dofAxsAngl).input(i_copies,coeff_order) ) % if input is considered part of the inverse controller
                            
                            joint(i_joint).dof(i_dofAxsAngl).input(i_copies,coeff_order) = 0 ;
                            
                            n_control_inputs = n_control_inputs + 1 ; % update number of control inputs
                            gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ; % construct unknown input vector with gamma
                            dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ; % gamma velocity
                            
                            sprdmp(n_sprdmps).Tt_u = sprdmp(n_sprdmps).Tt ; % T transpose matrix for inputs
                            Tj_u(n_q_states,n_control_inputs) = 1 ; % for unknown input to be found from inverse Jacobian controller

                        end
                        
                        if isnan( joint(i_joint).dof(i_dofAxsAngl).spring.init(i_copies,1) ) % when spring.init is used to denote the relaxed state is a copy of the joint IC
                            sprdmp(n_sprdmps).kx = 0 ;
                            sprdmp(n_sprdmps).dl = 0 ;
                        else
                            sprdmp(n_sprdmps).kx = smplfy( - joint(i_joint).dof(i_dofAxsAngl).spring.coeff(i_copies,coeff_order) * ...
                                ( q(n_q_states) - joint(i_joint).dof(i_dofAxsAngl).spring.compr(i_copies,coeff_order) * joint(i_joint).dof(i_dofAxsAngl).spring.init(i_copies,coeff_order) ) ) ; % spring compliance action
                            sprdmp(n_sprdmps).dl = smplfy( q(n_q_states) - joint(i_joint).dof(i_dofAxsAngl).spring.init(i_copies,coeff_order) ) ; % spring delta-l
                        end
                        sprdmp(n_sprdmps).vd = smplfy( - joint(i_joint).dof(i_dofAxsAngl).damp.visc(i_copies,coeff_order) ...
                            * u(n_q_states) ) ; % viscous damping
                        if joint(i_joint).dof(i_dofAxsAngl).damp.pow(i_copies,coeff_order) ~= 1 % nonlinear damping only if the damping power is not 1
                            sprdmp(n_sprdmps).vd = sprdmp(n_sprdmps).vd * abs( u(n_q_states) ).^( joint(i_joint).dof(i_dofAxsAngl).damp.pow(i_copies,coeff_order) - 1 ) ;
                        end
                        sprdmp(n_sprdmps).in = smplfy( joint(i_joint).dof(i_dofAxsAngl).input(i_copies,coeff_order) ) ; % external input
                        sprdmp(n_sprdmps).k_mat(1,n_q_states) = smplfy( joint(i_joint).dof(i_dofAxsAngl).spring.coeff(i_copies,coeff_order) ) ; % spring
                        sprdmp(n_sprdmps).vd_linear(1,n_q_states) = smplfy( - joint(i_joint).dof(i_dofAxsAngl).damp.visc(i_copies,coeff_order) ) ; % viscous
                        if joint(i_joint).dof(i_dofAxsAngl).damp.pow(i_copies,coeff_order) ~= 1
                            sprdmp(n_sprdmps).vd_linear(1,n_q_states) = sprdmp(n_sprdmps).vd_linear(1,n_q_states) * abs( u(n_q_states) ).^( joint(i_joint).dof(i_dofAxsAngl).damp.pow(i_copies,coeff_order) - 1 ) ;
                        end
                                                        
                        switch joint(i_joint).dof(i_dofAxsAngl).dir(i_copies,coeff_order)
                            case 1 % compression-only elements, e.g. soft contact
                                sprdmp(n_sprdmps).dir = smplfy( sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                            case 0 % both dir.ss, e.g. regular spring/damper
                                sprdmp(n_sprdmps).dir = 1 ;
                            case -1 % tension-only elements, e.g. wire
                                sprdmp(n_sprdmps).dir = smplfy( - sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                        end
                        
                        % better to keep this form rather than sprdmp
                        fj_k(n_q_states,1) = fj_k(n_q_states,1) ... % spring on DOFs
                            + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).kx ;
                        fj_vd(n_q_states,1) = fj_vd(n_q_states,1) ... % damper on DOFs
                            + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).vd ;
                        fj_in(n_q_states,1) = fj_in(n_q_states,1) ... % inputs on DOFs
                            + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).in ;
                        fj_sdi(n_q_states,1) = sprdmp(n_sprdmps).dir * ( sprdmp(n_sprdmps).kx + sprdmp(n_sprdmps).vd + sprdmp(n_sprdmps).in ) ; % all spring/damper/input force virtual work
                        fj_k_mat(n_q_states,n_q_states) = fj_k_mat(n_q_states,n_q_states) ... % spring on DOFs
                            + sprdmp(n_sprdmps).k_mat(1,n_q_states) ;
                        fj_vd_mat(n_q_states,n_q_states) = fj_vd_mat(n_q_states,n_q_states) ... % damper on DOFs
                            + sprdmp(n_sprdmps).vd_linear(1,n_q_states) ;
                        
                        % if direct geometrical control available
                        if joint(i_joint).dof(i_dofAxsAngl).control(i_copies,coeff_order) ~= 0
                            sprdmp(n_sprdmps).in = 0 ;
                            fj_in(n_q_states,1) = 0;
                            
                            n_constraints = n_constraints + 1 ;
                            pid = joint(i_joint).dof(i_dofAxsAngl).pid; % PID: P*u+I*q+D*a
                            pid_3 = 1; if pid.d(i_copies,coeff_order) ~= 0; pid_3 = pid.d(i_copies,coeff_order); end
                            
                            cnst(n_constraints).r = q(n_q_states) ; % constraint relation
                            cnst(n_constraints).T = pid_3 * sprdmp(n_sprdmps).Tt.' ; % use T.' in dynamics EOM and T in algebraic part
                            vcn = cnst(n_constraints).T * u.' ;
                            cnst(n_constraints).D = myJacobian( vcn , q ) ;
                            cnst(n_constraints).in = - pid.p(i_copies,coeff_order) * u(n_q_states) - pid.i(i_copies,coeff_order) * q(n_q_states) + ...
                                joint(i_joint).dof(i_dofAxsAngl).control(i_copies,coeff_order) ;
                            
                            if isinf( joint(i_joint).dof(i_dofAxsAngl).fixed(i_copies,coeff_order) ) % desired or known so no Tt
                                cnst(n_constraints).Tt = [] ;
                            else % constraint
                                cnst(n_constraints).Tt = cnst(n_constraints).T.'; % doesn't need pid
                                % lambdaf = [ lambdaf, lambda_vpa(n_cn) ] ;
                                lambda = [ lambda, sym( [ 'lambda' num2str( n_constraints ) ] , 'real' ) ] ;
                                dlambda = [ dlambda, sym( [ 'dlambda' num2str( n_constraints ) ] , 'real' ) ] ;
                            end
                            
                            if par.derive_collect == 5 % collect most terms
                                cnst(n_constraints).dc = - cnst(n_constraints).Dc * u.' + cnst(n_constraints).in;
                            end
                            
                            % sparse matrix
                            cnst(n_constraints).r = sprse( cnst(n_constraints).r ) ;
                            cnst(n_constraints).T = sprse( cnst(n_constraints).T ) ;
                            cnst(n_constraints).D = sprse( cnst(n_constraints).D ) ;
                        end
                        
                        if par.derive_collect == 5% collect most terms
                            sprdmp(n_sprdmps).w_vd_j = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                            sprdmp(n_sprdmps).w_sd = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).kx * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                            sprdmp(n_sprdmps).w_in = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).in * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                            sprdmp(n_sprdmps).Tt_u = sprdmp(n_sprdmps).Tt_u * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                        end
                        
                        % sparse matrices
                        sprdmp(n_sprdmps).Tt = sprse( sprdmp(n_sprdmps).Tt ) ;
                        sprdmp(n_sprdmps).kx = sprse( sprdmp(n_sprdmps).kx ) ;
                        sprdmp(n_sprdmps).dl = sprse( sprdmp(n_sprdmps).dl ) ;
                        sprdmp(n_sprdmps).vd = sprse( sprdmp(n_sprdmps).vd ) ;
                        sprdmp(n_sprdmps).in = sprse( sprdmp(n_sprdmps).in ) ;
                        sprdmp(n_sprdmps).k_mat = sprse( sprdmp(n_sprdmps).k_mat ) ;
                        sprdmp(n_sprdmps).vd_mat= sprse( sprdmp(n_sprdmps).vd_mat) ;
                    end
                    
                    % update spline series
                    joint(i_joint).dof(i_dofAxsAngl).series{i_copies} = subs( joint(i_joint).dof(i_dofAxsAngl).series{i_copies} , ... % substitute all C_states with q_states
                        joint(i_joint).dof(i_dofAxsAngl).qCs{i_copies} , joint(i_joint).dof(i_dofAxsAngl).qs{i_copies} ) ;
                        
                    % update current dof axis/angle with fitted spline
                    transl_rot(i_axsAngl) = joint(i_joint).dof(i_dofAxsAngl).series{i_copies} ;
                    transl_rot_springIC(i_axsAngl) = joint(i_joint).dof(i_dofAxsAngl).spring.init_series{i_copies} ;
                    
                end

            end
            
            % calculating transformation and rotation quaternions and vectors for the joint transformation
            [ Q_temp , TQ_temp ] = TQ_mat( transl_rot , [ q s ] , joint(i_joint).tr(i_transfs).type , joint(i_joint).tr(i_transfs).init_quat );
            joint(i_joint).Q{i_copies}.loc = Q_mult( joint(i_joint).Q{i_copies}.loc , Q_temp ) ;
            joint(i_joint).TQ{i_copies}.loc = TQ_mult( joint(i_joint).TQ{i_copies}.loc , TQ_temp ) ;
            
            % calculating transformation and rotation quaternions and vectors for the joint relaxed state
            [ Q_temp , TQ_temp ] = TQ_mat( transl_rot_springIC , [ q s ] , joint(i_joint).tr(i_transfs).type , joint(i_joint).tr(i_transfs).init_quat );
            joint(i_joint).spring.Q{i_copies}.loc = Q_mult( joint(i_joint).spring.Q{i_copies}.loc , Q_temp ) ;
            joint(i_joint).spring.TQ{i_copies}.loc = TQ_mult( joint(i_joint).spring.TQ{i_copies}.loc , TQ_temp ) ;
            
        end
        
        % ROM variable length: placed here for cases where dl is a function of same joint dof
        if joint(i_joint).rom.isROM % only for reduced order model

            % sliding dof is defined in the form of equality constraint w.r.t. a previously defined dof
            if joint(i_joint).rom.length(i_copies,4) ~= 0 % length: [init_length_start, init_length_end, type, coeff, i_joint, i_copies, i_axsAngl, i_coeffs, l_rom]

                temp = joint(i_joint).rom.length(i_copies,5:end) ; % [i_joint, i_copies, i_axsAngl, i_coeffs, l_rom]

                if temp(4) > 0 % i_coeffs is availavle, so the constraints point to a state
                    joint(i_joint).rom.delta_s(i_copies,1) = joint(i_joint).rom.length(i_copies,4) * ... % coeff(e.g. -+1) defining sliding direction
                        joint(temp(1)).dof(temp(3)).rom_coeff{temp(2),1}(temp(4)) ;

                else % otehrwise the constraint point to a location along the spline function
                    joint(i_joint).rom.delta_s(i_copies,1) = joint(i_joint).rom.length(i_copies,4) * ... % coeff(e.g. -+1) defining sliding direction
                        subs( joint(temp(1)).dof(temp(3)).series{temp(2)}(1,end) , [s, sw] , temp(5) * [1, 1] ) ;

                end

            end

            % update joint spatial integration range by sliding value delta_s
            if joint(i_joint).rom.length(i_copies,3) < 0 % base_growing or sliding

                joint(i_joint).Q{i_copies}.loc = subs( joint(i_joint).Q{i_copies}.loc , [s, sw] , [s, sw] + joint(i_joint).rom.delta_s(i_copies,1) ) ; % should update sw too to maintain knot loc.s
                joint(i_joint).TQ{i_copies}.loc = subs( joint(i_joint).TQ{i_copies}.loc , [s, sw] , [s, sw] + joint(i_joint).rom.delta_s(i_copies,1) ) ;
                % no need to update the integration upper bound, since s+delta_s is already applied to splines
                
                if joint(i_joint).rom.length(i_copies,3) == -1 % keep base unchanged for base_growing case
                    joint(i_joint).rom.length(i_copies,1) = joint(i_joint).rom.length(i_copies,1) - joint(i_joint).rom.delta_s(i_copies,1) ; % base_growing shuold be integrated for -q_s:original_length
                end

            else % otherwise: tip growing with no mass transfer (i.e. sliding)
                
                % update tip bound, no change for the lower bound
                joint(i_joint).rom.length(i_copies,2) = joint(i_joint).rom.length(i_copies,2) + joint(i_joint).rom.delta_s(i_copies,1) ; % tip moves with delta_s

            end            

            for ij_dof = 1 : i_dofAxsAngl % update rom series too for kin. const.s at tip

                joint(i_joint).dof(ij_dof).series{i_copies} = subs( joint(i_joint).dof(ij_dof).series{i_copies} , [s, sw] , [s, sw] + joint(i_joint).rom.delta_s(i_copies,1) ) ;
            
            end
        end
        
        % for spring/damper and constraints
        if ~isempty( joint(i_joint).tr2nd.trans )
            joint(i_joint).Q2nd{i_copies}.loc = sym( [ 1 0 0 0 ].' );
            joint(i_joint).TQ2nd{i_copies}.loc = sym( [ 1 0 0 0 ; 0 0 0 0 ].' );
            [ ~ , n_joint_transfs ] = size( joint(i_joint).tr2nd ) ; % number of transforamtions in a joint
            for i_transfs = 1 : n_joint_transfs
                [ Q_temp , TQ_temp ] = TQ_mat( [ joint(i_joint).tr2nd(i_transfs).trans joint(i_joint).tr2nd(i_transfs).rot ] , [ q s ] , joint(i_joint).tr2nd(i_transfs).type );
                joint(i_joint).Q2nd{i_copies}.loc = Q_mult( joint(i_joint).Q2nd{i_copies}.loc , Q_temp ) ;
                joint(i_joint).TQ2nd{i_copies}.loc = TQ_mult( joint(i_joint).TQ2nd{i_copies}.loc , TQ_temp ) ;
            end
        end
    end
end

% implement sparce matrices if requested
fj_k = sprse( fj_k ) ;
fj_vd = sprse( fj_vd ) ;
fj_in = sprse( fj_in ) ;
fj_sdi = sprse( fj_sdi ) ;
fj_k_mat = sprse( fj_k_mat ) ;
fj_vd_mat = sprse( fj_vd_mat ) ;
if ~isempty( Tj_u )
    [ temp , ~ ] = size( Tj_u ) ;
    if temp ~= n_q_states
        Tj_u(n_q_states,1) = 0;
    end
    Tj_u = sprse( Tj_u ) ;
end

% Adjustmentscorrecting dimensions for the generated vectors to become n_q_states
for i = 1 : numel( sprdmp ) % check all sprdmps
    if ~par.sparse && numel( sprdmp(i).Tt ) ~= n_q_states % fill all elements
        sprdmp(i).Tt(n_q_states,1) = 0 ;
        sprdmp(i).vd_linear(1,n_q_states) = 0 ;
        sprdmp(i).k_mat(1,n_q_states) = 0 ;
        if ~isempty( sprdmp(i).Tt_u )
            sprdmp(i).Tt_u(n_q_states,1) = 0 ;
        end
    end
end
for i = 1 : numel( cnst ) % check all constraints
    if ~par.sparse && numel( cnst(i).T ) ~= n_q_states % fill all elements
        cnst(i).T(1,n_q_states) = 0 ;
        cnst(i).Tt(n_q_states,1) = 0 ;
        cnst(i).D(1,n_q_states) = 0;
    end
end


if ismember( par.derive_collect , [ 3 4 ] ) % for all constraints
    for i = 1 : n_constraints
        Tcn = [ Tcn ; cnst(i).T ] ;
        Dcn = [ Dcn ; cnst(i).D ] ;
        C_constrainT = [ C_constrainT ; cnst(i).in ] ;
    end
    Tcu = Tcn.' ;
end

%% plot initial conditions and fitted splines
if par.plotIC > 0 % compare overall fit curves with init data
    figure

    for i_joint = 1 : n_jonts
        
        if joint(i_joint).rom.isROM % plot only for ROM elements

            for i_copies = 1 : joint(i_joint).n_copies
                
                s_test = subs( subs( joint(i_joint).rom.length(i_copies,1), q, q0 ), par.sym,par.var ) : 1e-3 : ...
                    subs( subs( joint(i_joint).rom.length(i_copies,2), q, q0 ), par.sym, par.var );
                pos_test = subs( subs( subs( subs( joint(i_joint).TQ{i_copies}.loc(:,2), q, q0 ), par.sym, par.var ), sw, s), s, s_test );
                pos_spring_test = subs( subs( subs( subs( joint(i_joint).spring.TQ{i_copies}.loc(:,2), q, q0 ), par.sym, par.var ), sw, s), s, s_test );
                Q_test = subs( subs( subs( subs( joint(i_joint).TQ{i_copies}.loc(:,1), q, q0 ), par.sym, par.var ), sw, s), s, s_test );
                Q_spring_test = subs( subs( subs( subs( joint(i_joint).spring.TQ{i_copies}.loc(:,1), q, q0 ), par.sym, par.var ), sw, s), s, s_test );
                
                subplot(2,2,1); plot3( pos_test(2,:), pos_test(3,:), pos_test(4,:) );
                hold on; axis equal
                subplot(2,2,1); plot3( pos_spring_test(2,:), pos_spring_test(3,:), pos_spring_test(4,:), '--' );
                hold on; axis equal; xlabel('x'); ylabel('y'); zlabel('z'); legend('IC', 'relaxed state'); title('Initial configuration')
                subplot(2,2,2); plot(s_test, Q_test(1,:), '-', s_test, Q_spring_test(1,:), '--' );
                hold on; xlabel('x'); ylabel('Q_0'); legend('Q_0'); legend('IC', 'relaxed state'); title('Initial orientation')
                
                % strains, curvatures, toraion
                temp = subs( subs( joint(i_joint).TQ{i_copies}.loc, q, q0 ), par.sym, par.var );
                dr = subs( diff( temp(:,2), s ), sw, s);
                dQ = subs( diff( temp(:,1), s ), sw, s);
                temp = subs( temp, sw, s);
                uQ = double( subs( Q_omega( temp(:,1) , dQ ), s, s_test ) ); % same as 2*Q_conj*dQ but less computation in derivation phase
                vr = double( subs( Q_rot( Q_conj( temp(:,1) ) , dr ), s, s_test ) ); % transfer to local frame in which K is defined
                temp0 = subs( subs( joint(i_joint).spring.TQ{i_copies}.loc, q, q0 ), par.sym, par.var );
                dr0 = subs( diff( temp0(:,2), s ), sw, s);
                dQ0 = subs( diff( temp0(:,1), s ), sw, s);
                temp0 = subs( temp0, sw, s);
                uQ0 = double( subs( Q_omega( temp0(:,1) , dQ0 ), s, s_test ) ); % same as 2*Q_conj*dQ but less computation in derivation phase
                vr0 = double( subs( Q_rot( Q_conj( temp0(:,1) ) , dr0 ), s, s_test ) ); % transfer to local frame in which K is defined
                
                subplot(2,2,3); plot( s_test, vr(2:4,:) , '-' , s_test, vr0(2:4,:) , '--' );
                hold on; xlabel('s'); ylabel('strains'); title('initial strains')
                legend('IC \epsilon_x', 'IC \epsilon_y', 'IC \epsilon_z','relaxed state \epsilon_x', 'relaxed state \epsilon_y', 'relaxed state \epsilon_z');
                subplot(2,2,4); plot( s_test, uQ(2:4,:) , '-' , s_test, uQ0(2:4,:) , '--' );
                hold on; xlabel('s'); ylabel('curvature & torsion'); title('initial curvatures & torsion')
                legend('\kappa_x', '\kappa_y', '\tau_z','relaxed state \kappa_x', 'relaxed state \kappa_y', 'relaxed state \tau_z');
                
            end
        
        end

    end

    %% %%%%%%      2023.01.29      %%%%%% %%
    % Sometimes it can be kind of annoying to press any key to continue
    % especially when there are multiple SRAs, so we can comment them out.
    
%     fprintf( 'Interpolation overall check! Press any key to continue... \n' );
%     pause

end

%% inertial terms
% Start with bodies and create R|TR. To do so, check R|TR for the
% previous body and if not available create R|TR for that till reaching
% ground. If the user provides a proper sequence of bodies the sequence of
% generalized coordinates numbers will rational starting frorm 1 for the
% nearest one to the ground
% SHOULD GIVE THE NEARED BODY TO GROUND FIRST
fprintf( 'Deriving inertial terms for body... \n' )
n_m = 0 ; % body type counter [ rigid , other ]
rom.mass = [] ; % reduced order model indicator
for b_count = 1 : n_bodies % number of bodies
    b_count
    
    for i_joint = 1 : n_jonts % look into all joints
        
        if joint(i_joint).second(1,1) == b_count % if the joint connects this body to another one,
            % 1st connecting joint is in the main kin. chain,
            % the rest are spring,damper, input, or constraints
            
            % continuum body integration range
            body(b_count).rom = [] ;
            body(b_count).n_copies = numel( joint(i_joint).first(1,:) ) - 1; % multiple body based on instances of main kin joint (not other joints)
            
            for i_copies = 1 : body(b_count).n_copies

                if ~joint(i_joint).rom.isROM

                    rom.mass = [ rom.mass; 0, 0 ] ;
                
                else % DON'T include int limits into system EOM so their q don't appear in diff
                    
                    body(b_count).rom.l(i_copies,:) = joint(i_joint).rom.length(i_copies,1:2) ;
                    rom.mass = [ rom.mass ; body(b_count).rom.l(i_copies,:) ] ;
                
                end
                
                % form absolute transfomation vectors
                if joint(i_joint).first(1,1) == 0 || ... % the joint number where the new frame is connected to the firstbody
                        ( joint(i_joint).first(1,i_copies+1) == 0 && isempty( body(joint(i_joint).first(1,1)).rom ) )

                    joint(i_joint).Q{i_copies}.abs = joint(i_joint).Q{i_copies}.loc ;
                    joint(i_joint).TQ{i_copies}.abs = joint(i_joint).TQ{i_copies}.loc ;

                else

                    if isempty( body(joint(i_joint).first(1,1)).rom ) % not rom

                        Q = body(joint(i_joint).first(1,1)).Q{joint(i_joint).first(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).first(1,1)).TQ{joint(i_joint).first(1,i_copies+1)}.abs ;

                    else

                        Q = body(joint(i_joint).first(1,1)).Q{joint(i_joint).first(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).first(1,1)).TQ{joint(i_joint).first(1,i_copies+1)}.abs ;

                        if isnan( joint(i_joint).first(2,i_copies+1) ) % at tip
                            joint(i_joint).first = sym( joint(i_joint).first );
                            joint(i_joint).first(2,i_copies+1) = body(joint(i_joint).first(1,1)).rom.l(joint(i_joint).first(1,i_copies+1),2);
                        end

                        Q = subs( Q , [s, sw] , joint(i_joint).first(2,i_copies+1) * [1, 1] ) ;
                        TQ = subs( TQ , [s, sw] , joint(i_joint).first(2,i_copies+1) * [1, 1] ) ;

                    end

                    joint(i_joint).Q{i_copies}.abs = Q_mult( Q , joint(i_joint).Q{i_copies}.loc ) ;
                    joint(i_joint).TQ{i_copies}.abs = TQ_mult( TQ , joint(i_joint).TQ{i_copies}.loc ) ;

                end
                
                % body local and absolute transformations
                body(b_count).Q{i_copies}.loc = joint(i_joint).Q{i_copies}.loc ;
                body(b_count).TQ{i_copies}.loc = joint(i_joint).TQ{i_copies}.loc ;
                body(b_count).Q{i_copies}.abs = joint(i_joint).Q{i_copies}.abs ;
                body(b_count).TQ{i_copies}.abs = joint(i_joint).TQ{i_copies}.abs ;
                
                joint(i_joint).rho(i_copies,:) = joint(i_joint).TQ{i_copies}.abs(2:4,2).' ;
                if ~joint(i_joint).rom.isROM % not a reduced order model
                    TQ_temp = TQ_mult( body(b_count).TQ{i_copies}.abs , [ 1 0 0 0 ; 0 body(b_count).tip(i_copies,:) ].' ) ;
                    r_jtips = [ r_jtips ; joint(i_joint).rho(i_copies,:) , TQ_temp(2:4,2).' , ... % base (joint location) and tip position
                        joint(i_joint).TQ{i_copies}.abs(1:4,1).' , TQ_temp(1:4,1).' , ...
                        body(b_count).radi(i_copies) ] ; % radius for plotting
                else
                    s1 = s * ( body(b_count).rom.l(i_copies,2) - body(b_count).rom.l(i_copies,1) ) + body(b_count).rom.l(i_copies,1) ; % normalized curve length
                    r_jtips = [ r_jtips ; subs( joint(i_joint).rho(i_copies,:) , [s, sw] , s1 * [1, 1] ) nan nan nan , ... % axial location
                        subs( joint(i_joint).TQ{i_copies}.abs(1:4,1).' , [s, sw] , s1 * [1, 1] ) nan nan nan nan , ... % axial orientation
                        body(b_count).radi(i_copies) ] ;  % radius for plotting
                end
                
                n_m = n_m + 1 ;
                im = 6 * n_m ; % 6 elements for mass and inertia matrix
                mass(n_m).M(1:3,1:3) = smplfy( sym( body(b_count).m(i_copies) * eye( 3 ) ) ) ;
                mass(n_m).M(4:6,4:6) = smplfy( sym( body(b_count).I(:,:,i_copies) ) ) ;
                
                % rotational terms in local (curvilinear) frame where I is defined
                temp = myJacobian( body(b_count).Q{i_copies}.abs , q ) ;
                % temp4 = 2 * Q_mult( Q_conj( body(b_count).Q{i_copies}.abs ) , temp ) ; % omega_loc = 2 * Q^{-1} * Q_{,t}
                temp4 = Q_omega( body(b_count).Q{i_copies}.abs , temp ) ;
                body(b_count).omega(i_copies).abs_loc = ( temp4(2:4,:) * u.' ).' ; % abs omega in local frame
                
                mass(n_m).T(4:6,:) = smplfy( temp4(2:4,:) ) ;
                if par.derive == 2 % linearize velocity higher terms
                    mass(n_m).Dd(4:6,:) = zeros( size( mass(n_m).T(4:6,:) ) ) ;
                else
                    mass(n_m).Dd(4:6,:) = smplfy( myJacobian( body(b_count).omega(i_copies).abs_loc.' , q ) ) ;
                end
                
                % translational terms in global frame since for m it does not matter the same as for I
                temp7 = TQ_mult( body(b_count).TQ{i_copies}.abs , [ 1 0 0 0 ; 0 body(b_count).l_com(i_copies,:) ].' ) ;
                body(b_count).r_com(i_copies,:) = temp7(2:4,2).';
                rho_coM = [ rho_coM ; body(b_count).r_com(i_copies,:) ] ; % COM position for output
                temp8 = myJacobian ( temp7(2:4,2) , q );
                body(b_count).v_com(i_copies,:) = ( temp8 * u.' ).';
                
                mass(n_m).T(1:3,:) = smplfy( temp8 ) ;
                if par.derive == 2 % linearize velocity higher terms
                    mass(n_m).Dd(1:3,:) = zeros( size( mass(n_m).T(1:3,:) ) ) ;
                else
                    mass(n_m).Dd(1:3,:) = smplfy( myJacobian ( body(b_count).v_com(i_copies,:).' , q ) ) ;
                end
                
                % gravity generalized work
                mass(n_m).fg = ( [ world.g 0 0 0 ].' ) ;
                
                if par.derive_collect == 5 % collect most terms
                    mass(n_m).TMT = mass(n_m).T.' * mass(n_m).M * mass(n_m).T * ( rom.mass(b_count,2) - rom.mass(b_count,1) ) ;
                    mass(n_m).TMfd = mass(n_m).T.' * mass(n_m).M * ( - mass(n_m).Dd * u.' + mass(n_m).fg ) * ( rom.mass(b_count,2) - rom.mass(b_count,1) ) ;
                end
                
                % sparse matrix
                mass(n_m).M = sprse( mass(n_m).M ) ;
                mass(n_m).T = sprse( mass(n_m).T ) ;
                mass(n_m).Dd = sprse( mass(n_m).Dd ) ;
                mass(n_m).fg = sprse( mass(n_m).fg ) ;
                
                if ismember( par.derive_collect , [ 3 4 ] ) % for all masses
                    M( im - 5 : im , im - 5 : im ) = mass(n_m).M ;
                    T ( im - 5 : im , : ) = mass(n_m).T ;
                    Dd ( im - 5 : im , 1 : n_q_states ) = mass(n_m).Dd ;
                    fgv = [ fgv , mass(n_m).fg.' ];
                end
                
            end
            break ; % other joints are spring or dampers and should have .tr2nd
        end
    end
end

%% spring/dampers/constraint
% look for the secondary joints that should be constraint or spring/dampers
fprintf( 'Deriving spring/damper/input dynamics for joints (according to which body they are connected to)... \n' )
w_sdi = sym_zero ; % total virt. work
w_k = sym_zero ; % spring virt. work
w_vd = sym_zero ; % viscous dampers virt. work
w_vd_mat = sym_zero ; % viscous dampers virt. work
w_in = sym_zero ; % Coulomb dampers virt. work
w_k_mat = sym_zero ; % spring stiffnes matrix for modal analysis
for b_count = 0 : n_bodies % number of bodies
    b_count
    
    for i_joint = 1 : n_jonts % look into all joints, first one is the main kinematic path and rest are froce and spring and constraints
        
        if joint(i_joint).second(1,1) == b_count && ~joint(i_joint).rom.isROM && ~isempty( joint(i_joint).tr2nd.trans ) % if the joint connects this body to another one and is not rom
            i_joint
            
            for i_copies = 1 : max( [ numel( joint(i_joint).first(1,:) ) , numel( joint(i_joint).second(1,:) ) ] ) - 1
                
                if joint(i_joint).first(1,1) == 0 || joint(i_joint).first(1,i_copies+1) == 0 % the joint number where the new frame is connected to

                    joint(i_joint).Q{i_copies}.abs = joint(i_joint).Q{i_copies}.loc ;
                    joint(i_joint).TQ{i_copies}.abs = joint(i_joint).TQ{i_copies}.loc ;

                else
                    
                    if isempty( body(joint(i_joint).first(1,1)).rom ) % connect to rigid body, i.e. not rom

                        Q = body(joint(i_joint).first(1,1)).Q{joint(i_joint).first(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).first(1,1)).TQ{joint(i_joint).first(1,i_copies+1)}.abs ;
                    
                    else % connect to rom body
                        
                        Q = body(joint(i_joint).first(1,1)).Q{joint(i_joint).first(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).first(1,1)).TQ{joint(i_joint).first(1,i_copies+1)}.abs ;
                        
                        if isnan( joint(i_joint).first(2,i_copies+1) ) % at tip
                        
                            joint(i_joint).first = sym( joint(i_joint).first );
                            joint(i_joint).first(2,i_copies+1) = body(joint(i_joint).first(1,1)).rom.l(joint(i_joint).first(1,i_copies+1),2);
                        
                        end
                        
                        Q = subs( Q , [s, sw] , joint(i_joint).first(2,i_copies+1) * [1, 1] ) ;
                        TQ = subs( TQ , [s, sw] , joint(i_joint).first(2,i_copies+1) * [1, 1] ) ;

                    end
                    
                    joint(i_joint).Q{i_copies}.abs = Q_mult( Q , joint(i_joint).Q{i_copies}.loc ) ;
                    joint(i_joint).TQ{i_copies}.abs = TQ_mult( TQ , joint(i_joint).TQ{i_copies}.loc ) ;
                        
                end
                joint(i_joint).rho(i_copies,:) = joint(i_joint).TQ{i_copies}.abs(2:4,2).';
                
                if joint(i_joint).second(1,1) == 0 || joint(i_joint).second(1,i_copies+1) == 0 % the joint number where the new frame is connected to the second body
                    
                    joint(i_joint).Q2nd{i_copies}.abs = joint(i_joint).Q2nd{i_copies}.loc ;
                    joint(i_joint).TQ2nd{i_copies}.abs = joint(i_joint).TQ2nd{i_copies}.loc ;
                
                else
                
                    if isempty( body(joint(i_joint).second(1,1)).rom )
                
                        Q = body(joint(i_joint).second(1,1)).Q{joint(i_joint).second(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).second(1,1)).TQ{joint(i_joint).second(1,i_copies+1)}.abs ;
                
                    else
                
                        Q = body(joint(i_joint).second(1,1)).Q{1,joint(i_joint).second(1,i_copies+1)}.abs ;
                        TQ = body(joint(i_joint).second(1,1)).TQ{1,joint(i_joint).second(1,i_copies+1)}.abs ;
                
                        if isnan( joint(i_joint).second(2,i_copies+1) ) % at tip
                            joint(i_joint).second(2,i_copies+1) = body(joint(i_joint).second(1,1)).rom.l(joint(i_joint).second(1,i_copies+1),2);
                        end
                
                        Q = subs( Q , [s, sw] , joint(i_joint).second(2,i_copies+1) * [1, 1] ) ;
                        TQ = subs( TQ , [s, sw] , joint(i_joint).second(2,i_copies+1) * [1, 1] ) ;
                
                    end
                
                    joint(i_joint).Q2nd{i_copies}.abs = Q_mult( Q , joint(i_joint).Q2nd{i_copies}.loc ) ;
                    joint(i_joint).TQ2nd{i_copies}.abs = TQ_mult( TQ , joint(i_joint).TQ2nd{i_copies}.loc ) ;
                
                end                
                
                % spring/damper/input:                
                n_sprdmps = n_sprdmps + 1 ;
                r_ks = [ r_ks ; joint(i_joint).TQ{i_copies}.abs(2:4,2).' , joint(i_joint).TQ2nd{i_copies}.abs(2:4,2).' , ... % jonit base and tip position
                    joint(i_joint).TQ{i_copies}.abs(1:4,1).' , joint(i_joint).TQ2nd{i_copies}.abs(1:4,1).' , ... % joint base and tip Q
                    joint(i_joint).radi(i_copies) ] ;  % radius for plotting
                r_sd = joint(i_joint).TQ2nd{i_copies}.abs(2:4,2) - joint(i_joint).TQ{i_copies}.abs(2:4,2) ; % TQ2nd - TQ: subtracting order should match direction of q0, otherwise does not matter
                % if q0 = 0 -> any order results in two actions: f2nd(r2nd-r) & f(r-r2nd)
                % dr_sd = myJacobian( r_sd , qf ) * uf.' ;
                
                %% constraints
                i_free = [] ; % free directions in (to be removed from) sprdmp
                if ~isempty( joint(i_joint).fixed )
                    
                    % constrain vector
                    if joint(i_joint).refbody(i_copies,1) ~= 0 % contraint wrt refbody frame
                        if isempty( body(joint(i_joint).refbody(i_copies,1)).rom ) % rigid link
                            Q_ref = body(joint(i_joint).refbody(i_copies,1)).Q(joint(i_joint).refbody(i_copies,2)).abs ;
                        else % rom
                            Q_ref = body(joint(i_joint).refbody(i_copies,1)).Q(joint(i_joint).refbody(i_copies,2)).abs ;
                            if isnan( joint(i_joint).refbody(i_copies,3) ) % at tip
                                joint(i_joint).refbody(i_copies,3) = body(joint(i_joint).refbody(i_copies,1)).rom.l(joint(i_joint).refbody(i_copies,2),2);
                            end
                            Q_ref = subs( Q_ref , [s, sw] , joint(i_joint).refbody(i_copies,3) * [1, 1] ) ;
                        end
                        temp = Q_rot( Q_conj( Q_ref ) , [ 0 ; r_sd ] ) ; % transforming to refbody frame
                        r_sd_r = temp(2:4) ;
                    else
                        r_sd_r = r_sd ;
                    end
                    
                    if numel( joint(i_joint).fixed(i_copies,:) ) < 7 % 6 trans. & rot. spring/dampers
                        % Q_sd = 2 * Q_mult( Q_conj( joint(j_count).TQ{i_copies}.abs(:,1) ) , joint(j_count).TQ2nd{i_copies}.abs(:,1) - joint(j_count).TQ{i_copies}.abs(:,1) ) ;
                        Q_sd = Q_omega( joint(i_joint).TQ{i_copies}.abs(:,1) , joint(i_joint).TQ2nd{i_copies}.abs(:,1) - joint(i_joint).TQ{i_copies}.abs(:,1) ) ;
                        rQ_sd = [ r_sd_r ; Q_sd(2:4,1) ] ;
                    else % 7 trans. & quat rot.
                        Q_sd = joint(i_joint).TQ2nd{i_copies}.abs(:,1) - joint(i_joint).TQ{i_copies}.abs(:,1) ;
                        rQ_sd = [ r_sd_r ; Q_sd(:,1) ] ;
                    end
                    
                    temp = myJacobian( rQ_sd , q ).' ;
                    rcn = [ rcn ; r_sd_r.' ] ;
                    
                    for i_c = 1 : numel( joint(i_joint).fixed(i_copies,:) )
                        if joint(i_joint).fixed(i_copies,i_c) == 1 ... % constraint
                                || isinf( joint(i_joint).fixed(i_copies,i_c) ) % desired or known
                            n_constraints = n_constraints + 1 ;
                            pid = joint(i_joint).pid; % PID: P*u+I*q+Da
                            pid_3 = 1; if pid.d(i_copies,i_c) ~= 0; pid_3 = pid.d(i_copies,i_c); end
                            
                            cnst(n_constraints).r = smplfy( rQ_sd(i_c) ) ; % constraint relation
                            cnst(n_constraints).T = pid_3 * smplfy( temp(:,i_c).' ) ; % use T.' in dynamics EOM and T in algebraic part
                            vcn = smplfy( cnst(n_constraints).T * u.' ) ;
                            cnst(n_constraints).D = smplfy( myJacobian( vcn , q ) ) ;
                            cnst(n_constraints).in = - pid.p(i_copies,i_c) * vcn - pid.i(i_copies,i_c) * cnst(n_constraints).r + ...
                                smplfy( joint(i_joint).control(i_copies,i_c) ) ;
                            
                            if isinf( joint(i_joint).fixed(i_copies,i_c) ) % desired or known so no Tt
                                cnst(n_constraints).Tt = [] ;
                            else % constraint
                                cnst(n_constraints).Tt = cnst(n_constraints).T.'; % dosen't need pid
                                % lambdaf = [ lambdaf, lambda_vpa(n_cn) ] ;
                                lambda = [ lambda, sym( [ 'lambda' num2str( n_constraints ) ] , 'real' ) ] ;
                                dlambda = [ dlambda, sym( [ 'dlambda' num2str( n_constraints ) ] , 'real' ) ] ;
                            end
                            
                            if par.derive_collect == 5 % collect most terms
                                cnst(n_constraints).dc = - cnst(n_constraints).Dc * u.' + cnst(n_constraints).in;
                            end
                            
                            % sparse
                            cnst(n_constraints).r = sprse( cnst(n_constraints).r ) ;
                            cnst(n_constraints).T = sprse( cnst(n_constraints).T ) ;
                            cnst(n_constraints).D = sprse( cnst(n_constraints).D ) ;
                            % cnst(n_cn).in = smplfy( cnst(n_cn).in ) ;
                            
                            if ismember( par.derive_collect , [ 3 4 ] ) % for all constraints
                                Tcn = [ Tcn ; cnst(n_constraints).T ] ;
                                Tcu = [ Tcu , cnst(n_constraints).T.' ] ;
                                Dcn = [ Dcn ; cnst(n_constraints).D ] ;
                                C_constrainT = [ C_constrainT ; cnst(n_constraints).in ] ;
                            end
                        else
                            i_free = [ i_free , i_c ] ; % to be removed from sprdmp
                        end
                    end
                end % terms below are similar to a spring/damper element parallel with the above constraint
                
                %% simple spring
                if numel( joint(i_joint).spring.coeff(i_copies,:) ) == 1 % simple spring
                    
                    l_sd0 = joint(i_joint).spring.init(i_copies,1) ;
                    if isnan( joint(i_joint).spring.init(i_copies,1) ) % init. l based on q0 and compression ratio
                        r_sd0 = subs( r_sd , q , q0 ).' ; % 1x3
                        l_sd0_q0 = sqrt( r_sd0 * r_sd0.' ) ; % based on int. config.
                        l_sd0 = [] ;
                        l_sd0 = l_sd0_q0 ;
                    end
                    l_sd0 = joint(i_joint).spring.compr(i_copies,1) * l_sd0 ;                    
                    
                    temp = smplfy( myJacobian( r_sd , q ) ) ;
                    temp_u = temp * u.' ;
                    sprdmp(n_sprdmps).Tt = smplfy( temp.' ) ; % virtual displacement
                    
                    if isinf( l_sd0 ) % if relaxed state is considered part of the inverse controller
                        l_sd0 = 0;
                        n_control_inputs = n_control_inputs + 1 ;
                        gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        sprdmp(n_sprdmps).Tt_u = [ sprdmp(n_sprdmps).Tt_u, ...
                            sprdmp(n_sprdmps).Tt*( - joint(i_joint).spring.coeff(i_copies,1) * r_sd / sqrt( r_sd.' * r_sd ) ) ] ;
                    end                    
                    if isinf( joint(i_joint).input(i_copies) ) % if input is considered part of the inverse controller
                        joint(i_joint).input(i_copies) = 0 ;
                        n_control_inputs = n_control_inputs + 1 ;
                        gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        sprdmp(n_sprdmps).Tt_u = sprdmp(n_sprdmps).Tt * ones(3,1) ;
                    end
                    
                    sprdmp(n_sprdmps).kx = smplfy( ... % all spring/damper force virtual work
                        ( - joint(i_joint).spring.coeff(i_copies,1) * ...
                        r_sd * ( 1 - l_sd0 / sqrt( r_sd.' * r_sd ) ) ) ) ; % instantanious spring force vector
                    sprdmp(n_sprdmps).dl = smplfy( sqrt( r_sd.' * r_sd ) - l_sd0 ) ; % spring delta_l
                    sprdmp(n_sprdmps).vd = smplfy( ... % viscous damping force virtual work
                        - joint(i_joint).damp.visc(i_copies).' ...
                        .* temp_u ) ; % instantanious viscous force matrix
                    if joint(i_joint).damp.pow(i_copies,1) ~= 1 % speedup trick
                        sprdmp(n_sprdmps).vd = sprdmp(n_sprdmps).vd .* ( abs( temp_u ).^( joint(i_joint).damp.pow(i_copies,1) - 1 ) ) ;
                    end
                    sprdmp(n_sprdmps).in = smplfy( ... % input force virtual work
                        joint(i_joint).input(i_copies) * ones(3,1) ) ; % instantanious input value
                    sprdmp(n_sprdmps).k_mat = 0 ;
                    % smplfy( joint(j_count).spring.coeff(i_copies,1) * ... % for modal analysis if k is linear w.r.t. states
                    %     temp ) ;
                    sprdmp(n_sprdmps).vd_mat= 0 ;
                    % smplfy( ... % viscous damping force virtual work
                    %     - joint(j_count).damp.visc(i_copies).' ...
                    %     .* temp ) ; % instantanious viscous force matrix
                    % if joint(j_count).damp.pow(i_copies,1) ~= 1 % speedup trick
                    %     sprdmp(n_sd).vd_mat= sprdmp(n_sd).vd_mat.* ( abs( temp_u ).^( joint(j_count).damp.pow(i_copies,1) - 1 ) ) ;
                    % end
                    
                    
                %% beam trans. & rot. or constraint
                else % 6 elements for beam trans. & rot. or constraint
                    
                    r_sd0 = subs( r_sd , q , q0 ).' ; % 1x3
                    l_sd0_q0 = sqrt( r_sd0 * r_sd0.' ) ; % based on int. config.
                    temp = Q_rot( Q_conj( joint(i_joint).TQ{i_copies}.abs(:,1) ) , [ 0 ; r_sd0.' ] ) ; % r_{loc} = Q^{-1} * r_{abs} * Q
                    r_sd_r = Q_rot( Q_conj( joint(i_joint).TQ{i_copies}.abs(:,1) ) , [ 0 ; r_sd ] ) ; % r_{loc} = Q^{-1} * r_{abs} * Q
                    
                    if ~isempty( joint(i_joint).xaxis ) % rotate to beam frame
                        r_sd0_r = temp(2:4,1).' ; % 1x3 in local frame
                        yaxis =  cross( r_sd0_r , joint(i_joint).xaxis(i_copies,:) ) ; % 1x3 beam frame axis w.r.t. local frame
                        xaxis = cross( yaxis , r_sd0_r ) ;
                        R_b = [ xaxis/sqrt( xaxis * xaxis.' ) ;
                            yaxis/sqrt( yaxis * yaxis.' ) ;
                            r_sd0_r/l_sd0_q0 ] ;
                        r_sd_rb = R_b.' * r_sd_r(2:4,1) ; % 3x1 transformed to beam frame
                        Q_rb = R2Q( R_b ) ; % beam frame relative to local frame
                        Q_b = Q_mult( Q_conj( Q_rb ) , joint(i_joint).TQ{i_copies}.abs(:,1) ) ;
                    else
                        r_sd_rb = r_sd_r(2:4,1) ; % 3x1 already in beam frame
                        Q_b = joint(i_joint).TQ{i_copies}.abs(:,1) ;
                    end
                    % Q_sd_r = 2 * Q_mult( Q_conj( Q_b ) , joint(j_count).TQ2nd{i_copies}.abs(:,1) - Q_b ) ;
                    Q_sd_r = Q_omega( Q_b , joint(i_joint).TQ2nd{i_copies}.abs(:,1) - Q_b ) ;
                    rQ_sd = [ r_sd_rb ; Q_sd_r(2:4,1) ] ; % 6 trans. & rot. spring/dampers
                    
                    rQ_sd0 = joint(i_joint).spring.init(i_copies,1:6) ;
                    for i_s = 1 : numel( rQ_sd0 )
                        if isnan( rQ_sd0(i_s) )
                            rQ_sd0 = sym( rQ_sd0 ) ;
                            rQ_sd0(i_s) = subs( rQ_sd(i_s) , q , q0 ) ;
                            % if i_s == 3 % init. l based on q0 and compression ratio
                            %     rQ_sd0(i_s) = l_sd0_q0 ;
                            % end
                        end
                    end
                    rQ_sd0 = rQ_sd0 .* joint(i_joint).spring.compr(i_copies,:) ;
                                   
                    temp = smplfy( myJacobian( rQ_sd , q ) ) ;
                    temp_u = temp * u.' ;
                    sprdmp(n_sprdmps).Tt = smplfy( temp.' ) ; % virtual displacement, need to be based on rQ_sd in the same frame as the force, i.e. local frame
                    
                    for i_s = 1 : numel( rQ_sd0 ) % if relaxed state is considered part of the inverse controller
                        if isinf( rQ_sd0(i_s) )
                            rQ_sd0(i_s) = 0 ;
                            n_control_inputs = n_control_inputs + 1 ;
                            gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                            dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                            sprdmp(n_sprdmps).Tt_u = [ sprdmp(n_sprdmps).Tt_u, ...
                                sprdmp(n_sprdmps).Tt(:,i_s)*( - joint(i_joint).spring.coeff(i_copies,i_s) ) ] ;
                        end
                    end
                    for i_in = 1 : numel( joint(i_joint).input(i_copies,:) ) % if input is considered part of the inverse controller
                        if isinf( joint(i_joint).input(i_copies,i_in) )
                            joint(i_joint).input(i_copies,i_in) = 0 ;
                            n_control_inputs = n_control_inputs + 1 ;
                            gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                            dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                            sprdmp(n_sprdmps).Tt_u = [ sprdmp(n_sprdmps).Tt_u, sprdmp(n_sprdmps).Tt(:,i_in) ] ;
                        end
                    end
                    
                    sprdmp(n_sprdmps).kx = smplfy( ... % all spring/damper force virtual work
                        - ( joint(i_joint).spring.coeff(i_copies,:).' ) ...
                        .* ( rQ_sd - rQ_sd0.' ) ) ; % instantanious spring force vector
                    sprdmp(n_sprdmps).dl = smplfy( sqrt( r_sd.' * r_sd ) - rQ_sd0(3) ) ; % spring delta-l
                    sprdmp(n_sprdmps).vd = smplfy( ... % viscous damping force virtual work
                        - ( joint(i_joint).damp.visc(i_copies,:).' ) ...
                        .* temp_u ) ; % instantanious viscous force matrix
                    if joint(i_joint).damp.pow(i_copies,1) ~= 1 % speedup trick
                        sprdmp(n_sprdmps).vd = sprdmp(n_sprdmps).vd .* ( abs( temp_u ).^( joint(i_joint).damp.pow(i_copies,1) - 1 ) ) ;
                    end
                    sprdmp(n_sprdmps).in = smplfy( ... % input force virtual work
                        joint(i_joint).input(i_copies,:).' ) ; % instantanious input value
                    sprdmp(n_sprdmps).k_mat = 0 ;
                    % smplfy( ( joint(j_count).spring.coeff(i_copies,:).' ) ... % for modal analysis if k is linear w.r.t. states
                    %     .* temp ) ;
                    sprdmp(n_sprdmps).vd_mat= 0 ;
                    % smplfy( ... % viscous damping force virtual work
                    %     - ( joint(j_count).damp.visc(i_copies,:).' ) ...
                    %     .* temp ) ; % instantanious viscous force matrix
                    % if joint(j_count).damp.pow(i_copies,1) ~= 1 % speedup trick
                    %     sprdmp(n_sd).vd_mat= sprdmp(n_sd).vd_mat.* ( abs( temp_u ).^( joint(j_count).damp.pow(i_copies,1) - 1 ) ) ;
                    % end
                                        
                    % % remove free directions (not needed as we can set k & nu = 0)
                    % sprdmp(n_sd).Tt(:,i_free) = [] ;
                    % sprdmp(n_sd).kx(i_free,:) = [] ;
                    % sprdmp(n_sd).vd(i_free,:) = [] ;
                    % sprdmp(n_sd).in(i_free,:) = [] ;
                    % sprdmp(n_sd).k_mat(i_free,:) = [] ;
                    % sprdmp(n_sd).vd_linear(i_free,:) = [] ;
                end
                
                rom.sprdmp = [ rom.sprdmp; 0, 0, 0 ] ;
                switch joint(i_joint).dir(i_copies)
                    case 1 % compression-only elements, e.g. soft contact
                        sprdmp(n_sprdmps).dir = smplfy( sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                    case 0 % both dir.ss, e.g. regular spring/damper
                        sprdmp(n_sprdmps).dir = 1 ;
                    case -1 % tension-only elements, e.g. wire
                        sprdmp(n_sprdmps).dir = smplfy( - sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                end
                
                if par.derive_collect == 5 % collect most terms                
                    sprdmp(n_sprdmps).w_vd_j = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).w_sd = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).kx * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).w_in = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).in * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).Tt_u = sprdmp(n_sprdmps).Tt_u * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                end
                
                % sparse matrix
                sprdmp(n_sprdmps).Tt = sprse( sprdmp(n_sprdmps).Tt ) ;
                sprdmp(n_sprdmps).kx = sprse( sprdmp(n_sprdmps).kx ) ;
                sprdmp(n_sprdmps).dl = sprse( sprdmp(n_sprdmps).dl ) ;
                sprdmp(n_sprdmps).vd = sprse( sprdmp(n_sprdmps).vd ) ;
                sprdmp(n_sprdmps).in = sprse( sprdmp(n_sprdmps).in ) ;
                sprdmp(n_sprdmps).k_mat = sprse( sprdmp(n_sprdmps).k_mat ) ;
                sprdmp(n_sprdmps).vd_mat= sprse( sprdmp(n_sprdmps).vd_mat) ;
                if ~isempty( sprdmp(n_sprdmps).Tt_u )
                    sprdmp(n_sprdmps).Tt_u = sprse( sprdmp(n_sprdmps).Tt_u ) ;
                end
                
                if ismember( par.derive_collect , [ 3 4 ] ) % for all spring/dampers
                    w_k = w_k + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).kx ;
                    w_vd = w_vd + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd ;
                    w_in = w_in + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).in ;
                    w_sdi = w_sdi + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * ( ...
                        sprdmp(n_sprdmps).kx + sprdmp(n_sprdmps).vd + sprdmp(n_sprdmps).in ) ; % all spring/damper/input force virtual work
                    w_k_mat = w_k_mat + sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).k_mat ;
                    w_vd_mat = w_vd_mat + sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd_mat;
                    Tcu = [ Tcu , sprdmp(n_sprdmps).Tt_u ] ;
                end
            end
        end
        
        %% rom
        if joint(i_joint).second(1,1) == b_count && joint(i_joint).rom.isROM % if the joint is reduced order model
            i_joint            
            
            for i_copies = 1 : max( [ numel( joint(i_joint).first(1,:) ) , numel( joint(i_joint).second(1,:) ) ] ) - 1
                rom.sprdmp = [ rom.sprdmp ; joint(i_joint).rom.length(i_copies,1:2), 0 ] ;
                r_sd = joint(i_joint).TQ{i_copies}.loc(:,2) ;
                n_sprdmps = n_sprdmps + 1 ;
                
                switch joint(i_joint).rom.stiffmodel % rom beam stiffness model
                    case 1 % continuous
                        dr_sd = diff( r_sd , s ) ;
                        dQ_sd = diff( joint(i_joint).TQ{i_copies}.loc(:,1) , s ) ;
                        % uQ_sd = 2 * Q_mult( Q_conj( joint(i_joint).TQ{i_copies}.loc(:,1) ) , dQ_sd ) ;
                        uQ_sd = Q_omega( joint(i_joint).TQ{i_copies}.loc(:,1) , dQ_sd ) ; % same as 2*Q_conj*dQ but less computation in derivation phase
                        vr_sd = Q_rot( Q_conj( joint(i_joint).TQ{i_copies}.loc(:,1) ) , dr_sd ) ; % transfer to local frame in which K is defined
                        rQ_sd = [ vr_sd(2:4,1) ; uQ_sd(2:4,1) ] ; % [ v u ]: 6 trans. & rot. spring/dampers
                        
                        % for spring IC
                        if max( isnan( joint(i_joint).spring.init(i_copies,1:6) ) )
                            r_sd_spr = joint(i_joint).spring.TQ{i_copies}.loc(:,2) ;
                            dr_sd_spr = diff( r_sd_spr , s ) ;
                            dQ_sd_spr = diff( joint(i_joint).spring.TQ{i_copies}.loc(:,1) , s ) ;
                            % uQ_sd_spr = 2 * Q_mult( Q_conj( joint(i_joint).spring.TQ{i_copies}.loc(:,1) ) , dQ_sd_spr ) ;
                            uQ_sd_spr = Q_omega( joint(i_joint).spring.TQ{i_copies}.loc(:,1) , dQ_sd_spr ) ;
                            vr_sd_spr = Q_rot( Q_conj( joint(i_joint).spring.TQ{i_copies}.loc(:,1) ) , dr_sd_spr ) ;
                            rQ_sd_spr = [ vr_sd_spr(2:4,1) ; uQ_sd_spr(2:4,1) ] ; % [ v u ]: 6 trans. & rot. spring/dampers
                        end
                        
                    case 2 % discretized
                        dr_sd = subs( r_sd , [s, sw] , [s, sw]+ds ) - r_sd ;
                        dQ_sd = subs( joint(i_joint).TQ{i_copies}.loc(:,1) , [s, sw] , [s, sw]+ds ) - joint(i_joint).TQ{i_copies}.loc(:,1) ;
                        % uQ_sd = 2 * Q_mult( Q_conj( joint(j_count).TQ{i_copies}.loc(:,1) ) , dQ_sd ) ;
                        uQ_sd = Q_omega( joint(i_joint).TQ{i_copies}.loc(:,1) , dQ_sd ) ; % same as 2*Q_conj*dQ but less computation in derivation phase
                        vr_sd = Q_rot( Q_conj( joint(i_joint).TQ{i_copies}.loc(:,1) ) , dr_sd ) ; % transfer to local frame in which K is defined
                        rQ_sd = [ vr_sd(2:4,1) ; uQ_sd(2:4,1) ] ; % [ v u ]: 6 trans. & rot. spring/dampers
                        
                        % for spring IC
                        if max( isnan( joint(i_joint).spring.init(i_copies,1:6) ) )
                            r_sd_spr = joint(i_joint).spring.TQ{i_copies}.loc(:,2) ;
                            dr_sd_spr = subs( r_sd_spr , [s, sw] , [s, sw]+ds ) - r_sd_spr ;
                            dQ_sd_spr = subs( joint(i_joint).spring.TQ{i_copies}.loc(:,1) , [s, sw] , [s, sw]+ds ) - joint(i_joint).spring.TQ{i_copies}.loc(:,1) ;
                            % uQ_sd_spr = 2 * Q_mult( Q_conj( joint(j_count).spring.TQ{i_copies}.loc(:,1) ) , dQ_sd_spr ) ;
                            uQ_sd_spr = Q_omega( joint(i_joint).spring.TQ{i_copies}.loc(:,1) , dQ_sd_spr ) ;
                            vr_sd_spr = Q_rot( Q_conj( joint(i_joint).spring.TQ{i_copies}.loc(:,1) ) , dr_sd_spr ) ;
                            rQ_sd_spr = [ vr_sd_spr(2:4,1) ; uQ_sd_spr(2:4,1) ] ; % [ v u ]: 6 trans. & rot. spring/dampers
                        end
                        rom.sprdmp(end,end) = 1 ;
                end
                
                % beam relaxed state
                % no i_copies for spring.init & spring.init_s at the moment
                rQ_sd0 = sym( joint(i_joint).spring.init(i_copies,1:6) ) ;

                % % transform strain coeff.s to global frame for less derivation complexity: only the strains not curvatures, no advantages in transforming the curvatures!
                % if isnan( max( rQ_sd0(1:3) ) ) % all translational strains are extracted from a fitted spline
                %     rQ_sd(1:3) = dr_sd(2:4,1); % replace with strain in global frame
                %     rQ_sd_spr(1:3) = dr_sd_spr(2:4,1); % replace with relaxed state strain in global frame
                %     K_v = Q_rot( joint(i_joint).TQ{i_copies}.loc(:,1) , [0, joint(i_joint).spring.coeff(i_copies,1:3) ].' ) ; % transform K to global frame
                %     joint(i_joint).spring.coeff(i_copies,1:3) = K_v(2:4) ; % K_strain in global and k_curvature in local curvilinear frame
                %     mu_v = Q_rot( joint(i_joint).TQ{i_copies}.loc(:,1) , [0, joint(i_joint).damp.visc(i_copies,1:3) ].' ) ; % transform mu to global frame
                %     joint(i_joint).damp.visc(i_copies,1:3) = mu_v(2:4) ; % K_strain in global and k_curvature in local curvilinear frame
                % end
                
                % extract relaxed state from fitted spline
                % copy over the strains/curvatures extracted from spline fitted for relaxed state
                for i_s = 1 : numel( rQ_sd0 )
                    if isnan( rQ_sd0(i_s) )
                        rQ_sd0(i_s) = rQ_sd_spr(i_s) ;
                    end
                end
                rQ_sd0 = rQ_sd0 .* joint(i_joint).spring.compr(i_copies,:) ;
                
                % virtual displacement of element both ends, here described by spatial differentiation
                temp = smplfy( myJacobian( rQ_sd , q ) ) ; % same as Jacobian( rQ_sd - rQ_sd0 , q ), need to be based on rQ_sd in the same frame as the force, i.e. local frame
                temp_u = smplfy( temp * u.' ) ;
                sprdmp(n_sprdmps).Tt = smplfy( temp.' ) ; % virtual displacement
                  
                for i_s = 1 : numel( rQ_sd0 ) % if relaxed state is considered part of the inverse controller
                    if isinf( rQ_sd0(i_s) )
                        rQ_sd0(i_s) = 0 ;
                        n_control_inputs = n_control_inputs + 1 ;
                        gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        sprdmp(n_sprdmps).Tt_u = [ sprdmp(n_sprdmps).Tt_u, ...
                            sprdmp(n_sprdmps).Tt(:,i_s)*( -joint(i_joint).spring.coeff(i_copies,i_s) ) ] ;
                    end
                end
                for i_in = 1 : numel( joint(i_joint).input(i_copies,:) ) % if input is considered part of the inverse controller
                    if isinf( joint(i_joint).input(i_copies,i_in) )
                        joint(i_joint).input(i_copies,i_in) = 0 ;
                        n_control_inputs = n_control_inputs + 1 ;
                        gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                        sprdmp(n_sprdmps).Tt_u = [ sprdmp(n_sprdmps).Tt_u, sprdmp(n_sprdmps).Tt(:,i_in) ] ;
                    end
                end
                
                sprdmp(n_sprdmps).kx = smplfy( ... % all spring/damper force virtual work
                    - ( joint(i_joint).spring.coeff(i_copies,:).' ) ...
                    .* ( rQ_sd - rQ_sd0.' ) ) ; % instantanious spring force vector
                sprdmp(n_sprdmps).dl = smplfy( dr_sd(2:4).' ) ; % spring delta-l
                sprdmp(n_sprdmps).vd = smplfy( ... % viscous damping force virtual work
                    - ( joint(i_joint).damp.visc(i_copies,:).' ) ...
                    .* temp_u ) ; % instantanious viscous force matrix
                if joint(i_joint).damp.pow(i_copies,1) ~= 1 % speedup trick
                    sprdmp(n_sprdmps).vd = sprdmp(n_sprdmps).vd .* ( abs( temp_u ).^( joint(i_joint).damp.pow(i_copies,1) - 1 ) ) ;
                end
                sprdmp(n_sprdmps).in = smplfy( ... % input force virtual work
                    joint(i_joint).input(i_copies,:).' ) ; % instantanious input value
                sprdmp(n_sprdmps).k_mat = 0 ;
                sprdmp(n_sprdmps).vd_mat= 0 ;
                
                switch joint(i_joint).dir(i_copies)
                    case 1 % compression-only elements, e.g. soft contact
                        sprdmp(n_sprdmps).dir = smplfy( sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                    case 0 % both dir.ss, e.g. regular spring/damper
                        sprdmp(n_sprdmps).dir = 1 ;
                    case -1 % tension-only elements, e.g. wire
                        sprdmp(n_sprdmps).dir = smplfy( - sign( sprdmp(n_sprdmps).dl ) + 1 ) / 2 ;
                end
                
                if par.derive_collect == 5 % collect most terms
                    sprdmp(n_sprdmps).w_vd_j = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).w_sd = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).kx * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).w_in = sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).in * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                    sprdmp(n_sprdmps).Tt_u = sprdmp(n_sprdmps).Tt_u * ( rom.sprdmp(end,2) - rom.sprdmp(end,1) ) ;
                end
                
                % sparse matrix
                sprdmp(n_sprdmps).Tt = sprse( sprdmp(n_sprdmps).Tt ) ;
                sprdmp(n_sprdmps).kx = sprse( sprdmp(n_sprdmps).kx ) ;
                sprdmp(n_sprdmps).dl = sprse( sprdmp(n_sprdmps).dl ) ;
                sprdmp(n_sprdmps).vd = sprse( sprdmp(n_sprdmps).vd ) ;
                sprdmp(n_sprdmps).in = sprse( sprdmp(n_sprdmps).in ) ;
                sprdmp(n_sprdmps).k_mat = sprse( sprdmp(n_sprdmps).k_mat ) ;
                sprdmp(n_sprdmps).vd_mat= sprse( sprdmp(n_sprdmps).vd_mat) ;
                if ~isempty( sprdmp(n_sprdmps).Tt_u )
                    sprdmp(n_sprdmps).Tt_u = sprse( sprdmp(n_sprdmps).Tt_u ) ;
                end
                
                if ismember( par.derive_collect , [ 3 4 ] ) % for all spring/dampers
                    w_k = w_k + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).kx ;
                    w_vd = w_vd + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd ;
                    w_in = w_in + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).in ;
                    w_sdi = w_sdi + sprdmp(n_sprdmps).dir * sprdmp(n_sprdmps).Tt * ( ...
                        sprdmp(n_sprdmps).kx + sprdmp(n_sprdmps).vd + sprdmp(n_sprdmps).in ) ; % all spring/damper/input force virtual work
                    w_k_mat = w_k_mat + sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).k_mat ;
                    w_vd_mat = w_vd_mat + sprdmp(n_sprdmps).Tt * sprdmp(n_sprdmps).vd_mat;
                    Tcu = [ Tcu , sprdmp(n_sprdmps).Tt_u ] ;
                end
            end
        end
    end
end
nlambda = numel( lambda ) ;
ngamma = numel( gamma ) ;

%% handle external forces
% linear force for now
fprintf( 'Deriving external load dynamics... \n' )
Ttef = sym( [] ) ;
ftau_ef = sym( [] ) ;
for i_exload = 1 : n_extLoads
    if isempty( exload(i_exload).exbody )
        n_extLoads = n_extLoads - 1 ;
        continue ;
    end
    i_exload
    
    for i_copies = 1 : numel( exload(i_exload).exbody(1,:) ) - 1
        
        exload(i_exload).Q{i_copies}.loc = sym( [ 1 0 0 0 ].' );
        exload(i_exload).TQ{i_copies}.loc = sym( [ 1 0 0 0 ; 0 0 0 0 ].' );
        
        [ ~ , n_joint_transfs ] = size( exload(i_exload).tr ) ; % number of transforamtions in a joint
        for i_transfs = 1 : n_joint_transfs
            [ Q_temp , TQ_temp ] = TQ_mat( [ exload(i_exload).tr(i_transfs).trans , exload(i_exload).tr(i_transfs).rot ] , [ q s ] , exload(i_exload).tr(i_transfs).type );
            exload(i_exload).Q{i_copies}.loc = Q_mult( exload(i_exload).Q{i_copies}.loc , Q_temp ) ;
            exload(i_exload).TQ{i_copies}.loc = TQ_mult( exload(i_exload).TQ{i_copies}.loc , TQ_temp ) ;
        end
        
        if isempty( body(exload(i_exload).exbody(1,1)).rom ) % not rom
            Q = body(exload(i_exload).exbody(1,1)).Q{exload(i_exload).exbody(1,i_copies+1)}.abs ;
            TQ = body(exload(i_exload).exbody(1,1)).TQ{exload(i_exload).exbody(1,i_copies+1)}.abs ;
        else
            Q = body(exload(i_exload).exbody(1,1)).Q{exload(i_exload).exbody(1,i_copies+1)}.abs ;
            TQ = body(exload(i_exload).exbody(1,1)).TQ{exload(i_exload).exbody(1,i_copies+1)}.abs ;
            if isnan( exload(i_exload).exbody(2,i_copies+1) ) % at tip
                exload(i_exload).exbody = sym( exload(i_exload).exbody );
                exload(i_exload).exbody(2,i_copies+1) = body(exload(i_exload).exbody(1,1)).rom.l(exload(i_exload).exbody(1,i_copies+1),2);
            end
            Q = subs( Q , [s, sw] , exload(i_exload).exbody(2,i_copies+1) * [1, 1] ) ;
            TQ = subs( TQ , [s, sw] , exload(i_exload).exbody(2,i_copies+1) * [1, 1] ) ;
        end
        exload(i_exload).Q{i_copies}.abs = Q_mult( Q , exload(i_exload).Q{i_copies}.loc ) ;
        exload(i_exload).TQ{i_copies}.abs = TQ_mult( TQ , exload(i_exload).TQ{i_copies}.loc ) ;
        
        % both load and action vector should be in same frame
        ref(i_exload,:) = exload(i_exload).TQ{i_copies}.abs(2:4,2).';
        r_ex = exload(i_exload).TQ{i_copies}.abs(2:4,2) ; % exerting point vector in ref. frame
        loads(i_exload).Tt(:,1:3) = smplfy( myJacobian( exload(i_exload).TQ{i_copies}.abs(2:4,2) , q ).' ) ; % in ref. frame
        temp = myJacobian( exload(i_exload).Q{i_copies}.abs , q ) ;
        % temp = 2 * Q_mult( Q_conj( exload(i_exload).Q{i_copies}.abs ) , temp ) ; % in exbody. frame: omega_abs = 2 * Q^{-1} * Q_{,t}
        temp = Q_omega( exload(i_exload).Q{i_copies}.abs , temp ) ;
        loads(i_exload).Tt(:,4:6) = smplfy( temp(2:4,:).' ) ; % in exbody frame
        
        % transfer f to ref. frame and tau to exbody. frame
        % default: in ref. frame
        f_reff = [ 0 exload(i_exload).ftau(i_copies,1:3) ].' ; % f in ref. frame
        tau_reff = [ 0 exload(i_exload).ftau(i_copies,4:6) ].' ; % tau in ref. frame
        if exload(i_exload).refbody(i_copies,1) ~= 0 % ftau in refbody frame
            if isempty( body(exload(i_exload).refbody(i_copies,1)).rom ) % rigid link
                Q_ref = body(exload(i_exload).refbody(i_copies,1)).Q(exload(i_exload).refbody(i_copies,2)).abs ;
            else % rom
                Q_ref = body(exload(i_exload).refbody(i_copies,1)).Q(exload(i_exload).refbody(i_copies,2)).abs ;
                if isnan( exload(i_exload).refbody(i_copies,3) ) % at tip
                    exload(i_exload).refbody(i_copies,3) = body(exload(i_exload).refbody(i_copies,1)).rom.l(exload(i_exload).refbody(i_copies,2),2);
                end
                Q_ref = subs( Q_ref , [s, sw] , exload(i_exload).refbody(i_copies,3) * [1, 1] ) ;
            end
            f_reff = Q_rot( Q_conj( Q_ref ) , f_reff ) ; % f in ref. frame
            tau_reff = Q_rot( Q_conj( Q_ref ) , tau_reff ) ; % tau in ref. frame
        end
        tau_exbf = Q_rot( Q_conj( exload(i_exload).Q{i_copies}.abs ) , tau_reff ) ; % tau in exbody. frame
        loads(i_exload).ftau = smplfy( [ f_reff(2:4,1) ; tau_exbf(2:4,1) ] ) ;
        
        % if ftau is considered part of the observer
        for i_ftau = 1 : numel( loads(i_exload).ftau )
            if isinf( loads(i_exload).ftau(i_ftau,1) )
                loads(i_exload).ftau(i_ftau,1) = 0 ;
                n_control_inputs = n_control_inputs + 1 ;
                gamma = [ gamma, sym( [ 'gamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                dgamma = [ dgamma, sym( [ 'dgamma' num2str( n_control_inputs ) ] , 'real' ) ] ;
                loads(i_exload).Tt_o = [ loads(i_exload).Tt_o, loads(i_exload).Tt(:,i_ftau) ] ;
            end
        end
        
        if par.derive_collect == 5 % collect most terms
            loads(i_exload).w_f = loads(i_exload).Tt * loads(i_exload).ftau ;
        end
        
        % sparse matrix
        loads(i_exload).Tt = sprse( loads(i_exload).Tt ) ;
        loads(i_exload).ftau = sprse( loads(i_exload).ftau ) ;
        loads(i_exload).Tt_o = sprse( loads(i_exload).Tt_o ) ;
        
        if ismember( par.derive_collect , [ 3 4 ] )  % for all ex. forces
            Ttef = [ Ttef loads(i_exload).Tt ] ;
            ftau_ef = [ ftau_ef ; loads(i_exload).ftau ] ;
            Tcu = [ Tcu , loads(i_exload).Tt_o ] ;
        end
    end
end


% k_mat for modal analysis:
k_mat = w_k_mat + fj_k_mat ; % total stiffnes matrix for modal analysis
vd_mat = w_vd_mat + fj_vd_mat ;

if par.clean % clean up memory
    clearvars -except ...
        q u lambda dlambda gamma dgamma s ds sw t_sym par ...
        mass sprdmp cnst loads ...
        n_q_states nlambda ngamma q0 n_m n_sprdmps n_constraints n_control_inputs n_extLoads ...
        M T fj_k fj_vd fj_in fj_sdi fj_k_mat fj_vd_mat Tj_u ...
        fgv Dd ref rcn Ttef ftau_ef Tcn Tcu Dcn r_jtips w_sdi ...
        w_k w_vd w_k_mat w_vd_mat w_in r_ks k_mat vd_mat rom
end


%% report:
save( 'eom/derivations.mat' ) ; % save all

save_func( q , u , lambda , dlambda , gamma , dgamma , s , ds , sw , t_sym , par , ...
    mass , sprdmp , cnst , loads , ...
    n_q_states , nlambda , ngamma , q0 , n_m , n_sprdmps , n_constraints , n_control_inputs , n_extLoads , ...
    M , T , fj_k , fj_vd , fj_in , fj_sdi , fj_k_mat , fj_vd_mat , Tj_u , ...
    fgv , Dd , ref , rcn , Ttef , ftau_ef , Tcn , Tcu , Dcn , r_jtips , w_sdi , ...
    w_k , w_vd , w_k_mat , w_vd_mat , w_in , r_ks , k_mat , vd_mat , rom ) ;


%% Complementary Functions:
function [ Q , TQ ] = TQ_mat( r , qs , type , init_Q_axis )
% Q = [ q0 r1 r2 r3 ] ; % quaternion format
% Q1 & Q2 are cloumn vectors

switch type % {'angle_axis', 'rot_strain', 'non_unit_quat', 'frenet_serret', 'simple_curvilinear', 'bishop_frame', 'growing'}
    
    case 'angle_axis' % angle-axis: 4 elements
        Q = ( [ cos( r(4) / 2 ), sin( r(4) / 2 )*r(5:7)/sqrt( r(5:7) * r(5:7).' ) ].' ) ;
        
    case 'rot_strain' % variable curvature with piecewise constant strain assumption in each elements: 3 elements
        Q = [ 1, r(4:6)/2 ].';
        
    case 'unit_quat' % unit quaternion: 3 elements
        Q = [ sqrt( 1 - r(4:6) * r(4:6).' ), r(4:6) ].' ; % % only 0:pi, avoid singularity
        
    case 'non_unit_quat' % non-uit quaternion: 4 elements
        Q = r(4:7).' ; % avoid singularity
        Q = Q / sqrt( Q.' * Q ) ;
        
    case 'frenet_serret'
        s = qs(end);
        rho = r(1:3).' ;
        drho = diff( rho , s );
        t = drho / sqrt( drho.' * drho ) ;
        
        ddrho = diff( drho , s );
        temp = cross( drho , ddrho ) ;
        b = temp / sqrt( temp.' * temp ) ;
        n = cross( b, t );
        
        % dt = diff( t , s );
        % n = dt / sqrt( dt.' * dt ) ;
        % b = cross( t, n );
        
        R = [ t, n, b ];
        Q(1,1) = sqrt( 1 + R(1,1) + R(2,2) + R(3,3) ) / 2 ; % only if trace(R)+1<0
        Q(2,1) = ( R(3,2) - R(2,3) ) / ( 4 * Q(1,1) ) ;
        Q(3,1) = ( R(1,3) - R(3,1) ) / ( 4 * Q(1,1) ) ;
        Q(4,1) = ( R(2,1) - R(1,2) ) / ( 4 * Q(1,1) ) ;
        
    case 'simple_curvilinear'
        s = qs(end) ;
        rho = r(1:3).' ;
        drho = diff( rho , s ) ;
        t = drho / sqrt( drho.' * drho ) ;
        init_Q_axis(2:4) = init_Q_axis(2:4) / sqrt( init_Q_axis(2:4) * init_Q_axis(2:4).' ) ;
        
        % according to definition
        % % Q(1,1) = sqrt( ( init_Q_axis(2:4) * init_Q_axis(2:4).' ) * ( t.' * t ) ) + init_Q_axis(2:4) * t ;
        % Q(1,1) = 1 + init_Q_axis(2:4) * t ; % vectors already normalized
        % Q(1,2:4) = cross( init_Q_axis(2:4) , t.' ) ;
        % Q = ( Q / sqrt( Q * Q.' ) ).' ;
        
        % simpleset derivation: singular at pi
        temp = sqrt( 2 + 2 * init_Q_axis(2:4) * t ) ;
        Q(1,1) = temp / 2 ;
        Q(1,2:4) = 1 / temp * cross( init_Q_axis(2:4) , t.' ) ; % vectors already normalized
        Q = Q.' ;        
        
        if isnan(temp); Q = [ 1, 0, 0, 0 ].'; end
        
    case 'bishop_frame' % same as 'simple_curvilinear' for now
        ... TODO
        
    otherwise
        Q = [ 1, 0, 0, 0 ].';
end

TQ = sym ( [ Q , [ 0, r(1:3) ].' ] ) ; % 4x4: Each QR contains a translation and then a rotation
Q = smplfy( sym( Q ) ) ;
TQ = smplfy( sym( TQ ) ) ;


