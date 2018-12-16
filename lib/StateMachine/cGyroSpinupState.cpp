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

    _gyroL->setMotorfreigabe(true);
    _gyroR->setMotorfreigabe(true);

    _exit = false;
    _blockInput = false;


    sTransition t_Spinup_Running;
    t_Spinup_Running.stateFrom = STATE_GYROSPINUP;
    t_Spinup_Running.stateTo = STATE_RUNNING;
    t_Spinup_Running.transitionCondition = [&]() { return _exit; };
    t_Spinup_Running.transitionAction = [&]() {};
    AddTransition(t_Spinup_Running);
}


void cGyroSpinupState::enter()
{
    Serial.println("cGyroSpinupState::enter");
    _gyroL->setMotorfreigabe(true);
    _gyroR->setMotorfreigabe(true);

    digitalWrite(LED_BUILTIN, LOW);
}



void cGyroSpinupState::process()
{
    if(Serial.available())
    {
        String in;
        in = Serial.readStringUntil('\n');

        if (!_blockInput)
        {
            if(in[0] == 'p')
            {
                int p = 0;
                char dir = ' ';
                sscanf(in.c_str(), "p%c%d", &dir, &p);

                if (dir == 'l')
                {
                    _gyroL->setLeistung(p);
                    Serial.printf("Linke Gyroleistung auf %d%% gesetzt.", p);
                }
                else if (dir == 'r')
                {
                    _gyroR->setLeistung(p);
                    Serial.printf("Rechte Gyroleistung auf %d%% gesetzt.", p);
                }
                else if (dir == 'a')
                {
                    _blockInput = true;
                    sAutomaticSpinParameters params;
                    params.l = _gyroL;
                    params.r = _gyroR;
                    params.blockInput = &_blockInput;
                    params.taskHandle = &_automaticSpinupTaskHandle;

                    xTaskCreate(&automaticSpinupMain, "automSpinup", 10000, &params, 1, &_automaticSpinupTaskHandle);
                }
                else if (dir == 's')
                {
                    _blockInput = true;
                    sAutomaticSpinParameters params;
                    params.l = _gyroL;
                    params.r = _gyroR;
                    params.blockInput = &_blockInput;
                    params.taskHandle = &_automaticSpindownTaskHandle;

                    xTaskCreate(&automaticSpindownMain, "automSpindown", 10000, &params, 1, &_automaticSpindownTaskHandle);
                }
            }
            else if (in[0] == 'q')
            {
                _exit = true;
            }
        }
        else
        {
            Serial.println("Automatic spin up/down is running. User input blocked");
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



void automaticSpinupMain(void* p)
{
    sAutomaticSpinParameters* params = (sAutomaticSpinParameters*)p;

    automaticSpinup(params->l);
    automaticSpinup(params->r);

    *params->blockInput = false;
    vTaskDelete(*params->taskHandle);
}

void automaticSpinup(cGyroansteuerung* g)
{
    g->setLeistung(25);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    g->setLeistung(40);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    g->setLeistung(30);
    vTaskDelay(500 / portTICK_PERIOD_MS);
}



void automaticSpindownMain(void* p)
{
    sAutomaticSpinParameters* params = (sAutomaticSpinParameters*)p;

    automaticSpinup(params->l);
    automaticSpinup(params->r);

    *params->blockInput = false;
    vTaskDelete(*params->taskHandle);
}

void automaticSpindown(cGyroansteuerung* g)
{
    g->setLeistung(25);
    vTaskDelay(30000 / portTICK_PERIOD_MS);
    g->setLeistung(0);
}