int R[4] = {2, 3, 4, 5};
int C[4] = {6, 7, 8, 9};
int scanP[5] = {44, 42, 40, 38};
int seg7P[8] = {22, 24, 26, 28, 30, 32, 34, 36};
int segCode[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8,
                   0x80, 0x98, 0X88, 0X83, 0XC6, 0XA1, 0X86, 0X8E
                  };
//01234567  89ABCDEF
int dispData[4] = {0, 0, 0, 0};
int key = 255;

void setup() {
  for (int i = 0; i < 4; i++)
  {
    pinMode(R[i], OUTPUT);
    digitalWrite(R[i], 1);
    pinMode(C[i], INPUT);
  }
  DDRC = B11111111;
  //  for (int i = 0; i < 8; i++)
  //  {
  //    pinMode(seg7P[i], OUTPUT);
  //    digitalWrite(seg7P[i], 1);
  //  }
  for (int i = 0; i < 5; i++)
  {
    pinMode(scanP[i], OUTPUT);
    digitalWrite(scanP[i], 1);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(R[i], 0);
    for (int j = 0; j < 4; j++)
    {
      int cc = digitalRead(C[j]);
      if (cc == 0)
      {
        while (cc == 0)
          cc = digitalRead(C[j]);
        key = i * 4 + j;
        if (key >= 0 and key < 16)
        {
          for (int dig = 2; dig >= 0; dig--)
            dispData[dig + 1] = dispData[dig];
          dispData[0] = key;
        }
      }
    }
    digitalWrite(R[i], 1);
    for (int sp = 0; sp < 12; sp++)
    {
      for (int dig = 0; dig < 4; dig++)
      {
        byte x = segCode[dispData[dig]];
        //        for (int k = 0; k < 8; k++)
        //        {
        //          digitalWrite(seg7P[k], bitRead(x, k));
        //        }
        PORTC = x;
        digitalWrite(scanP[dig], 0);
        delay(1);
        digitalWrite(scanP[dig], 1);
      }
    }
  }
}
