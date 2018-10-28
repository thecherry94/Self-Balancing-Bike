/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date:08:09.2018  
* Sources: 
* Content:
PINS:
D25   CLenkermotoransteuerung    PWML
D26   CLenkermotoransteuerung    PWMH
D32   CLenkermotoransteuerung    Phase
D33   CLenkermotoransteuerung    Current Sensor
D34   CLenkermotoransteuerung    Error 1
D35   CLenkermotoransteuerung    Error 2

* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*	
*/
#pragma once

#define LENKER_LINKS  0
#define LENKER_RECHTS  1
#define PWM_MAX  100
#define PWM_MIN  0
#define MOTORFREIGABE_FREI  1
#define MOTORFREIGABE_GESPERRT  0
#define PHASE_PIN 32
#define PWML_PIN DAC1
#define PWMH_PIN DAC2

class cLenkermotoransteuerung
{
public:
	cLenkermotoransteuerung();
	bool setLeistung(int pLeistung); //Die Motorleistung in % von -100, Linksdrehen bis 100 Rechtsdrehen, überprüft Motorfreigabe
	bool setMotorfreigabe(bool pMotorfreigabe); //aufrufen um den Motor freizugeben oder zu sperren, Freigabe = 1, Gesperrt = 0; bei Gesperrten Motor die Funktion setzt Leistung auf 0

private:
	bool 	m_drehrichtung = 1;
	bool 	m_motorfreigabe = 0;
	int 	m_leistung = 0;
	int 	m_istDuty = PWM_MIN;
    bool 	m_error1 = 0;
    bool 	m_error2 = 0;
	int 	m_freq = 5000;
	char 	m_pwmresolution = 8;
	char 	m_Channel = 0;
};