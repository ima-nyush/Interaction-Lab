#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

SoftwareSerial softSerial(4, 5)  //rx, tx
DFRobotDFPlayerMini myDFPlayer;

void setup() {

  Serial.begin(115200);
  softSerial.begin(9600);

  if (!myDFPlayer.begin(softSerial, /*isACK = */ false, /*doReset = */ false)) {  //Use serial to communicate with mp3.
    Serial.println("Error starting DFplayer");
  }
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);     //Play the first mp3
}

void loop() {
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();
  }
}
