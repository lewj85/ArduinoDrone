// Sweep4Millis
// by Jesse Lew

#include <Servo.h> 

// create 4 servo objects (max 8 can be created) 
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// variables that store servo position for clockwise / counterclockwise motion
int pos = 0;                // position
int cpos = 180;             // counter position
bool clockwise == true;     // initialize clockwise motion

// variables that handle timer
unsigned long previousMillis = 0;   // stores last time servos were updated
const long interval = 15;   // set timer interval to 15ms


// set servos to arduino pins
void setup() 
{ 
  myservo1.attach(9);       // set servo 1 to pin 9
  myservo2.attach(10);      // set servo 2 to pin 10
  myservo3.attach(11);      // set servo 3 to pin 11
  myservo4.attach(3);       // set servo 4 to pin 3
} 
 

// servo rotate loop. uses 15ms timer to count down to next servo instruction
void loop() 
{ 
  unsigned long currentMillis = millis();   // updates each loop
  
  
  // code that constantly runs goes here
  
  
  // if the interval time (15ms) is reached, update servos
  if(currentMillis - previousMillis >= interval)
  {
    if(clockwise == true && pos < 180)      // from 0 to 179 degrees 
    {
      pos++;                // update clockwise position
      cpos = 180-pos;       // update counterclockwise position
      myservo1.write(pos);  // move servo 1 to next position, clockwise 
      myservo2.write(pos);  // move servo 2 to next position, clockwise
      myservo3.write(cpos); // move servo 3 to next position, counterclockwise
      myservo4.write(cpos); // move servo 4 to next position, counterclockwise
    } 
    else if(clockwise == false && pos > 0)  // from 180 to 1 degree
    { 
      pos--;                // update counterclockwise position
      cpos = 180-pos;       // update clockwise position
      myservo1.write(pos);  // move servo 1 to next position, counterclockwise
      myservo2.write(pos);  // move servo 2 to next position, counterclockwise
      myservo3.write(cpos); // move servo 3 to next position, clockwise
      myservo4.write(cpos); // move servo 4 to next position, clockwise
    } 
    else if(clockwise == true && pos > 179) // at 180 degrees
    {
      // sentinel value reached, reverse directions of pos and cpos
      pos--;                // update counterclockwise position
      cpos = 180-pos;       // update clockwise position
      myservo1.write(pos);  // move servo 1 to next position, counterclockwise 
      myservo2.write(pos);  // move servo 2 to next position, counterclockwise
      myservo3.write(cpos); // move servo 3 to next position, clockwise
      myservo4.write(cpos); // move servo 4 to next position, clockwise
      clockwise == false;   // set flag to move counterclockwise
    }      
    else // (clockwise == false && pos < 1)   // at 0 degrees
    {
      // sentinel value reached, reverse directions of pos and cpos
      pos++;                // update clockwise position
      cpos = 180-pos;       // update counterclockwise position
      myservo1.write(pos);  // move servo 1 to next position, clockwise 
      myservo2.write(pos);  // move servo 2 to next position, clockwise
      myservo3.write(cpos); // move servo 3 to next position, counterclockwise
      myservo4.write(cpos); // move servo 4 to next position, counterclockwise
      clockwise == true;    // set flag to move clockwise
    }
  }
}
