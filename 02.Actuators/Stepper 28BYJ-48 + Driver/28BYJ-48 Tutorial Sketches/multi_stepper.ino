// MultiStepper example by Mike McCauley (mikem@airspayce.com)
// Shows how to multiple simultaneous steppers
// Runs both steppers forwards and backwards, accelerating and decelerating
// at the limits
// Adapted for two 28BYJ-48 stepper motors + ULN2003 driver boards

#include <AccelStepper.h>

// Define stepper1 pins (IN1 -> D8, IN2 -> D9, IN3 -> D10, IN4 -> D11)
int IN1_1 = 8;
int IN2_1 = 9;
int IN3_1 = 10;
int IN4_1 = 11;
// NOTE: the pin order is IN1, IN3, IN2, IN4
AccelStepper stepper1(AccelStepper::FULL4WIRE, IN1_1, IN3_1, IN2_1, IN4_1);

// Define stepper2 pins (IN1 -> D4, IN2 -> D5, IN3 -> D6, IN4 -> D7)
int IN1_2 = 4;
int IN2_2 = 5;
int IN3_2 = 6;
int IN4_2 = 7;
AccelStepper stepper2(AccelStepper::FULL4WIRE, IN1_2, IN3_2, IN2_2, IN4_2);

// Two motors draw more current than the Arduino 5V pin can comfortably
// supply: power the driver boards from an external 5V supply and
// connect its GND to the Arduino GND.

void setup() {
  stepper1.setMaxSpeed(300.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(2048);   // about one revolution

  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(4096);   // about two revolutions
}

void loop() {

  // Change direction at the limits
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  if (stepper2.distanceToGo() == 0) {
    stepper2.moveTo(-stepper2.currentPosition());
  }
  stepper1.run();
  stepper2.run();
}
