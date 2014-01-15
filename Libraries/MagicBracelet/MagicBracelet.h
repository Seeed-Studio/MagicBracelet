#ifndef _MAGIC_BRACELET_H_
#define _MAGIC_BRACELET_H_ 
 
#include <Wire.h>
#include <ADXL345.h> 
#include <IRSendRev.h>
#include <EEPROM.h>
#define IR_INPUT_PIN				A5
#define DEFAULT_TIME_CHECK 			1
#define IR_STRUCT_LEN				32
#define IR_RAW_DATA_LEN				26
#define MAX_APPLIANCE_LEN 			10
#define HOME_APPLICANCE_NAME_LEN	5



 struct IR_RAW_DATA
 {
	unsigned char totalLen;		//1bytes
	unsigned char startHigh; 	//1byte
	unsigned char startLow;  	//1byte
	unsigned char nShort;		//1byte
	unsigned char nLong;		//1byte
	unsigned char dataLen;		//1byte
	unsigned char data[20];		//10bytes
 };
 
 struct	IR_STRUCT				//22bytes
 {
	unsigned char index;		//1bytes
	unsigned char indexName[5];	//5bytes
	IR_RAW_DATA	irRawData;		//16bytes
 };
 
const char 	homeApplianceName[MAX_APPLIANCE_LEN][HOME_APPLICANCE_NAME_LEN] = {"LED0","LED1","AIR0","AIR1","FAN0","FAN1","TV0","TV1","ICE0","ICE1"};



class MagicBracelet
{
public:
	int sendIR(char index);
	int readIR(unsigned char* data);
    int storeIRToEEPROM(char index,unsigned char* dta);
	int storeMessageToEEPROM(void);
	int readMessageFromEEPROM(void);
private:
	//IR_STRUCT	irStruct;
};
#endif