#include <Wire.h>                // Including libraries
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <MPU6050.h>

RF24 radio(9, 8);                // CE, CSN

const byte address[6] = "00001"; //address through which two modules communicate.

MPU6050 sensor; // Initializing MPU6050
int16_t AccX , AccY , AccZ, GyroX , GyroY , GyroZ; 
const int ProxSensor=A3;
int value_arrayX[6]={0},value_arrayY[6]={0},value,value_avgX=0,value_avgY=0,i,j;

void setup()
{
  pinMode(ProxSensor,INPUT);
  Wire.begin();
  Serial.begin(115200);
  radio.begin();
  sensor.initialize();
  radio.openWritingPipe(address);
  radio.stopListening();  
}

void loop()
{ 
 sensor.getMotion6(&AccX, &AccY, &AccZ, &GyroX, &GyroY, &GyroZ); //Taking values of Accelerometer
 value = analogRead(ProxSensor);                                 //Taking values of Ir 
 if(value>=100)
 {
  value = 1;
 }
 else
 {
  value = 0;
 }
 value_arrayX[0]=AccX;
 value_arrayY[0]=AccY;
 value_avgX=0;
 i=0;
 for(i=0;i<6;i++)
    value_avgX=(value_avgX+value_arrayX[i])/6;                   //Taking Average
  value_avgY=0;
  j=0;
  for(j=0;j<6;j++)
    value_avgY=(value_avgY+value_arrayY[j])/6;                   //Taking Average
 radio.write(&value, sizeof(value));                             //Transmitting Data          
 radio.write(&value_avgX, sizeof(value_avgX));
 radio.write(&value_avgX, sizeof(value_avgX)); 
 Serial.println(value);
 Serial.println(value_avgX);
 Serial.println(value_avgY);
 delay(25);
 }
