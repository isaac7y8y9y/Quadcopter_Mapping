#include <Ultrasonic.h>    //add needed library
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

float ultra1, ultra2, ultra3, ult1, ult2, ult3;

#define LSM9DS1_M  0x1E
#define LSM9DS1_AG  0x6B
#define PRINT_CALCULATED // This line is active - the more-useful calculated values will print - see below
// #define PRINT_RAW // This line is not active (commented out) 
#define PRINT_SPEED 250
#define DECLINATION -12 // Irvine, CA declination 

int quad, color;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//send serial monitor reading
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

void loop() 
{  
  Serial.print(ultrasonic1.Ranging(CM)); //monitor 3 sensors input in centimeters
  Serial.print(" cm");
  Serial.print(ultrasonic2.Ranging(CM));
  Serial.print(" cm");
  Serial.print(ultrasonic3.Ranging(CM));
  Serial.println(" cm");

  printGyro();  // Print "G: gx, gy, gz"
  printAccel(); // Print "A: ax, ay, az"
  printMag();   // Print "M: mx, my, mz"
  
  // Print the heading and orientation for fun!
  // Call print attitude. The LSM9DS1's magnetometer x and y
  // axes are opposite to the accelerometer, so my and mx are
  // substituted for each other.
  printAttitude(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);
  Serial.println();

  ult1=ultrasonic1.Ranging(CM); //convert serial read to variables
  ult2=ultrasonic2.Ranging(CM);
  ult3=ultrasonic3.Ranging(CM);

  ultra1 = 0;  //set ultra1,ultra2, ultra3 to 0
  ultra2 = 0;
  ultra3 = 0;

  ultra1 = ult1 * .032084; //cm to ft conversion
  ultra2 = ult2 * .032084;
  ultra3 = ult3 * .032084;

  if (ultra2 >0 and ultra2 <=5 and ultra3 >5 and ultra3 <=10) { //boolean for ranges of quadrant in ft
    quad = 1;
  }
  else if (ultra2 >5 and ultra2 <=10 and ultra3 >5 and ultra3 <=10) { //use sensors greater than initial range to prevent overlap
    quad = 2;
  }
  else if (ultra2 >5 and ultra2 <=10 and ultra3 >0 and ultra3 <=5) {
    quad = 3;
  }
  else if (ultra2 >0 and ultra2 <=5 and ultra3 >0 and ultra3 <=5) {
    quad = 4;
  }

  if (ultra1 >2 and ultra1 <= 3.5) {
    color = 4;//blue
  }
  else if (ultra1 >3.5 and ultra1 <= 5) {
    color = 3;//green
  }
  else if (ultra1 >5 and ultra1 <= 6.5) {
    color = 2;//red
  }
  else if (ultra1 >6.5) {
    color = 1;//white
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

void printGyro()
{
  // To read from the gyroscope, you must first call the
  // readGyro() function. When this exits, it'll update the
  // gx, gy, and gz variables with the most current data.
  imu.readGyro();
  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
#ifdef PRINT_CALCULATED //library for calcGyro
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
#endif
}

void printAccel()
{
  // To read from the accelerometer, you must first call the
  // readAccel() function. When this exits, it'll update the
  // ax, ay, and az variables with the most current data.
  imu.readAccel();
  
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
#ifdef PRINT_CALCULATED//to use calcAccel function, call the library
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
#elif defined PRINT_RAW 
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
#endif

}

void printMag()
{
  // To read from the magnetometer, you must first call the
  // readMag() function. When this exits, it'll update the
  // mx, my, and mz variables with the most current data.
  imu.readMag();
  
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
#ifdef PRINT_CALCULATED //call the library to use calcMag
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}

// Calculate pitch, roll, and heading.
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(float ax, float ay, float az, float mx, float my, float mz) {
  
  float roll = atan2(ay, az); //find degree of roll
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)); //degree of pitch
  
  float heading;
  if (my == 0) {
    heading = (mx < 0) ? 180.0 : 0;
  }
  else {
    heading = atan2(mx, my); //degree of heading
  }
    
  heading -= DECLINATION * PI / 180; //heading - declimatnio in radians

  int data;
  if (heading < -0.261667) { //-15 degree in radians
    Serial.println("Quad not aligned");
  }
  else if (heading > 0.261667) { //15 degree in radians
    Serial.println("Quad not aligned");
  }
  else {
    Serial.println("Quad aligned");
  }
  
  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
  
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); 
  Serial.println(heading, 2);
}
