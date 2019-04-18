// define pins numbers
const int trigPin = 9;
const int echoPin = 10;

// define variables
long duration;
int distances; 

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // trigPin as output
  pinMode(echoPin, INPUT); // echoPin as input
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distances = duration*0.034/2;
  if(distances <= 10){
    digitalWrite(LED_BUILTIN, HIGH);
  }

  else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance is: ");
  Serial.println(distances);
}
