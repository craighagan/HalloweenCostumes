/*
  HEADBAND.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/


#include "Arduino.h"
#include "HEADBAND.h"
#include "Sleep.h"

HEADBAND::HEADBAND(LED leds[], int nr_leds) {
  _leds = leds;
  _nr_leds = nr_leds;
}

void HEADBAND::strobe_up() {
  int i;
  for(i=0;i<_nr_leds;i++) {
     _leds[i].blink(100);
     do_sleep(10); 
  }
}

void HEADBAND::strobe_down() {
  int i;
  for(i=_nr_leds-1;i>=0;i--) {
     _leds[i].blink(100);
     do_sleep(10);
  }  
}

void HEADBAND::start() {
  int led;
  int action = random(3);
  switch(action) {
    case 0:
      // strobe up
      strobe_up();
      break;
    case 1:
      // strobe down
      strobe_down();
      break;
    case 2:
      led = random(_nr_leds);
      _leds[led].choose();
      break;
  }
}
