//Lenkermotor Test Main
#include <Arduino.h>
#include "cLenkermotoransteuerung.h"
#include "cLenkersensor.h"

const int pPoti = A2;
pinMode(pPoti, INPUT);
Serial.begin(9600);


main()
{
    //Objekte ertellen
    cLenkermotoransteuerung Motor();
    Motor.setFrequenz(1000);
    Motor.setMotorfreigabe(true);
    int Zyklen,StartPWM,SprungPWM,
    serialPrint("ZyklenZahl Anfangsgesch und Sprunggeschwindichkeit eingeben")
    serialRead(Zyklen);
    serialRead(StartPWM)
    serialRead(SprungPWM);
    int APoti[1001], AVolt[1001];

    for(int x=0; x<Zyklen;x++)
    {

        //Anfang finden
        do{
            Motor.setLeistung(5);
            }while((analaogRead(pPoti)>=10&&<=20))
        Motor.setLeistung(0;) //Wir sind da
        serialPrint("Wir sind da");
        delay(1000);

        // Anfangszustand
        Motor.setLeistung(StartPWM);
        delay(1500);

        //Sprung
        serialPrint("Sprung");
        Motor.setLeistung(SprungPWM);
        for (int x=0; x<1000;x++)
            {
                APoti[x]=analaogRead(pPoti)
                //AVolt...
                delay(3);
            }
        Motor.setLeistung(0);
        serialPrint("Stopp");
        for (int x=0; x<1000;x++)
            {
                serialPrint(APoti[x])
                //AVolt...
                
            }
        serialPrint("Ende");
        
    }
}