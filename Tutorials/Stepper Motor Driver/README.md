## Work In Progress

This tutorial is still to be developed. If you want to contribute to it, please get in touch with Interaction Lab faculty.

Our steppers have an approximate max speed of 900rpm when set to full-stepping. Going past this may result in the motor missing steps or stalling entirely.

### IxLab examples codes from Andy for stepper motors based on by Mike McCauley's AccelStepper library (mikem@airspayce.com)

Constant speed example: Shows how to run AccelStepper in the simplest, fixed speed mode with no accelerations.

Run to position example: Shows how to use runToNewPosition which sets a new target position and then waits until the stepper has achieved it.

Bounce example: Make a single stepper bounce from one limit to another.

Knob stepper example: Make a single stepper follow the analog value read from a pot or whatever. The stepper will move at a constant speed to each newly set posiiton, depending on the 
value of the pot.

Multi stepper example: Shows how to use multiple simultaneous steppers.

Random example: Make a single stepper perform random changes in speed, position and acceleration.

Additional documenttion: https://www.airspayce.com/mikem/arduino/AccelStepper/index.html
