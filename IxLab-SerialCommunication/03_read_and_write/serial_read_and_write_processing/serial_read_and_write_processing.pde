// IMA NYU Shanghai
// Interaction Lab

import processing.serial.*;

int NUM_OF_VALUES_FROM_PROCESSING = 2;  /** YOU MUST CHANGE THIS ACCORDING TO YOUR PROJECT **/
int NUM_OF_VALUES_FROM_ARDUINO = 2;  /** YOU MUST CHANGE THIS ACCORDING TO YOUR PROJECT **/

Serial myPort;
String myString;

int processing_values[]; /** this array stores values you might want to send to Arduino **/
int sensorValues[];      /** this array stores values from Arduino **/

void setup() {
  size(500, 500);
  setupSerial();
}


void draw() {
  background(0);
  
  //receive the values from Arduino
  getSerialData();

  //use the values from arduino
  //this is an example
      /* 
      //sensorValues[1] are the values from the button
       if (sensorValues[1] == 1) { 
       fill(random(255), random(255), random(255));
       }
       //sensorValues[0] are the values from the potentiometer
       float r = map(sensorValues[0], 0, 1023, 0, width); 
       circle(width/2, height/2, r);
       
       // give values to the variables you want to send here
       //change the code according to your project
       
       if (mousePressed) {
       processing_values[0] = 1;
       } else {
       processing_values[0] = 0;
       }
       processing_values[1] = int(map(mouseX, 0, width, 0, 255));
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

  processing_values = new int[NUM_OF_VALUES_FROM_PROCESSING];
  sensorValues = new int[NUM_OF_VALUES_FROM_ARDUINO];
}

void getSerialData() {
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil( 10 ); // 10 = '\n'  Linefeed in ASCII
    if (myString != null) {
      print("from arduino: "+ myString);
      String[] serialInArray = split(trim(myString), ",");
      if (serialInArray.length == NUM_OF_VALUES_FROM_ARDUINO) {
        for (int i=0; i<serialInArray.length; i++) {
          sensorValues[i] = int(serialInArray[i]);
        }
      }
    }
  }
}

void sendSerialData() {
  String data = "";
  for (int i=0; i<processing_values.length; i++) {
    data += processing_values[i];
    //if i is less than the index number of the last element in the values array
    if (i < processing_values.length-1) {
      data += ","; // add splitter character "," between each values element
    } 
    //if it is the last element in the values array
    else {
      data += "\n"; // add the end of data character "n"
    }
  }
  //write to Arduino
  myPort.write(data); 
  print("to arduino: "+ data); // this prints to the console the values going to arduino
}
