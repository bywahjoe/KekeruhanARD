//LCD I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Pin
#define sensor_kekeruhan A1

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);

  //LCD Start
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  //LCD Run
  lcd.setCursor(0, 0);
  lcd.print("V. Sensor: ");
  lcd.print(getKekeruhan());

  lcd.setCursor(0, 1);
  lcd.print("V. Analog: ");
  lcd.print(analogRead(sensor_kekeruhan));
  delay(2000);
  lcd.clear();
}
int getKekeruhan() {
  //Formula
  float volt;
  float ntu;
  float val;

  val = 0;
  for (int i = 0; i < 800; i++)
  {
    val += ((float)analogRead(sensor_kekeruhan) / 1023) * 5;
  };
  val = val / 800;
  volt = roundf((val * 10.0f) / 10.0f);

  if (volt < 2.5) ntu = 3000;
  else ntu = -1120.4 * square(volt) + 5742.3 * volt - 4353.8;
  return ntu;
}
