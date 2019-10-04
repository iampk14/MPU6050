#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>   

Servo servoarm;
Servo servobase;          

int servo1 = 2;
int servo2 =3;

RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  servoarm.attach (servo1);
  servobase.attach (servo2);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    int16_t ax = 0;
    int16_t ay = 0;
    radio.read(&ax, sizeof(ax));
    radio.read(&ay, sizeof(ay));
    servoarm.write (ax); 
    servobase.write (ay);
    Serial.println(ax); 
  }
}
