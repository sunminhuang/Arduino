int F[2] = {13, 12};
int LED[4] = {7, 6, 5, 4};

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  for (int i = 4; i <= 7; i++)
  {
    digitalWrite(i, HIGH);
  }
}

void loop() {
  //  int gr[2][4] = {{1, 0, 0, 0}, {1, 1, 0, 1}};
  int de(1000);
  A();
  delay(de);
  for (int i = 0; i < 10; i++)
    B(200);
  delay(de);
  for (int i = 0; i < 10; i++)
    C(200);
  delay(de);
  for (int i = 0; i < 10; i++)
    D();
  delay(de);
  for (int i = 0; i < 10; i++)
    E();
  delay(de);
  for (int i = 0; i < 10; i++)
    k();
  delay(de);
}

void Stop()
{
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(F[i], LOW);
  }
  delay(500);
}
void A()//上層閃 下層閃
{
  for (int k = 0; k < 10; k++)
  {
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(F[i], HIGH);
      for (int j = 0; j < 4; j++)
      {
        digitalWrite(LED[j], LOW);
      }
      delay(200);
      for (int j = 0; j < 4; j++)
      {
        digitalWrite(LED[j], HIGH);
      }
      digitalWrite(F[i], LOW);
    }
  }
}
void B(int d)//側看左旋轉
{
  for (int i = 0; i < 4; i += 2)
  {
    digitalWrite(LED[i], LOW);
    digitalWrite(LED[i + 1], LOW);
    if (i == 0)
    {
      for (int j = 0; j <= 1; j++)
      {
        delay(d);
        digitalWrite(F[j], HIGH);
        delay(d);
        digitalWrite(F[j], LOW);
        delay(d);
      }
    }
    else if (i == 2)
    {
      for (int j = 1; j >= 0; j--)
      {
        delay(d);
        digitalWrite(F[j], HIGH);
        delay(d);
        digitalWrite(F[j], LOW);
        delay(d);
      }
    }
    digitalWrite(LED[i], HIGH);
    digitalWrite(LED[i + 1], HIGH);
  }
}
void C(int d)//俯瞰左旋轉
{
  digitalWrite(F[0], HIGH);
  digitalWrite(F[1], HIGH);
  for (int i = 0; i < 4; i++)
  {
    delay(d);
    digitalWrite(LED[i], LOW);
    delay(d);
    digitalWrite(LED[i], HIGH);
    delay(d);
  }
  digitalWrite(F[0], LOW);
  digitalWrite(F[1], LOW);
}
void D()//兩科隨機閃
{
  int ran_F[2] ;
  int ran_num[2];
  int d = 150;
  for (int i = 0; i < 2; i++)
    ran_F[i] = random(2);
  ran_num[0] = random(4);
  while (true)
  {
    ran_num[1] = random(4);
    if (ran_num[0] != ran_num[1])
      break;
  }
  for (int k = 0; k < 12; k++)
  {
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(F[ran_F[i]], HIGH);
      digitalWrite(LED[ran_num[i]], LOW);
      delay(10);
      digitalWrite(F[ran_F[i]], LOW);
      digitalWrite(LED[ran_num[i]], HIGH);
    }
  }
  delay(d);
}
void E()//隨機閃
{
  int gr[2][4] = {0};
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      gr[i][j] = random(2);
    }
  }
  for (int k = 0; k < 10000; k++)
  {
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(F[i], HIGH);
      for (int j = 0; j < 4; j++)
      {
        if (gr[i][j] == 1)
        {
          digitalWrite(LED[j], LOW);
        }
      }
      for (int j = 0; j < 4; j++)
      {
        if (gr[i][j] == 1)
        {
          digitalWrite(LED[j], HIGH);
        }
      }
      digitalWrite(F[i], LOW);
    }
  }
}
void k()
{
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(F[i], HIGH);
  }
  for (int j = 0; j < 2; j++)
  {
    digitalWrite(LED[j], LOW);
    digitalWrite(LED[j + 2], LOW);
    delay(250);
    digitalWrite(LED[j], HIGH);
    digitalWrite(LED[j + 2], HIGH);
    delay(250);
  }

}
