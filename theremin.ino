#include <math.h>
long duration;
float distance;
float oldDistance;
int freq;

const int trigPin = 10;
const int echoPin = 11;
//button for loop pedal
const int buttonPin = 13;
const int ledLoopingPin = 2; 

//Vcc connected to 5v and Gnd connected to ground

const int sample_rate_ms = 10; // delay - every frequency note is playing for 10ms
const int loop_duration_ms = 5000; // last 5000ms = last 5s
const int buffer_size = loop_duration_ms / sample_rate_ms;  //500 slots each 10 ms // buffer holds 500 frequencies

int freqBuffer[buffer_size] = {0};
int bufferIndex = 0;
bool isLooping = false;
int loopPlayIndex = 0;
bool lastButtonState = HIGH;

void setup() {
  //Set Pins for input and output
  pinMode(trigPin, OUTPUT);          //Subject to change, needs to be digital
  pinMode(echoPin, INPUT);           //Subject to change, needs to be digital
  pinMode(buttonPin, INPUT_PULLUP);  // standard for buttons
  pinMode(ledLoopingPin, OUTPUT);    // LED for isLooping
  Serial.begin(9600);
}

void loop() {

  //button stuff
  bool currentButtonState = digitalRead(buttonPin);
  // Serial.println(currentButtonState);


  if (lastButtonState == 0 && currentButtonState == 1) {  // button went from not pressed(0) to pressed(1)
    isLooping = !isLooping; // activate or deactivate looping based on what was happening
    Serial.println(isLooping);                            
    if (isLooping) {
      loopPlayIndex = bufferIndex;  //save loopPlayIndex
      digitalWrite(ledLoopingPin, HIGH);
    }
    if(!isLooping){
      digitalWrite(ledLoopingPin, LOW);
    }
  }
  lastButtonState = currentButtonState;

  if (!isLooping) {  // if not looping, read frequecies as usual

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
    distance = duration * 0.034 / 2;

    //Clean data
    // if((distance - oldDistance) > 10){
    //   distance = oldDistance;
    // }

    //Frequency
    //freq = 440*pow(2, (distance/12));

    // freq = (distance * 20) + 200;

    //Scale programmed
    if (distance < 4) {
      freq = 2093;
    } else if (distance < 7) {
      freq = 2349.32;
    } else if (distance < 10) {
      freq = 2637.02;
    } else if (distance < 13) {
      freq = 2793.83;
    } else if (distance < 16) {
      freq = 3135.96;
    } else if (distance < 19) {
      freq = 3520;
    } else if (distance < 22) {
      freq = 3951.07;
    } else if (distance < 38) {
      freq = 4186.01;
    } else {
      freq = 0;
    }
    tone(8, freq);
    oldDistance = distance;

    //Print distance
    // Serial.print("Distance: ");
    // Serial.println(distance);
    // Serial.println(freq);
    // delay(3);

    freqBuffer[bufferIndex] = freq; 
    bufferIndex = (bufferIndex + 1) % buffer_size;


    
  } else {  // if looping, then play frequencies in buffer
    int playFreq = freqBuffer[loopPlayIndex];
    tone(8, playFreq); 
    loopPlayIndex = (loopPlayIndex + 1) % buffer_size;
  }
  delay(sample_rate_ms); // delay 10 ms - each frequency plays for 10 ms

}
