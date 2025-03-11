/*
  Pin connection                 A0   -   A1  -  A2 -   A3   -   A4   -   A5      -     A6   -  A7  -  A8
  Colors: (lowerside)           black - brown - red - orange - yellow - green, (upper) white - gray - yellow
  Equivalent output: (lowerside) Out5 - Out6  - Out3 - Out2  -  Out7  - Out1, (upper)  Out4 -  Out9 -  Out8
  Equivalent surface: (lowerside) DoLe - DoCe - UpRi - CeRi  -  UpCe -  CeCe, (upper)  DoRi -  UpLe - CeLe
  Connect AREF to 3.3V
  Not connected to Arduino but present in setup: Purple (GNDA - VP), blue (3.3VD), green (GNDD)
*/

// Analog pins that measure voltage
//const int analogPins[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};
const int analogPins[9] = {A5, A3, A2, A6, A0, A1, A4, A8, A7}; // In order (Out 1, Out2, ..., Out9)
const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.0;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 5.0;  // Maximum current in mA
int rawData[9];      // Store raw ADC values
float voltages[9];   // Store calculated voltages
float currents[9];   // Store calculated currents
float total_current=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Total	CenCen	CenRig	UpRig	DowRig	DowLef	DowCen	UpCen	CenLef	UpLef"); // Set graph names
  
  // Set all pins as input
  for (int i = 0; i < 9; i++) {
    pinMode(analogPins[i], INPUT);
  }
}

void loop() {
  total_current=0;

  // Read analog data
  for (int i = 0; i < 9; i++) {
    rawData[i] = analogRead(analogPins[i]);
    voltages[i] = rawData[i] * (maxVoltage / 1023.0); // Convert to voltage

    // Map voltage to current
    if (voltages[i] < minVoltage) {
        currents[i] = minCurrent;
    } else if (voltages[i] > maxVoltage) {
        currents[i] = maxCurrent;
    } else {
        currents[i] = voltages[i] / 13.5; // Convert voltage to current (mA)
    }
    total_current+=currents[i];
  }

  for (int i = 0; i < 9; i++) {
    Serial.print(currents[i], 3);  // 3 decimals
    Serial.print(",");
  }
  Serial.println(total_current, 3);  // total current

  delay(150);
}

