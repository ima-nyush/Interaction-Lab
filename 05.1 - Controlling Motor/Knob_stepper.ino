// ProportionalControl example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper follow the analog value read from a pot or whatever
// The stepper will move at a constant speed to each newly set posiiton,
// depending on the value of the pot.

#include <AccelStepper.h>

int DIR_PIN = 2;
int STEP_PIN = 3;
int EN_PIN = 4;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

const int pot = A0;
int potVal;

void setup() {
  // Enable the stepper driver
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  stepper.setMaxSpeed(1000);
}

void loop() {

  potVal = analogRead(pot);
  stepper.moveTo(analog_in);
  stepper.setSpeed(300);
  stepper.runSpeedToPosition();
}
