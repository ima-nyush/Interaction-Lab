// Bounce example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper bounce from one limit to another
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
  // Change these to suit your stepper if you want
  // The 28BYJ-48 is geared, so keep the speed low (below ~800 steps/s)
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(200);
  // 1024 steps = about half a revolution
  stepper.moveTo(1024);
}

void loop() {

  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());
  }

  stepper.run();
}
