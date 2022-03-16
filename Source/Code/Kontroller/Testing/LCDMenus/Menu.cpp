#include "Menu.h"

Menu::Menu(LiquidCrystal &lcd, Screen &startScreen)
  : lcd(lcd)
{
  addScreen(startScreen);
}

void Menu::_update(bool _clear)
{
  screens[currentScreenIndex]->_update(lcd, _clear);
}

void Menu::addScreen(Screen &new_screen)
{
  if (screen_count > _MAX_SCREENS)
    return;
  screens[screen_count] = &new_screen;
  screen_count++;   
}


void Menu::nextScreen()
{
  if(currentScreenIndex >= screen_count)
    return;
  currentScreenIndex++;
}


void Menu::previousScreen()
{
  if(currentScreenIndex <= 0)
    return;
  currentScreenIndex--;
}

void Menu::cycleSelect(bool left)
{
  screens[currentScreenIndex]->cycleSelect(lcd, left); 
}

void Menu::callFunction()
{
  screens[currentScreenIndex]->callFunction();
}


Line& Menu::getSelectedLine()
{
  return screens[currentScreenIndex]->getSelectedLine();
}
