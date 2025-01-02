#include "test_messages.h"


void runTests() {
    Serial.println("Running Tests...");

    // Test 1: Callback Fonksiyonu
    char topic[] = "test/topic";
    byte payload[] = "on";
    unsigned int length = sizeof(payload) - 1;

    callback(topic, payload, length);
    if (messageFlag && strcmp(receivedMessage, "on") == 0) {
        Serial.println("Test 1 Passed: Callback Works!");
    } else {
        Serial.println("Test 1 Failed: Callback Error!");
    }

    // Test 2: ProcessMessage Fonksiyonu (LED Açma Testi)
    receivedMessage = strdup("on"); // Gelen mesajı simüle ediyoruz
    processMessage();
    if (digitalRead(LED_PIN) == HIGH) {
        Serial.println("Test 2 Passed: LED Turned ON!");
        delay(1000); // 1 saniyelik gecikme
    } else {
        Serial.println("Test 2 Failed: LED Error!");
    }

    // Belleği temizleme
    if (receivedMessage != NULL) {
        free(receivedMessage);
        receivedMessage = nullptr;
    }

    // Test 3: LED Kapalı Testi
    receivedMessage = strdup("off"); // Gelen mesajı simüle ediyoruz
    processMessage();
    if (digitalRead(LED_PIN) == LOW) {
        Serial.println("Test 3 Passed: LED Turned OFF!");
        delay(1000); // 1 saniyelik gecikme
    } else {
        Serial.println("Test 3 Failed: LED Error!");
    }

    // Temizlik
    if (receivedMessage != NULL) {
        free(receivedMessage);
        receivedMessage = nullptr;
    }

    Serial.println("All Tests Completed.");
}
