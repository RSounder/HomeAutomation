const int trigPin = 12; //D6

const int echoPin1 = 14; //D5
const int echoPin2 = 13; //D5
const int echoPin3 = 15; //D5

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration1;
long duration2;
long duration3;

float distance1Cm;
float distance2Cm;
float distance3Cm;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
  pinMode(echoPin3, INPUT); // Sets the echoPin3 as an Input
}

void loop() {

  trig();
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculate the distance
  distance1Cm = duration1 * SOUND_VELOCITY/2;
  // Prints the distance on the Serial Monitor
  if(distance1Cm != 0) {
    Serial.print("Distance1: ");
    Serial.println(distance1Cm);
  }
  
  delay(20);

  trig();
  duration2 = pulseIn(echoPin2, HIGH);
  distance2Cm = duration2 * SOUND_VELOCITY/2;
  if(distance2Cm != 0) {
    Serial.print("Distance2: ");
    Serial.println(distance2Cm);
  }
  
  delay(20);

  trig();
  duration3 = pulseIn(echoPin3, HIGH);
  distance3Cm = duration3 * SOUND_VELOCITY/2;
  if(distance3Cm != 0) {
    Serial.print("Distance3: ");
    Serial.println(distance3Cm);
  }

  Serial.println("---------------------");
  delay(2000);
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
