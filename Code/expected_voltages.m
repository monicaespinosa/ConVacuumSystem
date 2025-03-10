x=10.09:0.04:50;
Vlpf=x.*3.3./100;
y=linspace(-62.5, 0, length(x)); % mV
I=y./270; % mA
R=linspace(15000, 560000, length(x));
x_2=3300.*270./(R+270);
Vlpf_2=-0.0211*x_2+1.65;

% Para encontrar los valores de R correr línea R_exp=logspace(log10(14581),log10(642250), 10);
% 1.0e+05 * 0.1458    0.2220    0.3381    0.5149    0.7842    1.1942    1.8186    2.7694    4.2174    6.4225

subplot(1,2,1)
plot(R./1000, Vlpf_2, 'LineWidth',2)
xlabel("Rc (kΩ)"),ylabel("LPF voltage (V)")
grid on, grid minor
subplot(1,2,2)
plot(R./1000, Vlpf_2, 'LineWidth',2)
xscale log
xlabel("Rc (kΩ)"),ylabel("LPF voltage (V)")
%plot(y, x, 'LineWidth',2)
%ylabel("Percentage (%)"),xlabel("Voltage (mV)")
%plot(Vlpf,I , 'LineWidth',2)
%xlabel("Voltage in (V)"),ylabel("Voltage out (mV)")
%plot(y,Vlpf , 'LineWidth',2)
%xlabel("Voltage in (mV)"),ylabel("LPF voltage (V)")
grid on, grid minor

%% With signal conditioning stage
%{
V_out=(1.65-Vlpf_2).*2.5;
plot(R./1000, V_out, 'LineWidth',2)
xlabel("Resistance (Kohm)"),ylabel("SC stage voltage (V)")
xscale log
grid on, grid minor
%}
figure(1)
%R_exp=logspace(log10(630),log10(2800000), 20);
R_exp=R;
%R_exp=downsample(R, 50);
%x_exp=-3300.*12./(R_exp+12);
%Vlpf_exp=0.02106.*x_exp + 1.649;
Vlpf_exp=Vlpf_2;
V_out_exp=(1.65-Vlpf_exp).*2.5;
plot(R_exp./1000, V_out_exp,'-s', 'LineWidth',2)
xlabel("Resistance (Kohm)"),ylabel("SC stage voltage (V)")
title('Recommended resistance values (log scale) vs SC stage voltage output')
xscale log
grid on, grid minor

%% Real

figure(2)
R_real=[0.679, 1.005, 1.496, 2.4, 3.605, 5.687, 9.05, 12.93, 19.66, 32.84, 47.87, 81.5, 131, 198.2, 298.8, 468.5, 704, 1111, 1815, 2726];
R_real=R_real.*1000;
I_real=3.3./(R_real+12);
x_real=-3300.*12./(R_real+12);
Vlpf_real=0.02106.*x_real + 1.649;
V_out_real=(1.65-Vlpf_real).*2.5;
hold on
plot(R_real./1000, V_out_real,'-s', 'LineWidth',2)
plot(R_real./1000, Vlpf_real,'-s', 'LineWidth',2)
hold off
legend(['SC output','LPF output'])
xlabel("Resistance (Kohm)"),ylabel("SC stage voltage (V)")
title('Actual chosen values of resistance vs expected SC stage voltage output')
xscale log
grid on, grid minor

figure (3)
plot(R_real./1000, I_real.*1000,'-s', 'LineWidth',2)
xlabel("Resistance (Kohm)"),ylabel("Current (mA)")
xscale log
grid on, grid minor

