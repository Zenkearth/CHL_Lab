#include "C:\Users\Kearth\Documents\Arduino\libraries\Mylib\Mylib.h"
String _pattern = "-", _direction = "-";
void setup() {
  setupPin(4);
  Serial.begin(9600);
  Serial.println("Input command: ");
}
void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readString();
    Serial.println("=> " + inputString);
    if (inputString.substring(8, 14) == "circle")  //pattern=circle
      _pattern = "circle";
    if (inputString.substring(8, 16) == "infinity")  //pattern=infinity
      _pattern = "infinity";
    if (inputString.substring(10, 12) == "cw")  //direction=cw
      _direction = "cw";
    if (inputString.substring(10, 13) == "ccw")  //direction=ccw
      _direction = "ccw";
    Serial.print("pattern = " + String(_pattern));
    Serial.println(", direction = " + String(_direction));
  }
  My7Seg(_pattern, _direction);
}