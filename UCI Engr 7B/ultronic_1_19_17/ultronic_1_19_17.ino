#include <Ultrasonic.h>

Ultrasonic ultrasonic(12,13); //sensor object named "ultrasonic
                              //trigger is pin 12, echo is pin 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ultrasonic.Ranging(CM));//print out distance in centimeter
  Serial.println(" cm"); //print a space and cm, then start new line
  delay(100);
}
