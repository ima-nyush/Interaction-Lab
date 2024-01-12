int pingPin = 7;
int echoPin = 6;
unsigned long duration;
unsigned long timeOut = 100000;
bool recPulse = false;
bool firstSend = true;
unsigned long sendPulseStart;
unsigned long pulseStartTime;
unsigned long pulseEndTime;
int oldEcho;

void setup() {
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  microsUltraCM(pingPin, echoPin, timeOut);
}
//check for pulse received, timeout default of 1000000 microseconds (default of pulseIn);
void microsUltraCM(int pp, int ep, unsigned long to) {
  sendPulse(pp);
  receivePulse(ep);
  if (recPulse) {
    firstSend = true;
    recPulse = false;
    pulseStartTime = micros();
    pulseEndTime = micros();

    duration = micros() - sendPulseStart;
    float cm = duration / 29 / 2;
    Serial.println(cm);
  } else if (micros() >= sendPulseStart + to) {
    firstSend = true;
    recPulse = false;
    pulseStartTime = micros();
    pulseEndTime = micros();
  }
}

//micros based pulse (original was 10micros, too short for code to register, extended to 100)
void sendPulse(int pp) {
  if (firstSend) {
    sendPulseStart = micros();
    firstSend = false;
    digitalWrite(pp, LOW);
  } else {
    if (micros() <= sendPulseStart + 100) {
      digitalWrite(pp, HIGH);
    } else if (micros() <= sendPulseStart + 120) {
      digitalWrite(pp, LOW);
    }
  }
}

//micros based pulseIn
void receivePulse(int ep) {
  if (digitalRead(ep) == HIGH && oldEcho == LOW) {
    pulseStartTime = micros();
  } else if (digitalRead(ep) == LOW && oldEcho == HIGH) {
    pulseEndTime = micros();
  }
  if (pulseEndTime >= pulseStartTime + 200) {
    recPulse = true;
  }
  oldEcho = digitalRead(ep);
}