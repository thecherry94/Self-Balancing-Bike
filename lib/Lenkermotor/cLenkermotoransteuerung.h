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
#define PWML_PIN DAC1
#define PWMR_PIN DAC2
#define CHANNELL 0
#define CHANNELR 1
#define LENKERWINKEL_MAX 80
#define LENKERWINKEL_MIN -80
#define ANDY_LEISTUNG_MAX 30 //die maximiale Leistung die freigegeben
#define DELAY_TIME 10 //ms
#define PREZISION 2 //in Grad

class cLenkermotoransteuerung
{
public:
	cLenkermotoransteuerung();
	bool setLeistung(int pLeistung); //Die Motorleistung in % von -100, Linksdrehen bis 100 Rechtsdrehen, überprüft Motorfreigabe
	bool setMotorfreigabe(bool pMotorfreigabe); //aufrufen um den Motor freizugeben oder zu sperren, Freigabe = 1, Gesperrt = 0; bei Gesperrten Motor die Funktion setzt Leistung auf 0
	int setFrequenz(int pFreq); //Die Frequenz der beiden PWM Pins kann geändert werden
	bool runLenkermotor();
	bool position(int pWinkel, int pLeistung); //Fahre zu gewünschter Position und halte diese. //Eingabe des Winkels +-, Der Fahrleistung , Zyklisch aufrufen! Gibt 1 Zurück wenn Ziel erreicht.

private:
	byte 	m_drehrichtung = 2;
	bool 	m_motorfreigabe = 0;
	int 	m_istleistung = 0;
	int 	m_sollleistung = 0;
	int 	m_istDuty = 0;
	int 	m_freq = 5000;
	unsigned long m_time;
	double Setpoint=5, Input, Output; //Für Regler Motor
	//PID Lenker;//(double &Input,double &Output,double &Setpoint, int x= 5, int y= 3, int v= 1, int o= DIRECT);//ohne #defines Kp, Ki, Kd


	const byte 	m_pwmresolution = 8;
	lenkerDaten Sensordaten;
};

// class cPipsen
// {
// 	cPipsen();
// 	void makesomenoise();
// 	void Beep(int Ton);
// };


#endif