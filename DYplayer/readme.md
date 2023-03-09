# MP3 Player Model DY-SV5W
This documentation is an improved version, made for IMA/B @ NYU Shanghai, based on the following two sources:
- [DYPlayer Library](https://github.com/SnijderC/dyplayer).
- [Arduino serial control DY-SV5W audio playback](https://www.programmersought.com/article/94405345077/)

![Alt text](DY-SV5W-withTable.jpg?raw=true "MP3 player model DY-5V5W")

## DY-SV5W Features

DY-SV5W is a smart voice module with Integrated IO trigger, UART protocol control, One_line single-bus protocol control, standard MP3 and other 7 operating modes setting by DIP switch; Drive 4~8Ω, 3~5W speaker by a 5W class D audio amplifier on board；Support MP3、WAV decoding; Support TF card for maximum 32G downloading music files directly by micro USB connector.

1、Supports MP3、WAV decoding。
2、Supports sampling rate (KHz):8/11.025/12/16/22.05/24/32/44.1/48。
3、24bit DAC output，support dynamic range 90dB，SNR 85dB。
4、Supports FAT16/FAT32 file system，support TF card for maximum 32G。
5、Drives 4~8Ω speaker by 5W class D amplifier chip on board。
6、Play 65535 pieces of music by UART control protocol; Play, Pause, Selecting music, VOL+/- and so on can be controlled，the communication baud rate is 9600bps。
7、Play 255 pieces of music by IO triggering;
8、Play music by One_line control protocol，Play, Pause, Selecting music, VOL+/- and so on can be controlled。
9、Switch 7 operating modes using DIP switch easily

## Sound File Requirements
This MP3 module has requirements for the format of the files. We know that the following works well:
- Format the micro SD card with FAT16 or FAT32 format
- Make sure your files are in MP3 format in 44.1kHz
- Name your files as 0001.mp3 and 0002.mp3 and so on

## Setup
The MP3 can be programmed to play automatically or by using io0 to io7
For use with Arduino, make sure that the DIP switches are in the following position:
| CON pin    | Position   |
|:-----------|:-----------|
| `CON1`     | `Low`      |
| `CON2`     | `Low`      |
| `CON3`     | `High`     |

You have to also connect the MP3 with your Arduino:
| Pin      | Connect to                          |
|:---------|:------------------------------------|
| `V+`     | `5V`                                |
| `V-`     | `GND`                               |
| `IO0/TX` | `Arduino RX - pin 10 in our example`|
| `IO1/RX` | `Arduino TX - pin 11 in our example`|
| `SPK+`   | `Speaker`                           |
| `SPK-`   | `Speaker`                           |



## Library Installation
Download and install the library at

Download the [DYPlayer Libray](https://github.com/SnijderC/dyplayer/archive/master.zip) and unzip it into the libraries file of Arduino IDE by the path: ..\arduino-1.0.1\libraries. If having trouble, read the guide to Arduino library.

## Usage example
```cpp


#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DYPlayerArduino.h"

SoftwareSerial SoftSerial(10, 11);  //RX and TX from Arduino
DY::Player player(&SoftSerial);     //should connect them to io0 and io1

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the Player...");

  player.begin();
  player.setPlayingDevice(DY::Device::Sd); //SD card, USB storage volume is
  player.setVolume(30); // 30 is 100% of Volume; with 15 you get 50% Volume
  // player.setCycleMode(DY::PlayMode::Repeat); // Play all and repeat.
  player.play();
  // player.next();

}

void loop() {
  // Print the number of the sound that is playing.
  Serial.print("Playing Device: ");
  Serial.println((int16_t)player.checkPlayState()); //if you receive -1, it's fail
  // Print the number of the sound that is playing.
  Serial.print("Playing sound: ");
  Serial.println((int16_t)player.getPlayingSound());
  delay(500);
}
```

## Additional information
* You can find the original supplier information at [this link](https://detail.tmall.com/item.htm?spm=a230r.1.14.19.29901a2aDiFbEI&id=586292221116&ns=1&abbucket=14)
* This module works well with our micro SD cards of 8Gb and with the "Stereo Enclosure Speaker Set"
