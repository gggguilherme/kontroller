#include <LiquidCrystal.h>
#include <Arduino.h>

#define _MAX_SCREENS 16

class Line
{
  public:
    /*
    void attachFunction(void (*function)(void));
    */
    Line(int row, int collum, String line, String &var);
    
  protected:
    void _update(LiquidCrystal &lcd);
    void callFunction();
  private:
    friend class Screen;
    String line, varUnit;
    String &var;
    bool selected;
    int row, collum;
    void (*_function)(void);
};

class Screen
{
  public:
    //different constructors for line quantity
    Screen(Line line);

  private:
    friend class Menu;
    Line* lines[4];
    int selectedLineIndex = -1;
    int line_count = 0;
  public:
    void addLine(Line new_line);
  protected:
    Line getSelectedLine();
    void _update(LiquidCrystal &lcd, bool _clear);
};

class Menu
{
  private:
    Screen *screens[_MAX_SCREENS];
    int currentScreenIndex = 0;
    LiquidCrystal &lcd;
    int screen_count;
  public:
    Menu(LiquidCrystal &lcd, Screen startScreen);
    void _update(bool _clear = true);
    void addScreen(Screen new_screen);
    void nextScreen();
    void previousScreen();
    void cycleSelect(bool left);
    void callFunction();
    
};
