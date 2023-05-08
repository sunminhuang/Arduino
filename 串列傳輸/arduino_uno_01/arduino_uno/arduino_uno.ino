#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 7); // RX=8, TX=7

String text = "";
boolean gotText = false;
int values = 0;

void setup(void)
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("hello");
}

void loop(void)
{
  while (Serial.available())
  {
    gotText = true;
    char tempChar = char(Serial.read());
    text += tempChar;
    values *= 10;
    values += (tempChar - 48);
    delay(1);
  }
  if (gotText)
  {
    gotText = false;
    Serial.println(values);
    Serial.println("sunmin");
    text = "";
    values = 0;
  }
}
