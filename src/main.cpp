
//Lenkermotor Test Main
#include <Arduino.h>
#undef min
#undef max
#include "cStateMachine.h"
#include "cBike.h"
#include "cLivelog.h"
#include "global.h"


#include "cInitializationState.h"
#include "cGyroSpinupState.h"
#include "cRunningState.h"
#include "cGyroSpindownState.h"
#include "cEmergencyState.h"






// 19 = LINKS
// 15 = RECHTS
cBike bike(19, 15);

cStateMachine stateMachine;

cInitializationState initState(&bike, STATE_INIT);
cGyroSpinupState spinupState(&bike, STATE_GYROSPINUP);
cRunningState runningState(&bike, STATE_RUNNING);
cGyroSpindownState spindownState(&bike, STATE_GYROSPINDOWN);
cEmergencyState emergencyState(&bike, STATE_EMERGENCY);



void setup()
{
    
    Serial.println("Initialisiere States...");

    stateMachine.AddState(&initState);
    stateMachine.AddState(&runningState);
    stateMachine.AddState(&spinupState);
    stateMachine.AddState(&spindownState);
    stateMachine.AddState(&emergencyState);
    
    Serial.println("States initialisiert.");
}



void loop()
{
    stateMachine.Update();
}





/*

#define Musikleistung 14




static const char* test_site = "<html><head><title>HTTP Test</title></head><script>function btn_click(){var t=new XMLHttpRequest;t.open(\"POST\",\"/json\",!0),t.setRequestHeader(\"Content-Type\",\"application/json\"),t.onreadystatechange=function(){if(4===t.readyState&&200===t.status){var e=JSON.parse(t.responseText);console.log(e)}};var e=JSON.stringify({type:\"add\",data:[4,4,4]});console.log(e),t.send(e)}var txt,btn,lbl;document.addEventListener(\"DOMContentLoaded\",function(t){txt=document.getElementById(\"txt\"),btn=document.getElementById(\"btn\"),lbl=document.getElementById(\"lbl\")})</script><body><input id=\"txt\"/> <button type=\"button\" id=\"btn\" onclick=\"btn_click()\">Send</button><br/><label id=\"lbl\">Response</label></body></html>";

void setup_web_methods();

cBike bike(4);
void setup()
{
    Serial.begin(115200);
    
    pinMode(LED_BUILTIN, OUTPUT);
    EEPROM.begin(8192);
    bike.run();

    
    
    
    setup_web_methods();
}


void loop()
{
    bike.update();
}



void setup_web_methods()
{
    SERVER->connectToAP(WiFiConfig::apSSID, WiFiConfig::apPASS);

    SERVER->attachURL("/", [](AsyncWebServerRequest* req)
    {
        AsyncWebServerResponse* res = req->beginResponse(200, "text/html", test_site);
        req->send(res);
    }, HTTP_GET);

    SERVER->attachURL("/data", [](AsyncWebServerRequest* req)
    {
        AsyncWebServerResponse* res;

        if(req->hasParam("test"))
        {
            const char* param = req->getParam("test")->value().c_str();
            std::string response = std::string("Got your: ") + param;
            res = req->beginResponse(200, "text/plain", response.c_str());
        }
        else
        {
            res = req->beginResponse(200, "text/plain", "No parameter");
        }

        req->send(res);
    }, HTTP_GET);

    SERVER->attachJSON("/json", [](AsyncWebServerRequest* req, JsonVariant& json)
    {
        JsonObject& obj = json.as<JsonObject>();

        if(obj["type"] == "add")
        {
            JsonArray& arr = obj["data"];
            int sum = 0;
            for(int i = 0; i < arr.size(); i++)
            {
                sum += arr[i].as<float>();
            }

            StaticJsonBuffer<200> jsonbuf;
            JsonObject& root = jsonbuf.createObject();
            root["type"] = "sum";
            root["data"] = sum;

            char jsonchar[256];
            root.printTo((char*)jsonchar, root.measureLength() + 1);
            AsyncWebServerResponse* res = req->beginResponse(200, "application/json", jsonchar);
            req->send(res);
        }
    } );
}




/*
const int pPoti = 2; //A2
//cLenkermotoransteuerung Motor;
cLenkermotorV2 Motor;
cLenkersensor _lenkerSensor;
cBike bike(pPoti);
int Zyklen,StartPWM,SprungPWM;
int APoti[1000];
int zeit[1000];
int lastzeit;
int a = 0;
    int b = 0;
    int c = 0;

void setup()
{
    pinMode(pPoti, INPUT);
    Serial.begin(115200);

     //Setup Lenkersensor


    //Objekte ertellen
   Motor.setLenkerSensor(&_lenkerSensor);







  
    
    //Lenkersensor Kalibrieren
    Serial.println("Lenkersensor wird kalibriert...");
    _lenkerSensor.readCounter();
    // while(_lenkerSensor.getCalibration() == 1)
    // { ;}
    Serial.println("Lenkersensor kalibriert!!!");
}


void loop()
{

    
    a = 0;
    b = 0;
    c = 0;
    Serial.println("ZyklenZahl Anfangsgesch und Sprunggeschwindichkeit eingeben");
    while(a == 0&&b==0&&c==0) 
   {
       while(a==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				Zyklen = read.substring(0, read.length()).toInt();
                Serial.println(Zyklen);
				a=1;
			}
		}
	    while(b==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				StartPWM = read.substring(0, read.length()).toInt();
                Serial.println(StartPWM);
				b=1;
			}
		}
	    while(c==0)
	   {
		 while(Serial.available()) 
			{
				String read = Serial.readStringUntil('\n');
				SprungPWM = read.substring(0, read.length()).toInt();
                Serial.println(SprungPWM);
				c=1;
			}
		}
	}
    Serial.println("Musik fängt an!");
   if(true)
   {
       Motor.setMotorfreigabe(true);
        for(int i = 0; i<2;i++)
        {
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
                    // Motor.musik(NOTE_G6,0);
                    // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                    // delay(50);
            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
                    // Motor.musik(NOTE_G6,0);
                    // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                    // delay(50);

            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_DS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(450);
            Motor.musik(NOTE_AS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);

            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_DS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(450);
            Motor.musik(NOTE_AS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);

            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(1200);

            Motor.musik(NOTE_D7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
                    // Motor.musik(NOTE_D7,0);
                    // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                    // delay(50);
            Motor.musik(NOTE_D7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
                    // Motor.musik(NOTE_D7,0);
                    // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                    // delay(50);

                Motor.musik(NOTE_D7,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_DS7,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150);

                Motor.musik(NOTE_FS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_DS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150);

                Motor.musik(NOTE_G6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(1200);
        }
        for (int i = 0; i<2;i++)
        {
            Motor.musik(NOTE_G7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(450);
                // Motor.musik(NOTE_G6,0);
                // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                // delay(50);
            Motor.musik(NOTE_G6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);
                // Motor.musik(NOTE_G6,0);
                // while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                // delay(50);

            Motor.musik(NOTE_G7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_FS7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(450);
            Motor.musik(NOTE_F7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);

            Motor.musik(NOTE_E7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);
            Motor.musik(NOTE_DS7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);
            Motor.musik(NOTE_E7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_GS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(300);

            Motor.musik(NOTE_CS7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_C7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(450);
            Motor.musik(NOTE_B7,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);

            Motor.musik(NOTE_AS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);
            Motor.musik(NOTE_A6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(150);
            Motor.musik(NOTE_AS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(600);
            Motor.musik(NOTE_DS6,Musikleistung);
            while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            delay(300);


            if(i == 0)
            {

                Motor.musik(NOTE_FS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_DS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_FS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150); 

                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_G6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150);
                Motor.musik(NOTE_D7,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(1200);
            }
            else
            {

                Motor.musik(NOTE_FS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_DS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150);

                Motor.musik(NOTE_G6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(600);
                Motor.musik(NOTE_DS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(450);
                Motor.musik(NOTE_AS6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(150);

                Motor.musik(NOTE_G6,Musikleistung);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                delay(1200);       
                
                Motor.musik(2000,0);
                while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
            }

        }
   }
   Serial.println("Musik ist fertig!");

   Serial.println("Motor wird freigegeben...");
   Motor.setMotorfreigabe(true);

     for(int x=0; x<Zyklen;x++)
    {
        //Anfang finden
        do
        {
            _lenkerSensor.readCounter();
            Motor.setLeistung(15);
            while(Motor.runLenkermotor()== 1)
            {;}
        } while(_lenkerSensor.getMotorwinkel()!=0.0);

        Motor.setLeistung(0); //Wir sind da
        while(Motor.runLenkermotor()== 1){;}
        Serial.println("Wir sind da");
        delay(1000);

        // Anfangszustand
        Motor.setLeistung(StartPWM);
        while(Motor.runLenkermotor()== 1){;}
        digitalWrite(35,HIGH);
        delay(1500);


    


        lastzeit = millis();
       
        for (int i=0; i<1000;i++)
            {
                _lenkerSensor.readCounter();
                APoti[i] =_lenkerSensor.getMotorwinkel();
                zeit[i] = millis() - lastzeit;
                delay(1);
                if(i==500)
                {
                     //Sprung
                    Serial.println("Sprung");
                    Motor.setLeistung(SprungPWM);
                    while(Motor.runLenkermotor()== 1){;}        // Das while ist doof!!!!!
                    
                }
            }
        Motor.setLeistung(0);
        while(Motor.runLenkermotor() == 1){;}
        Serial.println("Stopp");
        for (int i=0; i<1000;i++)
            {
                Serial.print(zeit[i]);
                Serial.print(";");
                //Serial.print("Winkel:");
                Serial.println(APoti[i]);
            }
        Serial.println("Ende");
        delay(2000);
        
    }
    
}

*/
