# Water Flow Sensor YF-S201

YF-S201 is a sensor used to measure water or air flow. This module works based on the hall magnetic effect. 
So when a fluid flows through the rotor assembly, the rotor will rotate and the hall effect sensor will produce an electric pulse.
By counting these generated pulses, the amount of water passing through the sensor can be calculated.

## Hardware
<img src="./Images/EMG.png" width="400" >
This sensor has 3 pins:

VCC: Module power supply – 5V
GND: Ground
OUT: Pulse output


### Circuit Setup

* 1 x Arduino Uno
* 3 x Jumper Wires
* 1 x  YF-S201 sensor


 ![Image of tm1637 Diagram](./Images/EMG_diagram.png)

1. Connect the water flow sesnor as showcased on the diagram above.
2. Blow through the opening or let water flow though to get a reading.


## Code
Upload the code to your board and open the Serial Monitor to check how the flow values. 


```C++

double flow; 
unsigned long pulse_freq;

void setup(){
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, pulse, RISING); 
}

void loop (){
    flow = .00225 * pulse_freq;
    Serial.print(flow, DEC);
    Serial.println("L");
    delay(500);
  }

void pulse (){
  pulse_freq++;
}

```



