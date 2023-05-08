#include <splash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

int time_sec;
int time_min;
int time_hour;

unsigned long start_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("HELLO");
  // 設定 I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // 清除顯示緩衝區
  display.clearDisplay();
  Serial.println("HELLO2");
}

void loop() {
  Serial.println("HELLO3");
  String sec, mine, hour;
  start_time = millis();
  time_sec = start_time / 1000%60;
  time_min = (start_time / 60000+6)%60;
  time_hour = (start_time/ 3600000+22)%24;
  Serial.println(start_time);
  if (time_sec < 10)
    sec = "0" + String(time_sec);
  else
    sec = String(time_sec);
  if (time_min < 10)
    mine = "0" + String(time_min);
  else
    mine = String(time_min);
  if (time_hour < 10)
    hour = "0" + String(time_hour);
  else
    hour = String(time_hour);
    
  String Time = hour + ":" + mine + ":" + sec;
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  display.println(Time);
  display.display();
  display.clearDisplay();
}
