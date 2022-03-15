#include "Menu.h"


Line::Line(int row, int collum, String line, String &var)
: var(var)
{
    this->row = row;
    this->collum = collum;
    this->line = line;
}

void Line::_update(LiquidCrystal &lcd)
{
  lcd.setCursor(this->row, this->collum);
  lcd.print(String(this->line + this->var + this->varUnit));
}

/*
void Line::callFunction()
{
  this->_function();
}

void Line::attachFunction(void (*function)(void))
{
  this->_function = function;
}
*/
