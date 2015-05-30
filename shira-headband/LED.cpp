
/*
  LED.cpp - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "LED.h"
#include "Sleep.h"

LED::LED(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void LED::on()
{
  digitalWrite(_pin, HIGH);
}

void LED::off()
{
  digitalWrite(_pin, LOW);
}

void LED::dim(int amount)
{
  analogWrite(_pin, amount); 
}

void LED::dot()
{
  digitalWrite(_pin, HIGH);
  do_sleep(150);
  digitalWrite(_pin, LOW);
  do_sleep(150);  
}

void LED::dash()
{
  digitalWrite(_pin, HIGH);
  do_sleep(500);
  digitalWrite(_pin, LOW);
  do_sleep(150);
}

void LED::blink(int time)
{
 digitalWrite(_pin, HIGH);
 do_sleep(time);
 digitalWrite(_pin, LOW); 
}

void LED::glow(int time)
{
 int i;
 for(i=0;i<=255;i++) {
   analogWrite(_pin, i);
   do_sleep(10);
 }
 delay(time);
 for(i=255;i>=0;i--) {
   analogWrite(_pin, i);
   do_sleep(10);
 } 
}

void LED::choose() {
 int which;
 which = random(4);
 switch (which) {
    case 0:
      // dot
      LED::dot();
      break;
    case 1:
      // dash
      LED::dash();
      break;
    case 2:
      // blink
      LED::blink(random(100,1000));
      break;
    case 3:
      // glow
      LED::glow(random(100,1000));
      break;
 }  
}
