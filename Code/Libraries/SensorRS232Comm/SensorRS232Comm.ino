#include "SensorRS232Comm.h"

double PressureValue = 0.0;

ITR090 pressSensor(Serial2);

void setup(){
  pressSensor.init();
}
void loop(){
  PressureValue = pressSensor.readPressure();
}

//sólo falta probar el código funcionalmente en el arduino