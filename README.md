# ConVacuumSystem
This is a project done at EST-RUB. Here is the control and interface of a vacuum system using a Pfeiffer turbo pump plus a backing pump

## Current circuit
The circuit (still to try) goes as following:

![Shaltung_aufbau](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/82b41dbd-6f89-4a12-b220-900301cfcae9)

The voltage of the grid (1 kV) must be increased from 0 V slowly to see the reaction of the environment to the voltage according to the pressure. The voltage of the Wehnelt cylinder is completely experimental.

## Current measurement
The current measurement stated in the last picture should be something like this:
![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/2cd917ea-59be-4fdb-9466-b059a0c22ddf)

The current flowing through R_mess is theorically expected to be in the microampere (µA) to milliampere (mA) range. Supposing that the current is 10mA, the following circuit was simulated to choose the value of R_mess:

<img width="325" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/c4272afb-3ed3-4a7b-beaf-601a9c627d06">

<img width="524" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/5fd1832b-1cab-482d-b7eb-067055c954de">

The voltage across Rm increases as Rm does. A value of Rm=140 ohm is temporarily chosen.




Proposals of instrumentation amplifiers are:

### 1. TMCS1100 (By Texas Instruments)
The TMCS1100 is a galvanically isolated Hall-effect current sensor capable of DC or AC current measuremen. The output voltage is proportional to the input current with four sensitivity options, which are shown in the next table:

<img width="537" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/e9c50c54-f587-4aef-983e-6dd9759625b7">

However the smalles current that this sensor is able to measure is 125 mA (for the TMCS1100A4). This also measures up to 12 A, which should be enough. Ordering number: TMCS1100A4QDR.
