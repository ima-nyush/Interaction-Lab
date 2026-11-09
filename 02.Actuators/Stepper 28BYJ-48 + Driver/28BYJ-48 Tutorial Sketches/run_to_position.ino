// based on: Blocking example by Mike McCauley (mikem@airspayce.com)
// Shows how to use the blocking call runToNewPosition
// Which sets a new target position and then waits until the stepper has 
// achieved it. The 28BYJ-48 takes about 2048 steps for one rotation
// of the output shaft (in FULL4WIRE mode).
// Adapted for the 28BYJ-48 stepper motor + ULN2003 driver board
#include <AccelStepper.h>

// Driver board pins (IN1 -> D8, IN2 -> D9, IN3 -> D10, IN4 -> D11)
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// NOTE: the pin order is IN1, IN3, IN2, IN4
AccelStepper stepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  // Set initial speed & acceleration
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(200);
}

void loop() {
  stepper.runToNewPosition(2048);   // one full revolution
  delay(1000);
  stepper.runToNewPosition(0);      // back to the start
  delay(1000);
}
