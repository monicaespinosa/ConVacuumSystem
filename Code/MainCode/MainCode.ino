#include "PfeifferTC110.h"
#include <Arduino.h>
#include <SSD1803A_I2C.h>
#include<wire.h>
#include "SensorRS232Comm.h"

TwoWire Wire1;

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

double PressureValue = 0.0; // ITR090 Pressure
ITR090 pressSensor(Serial2);


const unsigned long checkInterval = 3000;
unsigned long lastCheckMillis = 0;
const unsigned long checkPressureInterval = 2000;
unsigned long lastCheckPressureMillis = 0;
const unsigned long setupInterval = 500;
unsigned long lastSetupMillis = 0;
const unsigned long ReadInterval = 17;
unsigned long lastReadMillis = 0;

int queryTurn = 0;

// ================================= SCREEN ================================

const uint8_t i2cAddr = 0x3D;
const uint8_t resetPin = 5;
const uint8_t address_pin = 11;

// Interruption settings
const byte interruptPin = 2;
const byte L0pin=7;
const byte L1pin=8;
int L0=0;
int L1=0;

// ***** State machine *****
#define UP 0
#define DOWN 1
#define OK 2
#define CANCEL 3
int arrow_state=0; // arrow position
int last_arrow_state=3; // highest possible arrow position
int screen_state=0;
bool int_1_activated=false; // Screen state
bool int_2_activated=false; // Arrow state
int pressed_button=UP;

uint8_t SelectArrow[8] = {
  0b00000,
  0b00100,
  0b01100,
  0b11111,
  0b11111,
  0b01100,
  0b00100,
  0b00000
  };
uint8_t degree[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
  };


bool reset = HIGH;

SSD1803A_I2C lcd(i2cAddr, resetPin);
int arrow_state_test=0;

void setup() {
  turboPump.init();
  pressSensor.init();
  Serial.begin(9600); // debugging

  pinMode(address_pin, OUTPUT);
  digitalWrite(address_pin, HIGH);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, reset);
  lcd.begin(Wire1, DOGM204); 
  lcd.display(SET_ROM_B);

  lcd.create(0, SelectArrow);
  lcd.create(1, degree);

  // Interruption settings
  pinMode(interruptPin, INPUT);
  pinMode(L0pin, INPUT);
  pinMode(L1pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruption, RISING);
}

void loop() {
  PressureValue = pressSensor.readPressure(); // ITR090 read 
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
      Serial.print("RPT010 Sensor Pressure: ");
      Serial.print(param["Pressure1"].receivedValue); // presión 1 es lectura del sensor RPT010 (parte superior el montaje)
      Serial.println(" mbar");

      Serial.print("ITR090 Sensor Pressure: ");
      Serial.print(PressureValue);
      Serial.println(" mbar");
      
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

  // ***** Screen State Machine *****
  arrow_state_change();
  screen_state_change();
  state_machine();

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


// ______________________ Screen functions __________________________

//This will be the main screen of the GUI
void PressureScreen(char *Status, double pressure1, char *pressure2){
  lcd.cls();
  lcd.locate(0,0);
  lcd.print("Pressure");
  lcd.locate(1,0);
  lcd.print("ITR090:");
  lcd.locate(2,0);
  lcd.print("RPT010:");
  lcd.locate(3,0);
  lcd.print("Turbo pump:");

  lcd.locate(1,16);
  lcd.print("mbar");
  lcd.locate(2,16);
  lcd.print("mbar");

  lcd.locate(1, 7);
  lcd.print(pressure1, 4);
  lcd.locate(2, 7);
  lcd.print(pressure2);

  lcd.locate(3,16);
  if(strcmp(Status, "111111")==0) lcd.print("ON");
  else lcd.print("OFF");
}

void ArrowTest(){
  if (arrow_state_test!=arrow_state) lcd.cls();
  lcd.locate(arrow_state, 19);
  lcd.write(0);
  arrow_state_test=arrow_state;
}

// if user presses the "Ok" button without an other action, 
// the menu will be displayed

void MenuScreen(char *BStatus, char *PStatus){
  lcd.cls();
  //Serial.println("Hola");
  lcd.locate(0, 0);
  lcd.print("Turn ");
  
  if(strcmp(BStatus, "000")==0) lcd.print("ON"); // Check how the value is actually returned
  else lcd.print("OFF"); //if bstatus == 2
  
  lcd.print(" Back. pump");

  lcd.locate(1, 0);
  lcd.print("Turn ");
  if(strcmp(PStatus, "000000")) lcd.print("ON"); // Check how the value is actually returned
  else lcd.print("OFF");
  lcd.print(" Turbo pump");
  
  lcd.locate(2, 0);
  lcd.print("Pump Temperature");

  lcd.locate(3, 0);
  lcd.print("Pump.Stat. settings");

  lcd.locate(arrow_state, 19);
  lcd.write(0);
  /*
  for(int i = 0; i < 3; i++){
    lcd.locate(i, 18);
    lcd.write(1);
    lcd.print("C");
  }
  */
}

void TempScreen(char *Temp1, char *Temp2, char *Temp3){
  //Serial.println("Starting Temp Screen");
  lcd.cls();

  int EleTemp = atoi(Temp1);
  int BearTemp = atoi(Temp2);
  int MotTemp = atoi(Temp3);

  lcd.locate(0, 0);
  lcd.print("Electronics:");
  lcd.locate(1, 0);
  lcd.print("Bearings:");
  lcd.locate(2, 0);
  lcd.print("Motor:");

  if(EleTemp > 99)lcd.locate(0,15);
  else if((EleTemp > 9)&&(EleTemp<=99))lcd.locate(0,16);
  else if(EleTemp<10)lcd.locate(0,17);
  lcd.print(EleTemp);

  if(BearTemp > 99)lcd.locate(1,15);
  else if((BearTemp > 9)&&(BearTemp<=99))lcd.locate(1,16);
  else if(BearTemp<10)lcd.locate(1,17);
  lcd.print(BearTemp);

  if(MotTemp > 99)lcd.locate(2,15);
  else if((MotTemp > 9)&&(MotTemp<=99))lcd.locate(2,16);
  else if(MotTemp<10)lcd.locate(2,17);
  lcd.print(MotTemp);

  for(int i = 0; i < 3; i++){
    lcd.locate(i, 18);
    lcd.write(1);
    lcd.print("C");
  }  
}

void TempSettings(){
  lcd.cls();
  lcd.locate(0, 0);
  lcd.print("Temp settings");
}

void BestaetigungScreen(char *Status, int PumpNumber){ // PumpNumber is 0 for the back pump, 1 for the turbo pump
  lcd.cls();
  lcd.locate(0, 0);
  lcd.print("Turn ");
  
  if(strcmp(Status, "000")) lcd.print("ON "); // change as Status can be a char array of 3 or 6 characters 
  else lcd.print("OFF ");
  lcd.locate(1, 0);
  if(PumpNumber==0) lcd.print("Back Pump?");
  else lcd.print("Turbo Pump?");
}

void screenSerialEvent(){
  while(Serial.available()){
    debugInput = Serial.read();
    if(debugInput == 'RS'){
      reset = LOW;
      digitalWrite(resetPin, reset);
      delay(20);
      reset = HIGH;
      digitalWrite(resetPin, reset);
      lcd.locate(0,0);
      lcd.print("Reset");
    }
  }
}

void screen_state_change(){
  if (int_1_activated){
    switch (screen_state){
      case 0:
        if (pressed_button==OK){
          screen_state=1;
        } else {
          screen_state=0;
        }
        break;
      case 1:
        if (pressed_button==CANCEL){
          screen_state=0;
        } else if ((arrow_state==3)&&(pressed_button==OK)){
          screen_state=3;
        } else if ((arrow_state==0)&&(pressed_button==OK)){
          screen_state=4;
        } else if ((arrow_state==1)&&(pressed_button==OK)){
          screen_state=5;
        } else if ((arrow_state==2)&&(pressed_button==OK)){
          screen_state=2;
        } else{
          screen_state=1;
        }
        break;
      case 2:
        if ((pressed_button==OK)||(pressed_button==CANCEL)){
          screen_state=1;
        } else {
          screen_state=2;
        }
        break;
      case 3:
        if ((pressed_button==OK)||(pressed_button==CANCEL)){
          screen_state=1;
        } else {
          screen_state=3;
        }
        break;
      case 4:
        if ((pressed_button==OK)||(pressed_button==CANCEL)){
          screen_state=1;
        } else {
          screen_state=4;
        }
        break;
      case 5:
        if ((pressed_button==OK)||(pressed_button==CANCEL)){
          screen_state=1;
        } else {
          screen_state=5;
        }
        break;
      default:
        screen_state=0;
        break;
    }
    int_1_activated=false;
  }
}

void arrow_state_change(){
  if (int_2_activated){
    switch (pressed_button){
      case UP:
        if (arrow_state!=0) {
          arrow_state=arrow_state-1;
        }
        break;
      case DOWN:
        if (arrow_state!=last_arrow_state){
          arrow_state=arrow_state+1;
        }
        break;
    }
  }
  int_2_activated=false;
}

void state_machine(){
  switch (screen_state){
    case 0:
      PressureScreen(param["PumpngStatn"].receivedValue, PressureValue, param["Pressure1"].receivedValue);
      break;
    case 1:
      MenuScreen(param["OpModeBKP"].receivedValue, param["MotorPump"].receivedValue);
      break;
    case 2: 
      TempScreen(param["TempElec"].receivedValue, param["TempMotor"].receivedValue, param["TempPmpBot"].receivedValue);
      break;
    case 3:
      TempSettings();
      break;
    case 4:
      BestaetigungScreen(param["OpModeBKP"].receivedValue, 0); // Back Pump status goes in
      break;
    case 5:
      BestaetigungScreen(param["MotorPump"].receivedValue, 1); // Turbo Pump status goes in
      break;
  }
}

void interruption(){
  Serial.println("Interruption activated");
  L0=digitalRead(L0pin);
  L1=digitalRead(L1pin);

  if ((L1==0)&&(L0==0)){
    pressed_button=UP;
    //Serial.println("UP");
    int_2_activated=true;
  } else if ((L1==0)&&(L0==1)){
    pressed_button=DOWN;
    //Serial.println("DOWN");
    int_2_activated=true;
  } else if ((L1==1)&&(L0==0)){
    pressed_button=OK;
    //Serial.println("OK");
    int_1_activated=true;
  } else if ((L1==1)&&(L0==1)){
    pressed_button=CANCEL;
    //Serial.println("CANCEL");
    int_1_activated=true;
  }
}
