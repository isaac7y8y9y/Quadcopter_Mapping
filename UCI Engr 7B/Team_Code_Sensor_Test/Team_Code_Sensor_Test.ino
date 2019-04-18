#include <Ultrasonic.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

Ultrasonic ultrasonic1(12,13); //ultrasonic 1 downward output 12, input 13
Ultrasonic ultrasonic2(8,7); //ultrasonic 2 left output 8, input 7
Ultrasonic ultrasonic3(4,2); //ultrasonic 3 front output 4, input 2

LSM9DS1 imu; // Name IMU object "imu"

float roll;
float pitch;
float heading;
float AX;
float AY;
float AZ;
float MX;
float MY;
float MZ;

float ultra1;
float ultra2;
float ultra3;

float ult1, ult2, ult3;

#define LSM9DS1_M  0x1E
#define LSM9DS1_AG  0x6B
#define PRINT_CALCULATED // This line is active - the more-useful calculated values will print - see below
// #define PRINT_RAW // This line is not active (commented out) 
#define PRINT_SPEED 250
#define DECLINATION -12 // Irvine, CA declination 

int quad, color;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  if (!imu.begin()) // This line means "If the IMU does NOT(!) begin, print the following message..."
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1); // wait forever 
    }
}

void loop() {  

  // put your main code here, to run repeatedly:
  Serial.print(ultrasonic1.Ranging(CM));
  Serial.print(" cm");
  Serial.print(ultrasonic2.Ranging(CM));
  Serial.print(" cm");
  Serial.print(ultrasonic3.Ranging(CM));
  Serial.println(" cm");

  ult1=ultrasonic1.Ranging(CM);
  ult2=ultrasonic2.Ranging(CM);
  ult3=ultrasonic3.Ranging(CM);
  
  ultra1 = 0;
  ultra2 = 0;
  ultra3 = 0;
  
  ultra1 = ult1 * .032084;
  ultra2 = ult2 * .032084;
  ultra3 = ult3 * .032084;

  if (ultra2 >0 and ultra2 <=5 and ultra3 >5 and ultra3 <=10) {
    quad = 1;
  }
  else if (ultra2 >5 and ultra2 <=10 and ultra3 >5 and ultra3 <=10) {
    quad = 2;
  }
  else if (ultra2 >5 and ultra2 <=10 and ultra3 >0 and ultra3 <=5) {
    quad = 3;
  }
  else if (ultra2 >0 and ultra2 <=5 and ultra3 >0 and ultra3 <=5) {
    quad = 4;
  }

  if (ultra1 >2 and ultra1 <= 3.5) {
    color = 4;
  }
  else if (ultra1 >3.5 and ultra1 <= 5) {
    color = 3;
  }
  else if (ultra1 >5 and ultra1 <= 6.5) {
    color = 2;
  }
  else if (ultra1 >6.5) {
    color = 1;
  }

  /* ***** The following 6 lines of code are IMPORTANT and must be executed in this EXACT order ***** */ 
  char a = 'E'; // Define character E to be used as indicator - see next line
  Serial.write(a); //FIRST: Send 'E' which indicates a new set of data is being transmitted
  Serial.write(quad/256); // returns INTEGER of division (e.g. 7/3 = 2)
  Serial.write(quad%256); // returns the REMAINDER of quadrant number divided by 256 (e.g. 7%3 = 1)
  // THIRD: Send the color number as two bytes
  Serial.write(color/256);
  Serial.write(color%256);
  delay(10);

}


