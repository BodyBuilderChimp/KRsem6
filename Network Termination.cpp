#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial Line(2, 3);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Line.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(5, 1);
  pinMode(6, 1); 
}

void loop() {
  // Ожидаем заполнения буфера
  if (Line.available() >= 4) {
    if (Line.read() == 0xAF) { // Синхробайт 0xAF
      byte b1 = Line.read();
      byte b2 = Line.read();
      byte d = Line.read();

      // Отображение данных на LCD
      lcd.setCursor(0, 0);
      lcd.print("B1:"); lcd.print(b1); 
      lcd.print(" B2:"); lcd.print(b2); lcd.print("cm   ");
      
      lcd.setCursor(0, 1);
      if(d == 1) {
        lcd.print("D: CALL ACTIVE");
        digitalWrite(6, 1);
      } else {
        lcd.print("D: IDLE        ");
        digitalWrite(6, 0);
      }
      
      // Индикация приёма кадра
      digitalWrite(5, !digitalRead(5)); 
    }
  }
}