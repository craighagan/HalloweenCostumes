/*
  HEADBAND.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/


#include "Arduino.h"
#include "HEADBAND.h"
#include "Sleep.h"

#define GLOW_RATE 3

HEADBAND::HEADBAND(LED leds[], int nr_leds) {
  _leds = leds;
  _nr_leds = nr_leds;
}

void HEADBAND::strobe_up() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}

void HEADBAND::strobe_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}


void HEADBAND::glow_up() {
  int led;
  for (led = 0; led < _nr_leds - 1; led++) {
    _leds[led].glow(100);
  }
}

void HEADBAND::glow_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].glow(100);
  }
}

void HEADBAND::glow_all() {
  int led;
  int amount;
  for (amount = 0; amount <= 255; amount += GLOW_RATE) {
    for (led = 0; led < _nr_leds; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
  do_sleep(100);
  for (amount = 255; amount >= 0; amount -= GLOW_RATE) {
    for (led = 0; led < _nr_leds; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
}

void HEADBAND::blink_all(int nr_times) {
  int led, nr_blinks;
  for (nr_blinks = 0; nr_blinks < nr_times; nr_blinks++) {
    for (led = 0; led < _nr_leds; led++) {
      _leds[led].on();
    }
    do_sleep(10);
    for (led = 0; led < _nr_leds; led++) {
      _leds[led].off();
    }
  }
}

void HEADBAND::alternate(int nr_times) {
  int led, nr_blinks;
  boolean turn_on = false;

  for (nr_blinks = 0; nr_blinks < nr_times; nr_blinks++) {
    for (led = 0; led < _nr_leds; led++) {
      if (led == 2) {
        _leds[led].on();
      } else {
        _leds[led].off();
      }
      turn_on = !turn_on;
    }
    do_sleep(96);
    for (led = 0; led < _nr_leds; led++) {
      if (led == 2) {
        _leds[led].off();
      } else {
        _leds[led].on();
      }
      turn_on = !turn_on;
    }
    do_sleep(96);
  }
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
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
  if (led > _nr_leds) led = 0;

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
  if (led > _nr_leds) led = 0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(between_letter_delay);

  // r
  led += 1;
  if (led > _nr_leds) led = 0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(after_letter_delay);
  _leds[led].dot();
  do_sleep(between_letter_delay);

  // a
  led += 1;
  if (led > _nr_leds) led = 0;

  _leds[led].dot();
  do_sleep(after_letter_delay);
  _leds[led].dash();
  do_sleep(between_letter_delay);

}

void HEADBAND::all_on() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].on();
  }
  do_sleep(64);
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
  }
}

void HEADBAND::start() {
  int led;
  int action = random(17);

  switch (action) {
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
      blink_all(random(3));
      break;
    case 14:
      shira_morse();
      break;
    case 15:
      alternate(random(5) + 5);
      break;
    case 16:
      all_on();
      break;
  }
  do_sleep(random(15) * 1000);
}
