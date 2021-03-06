/*
* File: LenkermotorV2.cpp
* Autor: AB
* Date: 26.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/	

#include <Arduino.h>
#include "cLenkermotorV2.h"

#include "cLenkersensor.h"
#include "cStatusLog.h"

 
template <typename T> int sgn(T val) {
    int x = (T(0) < val) - (val < T(0));
    return (x);
}


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
    Serial.println("Motorfreigabe enter");
    Motorfreigabe=pMotorfreigabe;
    runLenkermotor();
    Serial.println("Motorfreigabe");
    //if (Motorfreigabe)
    //LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTORV2, "Motor=frei"));
    //else
    //LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTORV2, "Motor=aus"));
}

bool cLenkermotorV2::runLenkermotor()
{
    //Freigabe prüfen
    if (_lenkerSensor->getLenkerwinkel() == 666) //Abfrage der Winkelklasse
    {
        Motorfreigabe = false;
        sollLeistung=0;
        istLeistung = 0;
        PWMschalten();
        Serial.println("Irgendein Problem beim Lenkersensor, bitte an Julian wenden!!!");
        return 1;
    }
    if(Motorfreigabe==false)
    {
        //Abschalten
        sollLeistung=0;
        istLeistung = 0;
        PWMschalten();
        return 1;
    }
    //Winkel prüfen
    
    if(_lenkerSensor->getLenkerwinkel()>ANSCHLAG||_lenkerSensor->getLenkerwinkel()<(ANSCHLAG*-1)||_lenkerSensor->getCalibration()==1)//???
    {
        if(_lenkerSensor->getLenkerwinkel()>ANSCHLAG)
            Serial.println("ACHTUNG ANSCHLAG LINKS!!!!");
        else if(_lenkerSensor->getLenkerwinkel()<(ANSCHLAG*-1))
            Serial.println("ACHTUNG ANSCHLAG RECHTS!!!!");
        else 
            Serial.println("Nicht Kalibiert!!!");
        
        sollLeistung=0;

        //Regler abschalten hier.

        //Schubumkehr======================
    if(abs(_lenkerSensor->getLenkerwinkel())>BREMSWINKEL_START&&abs(_lenkerSensor->getLenkerwinkel())<BREMSWINKEL_STOP&&Motorfreigabe)//???
        {
            //Drehen(ANSCHLAG,ANDYFAKTOR);
            int x=_lenkerSensor->getLenkerwinkel();
            sollLeistung=BREMSKRAFT*sgn(x); //Noch TESTEN !!!
            Serial.println("Schubumkehr");
        }
      
    }
    //Geschwindigkeit Prüfen
    // if(abs(_lenkerSensor->getLenkergeschwindigkeit())>MAXSPEED)//n.io.
    // {
    //     Serial.println(_lenkerSensor->getLenkergeschwindigkeit());
    //     Serial.println(abs(_lenkerSensor->getLenkergeschwindigkeit()));



    //     Serial.println("zu hohe Geschwindigkeit");
    //     sollLeistung=(abs(sollLeistung)-1)*sgn(sollLeistung); //Das wird wohl zu Schnell sein oder überschrieben werden
    //     //Fehler
    // }
    
    //dirchange prüfen==================================

    if(dirchange())
    {
        //running
        istLeistung=sollLeistung;
        PWMschalten();
        Regler.Compute();
        return 0;
    }
    Regler.Compute(); 
    return 1;
    
    
}

bool cLenkermotorV2::dirchange()
{
    if (sgn(istLeistung) != sgn(sollLeistung))
    {
        
        //dirchange
        if(sollLeistung<0)
            digitalWrite(dir_PIN,LOW);
        else if(sollLeistung>0)
            digitalWrite(dir_PIN,HIGH);
        else
            digitalWrite(dir_PIN,LOW);
        //Abschalten
        istLeistung=0;
        PWMschalten();
        //timer start
        Zeit=millis();
        istLeistung=sollLeistung;
    }
    else if(millis()>=Zeit+TOTZEIT)
     {
       return true;
     }
    return false;
}

void cLenkermotorV2::PWMschalten()
{
    //Log Motor
    int x = abs(istLeistung*2.55);
    ledcWrite(CHANNEL, x);
}

void cLenkermotorV2::setLeistung(int psollLeistung)
{
    
    if(psollLeistung<=100&&psollLeistung>=-100)
    {   
        if(abs(psollLeistung)<=Boost) psollLeistung=0; //Boost neu 24.12
        sollLeistung=psollLeistung*ANDYFAKTOR/100;
        Regler.SetMode(MANUAL);
    }  
    else
        LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,"MODULE_LENKERMOTORV2", "Bist du Dumm oder so? gibt ne gescheite Zahl an!!!! \n "));
    
}

bool cLenkermotorV2::Drehen(int pWinkel, int pLeistung)
{
    if(pLeistung<=-100&&pLeistung>=100)
    {
        return 1;
    }
   
    if(pWinkel<=_lenkerSensor->getLenkerwinkel()+PREZISION && pWinkel>=_lenkerSensor->getLenkerwinkel()-PREZISION)
    {
        return 0;
    }
    //PID...
    Serial.print("Input"); Serial.println(pWinkel);
    Regler.SetMode(AUTOMATIC);
    Serial.print("MRegler regelt:  "); Serial.println(Output);
    sollLeistung=Output* pLeistung/100;
    //Loging sollLeistung
    //LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION,"MODULE_LENKERMOTORV2", "Hier soll die Leistung stehen \n"));
    return 1;
}

int cLenkermotorV2::getLeistung(void)
{
    return istLeistung;
}

/*
byte cLenkermotorV2::sign(int Zahl)
{
    return(Zahl/abs(Zahl));
    
}*/

void cLenkermotorV2::setLenkerSensor(cLenkersensor* sensor)
{
  _lenkerSensor = sensor;
}

bool cLenkermotorV2::musik(int pTon, int pLeistung)
{
    if(pTon>=1000&&pTon<=5000&&pLeistung<15&&pLeistung>=0)
    {
        setLeistung(pLeistung*-1);
        ledcSetup(CHANNEL, pTon, 8);
        return 0;
    }
    return 1;
}