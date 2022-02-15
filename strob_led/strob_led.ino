#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <PWM.h>

byte STROB_LIGHT = 9;
volatile int FREQUENCY = 1;
volatile int MAX_FREQUENCY = 100;
byte POTENTIOMETER_PIN = A0;

void setup()
{
  Serial.begin(9600);
  InitTimersSafe();
  bool success = SetPinFrequencySafe(STROB_LIGHT, FREQUENCY);
  if (success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
  }
  pinMode(POTENTIOMETER_PIN, INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     Strobe");
  lcd.setCursor(0, 1);
  lcd.print("   Controller");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Strobe Frequency");
  lcd.setCursor(6, 1);
  FREQUENCY = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 1, MAX_FREQUENCY);
  lcd.print(String(FREQUENCY) + String("Hz"));
}

void loop()
{
  FREQUENCY = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 1, MAX_FREQUENCY);
  SetPinFrequencySafe(STROB_LIGHT, FREQUENCY);
  pwmWrite(STROB_LIGHT, 200);

  lcd.setCursor(6, 1);
  lcd.print(String(FREQUENCY) + String("Hz"));
  if (FREQUENCY < 10) {
    for (int LCD_SECOND_ROW = 0; LCD_SECOND_ROW < 16; LCD_SECOND_ROW++) {
      lcd.print(" ");
    }
  }
  delay(300);
}
