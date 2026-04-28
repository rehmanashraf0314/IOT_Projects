# ESP8266 Arduino Sketches

A collection of four Arduino sketches for the ESP8266 microcontroller, covering GPS reading, MQTT-based LED control, MPU6050 fall detection, and HTTP sensor data posting.

---

## Sketches

### 1. `gps_reader.ino`


This sketch reads GPS data using the **TinyGPSPlus** library over a **SoftwareSerial** connection on an ESP8266. The GPS module is connected on GPIO15 (RX). Once a valid GPS fix is acquired, it prints the **latitude**, **longitude**, **number of satellites**, and **altitude** to the Serial Monitor every second. If no fix is available yet, it prints a waiting message.

**Libraries required:**
- `TinyGPSPlus`
- `SoftwareSerial`

**Hardware:**
- ESP8266
- GPS Module (connected to GPIO15)

---

### 2. `mqtt_led_control.ino`


This sketch connects an ESP8266 to a WiFi network and then to a public **MQTT broker** (`broker.hivemq.com`). It subscribes to the topic `pieas/esp8266/led`. The onboard LED (GPIO2) can be toggled by pressing the key `p` in the Serial Monitor. When the LED state changes, the sketch publishes either `"ON"` or `"OFF"` to the MQTT topic so other devices on the same broker can see the state.

**Libraries required:**
- `ESP8266WiFi`
- `PubSubClient`

**Hardware:**
- ESP8266
- Onboard LED (GPIO2)

---

### 3. `mpu6050_fall_detector.ino`


This sketch reads accelerometer data from an **MPU6050** sensor (connected via I2C on SDA=GPIO4, SCL=GPIO5) and connects the ESP8266 to WiFi. It continuously monitors the **Z-axis acceleration**. If the Z value goes **negative** (which can indicate a fall or flip), the sketch sends an **HTTP POST request** to a local server at `192.168.43.167:8000/send_location/` with hardcoded GPS coordinates (latitude and longitude). This is intended as a basic fall/tilt detection and alert system.

**Libraries required:**
- `Adafruit_MPU6050`
- `Adafruit_Sensor`
- `Wire`
- `ESP8266WiFi`
- `ESP8266HTTPClient`

**Hardware:**
- ESP8266
- MPU6050 sensor (I2C)

---

### 4. `http_sensor_post.ino`


This sketch connects the ESP8266 to WiFi and sends an **HTTP GET request** every 5 seconds to a Node-RED server at `192.132.45.134:1880/update-sensor`, passing a hardcoded temperature value (`24.37`) as a query parameter. The server response code and payload are printed to the Serial Monitor. This is a basic example of pushing sensor data to a Node-RED dashboard or flow.

**Libraries required:**
- `ESP8266WiFi`
- `ESP8266HTTPClient`
- `WiFiClient`

**Hardware:**
- ESP8266

---

## Notes

- WiFi credentials (`ssid` and `password`) are hardcoded in each sketch. Change them before uploading to your board.
- Some sketches use hardcoded IP addresses for local servers. Update these to match your own network setup.
- All sketches are written for the **ESP8266** and tested with the Arduino IDE.
