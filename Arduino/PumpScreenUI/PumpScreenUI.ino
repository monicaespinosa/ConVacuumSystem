// This library uses as base the LiquidCrystal_i2c library 
#include <Arduino.h>
#include <SSD1803A_I2C.h>
#include<wire.h>
TwoWire Wire1;


const uint8_t i2cAddr = 0x3D;
const uint8_t resetPin = 5;
const uint8_t address_pin = 11;

// Interruption settings
#define UP 0
#define DOWN 1
#define OK 2
#define CANCEL 3
const byte interruptPin = 2;
const byte Y0pin=7;
const byte Y1pin=8;
int Y0=0;
int Y1=0;
int IntPinVal=0;


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
  pinMode(Y0pin, INPUT);
  pinMode(Y1pin, INPUT);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), interruption, FALLING);

}

void loop() {
  // mock-up of functions to test the UI 
  if(millis() - lastCheckMillis >= checkInterval){
    PumpStatus = !PumpStatus;
    lastCheckMillis += checkInterval;
  }
  if(millis() - lastSelMillis >= selInterval){
    CursorPos ++;
    if (CursorPos == 4) CursorPos = 0;
    lastSelMillis += selInterval;
  }
  //MenuScreen(!PumpStatus, PumpStatus, CursorPos);
  TempScreen(30, 5, 120);
  //delay(500);

}

//========FUNCTIONS======
//Ths will be the main screen of the GUI
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
void MenuScreen(bool BStatus, bool PStatus, int CursorRow){
  lcd.cls();

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

  lcd.locate(CursorRow, 19);
  lcd.write(0);
}

void TempScreen(int EleTemp, int BearTemp, int MotTemp){
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

void interruption(){
  Serial.println("Interruption activated");
  Y0=digitalRead(Y0pin);
  Y1=digitalRead(Y1pin);
  Serial.println(digitalRead(interruptPin));

  if ((~Y1)&&(~Y0)){
    //Serial.println("UP button pressed");
  } else if ((~Y1)&&Y0){
    //Serial.println("DOWN button pressed");
  } else if (Y1&&(~Y0)){
    //Serial.println("OK button pressed");
  } else if (Y1&&Y0){
    //Serial.println("CANCEL button pressed");
  }
}