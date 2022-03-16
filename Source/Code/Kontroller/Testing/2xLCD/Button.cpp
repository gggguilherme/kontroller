#include "Button.h"

Button::Button(int Pin)
{
  this->Pin = Pin;
  this->_init();
}

void Button::_init()
{
  pinMode(Pin, INPUT);
}

bool Button::pressed()
{
  return digitalRead(Pin);
}
