#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ONE_WIRE_BUS 2   // DS18B20 nối vào chân số 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int buzzer = 3;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);

  sensors.begin(); // khởi động DS18B20
}

void loop() {
  sensors.requestTemperatures();           // yêu cầu đo
  float tempC = sensors.getTempCByIndex(0); // đọc nhiệt độ từ cảm biến đầu tiên

  lcd.setCursor(0, 0);
  lcd.print("Nhiet do ");
  lcd.print(tempC);
  lcd.print("C   ");  

  if (tempC > 60) {
    tone(buzzer, 1000);
    lcd.setCursor(0, 1);
    lcd.print("Qua nong!     ");
  } else {
    noTone(buzzer);
    lcd.setCursor(0, 1);
    lcd.print("Binh thuong   ");
  }

  delay(1000);
}
