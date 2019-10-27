/*
  MP3.h - Library for controlling mp3 player.
  Created by Craig I. Hagan 10/9/2019
  Released into the public domain.
*/
#ifndef MP3_h
#define MP3_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class MP3 {
  public:
    MP3(SoftwareSerial *serial);
    void play_first();
    void pause();
    void play();
    void play(int track);
    void play_next();
    void play_previous();
    void MP3::set_volume(int volume);
    void _execute_CMD(byte CMD, byte Par1, byte Par2);
  private:
    SoftwareSerial *_serial;
};

#endif
