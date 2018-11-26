/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date: 11.11.2018  
* Sources: 
* Content: 

* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/

#include "cGyroansteuerung.h"

cGyroansteuerung::cGyroansteuerung(byte GyroPWMPin)
{
  pinMode(GyroPWMPin, OUTPUT);
   Gyro.attach(GyroPWMPin);
    Gyro.writeMicroseconds(GRUNDWERT); //Beep Beep
     Serial.print("Gyro auf Pin=");  Serial.println(GyroPWMPin);
}
 

bool cGyroansteuerung::setLeistung(byte pSollLeistung)
{
  if (pSollLeistung<=100&&pSollLeistung>=0)
  {
    sollLeistung=pSollLeistung*maxLeistung/100+BoostTo-2; //geändert 16.11.2018
     //Serial.println(sollLeistung);
    return 0;
  }
  return 1;
}
bool cGyroansteuerung::anlaufen() //main aufruf jeden Zyklus
{
  if(motorfreigabe == true)
  {
    if(sollLeistung!=istLeistung)
    {
      //magic
      if(millis()>vorigeZeit+beschleunigung||istLeistung<=BoostTo) //geändert 11.11.2018
      {//Schon 3 instanzen ;D
        vorigeZeit=millis();
        istLeistung=istLeistung+1*((sollLeistung-istLeistung)/abs(sollLeistung-istLeistung));
      }
    }
    else return 1;
  }
  else 
	istLeistung=0;
  //PWM Schalten
  int Lokal=GRUNDWERT+istLeistung; 
  Serial.println(istLeistung);
  Gyro.writeMicroseconds(Lokal);
  return 0;
}
bool cGyroansteuerung::setBeschleunigung(byte pBeschleunigung)
{
  if (pBeschleunigung<=60&&pBeschleunigung>=0)
  {
    beschleunigung=pBeschleunigung*10; // 1000/100=10
    return 0;
  }
  return 1;
}
void cGyroansteuerung::setMotorfreigabe(bool pMotorfreigabe)
{
   motorfreigabe=pMotorfreigabe;
   anlaufen();
}

int cGyroansteuerung::getLeistung(bool ist = true)
{
  return ist ? istLeistung : sollLeistung;
}


