#include "SensorRS232Comm.h"

// Definition of array size to store received data
byte receivedData[9] = {0}; // Array to store data received from the sensor

// Variables for pressure calculation
double Value = 0.0; // Variable to store the pressure value
byte highByte; // Higher-order byte received from the sensor
byte lowByte; // Lower-order byte received from the sensor

// Variables for time interval control
const int PresSenInterval = 40; // Time interval between pressure sensor readings (in milliseconds)
unsigned long PreviousPresSenMillis = 0; // Time in milliseconds of the last moment the sensor was read
const unsigned long ReceivedRS232Interval = 20; // Time interval between data received via RS232 (in milliseconds)
unsigned long lastReceivedRS232Millis = 0; // Time in milliseconds of the last moment data was received via RS232

// Constructor for the ITR090 class
ITR090::ITR090(HardwareSerial &port) : serialPort(port) {
  init(); // Initialize serial communication
  int chain_size=5;
  byte unit_command[chain_size]={3,16,62,0,78}; // Sets mbar as unit
  for(int i=0; i<chain_size; i++){
    serialPort.write(unit_command[i]);
  }
}

// Initialize serial communication
void ITR090::init() {
  serialPort.begin(9600); // Start serial communication with a baud rate of 9600
}

// Method to read pressure
double ITR090::readPressure() {
  // Check if at least 9 bytes are available in the input buffer
  if (serialPort.available() >= 9) {
    static int i = 0; // Static variable to control loop index
    
    byte foolByte = serialPort.read(); // Read a byte from the input buffer and store it in foolByte
    /*
    Serial.print("fool byte: ");
    Serial.println(foolByte);
    Serial.print("data: ");
    for (i = 0; i < 8; i++) {
      receivedData[i] = serialPort.read();
      Serial.print(receivedData[i]);
      Serial.print(" ");
    }
    Serial.println(" ");
    */

    // Check if enough time has passed since the last sensor reading
    if (millis() - PreviousPresSenMillis >= PresSenInterval) {
      byte mesByte = foolByte; // Corresponds to the first byte that should be received (length of data string)
      int sum=0;
      float used_sum=0;
      int a=0;
      float b=0;
      float to_add=0;
      for (i = 0; i < 7; i++) {
        receivedData[i] = serialPort.read();
        sum=sum+receivedData[i];
      }
      receivedData[7] = serialPort.read();
      for(i=0; i<8; i++){
        used_sum+=int(bitRead(sum, i))*pow(2,i);
      }
      
      // Check if the byte received from the sensor is equal to 7
      if ((mesByte == 7)&& (receivedData[0]==5)&&(abs(used_sum-float(receivedData[7]))<0.01) && (millis() - lastReceivedRS232Millis >= ReceivedRS232Interval)) {
        /*
        Serial.print("ITR 90 sensor synchronized. Received data: ");
        Serial.print(mesByte);
        Serial.print(" ");
        for (i = 0; i < 8; i++) {
          Serial.print(receivedData[i]);
          Serial.print(" ");
        }
        Serial.println(" ");
        */
        highByte = receivedData[3]; // Store the higher-order byte in highByte
        lowByte = receivedData[4]; // Store the lower-order byte in lowByte
        /*
        Serial.print("Used sum: ");
        Serial.println(used_sum);
        Serial.print("Check sum: ");
        Serial.println(float(receivedData[7]));
        Serial.println(used_sum-float(receivedData[7]));
        */
        
        lastReceivedRS232Millis += ReceivedRS232Interval; // Update the time of the last RS232 reception
      }
      sum=0;
      used_sum=0;
      
      // Reset the receivedData array to receive new data
      memset(receivedData, 0, sizeof(receivedData));
      
      // Check if the high and low bytes have been received
      if (highByte != 0 && lowByte != 0) {
        // Calculate the pressure value using the received bytes
        Value = pow(10.0, ((float(highByte) * 256 + float(lowByte)) / 4000 - 12.5));
        
        PreviousPresSenMillis += PresSenInterval; // Update the time of the last sensor reading
        return Value; // Return the pressure value
      } else {
        PreviousPresSenMillis += PresSenInterval; // Update the time of the last sensor reading
      }
    }
  }
}