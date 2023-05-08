#include "BluetoothSerial.h"

BluetoothSerial myBT;

void setup() {
  Serial.begin(115200);
  myBT.begin("ESP32_BT"); //藍芽裝置名稱
}

void loop() {
  if (Serial.available()) {
    //電腦端接受資料發送到藍牙
    myBT.write(Serial.read());
  }
  if (myBT.available()) {
    //藍牙端接受資料發送到電腦
    Serial.write(myBT.read());
  }
  delay(20);
}
