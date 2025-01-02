/*
    Yazan: Aybüke Sökmen
    Tarih: 02/02/25
    Program: MQTT ile LED Yakma
    Geliştirilen Ortam: Arduino IDE
    Test Ortamı: MQTTBox

    Açıklama:
    Bu program, MQTT protokolü üzerinden gönderilen mesajları dinleyerek bir LED'i
    açıp kapatır. Gelen mesajlar "on" ve "off" şeklindedir. LED'in durumu,
    mesajlara göre kontrol edilir.
*/
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

void setup() {
    // Makro çağrıları
    INIT_SERIAL();
    INIT_LED();
    INIT_WIFI();
    INIT_MQTT();

    // Testleri çalıştır
    RUN_TESTS();
}

void loop() {
    myMQTT.loop(); // MQTT döngüsü
    PROCESS_MESSAGES();
}
