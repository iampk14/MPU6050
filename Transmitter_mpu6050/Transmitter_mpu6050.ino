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

void setup()
{
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
  delay(2000);
  
  
  }
