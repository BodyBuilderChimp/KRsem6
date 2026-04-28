#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial Line(2, 3); // Медный канал
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int LED_SYNC = 5;
const int LED_CALL = 6;

void setup() {
  Line.begin(9600);
  lcd.init();
  lcd.backlight();
  
  pinMode(LED_SYNC, OUTPUT);
  pinMode(LED_CALL, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Druzhinin I.A.");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Заполнение буфера
  if (Line.available() >= 4) {
    if (Line.read() == 0xAF) { // Синхробайт
      byte b1 = Line.read();
      byte b2 = Line.read();
      byte d = Line.read();

      // LCD
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
      
      // Светодиод, отображающий принятие кадра
      digitalWrite(5, !digitalRead(5)); 
    }
  }
}
