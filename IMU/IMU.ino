// IMU, read values off MPU9250
// by Jesse Lew

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

// initialize counter
long int cpt=0;

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
    Data[index++]=Wire.read();
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
 
 
// Initializations
void setup()
{
  // Arduino initializations
  Wire.begin();
  Serial.begin(9600);
 
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
}


// Main loop, read and display data
void loop()
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
  delay(50);    
}
