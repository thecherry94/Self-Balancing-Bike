#pragma once



#include "cState.h"
#include "cBike.h"


class cInitializationState : public cState
{
    private:
        cBike* _bike;
        cLenkersensor* _sensLenker;
        cNeigungssensor* _sensNeigung;

    public:
        cInitializationState(cBike* bike, std::string name);

        void enter();
        void process();
        void leave();
};