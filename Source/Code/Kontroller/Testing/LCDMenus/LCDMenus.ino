#include "Menu.h"

//Starting LiquidCrystal
const int rs = 15, en = 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd1(rs, en, d4, d5, d6, d7);

const int _rs = 16, _en = 17, _d4 = 18, _d5 = 19, _d6 = 20, _d7 = 21;
LiquidCrystal lcd2(_rs, _en, _d4, _d5, _d6, _d7);

//Starting all the interface

String some_var = "yaaaaays";
int i_var = 4;

Line welcomeLine1(0, 0, "Kontroller :)");
Line welcomeLine2(0, 1, "Kerbal Space Program");
Line welcomeLine3(0, 2, "Starting...");
Line welcomeLine4(0, 3, "made in 2022 by @g");
Screen welcomeScreen(welcomeLine1);

Line varLine(0, 0, "VAR:", &some_var);
Line someLine1(0, 1, "how does it feel?");
Line someLine2(0, 2, "YY");
Screen varScreen(varLine);


Menu menu(lcd1, welcomeScreen);

//kRPC starting



//various varying variables

int _millis = millis();
int __millis = millis();
int b___millis = millis();

bool r_released;
bool l_released;
int r_hold;
int l_hold;

const int r_Pin = 8;
const int l_Pin = 9;

// Line functions for interactions

void foo()
{
  i_var += 43;
}

void setup() {
  Serial.begin(9600);
  
  lcd1.begin(20, 4);
  lcd1.cursor();

  // adding lines and screens to the menu

  welcomeScreen.addLine(welcomeLine2);
  welcomeScreen.addLine(welcomeLine3);
  welcomeScreen.addLine(welcomeLine4);

  menu.addScreen(varScreen);

  // boot welcome screen

  menu._update();
  delay(2000);
  menu.nextScreen();
}

void loop() {
  
  if (millis() - _millis > 1000)
  {
    menu._update();
    _millis = millis();
  }
  
  if (millis() - __millis > 5000)
  {
    __millis = millis();
  }

  if(digitalRead(r_Pin) && !digitalRead(l_Pin))
  {
    r_hold = millis() - b___millis;
  }
  else if(digitalRead(l_Pin) && !digitalRead(r_Pin))
  {
    l_hold = millis() - b___millis;
  }
  else
  {
    b___millis = millis();
  }

  i_var = r_hold;
  some_var = String(i_var);
  
} 
