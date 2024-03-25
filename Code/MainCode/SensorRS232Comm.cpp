#include "SensorRS232Comm.h"

// Definition of array size to store received data
byte receivedData[9] = {0}; // Array to store data received from the sensor

// Variables for pressure calculation
double Value = 0.0; // Variable to store the pressure value
byte highByte; // Higher-order byte received from the sensor
byte lowByte; // Lower-order byte received from the sensor

// Variables for time interval control
const int PresSenInterval = 2500; // Time interval between pressure sensor readings (in milliseconds)
unsigned long PreviousPresSenMillis = 0; // Time in milliseconds of the last moment the sensor was read
const unsigned long ReceivedRS232Interval = 20; // Time interval between data received via RS232 (in milliseconds)
unsigned long lastReceivedRS232Millis = 0; // Time in milliseconds of the last moment data was received via RS232

// Constructor for the ITR090 class
ITR090::ITR090(HardwareSerial &port) : serialPort(port) {
  init(); // Initialize serial communication
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
    
    // Check if enough time has passed since the last sensor reading
    if (millis() - PreviousPresSenMillis >= PresSenInterval) {
      byte mesByte = foolByte; // Store the received byte from the sensor in mesByte
      
      // Check if the byte received from the sensor is equal to 7
      if ((mesByte == 7) && (millis() - lastReceivedRS232Millis >= ReceivedRS232Interval)) {
        // Read the next 8 bytes from the input buffer and store them in receivedData
        for (i = 0; i < 8; i++) {
          receivedData[i] = serialPort.read();
        }
        highByte = receivedData[3]; // Store the higher-order byte in highByte
        lowByte = receivedData[4]; // Store the lower-order byte in lowByte
        
        lastReceivedRS232Millis += ReceivedRS232Interval; // Update the time of the last RS232 reception
      }
      
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