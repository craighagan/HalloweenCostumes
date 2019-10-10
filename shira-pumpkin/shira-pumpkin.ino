
#include "LED.h"
#include "PUMPKIN.h"
#include "Sleep.h"
#include "SoftwareSerial.h"

// https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#Sample_Code
#include "DFRobotDFPlayerMini.h"

#define NR_LEDS 5

LED leds[] = {
  LED(13), // orange
  LED(12), // orange
  LED(2), // purple
  LED(3), // purple
};

int serial_tx = 10;
int serial_rx = 11;
SoftwareSerial mp3serial(serial_tx, serial_rx);
//MP3 mp3(&mp3serial);
DFRobotDFPlayerMini myDFPlayer;


PUMPKIN pumpkin(leds, NR_LEDS, &myDFPlayer);

int i;

void setup() {
  mp3serial.begin(9600);

  if (!myDFPlayer.begin(mp3serial)) {  //Use mp3serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(15);  //Set volume value (0~30).
  //myDFPlayer.volumeUp(); //Volume Up
  //myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
//  myDFPlayer.EQ(DFPLAYER_EQ_POP);
//  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
//  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
//  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
//  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  //----Set device we use SD as default----
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  myDFPlayer.disableLoop(); //disable loop.

  myDFPlayer.play(1);  //Play the first mp3

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
