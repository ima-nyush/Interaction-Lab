# Solenoid

A Solenoid is a coil that when energized, produces a controlled magnetic field down through its center. By placing a magnetic armature inside that field, the armature can move in or out of the coil. Solenoids are found in paintball guns, pinball machines, printers, valves, and even automobiles.

## Hardware
(solenoid pic)
Here are some common solenoid specifications:

<u>Throw</u>- This refers to the length of the armature moving in and out of the solenoid.

<u>Mounting options</u> – Most solenoids have mounting holes in the case so that your armature can actually push and/or pull its load. Otherwise, the solenoid would likely push itself around instead of the load!

<u>Duty cycle</u> – This is expressed as a percentage of time the solenoid is switched on for. For example, if a solenoid is energised for 30 seconds before switching off for 30 seconds, its duty cycle is 50%.

<u>Operating Voltage</u> – Similarly to DC motors, this refers to the ideal voltage needed for the solenoid to run optimally. If you apply a lesser voltage you can expect a slower and weaker throw.

<u>Starting Force</u> – Measured in Newtons, this is the force the solenoid will have at the beginning of its movement.

<u>Actuation Time</u> – The time taken from switch-on to completion of the stroke.

### Circuit Setup
In this tutorial, we are going to switch a small 5v Solenoid on and off in intervals of 1 second. You will need the following components for this tutorial:

* 1 x Arduino Uno
* 1 x Solderless breadboard
* 5 x Jumper Wires
* 1 x 220 Ω Resistor
* 1 x [Diode](https://core-electronics.com.au/1n4001-diode-10-pack.html)
* 1 x [Power Transistor](https://core-electronics.com.au/tip120-power-darlington-transistors-3-pack.html)
* [**1 x 5v Solenoid**](https://core-electronics.com.au/5v-solenoid.html)

 (image of diagram )

1. Connect 5v Power and Ground from your Arduino to your power and ground rails on your breadboard
2. Connect your solenoid to separate lines on your breadboard, one to the 5v power from step 2, the other needs to connect to the collector (middle) of the transistor.
3. Connect your Diode between the two solenoid cables, this will prevent current discharging back through the circuit when the solenoid coil discharges.
4. Insert your power transistor on three separate lines of your breadboard, with the flat side facing toward the outside. Ensure the collector's leg is connected to the solenoid and diode line.
5. Connect a 220-ohm Resistor from the base leg of the transistor to a separate line
6. Connect the emitter leg to the ground rail.
7. Connect the other side of the resistor from step 6 to digital pin 9, that's our control pin.

## Code
Upload the code to your board. CLICK! CLICK! CLICK! CLICK! Your solenoid should be toggling on and off. 
```C++
int solenoidPin = 9;                    //This is the output pin on the Arduino

void setup() 
{
  pinMode(solenoidPin, OUTPUT);          //Sets that pin as an output
}

void loop() 
{
  digitalWrite(solenoidPin, HIGH);      //Switch Solenoid ON
  delay(1000);                          //Wait 1 Second
  digitalWrite(solenoidPin, LOW);       //Switch Solenoid OFF
  delay(1000);                          //Wait 1 Second
}
```

