#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6); //1,3 node

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String readText = "";
String tempText = "";

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  delay(100);
}

void loop() {
  // displayText("Solar", "    50%", 5000);
  // rec str = TSA075B076C077DLOW
  // 22 chars first three chars for id, so scroll from char#3 to 21
  
  if (espSerial.available()) {
    readText = espSerial.read();
    Serial.println(readText);
    Serial.println("#############");
  } else {
    readText = "Error";
  }
  if (readText.length() > 5 && (readText != tempText)) {
    tempText = readText;
    for( int i=2; i< readText.length()-4 ; i = i+4 ) {
      displayText(readText.substring(i,i+1), readText.substring(i+1,i+4), 5000);
      Serial.println(readText.substring(i,i+1));
      Serial.println(readText.substring(i+1,i+4));
      Serial.println("----------------");   
    }
  } else {
    displayText(readText, "", 1000);
    displayText("", readText, 1000);
  }
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
