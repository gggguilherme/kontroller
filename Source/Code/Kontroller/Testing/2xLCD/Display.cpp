#include "Display.h"

unsigned int last_millis = 0;

Display::Display(int rs, int en, int d4, int d5, int d6, int d7, unsigned short int width, unsigned short int height)
{
  lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
  lcd->begin(width, height);
  this->width = width;
  this->height = height;
}

void Display::_init()
{
  this->lcd->setCursor(0, height-1);
  this->lcd->print("flashscreen");
  this->flashscreen();
}

void Display::_loop()
{
  if(showingScrollMsg && millis() - last_millis > scrollMsgDelay)
  {
    showScrollMsg = scrollMsg.substring(0, scrollMsgIndex);
    lcd->setCursor(scrollMsgCollum, scrollMsgRow);
    if (scrollMsgCollum < 0)
    {
      scrollMsg.remove(1,1);
      showScrollMsg.remove(1,1);
      lcd->setCursor(0, scrollMsgRow);
    }
    if(scrollMsgIndex > scrollMsg.length());
    {
      showingScrollMsg = false;
      lcd->setCursor(0, 2);
      lcd->print("finished");
      return;
    }
    lcd->print(showScrollMsg);
    scrollMsgCollum--;
    scrollMsgIndex++;
    last_millis = millis();
  }
}

void Display::flashscreen()
{
  this->show_scrolling_message("Kontroller - Kerbal Space Program - Starting . . .", 0, 150);
}

void Display::show_scrolling_message(String message, int row, int _delay)
{
   this->scrollMsg = message;
   this->scrollMsgRow = row;  
   this->scrollMsgDelay = _delay;
   this->scrollMsgCollum = width;
   this->showingScrollMsg = true;
}
