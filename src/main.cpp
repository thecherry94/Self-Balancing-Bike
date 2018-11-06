//Lenkermotor Test Main
#include <Arduino.h>
#undef min
#undef max
#include "cLenkermotoransteuerung.h"
#include "cLenkersensor.h"
#include "cBike.h"



const int pPoti = 2; //A2


cBike bike(pPoti);

void setup()
{
    pinMode(pPoti, INPUT);
    Serial.begin(115200);

     
     //Setup Lenkersensor
    pinMode(ENCODER_INPUT, INPUT);
    pinMode(ENCODER_DIRECTION, INPUT);
    pinMode(ENCODER_ZERO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_ZERO), isr_lenkersensor, RISING);
    Serial.begin(115200);


    //Objekte ertellen
    cLenkermotoransteuerung Motor;
    Motor.setFrequenz(1000);
    Motor.setMotorfreigabe(true);
    int Zyklen,StartPWM,SprungPWM;
    Serial.println("ZyklenZahl Anfangsgesch und Sprunggeschwindichkeit eingeben");
    //serialRead(Zyklen);
    //serialRead(StartPWM)
    //serialRead(SprungPWM);
    int APoti[1001], AVolt[1001];

    for(int x=0; x<Zyklen;x++)
    {

        //Anfang finden
        do
        {
            Motor.setLeistung(5);
        } while((analogRead(pPoti)>=10&&analogRead(pPoti)<=20));

        Motor.setLeistung(0); //Wir sind da
        Serial.println("Wir sind da");
        delay(1000);

        // Anfangszustand
        Motor.setLeistung(StartPWM);
        delay(1500);

        //Sprung
        Serial.println("Sprung");
        Motor.setLeistung(SprungPWM);
        for (int x=0; x<1000;x++)
            {
                APoti[x]=analogRead(pPoti);
                //AVolt...
                delay(3);
            }
        Motor.setLeistung(0);
        Serial.println("Stopp");
        for (int x=0; x<1000;x++)
            {
                Serial.println(APoti[x]);
                //AVolt...
                
            }
        Serial.println("Ende");
        
    }
}


void loop()
{
    bike.update();
}