// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Wire.h>

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

// Set your access point network credentials
const char* ssid = "TopStationSensing";
const char* password = "StarkSenses97";

const int trigPin = 12; //D6
const int echoPin1 = 14; //D5
const int echoPin2 = 13; //D5
const int echoPin3 = 15; //D5

long duration1;
long duration2;
long duration3;

int distance1Cm;
int distance2Cm;
int distance3Cm;

int temp1 = 0, temp2 = 0 , temp3 = 0;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readWaterLevel() {

  trig();
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculate the distance
  distance1Cm = duration1 * SOUND_VELOCITY/2;
  // Prints the distance on the Serial Monitor
  if(distance1Cm != 0) {
    temp1 = distance1Cm; // if else to avoid erroneous 000 values
  } else {
    distance1Cm = temp1;
  }
  
  delay(20);

  trig();
  duration2 = pulseIn(echoPin2, HIGH);
  distance2Cm = duration2 * SOUND_VELOCITY/2;
  if(distance2Cm != 0) {
    temp2 = distance2Cm;
  } else {
    distance2Cm = temp2;
  }
  
  delay(20);

  trig();
  duration3 = pulseIn(echoPin3, HIGH);
  distance3Cm = duration3 * SOUND_VELOCITY/2;
  if(distance3Cm != 0) {
    temp3 = distance3Cm;
  } else {
    distance3Cm = temp3;
  }
  Serial.println("TTA" + paddZeros(distance1Cm) + "TTB" + paddZeros(distance2Cm) + "TTC" + paddZeros(distance3Cm));
  return "TTA" + paddZeros(distance1Cm) + "TTB" + paddZeros(distance2Cm) + "TTC" + paddZeros(distance3Cm);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
  pinMode(echoPin3, INPUT); // Sets the echoPin3 as an Input
  
  Serial.println();

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/waterLevel", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readWaterLevel().c_str());
  });

  bool status;

  // Start server
  server.begin();
}

void loop(){
}

void trig() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
}

String paddZeros(int i) {
  String str = String(i);
  if (i < 100) {
    str = "0"+str;
  }
  if (i < 10) {
    str = "0"+str;
  }
  return str; // returning as string
}
