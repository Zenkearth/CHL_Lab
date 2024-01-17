#include <Arduino.h>
const char digitPins[4] = {2, 3, 4, 5};
const char segmentPins[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const char segmentInfinity[8] = {6, 7, 12, 10, 9, 8, 12, 11};
byte pin = 0;

void setupPin(byte numDigit)
{
  for (byte i = 0; i < numDigit; i++)
  {
    pinMode(digitPins[i], OUTPUT);
  }
  pin = numDigit;
  for (byte i = 0; i < sizeof(segmentPins); i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void circle(String Direction)
{
  if (Direction != "-")
  {
    for (byte seg = (Direction == "cw") ? 0 : 5; (Direction == "cw") ? seg < sizeof(segmentPins) - 2 : seg != 255; (Direction == "cw") ? seg++ : seg--)
    {
      digitalWrite(segmentPins[seg], HIGH);
      delay(150);
      digitalWrite(segmentPins[seg], LOW);
    }
  }
}

void infinity(String Direction)
{
  if (Direction != "-")
  {
    for (byte seg = (Direction == "cw") ? 0 : 7; (Direction == "cw") ? seg < sizeof(segmentInfinity) : seg != 255; (Direction == "cw") ? seg++ : seg--)
    {
      digitalWrite(segmentInfinity[seg], HIGH);
      delay(150);
      digitalWrite(segmentInfinity[seg], LOW);
    }
  }
}

void My7Seg(String Pattern, String Direction)
{
  if (Pattern == "circle")
  {
    circle(Direction);
  }
  if (Pattern == "infinity")
  {
    infinity(Direction);
  }
}