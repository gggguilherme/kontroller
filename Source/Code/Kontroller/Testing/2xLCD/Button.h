#include <Arduino.h>

class Button
{
  public:
    Button(int Pin);
    bool pressed();
  private:
    void _init();
    int Pin;
};
