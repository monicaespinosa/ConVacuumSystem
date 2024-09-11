// Interruption settings
#define UP 0
#define DOWN 1
#define OK 2
#define CANCEL 3
const byte interruptPin = 2;
const byte L0pin=7;
const byte L1pin=8;
int L0=0;
int L1=0;
int IntPinVal=0;

void setup() {
  Serial.begin(9600);
// Interruption settings
  pinMode(interruptPin, INPUT);
  pinMode(L0pin, INPUT);
  pinMode(L1pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruption, RISING);
}

void loop() {
// Testing
  //Serial.print("L0PinValue:");
  //Serial.println(digitalRead(L0pin));
}

void interruption(){
  Serial.println("Interruption activated");
  L0=digitalRead(L0pin);
  L1=digitalRead(L1pin);
  Serial.print("L0PinValue:");
  //Serial.println(digitalRead(L0pin));
  Serial.println(L0);
  Serial.print("L1PinValue:");
  //Serial.println(digitalRead(L1pin));
  Serial.println(L1);
  //L0=digitalRead(L0pin);
  //L1=digitalRead(L1pin);

  if ((L1==0)&&(L0==0)){
    Serial.println("UP button pressed");
  } else if ((L1==0)&&(L0==1)){
    Serial.println("DOWN button pressed");
  } else if ((L1==1)&&(L0==0)){
    Serial.println("OK button pressed");
  } else if ((L1==1)&&(L0==1)){
    Serial.println("CANCEL button pressed");
  }
}
