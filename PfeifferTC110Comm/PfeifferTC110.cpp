#include "PfeifferTC110.h"

/*Data Type from the TC110 RS485 Protocol, numbers are assigned based on the datasheet of the TC110. 
  boolDataType = 0;
  intLongDataType = 1;
  intRealDataType = 2;
  stringDataType = 4;
  intShortDataType = 7;
  expoDataType = 10;
*/
struct pumpParameter paramList[40]{
  {"009", 0 , 6}, //0 ErrorAckn
  {"010", 0 , 6}, //1 PumpgnStatn
  {"017", 7 , 3}, //2 CfgSpdSwPt
  {"023", 0 , 6}, //3 MotorPump
  {"025", 7 , 3}, //4 OpModeBKP
  {"026", 7 , 3}, //5 SpdSetMode
  {"027", 7 , 3}, //6 GasMode
  {"035", 7 , 3}, //7 CfgAccA1
  {"036", 7 , 3}, //8 CfgAccB1

  {"303", 4 , 6}, //9 ErrorCode
  {"308", 1 , 6}, //10 SetRotSpd
  {"309", 1 , 6}, //11 ActualSpd
  {"326", 1 , 6}, //12 TempElec
  {"330", 1 , 6}, //13 TempPmpBot
  {"346", 1 , 6}, //14 TempMotor

  {"739", 4 , 6}, //15 PrsSn1Name
  {"740", 10, 6}, //16 Pressure1 // Atm. pressure at 100m above level of the sea ~ 990mbar
  {"742", 2 , 6}, //17 PrsCorriP1 
};

// Parameter hashmap - this way, the actual name of the parameter can be related to the values
paramDict param = {
  {"ErrorAckn"  , paramList[0]},
  {"PumpngStatn", paramList[1]},
  {"CfgSpdSwPt" , paramList[2]},
  {"MotorPump"  , paramList[3]},
  {"OpModeBKP"  , paramList[4]},
  {"SpdSetMode" , paramList[5]},
  {"GasMode"    , paramList[6]},
  {"CfgAccA1"   , paramList[7]},
  {"CfgAccB1"   , paramList[8]},

  {"ErrorCode"  , paramList[9]},
  {"SetRotSpd"  , paramList[10]},
  {"ActualSpd"  , paramList[11]},
  {"TempElec"   , paramList[12]},
  {"TempPmpBot" , paramList[13]},
  {"TempMotor"  , paramList[14]},

  {"PrsSn1Name" , paramList[15]},
  {"Pressure1"  , paramList[16]},
  {"PrsCorriP1" , paramList[17]}
};

const char endChar = '\r';  // ASCII character 13


//Time interval managing variables
/*const unsigned long checkInterval = 3000;
unsigned long lastCheckMillis = 0;
const unsigned long checkPressureInterval = 2000;
unsigned long lastCheckPressureMillis = 0;
const unsigned long setupInterval = 500;
unsigned long lastSetupMillis = 0;*/


bool saveAnswer = false;

TC110::TC110(byte ENPin, HardwareSerial &port):serialPort(port){
  this->ENPin = ENPin; 
  init();
}

void TC110::init(){
  serialPort.begin(9600); //Protocol RS485 has a BAUDRATE of 9600, therefore the serial port is fixed with this BAUDRATE 
  Serial.begin(9600);
  pinMode(ENPin, OUTPUT);
  RS485Mode(READ); //The idea is that the Master hears constantly the channel to receive any possible info from the slave.
}

/*This is only a helper to allow ease in reading the code, because of the shield that is being used, the connection of DE an !RE is 
  done analogical, yet for the IC that is not a certainty  */
void TC110::RS485Mode(bool mode){
  digitalWrite(ENPin, mode);
}

void TC110::sendCommand(char *com){
  serialPort.write(com);
  serialPort.write(endChar);
  serialPort.flush();
}

char TC110::ReadRS485Serial(char *strAnswer){
  RS485Mode(READ);
  if(serialPort.available()){
    static int i = 0;
    char ch = serialPort.read();
    if(ch != endChar && i < COMMANDSIZE-1){
      strAnswer[i] = ch;
      i++;
    }else if(ch == endChar || i == COMMANDSIZE-1){
      while(i < COMMANDSIZE){
        if(i == COMMANDSIZE-1){
          i = 0;
          saveAnswer = true;
          break;
        }
        strAnswer[i] = '\0'; // null terminator character, in string it signifies the end of a string (null-terminated string)
        i++;
      }
    }
  }
  return *strAnswer;
}

void TC110::SaveAnswer(char *answer){  
  char ReceivedLength = answer[PARAMCOMMSIZE-1];
  char paramStr[PARAMSIZE];

  for(int i = 0; i<PARAMSIZE; i++){
    paramStr[i] = answer[i+5];
  }
  paramStr[3] = '\0';

  if(validCheckSum(answer, COMMANDSIZE) && paramStr != NULL){
    int dataLength = ReceivedLength - '0';
    
    // Pumping stattion Status
    if (strcmp(paramStr, param["PumpngStatn"].parameter) == 0){
      copy(answer, param["PumpngStatn"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["PumpngStatn"].receivedValue[dataLength] = '\0';
      Serial.print(param["PumpngStatn"].receivedValue);

    }else if(strcmp(paramStr, param["MotorPump"].parameter) == 0){
      copy(answer, param["MotorPump"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["MotorPump"].receivedValue[dataLength] = '\0';
      Serial.print(param["MotorPump"].receivedValue);

    //Speed of the turbo pump
    }else if(strcmp(paramStr, param["ActualSpd"].parameter) == 0){
      copy(answer, param["ActualSpd"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["ActualSpd"].receivedValue[dataLength]='\0';

    // Temperature of the electronics of the DCU
    }else if(strcmp(paramStr, param["TempElec"].parameter) == 0 ){
      copy(answer, param["TempElec"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["TempElec"].receivedValue[dataLength] = '\0';
    
    // Temperature of the bottom part of the Turbo pump  
    }else if(strcmp(paramStr, param["TempPmpBot"].parameter) == 0 ){
      copy(answer, param["TempPmpBot"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["TempPmpBot"].receivedValue[dataLength] = '\0';

    //Pressure value from sensor RPT 010
    }else if(strcmp(paramStr, param["Pressure1"].parameter) == 0){
      char SensedPressure[7];
      copy(answer, SensedPressure, dataLength, PARAMCOMMSIZE);
      SensedPressure[dataLength]='\0';

      char expData[3];
      char valData[5];

      copy(SensedPressure, expData, 2, 4);
      copy(SensedPressure, valData, 4, 0);
      expData[2] = '\0';
      valData[4] = '\0';
      memset(SensedPressure, 0, sizeof(SensedPressure));

      int exp = atoi(expData) - 20;
      double val = double(atof(valData))*pow(10, -3);
    
      memset(expData, 0, sizeof(expData));
      itoa(exp, expData, 10);
      dtostrf(val, -4, 3, param["Pressure1"].receivedValue);
      strcat(param["Pressure1"].receivedValue, "E");
      strcat(param["Pressure1"].receivedValue, expData);
      param["Pressure1"].receivedValue[9]='\0';

    //Sensor name from DCU
    }else if(strcmp(paramStr, param["PrsSn1Name"].parameter)==0){
        copy(answer, param["PrsSn1Name"].receivedValue, dataLength, PARAMCOMMSIZE);
        param["PrsSn1Name"].receivedValue[dataLength] = '\0';

    }else if(strcmp(paramStr, param["ErrorCode"].parameter) == 0 ){
      copy(answer, param["ErrorCode"].receivedValue, dataLength, PARAMCOMMSIZE);
      param["ErrorCode"].receivedValue[dataLength] = '\0';

    }else{
      return;
    }
    
  }else{
    return;
  }
  
  memset(answer, 0, sizeof(answer));

}


char instructConst(int address, bool mode, pumpParameter param, int inData, char *str){
  char i[4];
  itoa(address, i, 10);
  
  //Stores de Address of the pump as the first 3 character of the intruction array
  if(address<10){
    strcpy(str, "00");
    strcat(str, i);
  }else if(address >= 10 && address < 100){
    strcpy(str, "0");
    strcat(str, i);
  }else strcpy(str, i);

  //Depending on the communication mode, it adds the next 2 characters to the array
  if(mode) strcat(str, "10");
  else strcat(str, "00");
  
  strcat(str, param.parameter);//strcat(str, param);
  
  if(!mode) strcat(str, "02");
  else{
    itoa(param.dataLength, i, 10);//itoa(dataLength, i, 10);

    if(param.dataLength < 10){
      strcat(str, "0");
      strcat(str, i);
      
    }else strcat(str, i);
  }
  
  
  if(!mode) strcat(str, "=?");
    
  else if(param.dataType == 0){
    if(inData == 1) strcat(str, "111111");
    else if(inData == 0) strcat(str, "000000");

  }else if((param.dataType == 1)|| (param.dataType == 2)){
    char data[param.dataLength];
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

  }else if(param.dataType == 7){
    char data[param.dataLength];
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
  int checkSum = ASCIIsum(0, PARAMCOMMSIZE + param.dataLength - 1, str) % 256;
  itoa(checkSum, Check, 10);
  if(checkSum <10){
    strcat(str, "00");
    strcat(str, Check);
  }else if(checkSum>=10 && checkSum<100){
    strcat(str, "0");
    strcat(str, Check);
  }else strcat(str, Check);

  return *str;
}

bool validCheckSum(char *string, int strSize){
  char checksum[4];
  for(int i = 0; i<4; i++){
    checksum[i] = string[i+strSize-4];
  }
  checksum[3] = '\0';
  int intChecksum = atoi(checksum);
  int confirmCheck = ASCIIsum(0, strSize-5, string) % 256;
  return(intChecksum == confirmCheck);
}

int ASCIIsum(int start, int end, char *string){
  int asciiTot = 0;
  for (int i = start; i <= end; i++){
    asciiTot = asciiTot + string[i]; 
  }
  return asciiTot;
}

void copy(char* src, char* dst, int length, int offset){
  for(int i = 0; i < length; i++){
    dst[i] = src[i + offset];
  }
}

char getEndChar(){
  return endChar;
}

bool getAnswerStat(){
  return saveAnswer;
}

bool changeAnswerStat(){
  return saveAnswer = false;
}


