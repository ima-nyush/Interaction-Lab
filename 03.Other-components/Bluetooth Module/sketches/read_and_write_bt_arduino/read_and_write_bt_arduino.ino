#include <SoftwareSerial.h>

#define NUM_OF_VALUES_FROM_PROCESSING 1 /* CHANGE THIS ACCORDING TO YOUR PROJECT */

#define rxPin 13
#define txPin 12

/* This array stores values from Processing */
int processing_values[NUM_OF_VALUES_FROM_PROCESSING];

int buttonPin = 2;
int ledPin = 4;

/* The Software Serial Library allows digital pins to be used as RX/TX pins. 
While we could use the default RX/TX pins 0 and 1 and normal serial communication,
these pins are also used to upload code to the board,
so anytime you would need to adjust and upload new code to the board, 
the bluetooth module would interrupt it. Software Serial is a workaround for this issue.

The defined RX pin should be connected to the HC-05's TX Pin, and the defined TX pin should be connected to the HC-05's RX Pin.
This is because the arduino board is receiving(RX) data trasmitted(TX) from the bluetooth module & vice versa*/
SoftwareSerial btSerial = SoftwareSerial(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  btSerial.begin(9600);
}

void loop() {
  getBTSerialData();

  if (processing_values[0] == 1) {
    // turn on an LED when the mouse is pressed
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  
  //send HIGH (1) when button pressed, send LOW (0) when not pressed
  btSerial.println(digitalRead(2));
}

void getBTSerialData() {
  static int tempValue = 0;  // the "static" makes the local variable retain its value between calls of this function
  static int tempSign = 1;
  static int valueIndex = 0;

  while (btSerial.available()) {
    char c = btSerial.read();
    if (c >= '0' && c <= '9') {
      // received a digit:
      // multiply the current value by 10, and add the character (converted to a number) as the last digit
      tempValue = tempValue * 10 + (c - '0');
    } else if (c == '-') {
      // received a minus sign:
      // make a note to multiply the final value by -1
      tempSign = -1;
    } else if (c == ',' || c == '\n') {
      // received a comma, or the newline character at the end of the line:
      // update the processing_values array with the temporary value
      if (valueIndex < NUM_OF_VALUES_FROM_PROCESSING) {  // should always be the case, but double-check
        processing_values[valueIndex] = tempValue * tempSign;
      }
      // get ready for the new data by resetting the temporary value and sign
      tempValue = 0;
      tempSign = 1;
      if (c == ',') {
        // move to dealing with the next entry in the processing_values array
        valueIndex = valueIndex + 1;
      } else {
        // except when we reach the end of the line
        // go back to the first entry in this case
        valueIndex = 0;
      }
    }
  }
}
