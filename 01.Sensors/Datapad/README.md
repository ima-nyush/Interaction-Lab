# 4x4 Keypad with Arduino Uno

A 4x4 keypad is a 16-button grid that connects to an Arduino Uno with 8 wires (4 rows, 4 columns). The Uno scans the rows and columns to tell which key is pressed, which makes it useful for number entry, menus, and code locks.

## What you need

- Arduino Uno and USB cable
- 4x4 membrane keypad
- 8 jumper wires
- Arduino IDE

---

## How it works

```
+---+---+---+---+
| 1 | 2 | 3 | A |   Row 1
+---+---+---+---+
| 4 | 5 | 6 | B |   Row 2
+---+---+---+---+
| 7 | 8 | 9 | C |   Row 3
+---+---+---+---+
| * | 0 | # | D |   Row 4
+---+---+---+---+
 Col1 Col2 Col3 Col4
```

Each key sits where a row meets a column. Pressing **6** connects Row 2 to Column 3, and the Arduino uses that to know which key you pressed.

---

## Step 1: Install the library

1. In the Arduino IDE, go to **Sketch → Include Library → Manage Libraries**.
2. Search for **Keypad**.
3. Install **Keypad by Mark Stanley, Alexander Brevig**.

---

## Step 2: Wire the keypad

Hold the keypad face up with the cable at the bottom. Count the pins from left to right.

| Keypad pin | Uno pin |
|---|---|
| 1 | D9 |
| 2 | D8 |
| 3 | D7 |
| 4 | D6 |
| 5 | D5 |
| 6 | D4 |
| 7 | D3 |
| 8 | D2 |

No power or ground wire is needed.

<img width="795" height="1509" alt="image" src="https://github.com/user-attachments/assets/85e5d0a2-7c29-457e-b86f-58b1a8090982" />

---

## Step 3: Upload the code

This sketch prints every key you press. If you type the code `1234` and press `#`, the built-in LED turns on for 2 seconds.

```cpp
#include <Keypad.h>

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {9, 8, 7, 6};
byte colPins[4] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

String password = "1234";  // Change this to set your code
String input = "";

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Type the code, then press #");
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;  // No key pressed

  Serial.println(key);

  if (key == '#') {
    // Check the code
    if (input == password) {
      Serial.println("Correct!");
      digitalWrite(13, HIGH);
      delay(2000);
      digitalWrite(13, LOW);
    } else {
      Serial.println("Wrong code");
    }
    input = "";  // Start over
  } else {
    input += key;  // Add the key to what you've typed
  }
}
```

---

## Step 4: Test it

1. Open **Tools → Serial Monitor** and set it to **9600**.
2. Press any key. It shows up in the Serial Monitor.
3. Press `1`, `2`, `3`, `4`, then `#`. You'll see `Correct!` and the LED turns on.
4. Press a different code, then `#`. You'll see `Wrong code`.

To change the code, edit this line and upload again:

```cpp
String password = "1234";
```

Replace the LED with a servo, buzzer, or relay to make something happen when the right code is entered.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Nothing prints | Set the Serial Monitor to 9600. Check the library is installed. |
| Wrong keys print (e.g. `1` shows `D`) | The cable is plugged in reversed. Flip the 8 wires end to end. |
| One row or column doesn't work | A wire is loose. Push it back in. |
| `Keypad.h: No such file` | The library isn't installed. Redo Step 1. |

---

## References

- [Keypad library](https://docs.arduino.cc/libraries/keypad/)
