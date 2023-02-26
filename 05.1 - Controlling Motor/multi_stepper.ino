// MultiStepper example by Mike McCauley (mikem@airspayce.com)
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other stepper at the same time

#include <AccelStepper.h>

// Define stepper1 pins
int DIR_PIN1 = 2;
int STEP_PIN1 = 3;
int EN_PIN1 = 4;
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN1, DIR_PIN1);

// Define stepper2 pins
int DIR_PIN2 = 5;
int STEP_PIN2 = 6;
int EN_PIN2 = 7;
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);


void setup() {
  // Enable the stepper1 driver
  pinMode(EN_PIN1, OUTPUT);
  digitalWrite(EN_PIN1, LOW);

  // Enable the stepper2 driver
  pinMode(EN_PIN2, OUTPUT);
  digitalWrite(EN_PIN2, LOW);

  stepper1.setMaxSpeed(300.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(24);

  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(1000000);
}

void loop() {

  // Change direction at the limits
  if (stepper1.distanceToGo() == 0)
    stepper1.moveTo(-stepper1.currentPosition());
  stepper1.run();
  stepper2.run();
}
