// IMA NYU Shanghai
// Interaction Lab

/**
  This example is to send multiple values from Processing to Arduino.
  You can find the Processing example file in the same folder which works with this Arduino file.
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
  getSerialData();

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
      /*
  //end of example

}
//receive serial data from Processing
void getSerialData() {
  if (Serial.available()) {
    char c = Serial.read();
    //switch - case checks the value of the variable in the switch function
    //in this case, the char c, then runs one of the cases that fit the value of the variable
    //for more information, visit the reference page: https://www.arduino.cc/en/Reference/SwitchCase
    switch (c) {
      //if the char c from Processing is a number between 0 and 9
      case '0'...'9':
        //save the value of char c to tempValue
        //but simultaneously rearrange the existing values saved in tempValue
        //for the digits received through char c to remain coherent
        //if this does not make sense and would like to know more, send an email to me!
        tempValue = tempValue * 10 + c - '0';
        break;
      //if the char c from Processing is a comma
      //indicating that the following values of char c is for the next element in the values array
      case ',':
        values[valueIndex] = tempValue;
        //reset tempValue value
        tempValue = 0;
        //increment valuesIndex by 1
        valueIndex++;
        break;
      //if the char c from Processing is character 'n'
      //which signals that it is the end of data
      case '\n':
        //save the tempValue
        //this will b the last element in the values array
        values[valueIndex] = tempValue;
        //reset tempValue and valueIndex values
        //to clear out the values array for the next round of readings from Processing
        tempValue = 0;
        valueIndex = 0;
        break;
    }
  }
}
