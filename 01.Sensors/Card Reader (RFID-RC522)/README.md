# RFID RC522 (I2C) with Arduino Uno

The RC522 is an RFID reader that reads 13.56 MHz cards and key fobs from a few centimeters away. Each card has a unique ID, so an Arduino can use it for things like access control, attendance tracking, or triggering an event when a specific card is scanned.

## What you need

- Arduino Uno and USB cable
- RC522 RFID reader, **I2C version**
- RFID card or key fob (usually included with the reader)
- 4 jumper wires
- Arduino IDE

---

## Step 1: Check your module

| Your module has... | Version | Use this guide? |
|---|---|---|
| 4–6 pins: VCC, GND, SDA, SCL | I2C | Yes |
| 8 pins, including MOSI and MISO | SPI | No |

> [!WARNING]
> Check the label for the voltage. If it says **3.3V only**, connect VCC to the Uno's **3.3V** pin, not 5V.

---

## Step 2: Install the library

1. In the Arduino IDE, go to **Sketch → Include Library → Manage Libraries**.
2. Search for **RFID_MFRC522v2**.
3. Install **RFID_MFRC522v2 by GithubCommunity**.

---

## Step 3: Wire the module

| RC522 | Uno |
|---|---|
| VCC | 5V (or 3.3V, see Step 1) |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

Leave any other pins (IRQ, RST) unconnected.

<img width="1251" height="969" alt="RFID-RC522" src="https://github.com/user-attachments/assets/ad884356-7156-433d-8742-2dd3480bdb78" />

---

## Step 4: Upload the code

This sketch prints the ID of any card you scan. If the card matches `myCard`, the built-in LED turns on for 2 seconds.

```cpp
#include <Wire.h>
#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>

MFRC522DriverI2C driver{0x28, Wire};  // 0x28 is the reader's I2C address
MFRC522 rfid{driver};

String myCard = "A1B2C3D4";  // Replace with your card's ID (Step 5)

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rfid.PCD_Init();
  pinMode(13, OUTPUT);
  Serial.println("Scan a card");
}

void loop() {
  // Wait until a card is scanned
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Turn the card's ID into text
  String cardID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) cardID += "0";
    cardID += String(rfid.uid.uidByte[i], HEX);
  }
  cardID.toUpperCase();

  Serial.print("Card ID: ");
  Serial.println(cardID);

  // Check if it's your card
  if (cardID == myCard) {
    Serial.println("Access granted");
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
  } else {
    Serial.println("Access denied");
  }

  rfid.PICC_HaltA();  // Stop reading this card
}
```

---

## Step 5: Add your card

1. Open **Tools → Serial Monitor** and set it to **9600**.
2. Hold your card flat on the reader. You'll see:

   ```
   Card ID: 7F3A9C12
   Access denied
   ```

3. Copy your card ID into the code:

   ```cpp
   String myCard = "7F3A9C12";
   ```

4. Upload again and scan the card. You'll see `Access granted` and the LED turns on.

Replace the LED with a servo, buzzer, or relay to make something happen when your card is scanned.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Nothing happens when you scan | Check SDA → A4 and SCL → A5. Hold the card flat, within 1–2 cm. |
| Still nothing | Your reader may use a different address. Run the I2C scanner below. |
| Some cards never read | The RC522 only reads 13.56 MHz cards. Thick white 125 kHz ID cards won't work. |
| Always "Access denied" | Check `myCard` matches the Serial Monitor exactly, with no spaces. |
| `MFRC522v2.h: No such file` | The library isn't installed. Redo Step 2. |

<details>
<summary><b>I2C scanner</b> (click to open)</summary>

Upload this, then open the Serial Monitor at 9600. It prints your reader's address.

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(address, HEX);
    }
  }
}

void loop() {}
```

If it prints an address other than `0x28`, change `0x28` in the Step 4 code to match. If it prints nothing, recheck your wiring.

</details>

---

## References

- [RFID_MFRC522v2 library](https://docs.arduino.cc/libraries/rfid_mfrc522v2/)
