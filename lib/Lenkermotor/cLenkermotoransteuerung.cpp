/*
* File: selfbalancingbike.h
* Autor: AB;ML
* Date:06:11.2018  
* Sources: 
* Content:
PINS:
D25   cLenkersteuerung    PWML
D26   cLenkersteuerung    PWMR

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
  if(pLeistung > 0 && pLeistung <10 && pLeistung !=0)
    pLeistung = 10;
  else if (pLeistung < 0 && pLeistung >-10&& pLeistung !=0)
    pLeistung = -10;
  
  
  m_sollleistung = pLeistung*ANDY_LEISTUNG_MAX*2.55/100;   //Der Wert wird zum Schutz in eine lokale Variable gespeichert
   
  
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

  /*_lenkerSensor->readCounter();
  if (_lenkerSensor->getMotorwinkel() > LENKERWINKEL_MAX || _lenkerSensor->getMotorwinkel() < LENKERWINKEL_ANDY)
            {
              LOG->write(cStatusLogEntry(EStatusLogEntryType::ERROR,MODULE_LENKERMOTOR, "Anschlag!!! Keine Motorfreigabe"));
              m_motorfreigabe = 0;
              setLeistung(0);
              Serial.println("Motor NICHT freigegeben");
              return 1;
            }
*/
  if(millis() > m_time+DELAY_TIME)
    {
      switch (m_drehrichtung)  //Ab hier Sicherheitsfunktion!!!!!!!!!!!
      {
        case LENKER_LINKS:
          ledcWrite(CHANNELR, 0);
          ledcWrite(CHANNELL, abs(m_sollleistung)); 
          /*if(m_sollleistung < m_ramp)
          {
            ledcWrite(CHANNELL, m_ramp); 
            m_ramp++;
          }
          else
          {
            ledcWrite(CHANNELL, m_ramp); 
            m_ramp--;
          }*/

        break;
        
        case LENKER_RECHTS:
          ledcWrite(CHANNELL, 0);
          ledcWrite(CHANNELR, m_sollleistung); 
          /*if(m_sollleistung > m_ramp)
          {
            ledcWrite(CHANNELR, m_ramp);  
            m_ramp--;
          }
           else
          {
            ledcWrite(CHANNELL, m_ramp); 
            m_ramp++;
          }   */    
        break;

        default:
          ledcWrite(CHANNELL, 0);
          ledcWrite(CHANNELR, 0);
        break;
      }
    }
  else
    return 1;
  return 0;
}


bool cLenkermotoransteuerung::setMotorfreigabe(bool pMotorfreigabe)
{
      m_motorfreigabe = 1;
      return 0; //wieder rausnehmen !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if(pMotorfreigabe == true)
      {
        if (_lenkerSensor->getMotorwinkel() > LENKERWINKEL_MAX || _lenkerSensor->getMotorwinkel() < LENKERWINKEL_ANDY)
            {
              LOG->write(cStatusLogEntry(EStatusLogEntryType::ERROR,MODULE_LENKERMOTOR, "Anschlag!!! Keine Motorfreigabe"));
              m_motorfreigabe = 0;
              setLeistung(0);
              Serial.println("Motor NICHT freigegeben");
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
      Serial.println("Motor freigegeben");
      return 0;
}   

int cLenkermotoransteuerung::setFrequenz(int pFreq)
{
  m_freq = pFreq;
  ledcSetup(CHANNELL, m_freq, m_pwmresolution); //Das geht nachträglich noch?
  ledcSetup(CHANNELR, m_freq, m_pwmresolution);
  return 0;
}

bool cLenkermotoransteuerung::position(int pSollwinkel, int pLeistung)
{
  //Abfrage ob Winkle I.O. ??

  Setpoint=pSollwinkel;
  Input= _lenkerSensor->getMotorwinkel();


  if(_lenkerSensor->getMotorwinkel()<=pSollwinkel+PREZISION && _lenkerSensor->getMotorwinkel()>=pSollwinkel-PREZISION)
  return 1;
  else 
  {
    //Lenker.Compute();
    setLeistung(Output*pLeistung);
    return 0;
  }
}


void cLenkermotoransteuerung::setLenkerSensor(cLenkersensor* sensor)
{
  _lenkerSensor = sensor;
}
