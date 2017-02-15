// Sonar - simple ultrasonic sensor program
// by Jesse Lew

// Notes: Detects up to 164cm.

// set pins
const int trigPin = 8;
const int echoPin = 7;

// sonar function 
int getDistance() 
{
  long duration;        // duration of the ping 
  long centimeters;     // distance in cm

  // the sensor is triggered by a HIGH pulse of 10 or more microseconds
  // so give a short LOW pulse beforehand to ensure a clean HIGH pulse
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // record duration (in microseconds) of the HIGH pulse from 
  // the moment the ping is sent to the moment its echo is received
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // speed of sound is 29 microseconds per centimeter
  // the ping travels out and back so divide distance by 2
  centimeters = duration / 29 / 2;

  // display distance
  Serial.print(centimeters);
  Serial.print("cm");
  Serial.println();

  return centimeters;
}

void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // measure distance in cm
  int distance = getDistance();
  
  // do stuff with distance variable
  
  delay(100);
}
