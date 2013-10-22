
#include "LED.h"
#include "BUTTON.h"

#define NR_LEDS 5

LED leds[] = {
  LED(13),
  LED(5),
  LED(A5),
  LED(A4),
  LED(6)
};

int i;

BUTTON button(11);

void setup() {
   //Serial.begin(9600);
  
   for(i=0;i<NR_LEDS;i++) {
      leds[i].off(); 
   }
}

void loop() {
  boolean is_pressed;
 
  is_pressed = button.pressed();
  
  if (is_pressed) {
    //Serial.print("button pressed\n");
    for(i=0;i<NR_LEDS&&is_pressed;i++) {
       is_pressed = button.pressed();
       leds[i].blink(40);
       delay(40);
    }
  } else {

     for(i=0;i<NR_LEDS&&!is_pressed;i++) {
       is_pressed = button.pressed();
       leds[i].blink(200);
       delay(750);
     }
  }
}
