#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

int TempHighTH = 50;
int TempLowTH = 5;
int HumaHighTH = 75;
int HumaLowTH = 20;

#define RedPin 11
#define YelPin 12
#define GreenPin 13
#define Buzzer 8

unsigned long previousMillis = 0;
const long interval = 100;

String inString;

DHT dht(DHTPIN, DHTTYPE);



LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.clear();
  Serial.begin(9600);
  dht.begin();
  pinMode(YelPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  setTH();
  unsigned long currentMillis = millis();
  delay(800);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("\nHumidity: ");
  Serial.print((int)h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print((int)t);
  Serial.print(" *C");
  alarm(t, h, currentMillis);
  showDHT(t, h);
}

void showDHT(int t, int h) {
  lcd.setCursor(0, 0);
  lcd.print("T: |" + (String)TempLowTH + "|" + (String)t + "|" + (String)TempHighTH + "|");
  lcd.setCursor(0, 1);
  lcd.print("H: |" + (String)HumaLowTH + "|" + (String)h + "|" + (String)HumaHighTH + "|");
}

void alarm(int t, int h, unsigned long currentMillis) {
  static boolean buzzerState = false;
  if (t >= TempHighTH || t <= TempLowTH) {
    if ((t == TempHighTH || t == TempLowTH) && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;
      if (buzzerState == false) {
        tone(Buzzer, 700);
        buzzerState = true;
      } else {
        noTone(Buzzer);
        buzzerState = false;
      }
      digitalWrite(RedPin, LOW);
      digitalWrite(GreenPin, LOW);
      digitalWrite(YelPin, HIGH);
      Serial.print("\tWarning!!! ");
      Serial.print(t >= TempHighTH ? "High" : "Low");
      Serial.print(" Temperature!! : ");
      Serial.print((String)t + " *C");
    } else {
      digitalWrite(GreenPin, LOW);
      digitalWrite(YelPin, LOW);
      digitalWrite(RedPin, HIGH);
      Serial.print("\tAlarm!!! ");
      Serial.print(t >= TempHighTH ? "High" : "Low");
      Serial.print(" Temperature!! : ");
      Serial.print((String)t + " *C");
      digitalWrite(Buzzer, 1);
    }
  } else if (h >= HumaHighTH || h <= HumaLowTH) {
    if ((h == HumaHighTH || h == HumaLowTH) && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis;
      if (buzzerState == false) {
        tone(Buzzer, 700);
        buzzerState = true;
      } else {
        noTone(Buzzer);
        buzzerState = false;
      }
      digitalWrite(RedPin, LOW);
      digitalWrite(GreenPin, LOW);
      digitalWrite(YelPin, HIGH);
      Serial.print("\tWarning!!! ");
      Serial.print(h >= HumaHighTH ? "High" : "Low");
      Serial.print(" Huminity!! : ");
      Serial.print((String)h + " %");
    } else {
      digitalWrite(GreenPin, LOW);
      digitalWrite(YelPin, LOW);
      digitalWrite(RedPin, HIGH);
      Serial.print("\tAlarm!!! ");
      Serial.print(h >= HumaHighTH ? "High" : "Low");
      Serial.print(" Huminity!! : ");
      Serial.print((String)h + " %");
      digitalWrite(Buzzer, 1);
    }
  } else {
    noTone(Buzzer);
    buzzerState = false;
    digitalWrite(YelPin, LOW);
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(Buzzer, 0);
  }
}

void setTH() {
  while (Serial.available() > 0) {
    inString = Serial.readString();
    inString.trim();
    inString.toUpperCase();
    if (inString.substring(0, 2) == "TH") {
      TempHighTH = inString.substring(2).toInt();
    }
    if (inString.substring(0, 2) == "TL") {
      TempLowTH = inString.substring(2).toInt();
    }
    if (inString.substring(0, 2) == "HH") {
      HumaHighTH = inString.substring(2).toInt();
    }
    if (inString.substring(0, 2) == "HL") {
      HumaLowTH = inString.substring(2).toInt();
    }
    inString = "";
  }
}