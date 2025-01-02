#include "../inc/Messages.h"

// Global Değişkenlerin Tanımlanması
volatile bool messageFlag = false;
char* receivedMessage = NULL; // Dinamik bellek için pointer

void ICACHE_FLASH_ATTR callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Yeni mesaj gelmeden önce eski belleği serbest bırak
    if (receivedMessage != NULL) {
        free(receivedMessage);
        receivedMessage = NULL;
    }

    // Bellek tahsisi
    receivedMessage = (char*)malloc(length + 1); // '\0' için ekstra 1 byte
    if (receivedMessage == NULL) {
        Serial.println("Error: Memory allocation failed!");
        return;
    }

    memcpy(receivedMessage, payload, length);
    receivedMessage[length] = '\0'; // Null terminator eklenir
    messageFlag = true;
}

void ICACHE_FLASH_ATTR processMessage() {
    if (receivedMessage == NULL) {
        Serial.println("No message to process.");
        return;
    }

    if (strcmp(receivedMessage, "on") == 0) {
        LED_ON();
        Serial.println("LED is ON");
    } else if (strcmp(receivedMessage, "off") == 0) {
        LED_OFF();
        Serial.println("LED is OFF");
    } else {
        Serial.println("Unknown command");
    }

    // Kullanımdan sonra bellek serbest bırakılır
    free(receivedMessage);
    receivedMessage = NULL;
}