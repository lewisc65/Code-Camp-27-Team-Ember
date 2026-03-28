long duration;
int distance;

const int trigPin = 10;
const int echoPin = 11;

//Vcc connected to 5v and Gnd connected to ground

void setup() {
  //Set Pins for input and output
  pinMode(trigPin, OUTPUT);  //Subject to change, needs to be digital
  pinMode(echoPin, INPUT);   //Subject to change, needs to be digital
  Serial.begin(9600);
}

void loop() {
  //Write trig low to start pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Data from Ultrasonic
  duration = pulseIn(echoPin, HIGH);

  //Conversion into centimeters
  distance = duration * 0.034 /2;

  //Print distance
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}