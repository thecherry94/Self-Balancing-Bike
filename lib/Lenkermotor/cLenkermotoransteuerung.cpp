/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date:08:09.2018  
* Sources: 
* Content:
PINS:
D25   cLenkersteuerung    PWML
D26   cLenkersteuerung    PWMH
D32   cLenkersteuerung    Phase
D33   cLenkersteuerung    Current Sensor

* ToDo: Aufgabe						Bearbeiter		fertig/in Bearbeitung
*	
*/
#include "cLenkermotoransteuerung.h"
#include <Arduino.h>

cLenkermotoransteuerung::cLenkermotoransteuerung()
{
  ledcSetup(m_Channel, m_freq, m_pwmresolution);
  ledcAttachPin(PWML_PIN, m_Channel);
  ledcAttachPin(PWMH_PIN, m_Channel);
  pinMode(PHASE_PIN, OUTPUT);
  pinMode(PWML_PIN, OUTPUT);
  pinMode(PWMH_PIN, OUTPUT);
};

bool cLenkermotoransteuerung::setLeistung(int pLeistung)
{
  m_leistung = pLeistung;   //Der Wert wird zum Schutz in eine lokale Variable gespeichert
    //Serial.print("setLeistung \n");
  if(m_motorfreigabe == 0)  //Es wird überprüft ob der Motor freigegeben ist
  {
    Serial.print("Motorgesperrt \n");
    m_istDuty = PWM_MIN;
    return 1;
  }
  if(m_leistung <-100 || m_leistung >100)
  {
    Serial.print("Bist du Dumm oder was, ALTAA gibt ne gescheite Zahl an!!!! \n");
    return 1;
  }
   

  if(m_leistung <0)
  {
    m_drehrichtung = LENKER_LINKS;
    //Serial.print("Links \n");
    digitalWrite(PHASE_PIN,m_drehrichtung);
  }
  else
  {
    m_drehrichtung = LENKER_RECHTS;
    //Serial.print("Rechts \n");
    digitalWrite(PHASE_PIN,m_drehrichtung);
  }
  m_leistung *=2.55;
  ledcWrite(m_Channel, abs(m_leistung));
  return 0;
}
bool cLenkermotoransteuerung::setMotorfreigabe(bool pMotorfreigabe)
{
      m_motorfreigabe = pMotorfreigabe;
      if(m_motorfreigabe == 0)
      {
        m_leistung = 0;
        ledcWrite(m_Channel, abs(m_leistung));
      }
      return 0;
}   
