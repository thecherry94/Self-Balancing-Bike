#pragma once



#include "cState.h"
#include "cBike.h"


class cEmergencyState : public cState
{
    private:
        cBike* _bike;

    public:
        cEmergencyState(cBike* bike, std::string name);

        void enter() override;
        void process() override;
        void leave() override;
};