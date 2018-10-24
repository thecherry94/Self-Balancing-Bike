#include "cBike.h"


#define hz2ms(x)     1000.0f*(1.0f/(float)x)


#define HTML_SCHECKER_DEMO ""


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
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Trying to connect to " + std::string(WIFI_SSID)));

    // Verbindung mit AP herstellen
    WIFI_COM->connect(WIFI_SSID, WIFI_PASSWORD);

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Connection successfull"));


    WIFI_COM->attachEvent("/measurements/neigung", [](AsyncWebServerRequest* req)
    {
        // Hier wird die Neigung gesendet
    });

    WIFI_COM->attachEvent("/ui/gyro_demo", [](AsyncWebServerRequest* req)
    {
        // Hier soll eine HTML-Seite übertragen werden, um das Gyro währenden der Demo
        // für Schecker steuern zu können

        req->send(200, "text/html", HTML_SCHECKER_DEMO);
    });


    _state = EBikeState::STARTING;
    while(_state != EBikeState::STOPPED)
    {
        switch(_state)
        {
            case EBikeState::STARTING:
            // Hier gyro auf drehzal bringen und überprüfen ob es auf drehzahl ist
            // Wenn es auf drehzahl ist, dann auf EBikeState::RUNNING wechseln
            break;

            case EBikeState::RUNNING:
            // Hier wird alles gemacht, wenn das gyro auf drehzahl ist
            // Evtl. hier auf eine abbruchbedingung warten
            break;
        }
    }

    // Hier beenden
    
    
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Shutdown"));
}

