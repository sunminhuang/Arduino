#include <DFRobot_LD3320.h>

DFRobot_LD3320 ld3320;

void setup() {
  Serial.begin(9600);
  ld3320.begin();
}

void loop() {
  if (ld3320.available()) {
    String result = ld3320.read();
    Serial.println(result);
  }
}
