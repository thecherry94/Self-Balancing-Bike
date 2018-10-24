#include "cBike.h"


#define hz2ms(x)     1000.0f*(1.0f/(float)x)

#include <time.h>
#include <random>


float* make_random_signal(float min, float max, bool rnd, int seed);
float add_sines(float t, int precision, bool rnd, int seed);


cBike::cBike()
{
    // Hier eure Klassen initialisieren
    // ...


    // Fahrradstatus auf STARTING setzen
    _state = EBikeState::STARTING;

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Bike starting"));
}


void cBike::run()
{
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Trying to connect to " + WIFI_SSID));

    // Verbindung mit AP herstellen
    WIFI_COM->connect(WIFI_SSID, WIFI_PASSWORD);

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Connection successfull"));


    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Start Sensor Task"));
    // Sensor task erstellen und starten
    xTaskCreatePinnedToCore(
        &sensor_main, 
        SENSOR_TASK, SENSOR_TASK_STACKSIZE, 
        nullptr, 0, nullptr, 
        task_core);

    // Irgendwas 
    while(true)
    {
        Serial.println("Task 2");
        delay(hz2ms(100));
    }
    
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Shutdown"));
}

// Test
//
void* sensor_main()
{
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Sensor main start"));

    make_signal()

    while(true)
    {}
}



float* make_signal(int seed, float total_time, int step, bool rnd = false, int seed = 1)
{
    srand(time(seed));

    int num_ticks = total_time / (float)step;
    float* retval = new float[num_ticks];

    
    for(int i = 0; i < num_ticks; i++)
    {
        float t = (float)i * (float)step;
        retval[i] = add_sines(t, 10, rnd, seed);



        delay(hz2ms(200));
    }


    return retval;
}


float add_sines(float t, int precision, bool rnd = false, int seed = 1)
{
    float retval = 0; 

    for (int n = 1; n < precision; n++)
    {
        float amplitude = 5 / (2*n);
        const float omega = (2.0 * PI) * 2.0; 

        retval += amplitude * sin(omega * (double)t);
    }

    if (rnd)
    {
        srand(time(seed));
        retval += 5.0f * (1.0f / (float)(rand() % 1000));
    }

    return retval;
}