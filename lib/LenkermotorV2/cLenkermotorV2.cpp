/*
* File: LenkermotorV2.cpp
* Autor: AB
* Date: 12.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/	

#include "cLenkermotorV2.h"

cLenkermotorV2::cLenkermotorV2()
{
ledcSetup(CHANNEL, Frequenz, 8); //8=Resolution
ledcAttachPin(PWM_PIN, CHANNEL);
pinMode(PWM_PIN, OUTPUT);
pinMode(dir_PIN, OUTPUT);
}

bool setMotorfreigabe( pMotorfreigabe)
{
    Motorfreigabe=pMotorfreigabe;
    running();
    return 0;
}

bool running()
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
    if(...)//n.io.
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

bool dirchange(int sollLeistung)
{
    if (sign(istLeistung)!=sign(sollLeistung))
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
        DIRPIN=dir;
        //timer start
        Zeit=millis();
    }
    else if(millis()>=Zeit+TOTZEIT)
    return true;
    
    return false;
}

PWMschalten()
{
    //mappen
    abs(istLeistung*255/100)
}

setLeistung(psollLeistung)
{
    if(psollLeistung<=100&&>=-100)
    sollLeistung=psollLeistung*ANDYFAKTOR/100;
    else
    //Fehler
    
    
}

bool Drehen(int pWinkel int pLeistung)
{
    if(psollLeistung<=-100&&>=100)
    {
        //Fehler
        return 1;
    }
    if(Winkel=...)
    {
        return 0;
    }
    //PID...
    sollLeistung=&Output*pLeistung/100;
    return 1;
}

int getLeistung();
{
    return istLeistung;
}