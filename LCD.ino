#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.begin(16, 2);
  lcd.print("hello");
}

void loop() {
  lcd.setCursor(16, 1);

  for(int i=0;i<10;i++)
  {
    lcd.print(i);
    //位移等候時間
    delay(250);
    //將第一行向左邊移一個位
    lcd.scrollDisplayLeft();
  }

  lcd.clear();
  
}


 
