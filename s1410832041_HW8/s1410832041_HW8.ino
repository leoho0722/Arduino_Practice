const int speaker = 13;
int freq[] = {262, 294, 330, 349, 392};
int melody[] = {5,3,3,4,2,2,1,2,3,4,5,5,5,5,3,3,4,2,2,1,3,5,5,3,2,2,2,2,2,3,4,3,3,3,3,3,4,5,5,3,3,4,2,2,1,3,5,5,1};
int beat[] = {1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4};

void setup() {
  pinMode(speaker, OUTPUT);
}

void loop() {
  for (int i = 0; i < 49; i++) {
    tone(speaker, freq[melody[i]-1]);
    delay(beat[i]*250);
    noTone(speaker);
    delay(0);
  }
  delay(1000);
}
