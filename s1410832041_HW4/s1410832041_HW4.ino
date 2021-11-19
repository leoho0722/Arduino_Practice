#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

DHT dht(2, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Temp");
  lcd.setCursor(0, 1);
  lcd.print("Humidity");
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
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
  lcd.print((char) 0xDF);
  lcd.print("C");
  Serial.print("目前溫度：");
  Serial.print(temp,2);
  Serial.print((char) 0xDF);
  Serial.println("C");

  lcd.setCursor(9, 1);
  lcd.print(humidity, 2);
  lcd.print("%");
  Serial.print("目前濕度：");
  Serial.print(humidity,2);
  Serial.println("%");

  delay(2000);
}
