/*
    Yazan: Aybüke Sökmen
    Tarih: 02/02/25
    Program: MQTT ile LED Yakma
    Geliştirilen Ortam: Arduino IDE
    Test Ortamı: MQTTBox

    Açıklama:
    Bu program, MQTT protokolü üzerinden gönderilen mesajları dinleyerek bir LED'i
    açıp kapatır. Gelen mesajlar "on" ve "off" şeklindedir. LED'in durumu,
    mesajlara göre kontrol edilir. Ayrıca bu program OTA (Over-the-Air) özelliği
    ile uzaktan güncellenebilir.
*/

#include <ArduinoOTA.h>          // OTA kütüphanesi
#include "inc/My_MQTT.h"
#include "inc/Messages.h"
#include "test/test_messages.cpp"

// Makrolar
#define INIT_SERIAL()           \
    Serial.begin(SERIALBAUDRATE)


#define INIT_LED()              \
    pinMode(LED_PIN, OUTPUT);   \
    LED_OFF()

#define INIT_WIFI()             \
    myWiFi.connect()

#define INIT_MQTT()             \
    myMQTT.connect();           \
    myMQTT.setCallback(callback)

#define PROCESS_MESSAGES()      \
    if (messageFlag) {          \
        processMessage();       \
        messageFlag = false;    \
    }

#define RUN_TESTS()             \
    runTests()

#define INIT_OTA()                      \
    ArduinoOTA.setHostname("MQTT_LED_Device");    /* Cihaz adı */ \
    ArduinoOTA.setPassword("123456");            /* Güncelleme için şifre */ \
    ArduinoOTA.onStart([]() {                    \
        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem"; \
        Serial.println("OTA Güncelleme Başladı: " + type); \
    });                                         \
    ArduinoOTA.onEnd([]() {                     \
        Serial.println("\nOTA Güncelleme Tamamlandı."); \
    });                                         \
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { \
        Serial.printf("OTA Yükleme: %u%%\r", (progress * 100) / total); \
    });                                         \
    ArduinoOTA.onError([](ota_error_t error) {  \
        Serial.printf("OTA Hatası [%u]: ", error); \
        if (error == OTA_AUTH_ERROR) Serial.println("Yetkilendirme Hatası"); \
        else if (error == OTA_BEGIN_ERROR) Serial.println("Başlatma Hatası"); \
        else if (error == OTA_CONNECT_ERROR) Serial.println("Bağlantı Hatası"); \
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Veri Alma Hatası"); \
        else if (error == OTA_END_ERROR) Serial.println("Bitirme Hatası"); \
    });                                         \
    ArduinoOTA.begin();                         \
    Serial.println("OTA Hazır.");


void setup() {

    INIT_SERIAL();
    INIT_LED();
    INIT_WIFI();
    INIT_MQTT();
    INIT_OTA();  // OTA başlatma
        // Testleri çalıştır
    RUN_TESTS();
}

void loop() {
    ArduinoOTA.handle();
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
        delay(1000);  // Bağlantı için tekrar deneme
    }
        myMQTT.loop();       // MQTT döngüsü
    PROCESS_MESSAGES();
}

