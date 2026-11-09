// random example by Mike McCauley (mikem@airspayce.com)
// Make a single stepper perform random changes in speed, position and acceleration

#include <AccelStepper.h>

int DIR_PIN = 2;
int STEP_PIN = 3;
int EN_PIN = 4;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Enable the stepper driver
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
}

void loop() {
     if (stepper.distanceToGo() == 0)
    {
	// Random change to speed, position and acceleration
	// Make sure we dont get 0 speed or accelerations
	delay(1000);
	stepper.moveTo(rand() % 200);
	stepper.setMaxSpeed(constrain((rand() % 1500), 75, 1500));
	stepper.setAcceleration(constrain((rand() % 1500), 75, 1500));
    }
    stepper.run();
}
