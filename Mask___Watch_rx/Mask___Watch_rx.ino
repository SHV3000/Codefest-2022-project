#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
int value = 0;
RF24 radio(7, 8); 
const byte addresses[][6] = {"00001"};

void setup() {
 Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      radio.read(&value, sizeof(value));
      }

      if (value == 1) {
       Serial.println("Safe");
        }

        else if (value == 2){
          Serial.println("UnSafe");
          }
        }
}
