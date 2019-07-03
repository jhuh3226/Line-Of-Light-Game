/*count down 3 times before each game starts. blink white for 3 times & spread the light*/
//int gradualLed = 110;

void countdown()
{
  if (countdownStart == true)
  {

    //-------------------------------------------------------------------------------------------------------------------------
    /*blink once*/
    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 225));
      }
    }
    pixels.show();
    delay(500);

    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 0));
      }
    }
    pixels.show();
    delay(500);

    /*blink twice*/
    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 225));
      }
    }
    pixels.show();
    delay(500);

    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 0));
      }
    }
    pixels.show();
    delay(500);

    /*blink third*/
    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 225));
      }
    }
    pixels.show();
    delay(500);

    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = 0; i <= numOfLeds ; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 0));
      }
    }
    pixels.show();
    delay(500);

    //-------------------------------------------------------------------------------------------------------------------------
    /*spread light*/
    // MATTI: this while loop reapeats this part of the code until you reach the end of the strip
    while (gradualLed1 < numOfLeds)
    {
      for (uint8_t r = 0; r < 4; r++)
      {
        for (int i = numOfLeds / 2; i <= gradualLed1 ; i++)
        {
          if (turnonBalance1 == true)
          {
            pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB, greenB, blueB));
          }
          else if (turnonTugOfWar == true)
          {
            pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB_tugofwar, greenB_tugofwar, blueB_tugofwar));
          }
        }


        for (int i = numOfLeds / 2 ; i > gradualLed2 ; i--)
        {
          if (turnonBalance1 == true)
          {
            pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA, greenA, blueA));
          }

          else if (turnonTugOfWar == true)
          {
            pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA_tugofwar, greenA_tugofwar, blueA_tugofwar));

          }

        }
      }

      // MATTI: this was moved outside the for loop (otherwise you change the values by 4 during each loop.)
      if (gradualLed1 < numOfLeds)
      {
        gradualLed1 = gradualLed1 + 2;
      }

      if (gradualLed2 > 0)
      {
        gradualLed2 = gradualLed2 - 2;
      }

      // MATTI: update the leds
      pixels.show();
      delay(10);
    }

    // MATTI: this also needs to be outside the for loops (or do you even need the delay?)
    //delay(2000);

    gradualLed1 = numOfLeds / 2;
    gradualLed2 = numOfLeds / 2;

    countdownStart = false;
    Serial.println("Countdown Done!");
  }
}

