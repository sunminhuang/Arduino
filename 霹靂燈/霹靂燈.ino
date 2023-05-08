void setup() 
{
  for(int i=0;i<19;i++)
  {
    pinMode(2+i,OUTPUT);
  }
}

void loop() {
  for(int i=0;i<9;i++)
  {
    digitalWrite(2+i,HIGH);
    delay(100);
    digitalWrite(2+i,LOW);
    delay(100);
  }
  for(int j=10;j >= 2;j--)
  {
    digitalWrite(j,HIGH);
    delay(100);
    digitalWrite(j,LOW);
    delay(100);
  }
}
