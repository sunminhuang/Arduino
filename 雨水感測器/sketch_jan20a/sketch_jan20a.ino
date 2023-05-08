int led=5;
int buzz=4;
int get_D3 = 3;
int get_A0 = A0;

void setup(){
  pinMode(led,OUTPUT);  
  pinMode(buzz, OUTPUT);  
  pinMode(get_D3, INPUT);
  Serial.begin(9600);  
}
void loop(){

  int value = analogRead(A0);    //從A0讀取感測值

  Serial.print(value);    
  Serial.print("   ");  

  if(digitalRead(get_D3) == LOW){
    Serial.println("Digital value : wet"); 
    digitalWrite(buzz,HIGH);     
  }
  else{
    Serial.println("Digital value : dry");
    digitalWrite(buzz,LOW);  
  }
  delay(1000);
}
