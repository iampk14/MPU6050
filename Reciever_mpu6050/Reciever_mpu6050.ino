#include "Wire.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#include <MPU6050.h>
MPU6050 sensor;

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

int16_t ax ,ay, az, gx, gy, gz;
const int ProxSensor=A3;
int value;


void setup()
{
  pinMode(ProxSensor,INPUT);
  Wire.begin();
  Serial.begin(9600);
  radio.begin();
  sensor.initialize();
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  radio.write(&ax, sizeof(ax));
  radio.write(&ay, sizeof(ay));
  Serial.println(ax);
  Serial.println(ay);
  value = analogRead(ProxSensor);
  if(value>=100)
  {
    value=1;
  }
  else
  {
    value=0;
  }
  radio.write(&value, sizeof(value));
  Serial.println(value);
 delay(4);
} 
