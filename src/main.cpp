#include "env.h"

#include <Arduino.h>
#include "LittleFS.h"

#include "WiFiManager.h"
#include "webServer.h"
#include "updater.h"
#include "fetch.h"
#include "configManager.h"
#include "timeSync.h"

struct task {
    unsigned long rate;
    unsigned long previous;
};

task taskA = {.rate = 1000, .previous = 0};

int sensorValue = 0;
const int analogInPin = A0;

void setup() {
    Serial.begin(115200);

    LittleFS.begin();
    configManager.begin();
    WiFiManager.begin(configManager.data.projectName);
    WiFiManager.setNewWifi(env_ssid, env_password);
    timeSync.begin();
}

void loop() {
    //software interrupts
    WiFiManager.loop();
    updater.loop();
    configManager.loop();


    //task A
    if (taskA.previous == 0 || (millis() - taskA.previous > taskA.rate)) {
        taskA.previous = millis();

        //do task
        sensorValue = analogRead(analogInPin);
        Serial.println(sensorValue);
        Serial.println(ESP.getFreeHeap());

        /*
        fetch.GET(env_api_base_url);
        while (fetch.busy()) {
            if (fetch.available()) {
                Serial.write(fetch.read());
            }
        }

        fetch.clean();
         */
    }
}