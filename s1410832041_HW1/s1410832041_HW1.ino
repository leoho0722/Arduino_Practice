/* HW1 跑馬燈，delay 100ms */
/* 變數宣告的地方 */

/* 腳位定義的地方 */
void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT); // 設定 LED1 的腳位為 11，以及模式為 OUTPUT
  pinMode(12, OUTPUT); // 設定 LED2 的腳位為 12，以及模式為 OUTPUT
  pinMode(13, OUTPUT); // 設定 LED3 的腳位為 13，以及模式為 OUTPUT
}

/* 主程式跑的地方 */
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for (i = 11; i < 14; i++) {
    digitalWrite(i, HIGH); // 讓 LED[i] 處於高電位，發亮
    delay(100); // 每秒閃爍
    digitalWrite(i, LOW); // 讓 LED[i] 處於低電位，不亮
  }
}
