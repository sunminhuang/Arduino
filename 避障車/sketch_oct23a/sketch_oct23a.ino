const int trigPin = 3;             //Trig Pin
const int echoPin = 4;             //Echo Pin
const int motorA1 =  8;            // A1A
const int motorA2  = 9;            // A1B
const int motorB1 =  10;            // B1A
const int motorB2 =  11;            // B1B

long duration, cm, inches;
int BackwardSpeed = 100;
int ForwardSpeed = 100;

void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);          // 定義輸入和輸出
  pinMode(echoPin, INPUT);

  pinMode( motorA1 , OUTPUT);
  pinMode( motorA2 , OUTPUT);

  pinMode( motorB1 , OUTPUT);
  pinMode( motorB2 , OUTPUT);
}

void loop() {
//
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(5);
//  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  pinMode(echoPin, INPUT);          // 讀取 echo 的電位
//  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
//
//  cm = (duration / 2) / 29.1;       // 將時間換算成距離 cm 或 inch
//  Serial.println(cm);

//  if ( cm < 20 ) {
//    // 先倒退
//    for (int i = 0; i < 5000 ; i++) {
//      motorBackward();
//    }
//    // 再右轉彎
//    for (int i = 0; i < 5000 ; i++) {
//      motorRight();
//    }
//  } else
//  {
//    motorLeft();
//    delay(1000);
//    motorForward();
//  }
  analogWrite(motorA1,255);
  digitalWrite(motorA2,HIGH);
  delay(2000);
  analogWrite(motorB1,255);
  digitalWrite(motorB2,LOW);
  delay(2000);
  analogWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  analogWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
  delay(3000);
  analogWrite(motorB1,255);
  digitalWrite(motorB2,HIGH);
  delay(2000);
  analogWrite(motorB1,255);
  digitalWrite(motorB2,LOW);
  delay(2000);
}

void motorStop() {
  digitalWrite( motorA1 , LOW);
  digitalWrite( motorA2 , LOW);
  digitalWrite( motorB1 , LOW);
  digitalWrite( motorB2 , LOW);
}

// 往後
void motorBackward() {
  //  digitalWrite( motorA1 , HIGH);
  analogWrite( motorA1 , BackwardSpeed);
  digitalWrite( motorA2 , LOW);
  digitalWrite( motorB1 , LOW);
  analogWrite( motorB2 , BackwardSpeed);

}

// 往前
void motorForward() {
  digitalWrite( motorA1 , LOW);
  analogWrite( motorA2 , ForwardSpeed);
  analogWrite( motorB1 , ForwardSpeed);
  digitalWrite( motorB2 , LOW);
}

// 右轉
void motorRight() {
  digitalWrite( motorA1 , LOW);
  analogWrite( motorA2 , ForwardSpeed);
  digitalWrite( motorB1 , LOW);
  analogWrite( motorB2 , ForwardSpeed);
}

// 左轉
void motorLeft() {
  digitalWrite( motorA1 , LOW);
  analogWrite( motorA2 , ForwardSpeed);
  digitalWrite( motorB1 , LOW);
  analogWrite( motorB2 , ForwardSpeed);
}
