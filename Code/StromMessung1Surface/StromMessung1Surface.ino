/*
  Pin connection: A9 to Out5 (black)
  Connect AREF to 3.3V and GND of the Arduino to GNDD
  Not connected to Arduino but present in setup: Purple (GNDA - VP), blue (3.3VD), green (GNDD)
*/

// Analog pins that measure voltage
const int analogPin = A10;
const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.3;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 2.0;  // Maximum current in mA
const float conv_factor=maxVoltage/maxCurrent;
int rawData;      // Store raw ADC values
float voltage;   // Store calculated voltages
float current;   // Store calculated currents

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
}

void loop() {
 
  // Read analog data
  rawData = analogRead(analogPin);
  voltage= rawData * (maxVoltage / 1023.0); // Convert to voltage

  // Map voltage to current
  if (voltage < minVoltage) {
      current = minCurrent;
  } else if (voltage > maxVoltage) {
      current = maxCurrent;
  } else {
      current = voltage / conv_factor; // Convert voltage to current (mA)
  }

  // Send data to Serial Plotter
  Serial.println(current);
  //Serial.print("\t");

  delay(150); // Delay between readings
}
