#include <Arduino.h>

#include "cWiFiKommunikation.h"

#define WIFI_SSID       "HIT-FRITZBOX-7490"
#define WIFI_PASSWORD   "63601430989011937932"

void setup() 
{
    WIFI_COM->connect(WIFI_SSID, WIFI_PASSWORD);

    Serial.begin(115200);
}

void loop() 
{
    Serial.println("gregr");
    Serial.println("fdsfs");
	Serial.println("thrhrsssssster");
}