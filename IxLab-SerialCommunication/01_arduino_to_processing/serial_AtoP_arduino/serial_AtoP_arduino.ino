// IMA NYU Shanghai
// Interaction Lab
// For sending multiple values from Arduino to Processing


void setup() {
  Serial.begin(9600);
}

void loop() {
  // to send values to Processing assign the values you want to send
  //this is an example
  int sensor1 = analogRead(A0);
  int sensor2 = analogRead(A1);
  int sensor3 = analogRead(A2);

  // send the values keeping this format
  Serial.print(sensor1);
  Serial.print(",");  // put comma between sensor values
  Serial.print(sensor2);
  Serial.print(",");  // put comma between sensor values
  Serial.print(sensor3);
  Serial.println(); // add linefeed after sending the last sensor value

  // too fast communication might cause some latency in Processing
  // this delay resolves the issue.
  delay(100);

  // end of example sending values
}
