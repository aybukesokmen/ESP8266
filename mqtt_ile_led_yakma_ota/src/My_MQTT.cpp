#include "../inc/My_MQTT.h"

// Global nesnelerin TANIMLANMASI
WiFiManager myWiFi;
WiFiClient espClient;
MQTTManager myMQTT(espClient);

// WiFiManager Sınıfı
WiFiManager::WiFiManager() {}

void WiFiManager::connect() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 40) {  // Daha fazla deneme
        delay(500);  // Daha uzun gecikme
        Serial.print(".");
        retryCount++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi. Restarting...");
        ESP.restart();  // Başarısız olursa cihazı yeniden başlat
    }
}



// MQTTManager Sınıfı
MQTTManager::MQTTManager(WiFiClient& espClient) : client(espClient) {}

void ICACHE_FLASH_ATTR MQTTManager::connect() {
    client.setServer(MQTT_SERVER, MQTT_PORT);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT broker...");
        if (client.connect(MQTT_CLIENT_ID)) {
            Serial.println("connected!");
            client.subscribe(MQTT_TOPIC);
            Serial.print("Subscribed to topic: ");
            Serial.println(MQTT_TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.println(client.state());
            Serial.println("Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void ICACHE_FLASH_ATTR MQTTManager::setCallback(MQTT_CALLBACK_SIGNATURE) {
    client.setCallback(callback);
}

void ICACHE_FLASH_ATTR MQTTManager::publishMessage(const char* topic, const char* message) {
    if (client.connected()) {
        client.publish(topic, message);
        Serial.print("Message published to ");
        Serial.print(topic);
        Serial.print(": ");
        Serial.println(message);
    } else {
        Serial.println("MQTT broker is not connected. Message not sent.");
    }
}

void ICACHE_FLASH_ATTR MQTTManager::loop() {
    if (!client.connected()) {
        connect();
    }
    client.loop();
}