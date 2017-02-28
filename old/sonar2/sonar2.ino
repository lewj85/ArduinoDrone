// Sonar2 - ultrasonic sensor program that avoids bad reads
// by Jesse Lew

// Notes: Detects up to 164cm. Assumes initial read is at 2cm
// because this will be used on an altitude sensor for a drone.
// While the drone has not taken off, the initial altitude is 2cm.


// variables that handle timer
unsigned long currentMillis = 0;    // initialize timer
unsigned long previousMillis = 0;   // stores last timer
const long interval = 50;   // set timer interval (ms)

// sonar pins/variables
const int trigPin = 8;
const int echoPin = 7;
int altitude = 2; // initialize to 2cm
int newAltitude;

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
  //Serial.print(centimeters);
  //Serial.print("cm");
  //Serial.println();

  return centimeters;
}

void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  currentMillis = millis();   // updates each loop
  //Serial.print(currentMillis);

  // if the interval time is reached, do something
  if((currentMillis - previousMillis) >= interval)
  {
    // display distance
    //Serial.print(altitude);
    //Serial.print("cm");
    //Serial.println();
    
    // get altitude from sonar
    newAltitude = getDistance();
    Serial.print("the newAltitude is: ");
    Serial.print(newAltitude);
    Serial.println();
    
    // if newAltitude is within 10cm of old value, update altitude
    // else ignore the bad read (do not update altitude)
    if((newAltitude - altitude) > -10 && (newAltitude - altitude) < 10)
    {
      altitude = newAltitude;
      Serial.print("altitude set to: ");
      Serial.print(altitude);
      Serial.println();
    }
    else
    {
      Serial.print("altitude still: ");
      Serial.print(altitude);
      Serial.println();
    }
    
    // update previousMillis
    previousMillis = currentMillis;
  }
}
