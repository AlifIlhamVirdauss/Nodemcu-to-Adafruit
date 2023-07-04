#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID       "nama_wifi_anda"
#define WIFI_PASSWORD   "password_wifi_anda"
#define MQTT_SERVER     "io.adafruit.com"
#define MQTT_PORT       1883
#define MQTT_USERNAME   "username_anda"
#define MQTT_KEY        "kunci_anda"
#define MQTT_TOPIC      "feeds"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY);

Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC);

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.connect();
}

void loop() {
  // Generate random data (0-100)
  float data = random(0, 101);

  // Convert data to string
  String dataString = String(data);

  // Publish data to Adafruit IO
  if (feed.publish(dataString.c_str())) {
    Serial.print("Data sent to Adafruit IO: ");
    Serial.println(dataString);
  } else {
    Serial.println("Failed to send data to Adafruit IO");
  }

  delay(5000);  // Delay 5 seconds between each data send
}
