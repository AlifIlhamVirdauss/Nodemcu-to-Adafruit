#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Insert ur Data
#define WIFI_SSID       "nama_wifi_anda"
#define WIFI_PASSWORD   "password_wifi_anda"
#define MQTT_SERVER     "io.adafruit.com"
#define MQTT_PORT       1883
#define MQTT_USERNAME   "username_anda"
#define MQTT_KEY        "kunci_anda"
#define MQTT_TOPIC      "feeds"
#define MQTT_TOPIC_AMP  "username/feeds/feeds_name"
#define MQTT_TOPIC_VOLT "username/feeds/feeds_name"
#define MQTT_TOPIC_RPM  "username/feeds/feeds_name"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY);

//Changes "FEEDSNAME"
Adafruit_MQTT_Publish feed_amp = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_FEEDSNAME);
Adafruit_MQTT_Publish feed_volt = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_FEEDSNAME);
Adafruit_MQTT_Publish feed_rpm = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_FEEDSNAME);

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
  String ampereString = String(data);
  String teganganString = String(data);
  String rpmString = String(data);

//Change "feeds_name" with ur feeds name
  // Publish data to Adafruit IO
  if (feed_amp.publish(ampereString.c_str())) {
    Serial.print("Data sent to Adafruit IO (feeds_name): ");
    Serial.println(ampereString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (feeds_name)");
  }

  if (feed_volt.publish(teganganString.c_str())) {
    Serial.print("Data sent to Adafruit IO (feeds_name): ");
    Serial.println(teganganString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (feeds_name)");
  }

  if (feed_rpm.publish(rpmString.c_str())) {
    Serial.print("Data sent to Adafruit IO (feeds_name): ");
    Serial.println(rpmString);
  } else {
    Serial.println("Failed to send data to Adafruit IO (feeds_name)");
  }

  delay(5000);  // Delay 5 seconds between each data send
