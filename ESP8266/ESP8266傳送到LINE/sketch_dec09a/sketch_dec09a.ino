#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#define DHTTYPE DHT11

// 修改成上述寄到登入郵箱的 Token號碼
#define LINE_TOKEN "Upw4m3oooX0Jwkzq2GikQFRJrZ2r0TIFPF1Ato0PiQP"

// 設定無線基地台SSID跟密碼
const char* ssid     = "FGO";
const char* password = "sm931017";

void setup(void)
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
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

  Serial.println(LINE.getVersion());
  LINE.setToken(LINE_TOKEN);
  LINE.notify("HELLO");
}

void loop(void)
{
  //  // 顯示 Line版本
  //  Serial.println(LINE.getVersion());
  //  LINE.setToken(LINE_TOKEN);
  //  // 先換行再顯示
  //  LINE.notify("HELLO");
  //  // 每2分鐘發送一次
  //  delay(120000);
}
