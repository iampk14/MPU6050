#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
Servo servoarm;
Servo servobase;
int servo1 = 5;
int servo2 = 4;
//address through which two modules communicate.
const byte address[6] = "00001";
  //int ax,acc[2];
void setup()
{
  while (!Serial);
    Serial.begin(9600);
  servoarm.attach(servo1); 
  servobase.attach(servo2);
  radio.begin();
  
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
     int ax,ay;
   radio.read(&ax,sizeof(ax));
   radio.read(&ay,sizeof(ay));
   
   Serial.println(ax);  
    Serial.println(ay);  
   delay(2000);  
  ax=map(ax,-17000,17000,0,180);
  ay=map(ay,-17000,17000,0,180);
  servoarm.write(ax);
  servobase.write(ay);


  }  
}
