//這個UNO 雙搖桿 及藍牙操作 程式 ， 由 維貿企業社 設計
//除了我們的買家 自我學習使用外，請勿複製分享給他人
//手控操作與藍牙APP    可同時操作， 不用切換
#include <Servo.h>
#include  <SoftwareSerial.h>
#include <Wire.h>//引用二個函式庫SoftwareSerial及Wire
const int ServoNumber = 4;    // 總共4顆伺服馬達
const int joystickGAP = 100;  // 搖桿中間值會左右漂移的間隙，搖桿讀取值 大於100才開始驅動馬達
const int servoSTOP_IdleTimes = 100;  // 搖桿未使用狀態計數器 達100次迴圈後 將馬達斷線
const int LED_JoysticBoard = 3;   // UNO搖桿板內建的LED紅光 接在 pin 3 腳位，可作為 狀態燈號
const int L_SW_JoysticBoard = 2;  //這是 Arduino內建的上拉電阻 的腳位  D2，D4  ，就不用拉電阻線路到+5V腳位
const int R_SW_JoysticBoard = 4;  //UNO搖桿板的Switch腳位： 內建線路 左搖桿按鍵= D2 ；  右搖桿按鍵=D4
int idleCounter[ServoNumber];       // 計數器：分別記錄4個馬達沒有動作 迴圈次數計數器
int motor_speed = 10; //  伺服馬達 移動的速度  （20= 正常，  小於5 就太快了）
char BTdata = '9'; //藍牙 接收到的資料 存放的字元變數 '9'=開機後進入待機狀態

SoftwareSerial BTSerial(12, 13); // 因為UNO雙搖桿板 已經設定通訊GPIO  RX = 12 / TX =13 ，Serial(RX,TX)
Servo myservo[ServoNumber];          // 宣告 操控 4台Servo motor

//// UNOR3雙搖桿控制板的腳位 說明
//**搖桿扳動方向 讀取的數據 X軸 往左邊=0  中間=512  往右邊=1023 *************//
//                          Y軸 往上邊=0  中間=512  往下邊=1023 ***********
// 搖桿的 UNO腳位 ：  左桿 X軸= A0 ，Y軸=A1  / 右桿 X軸= A3， Y軸=A2
//  pinMode(2,INPUT_PULLUP);  //Arduino  內建有上拉電阻的 UNO腳位  D2，D4
//  pinMode(4,INPUT_PULLUP);  //所以搖桿的Switch UNO腳位就是  左搖桿= D2 /  右搖桿=D4
// 搖桿板的LED燈： 接   UNO  D3 腳位

//伺服馬達初始角度 = {底座,上下,伸長,夾子} base/left/right meArm
int initialAngle[ServoNumber] = { 85 , 100 , 40 , 85};

// 機械手臂 搖桿及伺服馬達的初始設定, 一行 設定一顆馬達的參數
// 參數依序為 : joystickPin, servoPin, min, max, initialAngle
//  joystickPin : 分別指定 搖桿X,Y軸 連接Arduino UNO的analog腳位(用 0~3 代表 A0~A3)
//  servoPin : 分別指定 伺服馬達(橙/黃/棕 杜邦線)接在 UNO板的腳位
//  min : 伺服馬達最小的角度
//  max : 伺服馬達最大的角度
int servoConfig[ServoNumber][4] = {
  // joystickPin,servoPin, min,  max
  { 0,      11,     0,   179 }, //A0 = L.X ,  Buttom  旋轉底座
  { 1,      10,    60,   179 }, //A1 = L.Y ,  Left  讓爪子夾座 上升或下降
  { 2,       9,    10,   130 }, //A2 = R.Y ,  Right 讓爪子夾座  伸長 或 縮回
  { 3,       5,    55,   179 }, //A3 = R.X ,  Front (claw) 讓夾子 加緊 或 放開
};

// 初始化的程序 setup()，也就是 開機後 只有執行  一次，不再迴圈重複執行
void setup()
{
  Serial.begin(9600);   //開啟 序列埠 視窗 輸出  程式偵錯用的，可以設定要 觀察程式的參數
  BTSerial.begin(9600); // 開啟 藍牙功能
  pinMode(LED_JoysticBoard, OUTPUT);          // 設定顯示狀態用的 LED 接腳 Pin3
  digitalWrite(LED_JoysticBoard, HIGH);         // 點亮UNO搖桿板上的 紅色LED
  pinMode(L_SW_JoysticBoard, INPUT_PULLUP); //D2  //這是Arduino內建上拉電阻的腳位D2，D4  ，宣告：INPUT_PULLUP  很重要******
  pinMode(R_SW_JoysticBoard, INPUT_PULLUP); //D4  //UNO搖桿板的Switch腳位：左搖桿按鍵= D2；右搖桿按鍵=D4，就不用拉電阻線路到+5V腳位
}   //end setup

// 主程式 （迴圈重覆執行程序）
void loop()
{
  int chk, i, j;
  if (BTSerial.available())   //藍牙讀取資料
  {
    BTdata = BTSerial.read();
    //Serial.print("讀取手機的藍牙指令:   ");
    //Serial.println(BTdata);
  }
  if (BTdata != '0' )
  {
    digitalWrite(LED_JoysticBoard, HIGH);
  }
  else
  {
    digitalWrite(LED_JoysticBoard, LOW);
  }

  // 控制馬達斷電的計數器 每次迴圈計一次 分馬達編號依序 累計儲存， 超過設定servoSTOP_IdleTimes 100次後,切斷 該馬達的連線
  //因為  SG90伺服馬達 長時間開機 UNO的 Analog GPIO輸出電壓值 很不穩定，會讓馬達訊號誤判 馬達就無故 “抖動”
  // 所以  沒有用的的馬達  ，一定時間 就讓 該顆馬達 斷開GPIO的連線，也就是停掉 GPIO的訊號
  for (int k = 0; k < 4; k++)
  {
    idleCounter[k]++;      // 將關閉馬達電源的計數器 加 1
    if (idleCounter[k] > servoSTOP_IdleTimes) // 計數器 超過設定servoSTOP_IdleTimes 100次後,切斷 該馬達的連線
    {
      idleCounter[k] = 0;     // 計數器歸零
      myservo[k].detach();    // 切斷馬達的連線
      Serial.print(k);
      Serial.println("號舵機 已經關閉");
    }
  } //ending of  for k=0

  // 搖桿的 UNO腳位 ：  A0=左桿 X軸=藍牙L/R ，A1=Y軸=藍牙U/D
  //                    A3=右桿 X軸=藍牙1/2， A2=Y軸=藍牙3/4
  //**搖桿扳動方向 讀取的數據 X軸 往左邊=0  中間=512  往右邊=1023 *************//
  //                          Y軸 往上邊=0  中間=512  往下邊=1023 ***********

  switch (BTdata)
  {
    case 'L': i = 0; j = 1 ; break;
    case 'R': i = 0; j = -1; break;
    case 'U': i = 1; j = 1 ; break;
    case 'D': i = 1; j = -1 ; break;
    case '1': i = 3; j = 1 ; break;
    case '2': i = 3; j = -1 ; break;
    case '3': i = 2; j = -1 ; break;
    case '4': i = 2; j = 1 ; break;
    case 'A': i = 3; j = 2 ; break;   //進入 UNO搖桿板 的雙搖桿操控  記憶模式
    case 'B': i = 3; j = 3; break;   //結束 執行記憶模式 並存儲資料
    case '0': i = 9; break; // 手機藍牙APP 沒有操作按鍵時， 讓BTdata='0' ：進入手控模式 用搖桿板的雙搖桿操控
    //手機藍牙APP 開啟後 當操作按鍵時， 讓BTdata  改變：立即介入 轉為藍牙操控
    default: i = 9 ; move_motor(9);  BTdata = '0'; //開機後 馬達轉動到初始角度，然後進入手動或藍牙操控模式
  }

  if (i == 9)
  {
    Joystic();  //進入手控 UNO搖桿板雙搖桿操控模式
  }
  else
  {
    BT(i, j); //進入 藍牙操作副程式
  }

}    // end  of  loop() **********

//////// 開機後 讓機械手臂4個伺服馬達轉動到指定的角度//////
void move_motor(int v) {
  int outputPin, angleMin, angleMax, angleInit;
  int servo_angle[ServoNumber];
  Serial.print("V: "); Serial.print(v);
  //讀取角度參數  然後驅動馬達轉動到指定的角度
  for (int i = 0; i < ServoNumber; i++)
  {
    outputPin = servoConfig[i][1]; // 循序取得4個馬達 連接到Arduino Analog GPIO的接腳號碼
    myservo[i].attach(outputPin);  // 將 對應號碼 的馬達 連線 到指定 GPIO 控制腳
    switch (v)
    {
      case 9:
        angleInit = initialAngle[i]; //開機後的 讓4個伺服馬達 轉動到指定的 起始位置
        break;
      case 8:
        angleInit =  servo_angle[i];  // 由設定取得角度數據，作為驅動馬達角度的參數
        break;  //  準備給 執行記憶的動作
    }
    myservo[i].write(angleInit);

    idleCounter[i] = 0;     // 將搖桿未使用記數器歸零 ，這個數值到100 就切斷 馬達的電力
  }  // end for

}  // ending  of initialmotor() 副程式 結束


//////////////藍牙控制 副程式 /////////////////////////
void BT(int i, int j) {
  if ( j == 2 && motor_speed < 80)   {
    motor_speed++ ;
    Serial.print("速度  變慢了 參數=") ;  Serial.print(motor_speed); return;
  } // 調慢
  if ( j == 3 && motor_speed > 3)    {
    motor_speed--;
    Serial.print("速度  變快 快   參數=");  Serial.println(motor_speed); return;
  } // 調快

  int inputValue, currentAngle, joyStickOffset, angleOffset;
  int inputPin, outputPin, angleMin, angleMax, temp;

  currentAngle = myservo[i].read();   // 取得馬達目前的角度(0-90度）

  // 搖桿的 UNO腳位 ：  左桿 X軸= A0 ，Y軸=A1  / 右桿 X軸= A3， Y軸=A2
  inputPin   = servoConfig[i][0];  // 由設定取得搖桿輸入給 Arduino 的接腳參數
  outputPin  = servoConfig[i][1]; // 由設定取得馬達在 Arduino 的接腳參數
  angleMin   = servoConfig[i][2]; // 由設定取得馬達最小角度的參數
  angleMax   = servoConfig[i][3]; // 由設定取得馬達最大角度的參數

  currentAngle += j;   //命令馬達 轉動的角度

  // 如果命令馬達轉動角度 在最小角度參數 和 最大角度參數之間，不符合=馬達不執行馬達驅動改變角度的程序
  if (currentAngle > angleMin && currentAngle < angleMax)
  {
    idleCounter[i] = 0;  //將目前轉動的馬達 關閉電的計數器歸零
    if (!myservo[i].attached())   // 如果馬達未連線, 先行連線
    {
      myservo[i].attach(outputPin);
    }

    if (myservo[i].attached()) // 如果馬達已連線, 將再 轉動 1度 ，因為 j= 1度 )
    {
      myservo[i].write(currentAngle);     // 驅動 對應的 馬達 轉動角度
    }
  }
  delay(motor_speed);        // 暫停多少MS 再進入迴圈（延長迴圈的時間） = 角度移動的速度
} // ending  of  BT()


///////// UNO搖桿板的  雙搖桿操控//////
void Joystic() {
  int inputValue, currentAngle, joyStickOffset, angleOffset;
  int inputPin, outputPin, angleMin, angleMax, temp;
  for (int i = 0; i < ServoNumber; i++) {
    inputPin   = servoConfig[i][0];  // 由設定取得搖桿輸入給 Arduino 的接腳參數
    outputPin  = servoConfig[i][1]; // 由設定取得馬達在 Arduino 的接腳參數
    angleMin   = servoConfig[i][2]; // 由設定取得馬達最小角度的參數
    angleMax   = servoConfig[i][3]; // 由設定取得馬達最大角度的參數
    currentAngle = myservo[i].read();   // 取得馬達目前的角度(0-90度）
    // Serial.print(i); Serial.print("號舵機: "); Serial.print("  現在角度為  "); Serial.println(currentAngle);
    inputValue = analogRead(inputPin);  // 讀取搖桿的數值(0~1023)
    joyStickOffset = inputValue - 512;  // 計算 剛讀取的搖桿數據 和 搖桿未使用時的 中間值512 (1023/2=512) 的差動有多少, 用以判斷是否要 驅動馬達旋轉改變角度

    //  搖桿老化後 中間值 會稍微 左右跳動，所以設立  老化產生的間隙值  joystickGAP = 100;
    // 搖桿讀取值  距離中心點 100以上 才開始驅動馬達轉動
    // 搖桿的數值(0~1023) 中間值是512
    if (abs(joyStickOffset) > joystickGAP)
    {
      // 如果搖桿讀取值 往比 512 大的方向扳動就讓馬達角度減少, 反之則增加
      //  也就是 判斷你 扳動搖桿是先右邊  還是向左邊
      if (joyStickOffset > 0)
      {
        angleOffset = -1;
      }
      else
      {
        angleOffset = 1;
      }
      currentAngle += angleOffset;    // 計算新的馬達角度，也就是 程式執行迴圈 一次 ，讓馬達 旋轉1度

      // 如果命令馬達轉動角度 在最小角度參數 和 最大角度參數之間，不符合=馬達不執行馬達驅動改變角度的程序
      if (currentAngle > angleMin && currentAngle < angleMax)
      {
        idleCounter[i] = 0;

        // 如果馬達未連線, 先行連線
        if (!myservo[i].attached())
        {
          myservo[i].attach(outputPin);
        }

        // 如果馬達已連線, 將角度設為新的角度
        if (myservo[i].attached())
        {
          myservo[i].write(currentAngle);     // sets the servo position according to the scaled value
          digitalWrite(3, HIGH);          // 點亮UNO搖桿板上的 紅色LED
        }
      }
    }

  }
  if ( digitalRead(L_SW_JoysticBoard ) == LOW && motor_speed < 80)   {
    motor_speed++ ;
    Serial.print("速度  變慢了 參數=") ;  Serial.print(motor_speed);
  } // 調慢
  if ( digitalRead(R_SW_JoysticBoard ) == LOW && motor_speed > 3)    {
    motor_speed--;
    Serial.print("速度  變快 快   參數=");  Serial.println(motor_speed);
  } // 調快
  delay(motor_speed);        // 速度=暫停多少 MS 後繼續
}
