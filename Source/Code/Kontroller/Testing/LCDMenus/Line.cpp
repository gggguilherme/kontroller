#include "Menu.h"


Line::Line(int row, int collum, String line, String *var)
: var(var)
{
    this->row = row;
    this->collum = collum;
    this->line = line;
}

Line::Line(int row, int collum, String line)
: var(&empty_var)
{
    this->row = row;
    this->collum = collum;
    this->line = line;
}

void Line::_update(LiquidCrystal &lcd)
{ 
  String value = *var;
  lcd.setCursor(this->row, this->collum);
  if(value == empty_var)
  {
    lcd.print(line);
    return;
  }
  lcd.print(String(line + String(value)));
}

void Line::callFunction()
{
  this->_function();
}

void Line::attachFunction(void (*function)(void))
{
  this->_function = function;
}
