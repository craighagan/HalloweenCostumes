
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef SLEEP_h
#define SLEEP_h

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

extern int f_wdt;
void setup_sleep();
void do_sleep(int time);
void setup_watchdog(int ii);
void system_sleep();
ISR(WDT_vect);

#endif 
