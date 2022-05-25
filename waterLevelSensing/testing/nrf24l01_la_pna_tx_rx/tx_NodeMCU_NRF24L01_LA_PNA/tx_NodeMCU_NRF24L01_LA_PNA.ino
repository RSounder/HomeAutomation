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

}

void loop()
{
  String rawData = "A087B045C099D088E078";

  uint8_t dataArray[rawData.length()];
  rawData.getBytes(dataArray,rawData.length());
  nrf24.send(dataArray,sizeof(dataArray));
  nrf24.waitPacketSent();
  delay(5000);
}
