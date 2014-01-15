//**************
//IR sent demo v1.0
//Connect the IR sent pins to D3 for this demo
//By:http://www.seeedstudio.com/
//******************************
#include <IRSendRev.h>

void setup()
{
    //enableIROut(38);
}
//unsigned char d[] = {9, 90, 91, 11, 31, 4, 1, 2, 3, 4};
unsigned char d[] = {15, 70, 70, 20, 60, 10, 1, 2, 3, 4,5,6,7,8,9,10};
//Very Important:
//the first parameter(15): the data that needs to be sent;
//the next 2 parameter(70,70): the logic high and low duration of "Start";
//the next 2 parameter(20,60): the logic "short" and "long"duration in the communication
//                             that to say:  if "0", the high duration is 20ms and  low is 20 ms; while logic "1",
//                              the high duration is 20 ms and low is 60 ms;
//the next 2 parameter(10): number of data you will sent;
//the next parameter(1, 2, 3, 4,5,6,7,8,9,10): data you will sent ;
void loop()
{
    IR.Send(d, 38);//sent the data via 38Kz IR
    delay(1000);
}
