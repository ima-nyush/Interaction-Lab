# RFID RC522 (I2C) with Arduino Uno

A step-by-step guide to wiring an I2C version of the RC522 RFID reader to an Arduino Uno, reading card IDs, and building a simple card-based access check.

## Contents

- [What you need](#what-you-need)
- [Key terms](#key-terms)
- [About the RC522 (I2C)](#about-the-rc522-i2c)
- [Step 1: Install the library](#step-1-install-the-library)
- [Step 2: Wire the module](#step-2-wire-the-module)
- [Step 3: Find the I2C address](#step-3-find-the-i2c-address)
- [Step 4: Read a card](#step-4-read-a-card)
- [Step 5: Allow only specific cards](#step-5-allow-only-specific-cards)
- [Troubleshooting](#troubleshooting)
- [References](#references)

---

## What you need

- Arduino Uno and USB cable
- RC522 RFID reader, **I2C version** (see [About the RC522 (I2C)](#about-the-rc522-i2c) to check)
- RFID card or key fob (13.56 MHz, usually included with the reader)
- 4 jumper wires
- Arduino IDE

---

## Key terms

| Term | Meaning |
|---|---|
| **RFID** | Radio-Frequency Identification. The reader sends out a radio signal; a card held near it answers with its ID. No battery in the card. |
| **Tag / card** | The card or key fob you scan. Also called a PICC in the library code. |
| **UID** | The card's ID number, written in hexadecimal (e.g. `A1 B2 C3 D4`). Usually 4 or 7 bytes. |
| **I2C** | A way for devices to talk using 2 wires: SDA (data) and SCL (clock). Many devices can share the same 2 wires. |
| **I2C address** | Each I2C device has a number (e.g. `0x28`) so the Arduino knows which device it's talking to. |
| **Hexadecimal (hex)** | A way of writing numbers using 0–9 and A–F. `0x28` means 28 in hex (40 in normal numbers). |

---

## About the RC522 (I2C)

The RC522 reads and writes 13.56 MHz RFID cards (MIFARE type) from about 1–5 cm away.

The RC522 chip can use SPI, I2C, or UART, but each module board is wired for only one. This guide is for boards wired for **I2C**.

### Check which module you have

| Module | Pins | Use this guide? |
|---|---|---|
| **I2C version** | 4–6 pins: VCC, GND, SDA, SCL (sometimes also IRQ, RST) | Yes |
| **Standard blue board** | 8 pins: SDA, SCK, MOSI, MISO, IRQ, GND, RST, 3.3V | No. This is the SPI version. |

> [!WARNING]
> The standard blue 8-pin board also has a pin labeled **SDA**, but on that board it's an SPI pin, not I2C. If your board has MOSI and MISO pins, it's SPI and this guide won't work with it.

### Power

I2C RC522 modules vary. Check the label or the seller's page:

- Says **3.3V–5V** → use the Uno's **5V** pin.
- Says **3.3V** only → use the Uno's **3.3V** pin. 5V can damage it.
- No label → use **3.3V** to be safe.

---

## Step 1: Install the library

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries**.
3. Search for **RFID_MFRC522v2**.
4. Install **RFID_MFRC522v2 by GithubCommunity**.

> [!NOTE]
> Don't use the older **MFRC522** library by miguelbalboa. It only supports SPI.

---

## Step 2: Wire the module

| RC522 (I2C) | Uno |
|---|---|
| VCC | 5V or 3.3V (see [Power](#power)) |
| GND | GND |
| SDA | A4 |
| SCL | A5 |
| IRQ | Not connected |
| RST | Not connected |

The Uno's I2C pins are **A4 (SDA)** and **A5 (SCL)**. They're also available on the two unlabeled pins above AREF, near the USB port. Either location works; they're the same connection.

The library resets the module through software, so RST isn't needed. If the module doesn't respond in Step 3, connect RST to 3.3V.

<img width="625" height="425" alt="RFID-RC522" src="https://github.com/user-attachments/assets/230b4ae1-df72-476c-b994-753bfdab924c" />

---

## Step 3: Find the I2C address

The library needs your module's I2C address. Most RC522 I2C modules use `0x28`, but check before moving on.

### 3.1 Upload the scanner

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Scanning I2C bus...");

  int found = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      if (address < 0x10) Serial.print("0");
      Serial.println(address, HEX);
      found++;
    }
  }

  if (found == 0) {
    Serial.println("No devices found. Check wiring.");
  }
}

void loop() {}
```

### 3.2 Check the output

Open **Tools → Serial Monitor** at **9600**. You should see:

```
Scanning I2C bus...
Device found at 0x28
```

Write down the address. If it's not `0x28`, you'll change one line in the next steps.

---

## Step 4: Read a card

This sketch prints the UID of each card you scan.

### 4.1 Upload the sketch

```cpp
#include <Wire.h>
#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522Debug.h>

const uint8_t RFID_ADDRESS = 0x28;  // Change if Step 3 showed a different address

MFRC522DriverI2C driver{RFID_ADDRESS, Wire};
MFRC522 mfrc522{driver};

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mfrc522.PCD_Init();

  // Prints the reader's firmware version. Confirms the Arduino can talk to it.
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
  Serial.println("Scan a card");
}

void loop() {
  // Wait for a new card
  if (!mfrc522.PICC_IsNewCardPresent()) return;

  // Read the card's UID
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.print("Card UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Stop reading this card so it isn't read again immediately
  mfrc522.PICC_HaltA();
}
```

### 4.2 Check the output

Open the Serial Monitor at **9600**. You should see the firmware version first:

```
Firmware Version: 0x92 = v2.0
Scan a card
```

Hold a card flat against the reader. You should see:

```
Card UID: A1 B2 C3 D4
```

Scan each of your cards and write down their UIDs. You'll need them in Step 5.

If you see `WARNING: Communication failure` instead of a firmware version, see [Troubleshooting](#troubleshooting).

### 4.3 How the code works

| Part | What it does |
|---|---|
| `MFRC522DriverI2C driver{...}` | Tells the library to use I2C at your module's address. |
| `PICC_IsNewCardPresent()` | Checks if a card is near the reader. |
| `PICC_ReadCardSerial()` | Reads the card's UID. |
| `mfrc522.uid.uidByte[]` | The UID, stored as a list of bytes. |
| `mfrc522.uid.size` | How many bytes are in the UID (usually 4 or 7). |
| `PICC_HaltA()` | Tells the card to stop responding until it's removed and scanned again. |

---

## Step 5: Allow only specific cards

This sketch checks each scanned card against a list. Allowed cards turn on the built-in LED (pin 13) for 2 seconds.

### 5.1 Upload the sketch

Replace the UIDs in `allowedCards` with the ones you wrote down in Step 4. Use uppercase letters and single spaces, exactly as the Serial Monitor showed them.

```cpp
#include <Wire.h>
#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522Debug.h>

const uint8_t RFID_ADDRESS = 0x28;

MFRC522DriverI2C driver{RFID_ADDRESS, Wire};
MFRC522 mfrc522{driver};

// Replace with your card UIDs from Step 4
const char* allowedCards[] = {
  "A1 B2 C3 D4",
  "11 22 33 44"
};
const int NUM_CARDS = sizeof(allowedCards) / sizeof(allowedCards[0]);

const int LED = 13;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mfrc522.PCD_Init();
  pinMode(LED, OUTPUT);
  Serial.println("Scan a card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String uid = readUID();
  Serial.print("Card UID: ");
  Serial.println(uid);

  if (isAllowed(uid)) {
    Serial.println("Access granted");
    digitalWrite(LED, HIGH);
    delay(2000);
    digitalWrite(LED, LOW);
  } else {
    Serial.println("Access denied");
  }

  mfrc522.PICC_HaltA();
}

// Turns the UID bytes into text like "A1 B2 C3 D4"
String readUID() {
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uid += " ";
  }
  uid.toUpperCase();
  return uid;
}

// Checks if the UID is in the allowed list
bool isAllowed(String uid) {
  for (int i = 0; i < NUM_CARDS; i++) {
    if (uid == allowedCards[i]) return true;
  }
  return false;
}
```

### 5.2 Test it

1. Open the Serial Monitor at 9600.
2. Scan an allowed card. The Serial Monitor shows `Access granted` and the LED turns on for 2 seconds.
3. Scan a card not in the list. The Serial Monitor shows `Access denied`.

Replace the LED with a servo, relay, or buzzer to build a lock, a door chime, or a card-triggered event.

> [!NOTE]
> Card UIDs can be copied with cheap tools. This is fine for projects and installations, but don't use UID checks to protect anything valuable.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| I2C scanner finds no devices | Check SDA → A4 and SCL → A5 (not swapped). Check power and ground. Try connecting RST to 3.3V. |
| `WARNING: Communication failure` | The address in the code doesn't match Step 3. Update `RFID_ADDRESS`. |
| Scanner finds the device, but no cards are detected | Hold the card flat and within 1–2 cm of the reader. Try the other card or fob. |
| Some cards never read | The card may be the wrong type. The RC522 reads 13.56 MHz cards only. 125 kHz cards (common thick white ID cards) won't work. |
| UID doesn't match in Step 5 | Check the UID in `allowedCards` uses uppercase letters and single spaces, e.g. `"0A 1B 2C 3D"`. |
| Compile error: `MFRC522v2.h: No such file` | The library isn't installed. Redo Step 1. |
| Module has MOSI/MISO pins | It's the SPI version. This guide doesn't apply; it needs different wiring and code. |

---

## References

- [RFID_MFRC522v2 library (Arduino docs)](https://docs.arduino.cc/libraries/rfid_mfrc522v2/)
- [RFID_MFRC522v2 source and examples](https://github.com/OSSLibraries/Arduino_MFRC522v2)
- [Arduino Wire (I2C) reference](https://docs.arduino.cc/language-reference/en/functions/communication/wire/)
