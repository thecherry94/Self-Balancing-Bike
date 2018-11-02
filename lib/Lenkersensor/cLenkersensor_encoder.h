#ifndef LENKERSENSOR__H
#define LENKERSENSOR__H
/*  Autor: Julian Schweizerhof (Till Gostner)
    Name: cLenksensor.h */


////////////// global h //////////////
const unsigned char grn_Pin = 18;  // Pin Definition
const unsigned char wht_Pin = 19;  // Pin Definition
const unsigned char zero_Pin = 5;  // Pin Definition
struct lenkerDaten  // Struct mit Daten für den Lenker
{
  float lenkwinkel; // Winkel des Lenkers in °, in der Mitte: 0, nach links: positv, nach rechts: negativ
  float lenkgeschwindigkeit;  // Winkelgeschwindigkeit in °/s, nach links: positv, nach rechts: negativ
  float lenkbeschleunigung; // Winkelbeschleunigung °/s², nach rechts: positv, nach rechts: negativ
};
///////// cLenkersensor.h /////////////////
void isr_grn();
class cLenkersensor
{
  private: 
    lenkerDaten daten;  // Strukt für die Lenkerdaten mit Winkel, Geschwindigkeit, Beschleunigung
    float lastLenkwinkel; // letzter Lenkwenkel in °, für die Berechnung der Geschwindigkeit 
    float lastLenkgeschwindigkeit;  // letzter Lenkwenkel in °/s, für die Berechnung der Beschleunigung
    unsigned int lastZeit;  // letze Zeit des letzen Messwertes in ms
   public:
    cLenkersensor();  // Konstruktur
    bool getData(lenkerDaten &pdaten);  // Messdaten bekommen, Übergabeparameter: Datenstruct vom Typ lenkerDaten, Rückgabewert: 0: alles okay, 1: außerhalb vom Messbereich
    void setZero(); // Alles null setzen
    void isr_grn();
    int lenkcounter;
};
////// Beispiel Implementierung ////
/*
void setup() {
  Serial.begin(115200);
  pinMode(grn_Pin, INPUT_PULLUP);
  pinMode(wht_Pin, INPUT_PULLUP);
  pinMode(zero_Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(grn_Pin), isr_grn, RISING);
}
unsigned long x;
void loop() {
  Lenkersensor.getData(lDaten);
  Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 
  
  
}
*/

#endif