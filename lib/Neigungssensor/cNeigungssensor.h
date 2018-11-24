


#ifndef NEIGUNG_H
#define NEIGUNG_H

#include "Adafruit_BNO055.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"
#include "cWebServer.h"

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
        bool _calibrationRunning;
        bool _calibSuccess;

        // Zusätzliches Variablen
        //
        Adafruit_BNO055 _bno;

    public:
        cNeigungssensor(int bno_addr);
        
        void displaySensorDetails();
        void displaySensorStatus();
        void displayCalStatus();
        void displaySensorOffsets(const adafruit_bno055_offsets_t&);

        sensors_event_t getEvent();
        imu::Vector<3> getRawData(Adafruit_BNO055::adafruit_vector_type_t);

        bool loadCalibrationFromMemory();
        void displaySensorOrientation();

        bool IsCalibrated();

};

#endif
