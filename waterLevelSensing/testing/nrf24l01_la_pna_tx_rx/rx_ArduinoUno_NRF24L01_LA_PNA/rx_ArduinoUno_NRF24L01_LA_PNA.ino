#include <RH_NRF24.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);

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

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("   Welcome to        ");
    lcd.setCursor(0, 1);
    lcd.print(" Circuit Digest      ");

    delay(1000);
    lcd.clear();
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
      lcd.setCursor(0,0);
      lcd.print(data.substring(0,10));
      lcd.setCursor(11,0);
      lcd.print(data.substring(20,24));
      lcd.setCursor(0,1);
      lcd.print("Time:");
      lcd.setCursor(6,1);
      lcd.print(data.substring(11,19));
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
