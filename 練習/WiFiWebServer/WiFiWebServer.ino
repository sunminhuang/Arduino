//13=D7;16=D0;15=D8;14=D5;12=D6;4=D2;3=D9;2=D4;1=D10;0=D3

//本實作將教你如何將板子設定成http的伺服器
//本伺服器會依照接收到的訊息去改變*腳位
//http://server_ip/gpio/0 會將腳位變成低電壓
//http://server_ip/gpio/1 會將腳位變成高電壓
//本伺服器的IP會顯示在序列中

#include <ESP8266WiFi.h>

const char* ssid = "PB";//輸入你家的wifi名稱
const char* password = "92469246";//輸入你家wifi密碼

WiFiServer server(80);//開啟板子的port 80

void setup() {
  Serial.begin(115200);//開啟電腦序列埠，速度設為115200
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);//將腳位2設定成輸出，2 = D4
  digitalWrite(2, 0);//先將這個腳位設為低電壓
  
  //接下來板子開始要連線到你家基地台了
  Serial.println();//印空格
  Serial.println();//印空格
  Serial.print("Connecting to ");//印出連線到你家
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);//使用你家wifi和密碼開始連線
  
  while (WiFi.status() != WL_CONNECTED) {//還沒連線成功時會一直跳出點點點
    delay(500);
    Serial.print(".");
  }
  Serial.println("");//連線成功之後這裡會跳出連線成功
  Serial.println("WiFi connected");
  
  server.begin();//伺服器啟動
  Serial.println("Server started");

  Serial.println(WiFi.localIP());//列印出此伺服器被分配到的網區IP
}

void loop() {
  // 確定是否連線中，不是了話就跳出去
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // 等待傳到這個伺服器的訊息，一直等一直等
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  //收到傳過來的訊息之後，將收到的訊息轉成req
  String req = client.readStringUntil('\r');
  Serial.println(req);//列印出收到的訊息
  client.flush();
  
  // 開始比對收到的訊息來決定做什麼事
  int val;
  if (req.indexOf("/gpio/0") != -1)     //如果收到/gpio/0
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)//如果收到/gpio/1
    val = 1;
  else {                                //其他的
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(2, val);//依照收到的訊息改變燈的亮按
  
  client.flush();

  // 準備給發訊者的回應，內容以html的格式，代表發訊者會收到簡單的網頁
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  //準備好了，發給發訊者
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

}
