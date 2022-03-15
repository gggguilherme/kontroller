#include "Menu.h"

Screen::Screen(Line line)
{
  addLine(line);
}

void Screen::addLine(Line new_line)
{
  this->lines[line_count] = &new_line;
  this->line_count++;
}

void Screen::_update(LiquidCrystal &lcd, bool _clear)
{
  if (_clear)
    lcd.clear();
  
  for (int i = 0; i < line_count; i ++)
  {
    this->lines[i]->_update(lcd);
  }

  lines[0]->_update(lcd);
}

Line Screen::getSelectedLine()
{
  return *lines[selectedLineIndex];
}
