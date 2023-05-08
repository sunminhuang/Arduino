int red=2;
int yellow=3;
int green=4;
int buzz=5;

void setup () {
  pinMode (red,OUTPUT);
  pinMode (yellow,OUTPUT);
  pinMode (green,OUTPUT);
  pinMode (buzz,OUTPUT);  
  Serial.begin (9600);
  digitalWrite(buzz,LOW);   
}
 
void loop() {
  //從A0讀取輸入
  int value = analogRead(A0);
  Serial.println(value);          
  delay(500);
}
