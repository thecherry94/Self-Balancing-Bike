#include "cGyroSpinupState.h"
#include "stdio.h"

#include <Arduino.h>


/*
 * TODO:
 * Steuerung über Wifi
 */ 


cGyroSpinupState::cGyroSpinupState(cBike* bike, std::string name)
    : cState(name)
{
    _bike = bike;

    _gyroL = _bike->GetGyroL();
    _gyroR = _bike->GetGyroR();

    _exit = false;


    sTransition t_Spinup_Running;
    t_Spinup_Running.stateFrom = STATE_GYROSPINUP;
    t_Spinup_Running.stateTo = STATE_RUNNING;
    t_Spinup_Running.transitionCondition = [&]() { return _exit; };
    t_Spinup_Running.transitionAction = [&]() {};
}


void cGyroSpinupState::enter()
{
    Serial.println("cGyroSpinupState::enter");
    _gyroL->setMotorfreigabe(true);
    _gyroR->setMotorfreigabe(true);
}



void cGyroSpinupState::process()
{
    if(Serial.available())
    {
        String in;
        in = Serial.readStringUntil('\n');

        if(in[0] == 'p')
        {
            int p = 0;
            sscanf(in.c_str(), "p%d", &p);

            _gyroL->setLeistung(p);
            _gyroR->setLeistung(p);
        }
        else if (in[0] == 'q')
        {
            _exit = true;
        }
    }

    _gyroL->anlaufen();
    _gyroR->anlaufen();
}



void cGyroSpinupState::leave()
{
    Serial.println("cGyroSpinupState::leave");
    _exit = false;
}