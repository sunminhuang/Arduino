
int LED = 13;
int val ;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  Serial.println("0"); //送出字元 0
  reback_blink(); //執行副程式 reback_blink();
  delay(1000);
  Serial.println("1"); //送出字元 0
  reback_blink(); //執行副程式 reback_blink();
  delay(1000);
}

void reback_blink() { //此副程式中的註解拿掉，可以用在單獨對電腦的測試
  while (!Serial.available()) {
    /*Serial.println("wait");*/
  }
  if (Serial.available()) {
    val = Serial.read();
    if (val == '1') {
      digitalWrite(LED, HIGH);
      //Serial.println("one");
    }
    if (val == '0') {
      digitalWrite(LED, LOW);
      //Serial.println("zero");
    }
  }
}
