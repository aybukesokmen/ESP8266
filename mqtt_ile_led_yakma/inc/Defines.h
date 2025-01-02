#ifndef DEFINES_H
#define DEFINES_H

#include "Arduino.h"

// Serial Monitor Ayarları
#define SERIALBAUDRATE 115200

// WiFi ve MQTT Ayarları
#define WIFI_SSID "TP-Link_656F"
#define WIFI_PASSWORD "39244390"
#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "NodeMCUClient"
#define MQTT_TOPIC "deneme_broker"
#define MQTT_RESPONSE_TOPIC "deneme_broker_response"

// LED Pin Tanımları
#define LED_PIN D1
#define LED_ON() digitalWrite(LED_PIN, HIGH)  // LED'i aç
#define LED_OFF() digitalWrite(LED_PIN, LOW) // LED'i kapat

#endif // DEFINES_H
