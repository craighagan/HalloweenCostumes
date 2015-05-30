
/*
  LED.cpp - Library for flashing LED code.
  Created by Craig I. Hagan 9/30/2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "LED.h"
#include "JeeLib.h" // Low power functions library

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

void LED::dot()
{
  digitalWrite(_pin, HIGH);
  Sleepy::loseSomeTime(250);
  digitalWrite(_pin, LOW);
  Sleepy::loseSomeTime(250);  
}

void LED::dash()
{
  digitalWrite(_pin, HIGH);
  Sleepy::loseSomeTime(1000);
  digitalWrite(_pin, LOW);
  Sleepy::loseSomeTime(250);
}

void LED::blink(int time)
{
 digitalWrite(_pin, HIGH);
 Sleepy::loseSomeTime(time);
 digitalWrite(_pin, LOW); 
}

void LED::glow(int time)
{
 int i;
 for(i=0;i<=255;i++) {
   analogWrite(_pin, i);
   Sleepy::loseSomeTime(10);
 }
 delay(time);
 for(i=255;i>=0;i--) {
   analogWrite(_pin, i);
   Sleepy::loseSomeTime(10);
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
