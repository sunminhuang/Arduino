// include the library
#include <Unistep2.h>

// Define some steppers and the pins they will use
Unistep2 stepperY(8, 9, 10, 11, 4096, 1000); // IN1、IN2、IN3、IN4 引腳，每轉步數，步長延遲（微秒）

void setup()
{
  // Your setup code here
  // The library initializes the pins for you
  Serial.begin(9600);

}
int i = 0;
void loop()
{
  stepperY.run();
  //如果stepsToGo返回0步進不移動
  while (stepperY.stepsToGo() == 0)
  {
    stepperY.move(-4096);
  }

}
void R()
{

}
