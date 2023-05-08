//溫度感測器
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//IC卡
#include <SPI.h>;
#include <MFRC522.h>;     // 引用程式庫
#define RST_PIN      48        // 讀卡機的重置腳位
#define SS_PIN       53        // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
#define Name_quantity 2
byte chack[Name_quantity][4] = {
  {192, 186, 145, 117},
  {NULL, NULL, NULL, NULL},
};
String Name[Name_quantity] = {"sunmin", "XXXXXX"};
String user = "";
//螢幕
#include <splash.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);
//紅外線測距
#define sensor A0
//ws2812
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    2
#define LED_COUNT 10
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//步進馬達
int apin = 8;
int bpin = 9;
int cpin = 10;
int dpin = 11;
int delaytime = 2;
int above = 30;//上方校準
int down = 31;//下方校準

int send_N_C[2] = {NULL};

void setup() {
  Serial.println("================================================");
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Adafruit MLX90614 test");
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");
  Serial.println("RFID reader is ready!");
  SPI.begin();
  mfrc522.PCD_Init();   // 初始化MFRC522讀卡機模組
  Serial.println("================================================");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 設定 I2C addr 0x3C
  display.clearDisplay();// 清除顯示緩衝區
  Serial.println("OLED OK");
  OLED("Name", Temperature());
  Serial.println("================================================");
  Serial.println(Measurement());
  Serial.println("================================================");
  //ws2810設定
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();           // 初始化 燈條
  strip.show();            // 關閉所有燈
  strip.setBrightness(50); // 將亮度設置為 1/5（最大 = 255）
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(100, 5, 100));
    strip.show();
    delay(10);
  }
  strip.begin();
  strip.show();
  Serial.println("ws2812 OK");
  Serial.println("================================================");
  pinMode(4, OUTPUT); //繼電器設定
  Serial.println("Spray OK");
  Serial.println("================================================");
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  pinMode(dpin, OUTPUT);
  pinMode(above, INPUT);//上方
  pinMode(down, INPUT);//下方
  while (digitalRead(above) == LOW) //初始位置校準
  {
    Step_motor(true);
    delay(10);
  }
  Serial.println("Stepping motor OK");
  Serial.println("================================================");
}

void loop()
{
  /*
     判斷IC是否正確
     步進馬達下降
     檢查是否偵測到頭部
     量測體溫
     啟動繼電器噴灑酒精
     下降到最下面
     關閉繼電器
     打開子外燈
     上升
     回到最上面
     關閉紫外燈
  */

  if (RFID)
  {
    while (Measurement() > 4)//感測到人
      Step_motor(true);
    int temperature = Temperature();
    send_N_C[1] = temperature;
    Serial.println(send_N_C[0]+","+send_N_C[1]);
      OLED(user, temperature); //顯示名子與溫度
      user = "";
      Spray(true);//噴灑酒精
      while (down != HIGH) //到底部
      Step_motor(true);
      Spray(false);//挺只噴灑
      Ultraviolet_rays(true);//開啟紫外線
      while (above != HIGH) //上升最上方
        Step_motor(false);
        Ultraviolet_rays(false);//關閉紫外線
    }
}
//RFID  RST:5 SDA:53 MOSI:51 MISO:50 SCK:52  id[0]: C0 id[1]: BA id[2]: 91 id[3]: 75
bool RFID()
{
  bool ch = false;
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    int idSize = mfrc522.uid.size;   // 取得UID的長度
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    for (int i = 0; i < Name_quantity; i++)
    {
      for (int j = 0; j < idSize; j++)
      { // 逐一檢查UID碼
        if (id[j] == chack[i][j])
          ch = true;
        else
        {
          ch = false;
          break;
        }
      }
      if (ch)
      {
        user = String(Name[i]);
        send_N_C[0] = i;
      }
    }
    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
  }
  return ch;
}
//步進馬達
void Step_motor(bool UP_DOWN)
{
  if (UP_DOWN)
  {
    digitalWrite(dpin, HIGH);
    delay(delaytime);
    digitalWrite(dpin, LOW);

    digitalWrite(cpin, HIGH);
    delay(delaytime);
    digitalWrite(cpin, LOW);

    digitalWrite(bpin, HIGH);
    delay(delaytime);
    digitalWrite(bpin, LOW);

    digitalWrite(apin, HIGH);
    delay(delaytime);
    digitalWrite(apin, LOW);
  }
  else
  {
    digitalWrite(apin, HIGH);
    delay(delaytime);
    digitalWrite(apin, LOW);

    digitalWrite(bpin, HIGH);
    delay(delaytime);
    digitalWrite(bpin, LOW);

    digitalWrite(cpin, HIGH);
    delay(delaytime);
    digitalWrite(cpin, LOW);

    digitalWrite(dpin, HIGH);
    delay(delaytime);
    digitalWrite(dpin, LOW);
  }
}
//紅外線感測
int Measurement()
{
  float volts = analogRead(sensor) * 0.0048828125; // value from sensor * (5/1024)
  int distance = 13 * pow(volts, -1); // worked out from datasheet graph
  return distance;
}
//體溫計
float Temperature()
{
  return mlx.readObjectTempC();
}
//螢幕
void OLED(String Name, int C)
{
  // 顯示文字
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(Name);
  display.display();
  delay(2000);
  // 顯示數字
  display.setTextSize(1.5);
  display.setCursor(0, 8);
  display.println(C);
  display.display();
  delay(2000);
  display.clearDisplay();
}
//酒精噴灑
/*
   DC+ 接5V DC- 接GNGD IN 接PIN
   NC NO 選一個用
   NC：Normal Close，常閉，它在正常情況下是接通的。
   NO：Normal Open，常開，也就是正常情況它是不通電的。
   COM：Common Ground，共接電，很多人習慣把外電接到這個接腳，再從NO或NC接到外部設備上。
*/
void Spray(bool DP)
{
  if (DP)
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}
//WS2812
void Ultraviolet_rays(bool ON_OFF)
{
  if (ON_OFF)
  {
    for (int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(100, 5, 100));
    }
    strip.show();
  }
  else
  {
    for (int i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
}
