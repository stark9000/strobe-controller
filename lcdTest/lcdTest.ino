#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LCD Test");
  delay(1000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(2, 0);
  lcd.print("strobe controller");
}
