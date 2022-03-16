#include "Menu.h"

Screen::Screen(Line &line)
{
  addLine(line);
}

void Screen::addLine(Line &new_line)
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

Line& Screen::getSelectedLine()
{
  return *lines[selectedLineIndex];
}

void Screen::callFunction()
{
  getSelectedLine().callFunction();
}

void Screen::cycleSelect(LiquidCrystal &lcd, bool left)
{
  if(left)
  {
    this->selectedLineIndex--;
    if(this->selectedLineIndex < 0)
    {
      this->selectedLineIndex = this->line_count-1;
    }
  }
  else
  {
    this->selectedLineIndex++;
    if(this->selectedLineIndex > this->line_count-1)
    {
      this->selectedLineIndex = 0;
    }
  }

  Line line = this->getSelectedLine();
  lcd.setCursor(line.row, line.collum);
}
