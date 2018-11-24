#pragma once


#include "cNeigungssensor.h"
#include "cGyroansteuerung.h"
#include "cLenkersensor.h"
#include "cMeasurementLog.h"
//#include "precomp.h"
#include "global.h"
#include "cLenkermotorV2.h"
#include "cLivelog.h"



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


//static int task_core = 0;



class cBike
{
    private:
        /*
         ************************************************
         * Hier kommen eure Klassen als member hin      *
         * cMeineKlase _meineKlasse;                    *
         ************************************************
         */ 
        cGyroansteuerung _gyroL;
        cGyroansteuerung _gyroR;
        cNeigungssensor* _sensorNeigung;
        cLenkermotorV2 _Lenkmotor;
        cLenkersensor _lenkerSensor;        // Objekt erzeugt von cLenkersensor

        cLivelog<float>* _livelog;
        

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

        


        
        /*
         ************************************************
         *              Variabelen               *
         ************************************************
         */ 
        byte gyroleistung = 0;
    public:
        cBike(byte, byte);        // Hier sollen die Member lediglich mit Standardwerten initialisiert

        void run();         // Hier sitzt die Startlogik

        void update();      // Programmlogik
        void setup_webserver_methods();

        cLenkersensor* GetSensorLenker();  
        cGyroansteuerung* GetGyroL();
        cGyroansteuerung* GetGyroR();
        cLenkermotorV2* GetLenkeransteuerung();
        cNeigungssensor* GetSensorNeigung();

};