/*
* File: LenkermotorV2.h
* Autor: AB
* Date: 12.11.2018  
* Sources: 
* Content: Eine Header-Datei um auf alle Konstanten, Variablen und Funktion definieren, die f�r unser Fahrrad ben�tigt werden
* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*		
*/	

//DO NOT TOUCH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define TOTZEIT 80 //in ms  min 20
#define ANDYFAKTOR 50 //in Prozent
#define CHANNEL 2
#define Frequenz 2000
#define PWM_PIN 32
#define dir_PIN 14
#define PREZISION 3 //+-Grad
#define Boost 5 //in Prozent
#define MAXSPEED 1000 //in °/s
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
bool Drehen(int pWinkel, int pLeistung);        //noch net fertig
bool runLenkermotor();                          //Hauptfunktion Zyklisch aufrufen
void setLenkerSensor(cLenkersensor* sensor);
bool musik(int pTon, int pLeistung);




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