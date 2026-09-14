# Mic Sensor_MAX4466
Source：https://lastminuteengineers.com/max4466-arduino-tutorial/

It’s a well-designed module with flexible supply voltage and adjustable gain, making it suitable for a wide range of audio applications. This module is particularly suited for projects like real-time voice changers, audio recording/sampling, and audio-reactive projects that use Fast Fourier Transform (FFT) algorithms.


## MAX4466 Module Pinout

The module has three pins.

<img width="439" height="348" alt="MAX4466-Module-Pinout" src="https://github.com/user-attachments/assets/708d14e4-7b00-4afa-b902-b0d7ec861f6b" />

VCC is the power supply pin that accepts 2.4V to 5.5V DC voltage.
GND is the ground pin.
OUT is the analog output pin that delivers the amplified sound signal. 
Please note that the output will have a DC bias equal to VCC/2, so when it’s perfectly quiet, the voltage will remain steady at a VCC/2 level.


## Wiring a MAX4466 Module to an Arduino

The wiring is relatively simple. There are only three wires to connect: two for power and one for output.

The VCC of the MAX4466 module can range between 2.4-5VDC. For optimal performance, it’s recommended to use the 3.3V pin as it provides the “quietest” supply on the Arduino. Therefore, power the sensor with 3.3V and connect ground to ground. Then connect the output to an analog input pin. In this example we’ll use pin A0.

The wiring is shown in the image below.

<img width="587" height="335" alt="Wiring-MAX4466-Module-to-Arduino" src="https://github.com/user-attachments/assets/76987b5f-71e7-45d9-ba27-3269727c8f03" />


## Arduino Example Code – Measuring Sound Levels

The output from the MAX4466 amplifier is simply a varying voltage. To measure the sound level, we need to take multiple measurements to find the minimum and maximum values, or, in technical terms, the ‘peak-to-peak amplitude,’ of the signal.

In the example code below, we chose a sample window of 50 milliseconds. This duration is sufficient to measure sound levels for frequencies as low as 20 Hz, which is the lowest frequency that humans can hear. After finding the minimum and maximum samples, we compute the difference (to get the peak-to-peak amplitude of the sound) and convert it to volts. The output is then printed to the serial monitor.

```C++
const int sampleWindow = 50;  // Sample window width in mS (50 mS = 20Hz)
int const AMP_PIN = A0;       // Preamp output pin connected to A0
unsigned int sample;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS and then plot data
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AMP_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  Serial.println(peakToPeak);
  //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  //Serial.println(volts);
}
```

Once you have uploaded the sketch, open the serial monitor and set the baud rate to 9600. Now, try snapping your fingers near the sensor; you will observe a change in the readings.

<img width="616" height="350" alt="MAX4466-Serial-Monitor-Output" src="https://github.com/user-attachments/assets/33e86fcb-29c1-4cff-a7a1-5e8904651972" />

Serial data can be hard to visualize if you’re only looking at values. If you are using the Arduino IDE v1.6.6+, there is an option to view the data on a graph using the Arduino Serial Plotter.

In the Arduino IDE, choose Tools > Serial Plotter. You should observe a waveform similar to the image below, when you snap your fingers near the sensor.

<img width="617" height="402" alt="MAX4466-Serial-Plotter-Output" src="https://github.com/user-attachments/assets/a4afcb64-0b53-4174-aa6b-d84b46da33f4" />


![1-ezgif com-video-to-gif-converter (1)](https://github.com/user-attachments/assets/4958474f-c219-4c29-afd7-45417462fde6)

