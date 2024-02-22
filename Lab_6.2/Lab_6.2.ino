#include "C:\Users\Kearth\Documents\Arduino\test\LED7SEG\LED7SEG.h"
int incom[3] = { 0, 0, 0 };
int num[3] = { 0, 0, 0 } ;
int cnt = 0;
void setup() {
  setPortSegments();
  Serial.begin(9600);
  Serial.println("Input number & Enter");
}
void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == 13) {
      num[0] = incom[0];
      num[1] = incom[1];
      num[2] = incom[2];
      cnt = 0;
      Serial.print("\rLED 7 Segments Display :");
      Serial.print(num[0], DEC);
      Serial.print(num[1], DEC);
      Serial.println(num[2], DEC);
      Serial.println("------------------------------");
      Serial.println("Input number & Enter");
    } else {
      incom[cnt++] = int(ch - '0');
      if (cnt > 2) cnt = 0;
    }
  } else {
    DisplayNum(pin_seg[0], num[0]);
    DisplayNum(pin_seg[1], num[1]);
    DisplayNum(pin_seg[2], num[2]);
  }
}