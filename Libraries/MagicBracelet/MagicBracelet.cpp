#include "MagicBracelet.h"

int MagicBracelet::sendIR(char index)
{
	unsigned char irMessage[IR_STRUCT_LEN];
	
	if(index > MAX_APPLIANCE_LEN)
		return -1;
	//read IR Message from EEPROM
	for(int i = 0; i < IR_STRUCT_LEN; i++){
		irMessage[i] = EEPROM.read((index-1)*IR_STRUCT_LEN+i);
		//Serial.print(irMessage[i]);
		//Serial.print("\r\n");
	}
	//check home Appliance Name is correct or not
    #if 0
	unsigned char *p = &irMessage[1];
	if(0 != strncmp((const char *)p, homeApplianceName[index-1],HOME_APPLICANCE_NAME_LEN))
		return -1;
	else
		Serial.print("\r\n check home appliance name OK \r\n");
	#endif
	//IR.Send(irMessage+6,38);
	
	#if 1
	//send 3 times to make sure that IR Signal can be received
	for(int i = 0; i < 3; i++){
        Serial.print("\r\n send IR");
		IR.Send(irMessage+6,38);
		delay(1000);
    }
	#endif
	return 0;
}

int MagicBracelet::readIR(unsigned char* data)
{
    int length = 0;
	IR.Init(IR_INPUT_PIN);
	while(1){
		if(IR.IsDta()){
			length = IR.Recv(data);
			if(length > IR_RAW_DATA_LEN)
				continue;
            else 
                break;
		}
	}
	return length;
}
int MagicBracelet::storeIRToEEPROM(char index,unsigned char* dta)
{
    unsigned char irMessage[IR_STRUCT_LEN];
	unsigned char *p = NULL;
    if(index >= MAX_APPLIANCE_LEN)
		return -1;
    irMessage[0] = index;
    p = &irMessage[1];
    strncpy((char*)p,homeApplianceName[index-1],HOME_APPLICANCE_NAME_LEN);
    p = &irMessage[6];
    strncpy((char *)p,(const char*)dta,IR_RAW_DATA_LEN);
    for (int i =0;i < IR_STRUCT_LEN;i++){
      EEPROM.write(IR_STRUCT_LEN*(index-1)+i,irMessage[i]);
    }
    return 0;
}


int MagicBracelet::storeMessageToEEPROM(void)
{
	unsigned char lamp[IR_STRUCT_LEN] 	= {1,'L','A','M','P','\0',9,70,70,20,60,4,1,2,1,2};
	unsigned char tv[IR_STRUCT_LEN] 	= {2,'T','V','\0','\0','\0',9,70,70,20,60,4,2,1,2,1};
	unsigned char airOn[IR_STRUCT_LEN] 	= {3,'A','I','R','\0','\0',19,71,31,9,25,14,136,136,136,136,136,36,64,176,80,0,0,0,0,73};
	unsigned char airOff[IR_STRUCT_LEN]	= {4,'A','I','R','\0','\0',19,71,31,9,25,14,136,136,136,136,136,4,64,176,80,0,0,0,0,113};
    
	
	unsigned char* appliance[4] = {lamp,tv,airOn,airOff};
	
	for(int index = 0; index < 4; index++){
		unsigned char *p = appliance[index];
		for (int i = 0; i < IR_STRUCT_LEN; i++){
			EEPROM.write(IR_STRUCT_LEN*(index)+i,*(p+i));
		}
	}
	return 0;
}
int MagicBracelet::readMessageFromEEPROM(void)
{
	unsigned char irMessage[IR_STRUCT_LEN];
	for(int index = 0; index < 4; index++){
		for(int i = 0; i < IR_STRUCT_LEN; i++){
			irMessage[i] = EEPROM.read(index*IR_STRUCT_LEN+i);
			Serial.print(irMessage[i]);
			Serial.println();
		}
	}
	return 0;
}
