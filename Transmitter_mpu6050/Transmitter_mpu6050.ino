#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";

MPU6050 sensor ;
int16_t ax, ay, az ,gx, gy, gz ;

void setup ()
{ 
  Wire.begin ();
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop () 
{ 
 sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);
 Serial.println (ax);
 if(radio.available())
 {
  radio.write(&ax, sizeof(ax));
  radio.write(&ay, sizeof(ay));
  delay (2000);
 }
}
