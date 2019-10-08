
#include "LED.h"
#include "PUMPKIN.h"
#include "Sleep.h"

#define NR_LEDS 5

LED leds[] = {
  LED(13), // orange
  LED(12), // orange
  LED(2), // purple
  LED(3), // purple
};

PUMPKIN pumpkin(leds, NR_LEDS);

int i;

void setup() {
  setup_sleep();
  randomSeed(analogRead(0));
  for (i = 0; i < NR_LEDS; i++) {
    leds[i].off();
  }
  pumpkin.test();
  do_sleep(64);
  pumpkin.strobe_up();
  do_sleep(128);
}

void loop() {
  pumpkin.start();
}
