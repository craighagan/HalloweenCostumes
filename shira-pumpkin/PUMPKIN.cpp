/*
  PUMPKIN.h - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/


#include "Arduino.h"
#include "PUMPKIN.h"
#include "Sleep.h"
#include "DFRobotDFPlayerMini.h"


PUMPKIN::PUMPKIN(LED leds[], int nr_leds, DFRobotDFPlayerMini *mp3) {
  _leds = leds;
  _nr_leds = nr_leds;
  _mp3 = mp3;
}

void PUMPKIN::strobe_up() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}

void PUMPKIN::strobe_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}

void PUMPKIN::glow_up() {
  int led;
  for (led = 0; led < _nr_leds - 1; led++) {
    _leds[led].glow(100);
  }
}

void PUMPKIN::glow_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].glow(100);
  }
}


void PUMPKIN::glow_purple() {
  int led;
  int amount;
  for (amount = 0; amount <= 255; amount += GLOW_RATE) {
    for (led = _nr_leds / 2; led < _nr_leds; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
  do_sleep(100);
  for (amount = 255; amount >= 0; amount -= GLOW_RATE) {
    for (led = _nr_leds / 2; led < _nr_leds; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
}


void PUMPKIN::glow_orange() {
  int led;
  int amount;
  for (amount = 0; amount <= 255; amount += GLOW_RATE) {
    for (led = 0; led < _nr_leds / 2; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
  do_sleep(100);
  for (amount = 255; amount >= 0; amount -= GLOW_RATE) {
    for (led = 0; led < _nr_leds / 2; led++) {
      _leds[led].dim(amount);
    }
    do_sleep(10);
  }
}

void PUMPKIN::glow_all() {
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

void PUMPKIN::blink_all(int nr_times) {
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

void PUMPKIN::alternate_color(int middle_led, int nr_times, int blink_delay) {
  int led, nr_blinks;
  boolean turn_on = false;

  for (nr_blinks = 0; nr_blinks < nr_times; nr_blinks++) {
    for (led = 0; led < middle_led; led++) {
      _leds[led].on();
    }
    for (led = middle_led; led < _nr_leds; led++) {
      _leds[led].off();
    }
    do_sleep(blink_delay);
    for (led = 0; led < middle_led; led++) {
      _leds[led].off();
    }
    for (led = middle_led; led < _nr_leds; led++) {
      _leds[led].on();
    }
    do_sleep(blink_delay);
  }
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
  }
}


void PUMPKIN::alternate(int nr_times, int blink_delay) {
  int led, nr_blinks;
  boolean turn_on = false;

  for (nr_blinks = 0; nr_blinks < nr_times; nr_blinks++) {
    for (led = 0; led < _nr_leds; led++) {
      if (led % 2) {
        _leds[led].on();
      } else {
        _leds[led].off();
      }
      turn_on = !turn_on;
    }
    do_sleep(blink_delay);
    for (led = 0; led < _nr_leds; led++) {
      if (led % 2) {
        _leds[led].off();
      } else {
        _leds[led].on();
      }
      turn_on = !turn_on;
    }
    do_sleep(blink_delay);
  }
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
  }
}

void PUMPKIN::shira_morse() {
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

void PUMPKIN::all_on() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].on();
  }
  do_sleep(64);
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
  }
}

void PUMPKIN::play_sound() {
  if (_mp3->available()) {
      _mp3->next();    
  }
}

void PUMPKIN::test() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].on();
    do_sleep(1024);
    _leds[led].off();
  }
}

void PUMPKIN::start() {
  int led;
  int action = random(17);

  //action = 11; //deleteme
  switch (action) {
    case 0:
    case 1:
      // strobe up
      play_sound();
      strobe_up();
      break;
    case 2:
    case 3:
      // strobe down
      play_sound();
      strobe_down();
      break;
    case 5:
      play_sound();
      strobe_up();
      strobe_down();
      break;
    case 6:
      play_sound();
      alternate_color(2, random(5) + 5, 65);
      break;
    case 7:
      play_sound();
      glow_orange();
      break;
    case 8:
      play_sound();
      glow_purple();
      break;
    case 9:
      led = random(_nr_leds);
      _leds[led].choose();
      break;
    case 10:
      play_sound();
      alternate(random(5) + 5, 45);
      break;
    case 11:
      play_sound();
      alternate_color(2, random(5) + 5, 120);
      break;
    case 12:
      play_sound();
      glow_all();
      break;
    case 13:
      play_sound();
      blink_all(random(3));
      break;
    case 14:
      play_sound();
      shira_morse();
      break;
    case 15:
      play_sound();
      alternate(random(5) + 5, 45);
      break;
    case 16:
      play_sound();
      all_on();
      break;
  }
  do_sleep(random(5) * 1000);
}
