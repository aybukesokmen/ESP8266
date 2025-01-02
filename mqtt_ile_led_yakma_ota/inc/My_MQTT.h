#ifndef MY_MQTT_H
#define MY_MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Defines.h"

// WiFiManager sınıfı
class WiFiManager {
public:
    WiFiManager();
    void connect();
};

// MQTTManager sınıfı
class MQTTManager {
private:
    PubSubClient client;
    void reconnect();
public:
    MQTTManager(WiFiClient& espClient);
    void connect();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    void publishMessage(const char* topic, const char* message);
    void loop();
};

// Global nesnelerin referansları
extern WiFiManager myWiFi;
extern MQTTManager myMQTT;

#endif // MY_MQTT_H
