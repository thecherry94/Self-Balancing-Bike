/*
*
* Autor: AB;ML
* Date:6.11.2018  
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

#include <Arduino.h>
#include "cStatusLog.h"
#include "cLenkersensor.h"
#include <PID_v1.h>

#define MODULE_LENKERMOTOR "[LENKERMOTOR]"

#define LENKER_LINKS  0
#define LENKER_RECHTS  1
#define MOTORFREIGABE_FREI  1
#define MOTORFREIGABE_GESPERRT  0
#define PWML_PIN 33
#define PWMR_PIN 34
#define CHANNELL 8
#define CHANNELR 9
#define LENKERWINKEL_MAX 80
#define LENKERWINKEL_MIN -80
#define ANDY_LEISTUNG_MAX 60 //die maximiale Leistung die freigegeben
#define DELAY_TIME 10 //ms
#define PREZISION 2 //in Grad

class cLenkermotoransteuerung
{
public:
	cLenkermotoransteuerung();
	bool setLeistung(int pLeistung); //Die Motorleistung in % von -100, Linksdrehen bis 100 Rechtsdrehen, überprüft Motorfreigabe
	bool setMotorfreigabe(bool pMotorfreigabe); //aufrufen um den Motor freizugeben oder zu sperren, Freigabe = 1, Gesperrt = 0; bei Gesperrten Motor die Funktion setzt Leistung auf 0
	int setFrequenz(int pFreq); //Die Frequenz der beiden PWM Pins kann geändert werden
	bool runLenkermotor(); //Bei ret 0 wurde die neue Leistung gesetzt, bei ret 1 ist noch nicht genug Zeit vergangen
	bool position(int pSollwinkel, int pLeistung); //Fahre zu gewünschter Position und halte diese. //Eingabe des Winkels +-, Der Fahrleistung , Zyklisch aufrufen! Gibt 1 Zurück wenn Ziel erreicht.
	
	
	void setLenkerSensor(cLenkersensor* sensor);

private:
	byte 	m_drehrichtung = 2;
	bool 	m_motorfreigabe = 0;
	int 	m_istleistung = 0;
	int 	m_sollleistung = 0;
	int 	m_istDuty = 0;
	int 	m_freq = 5000;
	unsigned long m_time;
	double Setpoint=5, Input, Output; //Für Regler Motor

	const byte 	m_pwmresolution = 8;

	cLenkersensor* _lenkerSensor;
};

// class cPipsen
// {
// 	cPipsen();
// 	void makesomenoise();
// 	void Beep(int Ton);
// };


#endif