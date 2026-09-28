# NL-16 Bluetooth Module with Arduino Uno

A step-by-step guide to wiring, configuring, and using the NULLLAB NL-16 BLE module with an Arduino Uno.

> [!NOTE]
> NULLLAB has not published a standalone NL-16 datasheet. The defaults and AT commands here come from the docs for NULLLAB's BLE-Uno board, which uses the same chip (CH571F) and firmware features. Confirm your module's settings with `AT+ALL` (Step 2).

## Contents

- [What you need](#what-you-need)
- [Key terms](#key-terms)
- [About the NL-16](#about-the-nl-16)
- [Step 1: Choose your setup](#step-1-choose-your-setup)
- [Step 2: Configure the module](#step-2-configure-the-module)
- [Step 3: Wire for a project (Setup A)](#step-3-wire-for-a-project-setup-a)
- [Step 4: Control an LED from your phone](#step-4-control-an-led-from-your-phone)
- [Step 5: Connect from a web browser (optional)](#step-5-connect-from-a-web-browser-optional)
- [Step 6: Upload code wirelessly (Setup B)](#step-6-upload-code-wirelessly-setup-b)
- [Step 7: Connect two NL-16 modules (optional)](#step-7-connect-two-nl-16-modules-optional)
- [Troubleshooting](#troubleshooting)
- [References](#references)

---

## What you need

- Arduino Uno and USB cable
- NL-16 module
- 4–5 jumper wires
- Arduino IDE (1.8.8 or newer)
- A phone with a BLE app: **LightBlue** or **nRF Connect** (both free, iOS and Android)

---

## Key terms

| Term | Meaning |
|---|---|
| **BLE** | Bluetooth Low Energy. A different type of Bluetooth from the "classic" kind used by headphones and the HC-05. |
| **TX / RX** | Transmit / Receive. Data leaves a device on TX and arrives on RX, so one device's TX connects to the other's RX. |
| **Baud rate** | Serial communication speed. Both sides must use the same value or you get garbage text. |
| **AT command** | A text command sent over serial to change module settings (name, speed, role). |
| **Service / Characteristic** | How BLE organizes data. Think of a service as a folder and a characteristic as a file inside it that you read from or write to. |

---

## About the NL-16

- Chip: CH571F, Bluetooth 4.2 **BLE only**
- Works with iOS and Android phones through a BLE app
- **Does not** work with Bluetooth Classic devices (HC-05, HC-06, older Bluetooth 2.0 gear)
- **Cannot** be paired from your phone's Bluetooth settings menu. Always connect through a BLE app.

### Pins

| Pin | Function |
|---|---|
| STAT/D-RST | Connection status output; also used to reset the Arduino for wireless upload |
| RXD | Receives data (connect to Arduino TX) |
| TXD | Sends data (connect to Arduino RX) |
| GND | Ground |
| +5V | Power |

### BLE IDs

You'll need these when connecting from a phone or browser.

| Item | UUID | Use |
|---|---|---|
| Service | `FFE0` | The module's main service |
| Data characteristic | `FFE1` | Send/receive your data |
| AT characteristic | `FFE2` | Send AT commands over Bluetooth |

---

## Step 1: Choose your setup

There are two ways to wire the module. Pick based on what you're doing.

| Setup | Pins | Use it for |
|---|---|---|
| **A. SoftwareSerial** | D2, D3 | Most projects. Keeps USB Serial Monitor free for debugging. |
| **B. Hardware serial** | D0, D1 | Wireless code upload (Step 6). |

Start with Setup A. First, configure the module (Step 2).

---

## Step 2: Configure the module

You'll use the Uno as a USB-to-serial adapter so your computer can talk to the module directly.

### 2.1 Upload an empty sketch

Upload this to the Uno. It stops the Uno's own chip from using the serial pins.

```cpp
void setup() {}
void loop() {}
```

### 2.2 Wire for configuration

| NL-16 | Uno |
|---|---|
| +5V | 5V |
| GND | GND |
| TXD | pin 1 (TX) |
| RXD | pin 0 (RX) |

This looks reversed from normal wiring. It's correct: in this mode the computer's signals pass through the Uno's pins, so TX goes to TX.

### 2.3 Open Serial Monitor

1. Tools → Serial Monitor
2. Set baud rate to **115200** (the default). If you see nothing, try 9600.
3. Set line ending to **Both NL & CR**.

### 2.4 Test it

Type `AT` and press Enter. You should see `OK`.

Then type `AT+ALL` to see all current settings.

### 2.5 AT command rules

- Every command must end with a line break (the "Both NL & CR" setting handles this).
- Commands are **case-sensitive**. Use uppercase as shown.
- Commands only work when **nothing is connected over Bluetooth**. Disconnect your phone first.

### 2.6 Common commands

| Command | What it does |
|---|---|
| `AT` | Test connection. Replies `OK`. |
| `AT+ALL` | Show all settings |
| `AT+NAME=MyDevice` | Change the name shown when scanning |
| `AT+BAUD=0` | Set baud rate (0=9600, 1=19200, 2=38400, 3=57600, 4=115200) |
| `AT+MAC` | Show the module's address |
| `AT+ROLE=1` | Slave mode (default; phone connects to module) |
| `AT+ROLE=0` | Master mode (module connects to another module) |
| `AT+SETTING=DEFAULT` | Factory reset |

### 2.7 Set the baud rate

- **For Setup A (SoftwareSerial):** send `AT+BAUD=0` to set 9600. SoftwareSerial is unreliable at 115200.
- **For Setup B (wireless upload):** leave it at 115200.

After changing the baud rate, switch the Serial Monitor to the new rate.

---

## Step 3: Wire for a project (Setup A)

| NL-16 | Uno |
|---|---|
| +5V | 5V |
| GND | GND |
| TXD | D2 |
| RXD | D3 |

> [!WARNING]
> The CH571F chip runs at 3.3V. If your module has no visible voltage regulator or level-shifting parts, add a voltage divider on the D3 → RXD wire (1kΩ from D3 to RXD, 2kΩ from RXD to GND). It costs nothing and protects the module.

---

## Step 4: Control an LED from your phone

### 4.1 Upload the sketch

This turns the Uno's built-in LED (pin 13) on and off when you send `on` or `off`.

```cpp
#include <SoftwareSerial.h>

SoftwareSerial ble(2, 3);  // RX = D2 (from module TXD), TX = D3 (to module RXD)
const int LED = 13;
String buf;
unsigned long lastByte = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  // Serial Monitor
  ble.begin(9600);     // Module; must match AT+BAUD
  Serial.println("Ready");
}

void loop() {
  // Collect incoming characters
  while (ble.available()) {
    buf += (char)ble.read();
    lastByte = millis();
  }

  // Phone apps often don't send a newline,
  // so treat 20 ms of no data as the end of a message
  if (buf.length() && millis() - lastByte > 20) {
    buf.trim();
    Serial.print("Got: ");
    Serial.println(buf);

    if (buf == "on") {
      digitalWrite(LED, HIGH);
      ble.println("LED on");
    } else if (buf == "off") {
      digitalWrite(LED, LOW);
      ble.println("LED off");
    }

    buf = "";
  }
}
```

### 4.2 Connect from your phone

1. Open **LightBlue** or **nRF Connect**.
2. On Android, turn on Location and allow the app location access. Android requires this for BLE scanning.
3. Scan and tap your module to connect.
4. Open service `FFE0`, then characteristic `FFE1`.
5. Turn on **Notify** (or "Subscribe") to receive replies.
6. Choose **Write**, set format to **UTF-8 / Text**, and send `on`.

The LED turns on, the Serial Monitor shows `Got: on`, and your phone receives `LED on`. Send `off` to turn it off.

### 4.3 Sending data to the phone

Anything you `ble.print()` shows up on the phone (with Notify turned on). Two limits:

- Keep each message **under 64 bytes**. Longer messages can lose data.
- Wait **at least 100 ms** between messages.

---

## Step 5: Connect from a web browser (optional)

Chrome supports Web Bluetooth, so a web page (including a p5.js sketch) can talk to the module.

```js
async function connect() {
  const device = await navigator.bluetooth.requestDevice({
    filters: [{ services: [0xffe0] }]
  });
  const server = await device.gatt.connect();
  const service = await server.getPrimaryService(0xffe0);
  const ch = await service.getCharacteristic(0xffe1);

  // Receive
  await ch.startNotifications();
  ch.addEventListener("characteristicvaluechanged", e => {
    console.log(new TextDecoder().decode(e.target.value));
  });

  // Send
  await ch.writeValue(new TextEncoder().encode("on"));
}
```

Requirements:

- `connect()` must run from a button click. Browsers block it otherwise.
- The page must be served over `https://` or `localhost`.
- Use Chrome or Edge. Safari and Firefox don't support Web Bluetooth.

---

## Step 6: Upload code wirelessly (Setup B)

The NL-16 can upload sketches to the Uno over Bluetooth, with no USB cable.

### 6.1 Requirements

- Module baud rate: **115200** (the Uno bootloader requires it)
- An Android phone
- NULLLAB's upload app: [arduino_ble_flash_demo](https://github.com/nulllaborg/arduino_ble_flash_demo)

### 6.2 Wiring

| NL-16 | Uno |
|---|---|
| +5V | 5V |
| GND | GND |
| TXD | D0 (RX) |
| RXD | D1 (TX) |
| STAT/D-RST | RESET |

> [!IMPORTANT]
> Pins 0 and 1 are shared with USB. **Unplug the module's TXD/RXD wires before uploading over USB**, or the upload will fail.

### 6.3 Upload

1. In Arduino IDE: Sketch → Export Compiled Binary. This creates a `.hex` file in your sketch folder.
2. Copy the `.hex` file to your phone.
3. Open the NULLLAB app, connect to the module, select the file, and upload.

In your sketch, use `Serial` (not SoftwareSerial) to talk to the module in this setup, at 115200.

---

## Step 7: Connect two NL-16 modules (optional)

One module stays in slave mode (the default). Configure the other as master using the Step 2 setup:

1. `AT+ROLE=0` — set to master
2. `AT+SCAN` — list nearby devices with an index number
3. `AT+CONN=1` — connect by index, **or** `AT+CON=xx:xx:xx:xx:xx:xx` to connect by MAC address
4. `AT+AUTOCON=1` — reconnect automatically on power-up (takes effect after restart)

Once connected, text printed to one module comes out of the other module's TXD.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| No `OK` after typing `AT` | Try baud 115200, then 9600. Check line ending is "Both NL & CR". Check TX/RX wiring for the setup you're using. |
| AT commands stopped working | A device is connected. Disconnect it. |
| Garbled text | Baud rates don't match, or SoftwareSerial is running too fast. Set the module to 9600. |
| Phone can't find the module | Use a BLE app, not phone Settings. On Android, turn on Location. |
| Connected but no data arrives | Check you're writing to `FFE1` as text, and that Notify is on. |
| USB upload fails | Disconnect the module from pins 0 and 1. |
| Messages cut off or missing | Keep messages under 64 bytes and wait 100 ms between them. |

---

## References

- [NULLLAB BLE-Uno docs](https://github.com/nulllaborg/ble-uno) (same chip and AT commands)
- [Wireless upload app](https://github.com/nulllaborg/arduino_ble_flash_demo)
- [Web Bluetooth API (MDN)](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API)
