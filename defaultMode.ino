const int wheelSize = 240; // how many entries in the color wheel
const int brightness = 255;
int autoPosition = 0;

/*added for position change with sensor*/
long normalize(long value, long radix)
{
  long rval = value % radix;
  if (rval < 0) return radix + rval;
  else return rval;
}

long knobValue = positionLed / 2;
long ledPosition = normalize(knobValue, numOfLeds);
long colorValue = normalize(knobValue * 3, wheelSize);

//Serial.print("knobValue");
//Serial.println(knobValue);

//long colorValue = normalize(100, wheelSize);

void defaultMode()
{
  const int slugSize = 50;

  initializeToBlack();

  for (uint8_t r = 0; r < 4; r++)
  {
    for (int i = 0; i < slugSize; i++)
    {
      //once colorWheel(brightness, i)
      pixels.setPixelColor(r * numOfLeds + ((i + autoPosition) % numOfLeds), colorWheel(brightness, i));
    }

    autoPosition++;
    if (autoPosition >= numOfLeds)
    {
      autoPosition = 0;
    }
  }
}
// given a wheel position in 0-255 range
// return a rainbow color adjusted by intensity 0 to 1.0
uint32_t colorWheel(float intensity, byte wheelPos)
{
  const int wheelThird = (wheelSize - 1) / 3;

  intensity = 0.1;
  //    if (intensity < 0.0 ) intensity = 0.0;
  //    if (intensity > 1.0) intensity = 1.0;

  // as wheelPos progresses from 0 to 255 once, colorIndex should progress from 0 to 255 3 times
  // find out position in current third of wheel then multiple by 3 to get full color value
  byte colorIndex = (wheelPos % wheelThird) * 3;

  int fadeColor = (255 - colorIndex) * intensity;  // color going down
  int increaseColor = colorIndex * intensity;    // color going up

  switch (wheelPos / wheelThird)
  {
    case 0:    // first third of the wheel, red fading, no green, blue increasing
      return Adafruit_NeoPixel::Color(fadeColor, 0, increaseColor);
      break;
    case 1:    // second third of the wheel no red, green increasing, blue fading
      return Adafruit_NeoPixel::Color(0, increaseColor, fadeColor);
      break;

    case 2:    // last third of the wheel, red increasing, green fading, no blue
      return Adafruit_NeoPixel::Color(increaseColor, fadeColor, 0);
      break;
  }
}

