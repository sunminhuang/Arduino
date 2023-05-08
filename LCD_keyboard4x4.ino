#include <LiquidCrystal.h>
const byte colPins[4] = {6, A0, A1, A2};
const byte rowPins[4] = {10, 9, 8, 7};
const char keymap[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char dis[8] = {};


byte i, j;
byte scanVal;
int seconds = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  for (i = 0; i <= 3; i++) {
    pinMode(rowPins[i], INPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
    digitalWrite(rowPins[i], HIGH);
  }
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("093226      0525");
  lcd_1.setCursor(0, 1);
  lcd_1.print("student:");
  Serial.begin(9600);
}

void loop()
{
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      digitalWrite(colPins[j], LOW);
      scanVal = digitalRead(rowPins[i]);
      if (scanVal == LOW) {
        Serial.println(keymap[i][j]);
        for (int dig = 6; dig >= 0; dig--)
          dis[dig + 1] = dis[dig];
        dis[0] = keymap[i][j];
        delay(200);
        digitalWrite(colPins[j], HIGH);
        break;
      }
      digitalWrite(colPins[j], HIGH);
    }
  }
  lcd_1.setCursor(8, 1);
  for(int i=0;i<8;i++)
  {
    lcd_1.print(dis[7-i]);
  }

}
