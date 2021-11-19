const byte SWITCH1 = 10;
const byte SWITCH2 = 11;
const byte LED1 = 12;
const byte LED2 = 13;

void setup() {
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  bool sw1 = digitalRead(SWITCH1);
  bool sw2 = digitalRead(SWITCH2);
  (sw1) ? digitalWrite(LED1, HIGH) : digitalWrite(LED1, LOW);
//  digitalWrite(LED1, sw1);
  (sw2) ? digitalWrite(LED2, HIGH) : digitalWrite(LED2, LOW);
//  digitalWrite(LED2, sw2);
}
