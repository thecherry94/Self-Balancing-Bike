#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "Wire.h"
#include "cWebServer.h"

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

        float _neigungsBuffer[10];
        float _neigungsGeschwindigkeit;
        int _neigungsBufferIndex;

    public:
        cNeigungssensor(int bno_addr);
        
        void displaySensorDetails();
        void displaySensorStatus();
        void displayCalStatus();
        void displaySensorOffsets(const adafruit_bno055_offsets_t&);

        sensors_event_t getEvent();
        imu::Vector<3> getRawData(Adafruit_BNO055::adafruit_vector_type_t);
        
        float GetNeigungswinkelgeschwindigkeitZ();

        bool loadCalibrationFromMemory();
        void displaySensorOrientation();

        bool IsFullyCalibrated();

};

#endif