/*
 * DC+ 接5V DC- 接GNGD IN 接PIN
 * NC NO 選一個用
 * NC：Normal Close，常閉，它在正常情況下是接通的。
 * NO：Normal Open，常開，也就是正常情況它是不通電的。
 * COM：Common Ground，共接電，很多人習慣把外電接到這個接腳，再從NO或NC接到外部設備上。
 */

char Num; 
void setup() {
 pinMode(8,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  //讀取序列埠傳入的字元
  if(Serial.available()){
    Num=Serial.read();
    Serial.println(Num);
  } 
  delay(10);
  if(Num=='1'){
    digitalWrite(8,HIGH); //低電平觸發，LOW時繼電器觸發
  }
  else{
    digitalWrite(8,LOW);
  }
}
