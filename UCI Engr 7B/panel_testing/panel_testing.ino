int quad, color;

void setup()
{
  Serial.begin(9600); // Your code must operate that this speed.
}
void loop()
{  
  quad=1;
  color=1;
  
  /* ***** The following 6 lines of code are IMPORTANT and must be executed in this EXACT order ***** */ 
  char a = 'E'; // Define character E to be used as indicator - see next line
  Serial.write(a); //FIRST: Send 'E' which indicates a new set of data is being transmitted
  // SECOND: Send the quadrant number as two bytes
  Serial.write(quad/256); // returns INTEGER of division (e.g. 7/3 = 2)
  Serial.write(quad%256); // returns the REMAINDER of quadrant number divided by 256 (e.g. 7%3 = 1)
  // THIRD: Send the color number as two bytes
  Serial.write(color/256);
  Serial.write(color%256);
  delay(100);

  quad=2;
  color=1;

    /* ***** The following 6 lines of code are IMPORTANT and must be executed in this EXACT order ***** */ 
  Serial.write(a); //FIRST: Send 'E' which indicates a new set of data is being transmitted
  // SECOND: Send the quadrant number as two bytes
  Serial.write(quad/256); // returns INTEGER of division (e.g. 7/3 = 2)
  Serial.write(quad%256); // returns the REMAINDER of quadrant number divided by 256 (e.g. 7%3 = 1)
  // THIRD: Send the color number as two bytes
  Serial.write(color/256);
  Serial.write(color%256);
  delay(100);

  
  quad=3;
  color=1;

    /* ***** The following 6 lines of code are IMPORTANT and must be executed in this EXACT order ***** */ 
  Serial.write(a); //FIRST: Send 'E' which indicates a new set of data is being transmitted
  // SECOND: Send the quadrant number as two bytes
  Serial.write(quad/256); // returns INTEGER of division (e.g. 7/3 = 2)
  Serial.write(quad%256); // returns the REMAINDER of quadrant number divided by 256 (e.g. 7%3 = 1)
  // THIRD: Send the color number as two bytes
  Serial.write(color/256);
  Serial.write(color%256);
  delay(100);

  
  quad=4;
  color=1;

    /* ***** The following 6 lines of code are IMPORTANT and must be executed in this EXACT order ***** */ 
  Serial.write(a); //FIRST: Send 'E' which indicates a new set of data is being transmitted
  // SECOND: Send the quadrant number as two bytes
  Serial.write(quad/256); // returns INTEGER of division (e.g. 7/3 = 2)
  Serial.write(quad%256); // returns the REMAINDER of quadrant number divided by 256 (e.g. 7%3 = 1)
  // THIRD: Send the color number as two bytes
  Serial.write(color/256);
  Serial.write(color%256);
  delay(100);

}
 
