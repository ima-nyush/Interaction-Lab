# Text-to-Speech Module

## Circuit Diagram

## Code

First download the [syn6288 library](./syn6288/) and add it to your Arduino. This can be done by downloading the .zip file then in the Arduino IDE select **Sketch->Include Library->Add .zip Library**.

The example below loops a simple "Hello World!" over the TTS module.

```C++
#include <syn6288.h>
#include <SoftwareSerial.h>

#define txPin 12
#define rxPin 13

SoftwareSerial ttsSerial(12,13);
Syn6288 syn; 
uint8_t msg[] = {0xc4,0xe3,0xba,0xc3,0xca,0xc0,0xbd,0xe7}; //The message to broadcast goes here, use a GBK->Hexadecimal converter.

void setup()
{
  ttsSerial.begin(9600);
  pinMode(8,INPUT); //This pin produces a HIGH signal when the module is broadcasting a message, and low when not.
}
void loop()
{
  if (digitalRead(8)==LOW) { //This condition ensures that nothing is playing before sending the command to play something new.
    syn.play(msg, sizeof(msg), 1);
  }  
}
```

Since the modules we have are intended for Chinese speech they are based on GBK character encoding, which we need to convert to hexadecimal for Arduino. [Here](http://www.dwenzhao.cn/cal/php/hexhanzi.php) is a GBK->Hexadecimal converter that has the added benefit of formatting it with commas, allowing you to easily copy-paste the conversion into your code easily.
