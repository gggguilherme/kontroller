#include <LiquidCrystal.h>
#include <Arduino.h>

class Display
{
  public:
    Display(int rs, int en, int d4, int d5, int d6, int d7, unsigned short int width, unsigned short int height);
    void _loop();
    void _init();
    void show_scrolling_message(String message, int row, int _delay);
  private:              
    unsigned short int width, height;
    LiquidCrystal *lcd;
    void flashscreen();
    
    int scrollMsgRow, scrollMsgCollum, scrollMsgIndex, scrollMsgDelay;
    bool showingScrollMsg;
    String showScrollMsg;
    String scrollMsg;
    
    void erase(int x, int y);
};
