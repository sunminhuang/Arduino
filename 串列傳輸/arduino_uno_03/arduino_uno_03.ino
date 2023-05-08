#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

int LED = 13;
int val ;
void setup() {
  Serial.begin(9600);
  int a_n=0;
  int b_n=20;
  String a,b;
  a = String(a_n);
  b = String(b_n);
  a += b;
  Serial.println(a);
}
void loop() {

}
