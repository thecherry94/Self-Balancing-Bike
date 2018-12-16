#pragma once



#include "cState.h"
#include "cBike.h"


struct sAutomaticSpinParameters
{
    cGyroansteuerung* l;
    cGyroansteuerung* r;
    bool* blockInput;
    TaskHandle_t* taskHandle;
};


class cGyroSpinupState : public cState
{
    private:
        cBike* _bike;
        cGyroansteuerung* _gyroL;
        cGyroansteuerung* _gyroR;

        bool _exit;
        bool _blockInput;

        TaskHandle_t _automaticSpinupTaskHandle;
        TaskHandle_t _automaticSpindownTaskHandle;

    public:
        cGyroSpinupState(cBike* bike, std::string name);

        void enter() override;
        void process() override;
        void leave() override;
};


void automaticSpinupMain(void*);
void automaticSpinup(cGyroansteuerung* g);

void automaticSpindownMain(void*);
void automaticSpindown(cGyroansteuerung* g);