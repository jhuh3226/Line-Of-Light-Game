/*wave changing color on rotating*/
void defaulWave()
{
  int rmap = map(positionLed, 0, 240, 255, 0);
  int gmap = map(positionLed, 0, 240, 0, 0);
  int bmap = map(positionLed, 0, 240, 0, 255);
  int m = 2;

  //  Serial.print("ledColor");
  //  Serial.println(ledColor);

  //  Serial.print("positionLed: ");
  //  Serial.println(positionLed);
  //
  //  Serial.print(" timedifferencePlayer1: ");
  //  Serial.println(timedifferencePlayer1);
  //  Serial.print(" timedifferencePlayer2: ");
  //  Serial.println(timedifferencePlayer2);

  initializeToBlack();

  for (uint8_t r = 0; r < 4; r++)
  {
    if (changeDirectionDefault == true)
    {
      //      Serial.println("default, A being faster");
      for (int j = 0; j < numOfLeds; j++)
      {
        {
          pixels.setPixelColor(r * numOfLeds + j, pixels.Color(rmap / (((jMove + j) % 20)+1), gmap / (((jMove + j) % 20)+1), bmap / (((jMove + j) % 20)+1), 0));
        }
      }
    }

    else if (changeDirectionDefault == false)
    {
      //      Serial.println("default, B being faster");
      for (int j = numOfLeds -1 ; j > 0; j--)
      {
        pixels.setPixelColor(r * numOfLeds + j, pixels.Color(rmap / (((jMove - j) % 20)+1), gmap / (((jMove - j) % 20)+1), bmap / (((jMove - j) % 20)+1), 0));
      }
    }
  }

  jMove++;

  pixels.show();
  delay(50);
}

