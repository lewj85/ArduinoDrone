// Sweep4Servos
// by Jesse Lew

#include <Servo.h> 

// create 4 servo objects (max 8 can be created) 
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

// variables that store servo position (clockwise and counter)
int pos = 0; 
int cclk = 180;


// set servo pins
void setup() 
{ 
  myservo1.attach(9);   // set servo 1 to pin 9
  myservo2.attach(10);  // set servo 2 to pin 10
  myservo3.attach(11);  // set servo 3 to pin 11
  myservo4.attach(3);   // set servo 4 to pin 3
} 
 

// servo rotate loop 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // from 0 to 180 degrees 
  {
    cclk = 180-pos;       // counterclockwise position is reverse
    myservo1.write(pos);  // move servo 1 to next position, clockwise 
    myservo2.write(pos);  // move servo 2 to next position, clockwise
    myservo3.write(cclk); // move servo 3 to next position, counterclockwise
    myservo4.write(cclk); // move servo 4 to next position, counterclockwise
    delay(15);            // wait 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)   // from 180 to 0 degrees 
  { 
    cclk = 180-pos;       // counterclockwise position is reverse
    myservo1.write(pos);  // move servo 1 to next position, clockwise
    myservo2.write(pos);  // move servo 2 to next position, clockwise
    myservo3.write(cclk); // move servo 3 to next position, counterclockwise
    myservo4.write(cclk); // move servo 4 to next position, counterclockwise
    delay(15);            // wait 15ms for the servo to reach the position 
  } 
}
