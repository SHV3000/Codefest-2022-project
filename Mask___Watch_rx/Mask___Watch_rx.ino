#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

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
  display.setTextSize(3);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0);           
  display.println("SAFE");
        }

        else if (value == 2){
          Serial.println("UnSafe");
  display.setTextSize(2);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0);           
  display.println("UNSAFE");
          }
        }
}
