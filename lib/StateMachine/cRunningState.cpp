#include "cRunningState.h"
#include <stdio.h>


#define Motorpoti 27
pinMode(Motorpoti, INPUT);
int potiWert = 0;


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

     // Lenkermotorfreigabe setzen
     // Abfrage, ob Lenker gerade???

    // _lenker->setMotorfreigabe(true);
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
    Motorwert = analogRead(Motorpoti);
    printf("Der Potiwert ist: %d", Motorwert);
    Motorwert-=0.5*4095;
    Motorwert/=(40.95/2);
    printf("Der Potiwert ist: %d\n", Motorwert);

    _lenker->setLeistung(Motorwert);
}



void cRunningState::leave()
{
    Serial.println("cRunningState::leave");

    _switchSpinup = false;
    _lenker->setMotorfreigabe(false);
}