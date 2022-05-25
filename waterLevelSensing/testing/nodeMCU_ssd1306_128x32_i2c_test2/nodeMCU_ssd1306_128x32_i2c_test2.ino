#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);
String dispStr = "";
String tempStr = "";

void setup()
{
//  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
  
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Hello world!");
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop() {
  /*if (Serial.available()) {
  dispStr = Serial.read();
  Serial.println(dispStr);
  }
  if (tempStr != dispStr) {
  display.clearDisplay();
  display.setCursor(0,28);
  display.println(dispStr);
  display.display();
  tempStr = dispStr;
  }*/
}
