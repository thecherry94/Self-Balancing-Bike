#pragma once



#include "cState.h"
#include "cBike.h"


class cGyroSpindownState : public cState
{
    private:
        cBike* _bike;

    public:
        cGyroSpindownState(cBike* bike, std::string name);

        void enter() override;
        void process() override;
        void leave() override;
};