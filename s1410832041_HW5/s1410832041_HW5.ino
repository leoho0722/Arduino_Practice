/* 定義 LED 腳位 */
const byte LED1 = 7;
const byte LED2 = 8;

/* 定義光敏電阻腳位 */
const byte Cds = A0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  int val;
  val = analogRead(Cds);
  Serial.println(val);
  if (val <= 400) {
    /* 非常暗 */
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  } else if (val > 400 && val <= 700) {
    /*普通暗*/
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  } else if (val > 700) {
    /*天亮*/
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  delay(100);
}
