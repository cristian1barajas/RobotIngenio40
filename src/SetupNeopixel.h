#include <NeoPixelBus.h>

#define PIXEL_COUNT 12
#define PIXEL_PIN 17

const int colorSaturation = 255;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PIXEL_COUNT, PIXEL_PIN);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor black(0);

void highPixels1()
{
  strip.SetPixelColor(0, red);
  strip.SetPixelColor(1, red);
  strip.SetPixelColor(11, red);
  strip.Show();
}

void highPixels2()
{
  strip.SetPixelColor(2, green);
  strip.SetPixelColor(3, green);
  strip.SetPixelColor(4, green);
  strip.Show();
}

void highPixels3()
{
  strip.SetPixelColor(5, blue);
  strip.SetPixelColor(6, blue);
  strip.SetPixelColor(7, blue);
  strip.Show();
}

void highPixels4()
{
  strip.SetPixelColor(8, yellow);
  strip.SetPixelColor(9, yellow);
  strip.SetPixelColor(10, yellow);
  strip.Show();
}

void lowPixels1()
{
  strip.SetPixelColor(0, black);
  strip.SetPixelColor(1, black);
  strip.SetPixelColor(11, black);
  strip.Show();
}
void lowPixels2()
{
  strip.SetPixelColor(2, black);
  strip.SetPixelColor(3, black);
  strip.SetPixelColor(4, black);
  strip.Show();
}
void lowPixels3()
{
  strip.SetPixelColor(5, black);
  strip.SetPixelColor(6, black);
  strip.SetPixelColor(7, black);
  strip.Show();
}
void lowPixels4()
{
  strip.SetPixelColor(8, black);
  strip.SetPixelColor(9, black);
  strip.SetPixelColor(10, black);
  strip.Show();
}