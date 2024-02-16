#include "SensorRS232Comm.h"

byte receivedData[9]={0}; // 
double Value = 0.0;
byte highByte;
byte lowByte;

// Interval managing variables
const int PresSenInterval = 2500;
unsigned long PreviousPresSenMillis = 0;
const unsigned long ReceivedRS232Interval = 20;
unsigned long lastReceivedRS232Millis = 0;

ITR090::ITR090(HardwareSerial &port):serialPort(port){
  init();
} 
void ITR090::init(){
  serialPort.begin(9600);
}

double ITR090::readPressure(){
  if(serialPort.available() >= 9){
    static int i = 0;
    byte foolByte = serialPort.read();

    if(millis() - PreviousPresSenMillis >= PresSenInterval){
      byte mesByte = foolByte;
      
      if((mesByte==7) && (millis() - lastReceivedRS232Millis >= ReceivedRS232Interval)){
        for(i = 0; i < 8; i++){
          receivedData[i] = serialPort.read();
        }
        highByte = receivedData[3];
        lowByte = receivedData[4]; 

        lastReceivedRS232Millis += ReceivedRS232Interval;
      }
      memset(receivedData, 0, sizeof(receivedData));

      if(highByte != 0 && lowByte != 0){
        Value = pow(10.0, (( float(highByte) * 256 + float(lowByte) ) / 4000 - 12.5));
        PreviousPresSenMillis += PresSenInterval;
        return Value;
      }else PreviousPresSenMillis += PresSenInterval;
    }
    
  }
}