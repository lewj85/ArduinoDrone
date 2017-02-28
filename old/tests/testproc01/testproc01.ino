// Test Procedures 1
// by Jesse Lew

// Notes: It is turning but test values were too short. Back/forward
// pitch is reversed. 1501-2000 is forward, 1000-1499 is back.

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

// create 4 servo objects (max 8 can be created) 
Servo aux1;
Servo aux2;
Servo roll;
Servo pitch;
Servo yaw;
Servo throttle;

// initialize counter and procedures
long int cpt = 0;
bool startupProc = true;
bool testProc = true;

// variables that handle timer
unsigned long previousMillis = 0;   // stores last time servos were updated
const long interval = 50;   // set timer interval (ms)


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


// set servos to arduino pins
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
 

// main loop
void loop() 
{ 
  unsigned long currentMillis = millis();   // updates each loop
  //Serial.print(currentMillis);  

  // if the on/off switch is on
  if(digitalRead(13) == HIGH)
  {
    // run startup procedure once
    if(startupProc == true)
    {
      delay(1000);
      aux1.write(1100);   // turn aux1 (leveler) on with 1100
      aux2.write(1900);   // turn aux2 (motor lock) on with 1900
      delay(1500);
  
      // acceptable values: 885-2115, 
      // keeping between 1000-2000
      roll.write(1500);      // initialize center
      pitch.write(1500);     // initialize center
      yaw.write(1500);       // initialize center
      delay(1000);
      throttle.write(1000);  // minimum throttle
      
      startupProc = false;
    }
    
    if(testProc == true)
    {
      // test values
      delay(2000);
      throttle.write(1250);  // 25% throttle
      delay(1000);    
      throttle.write(1500);  // 50% throttle
      delay(1000);    
      throttle.write(1750);  // 75% throttle
      delay(1000);    
      //throttle.write(2000);  // 100% throttle
      //delay(1000);
      throttle.write(1500);  // 50% throttle
      delay(1000);
      roll.write(1400);      // roll left
      delay(250);
      roll.write(1600);      // roll right
      delay(250);
      roll.write(1500);      // center
      delay(1000);
      pitch.write(1400);     // pitch forward (went back)
      delay(250);
      pitch.write(1600);     // pitch back (went forward)
      delay(250);
      pitch.write(1500);     // center
      delay(1000);
      yaw.write(1400);       // spin left
      delay(250);
      yaw.write(1600);       // spin right
      delay(250);
      yaw.write(1500);       // center
      delay(1000);
      throttle.write(1000);  // minimum throttle
    
      testProc = false;
    }
  }
  else
  {
    throttle.write(1000);  // bring throttle to minimum
    aux2.write(1100);      // lock motors
    startupProc = true;    // reset startup procedure flag
  }
    
  // code that constantly runs before interval goes here 
  
  // if the interval time is reached, do something
  if(currentMillis - previousMillis >= interval)
  {
    // Display data counter
    Serial.print (cpt++,DEC);
    Serial.print ("\t");
   
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
    Serial.print ("aX\t");
    Serial.print (ax,DEC); 
    Serial.print ("\t");
    Serial.print ("aY\t");
    Serial.print (ay,DEC);
    Serial.print ("\t");
    Serial.print ("aZ\t");
    Serial.print (az,DEC);  
    Serial.print ("\t");
   
    // Gyroscope
    Serial.print ("gX\t");
    Serial.print (gx,DEC); 
    Serial.print ("\t");
    Serial.print ("gY\t");
    Serial.print (gy,DEC);
    Serial.print ("\t");
    Serial.print ("gZ\t");
    Serial.print (gz,DEC);  
    Serial.print ("\t");
  
    // End of line
    Serial.println("");
    
    // update previousMillis
    previousMillis = currentMillis;
  }
  
  // code that constantly runs after interval goes here 

}
