// based on ConstantSpeed example by Mike McCauley (mikem@airspayce.com)
#include <AccelStepper.h>

int DIR_PIN = 2;
int STEP_PIN = 3;
int EN_PIN = 4;

// Define a stepper and the pins it will use
// AccelStepper::DRIVER means a stepper driver (with step and direction pins)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Enable the stepper driver by setting the
  // EN pin to LOW
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  // The run() function will accelerate up to
  // the speed set here
  stepper.setMaxSpeed(1000);
  // Set the desired constant speed for use with
  // runSpeed()
  stepper.setSpeed(500); 
}

void loop() {
  stepper.runSpeed();
}
