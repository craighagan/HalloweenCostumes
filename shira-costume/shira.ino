
#include "LED.h"
#include "BUTTON.h"

#define NR_LEDS 7

LED leds[] = {
  LED(13),
  LED(A2),
  LED(10),
  LED(5),
  LED(A5),
  LED(6),
  LED(9)
};

int i;

BUTTON button(A3);
//BUTTON button(11);

void setup() {
   Serial.begin(9600);
   Serial.print("hello world\n");
   for(i=0;i<NR_LEDS;i++) {
      leds[i].off(); 
   }
}

void loop() {
  boolean is_pressed;
 
  is_pressed = button.pressed();
  
  if (is_pressed) {
    Serial.print("button pressed\n");
    for(i=0;i<NR_LEDS&&is_pressed;i++) {       
       leds[i].blink(40);
       is_pressed = button.pressed();
    }
  } else {
     Serial.print("button not pressed\n");
     for(i=0;i<NR_LEDS&&!is_pressed;i++) {
       leds[i].blink(200);
       delay(100);
       is_pressed = button.pressed();
       delay(100);
       is_pressed = button.pressed();
       delay(100);
       is_pressed = button.pressed();
       delay(100);
       is_pressed = button.pressed();       
     }     
  }
  
}