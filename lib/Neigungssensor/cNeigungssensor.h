#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "Wire.h"
#include "cKommunikation.h"

#ifndef NEIGUNG_H
#define NEIGUNG_H

#define EE_ADDRESS_NEIGUNG 1

class cNeigungssensor
{
    private:
        // Vom Klassendiagramm
        //
        float neigungsWinkel;
        //adafruit_bno055_offsets_t calibrationData;
        float refreshRate;
        int _refreshRate;

        bool _calibRestored;

        // Zusätzliches Variablen
        //
        Adafruit_BNO055 _bno;
        cWiFiKommunikation _com;

    public:
        cNeigungssensor(int bno_addr);
        
        void displaySensorDetails();
        void displaySensorStatus();
        void displayCalStatus();
        void displaySensorOffsets(const adafruit_bno055_offsets_t&);

        sensors_event_t getEvent();

        bool loadCalibrationFromMemory();
        void displaySensorOrientation();

};

#endif
