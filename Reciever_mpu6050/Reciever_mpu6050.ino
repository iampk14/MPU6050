#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(9, 8);  // CE, CSN
Servo servoarm;
Servo servobase;
Servo ir;
int servo1 = 5;
int servo2 = 4;
int servo3 = 2 ;
const byte address[6] = "00001";
int value,value_avgX,value_avgY;
int value_array[6]={0},value_avg=0,i=0;

void setup()
{
  while (!Serial);
    Serial.begin(115200);
  servoarm.attach(servo1);
  servobase.attach(servo2);
  ir.attach(servo3);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
   radio.read(&value_avgX,sizeof(value_avgX));
   radio.read(&value_avgY,sizeof(value_avgY));
   radio.read(&value, sizeof(value));
   Serial.println(value_avgX);
   Serial.println(value_avgY);
   Serial.println(value);

   value_array[0]=value;
  value_avg=0;
  for(i=0;i<6;i++)
    value_avg=value_avg+value_array[i];

  if(value_avg>2)
    value=1;
    else
    value=0;
  //update
  for(i=5;i>0;i--)
    value_array[i]=value_array[i-1];
  value_avgX=map(value_avgX,-17000,17000,0,180);
  value_avgY=map(value_avgY,-17000,17000,0,180);
  servoarm.write(value_avgX);
  servobase.write(value_avgY);
  if(value==1)
  {
  ir.write(180);
  }
  else
  {
   ir.write(0);  
  }
delay(25);
  }

    }
