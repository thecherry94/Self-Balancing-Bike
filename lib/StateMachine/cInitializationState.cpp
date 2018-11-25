#include "cInitializationState.h"
#include <WiFi.h>

#include <Arduino.h>


cInitializationState::cInitializationState(cBike* bike, std::string name)
    : cState(name)
{
    _bike = bike;
    _sensLenker = _bike->GetSensorLenker();
    _sensNeigung = _bike->GetSensorNeigung();


    sTransition t_Init_Spinup;
    t_Init_Spinup.stateTo = STATE_INIT;
    t_Init_Spinup.stateFrom = STATE_GYROSPINUP;
    t_Init_Spinup.transitionAction = [&]() { Serial.println("Tranistion INIT -> GYROSPINUP"); };
    t_Init_Spinup.transitionCondition = [&]() 
    { 
        return _sensLenker->getCalibration() == 0 && 
               _sensNeigung->IsCalibrated(); //&& 
               //WisFi.status() == WL_CONNECTED;
    };
    t_Init_Spinup.transitionCondition = []() {};

    AddTransition(t_Init_Spinup);

    //_bike->setup_webserver_methods();
}

cInitializationState::~cInitializationState()
{
    
}


void cInitializationState::enter()
{
    Serial.println("cInitializationState::enter");

    _sensNeigung->loadCalibrationFromMemory();
}



void cInitializationState::process()
{
    
}



void cInitializationState::leave()
{
    Serial.println("cInitializationState::leave");
}

