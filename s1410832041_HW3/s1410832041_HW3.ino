// 期中考會考類似的題目

/*
按鈕１：定義為腳位 4，LED 左旋
按鈕２:定義為腳位 5，LED 右旋
按鈕３：定義為腳位 6，LED 全亮
按鈕４：定義為腳位 7，LED 全熄
*/
const byte SWITCHs[] = {4, 5, 6, 7};

/*
LED1：定義為腳位 8
LED2：定義為腳位 9
LED3：定義為腳位 10
LED4：定義為腳位 11
LED5：定義為腳位 12
*/
const byte LEDs[] = {8, 9, 10, 11, 12};

int i;
char val;

void setup() {
  for (i = 0; i < 4; i++) {
    pinMode(SWITCHs[i], INPUT);
  }
  for (i = 0; i < 5; i++) {
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);
  }
  Serial.begin(9600);
  Serial.println("Arduino Uno Success Connect");
}

void loop() {
  /* HW2，用按鈕控制 */
  bool sw1 = !digitalRead(SWITCHs[0]);
  bool sw2 = !digitalRead(SWITCHs[1]);
  bool sw3 = !digitalRead(SWITCHs[2]);
  bool sw4 = !digitalRead(SWITCHs[3]);

  if (sw1) {
    btn1_func();
  } 
  
  if (sw2) {
    btn2_func();
  }
  
  if (sw3) {
    btn3_func();
  }
  
  if (sw4) {
    btn4_func();
  }
  
  /* HW3，用 Serial Port 控制 */
  if (Serial.available()) {
    Serial.println("Serial available");
    val = Serial.read();
    if (val == '1') {
      btn1_func();
    } else if (val == '2') {
      btn2_func();
    } else if (val == '3') {
      btn3_func();
    } else if (val == '4') {
      btn4_func();
    }
  }
  
}

/* LED 初始化 */
void led_init() {
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], LOW);
  }
}

/* 按鈕1：左旋 */
void btn1_func() {
  Serial.println("Button1：Left");
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], HIGH);
    delay(100);
    digitalWrite(LEDs[i], LOW);
  }
}

/* 按鈕2：右旋 */
void btn2_func() {
  Serial.println("Button2：Right");
  for (i = 4; i > -1; i--) {
    digitalWrite(LEDs[i], HIGH);
    delay(100);
    digitalWrite(LEDs[i], LOW);
  }
}

/* 按鈕3：LED 全亮 */
void btn3_func() {
  Serial.println("Button3：HighLight");
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], HIGH);
  }
}

/* 按鈕4：LED 全熄 */
void btn4_func() {
  Serial.println("Button4：Dark");
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], LOW);
  }
}
