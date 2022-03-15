#include "Menu.h"
const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 20, d7 = 21;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String var = "aa";

Line line(0, 0 ,"somthng", var);
Screen screen(line);
Menu menu(lcd, screen);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  menu._update(false);
  lcd.setCursor(0, 0);
  lcd.print("bruh please work");
}

void loop() {
  // put your main code here, to run repeatedly:
} 
