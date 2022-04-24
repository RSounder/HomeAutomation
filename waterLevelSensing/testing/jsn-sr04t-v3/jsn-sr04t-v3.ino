#include <HCSR04.h>
HCSR04 hc(13, 12); // Initialize Pin D7, D6
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int distance = hc.dist();
  if(distance != 0) {
    Serial.println(distance); // Print in centimeters the value from the sensor
  }
  delay(1000);
}
