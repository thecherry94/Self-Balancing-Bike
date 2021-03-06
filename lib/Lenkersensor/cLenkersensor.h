/*  Autor: Julian Schweizerhof (Till Gostner)
    Name: cLenksensor.h */

#ifndef LENKERSENSOR__H
#define LENKERSENSOR__H
#include "driver/pcnt.h"

////////////// Lenkersensor global.h //////////////
#define ENCODER_INPUT 15             // Pin Counter Input Definition
#define ENCODER_DIRECTION 4         // Pin Control Input Definition
#define ENCODER_ZERO 5             // Pin Nulldurchgang Definition
struct lenkerDaten  // Struct mit Daten für den Lenker
{
  float lenkwinkel; // Winkel des Lenkers in °, in der Mitte: 0, nach links: positv, nach rechts: negativ
  float lenkgeschwindigkeit;  // Winkelgeschwindigkeit in °/s, nach links: positv, nach rechts: negativ
  float lenkbeschleunigung; // Winkelbeschleunigung °/s², nach rechts: positv, nach rechts: negativ
};
////////////////////////////////////////////////////

///////// cLenkersensor.h /////////////////
#define ENCODER_1 PCNT_UNIT_0       // Name vom ENCODER_1
#define ENCODER_MAX_VALUE 511       // max Zählerwert vom Counter
#define ENCODER_MIN_VALUE -511      // min Zählerwert vom Counter
#define UMRECHNUNGSZAHL 0          // wenn der Nullpunkt nicht in der Mitte ist
#define GENAUIGKEIT 1               // Nach wie vielen Millisekunden wird die Geschwindigkeit neu berechnet?

void isr_zero();            // isr beim Nulldurchgang
void isr_dir();
void isr_input();

#define TOTWINKEL 100

class cLenkersensor
{
  private: 
    lenkerDaten daten;  // Strukt für die Lenkerdaten mit Winkel, Geschwindigkeit, Beschleunigung
    float lastLenkwinkel; // letzter Lenkwenkel in °, für die Berechnung der Geschwindigkeit 
    float lastLenkgeschwindigkeit;  // letzter Lenkwenkel in °/s, für die Berechnung der Beschleunigung
    unsigned int lastZeit;  // letze Zeit des letzen Messwertes in ms
   public:
    cLenkersensor();  // Konstruktur
    void readCounter(); // muss ausgeführt werden, damit die Messwerte kommen

    float getLenkerwinkel();    // return Motorwinkel als float
    float getLenkergeschwindigkeit();
    float getLenkerbeschleunigung();
    bool getData(lenkerDaten &pdaten);  // Messdaten bekommen, Übergabeparameter: Datenstruct vom Typ lenkerDaten, Rückgabewert: 0: alles okay, 1: Lenkermotorbetrieb verboten!!!
    float getMotorwinkel(); // get Motorwinkel in °
    bool getCalibration();
};

////// Beispiel Implementierung ////
/*

cLenkersensor Lenkersensor;         // Objekt des Lenkersensor
lenkerDaten lDaten;                 // Struct von lenkerDaten
void setup() {
    pinMode(ENCODER_INPUT, INPUT);
    pinMode(ENCODER_DIRECTION, INPUT);
    pinMode(ENCODER_ZERO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_ZERO), isr_lenkersensor, RISING);
    Serial.begin(115200);
}
void loop() {
    Lenkersensor.readCounter();
    Lenkersensor.getData(lDaten);
    Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 
}
*/
#endif