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


void HEADBAND::glow_up() {
  int i;
  for(i=0;i<_nr_leds-1;i++) {
    _leds[i].glow(100);
  } 
}

void HEADBAND::glow_down() {
  int i;
  for(i=_nr_leds-1;i>=0;i--) {
    _leds[i].glow(100);
  } 
}

void HEADBAND::glow_all() {
 int led;
 int amount;
 for(amount=0;amount<=255;amount++) {
   for(led=0;led<_nr_leds;led++) {
     _leds[led].dim(amount);
   }
   do_sleep(10);
 }
 do_sleep(100); 
 for(amount=255;amount>=0;amount--) {
   for(led=0;led<_nr_leds;led++) {
     _leds[led].dim(amount);
   }
   do_sleep(10);
 }
}

void HEADBAND::blink_all() {
  int i;
  for(i=0;i<_nr_leds;i++) {
    _leds[i].on();
  } 
  do_sleep(10);
  for(i=0;i<_nr_leds;i++) {
    _leds[i].off();
  }   
}

void HEADBAND::shira_morse() {
// shira : 
// s : ...
// h : ....
// i : ..
// r : .-.
// a : .-
  int led;
  int after_letter_delay = 128;
  int between_letter_delay = 532;

  // s
  led = random(_nr_leds);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(between_letter_delay);

  // h
  led = random(_nr_leds);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(between_letter_delay);

  // i
  led = random(_nr_leds);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(between_letter_delay);

  // r
  led = random(_nr_leds);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(between_letter_delay);

  // a
  led = random(_nr_leds);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(between_letter_delay);
  
}

void HEADBAND::start() {
  int led;
  int action = random(13);
  switch(action) {
    case 0:
    case 1:
      // strobe up
      strobe_up();
      break;
    case 2:
    case 3:
      // strobe down
      strobe_down();
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      led = random(_nr_leds);
      _leds[led].choose();
      break;
    case 8:
      glow_up();
      break;
    case 9:
      glow_down();
      break;
    case 10:
      glow_all();
      break;
    case 11:
      blink_all();
      break;
    case 12:
      shira_morse();
      break;
  }
  do_sleep(2000);
}
