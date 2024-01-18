#define USE_ARDUINO_INTERRUPTS true  // set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>

PulseSensorPlayground pulseSensor;
int bpm;

void setup() {   
  Serial.begin(9600);
  pulseSensor.analogInput(0);   
  pulseSensor.blinkOnPulse(LED_BUILTIN);
  // XXX: auto
  pulseSensor.setThreshold(506);
  pulseSensor.begin();
}

void loop() {
  bpm = pulseSensor.getBeatsPerMinute();
  Serial.println(bpm);
  delay(50);
}
