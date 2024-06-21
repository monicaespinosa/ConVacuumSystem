# ConVacuumSystem
This is a project done at EST-RUB. Here is the control and interface of a vacuum system using a Pfeiffer turbo pump plus a backing pump

## Current circuit
The circuit (still to try) goes as following:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/7b1d19c1-73f9-4d2d-945e-82eee775d735)

The setup still has to be simulated to find out V_c and to check the accuracy of the voltages selected for the grid and the plate.

## CST Simulations of the setup
The following setup was simulated:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/405f0f8f-9f3f-49e9-9c0a-5f4630cc735f)

Initially were the following voltages set:
* V_S 6.4 V
* V_C: 6.4 V
* V_G= 400 V
* V_P= 1000 V

The result for the obtained trajectory is shown below. The obtained current was around 5 mA.

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/585d3c0f-d25d-47a4-b070-d8ddf82cefa9)

However, the shape of the electron beams seems to change its shape in a very drastic way. Making the V_C smaller (more negative) should help concentring more the electrons to the center of the beam. A second simulation was made sweeping the voltage of the Wehnelt_Cylinider between -10 V and 6 V. 

As a result, the following charges on the plate were obtained:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/0f343619-c491-4c79-ba3d-49d591911f32)

Particles that come out of the coil:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/9a4e5f58-5a77-4f0c-96a8-2432bd74582c)

They are only high when the voltage at the Wehnelt Cylinider is equal or higher than that of the coil. A new simulation sweeping Vc between 6.4V and 15.4V is been made. Results:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/b6012328-200f-4f13-b67d-3d578c54f5ee)

Evidently, the current (and as a consequence the particles getting to the plate) exists only when V_C>=V_S. The trajectories of the particles change however as they seem to be pushed into the cylinder (because of the higher voltage):

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/3ac7468e-0a58-4944-a271-e15e163a092a)

A final simulation setting the voltage on the grid V_G=800 V, putting a porcelain cylinder around the components (to simulate the glass cylinider) and moving the cylinider along the z-axis was made. The obtained trajectories are:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/9e56299d-0ae6-4a87-bfa8-3b75c5c7e106)




## Current measurement
The current measurement stated in the last picture should be something like this:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/2cd917ea-59be-4fdb-9466-b059a0c22ddf)

The current flowing through R_mess is theorically expected to be around 5mA according to the simulations. Supposing that the current is 10mA, the following circuit was simulated to choose the value of R_mess:

<img width="325" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/c4272afb-3ed3-4a7b-beaf-601a9c627d06">

<img width="524" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/5fd1832b-1cab-482d-b7eb-067055c954de">

The voltage across Rm increases as Rm does. A value of Rm=140 ohm is temporarily chosen.




Proposals of instrumentation amplifiers are:

### 1. TMCS1100 (By Texas Instruments)
The TMCS1100 is a galvanically isolated Hall-effect current sensor capable of DC or AC current measuremen. The output voltage is proportional to the input current with four sensitivity options, which are shown in the next table:

<img width="537" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/e9c50c54-f587-4aef-983e-6dd9759625b7">

However the smalles current that this sensor is able to measure is 125 mA (for the TMCS1100A4). This also measures up to 12 A, which should be enough. Ordering number: TMCS1100A4QDR.

### 2. INA333-Q1 (By Texas Instruments)
The INA333-Q1 is a low-power, precision instrumentation amplifier, planned to be used as follows:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/99451df2-63c0-4bd9-bc2b-bc0e11a4809a)


The inside schematic of the INA333-Q1:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/315523b2-8e44-4ad4-ba65-47afb34f9fd2)

Some specifications:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/2ab0eaf7-e3f6-4b9a-9a2c-f7bf84dbed0c)

A LTSpice simulation was done to verify the gain of the device. However the results were not exactly what is expected. Additionals simulations should be done. The file is though attached in this repository as "Draft2.asc".


