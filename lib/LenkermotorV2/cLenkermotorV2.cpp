/*
* File: LenkermotorV2.cpp
* Autor: AB
* Date: 12.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/	

#include <Arduino.h>
#include "cLenkermotorV2.h"

#include "cLenkersensor.h"
#include "cStatusLog.h"

 cLenkersensor mySensor; //Objekt von julian das kann weg.

cLenkermotorV2::cLenkermotorV2() : 
    Regler(&Input, &Output, &Setpoint, (double)4, (double)1, (double)1, P_ON_M, DIRECT) //&Input, &Output, &Setpoint, Kp, Ki, Kd, POn, DIRECT
{
    ledcSetup(CHANNEL, Frequenz, 8); //8=Resolution
    ledcAttachPin(PWM_PIN, CHANNEL);
    pinMode(PWM_PIN, OUTPUT);
    pinMode(dir_PIN, OUTPUT);
    Regler.SetOutputLimits(-255*ANDYFAKTOR/100, 255*ANDYFAKTOR/100);
}

void cLenkermotorV2::setMotorfreigabe(bool pMotorfreigabe)
{
    Motorfreigabe=pMotorfreigabe;
    running();
    //if (Motorfreigabe)
    //LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTORV2, "Motor=frei"));
    //else
    //LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTORV2, "Motor=aus"));
}

bool cLenkermotorV2::running()
{
    //Freigabe prüfen
    if(Motorfreigabe==false)
    {
        //Abschalten
        sollLeistung=0;
        PWMschalten();
        return 1;
    }
    //Winkel prüfen
    if(abs(mySensor.getLenkerwinkel())>BREMSWINKEL-5||mySensor.getCalibration()==1)//n.io.
    {
        LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,"MODULE_LENKERMOTORV2", "Overshot"));
        if (abs(mySensor.getLenkerwinkel())>BREMSWINKEL)
        {
        Drehen(BREMSWINKEL,ANDYFAKTOR);
        LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,"MODULE_LENKERMOTORV2", "Powerbreak"));
        }
        else
        sollLeistung=0;
    }
    //Geschwindigkeit Prüfen
    if(abs(mySensor.getLenkergeschwindigkeit())>MAXSPEED)//n.io.
    {
        sollLeistung=(abs(sollLeistung)-1)*sign(sollLeistung); //Das wird wohl zu Schnell sein oder überschrieben werden
        //Fehler
    }
    
    //dirchange prüfen
    if(dirchange(sollLeistung))
    {
        //running
        istLeistung=sollLeistung;
        PWMschalten();
    }
    Regler.Compute();
    return 0;
    
}

bool cLenkermotorV2::dirchange(int sollLeistung)
{
    if (sign(istLeistung) != sign(sollLeistung))
    {
        //Abschalten
        istLeistung=0;
        PWMschalten();
        //dirchange
        if(sollLeistung<=0)
        dir=0;
        else
        dir=1;
        //Pin
        dir=dir_PIN;
        //timer start
        Zeit=millis();
    }
    else if(millis()>=Zeit+TOTZEIT)
    return true;
    
    return false;
}

void cLenkermotorV2::PWMschalten()
{
    //Log Motor
    ledcWrite(CHANNEL, abs(istLeistung*255/100));
}

void cLenkermotorV2::setLeistung(int psollLeistung)
{
    if(psollLeistung<=100&&psollLeistung>=-100)
    {   
        sollLeistung=psollLeistung*ANDYFAKTOR/100;
        //Regler.SetMode(MANUAL);
    }  
    else
        LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,"MODULE_LENKERMOTORV2", "Bist du Dumm oder so? gibt ne gescheite Zahl an!!!! \n "));

}

bool cLenkermotorV2::Drehen(int pWinkel, int pLeistung)
{
    if(pLeistung<=-100&&pLeistung>=100)
    {
        LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,"MODULE_LENKERMOTORV2", "Bist du Dumm oder so? gibt ne gescheite Zahl an!!!! \n "));
        return 1;
    }
   
    if(pWinkel<=mySensor.getLenkerwinkel()+PREZISION && pWinkel>=mySensor.getLenkerwinkel()-PREZISION)
    {
        return 0;
    }
    //PID...
    
    //Regler.SetMode(AUTOMATIC);
    //Regler.SetOutputLimits(-255*ANDYFAKTOR/100, 255*ANDYFAKTOR/100);
    Serial.print("MRegler regelt:"); Serial.println(Output);
    //sollLeistung=&Output*pLeistung/100;
    //Loging sollLeistung
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION,"MODULE_LENKERMOTORV2", "Hier soll die Leistung stehen \n"));
    return 1;
}

int cLenkermotorV2::getLeistung(void)
{
    return istLeistung;
}

bool cLenkermotorV2::sign(int Zahl)
{
return(Zahl/abs(Zahl));
}
