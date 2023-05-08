#include<FlexiTimer2.h>
#include<TimerOne.h>
boolean output = HIGH;
int scanP[5] = {38, 40, 42, 44, 46};
int seg7P[8] = {22, 24, 26, 28, 30, 32, 34, 36};
int segCode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98};
int dispData[4] = {0, 0, 0, 0};

void blinkLED()
{
//  boolean output=HIGH;
  output = !output;
  digitalWrite(46, output);
}

void event()
{
  dispData[3] = dispData[3] + 1;
  if (dispData[3] > 9)
  {
    dispData[3] = 0;
    dispData[2] = dispData[2] + 1;
  }
  if (dispData[2] > 5)
  {
    dispData[2] = 0;
    dispData[1] = dispData[1] + 1;
  }
  if (dispData[1] > 9)
  {
    dispData[1] = 0;
    dispData[0] = dispData[0] + 1;
  }
  if (dispData[0] == 2 and dispData[1] > 3)
  {
    dispData[0] = 0;
    dispData[1] = 0;
  }
}


void setup()
{
  FlexiTimer2::set(10, 1.0 / 1000, event);
  FlexiTimer2::start();
  for (int i = 0; i < 4; i++)
  {
    pinMode(scanP[i], OUTPUT);
    digitalWrite(scanP[i], 1);
  }
  DDRC = B11111111;
  //for(int i=0;i<8;i++)
  //{
  // pinMode(seg7P[i],OUTPUT);
  // digitalWrite(seg7P[i],1);
  //}
  pinMode(46, OUTPUT);
  digitalWrite(46, 0);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(blinkLED);
}

void loop()
{
  for (int i = 0; i < 250; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      byte x = segCode[dispData[j]];
      PORTC = x;
      //    for(int k=0;k<8;k++)
      //    {
      //     digitalWrite(seg7P[k],bitRead(x,k));
      //    }
      digitalWrite(scanP[j], 0);
      delay(1);
      digitalWrite(scanP[j], 1);
    }
  }
}
