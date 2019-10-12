
#include "LED.h"
#include "PUMPKIN.h"
#include "Sleep.h"
#include "SoftwareSerial.h"
// https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#Sample_Code
#include "DFRobotDFPlayerMini.h"


#define VOLUME 10
#define NR_LEDS 5

LED leds[] = {
  LED(13), // orange
  LED(12), // orange
  LED(3), // purple
  LED(2), // purple
};

int serial_tx = 11;
int serial_rx = 10;
SoftwareSerial mp3serial(serial_rx, serial_tx);
DFRobotDFPlayerMini myDFPlayer;

PUMPKIN pumpkin(leds, NR_LEDS, &myDFPlayer);
int i;

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}


void setup() {
  mp3serial.begin(9600);
  Serial.begin(9600);
  myDFPlayer.begin(mp3serial, true, true);

  delay(60);

  if (myDFPlayer.available()) {
    Serial.println(F("DFPlayer Mini online."));
  }
  printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(VOLUME);  //Set volume value (0~30).
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

  //myDFPlayer.play(1);  //Play the first mp3

  setup_sleep();
  randomSeed(analogRead(0));
  for (i = 0; i < NR_LEDS; i++) {
    leds[i].off();
  }
  pumpkin.test();
}

void loop() {
  pumpkin.start();
}
