# IoT Weather Station (ESP32)

An ESP32 reads temperature and humidity from a DHT22 sensor, shows them on a 16x2 I2C LCD, and uploads the readings over WiFi to ThingSpeak, where they are plotted as a live graph. If the temperature goes above 35°C, the display shows "Too hot!".

Built and tested in the Wokwi simulator: [open the project](https://wokwi.com/projects/476309782266858497)

![Circuit](circuit.png)

![ThingSpeak graph](graph.png)

## Parts

- ESP32 DevKit
- DHT22 temperature and humidity sensor
- 16x2 LCD with I2C module

## Wiring

| DHT22 | ESP32 |
|-------|-------|
| VCC   | 3V3   |
| SDA   | GPIO 15 |
| NC    | not connected |
| GND   | GND   |

| LCD | ESP32 |
|-----|-------|
| GND | GND   |
| VCC | 5V    |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

## Libraries

- DHT sensor library for ESPx
- LiquidCrystal I2C

## How to run

1. Open the Wokwi link above, or create a new ESP32 project and copy in `sketch/sketch.ino` and the wiring.
2. Create a free ThingSpeak channel with two fields: Temperature and Humidity.
3. Replace `YAHAN_APNI_WRITE_API_KEY_DAALO` in `sketch/sketch.ino` with your channel's Write API Key.
4. Start the simulation. Click the DHT22 to change the temperature and watch the graph update every 20 seconds.
