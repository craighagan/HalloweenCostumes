/*
  HEADBAND.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/
#ifndef HEADBAND_h
#define HEADBAND_h

#include "Arduino.h"
#include "LED.h"

class HEADBAND
{
  public:
    HEADBAND(LED leds[], int nr_leds);
    void start();
    void strobe_up();
    void strobe_down();
    void glow_up();
    void glow_down();
    void blink_all(int nr_times);
    void glow_all();
    void shira_morse();
    void alternate(int nr_times);
    void all_on();
  private:
    LED *_leds;
    int _nr_leds;
};

#endif
