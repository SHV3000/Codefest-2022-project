#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>



RF24 radio(7, 8); 
const byte addresses[][6] = {"00001"};
Servo myServo;
boolean buttonState = 0;

void setup() {
  pinMode(button, INPUT);
  myServo.attach(5);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      radio.read(&value, sizeof(value));
      myServo.write(value);
}
