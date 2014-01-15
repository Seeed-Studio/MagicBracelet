//**************
//IR receive demo v1.0
//Connect the IR sent pins to A4 for this demo
//By:http://www.seeedstudio.com/
//******************************
#include <IRSendRev.h>
//#include <IRSendRevInt.h>

void setup()
{
    Serial.begin(38400);
    IR.Init(A4);
    Serial.println("init over");
}

unsigned char dta[20];

void loop()
{
    if(IR.IsDta())
    {
       // IR.Recv(dta);
        int length= IR.Recv(dta);
        for (int i =0;i<length;i++)
        {
          Serial.print(dta[i]);
          Serial.print("\t");
        }
        Serial.println();
// Very Important:
// the received data is comprised of the trsmission parameters , please refer to 
// the sendTest.ino in the library ;
    }
    
    
}
