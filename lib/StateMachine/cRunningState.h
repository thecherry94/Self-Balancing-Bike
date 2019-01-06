#pragma once



#include "cState.h"
#include "cBike.h"

#include "InputOutput_Test.h"


class cRunningState : public cState
{
    private:
        cBike* _bike;
        cGyroansteuerung* _gyroL;
        cGyroansteuerung* _gyroR;
        cLenkermotorV2* _lenker;
        cLenkersensor* _sensLenker;
        cNeigungssensor* _sensNeigung;
        bool _switchSpinup;

        InputOutput_TestModelClass rtObj;// Instance of model class

        void rt_OneStep(void);

    public:
        cRunningState(cBike* bike, std::string name);

        void enter() override;
        void process() override;
        void leave() override;
};