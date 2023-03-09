

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
