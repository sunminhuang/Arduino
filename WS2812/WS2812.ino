#include <Adafruit_NeoPixel.h>

#define PIN 4    //設定輸出
#define NUMPIXELS 49 // 燈的數量

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // 時間延遲

int redColor = 255;
int greenColor = 255;
int blueColor = 255;

void setup() {
  pixels.begin();
}

void loop() {

  setColor();
  for (int i = 0; i < NUMPIXELS; i++) {
    //pixel.Color 採用 RGB 值，從 0,0,0 到 255,255,255
    pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    // 這會將更新的像素顏色發送到硬件。
    pixels.show();
    delay(20);
  }
  for (int i = 0; i < 256; i+=10)
  {
    for (int j = 0; j < NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(i, 0, i));
      pixels.show();
      delay(10);
    }
  }
  for (int i = 255; i > 0; i-=10)
  {
    for (int j = 0; j < NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(i, 0, i));
      pixels.show();
      delay(10);
    }
  }
}

// setColor()
// 選擇隨機值設置為 RGB
void setColor() {
  redColor = random(0, 255);
  greenColor = random(0, 255);
  blueColor = random(0, 255);
}
