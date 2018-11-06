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


    for(int x=0; x<Zyklen;x++)
void loop()
{
     for(int x=0; x<Zyklen;x++)
    {

        //Anfang finden
        do
        {
            Motor.setLeistung(5);
        } while((analogRead(pPoti)>=10&&analogRead(pPoti)<=20));
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
                APoti[x]=analogRead(pPoti);
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
<<<<<<< HEAD
}

cLenkersensor Lenkersensor;         // Objekt des Lenkersensor
lenkerDaten lDaten;                 // Struct von lenkerDaten

void loop()
{


    Lenkersensor.readCounter();
    if(Lenkersensor.getData(lDaten) == 0)
    {
        Serial.printf("Alles Gut!");
    }
    else
        Serial.printf("Alles Doof!");
    Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 


    bike.update();
    if(flagg == 1)
    {
        Serial.printf("Hoelle!");
    }
=======
    //bike.update();
>>>>>>> 970bdf6920b07ab24863420de4970cd306a37f1c
}