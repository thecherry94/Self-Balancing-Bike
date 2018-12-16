#include "cRunningState.h"
#include <stdio.h>


cRunningState::cRunningState(cBike* bike, std::string name)
    : cState(name)
{
    _bike = bike;

    _gyroL = _bike->GetGyroL();
    _gyroR = _bike->GetGyroR();

    _lenker = _bike->GetLenkeransteuerung();

    _switchSpinup = false;


    sTransition t_Running_Spinup;
    t_Running_Spinup.stateFrom = STATE_RUNNING;
    t_Running_Spinup.stateTo = STATE_GYROSPINUP;
    t_Running_Spinup.transitionCondition = [&]() { return _switchSpinup; };
    t_Running_Spinup.transitionAction = [&]() {};
}


void cRunningState::enter()
{
     Serial.println("cRunningState::enter");
     //_sensLenker->readCounter();
      //Serial.println("set pointer");
    _lenker->setLenkerSensor(_bike->GetSensorLenker());//cBike->GetSensorLenker());
     // Lenkermotorfreigabe setzen
     // Abfrage, ob Lenker gerade???
    Serial.println("123");
     _lenker->setMotorfreigabe(true);
}



void cRunningState::process()
{
    _gyroL->anlaufen();
    _gyroR->anlaufen();

    if (Serial.available())
    {
        String in = Serial.readStringUntil('\n');
        if(in[0] == 'q')
            _switchSpinup = true;
        else if (in['p'])
        {
            int p;
            sscanf(in.c_str(), "p%d", &p);
            
            _lenker->setLeistung(p);
        }
    }
}



void cRunningState::leave()
{
    Serial.println("cRunningState::leave");

    _switchSpinup = false;
    _lenker->setMotorfreigabe(false);
}