// Código LCD

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define LCD_SDA  20 // leitura de dados
#define LCD_SCL  21 // clock

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin (16,2);
  Serial.begin(115200);
}
void loop() {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Pablo lindo");

  lcd.setCursor(0,1);
  lcd.print("porem chato");

}
