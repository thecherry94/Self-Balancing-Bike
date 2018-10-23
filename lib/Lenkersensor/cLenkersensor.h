////////////// global h //////////////

#pragma once

const byte pinPoti = 10;


struct lenkerDaten
{
  float lenkwinkel; // [°]
  float lenkgeschwindigkeit; // [°/s]
  float lenkbeschleunigung; // [°/s²]
};

///////// cLenkersensor.h /////////////////
class cLenkersensor
{
  private: 
    lenkerDaten daten;
    float lastLenkwinkel; // [°] 
    float lastLenkgeschwindigkeit; // [°/s]
    unsigned int lastZeit; // in ms
   public:
    cLenkersensor();
    bool getData(lenkerDaten &pdaten);
};
///////// cLenkersensor.cpp /////////////////
cLenkersensor::cLenkersensor()
{
  lastLenkwinkel = analogRead(pinPoti) * 0.3516;
  lastZeit = millis();
}
bool cLenkersensor::getData(lenkerDaten &pdaten)
{
  daten.lenkgeschwindigkeit = ((analogRead(pinPoti) * 0.3516) - lastLenkwinkel) / (millis() - lastZeit) * 1000; // [°/s]
  daten.lenkbeschleunigung = (daten.lenkgeschwindigkeit - lastLenkgeschwindigkeit) / (millis() - lastZeit) * 1000; // [°/s²]
  daten.lenkwinkel = analogRead(pinPoti) * 0.3516;  // [°]
  
  
  pdaten = daten;
  lastLenkwinkel = daten.lenkwinkel;
  lastLenkgeschwindigkeit = daten.lenkgeschwindigkeit;
  lastZeit = millis();
}

///////// main.cpp /////////////////

cLenkersensor Lenkersensor;
lenkerDaten lDaten;
/*void setup() {
  // put your setup code here, to run once:
  pinMode(pinPoti, INPUT);
  
  Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Lenkersensor.getData(lDaten);
  Serial.printf("Winkel: %f grad \t Winkelgeschwindigkeit %f grad/s \t  Winkelbeschleunigung %f grad/s*s \n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung);
}
*/