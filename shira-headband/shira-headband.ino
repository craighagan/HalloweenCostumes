
#include "LED.h"
#include "HEADBAND.h"
#define NR_LEDS 3

LED leds[] = {
  LED(4),
  LED(3),
  LED(2),
};

HEADBAND headband(leds, NR_LEDS);

int i;

void setup() {
   Serial.begin(9600);
   Serial.print("hello world\n");
   randomSeed(analogRead(0));
   for(i=0;i<NR_LEDS;i++) {
      leds[i].off(); 
   }
}

void loop() {
   headband.start();
}
