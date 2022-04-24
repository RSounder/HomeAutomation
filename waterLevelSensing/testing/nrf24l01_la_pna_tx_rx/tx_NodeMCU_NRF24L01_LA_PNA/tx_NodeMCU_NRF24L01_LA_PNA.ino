#include <RH_NRF24.h>

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
}

void loop()
{
  Serial.println("Sending data to receiver");
  String dataString = "09107600";//String(ctime(&now));
  uint8_t dataArray[dataString.length()];
  dataString.getBytes(dataArray,dataString.length());
  nrf24.send(dataArray,sizeof(dataArray));
  nrf24.waitPacketSent();
  delay(5000);
}
