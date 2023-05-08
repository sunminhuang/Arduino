#define A_A1 8
#define A_B1 9
#define B_A1 10
#define B_B1 11
#define Speed 150
void setup() {
  // put your setup code here, to run once:
  pinMode(A_A1,OUTPUT);
  pinMode(A_B1,OUTPUT);
  pinMode(B_A1,OUTPUT);
  pinMode(B_B1,OUTPUT);
  digitalWrite(A_A1,LOW);
  digitalWrite(A_B1,LOW);
  digitalWrite(B_A1,LOW);
  digitalWrite(B_B1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A_A1,HIGH);
  analogWrite(A_B1,Speed);
  digitalWrite(B_A1,HIGH);
  analogWrite(B_B1,Speed);
  delay(4000);
  digitalWrite(A_A1,LOW);
  analogWrite(A_B1,Speed);
  digitalWrite(B_A1,LOW);
  analogWrite(B_B1,Speed);
  delay(4000);
}
