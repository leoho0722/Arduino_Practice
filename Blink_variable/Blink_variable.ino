/* 變數宣告的地方 */
const byte led1 = 8; // 宣告腳位 11 固定是 LED1 的腳位
const byte led2 = 9; // 宣告腳位 12 固定是 LED2 的腳位
const byte led3 = 10; // 宣告腳位 13 固定是 LED3 的腳位
const byte led4 = 11; // 宣告腳位 12 固定是 LED2 的腳位
const byte led5 = 12; // 宣告腳位 13 固定是 LED3 的腳位

/* 腳位定義的地方 */
void setup() {
  pinMode(led1, OUTPUT); // 設定 LED1 的腳位，以及模式為 OUTPUT
  pinMode(led2, OUTPUT); // 設定 LED2 的腳位，以及模式為 OUTPUT
  pinMode(led3, OUTPUT); // 設定 LED3 的腳位，以及模式為 OUTPUT
  pinMode(led4, OUTPUT); // 設定 LED1 的腳位，以及模式為 OUTPUT
  pinMode(led5, OUTPUT); // 設定 LED2 的腳位，以及模式為 OUTPUT
}

/* 主程式跑的地方 */
void loop() {
  digitalWrite(led1, HIGH); // 讓 LED1 處於高電位，發亮
  delay(100); // 每秒閃爍
  digitalWrite(led1, LOW); // 讓 LED1 處於低電位，不亮
  delay(100); // 每秒閃爍
  digitalWrite(led2, HIGH); // 讓 LED2 處於高電位，發亮
  delay(100); // 每秒閃爍
  digitalWrite(led2, LOW); // 讓 LED2 處於低電位，不亮
  delay(100); // 每秒閃爍
  digitalWrite(led3, HIGH); // 讓 LED3 處於高電位，發亮
  delay(100); // 每秒閃爍
  digitalWrite(led3, LOW); // 讓 LED3 處於低電位，不亮
  delay(100); // 每秒閃爍
  digitalWrite(led4, HIGH); // 讓 LED3 處於高電位，發亮
  delay(100); // 每秒閃爍
  digitalWrite(led4, LOW); // 讓 LED3 處於低電位，不亮
  delay(100); // 每秒閃爍
  digitalWrite(led5, HIGH); // 讓 LED3 處於高電位，發亮
  delay(100); // 每秒閃爍
  digitalWrite(led5, LOW); // 讓 LED3 處於低電位，不亮
  delay(100); // 每秒閃爍
}
