#include <Arduino.h>            // damit millis und analogWrite geht.
#include "cLenkersensor.h"

///////// cLenkersensor.cpp /////////////////
cLenkersensor::cLenkersensor()
{
  lastLenkwinkel = analogRead(pinPoti) * (-0.083) + 170;
  lastZeit = millis();
}
bool cLenkersensor::getData(lenkerDaten &pdaten)
{
  float messarray[lenksensor_anzahl];
  daten.lenkwinkel = 0;
  for (int i =0; i<lenksensor_anzahl; i++)
  {
    messarray[i] =  analogRead(pinPoti) * (-0.083) + 170;
  }
  quickSort(messarray,0,lenksensor_anzahl-1);
  for (int i =lenksensor_anzahl_loeschen; i<lenksensor_anzahl-lenksensor_anzahl_loeschen; i++)
  {
    daten.lenkwinkel = daten.lenkwinkel + messarray[i];
  }
  daten.lenkwinkel = daten.lenkwinkel / (lenksensor_anzahl-(2*lenksensor_anzahl_loeschen));
  
  daten.lenkgeschwindigkeit = (daten.lenkwinkel - lastLenkwinkel) / (millis() - lastZeit) * 1000; // [°/s]
  daten.lenkbeschleunigung = (daten.lenkgeschwindigkeit - lastLenkgeschwindigkeit) / (millis() - lastZeit) * 1000; // [°/s²]
  pdaten = daten;                                                 // Daten rückgeben
  lastLenkwinkel = daten.lenkwinkel;
  lastLenkgeschwindigkeit = daten.lenkgeschwindigkeit;
  lastZeit = millis();
  if (daten.lenkwinkel >= 169.5 || daten.lenkwinkel <= -169.5)
    return true;
  else return false;
}