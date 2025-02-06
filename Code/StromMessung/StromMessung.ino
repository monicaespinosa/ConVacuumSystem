// analog pins that measures voltage
const int analogPin1 = A0; 
const int analogPin2 = A1; 
const int analogPin3 = A2; 

const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.3;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 5.0;  // Maximum current in mA

void setup() {
  Serial.begin(9600);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(analogPin3, INPUT);
}

void loop() {
  // Read data
  int data1 = analogRead(analogPin1);
  int data2 = analogRead(analogPin2);
  int data3 = analogRead(analogPin3);

  // Find voltage
  float vol1 = data1 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  float vol2 = data2 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  float vol3 = data3 * (maxVoltage / 1023.0); // Convert the 0-1023 value to 0 - max. voltage
  
  // Map the voltage to current
  float voltages[3] = {vol1, vol2, vol3};
  float currents[3];

float voltages[3] = {vol1, vol2, vol3};
float currents[3];

  for (int i = 0; i < 3; i++) {
      if (voltages[i] < minVoltage) {
          currents[i] = minCurrent;
      } else if (voltages[i] > maxVoltage) {
          currents[i] = maxCurrent;
      } else {
          currents[i] = (voltages[i] - minVoltage) * (maxCurrent - minCurrent) / (maxVoltage - minVoltage) + minCurrent;
      }

      // Optimized printing
      Serial.print("Measured voltage ");
      Serial.print(i + 1);  // Prints the sensor number
      Serial.print(": ");
      Serial.print(voltages[i]);
      Serial.print(" V, Equivalent current: ");
      Serial.print(currents[i]);
      Serial.println(" mA");
  }


  delay(250); // Wait 250 ms before the next reading
}
