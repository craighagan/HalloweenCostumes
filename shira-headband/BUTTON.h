/*
  BUTTON.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/
#ifndef BUTTON_h
#define BUTTON_h

#include "Arduino.h"

#define DEBOUNCE_DELAY 50

class BUTTON
{
  public:
    BUTTON(int pin);
    boolean pressed();
    boolean debounce_pressed();
  private:
    int _pin;
    int _last_state;
    int _state;
    long _last_debounce_time;
};

#endif
