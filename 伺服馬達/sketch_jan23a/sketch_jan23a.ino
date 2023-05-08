#include <Servo.h>   //載入函式庫，這是內建的，不用安裝
#define servo_num 7
Servo myservo[servo_num];
int number[10][7] = {
  //  a
  //f   b
  //  g
  //e   c
  //  d
  //a,b,c,d,e,f,g
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 1, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}, //9
};
void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= servo_num; i++)
  {
    myservo[i].attach(i + 2);
  }
  for (int i = 0; i <= servo_num; i++)
    myservo[i].write(0);
  delay(1000);
  for (int i = 0; i <= servo_num; i++)
    myservo[i].write(90);
  delay(1000);
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (number[i][j] == 1)
        myservo[j].write(0);
      else
        myservo[j].write(90);
    }
    Serial.println(i);
    delay(1000);
  }
  for (int j = 0; j < 7; j++)
  {
    if (number[8][j] == 1)
      myservo[j].write(0);
    else
      myservo[j].write(90);
  }
  Serial.println("ok");
}

void loop() {

  if (Serial.available())
  {
    int x = Serial.parseInt();
    Serial.println(x);
    for (int i = 0; i <= servo_num; i++)
      if (number[x][i] == 1)
        myservo[i].write(0);
      else
        myservo[i].write(90);
  }
}
