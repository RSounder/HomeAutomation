//following test is for two nodeMCUs feeding data to one nodeMCU
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int id;
    String drink;
    String solar;
    String salt;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;

// Create an array with all the structures
struct_message boardsStruct[2] = {board1,board2};

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].drink = myData.drink;
  boardsStruct[myData.id-1].solar = myData.solar;
  boardsStruct[myData.id-1].salt = myData.salt;
  Serial.println("drink: " + boardsStruct[myData.id-1].drink);
  Serial.println("solar: " + boardsStruct[myData.id-1].solar);
  Serial.println("salt: " + boardsStruct[myData.id-1].salt);
  Serial.println();
}

void setup() {
  // Initialize Serial Monitor
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

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    displayText("Error", "WiFi", 5000);
    return;
  } else {
    displayText("Success!", "WiFi", 5000);
    }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

}

void loop(){
  displayText("Drink", boardsStruct[0].drink+"%", 5000);
  displayText("Solar", boardsStruct[0].solar+"%", 5000);
  displayText("Salt", boardsStruct[0].salt+"%", 5000);
}

void displayText(String text1, String text2, int delayTime) {
  display.setCursor(0, 0);
  display.println(text1);
  
  display.setCursor(64, 16);
  display.println(text2);

  display.display(); 
  delay(delayTime);
  display.clearDisplay();
}
