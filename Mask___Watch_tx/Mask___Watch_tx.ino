#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3D 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
int value = 0;
int button = 7;
int button1 = 8;

void onBeatDetected()
{
   Serial.println("Beat!");
}
 

RF24 radio(7, 8);
const byte addresses[][6] = {"00001"};

void setup() {
  pinMode(button, INPUT);
  pinMode(button1, INPUT);
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

if (button == 1) {
  
  }

else if (button1 == 1) {
    display.clearDisplay();
  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0);           
  display.println("SpO2:");
  display.setCursor(0,10);           
  display.println(pox.getSpO2());
  display.setCursor(30,10);           
  display.println("%");  
  }
        
if (pox.getSpO2() > 95){
  value = 1;
  }
else if (pox.getSpO2() < 95) {
  value = 2;
  }

radio.stopListening();
radio.write(&value, sizeof(value));
}
