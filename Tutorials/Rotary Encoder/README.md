```C++
int clkPin = 7;
int dtPin = 6;
int swPin = 5;

int count; //count from original position (0)
int dir; //1 = clockwise 2 = counter-clockwise
int button;
int pollRate = 25000;  //in uS


void setup() {
  Serial.begin(9600);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
}

void loop() {
  rotaryEncoder(clkPin, dtPin, pollRate);
  Serial.print(count);
  Serial.print(",");
  Serial.print(dir);
  Serial.print(",");
  Serial.println(button);
}

void rotaryEncoder(int cp, int dp, int pr) {
  unsigned long timeStarted = micros();
  int clkStateOld = digitalRead(cp);

  //print yes if button is pressed, print no if not
  if (digitalRead(swPin) == LOW) {
    button = 1;
  } else {
    button = 0;
  }
  //give window of time(default 25ms) to register pulse
  while (micros() <= timeStarted + pr) {
    int clkState = digitalRead(cp);
    int dtState = digitalRead(dp);
    if (clkState == HIGH && clkState != clkStateOld) {  //rising
      if (dtState == LOW) {
        count++;
        dir = 1;
        Serial.println(count);
        break;
      } else {
        count--;
        dir = 2;
        break;
      }
    }
    clkStateOld = clkState;
  }
}

```
