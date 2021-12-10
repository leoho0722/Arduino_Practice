#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "BluetoothSerial.h"
#include <DHT.h>
#include "ESP32Servo.h" // ESP32 用來控制 Speaker 的
#include "Speaker_Freq.h" // 頻率分配表
/* 腳位定義 */
const char DHTPIN = 5; // DHT22: 5
const char DHTTYPE = DHT22;
const char LEDs[] = {16, 17, 18, 19}; // LED: 16, 17, 18, 19
const char Switchs[] = {25, 26, 27}; // Switch1~3: 25, 26, 27
const char speaker = 33; // Speaker: 33

/* Wi-Fi SSID */
char* ssid = "2706";
char* pwd = "rootroot";

/* Speaker Settings */
/* 小蜜蜂1 */
int freq[] = {262, 294, 330, 349, 392};
int melody[] = {5,3,3,4,2,2,1,2,3,4,5,5,5,5,3,3,4,2,2,1,3,5,5,3,2,2,2,2,2,3,4,3,3,3,3,3,4,5,5,3,3,4,2,2,1,3,5,5,1};
int beat[] = {1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4};
/* 小蜜蜂2 */
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

DHT dht(DHTPIN, DHTTYPE);
float temp, humidity;
String dhtState = "";

BluetoothSerial SerialBT;
WebServer server(80);

void setup() {
  dht.begin();
  Serial.begin(115200);
  // SerialBT.begin("ESP32Test");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println("Wi-Fi Connected!");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  Serial.print("RSSI: "); Serial.println(WiFi.RSSI());

  server.on("/", systemRoute);

  server.onNotFound([] {
    server.send(404, "text/plain", "File Not Found!");
  });
  server.begin();

  for (int i = 0; i < 4; i++) {
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(Switchs[i], INPUT);
  }
  pinMode(speaker, OUTPUT);
}

void loop() {
  server.handleClient();
}

// Server systemRoute
void systemRoute() {
  String HTML = "\
  <html>\
    <head>\
      <meta charset= 'utf-8'>\
      <meta http-equiv=\"refresh\" content=\"2\">\
      <title>HW11 監控系統設計</title>\
    </head>\
    <body>";
  String HTML_Footer = "</body></html>";    
  getDHT();
  if (String(temp) == "nan" || String(humidity) == "nan") {
    dhtState = "Failed to read from DHT Sensor!";
  } else {
    dhtState = "Temp: " + String(temp) + " Degree C\n" + "Humidity: " + String(humidity) + " %";
    if (temp > 25.00) {
      dhtState = dhtState + "，室內溫度有變高的趨勢喔";
      digitalWrite(LEDs[0], HIGH); // LEDs[0]：提醒室內溫度有變高的趨勢
      littleBee2();
    } else if (temp < 20.00) {
      dhtState = dhtState + "，室內溫度有變低的趨勢喔";
      digitalWrite(LEDs[1], HIGH); // LEDs[1]：提醒室內溫度有變低的趨勢
      littleStar();
    } else {
      dhtState = dhtState + "，室內溫度很合適喔";
    }
    if (humidity > 65.00) {
      dhtState = dhtState + "，室內濕度有點高喔";
      digitalWrite(LEDs[2], HIGH); // LEDs[2]：提醒室內濕度有變高的趨勢
      littleBee2();
    } else if (humidity < 45.00) {
      dhtState = dhtState + "，室內濕度有點低喔";
      digitalWrite(LEDs[3], HIGH); // LEDs[3]：提醒室內濕度有變低的趨勢
      littleStar();
    } else {
      dhtState = dhtState + "，室內濕度很合適喔";
    }
  }
  Serial.println(dhtState);
  HTML = HTML + dhtState + HTML_Footer;
  Serial.println(HTML);
  server.send(200, "text/html", HTML); // 處理顯示溫溼度狀態的路由
}

// 溫溼度讀取
void getDHT() {
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT Sensor!");
    return;
  }
  // Serial Output
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("Degree C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  // SerialBT Output
  SerialBT.print("Temperature: ");
  SerialBT.print(temp);
  SerialBT.println("Degree C");
  SerialBT.print("Humidity: ");
  SerialBT.print(humidity);
  SerialBT.println("%");
  delay(1000);
}

// Speaker 發聲音
// 小蜜蜂－溫溼度變高的時候放
void littleBee() {
  for (int i = 0; i < 49; i++) {
    tone(speaker, freq[melody[i]-1]);
    delay(beat[i]*250);
    noTone(speaker);
    delay(0);
  }
  delay(1000);
}
void littleBee2() {
  for(int i = 0; i < sizeof(bee_melody)/sizeof(int); i++){
    tone(speaker, bee_melody[i], 55 * bee_beat[i]);
    delay(75 * bee_beat[i]);
  }  
}

// 小星星－溫溼度變低的時候放
void littleStar() {
  for(int i = 0; i < sizeof(bee_melody)/sizeof(int); i++){
    tone(speaker, star_melody[i], 55 * star_beat[i]);
    delay(75 * star_beat[i]);
  }
}