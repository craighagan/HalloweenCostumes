/*
  SPIDER.h - Library for flashing LED code.
  Created by Craig I. Hagan 10/25/2019
  Released into the public domain.
*/
#ifndef SPIDER_h
#define SPIDER_h

#include "Arduino.h"
#include "LED.h"
#include "DFRobotDFPlayerMini.h"
#include "NewPing.h"

#define GLOW_RATE 3

class SPIDER {
  public:
    SPIDER(LED leds[], int nr_leds, DFRobotDFPlayerMini *mp3, NewPing *sonar, int activation_distance);
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
    void play_sound(int file_nr);
    void test();
    void SPIDER::print_detail(uint8_t type, int value);
    void SPIDER::wait_sensor_activated();

    void play_first();
    void set_volume();
  private:
    LED *_leds;
    int _nr_leds;
    int _activation_distance;
    NewPing *_sonar;
    DFRobotDFPlayerMini *_mp3;
};

#endif
