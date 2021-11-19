const byte trigPin = 10;
const byte echoPin = 9;
unsigned long d;

unsigned long ping() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, 23200);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  d = ping() / 58;
  Serial.println(String("") + d + " cm");
  delay(1000);
}
