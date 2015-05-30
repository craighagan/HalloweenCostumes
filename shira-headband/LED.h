/*
  LED.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/
#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
  public:
    LED(int pin);
    void dot();
    void dash();
    void on();
    void off();
    void blink(int time);
    void glow(int time);
    void choose();
  private:
    int _pin;
};

#endif
