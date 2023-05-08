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

int val ;
void setup() {
  //設定LED為輸出模式
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); //設定通訊鮑率
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
void loop() {
  serial_blink();

}

void serial_blink() {
  String Name = "sunmin";
  while (!Serial.available()) {} //等待serial指令進入，如果Serial.available()沒有資料，就會一直等待
  if (Serial.available()) { //如果指令進入，會將Serial.read()的值設給val變數
    val = Serial.read();
    if (val == '1') { //val 收到1，LED燈亮，延遲1秒，並輸出字元1
      digitalWrite(LED_BUILTIN, HIGH);
      LINE.notify(Name+(val-48));
      delay(1000);
      Serial.print("1");
    }
    if (val == '0') { //val 收到0，LED熄滅，延遲1秒，並輸出字元0
      digitalWrite(LED_BUILTIN, LOW);
      LINE.notify(Name+(val-48));
      delay(1000);
      Serial.print("0");
    }
  }
}
