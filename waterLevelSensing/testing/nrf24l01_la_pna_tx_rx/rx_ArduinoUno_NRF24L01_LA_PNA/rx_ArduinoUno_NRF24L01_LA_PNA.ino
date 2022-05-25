#include <RH_NRF24.h>

RH_NRF24 nrf24;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ;
  if (!nrf24.init())
    Serial.println("initialization failed");
  if (!nrf24.setChannel(1))
    Serial.println("Channel Set failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("RF set failed");

    delay(1000);
}

void loop()
{
  if (nrf24.available())
  {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if(nrf24.recv(buf, &len))
    {
      Serial.print("Received: ");
      Serial.println((char*)buf);
      String data=String((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
