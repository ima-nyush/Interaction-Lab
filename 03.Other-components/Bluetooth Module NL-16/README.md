# NL-16 Bluetooth Module with Arduino Uno

The NL-16 is a Bluetooth Low Energy (BLE) module that lets your phone send and receive messages from an Arduino. You can use it to control things wirelessly or send sensor data to your phone.

> [!NOTE]
> The NL-16 is **BLE only**. You can't pair it from your phone's Bluetooth settings. Always connect through a BLE app.

## What you need

- Arduino Uno and USB cable
- NL-16 module
- 4 jumper wires
- Arduino IDE
- A phone with the free **LightBlue** app (iOS or Android)

---

## Step 1: Wire the module

| NL-16 | Uno |
|---|---|
| +5V | 5V |
| GND | GND |
| TXD | D2 |
| RXD | D3 |

Leave the STAT/D-RST pin unconnected.

<img width="3087" height="1637" alt="Uno_NL16_Bluetooth" src="https://github.com/user-attachments/assets/3ee98b45-abdd-4ef5-b805-8f9730829bb4" />

---

## Step 2: Set up the module (once)

The module comes set to a speed the Uno can't read reliably. This sketch changes it to 9600 and gives your module a name. You only need to run it once per module.

1. Change `BLE-01` to a unique name, so you can find your module when others are nearby.
2. Upload the sketch.
3. Open **Tools → Serial Monitor** and set it to **9600**.

```cpp
#include <SoftwareSerial.h>

SoftwareSerial ble(2, 3);  // D2 = from module TXD, D3 = to module RXD

String deviceName = "BLE-01";  // Give your module a unique name

void setup() {
  Serial.begin(9600);

  // Change the module's speed from 115200 to 9600
  ble.begin(115200);
  ble.print("AT+BAUD=0\r\n");
  delay(500);
  ble.end();

  // Talk to the module at the new speed
  ble.begin(9600);
  sendCommand("AT");
  sendCommand("AT+NAME=" + deviceName);
}

void loop() {}

void sendCommand(String command) {
  ble.print(command + "\r\n");
  delay(300);
  Serial.print(command + " -> ");
  while (ble.available()) {
    Serial.write(ble.read());
  }
  Serial.println();
}
```

You should see `OK` after each command:

```
AT -> OK
AT+NAME=BLE-01 -> OK
```

If you see nothing after the arrows, unplug the USB cable, plug it back in, and open the Serial Monitor again.

After it works, unplug and replug the USB cable so the new name takes effect.

---

## Step 3: Upload the LED sketch

This sketch turns the built-in LED on when your phone sends `1` and off when it sends `0`.

```cpp
#include <SoftwareSerial.h>

SoftwareSerial ble(2, 3);  // D2 = from module TXD, D3 = to module RXD

void setup() {
  Serial.begin(9600);
  ble.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Ready");
}

void loop() {
  if (ble.available()) {
    char c = ble.read();   // Read one character from the phone
    Serial.write(c);       // Show it in the Serial Monitor

    if (c == '1') {
      digitalWrite(13, HIGH);
      ble.println("LED on");   // Send a reply to the phone
    }
    if (c == '0') {
      digitalWrite(13, LOW);
      ble.println("LED off");
    }
  }
}
```

---

## Step 4: Connect from your phone

1. Open **LightBlue**. On Android, turn on Location and allow the app to use it.
2. Find your module's name in the list and tap it.
3. Tap the service **FFE0**, then the characteristic **FFE1**.
4. Tap **Listen for notifications** (or **Subscribe**) to see replies.
5. Change the format to **UTF-8 String**.
6. Tap **Write new value**, type `1`, and send it.

The LED turns on and your phone shows `LED on`. Send `0` to turn it off.

To send other data to your phone (like a sensor reading), use `ble.println()` in your sketch. Keep messages short and wait at least 100 ms between them.

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Step 2 shows nothing after the arrows | Unplug and replug the USB cable, then reopen the Serial Monitor. Check TXD → D2 and RXD → D3. |
| Phone can't find the module | Use the LightBlue app, not phone Settings. On Android, turn on Location. |
| LED doesn't respond | Check you're writing to **FFE1** as **UTF-8 String**. Check the phone is connected. |
| Garbled text in Serial Monitor | Set the Serial Monitor to 9600. Run Step 2 again. |

---

<details>
<summary><b>Extra: AT commands</b> (click to open)</summary>

AT commands change the module's settings. They only work when no phone is connected. Send them with the `sendCommand()` function from Step 2.

| Command | What it does |
|---|---|
| `AT` | Test. Replies `OK`. |
| `AT+ALL` | Show all settings |
| `AT+NAME=MyDevice` | Change the name |
| `AT+BAUD=0` | Set speed to 9600 (4 = 115200) |
| `AT+SETTING=DEFAULT` | Factory reset |

</details>

<details>
<summary><b>Extra: Connect from a web browser</b> (click to open)</summary>

Chrome and Edge can talk to the module directly from a web page, including a p5.js sketch.

```js
async function connect() {
  const device = await navigator.bluetooth.requestDevice({
    filters: [{ services: [0xffe0] }]
  });
  const server = await device.gatt.connect();
  const service = await server.getPrimaryService(0xffe0);
  const ch = await service.getCharacteristic(0xffe1);

  // Receive messages from the Arduino
  await ch.startNotifications();
  ch.addEventListener("characteristicvaluechanged", e => {
    console.log(new TextDecoder().decode(e.target.value));
  });

  // Send "1" to the Arduino
  await ch.writeValue(new TextEncoder().encode("1"));
}
```

- Call `connect()` from a button click.
- The page must run on `https://` or `localhost`.
- Safari and Firefox don't support this.

</details>

<details>
<summary><b>Extra: Upload code wirelessly</b> (click to open)</summary>

The NL-16 can upload sketches to the Uno over Bluetooth from an Android phone, using NULLLAB's [upload app](https://github.com/nulllaborg/arduino_ble_flash_demo).

This needs different wiring and the module set back to 115200 (`AT+BAUD=4`):

| NL-16 | Uno |
|---|---|
| +5V | 5V |
| GND | GND |
| TXD | D0 |
| RXD | D1 |
| STAT/D-RST | RESET |

1. In Arduino IDE: **Sketch → Export Compiled Binary** to create a `.hex` file.
2. Copy the `.hex` file to your phone.
3. Open the app, connect to the module, select the file, and upload.

Unplug the TXD and RXD wires before uploading over USB, or the upload fails.

</details>

---

## References

- [NULLLAB BLE-Uno docs](https://github.com/nulllaborg/ble-uno) (same chip and AT commands)
