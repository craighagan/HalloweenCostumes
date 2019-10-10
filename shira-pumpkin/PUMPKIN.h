/*
  PUMPKIN.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/
#ifndef PUMPKIN_h
#define PUMPKIN_h

#include "Arduino.h"
#include "LED.h"
#include "DFRobotDFPlayerMini.h"


#define GLOW_RATE 3

class PUMPKIN {
  public:
    PUMPKIN(LED leds[], int nr_leds, DFRobotDFPlayerMini *mp3);
    void start();
    void strobe_up();
    void strobe_down();
    void glow_up();
    void glow_down();
    void blink_all(int nr_times);
    void glow_all();
    void glow_purple();
    void glow_orange();
    void shira_morse();
    void alternate(int nr_times, int blink_delay);
    void alternate_color(int middle_led, int nr_times, int blink_delay);
    void all_on();
    void play_sound();
    void test();

    void play_first();
    void set_volume();
  private:
    LED *_leds;
    int _nr_leds;
    DFRobotDFPlayerMini *_mp3;
};

#endif
