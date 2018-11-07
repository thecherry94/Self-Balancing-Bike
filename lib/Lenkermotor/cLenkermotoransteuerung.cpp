/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date:06:11.2018  
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
   if(pLeistung <-100 || pLeistung >100)
  {
    LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTOR, "Bist du Dumm oder was, ALTAA gibt ne gescheite Zahl an!!!! \n "));
    return 1;
  }
  if(pLeistung > 0 && pLeistung <10)
    pLeistung = 10;
  else if (pLeistung < 0 && pLeistung >-10)
    pLeistung = -10;
  
  
  m_sollleistung = pLeistung*ANDY_LEISTUNG_MAX/100;   //Der Wert wird zum Schutz in eine lokale Variable gespeichert
   
  
  if(m_motorfreigabe == 0)  //Es wird Ã¼berprÃ¼ft ob der Motor freigegeben ist
  {
    LOG->write(cStatusLogEntry(EStatusLogEntryType::WARNING,MODULE_LENKERMOTOR, "Motor nicht freigegeben"));
    ledcWrite(CHANNELL, 0);
    ledcWrite(CHANNELR, 0);
    m_istleistung = 0;
    m_sollleistung = 0;
    return 1;
  }
 
  if(m_sollleistung <0)  //Eingabe ist kleiner 0, Drehrichtung nach LINKS
  {
    if(m_drehrichtung == LENKER_RECHTS) //Abfrage  ob vorherige Drehrichtung RECHTS war
      {
        ledcWrite(CHANNELR, 0);
        m_time = millis();
      }
      m_drehrichtung = LENKER_LINKS;
  }
  else if (m_sollleistung >0) //Drehrichtung soll nach RECHTS 
  {
    if(m_drehrichtung == LENKER_LINKS)
      {
        ledcWrite(CHANNELL, 0);
        m_time = millis();
      }
      m_drehrichtung = LENKER_RECHTS;
  }
  
  else
  {
    ledcWrite(CHANNELL, 0);
    ledcWrite(CHANNELR, 0);
  }
  return 0;
}

bool cLenkermotoransteuerung::runLenkermotor()
{
  if(m_motorfreigabe == 0)
    return 1;

  if(millis() > m_time+DELAY_TIME )
    {
        switch (m_drehrichtung)  //Ab hier Sicherheitsfunktion!!!!!!!!!!!
        {
          case LENKER_LINKS:
            ledcWrite(CHANNELR, 0);
            m_sollleistung *=2.55; //Äm nein soll das bei jedem aufruf erhöt werden oder was?
            ledcWrite(CHANNELL, m_sollleistung);
          break;  //Das ist Wichtig ;D
          
          case LENKER_RECHTS:
            ledcWrite(CHANNELL, 0);
            m_sollleistung *=2.55;
            ledcWrite(CHANNELR, m_sollleistung);            
          break;

          default:
            ledcWrite(CHANNELL, 0);
            ledcWrite(CHANNELR, 0);
          break;
        }
     }
  return 0;
}


bool cLenkermotoransteuerung::setMotorfreigabe(bool pMotorfreigabe)
{
      
      if(pMotorfreigabe == 1)
      {
        if (Sensordaten.lenkwinkel > LENKERWINKEL_MAX || Sensordaten.lenkwinkel < LENKERWINKEL_MIN)
            {
              LOG->write(cStatusLogEntry(EStatusLogEntryType::ERROR,MODULE_LENKERMOTOR, "Anschlag!!! Keine Motorfreigabe"));
              m_motorfreigabe = 0;
              setLeistung(0);
              return 1;
            }
        else
          m_motorfreigabe = 1;
      }
      else
        m_motorfreigabe = 0;
         
      
      ledcWrite(CHANNELL, 0);
      ledcWrite(CHANNELR, 0);
      m_istleistung = 0;
      m_sollleistung = 0;
      return 0;
}   

int cLenkermotoransteuerung::setFrequenz(int pFreq)
{
  m_freq = pFreq;
  ledcSetup(CHANNELL, m_freq, m_pwmresolution); //Das geht nachträglich noch?
  ledcSetup(CHANNELR, m_freq, m_pwmresolution);
  return 0;
}

bool cLenkermotoransteuerung::position(int pWinkel, int pLeistung)
{
  //Abfrage ob Winkle I.O. ??

//Reglen

  if(Sensordaten.lenkwinkel<=pWinkel+PREZISION && Sensordaten.lenkwinkel>=pWinkel-PREZISION)
  return 1;
  else 
  return 0;
}