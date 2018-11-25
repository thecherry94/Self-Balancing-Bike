#pragma once



#include "cState.h"
#include "cBike.h"


class cInitializationState : public cState
{
    private:
        cBike* _bike;
        cLenkersensor* _sensLenker;
        cNeigungssensor* _sensNeigung;

        long _counterWifi;

    public:
        cInitializationState(cBike* bike, std::string name);

        ~cInitializationState();

        void enter() override;
        void process() override;
        void leave() override;
};