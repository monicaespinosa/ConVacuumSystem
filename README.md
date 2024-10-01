<<<<<<< HEAD
# ConVacuumSystem
This is a project done at EST-RUB. Here is the control and interface of a vacuum system using a Pfeiffer turbo pump plus a backing pump
=======
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

A new simulation setting the voltage on the grid V_G=800 V, putting a porcelain cylinder around the components (to simulate the glass cylinider) and moving the cylinider along the z-axis was made. The obtained trajectories are:

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/9e56299d-0ae6-4a87-bfa8-3b75c5c7e106)

### Setting the voltage on the plate nearly to 0
Simulation with V_G = 1000 V and V_P = 4 V, and moving the cylinder to its initial position.

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/793896a4-7309-4a5e-bfd4-4e4e9c879427)

Simulation with the same parameters but moving the cylinder so its positioned closer to the plate.

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/8421cdd1-d5c9-4222-9ab9-39f22e9a9367)

Final simulation moving the cylinder back again and setting its voltage to -V_S.

![image](https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/66730606-2f4f-4ead-8a13-c946194bcbe8)


### Changing the cathode
For all the following simulations the following voltages are set: V_S=6.4V, V_C=-30V V_G = 1000V and V_P = 4V.

#### Vertical filled PEC cylinder
Model:

![image](https://github.com/user-attachments/assets/e61b0fd6-4c1f-4cc4-9087-67172321c731)


Trajectories:

![image](https://github.com/user-attachments/assets/9c09d741-97e4-4676-9c34-4f3a57b2470d)

Total current leaving the cathode: 1.191e-03 mA

### Vertical hollow PEC cylinder
The cathode looks like the one before but is hollow with a thickness of 0.3 mm.

Trajectories:

![image](https://github.com/user-attachments/assets/270f2000-f85e-44ef-9f3f-197fb305d620)

Total current leaving the cathode: 9.14e-02 mA

### Toroid
Model:

![image](https://github.com/user-attachments/assets/f4135615-c0ba-41a9-936d-de7f47c87b61)


Trajectories:

![image](https://github.com/user-attachments/assets/9688a467-bd68-4305-8b6f-8bfdfb9ad18a)


Total current leaving the cathode: 0.98 mA

### Rectangular cathode:
Model:

![image](https://github.com/user-attachments/assets/23e1c267-47ab-49bb-8cb7-2b3cd2cd397a)

Trajectories: 

![image](https://github.com/user-attachments/assets/a28f8327-6b3a-445f-8212-ae7b98d6d767)


Total current leaving the cathode: 0.78 mA

### Sphere
Model:

![image](https://github.com/user-attachments/assets/7cd68f25-79ad-4122-af77-de3036f23be3)

Trajectories:

![image](https://github.com/user-attachments/assets/14dc5615-78e2-4bb4-8abf-378560cff7c1)

Total current leaving the cathode: 1.19 mA


### cut Cone:
Model:

![image](https://github.com/user-attachments/assets/3869cedd-592c-41d6-9c5a-cb8cb0bd5b5a)

It didn't emit any current when being put this way. However, when rotating like this:

![image](https://github.com/user-attachments/assets/fbbe51be-5a77-4e12-8e6d-319d640f8fb3)

The following trajectories are gotten:

![image](https://github.com/user-attachments/assets/f6d17da3-f0b4-4fc1-9a01-1928ba956ee3)

Total current leaving the cathode: 0.71 mA



### Electron-gun Cathode
Model: 

![image](https://github.com/user-attachments/assets/387a45cd-ee46-4143-996c-e5277fd2d165)

It's a "cone" whose two planar circular faces are connected not by a rotated linear surface but a rotated exponential surface so it's internal radious get's thicker in an exponential way along the w axis as w decreases, simulating a pointy trunked cone. It was initially made small but only few particles were accelerated. Increasing its size and getting it closer to the grid produces the following trajectories:

![image](https://github.com/user-attachments/assets/b7cdce4d-d196-4516-bc6c-9664a834d68a)

The total current leaving the cathode was 9.35 mA. However the trajectories are messy and very disperse. After trying to move both the cathode and the grid further from the plate, because of the Wehnelt-Cylinder, the particles collide and then get dispersed again, without reaching the plate:

![image](https://github.com/user-attachments/assets/e6b2280f-2e24-4ba2-a903-8bd35732bebd)


### Toroid-Coil

Moldel:

![image](https://github.com/user-attachments/assets/4dc83fb6-3ac4-4320-a37f-b22c323c6896)

This toroid model was created using one of the predesigned macros of CST. However, each ring is made of small faces (in total 10000 for the whole coil), which made necessary to create a macro to select all faces in order to create a particle source out of the whole coil. The simulation results after making that are however dissapointing, the particles don't seem to be leaving the coil.

![image](https://github.com/user-attachments/assets/7731663e-2d4a-4e85-9636-51586dacb107)



## Current measurement

### Methode
As mentioned before, this is the electrical structure of the setup:

<img width="713" alt="image" src="https://github.com/user-attachments/assets/4841e218-f58f-4549-badb-dc8962dc0f3e">

The current measurement in between the plate and the voltage source V_p is more detailed here:

<img width="722" alt="image" src="https://github.com/user-attachments/assets/d1c168d9-1486-4fde-a79a-fc2c6efaeaeb">

The current flowing through R_mess is theorically expected to be around 5mA according to the simulations. Supposing that the current is 10mA, the following circuit was simulated to choose the value of R_mess:

<img width="325" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/c4272afb-3ed3-4a7b-beaf-601a9c627d06">

<img width="524" alt="image" src="https://github.com/monicaespinosa/ConVacuumSystem/assets/42346349/5fd1832b-1cab-482d-b7eb-067055c954de">

The voltage across Rm increases as Rm does. A value of Rm=140 ohm is temporarily chosen.

The following component is a amplifier that measures the voltage across the resistor R_mess and whose output is a digital signal whose amount of 1's is proportional to the current flowing through R_mess. The used amplifier is the Si8946A, that measures voltages between -62.5 mV and +62.5 mV, and whose output has a frequency of 10MHz. As this frequency is too high for a microcontroller like Arduino to read, a phase of signal conditioning is required. The simple RC filter produces an analog signal which corresponds to an average value of the quantity of 1's contained in the digital output of the amplifier. As this output is either a 0 or a 1, the analog response of the filter varies between 0V to 1V. However, as we intend to read this signal with Arduino, in order to take of advantage of all its measuring range the to-be-measured signal should be in the full range of 0V to 5V. This is the reason why an additional operational amplifier with a gain of 5 is used. The amplifier corresponds to the TLV9001 by Texas Instruments.

### PCB

The whole circuitry mentioned above, intended to be used for measuring the current caused by the electrons colliding into the plate and further flowing through R_mess, will be designed to be as close as posible to the plate. As not only the amount of current is important, but also the distribution of the electrons along the plate, this last is eventually going to be divided into many smaller plates whose incoming current will be measured separatedly. The first PCB designed to try the measuring circuitry has three plates. The PCB has two layers, one of them containing the plates

<img width="662" alt="image" src="https://github.com/user-attachments/assets/86f72270-88e2-4e12-a0b2-40b716db98b5">


and the other one the Si8946A amplifiers and the connector in charge of providing feeding voltage and of letting the signals out. 

<img width="607" alt="image" src="https://github.com/user-attachments/assets/2878375b-a1f5-40e5-b306-f3c0a488b9eb">

To know if the digital signal at 10 MHz is able to be carried by a normal jumper cable without using a SMA connector, some calculations need to be made:

Let's assume a square wave and use Bogatins rule of thumb [here](https://www.edn.com/rule-of-thumb-1-bandwidth-of-a-signal-from-its-rise-time/). According to the datasheet, the rise time is 20ns. The bandwidth of such a signal is 50 MHz, whose wavelength in free space is 6m, let's say 3m in the PCB. At 1/10th wavelength that's 30cm, which sets the upper limit to the jumper wire's length. 

Another option is to attach a second PCB using a PCB to PCB connector. 






>>>>>>> main
