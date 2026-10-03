# RFID RC522 (I2C) with Arduino Uno

The RC522 is an RFID reader that reads 13.56 MHz cards and key fobs from a few centimeters away. Each card has a unique ID, so an Arduino can use it for things like access control, attendance tracking, or triggering an event when a specific card is scanned.

## What you need

- Arduino Uno and USB cable
- RC522 RFID reader, **I2C version** (see [About the RC522 (I2C)](#about-the-rc522-i2c) to check)
- RFID card or key fob (13.56 MHz, usually included with the reader)
- 4 jumper wires
- Arduino IDE

---

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

<img width="1251" height="969" alt="RFID-RC522" src="https://github.com/user-attachments/assets/ad884356-7156-433d-8742-2dd3480bdb78" />


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
