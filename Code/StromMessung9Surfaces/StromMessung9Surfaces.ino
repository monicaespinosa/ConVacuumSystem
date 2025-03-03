// Analog pins that measure voltage
const int analogPins[9] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};

const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.3;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 5.0;  // Maximum current in mA
int rawData[9];      // Store raw ADC values
float voltages[9];   // Store calculated voltages
float currents[9];   // Store calculated currents

void setup() {
  Serial.begin(9600);
  
  // Set all pins as input
  for (int i = 0; i < 9; i++) {
    pinMode(analogPins[i], INPUT);
  }
}

void loop() {

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
        currents[i] = voltages[i] / 0.66; // Convert voltage to current (mA)
    }
  }

  // Send data to Serial Plotter
  for (int i = 0; i < 9; i++) {
    Serial.print(currents[i]);
    if (i < 8) Serial.print("\t"); // Separate values with tabs except the last one
  }
  Serial.println(); // New line to indicate end of row

  delay(150); // Delay between readings
}
