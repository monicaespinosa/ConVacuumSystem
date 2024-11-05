const int analogPin = A0; // analog pin that measures voltage
const float minVoltage = 0.05; // Minimum voltage in volts (50mV)
const float maxVoltage = 3.3;  // Maximum voltage in volts
const float minCurrent = 0.0;  // Minimum current in mA
const float maxCurrent = 5.0;  // Maximum current in mA

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
}

void loop() {
  int analogValue = analogRead(analogPin);
  float voltage = analogValue * (5.0 / 1023.0); // Convert the 0-1023 value to 0-5V
  
  // Map the voltage to current
  float current;
  if (voltage < minVoltage) {
    current = minCurrent; // If below 50mV, set current to 0mA
  } else if (voltage > maxVoltage) {
    current = maxCurrent; // If above 3.3V, set current to 5mA
  } else {
    current = (voltage - minVoltage) * (maxCurrent - minCurrent) / (maxVoltage - minVoltage) + minCurrent;
  }

  Serial.print("Measured voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Equivalent current: ");
  Serial.print(current);
  Serial.println(" mA");

  delay(500); // Wait 500 ms before the next reading
}
