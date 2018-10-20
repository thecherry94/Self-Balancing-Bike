#include <Arduino.h>

#include "precomp.h"

#include "cWiFiKommunikation.h"
#include "cStatusLog.h"
#include "cNeigungssensor.h"

#define WIFI_SSID       "HIT-FRITZBOX-7490"
#define WIFI_PASSWORD   "63601430989011937932"

void setup() 
{
    WIFI_COM->connect(WIFI_SSID, WIFI_PASSWORD);

    Serial.begin(115200);
}

void loop() 
{
    Serial.println("gregaaaaaaar");
    Serial.println("ssss");
	Serial.println("zzzzz");
}