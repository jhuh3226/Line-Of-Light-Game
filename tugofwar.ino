void tugOfWar()
{
  if (turnonTugOfWar == true)
  {
    /*set the center as white color*/
    int i = positionLed;

    for (uint8_t r = 0; r < 4; r++)
    {
      pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 255)); 
    }

    //-------------------------------------------------------------------------------------------------------------------------
    /*if playerA won*/
    if (positionLed >= numOfLeds)
    {
      tugofwarSucceedPlayerA = true;
    }

    /*if left playerB won*/
    else if (positionLed <= 0)
    {
      tugofwarSucceedPlayerB = true;
    }
  }
}
