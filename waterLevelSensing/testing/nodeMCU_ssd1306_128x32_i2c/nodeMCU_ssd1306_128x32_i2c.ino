
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  delay(100);
}

void loop() {
  displayText("Solar", "    50%", 5000);
  
  displayText("Drink", "    75%", 5000);
  
  displayText("Salt", "    20%", 5000);
}

void displayText(String text1, String text2, int delayTime) {
  display.setCursor(0, 0);
  display.println(text1);
  
  display.setCursor(0, 16);
  display.println(text2);
  
  display.display(); 
  delay(delayTime);
  display.clearDisplay();
}
