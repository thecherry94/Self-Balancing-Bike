/*
* File: selfbalancingbike.h
* Autor: AB, ML
* Date: 11.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		Headeraufbau designen		JS & ML 		in Bearbeitung
*/	

#ifndef GYROANSTEUERUNG__H
#define GYROANSTEUERUNG__H


/*************************************
			Includes
*************************************/


#include "ESP32_Servo.h"
#include <EEPROM.h>

/*************************************
			Konstanten
*************************************/

//	Gyroansteuerung

#define BoostTo 0
#define StandardGyroAnlauf 100
#define maxLeistung 100
#define verboteneZahl 6666
#define GRUNDWERT_LINKS 1000
#define GRUNDWERT_RECHTS 1000
#define WARTREZEIT 3000 //ms für Beep Beep

class cGyroansteuerung
{
  private:
  unsigned int beschleunigung= StandardGyroAnlauf; //Zeit für 1% Schritt in ms
  byte sollLeistung, istLeistung;
  bool motorfreigabe=false; //0=Keine Freigabe
  long vorigeZeit=millis()+WARTREZEIT; //Warten zu beginn   //geändert 16.11.2018 nutzlos!
  Servo Gyro;
  //EEPROM von Byte 0 bis 100 //Soll Drehzahl in 1/s Speichern

  public:
  cGyroansteuerung(byte GyroPWMPin);
  bool setLeistung(byte pSollLeistung); //ein WErt in % 0-100, setzt Drehgeschwindigkeit des Gyros
  bool anlaufen(); //return 1 wenn fertig !!Andreung in Diagramm
  bool setBeschleunigung(byte pBeschleunigung); //Zahl in sec bis Gyro komplet von 0 auf 100, Rückgabe ist 0=alles gut, 1 kein zulässiger Wert
  void setMotorfreigabe(bool pMotorfreigabe);
  bool setLookupDrehzahl(unsigned int pDrehzahl);
  void setMachNeLookup(int pMessDrehzahl); //1/min
  int getLeistung();
};



#endif