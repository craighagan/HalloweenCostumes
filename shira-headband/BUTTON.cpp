
/*
  BUTTON.cpp - Library for flashing BUTTON code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "BUTTON.h"

BUTTON::BUTTON(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _last_debounce_time = millis();
  _last_state = digitalRead(_pin);
  _state = HIGH;

  digitalWrite(_pin, HIGH);
}

boolean BUTTON::pressed()
{
  return digitalRead(_pin) == LOW;
}

boolean BUTTON::debounce_pressed()
{
  int cur_reading = digitalRead(_pin);
  if (cur_reading != _last_state) {
    _last_debounce_time = millis();
    _state = HIGH;
  } else {
    if ((millis() - _last_debounce_time) > DEBOUNCE_DELAY) {
      _state = cur_reading;
    }
  }
  _last_state = cur_reading;

  return _state == LOW;
}
