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

void Display::flashscreen()
{
  this->show_scrolling_message("Kontroller - Kerbal Space Program - Starting . . . ", 0, 50);
}

void Display::_loop()
{
  show_scrolling_message_loop();
}

void Display::show_scrolling_message_loop()
{
  if(showingScrollMsg && millis() - last_millis > scrollMsgDelay)
  {
    if (scrollMsgCollum == scrollMsg.length())
    {
      showingScrollMsg = false;
      return;
    }
    scrollMsgCollum --;
      int position_x = max(scrollMsgCollum, 0);
    int position_y = scrollMsgRow;
    scrollMsgIndex = min(scrollMsgIndex+1, scrollMsg.length());
    int startingStringIndex = 0;
    if(position_x == 0)
    {
      startingStringIndex = -scrollMsgCollum;
    }
    String showString = scrollMsg.substring(startingStringIndex, scrollMsgIndex);
    lcd->setCursor(position_x, position_y);
    lcd->print(showString);
    last_millis = millis();
  }
}


void Display::show_scrolling_message(String message, int row, int _delay)
{
   this->scrollMsg = message;
   this->scrollMsgRow = row;  
   this->scrollMsgDelay = _delay;
   this->scrollMsgCollum = width;
   this->showingScrollMsg = true;
   this->scrollMsgIndex = 0;
}
