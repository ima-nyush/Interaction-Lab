# Motion Sensors HC-SR501(PIR)
This tutorial is made for NYUSH IMA community based on [SunFounder Documentation](https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/components_basic/13-component_pir_motion.html).

![pirsensor](./images/pir-sensor.jpg)

## Introduction
The Passive Infrared(PIR) Motion Sensor is a sensor that detects motion. It is commonly used in security systems and automatic lighting systems. The sensor has two slots that detect infrared radiation. When an object, such as a person, passes in front of the sensor, it detects a change in the amount of infrared radiation and triggers an output signal.
## Hardware
![MotionSensorStructure](./images/motionsensor.png)

###Distance Adjustment
Turning the knob of the distance adjustment potentiometer clockwise, the range of sensing distance increases, and the maximum sensing distance range is about 0-7 meters. If turn it anticlockwise, the range of sensing distance is reduced, and the minimum sensing distance range is about 0-3 meters.

###Delay adjustment
Rotate the knob of the delay adjustment potentiometer clockwise, you can also see the sensing delay increasing. The maximum of the sensing delay can reach up to 300s. On the contrary, if rotate it anticlockwise, you can shorten the delay with a minimum of 5s.

##Two Trigger Modes

Choosing different modes by using the jumper cap.

H: Repeatable trigger mode, after sensing the human body, the module outputs high level. During the subsequent delay period, if somebody enters the sensing range,the output will keep being the high level.

L: Non-repeatable trigger mode, outputs high level when it senses the human body. After the delay, the output will change from high level into low level automatically.

