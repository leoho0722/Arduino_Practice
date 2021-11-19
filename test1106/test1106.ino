#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "Speaker_Freq.h" // 頻率分配表

/* 定義麥克風腳位 */
// 腳位A0：麥克風
const byte MIC = A0;
bool toggle = false;
// int max_value = 0;

/* 定義光敏電阻腳位 */
// 腳位A1：光敏電阻
const byte Cds = A1;

/* 定義蜂鳴器腳位 */
// 腳位1：蜂鳴器
const byte speaker = 2;
/* 小蜜蜂 */
int bee_melody[] = {
    freq_G5, freq_E5, freq_E5, 0, freq_F5, freq_D5, freq_D5, 0, freq_C5, freq_D5, freq_E5, freq_F5, freq_G5, freq_G5, freq_G5, 0,
    freq_G5, freq_E5, freq_E5, 0, freq_F5, freq_D5, freq_D5, 0, freq_C5, freq_E5, freq_G5, freq_G5, freq_E5, 0, 0, 0,
    freq_D5, freq_D5, freq_D5, freq_D5, freq_D5, freq_E5, freq_F5, 0, freq_E5, freq_E5, freq_E5, freq_E5, freq_E5, freq_F5, freq_G5, 0,
    freq_G5, freq_E5, freq_E5, 0, freq_F5, freq_D5, freq_D5, 0, freq_C5, freq_E5, freq_G5, freq_G5, freq_C5, 0, 0, 0
};
int bee_beat[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};
/* 小星星 */
int star_melody[] = {
    freq_C5, freq_C5, freq_G5, freq_G5, freq_A5, freq_A5, freq_G5, 0, freq_F5, freq_F5, freq_E5, freq_E5, freq_D5, freq_D5, freq_C5, 0,
    freq_G5, freq_G5, freq_F5, freq_F5, freq_E5, freq_E5, freq_D5, 0, freq_G5, freq_G5, freq_F5, freq_F5, freq_E5, freq_E5, freq_D5, 0,
    freq_C5, freq_C5, freq_G5, freq_G5, freq_A5, freq_A5, freq_G5, 0, freq_F5, freq_F5, freq_E5, freq_E5, freq_D5, freq_D5, freq_C5, 0
};
int star_beat[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

/* 定義 DHT11 溫濕度腳位 */
// 腳位2：DHT11 溫濕度感測器
DHT dht(2, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* 定義 LED 腳位 */
// 腳位3：LED1
// 腳位4：LED2
// 腳位5：LED3
// 腳位6：LED4
// 腳位7：LED5
const byte LEDs[] = {3, 4, 5, 6, 7};

/* 定義超音波距離感測腳位 */
// 腳位8：echoPin
// 腳位9：trigPin
const int echoPin = 8; // 回應
const byte trigPin = 9; // 觸發
unsigned long d;

/* 定義指撥開關腳位 */
// 腳位8：指撥開關1，右旋
// 腳位9：指撥開關2，左旋
// 腳位10：指撥開關7，全亮
// 腳位11：指撥開關8，全熄
const byte SWITCHs[] = {10, 11, 12, 13};
int sw_state = 0; // 判斷現在的 Switch 狀態

void setup() {
  /* Serial Port 初始化 */
  Serial.begin(9600);
  Serial.println("Arduino Connect!\n");

  /* 光敏電阻初始化，腳位A1 */
  pinMode(Cds, INPUT);

  /* 蜂鳴器初始化，腳位1 */
  pinMode(speaker, OUTPUT);

  /* LCD+溫濕度感測器初始化，腳位2 */
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Temp");
  lcd.setCursor(0, 1);
  lcd.print("Humidity");

  /* LED 初始化，腳位3~7 */
  for (int i = 0; i < 5; i++) {
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);
  }

  /* 超音波距離感測初始化，腳位8~9 */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* Switch 按鈕初始化，腳位10~13 */
  for (int i = 0; i < 4; i++) {
    pinMode(SWITCHs[i], INPUT);
  }
}

void loop() {
  // bool sw1 = !digitalRead(SWITCHs[0]);
  // bool sw2 = !digitalRead(SWITCHs[1]);
  // bool sw3 = !digitalRead(SWITCHs[2]);
  // bool sw4 = !digitalRead(SWITCHs[3]);

  // bool sw5 = !digitalRead(SWITCHs[4]);
  // bool sw6 = !digitalRead(SWITCHs[5]);
  // bool sw7 = !digitalRead(SWITCHs[6]);

  if (!digitalRead(SWITCHs[0])) { sw_state = 1; }
  if (!digitalRead(SWITCHs[1])) { sw_state = 2; }
  if (!digitalRead(SWITCHs[2])) { sw_state = 3; }
  if (!digitalRead(SWITCHs[3])) { sw_state = 4; }

  // if (!digitalRead(SWITCHs[4]) == true) { sw_state = 5; }
  // if (!digitalRead(SWITCHs[5]) == true) { sw_state = 6; }
  // if (!digitalRead(SWITCHs[6]) == true) { sw_state = 7; }
  // Serial.print("sw_state:"); Serial.println(sw_state);

  /* HW2，用按鈕控制*/
  if (sw_state == 1) {
    Serial.println("Run Button1 Func!");
    led_func(); // LED 左旋、右旋、全亮、全熄
  } else if (sw_state == 2) {
    Serial.println("Run Button2 Func!");
    lcd_dht(); // LCD+溫濕度感測
  } else if (sw_state == 3) {
    Serial.println("Run Button3 Func!");
    btn3_func(); // 光敏電阻
  } else if (sw_state == 4) {
    Serial.println("Run Button4 Func!");
    btn4_func(); // 麥克風拍手
  } else if (sw_state == 5) {
    Serial.println("Run Button5 Func!");
    btn5_func(); // 超音波感測
  } else if (sw_state == 6) {
    Serial.println("Run Little Bee Func!");
    littleBee(); // 揚聲器－小蜜蜂
  } else if (sw_state == 7) {
    Serial.println("Run Little Star Func!");
    littleStar(); // 揚聲器－小星星
  } else if (sw_state == 8) {
    Serial.println("Run Malio Func!");
    malio(); // 揚聲器－瑪莉歐
  }

  /* HW3，用 Serial Port 控制 */
  if (Serial.available()) {
    Serial.println("Serial available");
    char val = Serial.read();
    if (val == '1') {
      sw_state = 1;
      if (sw_state == 1) {
        Serial.println("Run Button1 Func!");
        led_func(); // LED 左旋、右旋、全亮、全熄
      }
    } else if (val == '2') {
      sw_state = 2;
      if (sw_state == 2) {
        Serial.println("Run Button2 Func!");
        lcd_dht(); // LCD+溫濕度感測
      }
    } else if (val == '3') {
      sw_state = 3;
      if (sw_state == 3) {
        Serial.println("Run Button3 Func!");
        btn3_func(); // 光敏電阻
      }
    } else if (val == '4') {
      sw_state = 4;
      if (sw_state == 4) {
        Serial.println("Run Button4 Func!");
        btn4_func(); // 麥克風拍手
      }
    } else if (val == '5') {
      sw_state = 5;
      if (sw_state == 5) {
        Serial.println("Run Button5 Func!");
        btn5_func(); // 超音波感測
      }
    } else if (val == '6') {
      sw_state = 6;
      if (sw_state == 6) {
        Serial.println("Run Little Bee Func!");
        littleBee(); // 揚聲器－小蜜蜂
      }
    } else if (val == '7') {
      sw_state = 7;
      if (sw_state == 7) {
        Serial.println("Run Litte Star Func!");
        littleStar(); // 揚聲器－小星星
      }
    } else if (val == '8') {
      sw_state = 8;
      if (sw_state == 8) {
        Serial.println("Run Malio Func!");
        malio(); // 揚聲器－瑪莉歐
      }
    }
    //
  }
  //
}

/* LED 右旋 */
void led_1_func() {
  Serial.println("LED 右旋");
  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDs[i], HIGH);
    delay(1000);
    digitalWrite(LEDs[i], LOW);
  }
}
/* LED 左旋 */
void led_2_func() {
  Serial.println("LED 左旋");
  for (int i = 4; i > -1; i--) {
    digitalWrite(LEDs[i], HIGH);
    delay(1000);
    digitalWrite(LEDs[i], LOW);
  }
}
/* LED 全亮 */
void led_3_func() {
  Serial.println("LED 全亮");
  for (int i = 0; i < 5; i++) { digitalWrite(LEDs[i], HIGH); }
}
/* LED 全熄 */
void led_4_func() {
  Serial.println("LED 全熄\n");
  for (int i = 0; i < 5; i++) { digitalWrite(LEDs[i], LOW); }
}
/* 按鈕1：右旋、左旋、全亮、全熄 */
void led_func() {
  led_1_func(); delay(1000); // 右旋
  led_2_func(); delay(1000); // 左旋
  led_3_func(); delay(1000); // 全亮
  led_4_func(); delay(1000); // 全熄
}

/* 按鈕2：LCD+溫濕度 */
void lcd_dht() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed to read");
    lcd.setCursor(0, 1);
    lcd.print("from DHT sensor!");
    Serial.println("Failed to read");
    Serial.println("from DHT sensor!");
    return;
  }

  lcd.setCursor(9, 0);
  lcd.print(temp, 2);
  lcd.print((char)0xDF);
  lcd.print("C");
  Serial.print("目前溫度：");
  Serial.print(temp, 2);
  Serial.print((char)0xDF);
  Serial.println("C");

  lcd.setCursor(9, 1);
  lcd.print(humidity, 2);
  lcd.print("%");
  Serial.print("目前濕度：");
  Serial.print(humidity, 2);
  Serial.println("%\n");

  delay(2000);
}

/* 按鈕3，光敏電阻感測 */
void btn3_func() {
  int val = analogRead(Cds); // 光敏電阻讀取到的值
  Serial.println(val);
  if (val <= 400) {
    led_3_func(); // 非常暗，LED 全亮
  } else if (val > 400 && val <= 700) {
    /* 普通暗，前三顆 LED 亮，後兩顆 LED 熄 */
    Serial.println("前三顆 LED 亮，後兩顆 LED 熄");
    for (int i = 0; i < 3; i++) {
      digitalWrite(LEDs[i], HIGH);
    }
    for (int i = 3; i < 5; i++) {
      digitalWrite(LEDs[i], LOW);
    }
  } else if (val > 700) {
    led_4_func(); // 天亮，LED 全熄
  }
  delay(1000);
}

/* 按鈕4，拍手用麥克風收音讓 LED 亮 */
void btn4_func() {
  int val = analogRead(MIC);
  Serial.println(val);
    if (val > 90) {
    toggle = !toggle;
    for (int i = 0; i < 5; i++) {
      digitalWrite(LEDs[i], toggle);
    }
    delay(100);
  }
  // for (int i = 0; i < 100; i++) {
  //   int val = analogRead(MIC);
  //   if (val > max_value) {
  //     max_value = val;
  //   }
  //   delay(1);
  // }
  // Serial.println(max_value);
  // if (max_value > 64) {
  //   toggle = !toggle;
  //   for (int i = 0; i < 5; i++) {
  //     digitalWrite(LEDs[i], toggle);
  //   }
  // }
  // max_value = 0;
}

/* 按鈕5，超音波距離感測 */
unsigned long ping() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}
void btn5_func() {
  d = ping() / 58;
  Serial.println(String("") + d + " cm");
  delay(1000);
}

/* 按鈕6，揚聲器演奏-小蜜蜂 */
void littleBee() {
  // for (int i = 0; i < count; i++) {
  //   int d = 1000 / bee_beat[i];
  //   tone(speaker, bee_melody[i], d);
  //   Serial.println(bee_melody[i]);
  //   int p = d * 1.3;
  //   delay(p);
  //   noTone(pin);
  // }
  for(int i = 0; i < sizeof(bee_melody)/sizeof(int); i++){
    tone(speaker, bee_melody[i], 55 * bee_beat[i]);
    delay(75 * bee_beat[i]);
  }
}

/* 按鈕7，揚聲器演奏-小星星 */
void littleStar() {
  for(int i = 0; i < sizeof(bee_melody)/sizeof(int); i++){
    tone(speaker, star_melody[i], 55 * star_beat[i]);
    delay(75 * star_beat[i]);
  }
  // for (int i = 0; i < count; i++) {
  //   int d = 1000 / star_beat[i];
  //   tone(pin, star_melody[i], d);
  //   int p = d * 1.3;
  //   delay(p);
  //   noTone(pin);
  // }
  // delay(2000);
}

/* 按鈕8，揚聲器演奏－瑪莉歐 */
void malio() {
  // 150 = 彈奏間隔時間
  tone(speaker, freq_E5, 150);
  delay(150);
  tone(speaker, freq_E5, 150);
  delay(150 * 3);
  tone(speaker, freq_E5, 150);
  delay(150 * 3);
  tone(speaker, freq_C5, 150);
  delay(150);
  tone(speaker, freq_E5, 150);
  delay(150 * 3);
  tone(speaker, freq_G5, 150);
  delay(150 * 7);
}