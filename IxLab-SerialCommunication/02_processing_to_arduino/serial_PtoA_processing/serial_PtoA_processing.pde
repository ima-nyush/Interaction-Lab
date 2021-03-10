// IMA NYU Shanghai
// Interaction Lab


/**
 * This example is to send multiple values from Processing to Arduino.
 * You can find the arduino example file in the same folder which works with this Processing file.
 * Please note that the echoSerialData function asks Arduino to send the data saved in the values array
 * to check if it is receiving the correct bytes.
 **/


import processing.serial.*;

int NUM_OF_VALUES = 3;  /** YOU MUST CHANGE THIS ACCORDING TO YOUR PROJECT **/
int values[] = new int[NUM_OF_VALUES]; /** this array stores values you might want to send to Arduino **/

Serial myPort;
String myString;


void setup() {
  size(500, 500);
  background(0);
  setupSerial();
}


void draw() {
  background(0);

  // give values to the variables you want to send here
  //change the code according to your project
  //for example:
  /*
    if (mousePressed) {
      values[0] = 1;
    } else {
      values[0] = 0;
    }
    values[1] = mouseX;
    values[2] = mouseY;
   */
  //end of example

  // send the values to Arduino.
  sendSerialData();

}

void setupSerial() {
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[PORT_INDEX], 9600);
  // WARNING!
  // You will definitely get an error here.
  // Change the PORT_INDEX to 0 and try running it again.
  // And then, check the list of the ports,
  // find the port "/dev/cu.usbmodem----" or "/dev/tty.usbmodem----" 
  // and replace PORT_INDEX above with the index number of the port.

  myPort.clear();
  // Throw out the first reading,
  // in case we started reading in the middle of a string from the sender.
  myString = myPort.readStringUntil( 10 );  // 10 = '\n'  Linefeed in ASCII
  myString = null;

}

void sendSerialData() {
  String data = "";
  for (int i=0; i<values.length; i++) {
    data += values[i];
    //if i is less than the index number of the last element in the values array
    if (i < values.length-1) {
      data += ","; // add splitter character "," between each values element
    } 
    //if it is the last element in the values array
    else {
      data += "\n"; // add the end of data character linefeed "\n"
    }
    
  }
  //write to Arduino
  myPort.write(data);
  print(data); // this prints to the console the values going to arduino 
  
}
