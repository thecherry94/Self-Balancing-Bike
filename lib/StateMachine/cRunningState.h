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
        cLenkersensor* _sensLenker;
        bool _switchSpinup;

    public:
        cRunningState(cBike* bike, std::string name);

        void enter() override;
        void process() override;
        void leave() override;
};