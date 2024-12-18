// This library uses as base the LiquidCrystal_i2c library 
#include <Arduino.h>
#include <SSD1803A_I2C.h>
#include<wire.h>
TwoWire Wire1;


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

const unsigned long checkInterval = 5000;
unsigned long lastCheckMillis = 0;

const unsigned long selInterval = 100;
unsigned long lastSelMillis = 0;

char debugInput;

int CursorPos = 0;
bool PumpStatus = false;
bool reset = HIGH;

SSD1803A_I2C lcd(i2cAddr, resetPin);
int arrow_state_test=0;

void setup(){
  
  Serial.begin(9600);

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
  // mock-up of functions to test the UI 
  if(millis() - lastCheckMillis >= checkInterval){
    PumpStatus = !PumpStatus;
    lastCheckMillis += checkInterval;
    //MenuScreen(!PumpStatus, PumpStatus);
    //TempScreen(30, 5, 120);
  }

  
  //TempScreen(30, 5, 120);
  // ***** State Machine *****
  arrow_state_change();
  screen_state_change();
  state_machine();
  //ArrowTest();
}

//========FUNCTIONS======
//This will be the main screen of the GUI
void PressureScreen(bool Status, double pressure1, int exp1, double pressure2, int exp2){
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
  lcd.print(pressure1, 3);
  lcd.locate(2, 7);
  lcd.print(pressure2, 3);
  
  lcd.locate(1, 12);
  lcd.print("E");
  lcd.print(exp1);
  lcd.locate(2, 12);
  lcd.print("E");
  lcd.print(exp2);

  lcd.locate(3,16);
  if(Status) lcd.print("ON");
  else lcd.print("OFF");
}

// if user presses the "Ok" button without an other action, 
// the menu will be displayed - function still not programmed
void ArrowTest(){
  if (arrow_state_test!=arrow_state) lcd.cls();
  lcd.locate(arrow_state, 19);
  lcd.write(0);
  arrow_state_test=arrow_state;
}

void MenuScreen(bool BStatus, bool PStatus){
  lcd.cls();
  //Serial.println("Hola");
  lcd.locate(arrow_state, 19);
  lcd.write(0);
  lcd.locate(0, 0);
  lcd.print("Turn ");
  
  if(BStatus) lcd.print("ON");
  else lcd.print("OFF");
  
  lcd.print(" Back. pump");

  lcd.locate(1, 0);
  lcd.print("Turn ");
  if(PStatus) lcd.print("ON");
  else lcd.print("OFF");
  lcd.print(" Turbo pump");
  
  lcd.locate(2, 0);
  lcd.print("Pump Temperature");

  lcd.locate(3, 0);
  lcd.print("Pump.Stat. settings");

}

void TempScreen(int EleTemp, int BearTemp, int MotTemp){
  //Serial.println("Starting Temp Screen");
  lcd.cls();

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
  lcd.locate(1, 0);
  lcd.print("    ");
  lcd.locate(2, 0);
  lcd.print("    ");

  for(int i = 0; i < 3; i++){
    lcd.locate(3, i);
    lcd.print(" ");
  }
}

void BestaetigungScreen(bool Status, int PumpNumber){ // PumpNumber is 0 for the back pump, 1 for the turbo pump
  Serial.println("Bestaetigung");
  lcd.cls();
  lcd.locate(0, 0);
  lcd.print("Turn ");
  
  if(Status) lcd.print("ON ");
  else lcd.print("OFF ");
  if(PumpNumber==0) lcd.print("Back Pump?");
  else lcd.print("Turbo Pump?");

  lcd.locate(2, 0);
  lcd.print("    ");
  lcd.locate(3, 0);
  lcd.print("    ");
}

void serialEvent(){
  while(Serial.available()){
    debugInput = Serial.read();
    if(debugInput == 'P'){
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
    Serial.print("Screen state: ");
    Serial.println(screen_state);
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
    int_2_activated=false;
    Serial.print("Arrow state: ");
    Serial.println(arrow_state);
  }
}

void state_machine(){
  switch (screen_state){
    case 0:
      PressureScreen(PumpStatus, 0.1, -3, 0.2, -4);
      break;
    case 1:
      MenuScreen(!PumpStatus, PumpStatus);
      break;
    case 2: 
      TempScreen(30, 5, 120);
      break;
    case 3:
      TempSettings();
      break;
    case 4:
      BestaetigungScreen(PumpStatus, 0); // Back Pump status goes in
      break;
    case 5:
      BestaetigungScreen(PumpStatus, 1); // Turbo Pump status goes in
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
