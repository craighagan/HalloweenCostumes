#include "SoftwareSerial.h"
#include "MP3.h"

// https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#Sample_Code
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

MP3::MP3(SoftwareSerial *software_serial) {
  _serial = software_serial;
}


void MP3::set_volume(int volume) {
  _execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

void MP3::play_first() {
  _execute_CMD(0x3F, 0, 0); // initialize
  delay(500);
  set_volume(20);
  delay(500);
  _execute_CMD(0x11, 0, 1); // repeat play 
  delay(500);
}

void MP3::pause()
{
  _execute_CMD(0x0E,0,0);
  delay(500);
}

void MP3::play()
{
  _execute_CMD(0x0D, 0, 1); 
  delay(500);
}

void MP3::play(int track) {
  _execute_CMD(0x03, 0, track);
  delay(500);
  _execute_CMD(0x0D, 0, 1);
  delay(500);
}

void MP3::play_next()
{
  _execute_CMD(0x01,0,1);
  delay(500);
}

void MP3::play_previous()
{
  _execute_CMD(0x02,0,1);
  delay(500);
}


void MP3::_execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                            Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
                          };
  //Send the command line to the module
  for (byte k = 0; k < 10; k++)
  {
    _serial->write( Command_line[k]);
  }
}
