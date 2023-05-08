#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <SPI.h>;
#include <MFRC522.h>;     // 引用程式庫
#define RST_PIN      48        // 讀卡機的重置腳位
#define SS_PIN       53        // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
byte chack[4] = {192, 186, 145, 117};

#include <splash.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);

#define sensor A0 //紅外線測距

//ws2812
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    2
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int apin = 8;
int bpin = 9;
int cpin = 10;
int dpin = 11;
int delaytime = 2;

const int stepPin = 30;
const int dirPin = 31;

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
  OLED("OLED OK", Temperature());
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
  Serial.println("ws2812 OK");
  Serial.println("================================================");
  pinMode(4, OUTPUT); //繼電器設定
  Serial.println("Spray OK");
  Serial.println("================================================");
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  pinMode(dpin, OUTPUT);

  //  pinMode(stepPin, OUTPUT);
  //  pinMode(dirPin, OUTPUT);
}

void loop()
{
  /*
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
    }
    delay(1000); // One second delay

    digitalWrite(dirPin,LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < 400; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
    }
    delay(1000);
  */

  if (RFID())//當RFID感測到
  {
    /*
      步進馬達轉動
      檢查是否碰到人
      量測體溫
      啟動繼電器噴灑酒精
      到底
      關閉繼電器
      打開子外燈
      上升
      回到最上面
      關閉紫外燈
    */

    int i = 0;//紀錄步數
    while (true)
    {
      Step_motor(true);//步進馬達下降
      i++;
      if (Measurement() <= 4)//感測到人
      {
        Serial.println("Y");
        Serial.println(Temperature());//顯示量測到的溫度在監控視窗
        Serial.println(Measurement());//顯示距離在監控視窗
        OLED("sunmin", Temperature());//用OLED顯示溫度
        display.clearDisplay();
        Spray(true);//繼電器開啟
        while (true)
        {
          Step_motor(true);
          i++;
          if (i >= 1000)//如果到底了
          {
            Spray(false);//關閉繼電器
            break;
          }
        }
        Ultraviolet_rays(true);//ws2812開啟
        for (int j = 0; j < i; j++) //步進馬達上升
        {
          Step_motor(false);
        }
        Ultraviolet_rays(false);//關閉ws2812
        break;
      }
    }
  }
  else
    Serial.println("N");
  delay(500);
}
//RFID  RST:5 SDA:53 MOSI:51 MISO:50 SCK:52  id[0]: C0 id[1]: BA id[2]: 91 id[3]: 75
bool RFID()
{
  bool ch = false;
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("OO");
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    int idSize = mfrc522.uid.size;   // 取得UID的長度
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    for (int i = 0; i < idSize; i++)
    { // 逐一檢查UID碼
      if (id[i] == chack[i]){
        ch = true;
      }
      else
      {
        ch = false;
        break;
      }
    }
    mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
  }
  return ch;
}
//步進馬達
void Step_motor(bool R_L)
{
    if (R_L)
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
//紅外線測距
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
void OLED(char Name[10], int C)
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
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, strip.Color(100, 5, 100));       //  Set pixel's color (in RAM)
    }
    strip.show();
  }
  else
  {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, strip.Color(0, 0, 0));     //  Set pixel's color (in RAM)
    }
    strip.show();
  }
}
