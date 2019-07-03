int rangeOfBalance = 20;
//game difficulty should be 9000
long gameDifficulty = 8000;

//unsigned long interval = 1000;

void balancing1()
{
  //  Serial.print("countdownActivate");
  //  Serial.println(countdownActivate);

  //-------------------------------------------------------------------------------------------------------------------------
  if (turnonBalance1 == true)
  {
    /*constrain led position within the limit*/
    positionLed = constrain(positionLed, 0, 240);

    /*trigger balance white*/
    if ((currentTime >= gameResultTime && currentTime <= gameResultTime + gameDifficulty) && (balancing1Done == false))
    {
      turnonBalanceWhite = true;

      /*radom number creater*/
      gotNumber = false;
    }

    //-------------------------------------------------------------------------------------------------------------------------
    /*failed to reach the goal & time has passed*/
    else if (currentTime >= gameResultTime + gameDifficulty && (balancing1Done == false))
    {
      turnonBalanceWhite = false;
      gameResultTime = currentTime;

      gotNumber = false;

      Serial.println("Didn't make it");
      balanceLostScore ++;
      Serial.print("balanceLostScore");
      Serial.println(balanceLostScore);

      initializeToBlack();

      /*indication of failing by blinking*/
      while (gradualLed1 < numOfLeds)
      {
        for (uint8_t r = 0; r < 4; r++)
        {
          for (int i = 0 ; i < numOfLeds ; i++)
          {
            pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255));
          }
        }

        if (gradualLed1 < numOfLeds)
        {
          gradualLed1 += 5;
        }
        pixels.show();
      }
      gradualLed1 = numOfLeds / 2;
      
    }

    //-------------------------------------------------------------------------------------------------------------------------
    /*succeeded to reach the goal*/
    else if (balancing1Done == true)
    {
      gameResultTime = currentTime;
      balancing1Done = false;
      gotNumber = false;

      //~ing
      // increase the score only if the two players moved winder, then what will indicate movement of the winder
      if ((timer1 > gameStartTime) && (timer2 > gameStartTime))
      {
        balanceScore ++;
        Serial.println("On the way to success");
        Serial.print("balanceScore");
        Serial.println(balanceScore);
      }
    }
  }
  //  Serial.print("currentTime");
  //  Serial.println(currentTime);
  //  Serial.print("gameResultTime");
  //  Serial.println(gameResultTime);
  //-------------------------------------------------------------------------------------------------------------------------

  /*trigger balance white*/
  if (turnonBalance1 == true && turnonBalanceWhite == true)
  {
    /*stop creating random number*/
    gotNumber = true;

    /*white color area*/
    for (uint8_t r = 0; r < 4; r++)
    {
      for (int i = randNumber; i < randNumber + rangeOfBalance; i++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255));
      }
    }

    /*set the center position of led as red*/
    if (positionLed >= randNumber  && positionLed <= randNumber + (rangeOfBalance - 1))
    {
      int i = positionLed;
      for (uint8_t r = 0; r < 4; r++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(255, 0, 0));
      }

      //if within the position, decrease the value added up number by setting boolean as true
      insideValueAimArea = true;
    }
    else
    {
      int i = positionLed;

      for (uint8_t r = 0; r < 4; r++)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255));
      }

      //if outside the area, increase the value added up number by setting boolean as false
      insideValueAimArea = false;
    }


    /*if before it wasn't inside the range and now inside the range, save the current time*/
    if (positionLed >= randNumber  && positionLed <= randNumber + (rangeOfBalance - 1) && inside == false)
    {
      //      outside = false;
      insideTime = currentTime;
      inside = true;
      //      Serial.println("insideTime");
      //      Serial.println(insideTime);
    }

    /* if before it wasn't outside the range and now inside the range, save the current time*/
    if (!(positionLed >= randNumber && positionLed <= randNumber + (rangeOfBalance - 1)) && outside == false)
    {
      inside = false;
      //      outsideTime = currentTime;
      //      Serial.println("outsideTime");
      //      Serial.println(outsideTime);
      //      outside = true;
    }


    if (positionLed >= randNumber  && positionLed <= randNumber + (rangeOfBalance - 1))
    {
      // if difference betwwen outsidetime and inside time is bigger than 1 seconds and less than 2 seconds,
      if ((currentTime - insideTime) >= 500 && (currentTime - insideTime) < 1000)
      {
        Serial.println("1 second passed");
        //        for (uint8_t r = 0; r < 4; r++)
        //        {
        //          pixels.setPixelColor(r * numOfLeds + randNumber, pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 1), pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 14), pixels.Color(redB, greenB, blueB, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 15), pixels.Color(redB, greenB, blueB, 150));
        //        }
      }

      // if difference betwwen outsidetime and inside time is bigger than 2 seconds and less than 3 seconds,
      if ((currentTime - insideTime) >= 1000 && (currentTime - insideTime) < 1500)
      {
        Serial.println("2 second passed");
        //        for (uint8_t r = 0; r < 4; r++)
        //        {
        //          pixels.setPixelColor(r * numOfLeds + randNumber, pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 1), pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 2), pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 3), pixels.Color(redA, greenA, blueA, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 12), pixels.Color(redB, greenB, blueB, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 13), pixels.Color(redB, greenB, blueB, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 14), pixels.Color(redB, greenB, blueB, 150));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 15), pixels.Color(redB, greenB, blueB, 150));
        //        }
      }

      // if difference betwwen outsidetime and inside time is bigger than 3 seconds and less than 4 seconds,
      if ((currentTime - insideTime) >= 1500 && (currentTime - insideTime) < 2000)
      {
        Serial.println("3 second passed");
        //        for (uint8_t r = 0; r < 4; r++)
        //        {
        //          pixels.setPixelColor(r * numOfLeds + randNumber, pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 1), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 2), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 3), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 4), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 5), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 6), pixels.Color(redA, greenA, blueA));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 9), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 10), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 11), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 12), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 13), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 14), pixels.Color(redB, greenB, blueB));
        //          pixels.setPixelColor(r * numOfLeds + (randNumber + 15), pixels.Color(redB, greenB, blueB));
        //        }

      }

      if ((currentTime - insideTime) >= 2000 && turnonBalance1 == true)
      {
        for (uint8_t r = 0; r < 4; r++)
        {
          pixels.setPixelColor(r * numOfLeds + randNumber, pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 1), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 2), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 3), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 4), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 5), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 6), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 7), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 8), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 9), pixels.Color(redA, greenA, blueA));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 10), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 11), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 12), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 13), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 14), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 15), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 16), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 17), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 18), pixels.Color(redB, greenB, blueB));
          pixels.setPixelColor(r * numOfLeds + (randNumber + 19), pixels.Color(redB, greenB, blueB));
        }

        /*indication of succeess*/
        initializeToBlack();

        while (gradualLed1 < numOfLeds)
        {
          for (uint8_t r = 0; r < 4; r++)
          {
            for (int i = numOfLeds / 2; i <= gradualLed1 ; i++)
            {
              pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB, greenB, blueB));
            }
            for (int i = numOfLeds / 2 ; i > gradualLed2 ; i--)
            {
              pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA, greenA, blueA));
            }
          }

          if (gradualLed1 < numOfLeds)
          {
            gradualLed1 = gradualLed1 + 4;
          }

          if (gradualLed2 > 0)
          {
            gradualLed2 = gradualLed2 - 4;
          }

          pixels.show();
          delay(10);
        }

        gradualLed1 = numOfLeds / 2;
        gradualLed2 = numOfLeds / 2;

        balancing1Done = true;
        turnonBalanceWhite = false;

        gotNumber = false;
      }
    }
  }
}

