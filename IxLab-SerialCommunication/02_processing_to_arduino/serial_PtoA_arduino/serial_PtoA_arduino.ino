// IMA NYU Shanghai
// Interaction Lab

/**
  This example is to send multiple values from Processing to Arduino.
  You can find the Processing example file in the same folder which works with this Arduino file.
  Please note that the echo case (when char c is 'e' in the getSerialData function below)
  checks if Arduino is receiving the correct bytes from the Processing sketch
  by sending the values array back to the Processing sketch.
 **/

#define NUM_OF_VALUES 3    /** YOU MUST CHANGE THIS ACCORDING TO YOUR PROJECT **/


/** DO NOT REMOVE THESE **/
int tempValue = 0;
int valueIndex = 0;

/* This is the array of values storing the data from Processing. */
int values[NUM_OF_VALUES];


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {

  // add your code here using elements in the values array
  
  //this is an example
      /*
        if (values[0] == 1) {
          //turn on an LED when the mouse is pressed
          digitalWrite(13, HIGH);
          // map values from mouseX to frequency from (0 - 500 pixels)
          //to the output pitch range (120 - 1500Hz)
          int f = map(values[1], 0, 500, 120, 1500);
          // map values from mouseY to frequency from (0 - 500 pixels)
          //to the output duration range (10 - 2000 milliseconds)
          int d = map(values[2], 0, 500, 10, 2000);
          // play the pitch:
          tone(8, values[1], values[2]);
          delay(1);        // delay in between reads for stability
        } else {
          digitalWrite(13, LOW);
        }
      */
  //end of example


}
