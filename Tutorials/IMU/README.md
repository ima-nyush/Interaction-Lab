# IMU

In this tutorial we will learn how to use the MPU6050 paired with an Arduino Leonardo to control the mouse cursor from your laptop.
The MPU6050 is an IMU device (Inertial Measurement Unit) that calculates three-axis accelerometer and three-axis gyroscope data.


## Hardware
![Image the MPU6050](./Images/MPU-6050.png)

Here are some common IMU specifications:

<u>Gyroscope </u> – The gyroscope measures rotational velocity or rate of change of the angular position over time, along the X, Y and Z axis. 

<u>Accelerometer </u> – The accelerometer can measure both static and dynamic forces of acceleration, along the X, Y and Z axis. The earth gravitational force is a typical example of static force, while dynamic forces can be caused by vibrations, movements and so on.


### Circuit Setup

* 1 x Arduino Leonardo
* 4 x Jumper Wires (M/F)
* 1 x MPU 6050

 ![Image of MPU6050 Diagram](./Images/MPU6050_circuit.jpeg)


|MPU6050    | Arduino        | 
| ------------- |:-------------:| 
| GND     | GND | 
| VCC     | 5V     |   
| SDA |  SDA   | 
| SCL | SCL      | 


## Code
Beefore running the code, you will need to install the following libraries to make it work. In your library manager search for:
- Adafruit MPU6050 by adafruit
- Mouse by Arduino
- Additionally you will need to do a manual installation of the library I2Cdevlib by jrwoberg. You can install it by following these instructions:
   Download the i2cdevlib project: https://github.com/jrowberg/i2cdevlib/archive/master.zip (8.2k)  
   Unzip the downloaded file.  
   Move the "Arduino/I2Cdev" subfolder inside the Arduino library folder. Usually in this location: Documents -> Arduino -> Libraries  


Upload the code to your board and see how the mouse on the screen moves according to the position of the IMU. 

Code reference from edwardthe found at hackster.io

```C++
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Mouse.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = (gx - 400) / 200; // "-400" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy = -(gz - 200) / 200; // same here about "-200"
  Mouse.move(vx, vy);
  delay(20);
}
```

