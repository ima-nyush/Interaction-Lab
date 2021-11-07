// IMA NYU Shanghai
// Interaction Lab
//This example is to send multiple values from Processing to Arduino and Arduino to Processing.

#define NUM_OF_VALUES_FROM_PROCESSING 2    /** YOU MUST CHANGE THIS ACCORDING TO YOUR PROJECT **/

/** DO NOT REMOVE THESE **/
int tempValue = 0;
int valueIndex = 0;

/* This is the array of values storing the data from Processing. */
int processing_values[NUM_OF_VALUES_FROM_PROCESSING];

void setup() {
  Serial.begin(9600);
  // this block of code is an example of an LED, a DC motor, and a button
  /*
    pinMode(13, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(2, INPUT);
  */
  //end example
}

void loop() {

  // to receive a value from Processing
  getSerialData();
  
  // add your code here
  // use elements in the values array
  //and print values to send to Processing

  // this is an example:
  /*
    //example of using received values and turning on an LED
    if (processing_values[0] == 1) {
    digitalWrite(13, HIGH);
    } else {
    digitalWrite(13, LOW);
    }
    analogWrite(9, processing_values[1]);
    // too fast communication might cause some latency in Processing
    // this delay resolves the issue.
    delay(10);
    //end of example of using received values


    //example of sending the values to Processing
    int sensor1 = analogRead(A0); // a potentiometer
    int sensor2 = digitalRead(2); // the button

    // send the values keeping this format
    Serial.print(sensor1);
    Serial.print(",");  // put comma between sensor values
    Serial.print(sensor2);
    Serial.println(); // add linefeed after sending the last sensor value
    // end of example sending values
  */
  // end of example
}

//receive serial data from Processing
void getSerialData() {
  while (Serial.available()) {
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
        processing_values[valueIndex] = tempValue;
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
        processing_values[valueIndex] = tempValue;
        //reset tempValue and valueIndex values
        //to clear out the values array for the next round of readings from Processing
        tempValue = 0;
        valueIndex = 0;
        break;
    }
  }
}
