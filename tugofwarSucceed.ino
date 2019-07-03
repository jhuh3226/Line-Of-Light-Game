int gradualLed_A = 0;
int gradualLed_B = numOfLeds;
int increasingSpeed = 7;

void tugofwarSucceedLed()
{
  if ( tugofwarSucceedPlayerA == true)
  {
    initializeToBlack();

    Serial.println("tugofwar-playerA won");

    /*fill up with winner color one by one*/
    //1st line-------------------------------------------

    while (gradualLed_A < numOfLeds)
    {
      for (int i = 0; i <= gradualLed_A ; i++)
      {

        Serial.println("tugofwar-playerA won line 1 moving");
        int r = 0;
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA_tugofwar, greenA_tugofwar, blueA_tugofwar));
      }

      if (gradualLed_A < numOfLeds)
      {
        gradualLed_A = gradualLed_A + increasingSpeed;
      }

      pixels.show();
    }
    gradualLed_A = 0;

    //2nd line-------------------------------------------
    while (gradualLed_A < numOfLeds)
    {
      for (int i = 0; i <= gradualLed_A ; i++)
      {
        Serial.println("tugofwar-playerA won line 2 moving");
        int r = 1;
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA_tugofwar, greenA_tugofwar, blueA_tugofwar));
      }

      if (gradualLed_A < numOfLeds)
      {
        gradualLed_A = gradualLed_A + increasingSpeed;
      }

      pixels.show();
    }
    gradualLed_A = 0;

    //3rd line-------------------------------------------

    while (gradualLed_A < numOfLeds)
    {
      for (int i = 0; i <= gradualLed_A ; i++)
      {
        Serial.println("tugofwar-playerA won line 3 moving");
        int r = 3;
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA_tugofwar, greenA_tugofwar, blueA_tugofwar));
      }

      if (gradualLed_A < numOfLeds)
      {
        gradualLed_A = gradualLed_A + increasingSpeed;
      }

      pixels.show();
    }

    delay(100);
    gradualLed_A = 0;


    /*reset to default*/
    reset();
    turnDefault = true;
    turnonTugOfWar = false;
    turnonBalance1 = false;
  }

  //-------------------------------------------------------------------------------------------------------------------------
  else if ( tugofwarSucceedPlayerB == true)
  {
    initializeToBlack();
    
    Serial.println("tugofwar-playerB won");

    /*fill up with winner color one by one*/
    //1st line-------------------------------------------
    while (gradualLed_B > 0)
    {
      Serial.println("tugofwar-playerB won line 1 moving");
      for (int i = numOfLeds; i > gradualLed_B ; i--)
      {
        int r = 0;
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB_tugofwar, greenB_tugofwar, blueB_tugofwar));
      }

      if (gradualLed_B > 0)
      {
        gradualLed_B = gradualLed_B - increasingSpeed;
      }

      pixels.show();
    }
    gradualLed_B = numOfLeds;

    //2nd line-------------------------------------------
    while (gradualLed_B > 0)
    {
      Serial.println("tugofwar-playerB won line 2 moving");
      for (int i = numOfLeds; i > gradualLed_B ; i--)
      {
        int r = 1;
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB_tugofwar, greenB_tugofwar, blueB_tugofwar));
      }

      if (gradualLed_B > 0)
      {
        gradualLed_B = gradualLed_B - increasingSpeed;
      }

      pixels.show();
    }
    gradualLed_B = numOfLeds;

    //3rd line-------------------------------------------
    while (gradualLed_B > 0)
    {
      Serial.println("tugofwar-playerB won line 3 moving");
      for (int i = 0; i <= gradualLed_A ; i++)
        for (int i = numOfLeds; i > gradualLed_B ; i--)
        {
          int r = 3;
          pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB_tugofwar, greenB_tugofwar, blueB_tugofwar));
        }

      if (gradualLed_B > 0)
      {
        gradualLed_B = gradualLed_B - increasingSpeed;
      }

      pixels.show();
    }
    delay(100);
    gradualLed_B = numOfLeds;

    /*reset to default*/
    reset();
    turnDefault = true;
    turnonTugOfWar = false;
    turnonBalance1 = false;
  }
}

