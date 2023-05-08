/* 修改自 5/3/2014  Version 1.0   Mike Barela for Adafruit Industries
   將瀏覽器連線的子目錄呈現方式，改成一連線該 IP 就出現溫濕度，且從華氏換算成攝氏
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2

// 設定無線基地台SSID跟密碼
const char* ssid     = "MyHome";     //改成您的SSID  
const char* password = "12345678";   //改成您的密碼

ESP8266WebServer server(80);

DHT dht(DHTPIN, DHTTYPE, 11);    // 11 works fine for ESP8266
 
float humidity, temp_f;   // 從 DHT-11 讀取的值
String webString="";      // 顯示的字串

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
 
 
void setup(void)
{
  Serial.begin(115200);  // 設定速率 感測器
  dht.begin();           // 初始化

  // 連接無線基地台
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
//  server.on("/", handle_root);
  
  server.on("/", [](){     
    gettemperature();       // 讀取感測器資料
    webString="Temperature: "+String((int)(temp_f-32)*5/9)+" C,   "+" Humidity: "+String((int)humidity)+"%";    // Arduino has a hard time with float to string
    server.send(200, "text/plain", webString);            // 回應瀏覽器詢問的
  });

  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 

void gettemperature() {
  // 量測間等待至少 2 秒
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // 將最後讀取感測值的時間紀錄下來 
    previousMillis = currentMillis;   

    // 讀取溫度大約 250 微秒!
    humidity = dht.readHumidity();          // 讀取濕度(百分比)
    temp_f = dht.readTemperature(true);     // 讀取溫度(華氏)
    
    // 檢查兩個值是否為空值
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
