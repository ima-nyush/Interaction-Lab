// random example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper perform random changes in speed, position and acceleration
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
}

void loop() {
     if (stepper.distanceToGo() == 0)
    {
	// Random change to speed, position and acceleration
	// Make sure we dont get 0 speed or accelerations
	// The 28BYJ-48 is geared, so speeds are kept below ~800 steps/s
	delay(1000);
	stepper.moveTo(rand() % 2048);   // anywhere within one revolution
	stepper.setMaxSpeed(constrain((rand() % 800), 100, 800));
	stepper.setAcceleration(constrain((rand() % 800), 100, 800));
    }
    stepper.run();
}
