const byte LED = 8;
const byte MIC = A0;
bool toggle = false;
int max_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    int val = analogRead(MIC);
    if (val > max_value) {
      max_value = val;
    }
    delay(1);
  }
  Serial.println(max_value);
  if (max_value > 64) {
    toggle = !toggle;
    digitalWrite(LED, toggle);
  }
  max_value = 0;
}
