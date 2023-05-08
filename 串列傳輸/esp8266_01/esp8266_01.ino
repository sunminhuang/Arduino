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
SoftwareSerial mySerial(1, 2); // RX=8, TX=7

String text = "";
boolean gotText = false;
int values = 0;

void setup(void)
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("hello");
  pinMode(LED_BUILTIN, OUTPUT);

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
  String Name = "sunmin";
  while (mySerial.available())
  {
    gotText = true;
    char tempChar = char(mySerial.read());
    text += tempChar;
    values *= 10;
    values += (tempChar-48);
    delay(1);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (gotText)
  {
    digitalWrite(LED_BUILTIN, LOW);
    gotText = false;
    mySerial.println(values);
    LINE.notify(Name+String(values));
//    LINE.notify(values);
    text = "";
    values = 0;
  }
}
