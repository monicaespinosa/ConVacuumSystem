// Interruption settings
#define UP 0
#define DOWN 1
#define OK 2
#define CANCEL 3
const byte interruptPin = 3;
const byte Y0pin=7;
const byte Y1pin=8;
int Y0=0;
int Y1=0;
int IntPinVal=0;

void setup() {
  Serial.begin(9600);
// Interruption settings
  pinMode(interruptPin, INPUT);
  pinMode(Y0pin, INPUT);
  pinMode(Y1pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruption, FALLING);
}

void loop() {
// Testing
  //Serial.print("IntPinValue:");
  //Serial.println(digitalRead(interruptPin));
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
