#include <Arduino.h>            // damit millis und analogWrite geht.
#include "cLenkersensor_encoder.h"



cLenkersensor::cLenkersensor()
{
  setZero();
}


bool cLenkersensor::getData(lenkerDaten &pdaten)
{
  daten.lenkwinkel = 360/255.0*lenkcounter*9/28.0;
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
void cLenkersensor::setZero()
{
  lastLenkwinkel = 0;
  lastLenkgeschwindigkeit = 0;
  lastZeit = millis();
  lenkcounter = 0;
  daten.lenkbeschleunigung = 0;
  daten.lenkgeschwindigkeit = 0;
  daten.lenkwinkel = 0;
}

cLenkersensor Lenkersensor;   // Objekt des Lenkersensor
lenkerDaten lDaten;           // Struct von lenkerDaten
void isr_grn()
{
  if(digitalRead(wht_Pin) == HIGH)
    Lenkersensor.lenkcounter--;
   else
    Lenkersensor.lenkcounter++;
}
