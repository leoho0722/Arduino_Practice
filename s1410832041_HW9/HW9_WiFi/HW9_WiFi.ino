#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

DHT dht(2, DHT11);
float temp, humidity; // 宣告溫度、濕度
String dhtState = ""; // 顯示溫溼度的字串

// Wi-Fi SSID、Password 宣告
// 冠博的
//const char* ssid = "Pro";
//const char* pwd = "ahg68er54sdDGFH";

// 2706 的
//const char* ssid = "2706_5G";
//const char* pwd = "rootroot";

// 家裡的
const char* ssid = "D-Link DIR-867";
const char* pwd = "10260722";

ESP8266WebServer server(80);

void setup() {
  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
  }
  
  Serial.println("Wi-Fi Connected!");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP()); // 顯示 IP Address
  Serial.print("Wi-Fi RSSI:");
  Serial.println(WiFi.RSSI()); // 顯示 Wi-Fi 訊號強度

  server.on("/", rootRoute); // 處理首頁的路由
  
  server.on("/about", aboutRoute); // 處理關於的路由

  // 處理溫溼度的路由
  server.on("/dht", []() {
    getDHT();
    if (String(temp) == "nan" || String(humidity) == "nan") {
      dhtState = "Failed to read from DHT sensor!";
    } else {
      dhtState = "Temp: " + String(temp) + " Degree Celsius\n" + "Humidity: " + String(humidity) + " %\n";
    }
    server.send(200, "text/plain", dhtState); // 處理顯示溫溼度狀態的路由
  });

  // 處理找不到路徑的路由
  server.onNotFound([]() {
    server.send(404, "text/plain", "File Not Found!"); // 處理找不到檔案的路由
  });

  server.begin(); // 啟動網頁伺服器
}

void loop() {
  server.handleClient();
}

void rootRoute() {
  String HTML = "\
  <html>\
    <head><meta charset= 'utf-8'></head>\
    <body>　Arduino Hello World!</body>\
  </html>";
  server.send(200, "text/html", HTML);
}

void aboutRoute() {
  String HTML = "\
  <html>\
    <head><meta charset= 'utf-8'></head>\
    <body>　第6組　1410832041 何秉翰　1410832050 方冠博　HW9：Wi-Fi 伺服器設計</body>\
  </html>";
  server.send(200, "text/html", HTML);
}

void getDHT() {
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temp:");
  Serial.print(temp, 2);
  Serial.print("Degree Celsius"); // 攝氏溫度

  Serial.print("Humidity:");
  Serial.print(humidity, 2);
  Serial.print("%");
}
