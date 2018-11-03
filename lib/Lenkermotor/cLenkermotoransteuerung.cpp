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

cLenkermotoransteuerung::cLenkermotoransteuerung()
{
  ledcSetup(CHANNELL, m_freq, m_pwmresolution);
  ledcSetup(CHANNELR, m_freq, m_pwmresolution);
  ledcAttachPin(PWML_PIN, CHANNELL);
  ledcAttachPin(PWMR_PIN, CHANNELR);
  pinMode(PWML_PIN, OUTPUT);
  pinMode(PWMR_PIN, OUTPUT);
};

bool cLenkermotoransteuerung::setLeistung(int pLeistung)
{
  m_sollleistung = pLeistung;   //Der Wert wird zum Schutz in eine lokale Variable gespeichert
    //Serial.print("setLeistung \n");
  if(m_motorfreigabe == 0 || Sensordaten.lenkwinkel > LENKERWINKEL_MAX || Sensordaten.lenkwinkel < LENKERWINKEL_MIN)  //Es wird überprüft ob der Motor freigegeben ist
  {
    Serial.print("Motorgesperrt \n");
    ledcWrite(CHANNELL, 0);
    ledcWrite(CHANNELR, 0);
    m_istleistung = 0;
    m_sollleistung = 0;
    return 1;
  }
  if(m_sollleistung <-100 || m_sollleistung >100)
  {
    Serial.print("Bist du Dumm oder was, ALTAA gibt ne gescheite Zahl an!!!! \n");
    return 1;
  }

  if(m_sollleistung <0)
  {
    if(m_drehrichtung == LENKER_RECHTS)
      {
        ledcWrite(CHANNELR, 0);
        delay(3);
        ledcWrite(CHANNELR, 0);
      }
      m_drehrichtung = LENKER_LINKS;
  }
  else if (m_sollleistung >0)
  {
    if(m_drehrichtung == LENKER_LINKS)
      {
        ledcWrite(CHANNELL, 0);
        delay(3);
        ledcWrite(CHANNELL, 0);
      }
      m_drehrichtung = LENKER_RECHTS;
  }

switch (m_drehrichtung)
{
  case 0:
    ledcWrite(CHANNELR, 0);
    m_sollleistung *=2.55;
    for(byte i = 0; i < abs(m_sollleistung); i++)
    {
      ledcWrite(CHANNELL, i);
      delay(2);
    }
  break;
  
  case 1:
    ledcWrite(CHANNELL, 0);
    m_sollleistung *=2.55;
    for(byte i = 0; i < abs(m_sollleistung); i++)
    {
      ledcWrite(CHANNELR, i);
      delay(2);
    }
  break;

  default:
    ledcWrite(CHANNELL, 0);
    ledcWrite(CHANNELR, 0);
  break;
}
  return 0;
}

bool cLenkermotoransteuerung::setMotorfreigabe(bool pMotorfreigabe)
{
      m_motorfreigabe = pMotorfreigabe;
      if(m_motorfreigabe == 0)
      {
        if (Sensordaten.lenkwinkel > LENKERWINKEL_MAX || Sensordaten.lenkwinkel < LENKERWINKEL_MIN)
            {
              Serial.print("Motorgesperrt \n");
            }
        else
          m_motorfreigabe = 1;
      }
      ledcWrite(CHANNELL, 0);
      ledcWrite(CHANNELR, 0);
      m_istleistung = 0;
      m_sollleistung = 0;
      return 0;
}   

int cLenkermotoransteuerung::setFrequenz(int pFreq)
{
  m_freq = pFreq;
  ledcSetup(CHANNELL, m_freq, m_pwmresolution);
  ledcSetup(CHANNELR, m_freq, m_pwmresolution);
  return 0;
}