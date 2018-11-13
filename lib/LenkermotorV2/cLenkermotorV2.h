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
#define ANDYFAKTOR 30 //in Prozent
#define CHANNEL 3
#define Frequenz 1000
#define PWM_PIN 15 //! Noch klätren.  Sollte man das nicht wo gesammelt machen?
#define dir_PIN 16
#define PREZESSION 3 //+-Grad



class cLenkermotorV2

{

public:

cLenkermotorV2();
void setLeistung(int psollLeistung);            //-100 bis 100
int getLeistung();                              //is klar
bool setMotorfreigabe(bool pMotorfreigabe);     //auf true setzen!!! sonnst geht nix
bool Drehen(int pWinkel, int pLeistung);         //noch net fertig
bool running();                                 //Hauptfunktion Zyklisch aufrufen


private:

unsigned long Zeit;
bool dir=0;
int sollLeistung=0;
int istLeistung=0;
bool Motorfreigabe=0;
void PWMschalten();
bool dirchange(int sollLeistung);


};