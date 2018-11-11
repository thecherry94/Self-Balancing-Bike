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
}
 

bool cGyroansteuerung::setLeistung(byte pSollLeistung)
{
  if (pSollLeistung<=maxLeistung&&pSollLeistung>=0)
  {
    sollLeistung=pSollLeistung;
     Serial.println(sollLeistung);
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
      if(millis()>vorigeZeit+beschleunigung||istLeistung<=GRUNDWERT+BoostTo) //geändert 11.11.2018
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
  Serial.println(Lokal-GRUNDWERT);
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
   //laufen() aufrufen?
}

//Nicht Aktiv

bool cGyroansteuerung::setLookupDrehzahl(unsigned int pDrehzahl)
{
	/*int Zeiger;
	for (int x = 100;x <= 200; x++)
	{
		if (pDrehzahl >= EEPROM.read(x))
		{
			Zeiger = x;
			break;
		}
	}
	sollLeistung = EEPROM.read(Zeiger);*/
  return 0;
}
void cGyroansteuerung::setMachNeLookup(int pMessDrehzahl)
{
	int Adresse = istLeistung + 100; //Ab Adresse 100 bis 200
  EEPROM.begin(4096);
	EEPROM.put(Adresse, pMessDrehzahl);
  EEPROM.commit();
}


int cGyroansteuerung::getLeistung(bool ist = true)
{
  return ist ? istLeistung : sollLeistung;
}


