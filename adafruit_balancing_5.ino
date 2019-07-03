#include <Adafruit_NeoPXL8.h>

const byte interruptPin = MOSI;
const byte interruptPin2 = SCK;

/*button pin*/
const byte tugofwarButtonPin = 10;
const byte BalanceButtonPin = 12;
const byte resetButtonPin = 11;

//light speed;
float lightSpeed = 1.0;

int readingTugofwar;
int readingBalance;
int readingReset;

int balanceScore = 0;
int balanceLostScore = 0;
int gradualLed1;
int gradualLed2;

volatile byte state = LOW;

long randNumber;

boolean resetBack = false;

unsigned long currentTime;
unsigned long endTime;
unsigned long previousTime = 0;
unsigned long gameResultTime;
unsigned long gameStartTime;

/*used for countdown*/
unsigned long interval = 1000;

unsigned long insideTime;
unsigned long outsideTime;

volatile long timedifferencePlayer1;
volatile long timedifferencePlayer2;
volatile long temptimedifferencePlayer1;
volatile long temptimedifferencePlayer2;
volatile long timer1;//last millis
volatile long timer2;//last millis

volatile long constrainedTime1;
volatile long constrainedTime2;

boolean inside = false;
boolean outside = false;

boolean balancing1Done = false;
boolean turnonBalance1 = false;
boolean turnonTugOfWar = false;

boolean turnonBalanceWhite = false;

boolean countdownStart = false;
boolean countdownActivate = false;

boolean tugofwarSucceedPlayerA = false;
boolean tugofwarSucceedPlayerB = false;

boolean turnDefault = true;
//boolean gameStarted = true;

boolean getRandomNumber = true;
boolean gotNumber = false;

volatile float value;
volatile float previousValue;
boolean increaseValue = false;
boolean decreaseValue = false;

boolean player1Update = false;
boolean player2Update = false;

//if statement of getting random number
boolean okNumber = false;

//change direction
boolean changeDirectionDefault = false;

//inactive alert
boolean giveInactiveAlert = false;

const int numOfLeds = 240; // Number of leds

float floatPositionLed = numOfLeds / 2.0;
int positionLed = numOfLeds / 2;
int previousPositionLed;
int ledColor;

//variable for the led color, playerA: 0~positionled, playerB: positionled ~240
int redA = 255;
int greenA = 0;
int blueA = 255;

int redB = 0;
int greenB = 0;
int blueB = 255;

//variable for the led color for "tug of war", playerA: 0~positionled, playerB: positionled ~240
int redA_tugofwar = 255;
int greenA_tugofwar = 130;
int blueA_tugofwar = 0;

int redB_tugofwar = 0;
int greenB_tugofwar = 255;
int blueB_tugofwar = 255;

//brightness of the color
int brightnessValue = 0;

//balance game succeed
int lMove = 240;

//balance game fail
int gradualLedFail1 = numOfLeds / 2;
int gradualLedFail2 = numOfLeds / 2;

//default mode
int jMove = 240;

//
boolean insideValueAimArea = false;

int8_t dinPin[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, MISO, 13, -1, -1, -1, -1 };
Adafruit_NeoPXL8 pixels(numOfLeds, dinPin, NEO_GRBW);

//-------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);

  pinMode(tugofwarButtonPin, INPUT_PULLUP);
  pinMode(BalanceButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), rotate1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), rotate2, RISING);

  pixels.begin(); // Initializes the NeoPixel library
  pixels.setBrightness(255); // Value from 0 to 255%

  //randomSeed(analogRead(0));

  initializeToBlack();
  pixels.show();

}

//-------------------------------------------------------------------------------------------------------------------------
void loop()
{
  currentTime = millis();
  increaseValueFunction();
  decreaseValueFunction();
  countdown();
  light();
  balancing1();
  tugOfWar();
  randomNumb();
  balanceSucceedLed();
  balanceFailLed();
  tugofwarSucceedLed();
  inactive();
  inactiveAlert();

  /*button*/
  readingTugofwar = digitalRead(tugofwarButtonPin);
  readingBalance = digitalRead(BalanceButtonPin);
  readingReset = digitalRead(resetButtonPin);

  //  Serial.print("Tugofwar");
  //  Serial.println(readingTugofwar);
  //  Serial.print("Balance");
  //  Serial.println(readingBalance);
  //  Serial.print("Reset");
  //  Serial.println(readingReset);

  /*if not played, show default rainbow mode*/
  if (turnDefault == true)
  {
    defaulWave();
  }

  //-------------------------------------------------------------------------------------------------------------------------
  /*reset button*/
  if (readingReset == LOW)
  {
    Serial.println("Reset button clicked");

    reset();

    turnDefault = true;
    turnonTugOfWar = false;
    turnonBalance1 = false;
  }

  /*tugofwar button*/
  if (readingTugofwar == LOW)
  {
    Serial.println("Tug of War button clicked");

    reset();

    countdownStart = true;

    //resets game when not played
    gameStartTime = currentTime;
    Serial.print("gameStartTime: ");
    Serial.println(gameStartTime);

    turnDefault = false;
    turnonTugOfWar = true;
    turnonBalance1 = false;
  }

  /*balance button*/
  if (readingBalance == LOW)
  {
    Serial.println("Balance button clicked");

    reset();

    countdownStart = true;

    //resets game when not played
    gameStartTime = currentTime;
    Serial.print("gameStartTime: ");
    Serial.println(gameStartTime);

    turnDefault = false;
    turnonTugOfWar = false;
    turnonBalance1 = true;
  }

  /*print out status of the each button*/
  //  Serial.println(turnDefault);
  //  Serial.println(turnonTugOfWar);
  //  Serial.println(turnonBalance1);
  //-------------------------------------------------------------------------------------------------------------------------

  /* has to be end of the loop*/
  pixels.show();
}

void rotate1()
{
  temptimedifferencePlayer1 = currentTime - timer1;
  timer1 = currentTime;

  //  Serial.print(" timer1: ");
  //  Serial.println(timer1);

  if (temptimedifferencePlayer1 != 0)
  {
    timedifferencePlayer1 = temptimedifferencePlayer1;
    Serial.print(" timedifferencePlayer1: ");
    Serial.println(timedifferencePlayer1);
    player1Update = true;
  }
}

void rotate2()
{
  temptimedifferencePlayer2 = currentTime - timer2;
  timer2 = currentTime;

  //  Serial.print(" timer2: ");
  //  Serial.println(timer2);

  if (temptimedifferencePlayer2 != 0)
  {
    timedifferencePlayer2 = temptimedifferencePlayer2;
    Serial.print(" timedifferencePlayer2: ");
    Serial.println(timedifferencePlayer2);
    player2Update = true;
  }
}

void light()
{
  if ((timedifferencePlayer1 < timedifferencePlayer2) && decreaseValue == false /*&& player1Update == true*/)
  {
    decreaseValue = true;
    player1Update = false;
    changeDirectionDefault = true;

    //~ing
    lightSpeed = map(constrain(timedifferencePlayer2, 30.0, 200.0), 30.0, 200.0, 500.0, 100.0) * -1;
    lightSpeed = lightSpeed / 100.0;

    Serial.print("lightSpeed 1: ");
    Serial.println(lightSpeed);
  }

  if ((timedifferencePlayer1 > timedifferencePlayer2) && increaseValue == false /*&& player2Update == true*/)
  {
    increaseValue = true;
    player2Update = false;
    changeDirectionDefault = false;

    //Serial.print("td 2 ");
    //Serial.println(timedifferencePlayer1);
    lightSpeed = map(constrain(timedifferencePlayer1, 30.0, 200.0), 30.0, 200.0, 500.0, 100.0);
    lightSpeed = lightSpeed / 100.0;

    Serial.print("lightSpeed 2: ");
    Serial.println(lightSpeed);

    //Serial.println("Player2 faster");
  }

  //  Serial.print("value: ");
  //  Serial.println(value);
  //
  //  Serial.print("floatPositionLed: ");
  //  Serial.println(floatPositionLed);


  floatPositionLed = floatPositionLed + value;
  positionLed = floor(floatPositionLed);
  /*constrain led position within the limit*/
  positionLed = constrain(positionLed, 0, 240);

  //~ing
  /*when default wave mood  value don't exceed led limit*/
  if (turnDefault == true)
  {
    //when default wave mood, value don't add up the value*/
    value = 0;

    //    Serial.print("previousPositionLed: ");
    //    Serial.println(previousPositionLed);
    //    Serial.print("positionLed: ");
    //    Serial.println(positionLed);

    if (positionLed >= (numOfLeds - 1))
    {
      Serial.println("default-make led color 0");
      ledColor = 0;
      floatPositionLed = 0;
      positionLed = 0;
    }

    f  else if (positionLed < 0)
    {
      Serial.println("default-make led color 240");

      ledColor = 240;
      floatPositionLed = 240;
      positionLed = 240;
    }
  }

  /*when tug of war, unlike balance don't add up the value*/
  if (turnonTugOfWar == true)
  {
    value = 0.0;
  }

  //~do
  /*when balance game, if it reaches the other end, stop the movement of LED*/
  if (turnonBalance1 == true)
  {
    if (positionLed >= (numOfLeds - 1) || positionLed <= 0)
    {
      value = 0.0;
    }
  }

  timedifferencePlayer1 = 0;
  timedifferencePlayer2 = 0;

  /*added for adafruit*/
  for (uint8_t r = 0; r < 4; r++)
  {
    for (int i = 0; i <= positionLed ; i++)
    {
      if (turnonBalance1 == true || turnDefault == true)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA, greenA, blueA, brightnessValue));
      }

      else if (turnonTugOfWar == true)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redA_tugofwar, greenA_tugofwar, blueA_tugofwar, brightnessValue));
      }
    }
  }

  for (uint8_t r = 0; r < 4; r++)
  {
    for (int i = numOfLeds; i > positionLed ; i--)
    {
      if (turnonBalance1 == true || turnDefault == true)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB, greenB, blueB, brightnessValue));
      }

      else if (turnonTugOfWar == true)
      {
        pixels.setPixelColor(r * numOfLeds + i, pixels.Color(redB_tugofwar, greenB_tugofwar, blueB_tugofwar, brightnessValue));
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------
void increaseValueFunction()
{
  /*tug of war*/
  if (increaseValue == true && turnonTugOfWar == true)
  {
    value = 4.0;
    increaseValue = false;
  }

  /*balance*/
  if (increaseValue == true && turnonBalance1 == true && !(positionLed > (numOfLeds - 1)))
  {
    //if within the white aim area, decrease the value
    if (insideValueAimArea == true)
    {
      value = 0.25;
      increaseValue = false;
    }

    //if not, increase the value
    else
    {
      Serial.println("value is not 0.00");
      value = lightSpeed * 0.25;
      increaseValue = false;
    }
  }

  /*default*/
  if (increaseValue == true && turnDefault == true)
  {
    value = 4.0;
    increaseValue = false;
  }
}

void decreaseValueFunction()
{
  /*tug of war*/
  if (decreaseValue == true && turnonTugOfWar == true)
  {
    value = -3.0;
    decreaseValue = false;
  }

  /*balance*/
  if (decreaseValue == true && turnonBalance1 == true && !(positionLed < 0))
  {
    //if within the white aim area, decrease the value
    if (insideValueAimArea == true)
    {
      value = -0.25;
      decreaseValue = false;
    }

    //if not, decrease the value
    else
    {
      value = lightSpeed * 0.25;
      decreaseValue = false;
    }
  }


  //  //~ing if value is 0, don't make the value to be 0
  //  if (turnonBalance1 == true)
  //  {
  //    //if value was above 0 (like 0.75) but fell to 0, make that value to 0.05
  //    previousValue = value;
  //
  //    if ((previousValue > 0.0) && (value == 0))
  //    {
  //      Serial.println("value was above 0, now is  0.00");
  //      value = 0.05;
  //    }
  //
  //    else if ((previousValue < 0.0) && (value == 0))
  //    {
  //      Serial.println("value was below 0, now is  0.00");
  //      value = -0.05;
  //    }
  //  }

  /*default*/
  if (decreaseValue == true && turnDefault == true)
  {
    value = -4.0;
    decreaseValue = false;
  }
}

//-------------------------------------------------------------------------------------------------------------------------
void resetValue()
{
  /*reset value*/
  initializeToBlack();

  resetBack = false;
  //currentTime = 0;
  endTime = 0;
  previousTime = 0;
  gameResultTime = currentTime;
  gameStartTime = 0;

  insideTime = 0;
  outsideTime = 0;

  timedifferencePlayer1 = 0;
  timedifferencePlayer2 = 0;
  temptimedifferencePlayer1 = 0;
  temptimedifferencePlayer2 = 0;
  timer1 = 0;//last millis
  timer2 = 0;//last millis

  balanceScore = 0;
  balanceLostScore = 0;

  changeDirectionDefault = false;

  inside = false;
  outside = false;

  balancing1Done = false;
  turnonBalance1 = false;
  turnonTugOfWar = false;

  turnonBalanceWhite = false;

  countdownStart = false;
  countdownActivate = false;

  tugofwarSucceedPlayerA = false;
  tugofwarSucceedPlayerB = false;

  turnDefault = true;
  //gameStarted = true;

  getRandomNumber = true;
  gotNumber = false;

  increaseValue = false;
  decreaseValue = false;

  player1Update = false;
  player2Update = false;

  okNumber = false;

  //inactive alert
  giveInactiveAlert = false;

  floatPositionLed = numOfLeds / 2;
  positionLed = numOfLeds / 2;

  gradualLed1 = numOfLeds / 2;
  gradualLed2 = numOfLeds / 2;

  lMove = 240;

  jMove = 240;

  gradualLedFail1 = numOfLeds / 2;
  gradualLedFail2 = numOfLeds / 2;

  insideValueAimArea = false;

  //brightness of the color
  brightnessValue = 0;
  /*reset value*/
}

//-------------------------------------------------------------------------------------------------------------------------
void initializeToBlack()
{
  for (uint8_t r = 0; r < 4; r++)
  {
    for (int i = 0; i < numOfLeds ; i++)
    {
      pixels.setPixelColor(r * numOfLeds + i, pixels.Color(0, 0, 0, 0)); // This sends the updated pixel color to the hardware.
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------
void reset()
{
  Serial.println("reset");
  resetValue();
}

//-------------------------------------------------------------------------------------------------------------------------
void inactive()
{
  //Serial.println(currentTime);
  if (turnonTugOfWar == true || turnonBalance1 == true)
  {
    /*reset to default mode when both players stopped playing game after playing for a while*/
    //both of winder rotated
    if ((timer1 > gameStartTime) && (timer2 > gameStartTime))
    {
      //either of winder stopped rotating
      if ( (currentTime - timer1 >= 9000) && (currentTime - timer2 >= 9000))
      {
        reset();

        turnDefault = true;
        turnonTugOfWar = false;
        turnonBalance1 = false;

        Serial.println("reset due to inactive game play - both stopped after playing");
      }

      //steadily light getting dimed or dark
      if ( (currentTime - timer1 < 9000) && (currentTime - timer1 >= 6000) && (currentTime - timer2 < 9000) (currentTime - timer2 >= 6000))
      {
        giveInactiveAlert = true;

        Serial.println("getting dim - both stopped after playing");
      }
      else
      {
        giveInactiveAlert = false;
      }
    }

    //-----------------------------------
    /*reset to default mode when one player stopped playing game after playing for a while*/
    //both of winder rotated
    if ((timer1 > gameStartTime) && (timer2 > gameStartTime))
    {
      //either of winder stopped rotating
      if ( (currentTime - timer1 >= 15000) || (currentTime - timer2 >= 15000))
      {
        reset();

        turnDefault = true;
        turnonTugOfWar = false;
        turnonBalance1 = false;

        Serial.println("reset due to inactive game play - one stopped after playing");
      }

      //steadily light getting dimed or dark
      if ( (currentTime - timer1 < 15000) && (currentTime - timer1 >= 12000) && (currentTime - timer2 < 15000) (currentTime - timer2 >= 12000))
      {
        giveInactiveAlert = true;

        Serial.println("getting dim - one stopped after playing");
      }
      else
      {
        giveInactiveAlert = false;
      }
    }

    //-------------------------------------
    /*reset to default mode when only one player started playing but stopped after player for a while*/
    else if ((timer1 > gameStartTime) || (timer2 > gameStartTime))
    {
      if ( (currentTime - timer1 >= 9000) && (currentTime - timer2 >= 9000))
      {
        reset();

        turnDefault = true;
        turnonTugOfWar = false;
        turnonBalance1 = false;

        Serial.println("reset due to inactive game play - only one started game and stopped after rotating");
      }

      //steadily light getting dimed or dark
      if ( (currentTime - timer1 < 9000) && (currentTime - timer1 >= 6000) && (currentTime - timer2 < 9000) (currentTime - timer2 >= 6000))
      {
        giveInactiveAlert = true;

        Serial.println("getting dim - only one started game and stopped after rotating");
      }
      else
      {
        giveInactiveAlert = false;
      }
    }

    //-------------------------------------
    /*reset to default mode when players didn't play at all after pushing a button*/
    else if ((currentTime - gameStartTime) >= 8000)
    {
      if ((timer1 < gameStartTime) && (timer2 < gameStartTime))
      {
        reset();

        turnDefault = true;
        turnonTugOfWar = false;
        turnonBalance1 = false;

        Serial.println("reset due to inactive game play - both didn't play after button clicked");
      }
    }

    //steadily light getting dimed or dark
    if ((timer1 < gameStartTime) && (timer2 < gameStartTime))
    {
      if ( (currentTime - timer1 < 8000) && (currentTime - timer1 >= 5000) && (currentTime - timer2 < 8000) (currentTime - timer2 >= 5000))
      {
        giveInactiveAlert = true;

        Serial.println("getting dim - both didn't play after button clicked");
      }
      else
      {
        giveInactiveAlert = false;
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------
void randomNumb()
{
  if (getRandomNumber == true && gotNumber == false)
  {
    randNumber = random(numOfLeds - 21);
    //Serial.println(randNumber);
  }
  //  Serial.println(randNumber);

  //  if (getRandomNumber == true && gotNumber == false)
  //  {
  //    while (okNumber == false)
  //    {
  //      randNumber = random(numOfLeds - 20);
  //
  //      Serial.print("random: ");
  //      Serial.println(randNumber);
  //
  //      if ( abs(randNumber - ledPosition) < 150)
  //      {
  //        okNumber = true;
  //        Serial.println("Number is ok.");
  //      }
  //      else
  //      {
  //        okNumber = false;
  //        Serial.println("Number is too far. Trying again.");
  //      }
  //    }
  //  }
}


