```C++
#define PIN_A 2
#define PIN_B 3

int delta = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_A), shaft_moved, FALLING);
}

void loop() {
  int old = delta;
  delta = 0;
  Serial.println(10000+old);
  delay(100);
}

void shaft_moved() {
  int pinb_value = digitalRead(PIN_B);
  if (pinb_value == HIGH) {
    delta = delta - 1;
  } else {
    delta = delta + 1;
  }
}

```
