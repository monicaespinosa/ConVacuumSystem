% ElectronEmissionCurrentEstimation_graphs.m
% Graphs
% Always run first section

% Physical Constants
k = 8.617e-5; % Boltzmann constant (eV/K)
A_Richardson = 120; % Richardson constant (A/cm^2/K^2) for tungsten
phi = 4.5; % Work function of tungsten (eV)
e = 1.6e-19; % Elementary charge (C)
m = 9.11e-31; % Electron mass (kg)
epsilon_0 = 8.85e-12; % Vacuum permittivity (F/m)
sigma = 1e-19; % Estimated collision cross-section (m^2)

% Experimental Parameters
T = 2000; % Temperature of the cathode (K)
Vs = 6; % Voltage applied to the cathode (V)
Vp = 60; % Voltage applied to the anode (V)
d = 0.05; % Distance between cathode and anode (m)
p_torr=1e-5; % Pressure in the vacuum chamber (Torr)
p = p_torr*133.3; % Pressure in the vacuum chamber (Pa)
D = 0.005; % Diameter of the tungsten filament (m)
L = 0.01; % Length of the tungsten filament (m)
dg = 0.01; % Distance from the grid to the anode (m), from 0 to d
Vg = 2000; % Voltage applied to the grid (V)

% Calculate the surface area of the cathode
A_cathode = pi * D * L; 

% Current vector
I_effective=zeros(1, length(T));

%% Sweeping temperature
% Parameter to sweep
T = linspace(293.15,2500, 1000); % Temperature of the cathode (K)

for n=1:length(T)
    J = A_Richardson * T(n)^2 * exp(-phi / (k * T(n)));
    I_emission = J * A_cathode; 
    I_space_charge_grid = (4 * epsilon_0 / 9) * sqrt(2 * e / m) * A_cathode * ((Vg-Vs)^(3/2) / (d-dg)^2 + (Vp-Vs)^(3/2) / d^2);
    mean_free_path = (k * T(n)) / (sqrt(2) * pi * sigma * p);
    collision_factor = exp(-d / mean_free_path);
    I_effective(n) = min(I_emission, I_space_charge) * collision_factor;
end

figure
plot(T, I_effective*1000, 'LineWidth',2,'Color','#0072BD');
grid("minor"),grid("on")
xlabel("Cathode temperature (K)"),ylabel("Anode current (mA)")
T = 2500;

%% Sweeping anode voltage

Vp=linspace(Vg, 100, 1000);

for n=1:length(Vp)
    J = A_Richardson * T^2 * exp(-phi / (k * T));
    I_emission = J * A_cathode; 
    I_space_charge_grid = (4 * epsilon_0 / 9) * sqrt(2 * e / m) * A_cathode * ((Vg-Vs)^(3/2) / (d-dg)^2 + (Vp(n)-Vs)^(3/2) / d^2);
    mean_free_path = (k * T) / (sqrt(2) * pi * sigma * p);
    collision_factor = exp(-d / mean_free_path);
    I_effective(n) = min(I_emission, I_space_charge) * collision_factor;
end

figure
plot(Vp, I_effective*1000, 'LineWidth',2,'Color','#0072BD');
grid("minor"),grid("on")
%ylim([0 1e-1])
xlabel("Anode voltage (V)"),ylabel("Anode current (mA)")
Vp=60;

%% Sweeping grid voltage
Vg=linspace(0, 2000, 1000);

for n=1:length(Vp)
    J = A_Richardson * T^2 * exp(-phi / (k * T));
    I_emission = J * A_cathode; 
    I_space_charge_grid = (4 * epsilon_0 / 9) * sqrt(2 * e / m) * A_cathode * ((Vg(n)-Vs)^(3/2) / (d-dg)^2 + (Vp-s)^(3/2) / dg^2);
    mean_free_path = (k * T) / (sqrt(2) * pi * sigma * p);
    collision_factor = exp(-d / mean_free_path);
    I_effective(n) = min(I_emission, I_space_charge) * collision_factor;
end

figure
plot(Vg, I_effective*1000, 'LineWidth',2,'Color','#0072BD');
grid("minor"),grid("on")
%ylim([0 1e-1])
xlabel("Grid voltage (V)"),ylabel("Anode current (mA)")
Vg=1000;