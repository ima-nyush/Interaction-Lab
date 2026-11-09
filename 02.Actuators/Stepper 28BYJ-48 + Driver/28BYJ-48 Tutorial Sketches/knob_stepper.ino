// ProportionalControl example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper follow the analog value read from a pot or whatever
// The stepper will move at a constant speed to each newly set position,
// depending on the value of the pot.
// Adapted for the 28BYJ-48 stepper motor + ULN2003 driver board

#include <AccelStepper.h>

// Driver board pins (IN1 -> D8, IN2 -> D9, IN3 -> D10, IN4 -> D11)
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// NOTE: the pin order is IN1, IN3, IN2, IN4
AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);

// Approximate number of steps for one output-shaft revolution
const int STEPS_PER_REVOLUTION = 2048;

const int pot = A0;
int potVal;

void setup() {
  stepper.setMaxSpeed(1000);
}

void loop() {

  potVal = analogRead(pot);
  // Map the full pot range (0-1023) to one full revolution of the motor
  stepper.moveTo(map(potVal, 0, 1023, 0, STEPS_PER_REVOLUTION));
  stepper.setSpeed(500);
  stepper.runSpeedToPosition();
}
