// Sonar Drone 02 - Test flight program with altitude control
// by Jesse Lew

// Notes: 70% takeoff. COG pitch 1515. throttlechange = 3.
// Need to add landing procedures.

#include <Servo.h> 
#include <Wire.h> 
 
#define    MPU9250_ADDRESS            0x68

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18
 
#define    ACC_FULL_SCALE_2_G         0x00  
#define    ACC_FULL_SCALE_4_G         0x08
#define    ACC_FULL_SCALE_8_G         0x10
#define    ACC_FULL_SCALE_16_G        0x18

// create 6 servo objects (max 8 can be created) 
Servo aux1;
Servo aux2;
Servo roll;
Servo pitch;
Servo yaw;
Servo throttle;

// declare value variables - initialized in startup procedures
int rollVal;
int pitchVal;
int yawVal;
int throttleVal;
int minThrottle = 1000;
int maxThrottle = 2000;

// initialize counter and procedures
long int cpt = 0;
bool startupProc = true;
bool testProc = true;

// variables that handle timer
unsigned long currentMillis = 0;    // initialize timer
unsigned long previousMillis = 0;   // stores last timer
const long interval = 50;   // set timer interval (ms)

// sonar pins/variables
const int trigPin = 7;
const int echoPin = 8;
int altitude = 2;         // initialize to 2cm
int newAltitude;          // for storing acceptable new altitude
int altitudeChange = 10;  // range of acceptable altitude changes (cm)
int desiredAltitude = 20; // hover altitude (cm)
int throttleChange = 3;   // amount to adjust throttle by (*0.1%)

// sonar function 
int getDistance() 
{
  long duration;          // duration of the ping 
  long centimeters;       // distance in cm

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


void shutdownProc()
{
    //throttle.write(1000);  // bring throttle to minimum
    aux2.write(1100);        // lock motors
    //Serial.print("motors should be locked now");
    //startupProc = true;      // reset startup procedure flag
}


// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
 
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
  {
    Data[index++]=Wire.read();
  }
}
 
 
// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


// SETUP
// set arduino pins
void setup() 
{ 
  // can add min/max values with attach(pin#, min#, max#)
  aux1.attach(5);      // set AUX1 (leveler) to pin 5
  aux2.attach(6);      // set AUX2 (motor lock) to pin 6
  roll.attach(11);     // set roll to pin 11
  pitch.attach(9);     // set pitch 2 to pin 9
  yaw.attach(10);      // set yaw to pin 10
  throttle.attach(3);  // set throttle to pin 3
  
  // on/off ARM/level switch
  pinMode(13, INPUT);
  
  // Arduino initializations
  Wire.begin();
  Serial.begin(9600);
  
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
} 
 

// MAIN LOOP
void loop() 
{ 
  currentMillis = millis();   // updates each loop
  //Serial.print(currentMillis);

  // if the on/off switch is on
  if(digitalRead(13) == HIGH)
  {
    // run startup procedure once
    // STARTUP PROCEDURES
    //Serial.print("made it to startup proc");
    if(startupProc == true)
    {
      Serial.print("Startup initiated.");
      Serial.println("");
      delay(1000);
      Serial.print("Setting Aux1.");
      Serial.println("");
      aux1.write(1100);   // turn aux1 (leveler) on with 1100
      delay(1000);
  
      // acceptable values: 885-2115 
      // keeping between: 1000-2000
      Serial.print("Setting initial values to roll, pitch, yaw, throttle.");
      Serial.println("");
      rollVal = 1500;          // set starting roll
      pitchVal = 1515;         // set starting pitch
      yawVal = 1500;           // set starting yaw
      throttleVal = minThrottle;      // minimum throttle
      delay(500);

      Serial.print("Writing those values now.");
      Serial.println("");
      roll.write(rollVal);     // initialize drone
      pitch.write(pitchVal);   // initialize drone
      yaw.write(yawVal);       // initialize drone
      throttle.write(throttleVal);  // minimum throttle
      delay(2000);
      
      // unlocking motors
      Serial.print("Unlocking motors now.");
      Serial.println("");
      aux2.write(1900);   // turn aux2 (motor lock) off with 1900
      delay(2000);
      
      startupProc = false;
    }
    
    // TEST PROCEDURES
    if(testProc == true)
    {
      Serial.print("Starting test procedure.");
      Serial.println("");
      // test values
      delay(1000);
      throttleVal = 1700;
      throttle.write(throttleVal);  // 70% throttle

      testProc = false;
    }
    
    // if the interval time is reached, do something
    if((currentMillis - previousMillis) >= interval)
    {
      // get altitude from sonar
      //newAltitude = getDistance();
      //Serial.print("the newAltitude is: ");
      //Serial.print(newAltitude);
      
      // if newAltitude is within 10cm of old value, update altitude
      // else ignore the bad read (do not update altitude)
      if((newAltitude - altitude) > (-1*altitudeChange) && \
      (newAltitude - altitude) < altitudeChange)
      {
        altitude = newAltitude;
        //Serial.print("altitude set to: ");
        //Serial.println(altitude);
      }
      
      // display distance
      //Serial.print(altitude);
      //Serial.print("cm");
      //Serial.println();
      
      // if altitude == desiredAltitude, don't do anything
      if(altitude == desiredAltitude)
      {
        //Serial.print("should not change. throttleVal = ");
        //Serial.print(throttleVal);
        //Serial.println();
      }
      // else if altitude too low, increase throttle incrementally
      // but never go beyond maximum value of 2000
      else if(altitude < desiredAltitude && throttleVal < maxThrottle)
      {
        throttleVal+=throttleChange; // set new throttle
        throttle.write(throttleVal); // send new throttle
        //Serial.print("should be increasing. throttleVal = ");
        //Serial.print(throttleVal);
        //Serial.println();
      }
      // else if altitude too high, decrease throttle incrementally
      // but never go beyond minimum value of 1000
      else if(altitude > desiredAltitude && throttleVal > minThrottle)
      {
        throttleVal-=throttleChange; // set new throttle
        throttle.write(throttleVal); // send new throttle
        //Serial.print("should be decreasing. throttleVal = ");
        //Serial.print(throttleVal);
        //Serial.println();
      }
      
      // Display data counter
      //Serial.print (cpt++,DEC);
      //Serial.print ("\t");
     
      // Read accelerometer and gyroscope
      uint8_t Buf[14];
      I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
     
     
      // Create 16 bits values from 8 bits data
     
      // Accelerometer
      int16_t ax=-(Buf[8]<<8 | Buf[9]);
      int16_t ay=-(Buf[10]<<8 | Buf[11]);
      int16_t az=Buf[12]<<8 | Buf[13];
     
      // Gyroscope
      int16_t gx=-(Buf[0]<<8 | Buf[1]);
      int16_t gy=-(Buf[2]<<8 | Buf[3]);
      int16_t gz=Buf[4]<<8 | Buf[5];
    
     
      // Display values
      
      // Accelerometer
      //Serial.print ("aX\t");
      //Serial.print (ax,DEC); 
      //Serial.print ("\t");
      //Serial.print ("aY\t");
      //Serial.print (ay,DEC);
      //Serial.print ("\t");
      //Serial.print ("aZ\t");
      //Serial.print (az,DEC);  
      //Serial.print ("\t");
     
      // Gyroscope
      //Serial.print ("gX\t");
      //Serial.print (gx,DEC); 
      //Serial.print ("\t");
      //Serial.print ("gY\t");
      //Serial.print (gy,DEC);
      //Serial.print ("\t");
      //Serial.print ("gZ\t");
      //Serial.print (gz,DEC);  
      //Serial.print ("\t");
    
      // End of line
      //Serial.println("");
      
      // update previousMillis
      previousMillis = currentMillis;
    }
  }
  else
  {
    shutdownProc(); // run shutdown procedures
  }
    
  // code that constantly runs before interval goes here 
  
  // min throttle after 20 seconds
  if(currentMillis > 25000)
  {
    //landProc();     // run landing procedures
    shutdownProc(); // run shutdown procedures
    Serial.print ("You're not supposed to read this for 25 seconds");
  }
}
