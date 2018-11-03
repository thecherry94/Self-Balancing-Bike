/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date:08:09.2018  
* Sources: 
* Content:
PINS:
D25   CLenkermotoransteuerung    PWML
D26   CLenkermotoransteuerung    PWMR


* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*	
*/
#ifndef LENKERMOTORANSTEUERUNG__H
#define LENKERMOTORANSTEUERUNG__H

#include <cLenksensor.h>
#include <Arduino.h>

#define LENKER_LINKS  0
#define LENKER_RECHTS  1
#define PWM_MAX  100
#define PWM_MIN  0
#define MOTORFREIGABE_FREI  1
#define MOTORFREIGABE_GESPERRT  0
#define PWML_PIN DAC1
#define PWMR_PIN DAC2
#define CHANNELL 0
#define CHANNELR 1
#define LENKERWINKEL_MAX 80
#define LENKERWINKEL_MIN -80

class cLenkermotoransteuerung
{
public:
	cLenkermotoransteuerung();
	bool setLeistung(int pLeistung); //Die Motorleistung in % von -100, Linksdrehen bis 100 Rechtsdrehen, überprüft Motorfreigabe
	bool setMotorfreigabe(bool pMotorfreigabe); //aufrufen um den Motor freizugeben oder zu sperren, Freigabe = 1, Gesperrt = 0; bei Gesperrten Motor die Funktion setzt Leistung auf 0
	int setFrequenz(int pFreq); //Die Frequenz der beiden PWM Pins kann geändert werden

private:
	byte 	m_drehrichtung = 2;
	bool 	m_motorfreigabe = 0;
	int 	m_istleistung = 0;
	int 	m_sollleistung = 0;
	int 	m_istDuty = PWM_MIN;
	int 	m_freq = 5000;
	const byte 	m_pwmresolution = 8;
	lenkerDaten Sensordaten;
};


#endif