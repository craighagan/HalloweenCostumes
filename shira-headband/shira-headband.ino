
#include "LED.h"
#include "HEADBAND.h"
#include "Sleep.h"

#define NR_LEDS 5

LED leds[] = {
  LED(0),
  LED(1),
  LED(2),
  LED(3),
  LED(4),
};

HEADBAND headband(leds, NR_LEDS);

int i;

void setup() {
  setup_sleep();
  randomSeed(analogRead(0));
  for (i = 0; i < NR_LEDS; i++) {
    leds[i].off();
  }
  headband.test();
  do_sleep(64);
  headband.strobe_up();
  do_sleep(128);
}

void loop() {
  headband.start();
}
