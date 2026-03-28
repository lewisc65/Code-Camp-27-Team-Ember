int buttonPin = 13;
int ledPin = 12;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(buttonPin, INPUT);    // sets the digital pin 7 as input
  Serial.begin(9000);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(buttonPin);
  Serial.println(val);
  delay(50);
}
