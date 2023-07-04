#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID       "KPU ATAS"
#define WIFI_PASSWORD   "87654321"
#define MQTT_SERVER     "io.adafruit.com"
#define MQTT_PORT       1883
#define MQTT_USERNAME   "alifilham1"
#define MQTT_KEY        "aio_oxKf27cIkY8zOe6xUIgVirYqzAkp"
#define MQTT_TOPIC_AMP  "alifilham1/feeds/ampere"
#define MQTT_TOPIC_VOLT "alifilham1/feeds/tegangan"
#define MQTT_TOPIC_RPM  "alifilham1/feeds/rpm"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY);

Adafruit_MQTT_Publish feed_amp = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_AMP);
Adafruit_MQTT_Publish feed_volt = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_VOLT);
Adafruit_MQTT_Publish feed_rpm = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_RPM);

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
  // Generate random data for ampere, voltage, and RPM
  float ampere = random(0, 101);
  float tegangan = random(0, 101);
  float rpm = random(0, 101);

  // Convert data to string
  String ampereString = String(ampere);
  String teganganString = String(tegangan);
  String rpmString = String(rpm);

  // Publish data to Adafruit IO
  if (feed_amp.publish(ampereString.c_str())) {
    Serial.print("Data sent to Adafruit IO (Ampere): ");
    Serial.println(ampereString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (Ampere)");
  }

  if (feed_volt.publish(teganganString.c_str())) {
    Serial.print("Data sent to Adafruit IO (Tegangan): ");
    Serial.println(teganganString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (Tegangan)");
  }

  if (feed_rpm.publish(rpmString.c_str())) {
    Serial.print("Data sent to Adafruit IO (RPM): ");
    Serial.println(rpmString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (RPM)");
  }

  delay(5000);  // Delay 5 seconds between each data send
}
