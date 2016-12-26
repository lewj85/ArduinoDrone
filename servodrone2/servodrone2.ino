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
  
  if(turnON = true)
  {
    delay(1000);
    aux1.write(100);   // turn aux1 on with value: 55
    delay(1000);
    aux2.write(129);   // turn aux2 (the motors) on
    delay(2000);

    // acceptable values: 33-152, middle: 93 
    // cleanflight 885-2115, 1000-2000 is 44-141
    roll.write(93);      // initialize center
    pitch.write(93);     // initialize center
    yaw.write(93);       // initialize center
    delay(1000);
    throttle.write(44);  // minimum throttle
    
    // test values
    delay(2000);
    throttle.write(68);  // 25% throttle
    delay(1000);    
    throttle.write(93);  // 50% throttle
    delay(1000);    
    throttle.write(117); // 75% throttle
    delay(1000);    
    throttle.write(141); // 100% throttle
    delay(1000);
    throttle.write(93);  // 50% throttle
    delay(1000);
    roll.write(44);      // roll left
    delay(1000);
    roll.write(141);     // roll right
    delay(1000);
    roll.write(93);      // center
    delay(1000);
    pitch.write(44);     // pitch forward
    delay(1000);
    pitch.write(141);    // pitch back
    delay(1000);
    pitch.write(93);     // center
    delay(1000);
    yaw.write(44);       // spin left
    delay(1000);
    yaw.write(141);      // spin right
    delay(1000);
    yaw.write(93);       // center

    turnON = false;
  }
  
  // code that constantly runs goes here
  
  
  // if the interval time (15ms) is reached, update servos
  if(currentMillis - previousMillis >= interval)
  {
   
  }
}
