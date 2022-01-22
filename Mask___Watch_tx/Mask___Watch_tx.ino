#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
int value = 0;
void onBeatDetected()
{
   Serial.println("Beat!");
}
 

RF24 radio(7, 8);
const byte addresses[][6] = {"00001"};

void setup() {
  radio.begin();
  radio.openWritingPipe(addresses[0]); 
  radio.setPALevel(RF24_PA_MIN);

    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
  
}

void loop() {

    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print(pox.getHeartRate());
        Serial.print(pox.getSpO2());
        tsLastReport = millis();    
        }
if (pox.getSpo2() > 95){
  value = 1;
  }
else if (pox.getSpo2() < 95) {
  value = 2;
  }

radio.stopListening();
radio.write(&value, sizeof(value));
}
