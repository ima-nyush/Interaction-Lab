# Infrared Proximity Sensor

![Image of L298N](./Images/)

In this tutorial we will use the Sharp IR sensor (GP2Y0A41SK0F) to measure distance from an object.

IR Sensors work by using a specific light sensor to detect a select light wavelength in the Infra-Red (IR) spectrum. By using an LED which produces light at the same wavelength as what the sensor is looking for, you can look at the intensity of the received light. When an object is close to the sensor, the light from the LED bounces off the object and into the light sensor. This results in a large jump in the intensity, which we already know can be detected using a threshold.

Since the sensor works by looking for reflected light, it is possible to have a sensor that can return the value of the reflected light. This type of sensor can then be used to measure how "bright" the object is. This is useful for tasks like line tracking.

In this tutorial we will try to measure the distance from an object (4~30cm).

# Ciruit Diagram

# Arduino Code

``` C++
// Sharp IR GP2Y0A41SK0F Distance Test
// http://tinkcore.com/sharp-ir-gp2y0a41-skf/

#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 
  
  if (distance <= 30){
    Serial.println(distance);   // print the distance
  }
}
```
