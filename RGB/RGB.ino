void setup() {
  pinMode(2,INPUT_PULLUP);//紅色按鈕
  pinMode(3,INPUT_PULLUP);//綠色按鈕
  pinMode(4,INPUT_PULLUP);//藍色按鈕

  pinMode(5,OUTPUT);//R
  pinMode(6,OUTPUT);//G
  pinMode(7,OUTPUT);//B
}

void loop() 
{
  if(digitalRead(2) == LOW)
  {
    //紅色按下
    digitalWrite(5,1);//R
    digitalWrite(6,0);//G
    digitalWrite(7,1);//B
  }
  else if(digitalRead(3) == LOW)
  {
    //綠色按下
    digitalWrite(5,1);//R
    digitalWrite(6,1);//G
    digitalWrite(7,0);//B
  }
  else if(digitalRead(4) == LOW)
  {
    //藍色按下
    digitalWrite(5,1);//R
    digitalWrite(6,1);//G
    digitalWrite(7,1);//B
  }
}
