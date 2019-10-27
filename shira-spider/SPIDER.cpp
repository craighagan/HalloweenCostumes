/*
  SPIDER.h - Library for flashing LED code.
  Created by Craig I. Hagan 10/25/2019
  Released into the public domain.
*/


#include "Arduino.h"
#include "SPIDER.h"
#include "Sleep.h"
#include "DFRobotDFPlayerMini.h"
//#include "NewPing.h"

#define NR_BLINKS 20
#define DELAY_TIME 120

SPIDER::SPIDER(LED leds[], int nr_leds, DFRobotDFPlayerMini *mp3, NewPing *sonar, int activation_distance) {
  _leds = leds;
  _nr_leds = nr_leds;
  _mp3 = mp3;
  _sonar = sonar;
  _activation_distance = activation_distance;
}

void SPIDER::strobe_up() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}

void SPIDER::strobe_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].blink(100);
    do_sleep(10);
  }
}

void SPIDER::glow_up() {
  int led;
  for (led = 0; led < _nr_leds - 1; led++) {
    _leds[led].glow(100);
  }
}

void SPIDER::glow_down() {
  int led;
  for (led = _nr_leds - 1; led >= 0; led--) {
    _leds[led].glow(100);
  }
}


void SPIDER::glow_purple() {
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


void SPIDER::glow_orange() {
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

void SPIDER::glow_all() {
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

void SPIDER::blink_all(int nr_times) {
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

void SPIDER::alternate_color(int middle_led, int nr_times, int blink_delay) {
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


void SPIDER::alternate(int nr_times, int blink_delay) {
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

void SPIDER::shira_morse() {
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

void SPIDER::all_on() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].on();
  }
  do_sleep(64);
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].off();
  }
}


void SPIDER::print_detail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}


void SPIDER::play_sound() {
  _mp3->next();
  print_detail(_mp3->readType(), _mp3->read()); //Print the detail message from DFPlayer to handle different errors and states.
}

void SPIDER::play_sound(int file_nr) {
  _mp3->play(file_nr);
  print_detail(_mp3->readType(), _mp3->read()); //Print the detail message from DFPlayer to handle different errors and states.
}

void SPIDER::test() {
  int led;
  for (led = 0; led < _nr_leds; led++) {
    _leds[led].on();
    do_sleep(1024);
    _leds[led].off();
  }
  play_sound(2);
}

void SPIDER::wait_sensor_activated() {
  float distance = 0;

  while (true) {
    distance = _sonar->ping_in();
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" in");
    // Send results to Serial Monitor
    if (distance > 0 and distance <= _activation_distance) {
      return;
    }
  }
  do_sleep(250);
}


void SPIDER::start() {
  int led;
  //int action = random(17);
  int action = random(3);

  action = 0;
  Serial.println(action);

  switch (action) {
    case 0:
      play_sound();
      alternate(NR_BLINKS, DELAY_TIME);
      break;    
    case 1:
      play_sound();
      alternate_color(2, NR_BLINKS, DELAY_TIME);
      break;
    case 2:
      play_sound();
      blink_all(NR_BLINKS);
      break;
  }
  do_sleep(3000);
  wait_sensor_activated();
}
