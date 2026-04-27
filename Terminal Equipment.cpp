const int POT_PIN = A0;      // Потенциометр (B1)
const int TRIG_PIN = 9;      // УЗ-датчик - Trig (B2)
const int ECHO_PIN = 10;     // УЗ-датчик - Echo (B2)
const int BUTTON_PIN = 2;    // Кнопка сигнализации (D)

void setup() {
  Serial.begin(9600);        // Скорость ISDN
  pinMode(TRIG_PIN, 1);
  pinMode(ECHO_PIN, 0);
  pinMode(BUTTON_PIN, 2);
}

void loop() {
  // Канал B1
  byte b1_data = map(analogRead(POT_PIN), 0, 1023, 0, 255); [cite: 54]

  // Канал B2
  digitalWrite(TRIG_PIN, 0);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, 1);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, 0);
  long duration = pulseIn(ECHO_PIN, 1);
  byte b2_data = constrain(duration * 0.034 / 2, 0, 255); 

  // Канал D
  byte d_data = (digitalRead(BUTTON_PIN) == 0) ? 1 : 0; 

  // Формирование и отправка TDM-кадра
  byte frame[4];
  frame[0] = 0xAF;    // Маркер синхронизации
  frame[1] = b1_data; // Оцифрованный "голос" (B1)
  frame[2] = b2_data; // Телеметрия (B2)
  frame[3] = d_data;  // Сигнализация (D)

  Serial.write(frame, 4); // Отправка пакета в линию
  
  delay(100); // Частота обновления кадра
}