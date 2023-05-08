#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#define DHTTYPE DHT11

// 修改成上述寄到登入郵箱的 Token號碼
#define LINE_TOKEN "Upw4m3oooX0Jwkzq2GikQFRJrZ2r0TIFPF1Ato0PiQP"

// 設定無線基地台SSID跟密碼
const char* ssid     = "FGO";
const char* password = "sm931017";

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX

String text = "";
boolean gotText = false;
String ans = "";
String Name[2] = {"sunmin", "XXXXXX"};

void setup(void)
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("hello");

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
  int name_tem[2] = {0};
  while (Serial.available())
  {
    gotText = true;
    text = Serial.readString();
  }
  int len = text.length();
  if (gotText)
  {
    int bun;
    for (int i = 0; i < len; i++)
      if (text[i] == 44)
        bun = i;
    for (int i = 0; i < bun ; i++) {
      name_tem[0] += (text[i] - 48);
    }
    int p = len - bun - 2;
    for (int i = bun + 1; i < len - 2; i++)
    {
      name_tem[1] *= 10;
      name_tem[1] += (text[i] - 48);
    }
    ans += Name[name_tem[0]] + "：" + name_tem[1] + "℃";
    LINE.notify(ans);
    gotText = false;
    text = "";
    ans = "";
  }
}
