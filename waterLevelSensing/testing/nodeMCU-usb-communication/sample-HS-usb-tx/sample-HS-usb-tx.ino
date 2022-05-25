#include <RH_NRF24.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(1, 3);
RH_NRF24 nrf24(2,4);
String str;

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

  espSerial.begin(9600);
  delay(2000);

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
      String dataStr = String((char*)buf);
      espSerial.println(dataStr);
    }
    else
    {
      Serial.println("recv failed");
      espSerial.println("RF Error");
    }
  } else {
      espSerial.println("No RF found");
  }
}
 
