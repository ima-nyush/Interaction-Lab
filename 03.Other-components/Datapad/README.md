# 4x4 Keypad with Arduino Uno

A 4x4 keypad is a 16-button grid that connects to an Arduino Uno with only 8 wires (4 rows, 4 columns). The Uno scans the rows and columns to tell which key is pressed, which makes it useful for number entry, menus, and code locks.


## What you need

- Arduino Uno and USB cable
- 4x4 membrane keypad (16 keys, 8-pin ribbon connector)
- 8 male-to-male jumper wires
- Arduino IDE

No resistors are needed.


## About the 4x4 keypad

### Layout

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

### How it works

16 keys would normally need 16 wires. The keypad uses 8 instead: 4 for rows and 4 for columns.

Each key sits where one row crosses one column. Pressing a key connects that row to that column. For example, pressing **6** connects Row 2 to Column 3. The Arduino checks every row-column combination many times per second to find which one is connected.

### Pins

Hold the keypad face up with the ribbon cable at the bottom. The 8 pins, left to right, are:

| Pin (left to right) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|
| **Function** | Row 1 | Row 2 | Row 3 | Row 4 | Col 1 | Col 2 | Col 3 | Col 4 |

> [!NOTE]
> The pins are usually unlabeled. The order above is the most common, but some keypads differ. If the wrong keys show up after wiring, see [Troubleshooting](#troubleshooting).

---

## Step 1: Install the library

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for **Keypad**.
4. Install **Keypad by Mark Stanley, Alexander Brevig**.

---

## Step 2: Wire the keypad

Plug jumper wires directly into the keypad's ribbon connector.

| Keypad pin | Function | Uno pin |
|---|---|---|
| 1 | Row 1 | D9 |
| 2 | Row 2 | D8 |
| 3 | Row 3 | D7 |
| 4 | Row 4 | D6 |
| 5 | Col 1 | D5 |
| 6 | Col 2 | D4 |
| 7 | Col 3 | D3 |
| 8 | Col 4 | D2 |

The keypad needs no power or ground wire. The Arduino's pins supply everything.

> [!IMPORTANT]
> Don't use pins D0 and D1. They're used for USB communication, and using them will block uploads and the Serial Monitor.

<img width="218" height="447" alt="UNO_4x4Datapad" src="https://github.com/user-attachments/assets/be5cb8d9-29a4-4762-8b0d-82a76d6adffa" />
---

## Step 3: Read key presses

This sketch prints each key you press to the Serial Monitor.

### 3.1 Upload the sketch

```cpp
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

// The key layout, matching the printed keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};  // Row 1, Row 2, Row 3, Row 4
byte colPins[COLS] = {5, 4, 3, 2};  // Col 1, Col 2, Col 3, Col 4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("Press a key");
}

void loop() {
  char key = keypad.getKey();  // Returns the key, or nothing if no key is pressed

  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);
  }
}
```

## Step 4: Build a code lock

This sketch uses the keypad as a code lock. The built-in LED (pin 13) turns on when the correct code is entered.

| Key | Action |
|---|---|
| `0`–`9` | Enter digits |
| `#` | Submit the code |
| `*` | Clear what you've typed |
| `A` | Lock again (LED off) |

### 4.1 Upload the sketch

Same wiring as Step 2.

```cpp
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String PASSWORD = "1234";  // Change this to set your code
String input = "";
const int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.println("Enter code, then press #");
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;  // No key pressed; check again

  if (key >= '0' && key <= '9') {
    input += key;
    Serial.print('*');  // Show * instead of the digit
  }
  else if (key == '#') {
    Serial.println();
    if (input == PASSWORD) {
      Serial.println("Unlocked");
      digitalWrite(LED, HIGH);
    } else {
      Serial.println("Wrong code");
    }
    input = "";
  }
  else if (key == '*') {
    input = "";
    Serial.println();
    Serial.println("Cleared");
  }
  else if (key == 'A') {
    digitalWrite(LED, LOW);
    input = "";
    Serial.println();
    Serial.println("Locked");
  }
}
```

### 4.2 Test it

1. Open the Serial Monitor at 9600.
2. Type `1`, `2`, `3`, `4`, then `#`. The Serial Monitor shows `Unlocked` and the LED turns on.
3. Press `A`. The LED turns off.
4. Type a wrong code and press `#`. The Serial Monitor shows `Wrong code`.

### 4.3 Ideas for B, C, and D

Keys `B`, `C`, and `D` are unused. Add more `else if` blocks to give them jobs, for example:

```cpp
  else if (key == 'B') {
    // Your code here, e.g. turn on a buzzer, move a servo, change a mode
  }
```

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Nothing prints | Check the Serial Monitor baud rate is 9600. Check the library is installed. |
| Wrong keys print (e.g. pressing `1` prints `D`) | The pin order is reversed. Flip the 8 wires end to end, or reverse the arrays in code: `rowPins = {2, 3, 4, 5}` and `colPins = {6, 7, 8, 9}`. |
| Rows and columns are swapped (e.g. `2` prints `4`) | Swap the `rowPins` and `colPins` arrays in the code. |
| One whole row or column doesn't work | A loose wire. Reseat the jumper for that row or column. |
| Upload fails | A wire is on D0 or D1. Move it. |
| Compile error: `Keypad.h: No such file` | The library isn't installed. Redo Step 1. |

---

## References

- [Keypad library (Arduino docs)](https://docs.arduino.cc/libraries/keypad/)
- [Keypad library source](https://github.com/Chris--A/Keypad)
