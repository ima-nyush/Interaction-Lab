```C++
//Pinouts
int clkPin = 2;
int dtPin = 3;
int swPin = 4;
//value
int val;
//max rate the sensor can trigger in uS
//this helps with mechanical bounce
int pollRate = 2500;
unsigned long lastPollTime;

void setup() {
  Serial.begin(9600);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(clkPin), shaft_moved, RISING);
}

void loop() {
  Serial.println(val);
  delay(100);
}

void shaft_moved() {
  if (micros() >= lastPollTime + pollRate) {
    int dtVal = digitalRead(dtPin);
    lastPollTime = micros();
    if (dtVal == HIGH) {
      val -= 1;
    } else {
      val += 1;
    }
  }
}
```
