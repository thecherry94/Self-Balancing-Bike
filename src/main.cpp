#include <Arduino.h>

#include "precomp.h"

#define WIFI_SSID       "HIT-FRITZBOX-7490"
#define WIFI_PASSWORD   "63601430989011937932"





cMeasurementLog<float> mes("Zeit [sec]", "Neigung [°]");

void make_example_sinus(
	cMeasurementLog<float>& log, 
	float amplitude, float frequency, 
	float total_time, float time_step)
{
	int num_ticks = total_time / time_step;

	for (int tk = 0; tk < num_ticks; tk++)
	{
		float time = tk * time_step;
		log.write(time, amplitude * sin(2.0*PI*frequency * time / 4.0f));
	}
}

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