#include "env.h"
#include <string>
#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);         // Start the Serial communication to send messages to the computer
    delay(10);
    Serial.println('\n');

    WiFi.begin(env_ssid, env_password);             // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(env_ssid); Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
}