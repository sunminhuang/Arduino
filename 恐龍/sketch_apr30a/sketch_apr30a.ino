#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    4
#define LED_COUNT 49
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//#include <splash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // 設定 I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // 清除顯示緩衝區
  display.clearDisplay();
}

void loop() {
  //  colorWipe(strip.Color(134,   11,   235), 50);
  //  colorWipe(strip.Color(  40, 151,   212), 50);
  //  colorWipe(strip.Color(  246,   175, 0), 50);
  for (int i = 0; i < 10; i++)
  {
    colorWipe(strip.Color(  random(0, 255),   random(0, 255), random(0, 255)), 50);
    display.clearDisplay();
  }
  colorWipe2(50);
  rainbow(20);             // Flowing rainbow cycle along the whole strip
}

void colorWipe2(int wait) {
  for (int j = 5; j < 255; j += 5)
  {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(  0,   0, j));
    }
    strip.show();
    delay(wait);
  }
  for (int j = 5; j < 255; j += 5)
  {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(  0,   0, 255 - j));
    }
    strip.show();
    delay(wait);
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
