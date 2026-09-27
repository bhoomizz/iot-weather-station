#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTesp.h"
#include <LiquidCrystal_I2C.h>

String apiKey = "YAHAN_APNI_WRITE_API_KEY_DAALO";

DHTesp dht;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dht.setup(15, DHTesp::DHT22);
  lcd.init();
  lcd.backlight();

  // Wokwi ka virtual WiFi se connect karo
  lcd.print("WiFi connecting");
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.print("WiFi connected!");
  delay(1000);
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();

  // LCD pe dikhao
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(data.temperature, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  if (data.temperature > 35) {
    lcd.print("Too hot!");
  } else {
    lcd.print("Hum: ");
    lcd.print(data.humidity, 1);
    lcd.print(" %");
  }

  // ThingSpeak pe bhejo
  HTTPClient http;
  String url = "http://api.thingspeak.com/update?api_key=" + apiKey
             + "&field1=" + String(data.temperature)
             + "&field2=" + String(data.humidity);
  http.begin(url);
  int code = http.GET();
  Serial.print("ThingSpeak response: ");
  Serial.println(code);  // 200 aaye to data pahunch gaya
  http.end();

  delay(20000);  // ThingSpeak free mein 15 second se jaldi data nahi leta
}
