// analog pins that measures voltage
const int analogPin0 = A0; 
const int analogPin1 = A1; 
const int analogPin2 = A2; 

const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.3;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 5.0;  // Maximum current in mA

void setup() {
  Serial.begin(9600);
  pinMode(analogPin0, INPUT);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
}

void loop() {
  // Read data
  int data0 = analogRead(analogPin0);
  int data1 = analogRead(analogPin1);
  int data2 = analogRead(analogPin2);

  // Find voltage
  float vol0 = data0 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  float vol1 = data1 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  float vol2 = data2 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  
  // Map the voltage to current
  float voltages[3] = {vol0, vol1, vol2};
  float currents[3];

  float voltages[3] = {vol0, vol1, vol2};
  float currents[3];

  for (int i = 0; i < 3; i++) {
      if (voltages[i] < minVoltage) {
          currents[i] = minCurrent;
      } else if (voltages[i] > maxVoltage) {
          currents[i] = maxCurrent;
      } else {
          currents[i] = voltages[i]/0.66; // mA
      }

      // Send data to Serial Plotter
      Serial.print(vol0);
      Serial.print("\t");  // Tab separates the values
      Serial.print(vol1);
      Serial.print("\t");
      Serial.println(vol2); // Newline ends the row
  }


  delay(150); // Wait 250 ms before the next reading
}
