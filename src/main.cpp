//Lenkermotor Test Main
#include <Arduino.h>
#undef min
#undef max
#include "cLenkermotoransteuerung.h"
#include "cLenkersensor.h"
#include "cBike.h"



const int pPoti = 2; //A2
lenkerDaten Sensordaten;
cLenkermotoransteuerung Motor;
cBike bike(pPoti);
int Zyklen,StartPWM,SprungPWM;
int APoti[1001];
int AVolt[1001];


void setup()
{
    pinMode(pPoti, INPUT);
    Serial.begin(115200);

<<<<<<< HEAD
=======
     
     //Setup Lenkersensor
    pinMode(ENCODER_INPUT, INPUT);
    pinMode(ENCODER_DIRECTION, INPUT);
    pinMode(ENCODER_ZERO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_ZERO), isr_lenkersensor, RISING);
    Serial.begin(115200);

>>>>>>> 04f0484013030b900650b8203ee4d75e632cf85a

    //Objekte ertellen
   
    Motor.setFrequenz(1000);
    Motor.setMotorfreigabe(true);
    Serial.println("ZyklenZahl Anfangsgesch und Sprunggeschwindichkeit eingeben");
    
    int a = 0;
    int b = 0;
    int c = 0;
   
while(a == 0&&b==0&&c==0) 
   {
       while(a==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				Zyklen = read.substring(1, read.length()).toInt();
				a=1;
			}
		}
	    while(b==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				StartPWM = read.substring(1, read.length()).toInt();
				b=1;
			}
		}
	    while(c==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				SprungPWM = read.substring(1, read.length()).toInt();
				c=1;
			}
		}
	}
   
}


void loop()
{
     for(int x=0; x<Zyklen;x++)
    {

        //Anfang finden
        do
        {
            Motor.setLeistung(5);
        } while((Sensordaten.lenkwinkel>=10&&Sensordaten.lenkwinkel<=20));

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
                APoti[x]=Sensordaten.lenkwinkel;
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
    //bike.update();
}