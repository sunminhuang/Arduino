#include <WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>
#include <Wire.h>
uint8_t readStatus = 0;

// 修改成上述寄到登入郵箱的 Token權杖號碼
#define LINE_TOKEN "3BI6HbpEz7XuhAXjUEr38KGdVzJ5fji2gCOYvDhAjtm"

// 設定無線基地台SSID跟密碼
const char* ssid     = "FGO";
const char* password = "sm931017";

void setup(void)
{
  Serial.begin(115200);  // 設定速率 感測器

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
  
  LINE.setToken(LINE_TOKEN);
  // 先換行再顯示
  LINE.notify("\nHELLO sunmin");
}

void loop(void)
{

}
