#pragma once



#include "cState.h"
#include "cBike.h"


class cRunningState : public cState
{
    private:
        cBike* _bike;

        cGyroansteuerung* _gyroL;
        cGyroansteuerung* _gyroR;

        cLenkermotorV2* _lenker;

        bool _switchSpinup;

    public:
        cRunningState(cBike* bike, std::string name);

        void enter();
        void process();
        void leave();
};