#include <SoftwareSerial.h>

SoftwareSerial LineOut(2, 3); 

const int POT_PIN = A0;      // Потенциометр (B1)
const int TRIG_PIN = 7;      // Дальномер (B2) Trig
const int ECHO_PIN = 8;      // Дальномер (B2) Echo
const int BUTTON_PIN = 4;    // Кнопка (D)

void setup() {
  Serial.begin(9600);
  LineOut.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // B1
  byte b1_data = map(analogRead(POT_PIN), 0, 1023, 0, 255);

  // B2
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  byte b2_data = constrain(duration * 0.034 / 2, 0, 255);

  // D
  byte d_data = (digitalRead(BUTTON_PIN) == 1) ? 1 : 0;

  // TDM
  byte frame[4];
  frame[0] = 0xAF;    // Синхробайт
  frame[1] = b1_data;
  frame[2] = b2_data;
  frame[3] = d_data;

  // Отправка кадра
  LineOut.write(frame, 4);

  // В контроль для проверки
  Serial.print("Sent: B1="); Serial.print(b1_data);
  Serial.print(" B2="); Serial.print(b2_data);
  Serial.print(" D="); Serial.println(d_data);

  delay(100); // Кадр отправляется 10 раз в секунду
}
