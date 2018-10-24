/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date: 08.09.2018  
* Sources: 
* Content: 

* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/
/*
//HEADER Kopieren:

#include <Servo.h>
#include <EEPROM.h>
#define Gyro1PWMPin ?
#define StandadGyroAnlauf 15
#define maxLeistung 70
#define verboteneZahl 6666

===================================================

class cGyroansteuerung
{
  private:
  unsigned int beschleunigung= StandadGyroAnlauf; //Zeit für 1% Schritt in ms
  char sollLeistung, istLeistung;
  bool motorfreigabe=false; //0=Keine Freigabe
  long vorigeZeit=clock();
  //EEPROM von Byte 0 bis 100 //Soll Drehzahl in 1/s Speichern

  public:
  cGyroansteuerung();
  bool setLeistung(char pSollLeistung);
  bool laufen(); //return 1 wenn fertig !!Andreung in Diagramm
  bool setBeschleunigung(char pBeschleunigung); //Zahl in s bis Gyro komplet von 0 auf 100
  void setMotorfreigabe(bool pMotorfreigabe);
  // bool setLookupDrehzahl(unsignd int pDrehzahl);
  // void setMachNeLookup(int pMessDrehzahl); //1/min
};


*/

#include "cGyroansteuerung.h"

cGyroansteuerung::cGyroansteuerung(char GyroPWMPin)
{
  pinMode(GyroPWMPin, OUTPUT);
    Gyro.attach(GyroPWMPin);
}
  //???Hier attachen des PINS?

bool cGyroansteuerung::setLeistung(char pSollLeistung)
{
  if (pSollLeistung<maxLeistung&&pSollLeistung>=0)
  {
    sollLeistung=pSollLeistung;
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
      if(millis()>vorigeZeit+beschleunigung) //Schon 3 instanzen ;D
      {
        vorigeZeit=millis();
        istLeistung=istLeistung+1*((sollLeistung-istLeistung)/abs(sollLeistung-istLeistung));
      }
    }
    else return 1;
  }
  else 
	istLeistung=0;
  //PWM Schalten
  int Lokal=1000+istLeistung*10; 
  Gyro.writeMicroseconds(Lokal);
  return 0;
}
bool cGyroansteuerung::setBeschleunigung(char pBeschleunigung)
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


