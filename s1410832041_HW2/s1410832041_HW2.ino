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

void setup() {
  for (i = 0; i < 4; i++) {
    pinMode(SWITCHs[i], INPUT);
  }
  for (i = 0; i < 5; i++) {
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);
  }
}

void loop() {
  bool sw1 = !digitalRead(SWITCHs[0]);
  bool sw2 = !digitalRead(SWITCHs[1]);
  bool sw3 = !digitalRead(SWITCHs[2]);
  bool sw4 = !digitalRead(SWITCHs[3]);
//  sw1 = sw2 = sw3 = sw4 = false;
  
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
}

///* 按鈕１：左旋 */
void btn1_func() {
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], HIGH);
    delay(100);
    digitalWrite(LEDs[i], LOW);
  }
}

/* 按鈕２：右旋 */
void btn2_func() {
  for (i = 4; i > -1; i--) {
    digitalWrite(LEDs[i], HIGH);
    delay(100);
    digitalWrite(LEDs[i], LOW);
  }
}

/* 按鈕３：LED 全亮 */
void btn3_func() {
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], HIGH);
  }
}

/* 按鈕４：LED 全熄 */
void btn4_func() {
  for (i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], LOW);
  }
}
