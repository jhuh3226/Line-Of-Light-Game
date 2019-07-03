void balanceFailLed()
{
  /*if players fails 3 times(or more)*/
  if (balanceLostScore >= 3)
  {
    Serial.println("balance game failed");

    /*change into white failing mode*/
    while ((gradualLedFail1 < numOfLeds) || (gradualLedFail2 > 0))
    {
      Serial.println("balance game failed notification");

      for (uint8_t r = 0; r < 4; r++)
      {
        for (int i = numOfLeds/2; i <= gradualLedFail1 ; i++)
        {
          pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255));
        }
        for (int i = numOfLeds/2 ; i > gradualLedFail2 ; i--)
        {
          pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255));
        }
      }

      if (gradualLedFail1 < numOfLeds)
      {
        gradualLedFail1 = gradualLedFail1 + 10;
      }

      if (gradualLedFail2 > 0)
      {
        gradualLedFail2 = gradualLedFail2 - 10;
      }

      pixels.show();
      delay(100);
    }

    /*reset to default*/
    reset();
    turnDefault = true;
    turnonTugOfWar = false;
    turnonBalance1 = false;
  }
}
