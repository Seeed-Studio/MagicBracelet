/*****************************************************************************/
//Introduction:this sketch can be used to test gesture recognition.3-Axis Digital 
//   Accelerometer(16g) is in need. Start to test, you should press the button and
//   draw your graphics in the air.Matching results will be seen in serial output.
//   Any problems, please feel free to contact me !
//   now we only support 15 kinds of gestures. It is as follow
//
/*********************************************************************************************************************************************
 *|   0   |   1   |   2	 |   3   |    4   |	5   |	6    |    7  |    8  |    9    |    10   |   11  |   12  |   13    |    14   |   15  |*
 *|   *   |   *   |  *   |   *   |  * * * |	  * |* * *   |*      | *     |* * * *  |  * * * *|    *  |*      |  *      |      *  |      *|*
 *|  ***  |   *   | *    |    *  | * *	  |	 *  |   * *  | *     |* * * *|      *  |  *      |* * * *|*      |* * *    |    * * *|      *|*
 *| * * * | * * * |******|****** |*   *	  | *   *   |  *   * |  *   *| *    *|      *  |  *      |*   *  |*   *  |  *      |      *  |  *   *|*
 *|   *   |  ***  | *    |    *  |     *  |  * *    | *      |   * * |      *|    * * *|* * *    |*      |* * * *|  *      |      *  |* * * *|*
 *|   *   |   *   |  *   |   *   |      * |   * * * |*       |* * *  |      *|      *  |  *      |*      |    *  |  * * * *|* * * *  |  *    |*
 *********************************************************************************************************************************************
//
//  Hardware:3-Axis Digital Accelerometer(16g)
//  Arduino IDE: Arduino-1.0
//  Author:lawliet.zou(lawliet.zou@gmail.com)		
//  Date: Dec 24,2013
//  Version: v1.0
//  by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/
#include <EEPROM.h>
#include <IRSendRev.h>
#include <IRSendRevInt.h>
#include <MagicBracelet.h>
#include <gesture.h>
#include <Wire.h>
#include <ADXL345.h>
#include <SeeedOLED.h>

int vibration = 14;
int brightness = 150;
int updateMessage = 0;
MagicBracelet magicBracelet;
Gesture gesture;
void setup(){
    Serial.begin(9600);
    pinMode(vibration,OUTPUT);
    gesture.init();
    Wire.begin();	
    SeeedOled.init();  //initialze SEEED OLED display
    DDRB|=0x21;        //digital pin 8, LED glow indicates Film properly Connected .
    PORTB |= 0x21;
    showMessage();
}

void loop(){
    gesture.wakeUp();
    if(gesture.gestureWakeUp){
        updateMessage = 1;
        gesture.gestureWakeUp = 0;
        digitalWrite(vibration,HIGH);
        //SeeedOled.setTextXY(4,1);          //Set the cursor to Xth Page, Yth Column  
        //SeeedOled.putString(" Gesture Mode "); //Print the String
        SeeedOled.setTextXY(4,1);          //Set the cursor to Xth Page, Yth Column  
        SeeedOled.putString("              ");
        SeeedOled.setTextXY(3,1);          //Set the cursor to Xth Page, Yth Column  
        SeeedOled.putString(" Switch Mode: "); //Print the String
        SeeedOled.setTextXY(5,2);          //Set the cursor to Xth Page, Yth Column  
        SeeedOled.putString(" 1.Gesture"); //Print the String
        SeeedOled.setTextXY(6,2);          //Set the cursor to Xth Page, Yth Column  
        SeeedOled.putString(" 2.IR Record"); //Print the String
        delay(3000);
        digitalWrite(vibration,LOW);
        int mode = gesture.getVergence();
        switch(mode){
            case 1:
                SeeedOled.setTextXY(3,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("             "); //Print the String
                SeeedOled.setTextXY(4,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString(" Gesture Mode"); //Print the String
                SeeedOled.setTextXY(5,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("             "); //Print the String
                SeeedOled.setTextXY(6,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("             "); //Print the String
                digitalWrite(vibration,HIGH);
                delay(2000);
                digitalWrite(vibration,LOW);
                enterGestureMode();
                break;
            case 2:
                SeeedOled.setTextXY(3,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("             "); //Print the String
                SeeedOled.setTextXY(4,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("  IR  Record "); //Print the String
                SeeedOled.setTextXY(5,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("             "); //Print the String
                SeeedOled.setTextXY(6,1);          //Set the cursor to Xth Page, Yth Column  
                SeeedOled.putString("  Switch IR  "); //Print the String
                digitalWrite(vibration,HIGH);
                delay(2000);
                digitalWrite(vibration,LOW);   
                enterIRRecordMode();             
                break;
            default:
                break;
        }
    }
    if(updateMessage){
        showMessage();
        updateMessage = 0;
    }
}

void enterIRRecordMode(void)
{
    int index = 0;
    SeeedOled.setTextXY(6,1);
    SeeedOled.putString("             ");
    SeeedOled.setTextXY(6,5);
    SeeedOled.putString(homeApplianceName[index]);
    while(1){
        int mode = gesture.getVergence();
        if(mode == 1){
            if(index == 0){
                index = 9;
            }else{
                index--;
            }
        }else if(mode == 2){
            if(index == 9){
                index = 0;
            }else{
                index++;
            }
        }else if(mode == 0){
            break;
        }
        digitalWrite(vibration,HIGH);
        delay(1000);
        digitalWrite(vibration,LOW); 
        SeeedOled.setTextXY(6,1);
        SeeedOled.putString("             ");
        SeeedOled.setTextXY(6,5);          //Set the cursor to Xth Page, Yth Column  
        SeeedOled.putString(homeApplianceName[index]); //Print the String
    }
    SeeedOled.setTextXY(6,1);
    SeeedOled.putString("             ");
    SeeedOled.setTextXY(6,1);            
    SeeedOled.putString("Choose:");
    //SeeedOled.putString(homeApplianceName[index]); //Print the String
    SeeedOled.setTextXY(6,12);
    char number[2];
    SeeedOled.putString(itoa(index,number,10)); //Print the String
    //magicHand.readIR(index);
    digitalWrite(vibration,HIGH);
    delay(3000);
    digitalWrite(vibration,LOW); 
    SeeedOled.setTextXY(6,1);
    SeeedOled.putString("             ");
    SeeedOled.setTextXY(6,1);            
    SeeedOled.putString(" Recv IR ... ");     
    int length[2];
    unsigned char data[2][IR_RAW_DATA_LEN];
    while(1){
        for(int i = 0; i < 2; i++){
            length[i] = magicBracelet.readIR(data[i]);
            SeeedOled.setTextXY(6,1);
            SeeedOled.putString("             ");
            SeeedOled.setTextXY(6,1);            
            SeeedOled.putString(" Get IR OK ");            
        }
        if(length[0] == length[1]){
            int len;
            for(len = 0; len < length[0]; len++){
                if(abs(data[0][len] - data[1][len]) > 3){
                    SeeedOled.setTextXY(6,1);
                    SeeedOled.putString("             ");
                    SeeedOled.setTextXY(6,1);            
                    SeeedOled.putString(" IR No Match!"); 
                    digitalWrite(vibration,HIGH);
                    delay(3000);
                    digitalWrite(vibration,LOW);                    
                    continue;
                }

             }
             if(len == length[0]-1){
                SeeedOled.setTextXY(6,1);
                SeeedOled.putString("             ");
                SeeedOled.setTextXY(6,1);            
                SeeedOled.putString(" Store IR"); 
                digitalWrite(vibration,HIGH);
                delay(3000);
                digitalWrite(vibration,LOW); 
                magicBracelet.storeIRToEEPROM(index+1,data[0]);
                break;
            }
        }
    }
}

void enterGestureMode(void)
{
      if(!gesture.samplingAccelerateData){       
	    gesture.checkMoveStart();
      }
	if(gesture.samplingAccelerateData){
          if(0 != gesture.getAccelerateData()){
              SeeedOled.setTextXY(6,1);          //Set the cursor to Xth Page, Yth Column  
              SeeedOled.putString("Gesture Error!"); //Print the String
          }
	}
	if(gesture.calculatingAccelerateData){
	  int matchingResult = gesture.calculateAccelerateData();
          SeeedOled.setTextXY(6,1);          //Set the cursor to Xth Page, Yth Column  
          SeeedOled.putString("             ");
          SeeedOled.setTextXY(6,1);          //Set the cursor to Xth Page, Yth Column  
          SeeedOled.putString(" matching:");
          SeeedOled.setTextXY(6,12);
          char number[2];
          SeeedOled.putString(itoa(matchingResult,number,10)); //Print the String
          if((matchingResult >= 0) && (matchingResult <= 3)){
              digitalWrite(vibration,HIGH);
              delay(3000);
              digitalWrite(vibration,LOW);
              magicBracelet.sendIR(matchingResult+1);
          }
      }    
}

void showMessage(void)
{
    SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();           //Set addressing mode to Page Mode
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("****************");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("*Magic bracelet*");
    SeeedOled.setTextXY(2,0);
    SeeedOled.putString("****************");
    SeeedOled.setTextXY(3,0);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(3,15);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(4,0);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(4,15);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(5,0);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(5,15);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(6,0);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(6,15);
    SeeedOled.putString("*");
    SeeedOled.setTextXY(7,0);
    SeeedOled.putString("****************");
    SeeedOled.setTextXY(4,1);
    SeeedOled.putString("Gesture&Walker");
}

