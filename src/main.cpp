#include <Arduino.h>

#include "precomp.h"




void setup() 
{
    Serial.begin(115200);
    WIFI_COM->connect(WIFI_SSID, WIFI_PASSWORD);
    

    make_example_sinus(mes, 10.0f, 1.0f, 5.0f, 0.05f);

    WIFI_COM->attachEvent("/get_measurement", [](AsyncWebServerRequest* r)
    {
        AsyncWebServerResponse* resp = r->beginResponse(200, "text", mes.exprt(EMeasurementLogFormatting::FORMAT_EXCEL).c_str());
        
        resp->addHeader("Content-Type", "application/octet-stream");
        resp->addHeader("Content-Disposition", "form-data;filename=\"measurements.txt\"");
      
        r->send(resp);  
    });

    WIFI_COM->attachEvent("/hello", [](AsyncWebServerRequest* r)
    {
        r->send(200, "text", "Hellooooo");
    });
}

void loop() 
{
    
}