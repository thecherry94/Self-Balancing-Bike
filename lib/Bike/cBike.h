#pragma once

// precomp entählt alle benötigten header Dateien
<<<<<<< HEAD
//#include "precomp.h"
//Komm on das kann man doch net hochladen. wie soll das bei mir funktionieren.
//#include "D:\Users\Max\Documents\GitHub\Self-Balancing-Bike\lib\Neigungssensor\cNeigungssensor.h"
//!!!!!!!!!!!!!!! 
#include "cNeigungssensor.h"
#include "cGyroansteuerung.h"
#include "cLenkermotoransteuerung.h"
#include "cLenkersensor.h"
#include "cMeasurementLog.h"
=======
#include "precomp.h"
>>>>>>> parent of 60a343d... ACHTUNG!!!!!
#include "global.h"



#define SENSOR_TASK             "sensor-main"
#define SENSOR_TASK_STACKSIZE   10000

#define MODULE_BIKE     "[BIKE_MAIN_MODULE]"

enum EBikeState
{
    STARTING,       // Lenkersensor Nullpunkt
    INITIALIZATION, // Gyromotor an piepen
    GYRO_SPINUP,    // Gyro andrehen
    RUNNING,        // warten auf Benutzereingabe für Lenkermotor für Eingang in Zustand
    GYRO_SPINDOWN,  // Warnung! Festhalten, Regelung aus --> Motor langsam in Nullstellung fahren, Motor aus, Gyros bremsen
    STOPPED,         // Alle Freigaben wegnehmen, 
    EMERGENCY       // Sofort Stopp
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
        cGyroansteuerung _gyro;
        cNeigungssensor* _sensorNeigung;
        cLenkermotoransteuerung _Lenkmotor;
        cLenkersensor _lenkerSensor;        // Objekt erzeugt von cLenkersensor
        

        /*
         ************************************************
         *              Verwaltungsmember               *
         ************************************************
         */ 

        EBikeState              _state;

        AsyncWebSocket*         _main_socket;


        /*
         ************************************************
         *             Private Funktionen               *
         ************************************************
         */ 

        void setup_webserver_methods();


        
        /*
         ************************************************
         *              Variabelen               *
         ************************************************
         */ 
        byte gyroleistung = 0;
    public:
        cBike(byte);        // Hier sollen die Member lediglich mit Standardwerten initialisiert

        void run();         // Hier sitzt die Startlogik

        void update();      // Programmlogik

};