// Sweep4Millis
// by Jesse Lew

#include <Servo.h> 

// create 4 servo objects (max 8 can be created) 
Servo aux1;
Servo aux2;
Servo channel1;
Servo channel2;
Servo channel3;
Servo channel4;

bool turnON = true;

// variables that handle timer
unsigned long previousMillis = 0;   // stores last time servos were updated
const long interval = 100;   // set timer interval to 100ms


// set servos to arduino pins
void setup() 
{ 
  // can add min/max values with attach(pin#, min#, max#)
  aux1.attach(5);     // set AUX1 to pin 5
  aux2.attach(6);     // set AUX2 to pin 6
  channel1.attach(11);    // set servo 1 to pin 11
  channel2.attach(9);     // set servo 2 to pin 9
  channel3.attach(10);    // set servo 3 to pin 10
  channel4.attach(3);     // set servo 4 to pin 3
  
//  Serial.begin(9600);
} 
 

// servo rotate loop. uses 15ms timer to count down to next servo instruction
void loop() 
{ 
  unsigned long currentMillis = millis();   // updates each loop
//  Serial.print(currentMillis);
//  Serial.print('\n');
  
  
  if(turnON = true)
  {
    aux1.write(100);  // turn aux1 on with value: 55
    aux2.write(129);  // turn aux2 (the motors) on

    // acceptable values: 33-152, middle: 92/93 
    // cleanflight shows 885-2115, 1000-2000 is 44-141
    channel1.write(113);  // roll
    channel2.write(93);   // pitch
    channel3.write(73);   // yaw
    channel4.write(53);   // throttle  
    
    turnON = false;
  }
  
  // code that constantly runs goes here
  
  
  // if the interval time (15ms) is reached, update servos
  if(currentMillis - previousMillis >= interval)
  {
  
        
  } 
}
