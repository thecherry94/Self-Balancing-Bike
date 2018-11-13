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
#include <PID_v1.h>
#include "cLenkersensor.h"

 cLenkersensor mySensor;

cLenkermotorV2::cLenkermotorV2()
{
ledcSetup(CHANNEL, Frequenz, 8); //8=Resolution
ledcAttachPin(PWM_PIN, CHANNEL);
pinMode(PWM_PIN, OUTPUT);
pinMode(dir_PIN, OUTPUT);
}

bool cLenkermotorV2::setMotorfreigabe(bool pMotorfreigabe)
{
    Motorfreigabe=pMotorfreigabe;
    running();
    return 0;
}

bool cLenkermotorV2::running()
{
    //Freigabe prüfen
    if(Motorfreigabe==false)
    {
        //Abschalten
        istLeistung=0;
        PWMschalten();
        return 1; //Abbruch
        //Fehler
    }
    //Winkel prüfen
    if(abs(mySensor.getLenkerwinkel())<75||mySensor.getCalibration()==1)//n.io.
    {
        istLeistung=0;
        //Fehler
    }
    //Geschwindigkeit Prüfen
    
    //dirchange prüfen
    if(dirchange(sollLeistung))
    {
        //running
        istLeistung=sollLeistung;
        PWMschalten();
        
    }
    //PID compute
    return 0;
    
}

bool cLenkermotorV2::dirchange(int sollLeistung)
{
    if (istLeistung/abs(istLeistung) != sollLeistung/abs(sollLeistung))
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
    //mappen
    abs(istLeistung*255/100);
}

void cLenkermotorV2::setLeistung(int psollLeistung)
{
    if(psollLeistung<=100&&psollLeistung>=-100)
    sollLeistung=psollLeistung*ANDYFAKTOR/100;
    //else
    //Fehler
    
    
}

bool cLenkermotorV2::Drehen(int pWinkel, int pLeistung)
{
    if(pLeistung<=-100&&pLeistung>=100)
    {
        //Fehler
        return 1;
    }
   
    if(pWinkel<=mySensor.getLenkerwinkel()+PREZESSION && pWinkel>=mySensor.getLenkerwinkel()-PREZESSION)
    {
        return 0;
    }
    //PID...
    //sollLeistung=&Output*pLeistung/100;
    return 1;
}

int cLenkermotorV2::getLeistung(void)
{
    return istLeistung;
}