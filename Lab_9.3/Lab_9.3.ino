#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // กำหนดค่าสำหรับ LCD
const int EEPROMAddress = 0; // ที่อยู่เริ่มต้นใน EEPROM สำหรับเก็บ IP address

String ipAddress = ""; // สตริงเพื่อเก็บ IP address ที่จะแสดงบน LCD

void setup() {
  Serial.begin(9600); // เริ่มการสื่อสารผ่าน Serial ที่ baud rate 9600
  lcd.begin(); // เริ่มใช้งาน LCD
  lcd.backlight(); // เปิดไฟหลัง LCD
  lcd.setCursor(0,0);
  lcd.print("IP Address:");

  // อ่านและแสดง IP address จาก EEPROM หากมี
  displayIPAddressFromEEPROM();
}

void loop() {
  if (Serial.available() > 0) {
    // รอรับสตริงจาก Serial Monitor
    ipAddress = Serial.readStringUntil('\n');
    ipAddress.trim(); // ลบ whitespace ที่ไม่จำเป็น
    if (ipAddress.length() > 0) {
      // แปลงและเขียน IP address ไปยัง EEPROM
      writeIPAddressToEEPROM(ipAddress);
      // แสดง IP address บน LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("IP Address:");
      lcd.setCursor(0,1);
      lcd.print(ipAddress);
    }
  }
}

void writeIPAddressToEEPROM(String ip) {
  int parts[4] = {0}; // สำหรับเก็บส่วนต่างๆ ของ IP address
  if (sscanf(ip.c_str(), "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]) == 4) {
    for (int i = 0; i < 4; i++) {
      EEPROM.write(EEPROMAddress + i, parts[i]);
    }
  }
}

void displayIPAddressFromEEPROM() {
  String storedIPAddress = "";
  for (int i = 0; i < 4; i++) {
    int value = EEPROM.read(EEPROMAddress + i);
    if (i > 0) storedIPAddress += ".";
    storedIPAddress += String(value);
  }
  if (storedIPAddress.length() > 7) { // ตรวจสอบว่า IP address ดูเหมือนจะถูกต้อง
    lcd.setCursor(0,1);
    lcd.print(storedIPAddress);
    ipAddress = storedIPAddress; // อัปเดต IP address ปัจจุบัน
  }
}
