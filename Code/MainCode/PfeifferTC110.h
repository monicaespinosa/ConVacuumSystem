#ifndef PFEIFFERTC110_H
#define PFEIFFERTC110_H

#define READ 0
#define WRITE 1
#define PARAMSIZE 4
#define PARAMCOMMSIZE 10
#define COMMANDSIZE 20 // Every command in RS485 protocol has 10 character to specify what type of request/command 
                       // the master requires from the slave. I'll assume that the maximum data size will be 06, 
                       // which means that total command size is 20

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <map>
#include <string>

class TC110{
  
  private:
    byte ENPin;
    HardwareSerial &serialPort;

  public:
    TC110(byte ENPin, HardwareSerial &port);
    void init();
    void RS485Mode(bool mode);
    void sendCommand(char com[]);
    char ReadRS485Serial(char strAnswer[]);
    void SaveAnswer(char answer[]);
};

struct pumpParameter{
  char parameter[PARAMSIZE];
  int dataType;
  int dataLength;
  char receivedValue[10];
};

extern pumpParameter paramList[];

using paramDict = std::map<std::string , pumpParameter>;
extern paramDict param;


char instructConst(int address, bool mode, pumpParameter param, int inData, char *str);
int ASCIIsum(int start, int end, char *string);
bool validCheckSum(char *string, int strSize);
void copy(char* src, char* dst, int length, int offset);
char getEndChar();
bool getAnswerStat();
bool changeAnswerStat();


#endif