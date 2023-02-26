// Bounce example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper bounce from one limit to another

#include <AccelStepper.h>

int DIR_PIN = 2;
int STEP_PIN = 3;
int EN_PIN = 4;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Enable the stepper driver
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(100);
  stepper.moveTo(600);
}

void loop() {

  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run();
}
