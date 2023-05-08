//ws2812
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    2
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//顯示器用
#include <splash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define sensor1 A0//紅外線腳位
int High;//測量之高

#define sensor2 A1 //是否偵測到人
bool DP = false;

Adafruit_SSD1306 display(-1);//顯示器

//馬達腳位設定
#define A_A1 8
#define A_B1 9
#define B_A1 10
#define B_B1 11
#define Speed 150
int UP_DOWN_STOP[3] = {0, 1, 2};//控制上升或下降

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);//序列埠監控視窗
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// 設定 I2C addr 0x3C
  display.clearDisplay();// 清除顯示緩衝區

  //馬達腳位設定
  pinMode(A_A1, OUTPUT);
  pinMode(A_B1, OUTPUT);
  pinMode(B_A1, OUTPUT);
  pinMode(B_B1, OUTPUT);
  digitalWrite(A_A1, LOW);
  digitalWrite(A_B1, LOW);
  digitalWrite(B_A1, LOW);
  digitalWrite(B_B1, LOW);

  //ws2810設定
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();           // 初始化 燈條
  strip.show();            // 關閉所有燈
  strip.setBrightness(50); // 將亮度設置為 1/5（最大 = 255）

  //繼電器設定
  pinMode(4,OUTPUT);
}

void loop() {
  Height_measurement();//紅外線偵測高度
  Detect_people();//檢測人
  Spray();
  //  Oled(High,UP_DOWN_STOP[0]); //顯示高度 與上升下降停止
  logic();
}

//判斷上升或下降
void logic()
{
  if (High > 15)
  {
    Rise_fall(UP_DOWN_STOP[0]);//上升0 下降1 停止2
    Oled(High, UP_DOWN_STOP[0],DP);
    digitalWrite(3, HIGH);
    RGB(true);
  }
  else if (High < 5)
  {
    Rise_fall(UP_DOWN_STOP[1]);
    Oled(High, UP_DOWN_STOP[1],DP);
    digitalWrite(3, HIGH);
  }
  else
  {
    Rise_fall(UP_DOWN_STOP[2]);
    Oled(High, UP_DOWN_STOP[2],DP);
    digitalWrite(3, LOW);
    RGB(false);
  }
}
//上升下降
void Rise_fall(int seesaw)
{
  switch (seesaw)
  {
    case 0:
      digitalWrite(A_A1, HIGH);
      analogWrite(A_B1, Speed);
      digitalWrite(B_A1, HIGH);
      analogWrite(B_B1, Speed);
      break;
    case 1:
      digitalWrite(A_A1, LOW);
      analogWrite(A_B1, Speed);
      digitalWrite(B_A1, LOW);
      analogWrite(B_B1, Speed);
      break;
    case 2:
      digitalWrite(A_A1, LOW);
      analogWrite(A_B1, 0);
      digitalWrite(B_A1, LOW);
      analogWrite(B_B1, 0);
      break;
  }
}
//高度測量 A0
void Height_measurement()
{
  float volts = analogRead(sensor1) * 0.0048828125; // value from sensor * (5/1024)
  int distance = 13 * pow(volts, -1); // worked out from datasheet graph
  delay(100); // slow down serial port
  if (distance <= 30)
  {
    Serial.println(distance);   // print the distance
  }
  High = distance;
  //  return High;
}
//偵測人
void Detect_people()
{
  float volts2 = analogRead(sensor2) * 0.0048828125;
  int distance2 = 13 * pow(volts2, -1); // worked out from datasheet graph
  delay(100); // slow down serial port
  if (distance2 <= 5)
  {
    DP = true;
  }
  else
  {
    DP = false;
  }
}
//顯示器 SCK A5 SDA A4
void Oled(int H, int C,bool YESNO)
{
  display.clearDisplay();
  display.setTextSize(2);  // 設定文字大小
  display.setTextColor(1); // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0); // 設定起始座標
  display.print("high=");     // 要顯示的字串
  display.println(H);   // 要顯示的字串
  display.print(C);
  if(YESNO)
    display.print("YES");
  display.display();       // 要有這行才會把文字顯示出來
}
//酒精噴灑
/*
 * DC+ 接5V DC- 接GNGD IN 接PIN
 * NC NO 選一個用
 * NC：Normal Close，常閉，它在正常情況下是接通的。
 * NO：Normal Open，常開，也就是正常情況它是不通電的。
 * COM：Common Ground，共接電，很多人習慣把外電接到這個接腳，再從NO或NC接到外部設備上。
 */
void Spray()
{
  if(DP)
    digitalWrite(4,HIGH);
  else
    digitalWrite(4,LOW);
}
//紫外線開啟 PIN 2
void RGB(bool ON_OFF)
{
  if (ON_OFF)
  {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, strip.Color(100, 5, 100));       //  Set pixel's color (in RAM)
    }
    strip.show();
  }
  else
  {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, strip.Color(0, 0, 0));     //  Set pixel's color (in RAM)
    }
    strip.show();
  }
}
