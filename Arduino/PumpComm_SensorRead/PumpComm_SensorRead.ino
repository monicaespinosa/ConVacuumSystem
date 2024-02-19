#define READ 0
#define WRITE 1
#define PARAMSIZE 4

// Arduino pins
const int ENRS485Pin = 6; //RS-485 shield enable terminal, on arduino uno it would be digital port 2 using DFROBOT shield

const char endChar = '\r';  // ASCII character 13
// Setting Parameters
const char ErrorAckn[PARAMSIZE] = "009";
const char PumpgnStatn[PARAMSIZE] = "010";
const char CfgSpdSwPt[PARAMSIZE] = "017";
const char MotorPump[PARAMSIZE] = "023";
const char OpModeBKP[PARAMSIZE] = "025";
const char SpdSetMode[PARAMSIZE] = "026";
const char GasMode[PARAMSIZE] = "027";
const char CfgAccA1[PARAMSIZE] = "035";
const char CfgAccA2[PARAMSIZE] = "036";

// Status only
const char ErrorCode[PARAMSIZE] = "303";
const char SetRotSpd[PARAMSIZE] = "308";
const char ActualSpd[PARAMSIZE] = "309";
const char NominalSpd[PARAMSIZE] = "315"; //HiPace 10 -> 1500 Hz = 1.5kHz
const char TempElec[PARAMSIZE] = "326";
const char TempPmpBot[PARAMSIZE] = "330";
const char TempBearng[PARAMSIZE] = "342";
const char Pressure[PARAMSIZE] = "340";
const char TempMotor[PARAMSIZE] = "346";

// Sollwertvorgaben
const char SpdSwtPt1[PARAMSIZE] = "701"; 
const char SpdSVal[PARAMSIZE] = "707";
const char SpdSwtPt2[PARAMSIZE] = "719";
const char PrsSn1Name[PARAMSIZE] = "739";
const char Pressure1[PARAMSIZE] = "740"; // Atm. pressure at 100m aboce level of the sea ~ 990mbar
const char PrsCorriPi1[PARAMSIZE] = "742";

const int boolDataType = 0;
const int intLongDataType = 1;
const int intRealDataType = 2;
const int stringDataType = 4;
const int intShortDataType = 7;
const int expoDataType = 10;
const int requestData = 13;

const int paramCommSize = 10;
const int commandSize = 20; // Every command in RS485 protocol has 10 character to specify what type of request/command 
                            // the master requires from the slave. I'll assume that the maximum data size will be 06, 
                            // which means that total command size is 20

char outCommand[commandSize] = {0};
char command[commandSize] = {0};
char answer[commandSize+1] = {0};
char paramStr[PARAMSIZE] = {0};

char debugInput;

bool changeStatus = false;
bool MotorPumpStatus = false;
bool BackPumpStatus = false;
bool ShowAnswer = false;

bool setupVar = true;

//Interval variables and values: this code doesn't use any delay function. to allow the use of interruptions and events for debugging
//Instead, everything is set in different interval of time trying to avoid any collition on the different communication functions
const unsigned long checkInterval = 3000;
unsigned long lastCheckMillis = 0;
const unsigned long checkPressureInterval = 2000;
unsigned long lastCheckPressureMillis = 0;
const unsigned long setupInterval = 500;
unsigned long lastSetupMillis = 0;
const unsigned long ReadInterval = 17; //RS485 specification
unsigned long lastReadMillis = 0;
const unsigned long ReceivedRS232Interval = 20; //RS232 specification
unsigned long lastReceivedRS232Millis = 0;

int queryTurn = 0;

// Stored variables, from DCU comunication
char SensorName[7];
double PressRPTData = 0.0;
int ElecTemp = 0;

// Pressure sensor variables
byte receivedData[9]={0}; 
double PressureValue = 0.0;
byte highByte;
byte lowByte;

// Interval managing variables for pressure sensor
const int PresSenInterval = 100;
unsigned long PreviousPresSenMillis = 0;

void setup() {
  Serial.begin(9600); // debugging
  Serial3.begin(9600, SERIAL_8N1); //TX3RX3 - Serial port used to interface with the RS-232 communication protocol
  Serial2.begin(9600); //TX2RX2 - Serial port used to interface with the RS-485 communication protocol

  // RS485 Communication control pins
  pinMode(ENRS485Pin, OUTPUT);

  RS485Mode(READ);
}

void loop() {
  if(setupVar == true){
    if(millis() - lastSetupMillis >= setupInterval){ 
      RS485Mode(WRITE);

      if(queryTurn == 0){
        Serial.println("Pumping station: ");
        instructConst(1, WRITE, PumpgnStatn, 6, boolDataType, 1, command);
        queryTurn++;
      }else if(queryTurn == 1){
        Serial.println("Config Accessor A1: ");
        instructConst(1, WRITE, CfgAccA1, 3, intShortDataType, 3, command);
        queryTurn++;
      }else if(queryTurn == 2){
        Serial.println("Config Accessor B1: ");
        instructConst(1, WRITE, CfgAccA2, 3, intShortDataType, 6, command);
        queryTurn++;
      }else if(queryTurn == 3){
        Serial.println("Gas Mode: ");
        instructConst(1, WRITE, GasMode, 3, intShortDataType, 1, command);
        queryTurn++;
      }else if(queryTurn == 4){
        Serial.println("Operation Mode Backing Pump: ");
        instructConst(1, WRITE, OpModeBKP, 3, intShortDataType, 2, command);
        queryTurn++;
      }else if(queryTurn == 5){
        Serial.println("PV.can attached sensor name:");
        instructConst(1, READ, PrsSn1Name, 2, requestData, 0, command);
        queryTurn++;
      }else if(queryTurn == 6){
        Serial.println("Pressure sensor calibration factor:");
        instructConst(1, WRITE, PrsCorriPi1, 6, intRealDataType, (int)1.0*100, command);
        queryTurn++;
      }else if(queryTurn == 7){
        Serial.println("Motor turbo Pump: ");
        instructConst(1, WRITE, MotorPump, 6, boolDataType, 0, command);
        queryTurn = 0;
        setupVar = false;
      }
      Serial3.write(command);
      Serial3.write(endChar);
      Serial3.flush();

      memset(command, 0, sizeof(command));
      
      lastSetupMillis += setupInterval;
    }
    
  }else if(setupVar == false){
    if(millis() - lastCheckMillis >= checkInterval){ 
      RS485Mode(WRITE);
          
      if(queryTurn == 0){ 
        instructConst(1, READ, ActualSpd, 2, requestData, 0, outCommand);
        queryTurn++;
      }else if(queryTurn == 1){
        instructConst(1, READ, TempElec, 2, requestData, 0, outCommand);
        queryTurn++;
      }else if(queryTurn == 2){
        instructConst(1, READ, TempPmpBot, 2, requestData, 0, outCommand);
        queryTurn++;
      }else if(queryTurn == 3){
        instructConst(1, READ, ErrorCode, 2, requestData, 0, outCommand);
        queryTurn = 0;
      }
      
      Serial3.write(outCommand);
      Serial3.write(endChar);
      Serial3.flush();

      memset(outCommand, 0, sizeof(outCommand));

      lastCheckMillis += checkInterval;
    }
    
    if(millis() - lastCheckPressureMillis >= checkPressureInterval){ 
      RS485Mode(WRITE);

      instructConst(1, READ, Pressure1, 2, requestData, 0, command);
      Serial.print("ITR 090: ");
      Serial.print(PressureValue, 4);  
      Serial.println(" mbar");

      Serial3.write(command);
      Serial3.write(endChar);
      Serial3.flush();

      memset(command, 0, sizeof(command));

      lastCheckPressureMillis += checkPressureInterval;
    }

  }

  if(millis() - lastReadMillis >= ReadInterval){
    ReadRS485Serial(answer);
    if(ShowAnswer) {
      //Serial.println(answer);
      SaveAnswer();
      ShowAnswer = false;
    }
    
    lastReadMillis += ReadInterval;
  }
    
  ReadPressure();
}

//================================================================== FUNCTIONS ======================================================

// This is only a helper to allow ease in reading the code, because of the shield that is being used, the connection of DE an !RE is 
// done analogical, yet for the IC that is not a certainty  
void RS485Mode(bool mode){
  digitalWrite(ENRS485Pin, mode);
}

// This function works to partially automatize the constrcution of the outgoing command, the idea is to generalize the funtion either 
// using a configuration file or a dictionary with the important parameters. Rn, it works with almost all types of commands that use
// the DCU, still is not complete.
char instructConst(int address, bool mode, char param[], const int dataLength, const int dataType,
                  int inData, char str[]){
  char i[4];
  itoa(address, i, 10);
  if(address<10){
    strcpy(str, "00");
    strcat(str, i);
  }else if(address >= 10 && address < 100){
    strcpy(str, "0");
    strcat(str, i);
  }else strcpy(str, i);

  if(mode) strcat(str, "10");
  else strcat(str, "00");

  strcat(str, param);
  
  itoa(dataLength, i, 10);

  if(dataLength < 10){
    strcat(str, "0");
    strcat(str, i);
    
  }else strcat(str, i);
  
  if(dataLength == 2) strcat(str, "=?");
    
  else if(dataType == boolDataType){
    if(inData == 1) strcat(str, "111111");
    else if(inData == 0) strcat(str, "000000");

  }else if((dataType == intLongDataType)|| (dataType == intRealDataType)){
    char data[dataLength];
    itoa(inData, data, 10);

    if(inData < 10){
      strcat(str, "00000");
      strcat(str, data);
      
    }else if(inData >= 10 && inData < 100){
      strcat(str, "0000");
      strcat(str, data);
      
    }else if(inData >= 100 && inData < 1000){
      strcat(str, "000");
      strcat(str, data);
      
    }else if(inData >= 1000 && inData < 10000){
      strcat(str, "00");
      strcat(str, data);
      
    }else if(inData >= 10000 && inData < 100000){
      strcat(str, "0");
      strcat(str, data);
      
    }else strcat(str, data);

  }else if(dataType == intShortDataType){
    char data[dataLength];
    itoa(inData, data, 10);
    
    if(inData < 10){
      strcat(str, "00");
      strcat(str, data);
      
    }else if(inData >= 10 && inData < 100){
      strcat(str, "0");
      strcat(str, data);
      
    }else strcat(str, data);
  }

  char Check[4];
  int checkSum = ASCIIsum(0, paramCommSize + dataLength - 1, str) % 256;
  itoa(checkSum, Check, 10);
  if(checkSum <10){
    strcat(str, "00");
    strcat(str, Check);
  }else if(checkSum>=10 && checkSum<100){
    strcat(str, "0");
    strcat(str, Check);
  }else strcat(str, Check);

  return str;
}

char ReadRS485Serial(char strAnswer[]){
  RS485Mode(READ);
  if(Serial3.available()){
    static int i = 0;
    char ch = Serial3.read();
    if(ch != endChar && i < commandSize-1){
      strAnswer[i] = ch;
      i++;
    }else if(ch == endChar || i == commandSize-1){
      while(i < commandSize){
        if(i == commandSize-1){
          i = 0;
          ShowAnswer = true;
          break;
        }
        strAnswer[i] = '\0'; // null terminator character, in string it signifies the end of a string (null-terminated string)
        i++;
      }
    }
  }
  return strAnswer;
}

//at this point this function shows in comprehensible format the information from the TC110. Right now it doesn't store the 
//information in any global variable. 
void SaveAnswer(){  
  char ReceivedLength = answer[paramCommSize-1];

  for(int i = 0; i<PARAMSIZE; i++){
    paramStr[i] = answer[i+5];
  }
  paramStr[3] = '\0';

  if(validCheckSum(answer, commandSize) && paramStr != NULL && setupVar == false){
    int dataLength = ReceivedLength - '0';
    if(strcmp(paramStr, Pressure1) == 0){
      char SensedPressure[7];
      copy(answer, SensedPressure, dataLength, paramCommSize);
      SensedPressure[6]='\0';

      char expData[2];
      copy(SensedPressure, expData, 2, 4);

      int exp = atoi(expData) - 20;
      PressRPTData = (double(atof(SensedPressure)-(exp+20)))*pow(10, 5);

      Serial.print("RPT 010: ");
      Serial.print(PressRPTData);
      Serial.print("x10^");
      Serial.print(exp);
      Serial.println(" mbar");

    }else if(strcmp(paramStr, PrsSn1Name)==0){
        copy(answer, SensorName, dataLength, paramCommSize);
        SensorName[6] = '\0';

        Serial.println(SensorName);

    }else if(strcmp(paramStr, ActualSpd) == 0){
      char ActualSpeed[6];
      copy(answer, ActualSpeed, dataLength, paramCommSize);

      int pumpSpeed = atoi(ActualSpeed);
      
      Serial.print("Actual Speed: ");
      Serial.println(pumpSpeed);
      
    }else if(strcmp(paramStr, TempPmpBot) == 0 ){
      char TempPump[6];
      copy(answer, TempPump, dataLength, paramCommSize);

      int pumpTemp = atoi(TempPump);
      
      Serial.print("Temperature pump bottom part: ");
      Serial.print(pumpTemp);
      Serial.println("°C");
    }else if(strcmp(paramStr, TempElec) == 0 ){
      char TempE[6];
      copy(answer, TempE, dataLength, paramCommSize);

      int ElecTemp = atoi(TempE);
      
      Serial.print("Temperature electronics: ");
      Serial.print(ElecTemp);
      Serial.println("°C");

    }else if(strcmp(paramStr, ErrorCode) == 0 ){
      char Error[6];
      copy(answer, Error, dataLength, paramCommSize);

      Serial.print("Error: ");
      Serial.print(Error);
      Serial.print("Check Malfunctions section on the TC110 Operation Manual (page 40)");

    }else{
      Serial.print("Answer: ");
      Serial.println(answer);
    }
    
  }else{
    Serial.print("Answer: ");
    Serial.println(answer);
  }
  
  memset(answer, 0, sizeof(answer));

}

bool validCheckSum(char string[], int strSize){
  char checksum[4];
  for(int i = 0; i<4; i++){
    checksum[i] = string[i+strSize-4];
  }
  checksum[3] = '\0';
  int intChecksum = atoi(checksum);
  int confirmCheck = ASCIIsum(0, strSize-5, string) % 256;
  return(intChecksum == confirmCheck);
}

int ASCIIsum(int start, int end, char string[]){
  int asciiTot = 0;
  for (int i = start; i <= end; i++){
    asciiTot = asciiTot + string[i]; 
  }
  return asciiTot;
}

// read the output signal of the sensor and transform its value to the sensed pressure based on the characteristic function found in 
// the datasheet 
void ReadPressure(){
  if(Serial2.available() >= 9){
    static int i = 0;
    byte foolByte = Serial2.read();

    if(millis() - PreviousPresSenMillis >= PresSenInterval){
      byte mesByte = foolByte;
      
      if((mesByte==7) && (millis() - lastReceivedRS232Millis >= ReceivedRS232Interval)){
        for(i = 0; i < 8; i++){
          receivedData[i] = Serial2.read();
        }
        highByte = receivedData[3];
        lowByte = receivedData[4]; 

        lastReceivedRS232Millis += ReceivedRS232Interval;
      }
      memset(receivedData, 0, sizeof(receivedData));

      if(highByte != 0 && lowByte != 0){
        PressureValue = pow(10.0, (( float(highByte) * 256 + float(lowByte) ) / 4000 - 12.5));
      }
      PreviousPresSenMillis += PresSenInterval;
    }
    
  }
}

void copy(char* src, char* dst, int length, int offset){
  for(int i = 0; i < length; i++){
    dst[i] = src[i + offset];
  }
}

// meanwhile, there is still no integration with the LCD module or any external input from the user, so, as debugging tool 
// I've been using communication events to see if the pump and the arduino are communicating in a correct way
void serialEvent(){
  while(Serial.available()){
    debugInput = Serial.read();
    RS485Mode(WRITE);
    if(debugInput == 'P'){
      MotorPumpStatus = !MotorPumpStatus;
      if(MotorPumpStatus == true) instructConst(1, WRITE, MotorPump, 6, boolDataType, 1, outCommand);
      else if(MotorPumpStatus == false) instructConst(1, WRITE, MotorPump, 6, boolDataType, 0, outCommand);
    }else if(debugInput == 'O'){
      BackPumpStatus = !BackPumpStatus;
      if(BackPumpStatus == true) instructConst(1, WRITE, OpModeBKP, 3, intShortDataType, 0, outCommand);
      else if(BackPumpStatus == false) instructConst(1, WRITE, OpModeBKP, 3, intShortDataType, 2, outCommand);
    }
    Serial3.write(outCommand);
    Serial3.write(endChar);
    Serial3.flush();
    RS485Mode(READ);
  }
}
