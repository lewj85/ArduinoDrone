// Servo Drone 2
// by Jesse Lew

#include <Servo.h> 

// create 4 servo objects (max 8 can be created) 
Servo aux1;
Servo aux2;
Servo roll;
Servo pitch;
Servo yaw;
Servo throttle;

bool turnON = true;

// variables that handle timer
unsigned long previousMillis = 0;   // stores last time servos were updated
const long interval = 100;   // set timer interval to 100ms


// set servos to arduino pins
void setup() 
{ 
  // can add min/max values with attach(pin#, min#, max#)
  aux1.attach(5);      // set AUX1 to pin 5
  aux2.attach(6);      // set AUX2 to pin 6
  roll.attach(11);     // set roll to pin 11
  pitch.attach(9);     // set pitch 2 to pin 9
  yaw.attach(10);      // set yaw to pin 10
  throttle.attach(3);  // set throttle to pin 3
  
  //Serial.begin(9600);
} 
 

// servo rotate loop. uses 15ms timer to count down to next servo instruction
void loop() 
{ 
  unsigned long currentMillis = millis();   // updates each loop
  //Serial.print(currentMillis);  
  
  // run once, at start
  if(turnON = true)
  {
    delay(1000);
    aux1.write(1500);  // turn aux1 on with 1100
    delay(1000);
    aux2.write(1900);   // turn aux2 on (unlock motors) with 1900
    delay(2000);

    // acceptable values: 885-2115, 
    // keeping between 1000-2000
    roll.write(1500);      // initialize center
    pitch.write(1500);     // initialize center
    yaw.write(1500);       // initialize center
    delay(1000);
    throttle.write(1000);  // minimum throttle
    
    turnON = false;
  }
    
  // code that constantly runs goes here 
  
  // if the interval time is reached, do something
  if(currentMillis - previousMillis >= interval)
  {
    // code that runs every set interval goes here
  }
}
