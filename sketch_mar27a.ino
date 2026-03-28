#include <math.h>
long duration;
float distance;
float oldDistance;
int freq;

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

  //Clean data
  // if((distance - oldDistance) > 10){
  //   distance = oldDistance;
  // }

  //Frequency 
  //freq = 440*pow(2, (distance/12));

  // freq = (distance * 20) + 200;
  
  //Scale programmed
  if(distance < 4){
    freq = 2093;
  } else if(distance < 7){
    freq = 2349.32;
  } else if(distance < 10){
    freq = 2637.02;
  } else if(distance < 13){
    freq = 2793.83;
  } else if(distance < 16){
    freq = 3135.96;
  } else if(distance < 19){
    freq = 3520;
  } else if(distance < 22){
    freq = 3951.07;
  } else if(distance < 38){
    freq = 4186.01;
  } else{
    freq = 0;
  }
  tone(8, freq);
  oldDistance = distance;

  //Print distance
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.println(freq);
  delay(3);
}