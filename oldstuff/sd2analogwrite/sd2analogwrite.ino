// Convert servodrone2 to analogWrite()
// by Jesse Lew

// tie each channel to pin on arduino
int aux1 = 5;
int aux2 = 6;
int throttle = 3;
int pitch = 9;
int roll = 10;
int yaw = 11;
bool turnON = true;


void setup()
{
}

void loop() 
{  
  if(turnON = true)
  {
    // unlock motors
    delay(2000);
    analogWrite(aux1, 20);
    
    delay(2000);
    analogWrite(aux2, 240);
    delay(2000);
    
    // calibrate
    analogWrite(pitch, 128);
    analogWrite(roll, 128);
    analogWrite(yaw, 128);
    
    // throttle up
    delay(1000);
    analogWrite(throttle, 40);

    turnON = false;
  }
}


