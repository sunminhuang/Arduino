int apin = 8;
int bpin = 9;
int cpin = 10;
int dpin = 11;
int delaytime = 2;

void setup()
{
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  pinMode(dpin, OUTPUT);

}

void loop()
{
  for(int i = 0;i<500;i++)
    R();
  delay(1000);
  for(int i = 0;i<500;i++)
    L();
  delay(1000);
}
void R()
{
  digitalWrite(dpin, HIGH);
  delay(delaytime);
  digitalWrite(dpin, LOW);

  digitalWrite(cpin, HIGH);
  delay(delaytime);
  digitalWrite(cpin, LOW);

  digitalWrite(bpin, HIGH);
  delay(delaytime);
  digitalWrite(bpin, LOW);

  digitalWrite(apin, HIGH);
  delay(delaytime);
  digitalWrite(apin, LOW);

}
void L()
{
  digitalWrite(apin, HIGH);
  delay(delaytime);
  digitalWrite(apin, LOW);

  digitalWrite(bpin, HIGH);
  delay(delaytime);
  digitalWrite(bpin, LOW);

  digitalWrite(cpin, HIGH);
  delay(delaytime);
  digitalWrite(cpin, LOW);

  digitalWrite(dpin, HIGH);
  delay(delaytime);
  digitalWrite(dpin, LOW);
}
