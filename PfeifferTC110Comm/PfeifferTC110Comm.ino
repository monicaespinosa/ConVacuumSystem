#include "PfeifferTC110.h"

// Arduino pins
const int ENRS485Pin = 6;

TC110 turboPump(byte(ENRS485Pin), Serial3);

char command[COMMANDSIZE] = {0};
char outCommand[COMMANDSIZE] = {0};
char answer[COMMANDSIZE+1] = {0};
char paramStr[PARAMSIZE] = {0};

char debugInput;

bool changeStatus = false;
bool MotorPumpStatus = false;
bool BackPumpStatus = false;

bool setupVar = true;

const unsigned long checkInterval = 3000;
unsigned long lastCheckMillis = 0;
const unsigned long checkPressureInterval = 2000;
unsigned long lastCheckPressureMillis = 0;
const unsigned long setupInterval = 500;
unsigned long lastSetupMillis = 0;
const unsigned long ReadInterval = 17;
unsigned long lastReadMillis = 0;

int queryTurn = 0;

void setup() {
  turboPump.init();
  Serial.begin(9600); // debugging

}

void loop() {
  if(setupVar == true){
    if(millis() - lastSetupMillis >= setupInterval){ 
      turboPump.RS485Mode(WRITE);

      if(queryTurn == 0){
        Serial.println("Pumping station: ");
        instructConst(1, WRITE, param["PumpngStatn"], 1, command);
        queryTurn++;

      }else if(queryTurn == 1){
        Serial.println("Config Accessor A1: ");
        instructConst(1, WRITE, param["CfgAccA1"], 3, command);
        queryTurn++;

      }else if(queryTurn == 2){
        Serial.println("Config Accessor B1: ");
        instructConst(1, WRITE, param["CfgAccB1"], 6, command);
        queryTurn++;

      }else if(queryTurn == 3){
        Serial.println("Gas Mode: ");
        instructConst(1, WRITE, param["GasMode"], 1, command);
        queryTurn++;

      }else if(queryTurn == 4){
        Serial.println("Operation Mode Backing Pump: ");
        instructConst(1, WRITE, param["OpModeBKP"], 2, command);
        queryTurn++;

      }else if(queryTurn == 5){
        Serial.println("PV.can attached sensor name:");
        instructConst(1, READ, param["PrsSn1Name"], 0, command);
        queryTurn++;

      }else if(queryTurn == 6){
        Serial.println("Pressure sensor calibration factor:");
        instructConst(1, WRITE, param["PrsCorriP1"], (int)1.0*100, command);
        queryTurn++;

      }else if(queryTurn == 7){
        Serial.println("Motor turbo Pump: ");
        instructConst(1, WRITE, param["MotorPump"], 0, command);
        queryTurn = 0;
        setupVar = false;
      }
      
      turboPump.sendCommand(command);
      memset(command, 0, sizeof(command));
      
      lastSetupMillis += setupInterval;
    }
    
  }else if(setupVar == false){
    if(millis() - lastCheckMillis >= checkInterval){ 
      turboPump.RS485Mode(WRITE);
          
      if(queryTurn == 0){ 
        instructConst(1, READ, param["ActualSpd"], 0, command);
        queryTurn++;
      }else if(queryTurn == 1){
        instructConst(1, READ, param["TempElec"], 0, command);
        queryTurn++;
      }else if(queryTurn == 2){
        instructConst(1, READ, param["TempPmpBot"], 0, command);
        queryTurn++;
      }else if(queryTurn == 3){
        instructConst(1, READ, param["ErrorCode"], 0, command);
        queryTurn = 0;
      }

      turboPump.sendCommand(command);
      memset(command, 0, sizeof(command));

      lastCheckMillis += checkInterval;
    }

    if(millis() - lastCheckPressureMillis >= checkPressureInterval){ 
      turboPump.RS485Mode(WRITE);

      instructConst(1, READ, param["Pressure1"], 0, outCommand);
      //Serial.print("ITR 090: ");
      //Serial.print(PressureValue, 4);  
      //Serial.println(" mbar");
      
      turboPump.sendCommand(outCommand);

      memset(outCommand, 0, sizeof(outCommand));

      lastCheckPressureMillis += checkPressureInterval;
    }

  }

  if(millis() - lastReadMillis >= ReadInterval){
    turboPump.ReadRS485Serial(answer);
    if(getAnswerStat()) {
      turboPump.SaveAnswer(answer);
      changeAnswerStat();
    }
    
    lastReadMillis += ReadInterval;
  }

}

//================================================================== FUNCTIONS ======================================================
 
void serialEvent(){
  while(Serial.available()){
    debugInput = Serial.read();
    turboPump.RS485Mode(WRITE);
    if(debugInput == 'P'){
      MotorPumpStatus = !MotorPumpStatus;
      if(MotorPumpStatus == true) instructConst(1, WRITE, param["MotorPump"], 1, outCommand);
      else if(MotorPumpStatus == false) instructConst(1, WRITE, param["MotorPump"], 0, outCommand);
    }else if(debugInput == 'O'){
      BackPumpStatus = !BackPumpStatus;
      if(BackPumpStatus == true) instructConst(1, WRITE, param["OpModeBKP"], 0, outCommand);
      else if(BackPumpStatus == false) instructConst(1, WRITE, param["OpModeBKP"], 2, outCommand);
    }
    turboPump.sendCommand(outCommand);
    turboPump.RS485Mode(READ);
  }
}