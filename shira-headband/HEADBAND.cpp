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
  led += 1;
  if (led > _nr_leds) led=0;
  
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(between_letter_delay);

  // i
  led += 1;
  if (led > _nr_leds) led=0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(between_letter_delay);

  // r
  led += 1;
  if (led > _nr_leds) led=0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(after_letter_delay);
  _leds[led].dot();  
  do_sleep(between_letter_delay);

  // a
  led += 1;
  if (led > _nr_leds) led=0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(between_letter_delay);
  
}

void HEADBAND::start() {
  int led;
  int action = random(15);
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
    case 5:
      strobe_up();
      strobe_down();
      break;
    case 6:
    case 7:
    case 8:
    case 9:
      led = random(_nr_leds);
      _leds[led].choose();
      break;
    case 10:
      glow_up();
      break;
    case 11:
      glow_down();
      break;
    case 12:
      glow_all();
      break;
    case 13:
      blink_all();
      break;
    case 14:
      shira_morse();
      break;
  }
  do_sleep(random(15)*1000);
}
