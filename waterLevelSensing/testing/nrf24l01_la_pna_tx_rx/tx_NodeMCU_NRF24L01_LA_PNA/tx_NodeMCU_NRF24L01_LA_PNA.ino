#include <RH_NRF24.h>
#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "Stark";
const char* password = "eachday97";

RH_NRF24 nrf24(2,4);

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  if (!nrf24.init())
    Serial.println("initialization failed");
  if (!nrf24.setChannel(1))
    Serial.println("Channel set failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("RF set failed");

   Serial.setDebugOutput(true);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  configTime(11*1800, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop()
{
  Serial.println("Sending data to receiver");
  time_t now = time(nullptr);
  String timestring = String(ctime(&now));
  uint8_t dataArray[timestring.length()];
  timestring.getBytes(dataArray,timestring.length());
  nrf24.send(dataArray,sizeof(dataArray));
  nrf24.waitPacketSent();
  delay(1000);
}
