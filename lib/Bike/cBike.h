#pragma once

// precomp entählt alle benötigten header Dateien
#include "cWiFiKommunikation.h"
#include "cNeigungssensor.h"
#include "cStatusLog.h"
#include "cMeasurementLog.h"
#include "cGyroansteuerung.h"
#include "cLenkermotoransteuerung.h"
#include "cLenkersensor.h"



#define WIFI_SSID       "HIT-FRITZBOX-7490"
#define WIFI_PASSWORD   "63601430989011937932"


#define SENSOR_TASK             "sensor-main"
#define SENSOR_TASK_STACKSIZE   10000

#define MODULE_BIKE     "BIKE_MAIN_MODULE"

enum EBikeState
{
    STARTING,
    INITIALIZATION,
    GYRO_SPINUP,
    RUNNING,
    GYRO_SPINDOWN,
    STOPPED
};


static int task_core = 0;



class cBike
{
    private:
        /*
         ************************************************
         * Hier kommen eure Klassen als member hin      *
         * cMeineKlase _meineKlasse;                    *
         ************************************************
         */ 

        

        /*
         ************************************************
         *              Verwaltungsmember               *
         ************************************************
         */ 

        EBikeState              _state;

    public:
        cBike();        // Hier sollen die Member lediglich mit Standardwerten initialisiert

        void run();     // Hier sitzt die Startlogik

};