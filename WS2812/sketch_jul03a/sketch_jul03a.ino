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
  Serial.begin(9600);
//  for (i = 0; i < 124; i++)
//    pixels.setPixelColor(i, pixels.Color(100, 5, 100));
//  delay(100000);
}

void loop()
{
  bool loop = true;
  while (loop) {
    for (i = 0; i < 124; i++)
    {
      pixels.setPixelColor(i, pixels.Color(R, G, B));
      pixels.show();
      delay(20);
    }

    if (R <= 100)
    {
      R++;
    }
    if (R >= 100 && G <= 100)
      G++;
    if (G >= 100 && B <= 100)
      B++;
    if (B >= 100)
      loop = false;
  }
  loop = true;
  while (loop)
  {
    for (i = 0; i < 124; i++) {
      pixels.setPixelColor(i, pixels.Color(R, G, B));
      pixels.show();
      delay(20);
    }

    if (B >= 0)
      B--;
    if (B <= 0 && G >= 0)
      G--;
    if (G <= 0 && R >= 0)
      R--;
    if (R <= 0)
      loop = false;
  }
}
