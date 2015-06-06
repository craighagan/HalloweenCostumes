#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int f_wdt = 0;

void setup_sleep() {

}

// set system into the sleep state
// system wakes up when wtchdog is timed out
// taken from https://arduinoelectronics.wordpress.com/2014/01/06/ultra-low-power-led-flasher-with-attiny/

#ifdef ARDUINO_attiny
void system_sleep() {
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter ON
}

#else

void system_sleep() {

}

#endif

#ifdef ARDUINO_attiny

// taken from https://arduinoelectronics.wordpress.com/2014/01/06/ultra-low-power-led-flasher-with-attiny/
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}
#else
void setup_watchdog(int ii) {
  if (ii >= 9) ii = 9;

  switch (ii) {
    case 9:
      delay(8000);
      break;
    case 8:
      delay(4000);
      break;
    case 7:
      delay(2000);
      break;
    case 6:
      delay(1000);
      break;
    case 5:
      delay(500);
      break;
    case 4:
      delay(250);
      break;
    case 3:
      delay(128);
      break;
    case 2:
      delay(64);
      break;
    case 1:
      delay(32);
      break;
    case 0:
      delay(16);
      break;
  }
}
#endif

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt = 1; // set global flag
}


void do_sleep(int time) {

  while (time > 0) {
    if (time >= 8000) {
      setup_watchdog(9);
      system_sleep();
      time -= 8000;
    } else if (time >= 4000) {
      setup_watchdog(8);
      system_sleep();
      time -= 4000;
    } else if (time >= 2000) {
      setup_watchdog(7);
      system_sleep();
      time -= 2000;
    } else if (time >= 1000) {
      setup_watchdog(6);
      system_sleep();
      time -= 1000;
    } else if (time >= 500) {
      setup_watchdog(5);
      system_sleep();
      time -= 500;
    } else if (time >= 250) {
      setup_watchdog(4);
      system_sleep();
      time -= 250;
    } else if (time >= 128) {
      setup_watchdog(3);
      system_sleep();
      time -= 128;
    } else if (time >= 64) {
      setup_watchdog(2);
      system_sleep();
      time -= 64;
    } else if (time >= 32) {
      setup_watchdog(1);
      system_sleep();
      time -= 32;
    } else if (time >= 16) {
      setup_watchdog(0);
      system_sleep();
      time -= 16;
    } else {
      delay(time);
      time = 0;
    }
  }
}

