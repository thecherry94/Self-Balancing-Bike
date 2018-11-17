/*
* File: LenkermotorV2.h
* Autor: AB
* Date: 12.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/	


#define TOTZEIT 20 //in ms
#define ANDYFAKTOR 60 //in Prozent
#define CHANNEL 9
#define Frequenz 1000
#define PWM_PIN DAC1
#define dir_PIN DAC2
#define PREZISION 3 //+-Grad
#define Boost 5 //in Prozent
#define MAXSPEED 10000 //in Kp
#define BREMSWINKEL 85


#include <PID_v1.h>
#include "cLenkersensor.h"

class cLenkermotorV2

{

public:

cLenkermotorV2();
void setLeistung(int psollLeistung);            //-100 bis 100
int getLeistung();                              //is klar
void setMotorfreigabe(bool pMotorfreigabe);     //auf true setzen!!! sonnst geht nix
bool Drehen(int pWinkel, int pLeistung);         //noch net fertig
bool running();                                 //Hauptfunktion Zyklisch aufrufen
void setLenkerSensor(cLenkersensor* sensor);



private:

unsigned long Zeit = 0;
bool dir=0;
int sollLeistung=0;
int istLeistung=0;
bool Motorfreigabe=0;
void PWMschalten();
bool dirchange();
//byte sign(int Zahl);
void Bremsen();
double Setpoint, Input, Output;
PID Regler;
cLenkersensor* _lenkerSensor;

};