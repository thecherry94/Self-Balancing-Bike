#pragma once



#include "cState.h"
#include "cBike.h"


class cGyroSpinupState : public cState
{
    private:
        cBike* _bike;
        cGyroansteuerung* _gyroL;
        cGyroansteuerung* _gyroR;

        bool _exit;


    public:
        cGyroSpinupState(cBike* bike, std::string name);

        void enter();
        void process();
        void leave();
};