#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

#include "Defines.h"

#include <stdlib.h>
#include "My_MQTT.h"

// Global Değişkenler
extern volatile bool messageFlag;
extern char* receivedMessage; 


// Callback ve İşleme Fonksiyonları
void callback(char* topic, byte* payload, unsigned int length);
void processMessage();

#endif // MESSAGES_H
