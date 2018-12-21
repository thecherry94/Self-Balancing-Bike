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
                else if (dir == 'a') //Links hochfahren
                {
                    /*_blockInput = true;
                    sAutomaticSpinParameters params;
                    params.l = _gyroL;
                    params.r = _gyroR;
                    params.blockInput = &_blockInput;
                    params.taskHandle = &_automaticSpinupTaskHandle;

                    xTaskCreate(&automaticSpinupMain, "automSpinup", 10000, &params, 1, &_automaticSpinupTaskHandle);*/
                    /******* Anlaufen Gyro Links *********************/
                    Flag_anlaufen_links = true;
                    if(Flag_anlaufen_rechts == false&&Flag_anlaufen_links == true) 
                        automaticSpinup_Links(_gyroL, &Flag_anlaufen_links, &Anlauf_case);
                }
                else if (dir == 'b') //Rechts Hochfahren
                {
                    Flag_anlaufen_rechts = true;
                    if (Flag_anlaufen_rechts == true&&Flag_anlaufen_links == false) 
                        automaticSpinup_Rechts(_gyroR, &Flag_anlaufen_rechts, &Anlauf_case);
                }
                else if (dir == 'c') //Beide runterfahren
                {
                    
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
    if (Flag_anlaufen_rechts == false&&Flag_anlaufen_links == true)
        automaticSpinup_Links(_gyroR, &Flag_anlaufen_links,&Anlauf_case);
    if (Flag_anlaufen_rechts == true&&Flag_anlaufen_links == false)
        automaticSpinup_Rechts(_gyroR,&Flag_anlaufen_rechts, &Anlauf_case);
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

   // automaticSpinup(params->l, );
    //automaticSpinup(params->r, );

    *params->blockInput = false;
    vTaskDelete(*params->taskHandle);
}

void automaticSpinup_Links(cGyroansteuerung* g,bool* flag, byte* case_state)
{
   /* g->setLeistung(25);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    g->setLeistung(40);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    g->setLeistung(30);
    vTaskDelay(500 / portTICK_PERIOD_MS);*/
    
        //Anlauframpe Links
        switch (*case_state)
        {
            case 0:
                g->setBeschleunigung(8);
                g->setLeistung(50);
                if(g->getLeistung() == 50)
                    *case_state = 1;
            break;
            case 1:
                g->setBeschleunigung(30);
                g->setLeistung(24);
                if(g->getLeistung() == 24)
                    *case_state = 2;
            break;
            case 2:
                g->setBeschleunigung(100);
                g->setLeistung(30);
                if(g->getLeistung() == 30)
                    *case_state = 3;
            break;
            default:
                *flag =false;
                *case_state = 0;
                break;
        }
}
//Anlauframpe Rechts
void automaticSpinup_Rechts(cGyroansteuerung* g, bool* flag, byte* case_state)
{
        switch (*case_state)
        {
            case 0:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                if(g->getLeistung() == 180)
                    *case_state = 1;
            break;
            case 1:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                delay(2000);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;

            case 2:
                g->setBeschleunigung(1);
                g->setLeistung(80);
                if(g->getLeistung() == 80)
                    *case_state+=1;
            break;
            case 3:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;
            case 4:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                delay(2000);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;

            case 5:
                g->setBeschleunigung(1);
                g->setLeistung(80);
                if(g->getLeistung() == 80)
                    *case_state+=1;
            break;
            case 6:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;
            case 7:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                delay(2000);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;
            
            case 8:
                g->setBeschleunigung(1);
                g->setLeistung(80);
                if(g->getLeistung() == 80)
                    *case_state+=1;
            break;
            case 9:
                g->setBeschleunigung(1);
                g->setLeistung(180);
                if(g->getLeistung() == 180)
                    *case_state+=1;
            break;
            case 10:
                g->setBeschleunigung(1);
                g->setLeistung(130);
                if(g->getLeistung() == 130)
                    *case_state+=1;
            break;
            default:
                *flag =false;
                *case_state = 0;
            break;
        }    
}



void automaticSpindownMain(void* p)
{
    sAutomaticSpinParameters* params = (sAutomaticSpinParameters*)p;

    //automaticSpinup(params->l);
    //automaticSpinup(params->r);

    *params->blockInput = false;
    vTaskDelete(*params->taskHandle);
}

void automaticSpindown(cGyroansteuerung* g)
{
    g->setLeistung(25);
    vTaskDelay(30000 / portTICK_PERIOD_MS);
    g->setLeistung(0);
}