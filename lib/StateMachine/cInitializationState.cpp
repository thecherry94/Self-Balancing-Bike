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
               _sensNeigung->IsFullyCalibrated() &&
               WiFi.status() == WL_CONNECTED;
    };

    AddTransition(t_Init_Spinup);

    
    //_bike->setup_webserver_methods();

    _counterWifi = 0;
    pinMode(LED_BUILTIN, OUTPUT);
}

cInitializationState::~cInitializationState()
{
    
}


void cInitializationState::enter()
{
    EEPROM.begin(9600);
    //EEPROM.writeInt(0, 0);
    //EEPROM.commit();

   

    bool create_ap = false;
    bool use_config = false;

    Serial.println("cInitializationState::enter");

    SerialPrettyPrint("Neigungssensor Initialisierungsroutine", 40, '*');
    _bike->InitNeigungssensor();
    _sensNeigung = _bike->GetSensorNeigung();
    _sensNeigung->loadCalibrationFromMemory();




    /*
    while(Serial.available())
    {
        Serial.print("[1] Als Access Point erstellen\n[2] Zu einem Access Point verbinden\n: ");

        char in;
        Serial.readBytes(&in, 1);
        Serial.flush();

        if (in == '1')
        {
            create_ap = false; // Eigentlich true
            break;
        }
        else if (in == '2')
        {
            create_ap = false;
            break;
        }
    }

    Serial.print("\n\n\n");

    while(Serial.available())
    {
        Serial.print("[1] Eigene Werte eintippen\n[2] Standartwerte aus der Konfiguration nehmen\n: ")
        
        char in;
        Serial.readBytes(&in, 1);
        Serial.flush();

        if (in == '1')
        {
            use_config = false;
            break;
        }
        else
        {
            use_config = true;
            break;
        }
    }

    Serial.print("\n\n\n");

    if (use_config)
    {
        Serial.println("Nicht implementiert");
    }
    */

   _counterWifi = millis();

    if (WiFi.status() != WL_CONNECTED)
    {
        if(!create_ap)
            SERVER->connectToAP(WiFiConfig::apSSID, WiFiConfig::apPASS);
    }
}



void cInitializationState::process()
{
    if (millis() - _counterWifi >= 500)
    {
        _counterWifi = millis();

        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}



void cInitializationState::leave()
{
    Serial.println("cInitializationState::leave");
}

