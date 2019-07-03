/*if succeed, spread the light from the led postion*/

void balanceSucceedLed()
{
  /*if players managed to succeed 5 times(or more)*/
  if (balanceScore >= 5)
  {
    Serial.println("balance game succeeded");

    while (lMove < 420)
    {
      for (uint8_t r = 0; r < 4; r++)
      {
        for (int l = numOfLeds / 2; l < numOfLeds; l++)
        {
          int mod = (lMove - l) % 40;
          if (mod < 20)
          {
            pixels.setPixelColor(r * numOfLeds + l, 255, 0, 255);
          }
          else
          {
            pixels.setPixelColor(r * numOfLeds + l, 0, 0, 255);
          }
        }

        for (int l = numOfLeds / 2; l > 0; l--)
        {
          int mod = (lMove + l) % 40;
          if (mod < 20)
          {
            pixels.setPixelColor(r * numOfLeds + l, 255, 0, 255);
          }
          else
          {
            pixels.setPixelColor(r * numOfLeds + l, 0, 0, 255);
          }
        }
      }
      lMove = lMove + 1;
      pixels.show();
    }


    /*reset to default*/
    reset();
    turnDefault = true;
    turnonTugOfWar = false;
    turnonBalance1 = false;
  }
}

