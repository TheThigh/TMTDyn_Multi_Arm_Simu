function par = post_proc( t , t_equil , z , z_equil , rjtip , rjtip_equil , Qjtip_all , Qjtip_equil_all , ...
    Phi_modal , M_modal , K_modal , V_modal , omega , xi , ...
    par )

if ~iscell(rjtip)
    fprintf( 'post-processing... \n' )
    par.elapsed_time = [ par.elapsed_time toc( par.timer ) ] ;
    toc( par.timer );
    
    Err_vec = zeros( 1 , 3 ) ; 
    for i = 1 : numel( t )
        tip_sim(i,:) = rjtip(end,4:6,i) ;
        % error analysis
        step = floor( t(i) / 0.05 ) ;
        Err_vec(i,:) = par.user_pars.tip_pos(step,2:4) - tip_sim(i,:) ;
        Err_abs_all(i) = sqrt( Err_vec(i,:) * Err_vec(i,:)' ) ;    
    end
    
    Err_abs = mean( Err_abs_all )
    Err_std = std( Err_abs_all )
    Err_norm = Err_abs / ( par.var(5) + par.var(17) ) * 100
    
    figcompare = figure ;
    subplot(1,2,1);
    
    % 2022.12.28
    % Delete the experimental data since it is of no use for a different
    % simulation scenario, meanwhile we keep the original source code in the
    % format of comment for back use.
    % plot( par.user_pars.tip_pos(:,1) , par.user_pars.tip_pos(:,2:4) , '--' , t , tip_sim , '-' , 'LineWidth' , 2 ) ;
    % legend( 'x_{exp}' , 'y_{exp}' , 'z_{exp}' , 'x_{sim}' , 'y_{sim}' , 'z_{sim}' ) ; title( 'Sim.')
    
    plot(t , tip_sim , '-' , 'LineWidth' , 1);
    grid on;
    xlabel('Time (s)'); ylabel('Position (m)');
    legend('x_{p}' , 'y_{p}' , 'z_{p}','location','northeastoutside'); title('Simulated');
    
    % tip_exp_ali = transformed ( par.tip_exp(:,2:4) ) ;
    % figure  ;
    % plot( par.tip_exp(:,1) , tip_exp_ali , '--' , t_all , tip_sim , linetype , 'LineWidth' , 2 ) ;
    % legend( 'x_{exp}' , 'y_{exp}' , 'z_{exp}' , 'x_{sim}' , 'y_{sim}' , 'z_{sim}' ) ;
    
    % for i = 1 : 3
    %     tip_sim_avg(:,i) = smooth( tip_sim(:,i) , 'moving' , 31 ) ;
    % end
    % figure  ;
    % plot( par.tip_exp(:,1) , par.tip_exp(:,2:4) , '--' , t_all , tip_sim_avg , linetype , 'LineWidth' , 2 ) ;
    % legend( 'x_{exp}' , 'y_{exp}' , 'z_{exp}' , 'x_{sim}' , 'y_{sim}' , 'z_{sim}' ) ;
    
    subplot(1,2,2)
    windowSize = floor( 0.5 * par.n_datasample ) ;
    tmp = windowSize ;
    b_filter = (1/windowSize)*ones(1,windowSize);
    a_filter = 1;
    tip_sim_filter = filter( b_filter , a_filter , tip_sim ) ;
    
    % 2022.12.28
    % The same reason as above for commenting the original source code.
    % plot( par.user_pars.tip_pos(:,1) , par.user_pars.tip_pos(:,2:4) , '--' , t(tmp:end) , tip_sim_filter(tmp:end,:) , '-' , 'LineWidth' , 2 ) ;
    % legend( 'x_{exp}' , 'y_{exp}' , 'z_{exp}' , 'x_{sim}' , 'y_{sim}' , 'z_{sim}' ) ; title( 'Filtered')
    
    plot(t(tmp:end) , tip_sim_filter(tmp:end,:) , '-' , 'LineWidth' , 1);
    grid on;
    xlabel('Time (s)'); ylabel('Position (m)');
    legend('x_{p}' , 'y_{p}' , 'z_{p}','location','northeastoutside'); title('Filtered');
    
    set(gcf,'position',[50,325,1200,400]);
    
    % subplot(1,2,2)
    % tip_sim_smooth = smoothV( tip_sim , 0.5 * stepT ) ;
    % plot( par.tip_exp(:,1) , par.tip_exp(:,2:4) , '--' , t_all , tip_sim_smooth , linetype , 'LineWidth' , 2 ) ;
    % legend( 'x_{exp}' , 'y_{exp}' , 'z_{exp}' , 'x_{sim}' , 'y_{sim}' , 'z_{sim}' ) ;  title( 'Smooth')
    
    pause( 1 )
    save( 'results/results_post_proc.mat' ) ; % save workspace

    %% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%
    %% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%
    %% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%

    % 2023.01.30
    % Cope with the situation for n_SRA>=2
else
    for i=1:par{1,1}.user_pars.n_SRA
        for j=1:numel(t)
            tip_sim{i,1}(j,:)=rjtip{i,1}(end,4:6,j);
        end
    end
    figure(3);

    for i=1:par{1,1}.user_pars.n_SRA
        subplot(par{1,1}.user_pars.n_SRA,2,2*(i-1)+1);
        plot(t , tip_sim{i,1} , '-' , 'LineWidth' , 1);
        grid on;
        xlabel('Time (s)'); ylabel('Position (m)');
        legend('x_{p}' , 'y_{p}' , 'z_{p}','location','northeastoutside');
        title(['Simulated - Arm ',num2str(i)]);

        subplot(par{1,1}.user_pars.n_SRA,2,2*(i-1)+2);
        windowSize = floor( 0.5 * par{i,1}.n_datasample ) ;
        tmp = windowSize ;
        b_filter = (1/windowSize)*ones(1,windowSize);
        a_filter = 1;
        tip_sim_filter = filter( b_filter , a_filter , tip_sim{i,1} ) ;
        plot(t(tmp:end) , tip_sim_filter(tmp:end,:) , '-' , 'LineWidth' , 1);
        grid on;
        xlabel('Time (s)'); ylabel('Position (m)');
        legend('x_{p}' , 'y_{p}' , 'z_{p}','location','northeastoutside'); title(['Filtered - Arm ',num2str(i)]);
    end
    frame_y_min=325-(400-325)*(par{1,1}.user_pars.n_SRA*2);
    frame_y_max=325+(400-325)*(par{1,1}.user_pars.n_SRA*2);
    set(gcf,'position',[50,frame_y_min,1200,frame_y_max]);
    save( 'results/results_post_proc.mat' ) ; % save workspace
end


