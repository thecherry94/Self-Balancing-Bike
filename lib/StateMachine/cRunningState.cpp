#include "cRunningState.h"
#include <stdio.h>

#include <stddef.h>
#include <stdio.h>                     // This ert_main.c example uses printf/fflush 
#include "InputOutput_Test.h"          // Model's header file
#include "rtwtypes.h"


#include <iostream>





int Motorwert = 0;



void cRunningState::rt_OneStep(void)
{
	static boolean_T OverrunFlag = false;

	// Disable interrupts here

	// Check for overrun
	if (OverrunFlag) {
		rtmSetErrorStatus(rtObj.getRTM(), "Overrun");
		return;
	}

	OverrunFlag = true;

	// Save FPU context here (if necessary)
	// Re-enable timer or interrupt here
	// Set model inputs here

	rtObj.rtU.e1 = _sensLenker->getLenkerwinkel()/95.0f;
	rtObj.rtU.e2 = _sensLenker->getLenkergeschwindigkeit()/500.0f;
	rtObj.rtU.e3 = _sensNeigung->getRawData().z()/15.0f;
	rtObj.rtU.e4 = _sensNeigung->GetNeigungswinkelgeschwindigkeitZ() / 20.0f;


	// Step the model
	rtObj.step();

	// Get model outputs here
	cout << "Der Reglerausgang: " << rtObj.rtY.reglerausgang << endl;
    _lenker->setLeistung(rtObj.rtY.reglerausgang*100);
	// Indicate task complete
	OverrunFlag = false;

	// Disable interrupts here
	// Restore FPU context here (if necessary)
	// Enable interrupts here
}


cRunningState::cRunningState(cBike* bike, std::string name)
    : cState(name)
{
    _bike = bike;

    _gyroL = _bike->GetGyroL();
    _gyroR = _bike->GetGyroR();
    _sensLenker = _bike->GetSensorLenker();
    _sensNeigung = _bike->GetSensorNeigung();
    _lenker = _bike->GetLenkeransteuerung();

    _switchSpinup = false;


    sTransition t_Running_Spinup;
    t_Running_Spinup.stateFrom = STATE_RUNNING;
    t_Running_Spinup.stateTo = STATE_GYROSPINUP;
    t_Running_Spinup.transitionCondition = [&]() { return _switchSpinup; };
    t_Running_Spinup.transitionAction = [&]() {};
    AddTransition(t_Running_Spinup);
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

    rtObj.initialize();
}

int zaehler = 0;
int Motorwerte[100];

void cRunningState::process()
{
    _gyroL->anlaufen();
    _gyroR->anlaufen();
    _sensLenker->readCounter();
    _lenker->runLenkermotor();

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
    

    //Verfahren mit Poti
    Motorwert = analogRead(27);
    Motorwert-=0.5*4095;
    Motorwert/=(40.95/2);
    Motorwerte[zaehler] = Motorwert;
    printf("Der Potiwert ist: %d\n", Motorwert);
    if(zaehler > 99)
    {
        Motorwert = 0;
        for(int i = 0; i < zaehler; i++)
        {
            Motorwert =  Motorwert + Motorwerte[i];
        }
        Motorwert = Motorwert / zaehler;
        if(Motorwert < 10 && Motorwert > -10)
        {
            _lenker->setLeistung(0);
        }
        else
            _lenker->setLeistung(Motorwert);
        printf("Der Motorwert ist: %d;", Motorwert);
        zaehler = 0;    
    }
    zaehler++;

    //Regler Aufruf==========================0
    //Regler_Interface(cBike* bike)

    rt_OneStep()
}



void cRunningState::leave()
{
    Serial.println("cRunningState::leave");

    _switchSpinup = false;
    _lenker->setMotorfreigabe(false);
}