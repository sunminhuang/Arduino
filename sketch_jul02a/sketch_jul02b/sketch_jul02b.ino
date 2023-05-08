#include <Adafruit_NeoPixel.h>

int i;
int color, R, G, B;
int add;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(124, 6, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();
  pixels.setBrightness(30);
  color = 0;
  R = 0;
  G = 0;
  B = 0;
  add = 1;
  //Serial.begin(9600);
//  for (i = 0; i < 124; i++) 
//   pixels.setPixelColor(i, pixels.Color(50, 50, 50));
  delay(1000);
}

void loop()
{

  for (i = 0; i < 124; i++) {
    pixels.setPixelColor(i, pixels.Color(color,color,color));
  }
  pixels.show();
  delay(20);
  color = color + add;
  if (color >= 100) {
    add = -1;
  } else if (color <= 0) {
    add = 1;
  }

}
