# DS1302 Real-Time Clock with Arduino Uno

A step-by-step guide to wiring, setting, and reading the time from a DS1302 real-time clock (RTC) module with an Arduino Uno.

## Contents

- [What you need](#what-you-need)
- [Key terms](#key-terms)
- [About the DS1302](#about-the-ds1302)
- [Step 1: Install the library](#step-1-install-the-library)
- [Step 2: Wire the module](#step-2-wire-the-module)
- [Step 3: Set and read the time](#step-3-set-and-read-the-time)
- [Step 4: Set the time manually (optional)](#step-4-set-the-time-manually-optional)
- [Step 5: Use the time in a project](#step-5-use-the-time-in-a-project)
- [Troubleshooting](#troubleshooting)
- [References](#references)

---

## What you need

- Arduino Uno and USB cable
- DS1302 RTC module
- CR2032 coin battery
- 5 female-to-male jumper wires
- Arduino IDE

---

## Key terms

| Term | Meaning |
|---|---|
| **RTC** | Real-Time Clock. A chip that keeps track of the date and time, even when the Arduino is off. |
| **Backup battery** | The coin battery on the module. It keeps the clock running when the Arduino has no power. |
| **Library** | Pre-written code you install so you don't have to write the low-level communication yourself. |
| **Serial Monitor** | The window in the Arduino IDE that shows text sent from the Arduino. |

---

## About the DS1302

The Arduino has no built-in clock. It only knows how long it has been running since it was last powered on or reset. When it loses power, that count starts over.

The DS1302 solves this. It counts seconds, minutes, hours, day, month, and year on its own, powered by its coin battery. The Arduino asks it for the time whenever it needs it.

### Pins

| Pin | Also labeled | Function |
|---|---|---|
| VCC | | Power (5V from the Uno) |
| GND | | Ground |
| CLK | SCLK | Clock signal for communication |
| DAT | IO | Data line |
| RST | CE | Chip enable (turns communication on/off) |

> [!NOTE]
> The module's **RST** pin is not connected to the Arduino's RESET pin. Despite the name, it's a normal data pin and goes to a digital pin on the Uno.

![NL-16 wiring diagram](UNO_DS1302_wiring.png)
---

## Step 1: Install the library

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for **Rtc by Makuna**.
4. Click **Install**.

There are several DS1302 libraries. This guide uses Rtc by Makuna because it's actively maintained and its example sketch uses the same wiring as this guide.

---

## Step 2: Wire the module

### 2.1 Insert the battery

Put the CR2032 in the holder, flat side (+) facing up. Without a battery, the module forgets the time every time the Arduino loses power.

### 2.2 Connect the wires

| DS1302 | Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| CLK | D5 |
| DAT | D4 |
| RST | D2 |

You can use other digital pins. If you do, change the pin numbers in the code to match.

---

## Step 3: Set and read the time

This sketch does two things:

1. **The first time it runs**, it sets the RTC to the time your computer compiled the sketch.
2. **Every time after**, it reads the time from the RTC and prints it once per second.

### 3.1 Upload the sketch

```cpp
#include <ThreeWire.h>
#include <RtcDS1302.h>

// Pin order: DAT, CLK, RST
ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(9600);
  Rtc.Begin();

  // Date and time this sketch was compiled on your computer
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  // Allow writing to the RTC
  if (Rtc.GetIsWriteProtected()) {
    Rtc.SetIsWriteProtected(false);
  }

  // Start the clock if it's stopped
  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was stopped. Starting it.");
    Rtc.SetIsRunning(true);
  }

  // Set the time if the RTC has no valid time (first use or dead battery)
  if (!Rtc.IsDateTimeValid()) {
    Serial.println("RTC time invalid. Setting to compile time.");
    Rtc.SetDateTime(compiled);
  }

  // Set the time if the RTC is behind the compile time
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is behind. Updating to compile time.");
    Rtc.SetDateTime(compiled);
  }
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();

  if (!now.IsValid()) {
    Serial.println("RTC lost the time. Check the battery and wiring.");
  } else {
    printDateTime(now);
  }

  delay(1000);
}

// Prints the time as YYYY-MM-DD HH:MM:SS
void printDateTime(const RtcDateTime& dt) {
  char text[20];
  snprintf(text, sizeof(text), "%04u-%02u-%02u %02u:%02u:%02u",
           dt.Year(), dt.Month(), dt.Day(),
           dt.Hour(), dt.Minute(), dt.Second());
  Serial.println(text);
}
```

### 3.2 Check the output

Open **Tools → Serial Monitor** and set the baud rate to **9600**. You should see:

```
2026-09-28 14:30:05
2026-09-28 14:30:06
2026-09-28 14:30:07
```

The time will be a few seconds behind your computer. That's the time it took to compile and upload.

### 3.3 Test the battery backup

1. Unplug the Arduino.
2. Wait a minute.
3. Plug it back in and open the Serial Monitor.

The time should show the correct current time, not the time you unplugged it. That means the battery kept the clock running.

---

## Step 4: Set the time manually (optional)

Use this if you want to set an exact time instead of the compile time.

Replace the `setup()` function in Step 3 with this. Change the numbers to your target time, upload once, then upload the Step 3 sketch again.

```cpp
void setup() {
  Serial.begin(9600);
  Rtc.Begin();
  Rtc.SetIsWriteProtected(false);
  Rtc.SetIsRunning(true);

  // Year, month, day, hour, minute, second (24-hour time)
  Rtc.SetDateTime(RtcDateTime(2026, 9, 28, 14, 30, 0));

  Serial.println("Time set.");
}
```

> [!IMPORTANT]
> Upload the Step 3 sketch again right after. If you leave this sketch on the Uno, it resets the clock to the same time every time the Arduino powers on.

---

## Step 5: Use the time in a project

Once you can read the time, you can make things happen at specific times. This example turns on the built-in LED (pin 13) between 8:00 and 18:00.

Add this to the end of `loop()` in the Step 3 sketch:

```cpp
  int hour = now.Hour();

  if (hour >= 8 && hour < 18) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
```

And add this line inside `setup()`:

```cpp
  pinMode(13, OUTPUT);
```

Replace the LED with a relay, buzzer, or servo to build timers, alarms, or schedules.

### Available time values

| Function | Returns |
|---|---|
| `now.Year()` | Year (e.g. 2026) |
| `now.Month()` | 1–12 |
| `now.Day()` | 1–31 |
| `now.Hour()` | 0–23 |
| `now.Minute()` | 0–59 |
| `now.Second()` | 0–59 |
| `now.DayOfWeek()` | 0–6 (0 = Sunday) |

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Time shows `2000-01-01` or random numbers | Check wiring. Confirm the pin numbers in `ThreeWire myWire(4, 5, 2)` match your wires (order is DAT, CLK, RST). |
| Time doesn't change (stuck on one second) | The clock isn't running. Make sure `Rtc.SetIsRunning(true)` runs in `setup()`. |
| Time resets every time the Arduino restarts | No battery, dead battery, or battery inserted upside down. Or the Step 4 sketch is still on the Uno. |
| "RTC lost the time" message | Battery is dead or missing. Replace it and re-upload the Step 3 sketch. |
| Time is off by a few minutes after a few weeks | Normal. The DS1302 drifts over time. Re-set it, or switch to a DS3231 module if you need higher accuracy. |
| Compile error: `RtcDS1302.h: No such file` | The library isn't installed. Redo Step 1. |

---

## References

- [Rtc by Makuna library](https://github.com/Makuna/Rtc)
- [DS1302 example sketch](https://github.com/Makuna/Rtc/blob/master/examples/DS1302_Simple/DS1302_Simple.ino)
- [Rtc library wiki](https://github.com/Makuna/Rtc/wiki)
