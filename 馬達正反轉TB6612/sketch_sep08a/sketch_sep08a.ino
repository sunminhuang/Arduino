#include <SparkFun_TB6612.h>
// 設定所有腳位對應 Arduino 的Pins
#define AIN1 2   // 控制輸入A1
#define AIN2 4   // 控制輸入A2
#define BIN1 7   // 控制輸入B1
#define BIN2 8   // 控制輸入B2
#define PWMA 5
#define PWMB 6
#define STBY 9

//超音波
int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
long duration, cm, inches;

// 設定Offset，可以是 1 或 -1，1表示正轉，-1表示反轉
const int offsetA = 1;
const int offsetB = 1;

// 初始化馬達，設定控制板引腳

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup()
{
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出
  pinMode(echoPin, INPUT);
}

void loop() {
  while (true)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);             // 讀取 echo 的電位
    duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
    cm = (duration / 2) / 29.1;
  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    if (cm >= 15)
    {
      forward(motor1, motor2, 150);  // 兩個馬達以150的速度前進
    }
    else if (cm <= 5) {
      back(motor1, motor2, -150);  // 兩個馬達以150的速度後退
    }
    else if (cm < 15 and cm > 5)
    {
      brake(motor1, motor2);     // 兩個馬達停止
    }
    delay(100);
  }
}
