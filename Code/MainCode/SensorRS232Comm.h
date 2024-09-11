#ifndef SENSORRS232COMM_H
#define SENSORRS232COMM_H
#include <Arduino.h>

class ITR090{
  private:
  HardwareSerial &serialPort;

  public:
  ITR090(HardwareSerial &port);
  void init();
  double readPressure();

};

#endif