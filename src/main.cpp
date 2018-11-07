//Lenkermotor Test Main
#include <Arduino.h>
#undef min
#undef max
//#include "cLenkermotoransteuerung.h"
//#include "cLenkersensor.h"
//#include "cBike.h"
#include "cWebServer.h"
#include "global.h"

static const char* test_site = "<html><head><title>HTTP Test</title></head><script>function btn_click(){var t=new XMLHttpRequest;t.open(\"POST\",\"/json\",!0),t.setRequestHeader(\"Content-Type\",\"application/json\"),t.onreadystatechange=function(){if(4===t.readyState&&200===t.status){var e=JSON.parse(t.responseText);console.log(e)}};var e=JSON.stringify(\'{\"type\": \"add\", \"data\": [4, 4, 4]}\');console.log(e),t.send(e)}var txt,btn,lbl;document.addEventListener(\"DOMContentLoaded\",function(t){txt=document.getElementById(\"txt\"),btn=document.getElementById(\"btn\"),lbl=document.getElementById(\"lbl\")})</script><body><input id=\"txt\"/> <button type=\"button\" id=\"btn\" onclick=\"btn_click()\">Send</button><br/><label id=\"lbl\">Response</label></body></html>";

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

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
        Serial.println("JSON CALLED");
        obj.prettyPrintTo(Serial);

        if(obj["type"].asString() == "add")
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
            Serial.println("JSON SENT");
            return;
        }

        Serial.println("JSON ERROR");
    });
}


void loop()
{

}



/*

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

cLenkersensor Lenkersensor;         // Objekt des Lenkersensor
lenkerDaten lDaten;                 // Struct von lenkerDaten


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
    Lenkersensor.readCounter();
    if(Lenkersensor.getData(lDaten) == 0)
    {
        Serial.printf("Alles Gut!");
    }
    else
        Serial.printf("Alles Doof!");
    Serial.printf("%f;%f;%f\n", lDaten.lenkwinkel, lDaten.lenkgeschwindigkeit, lDaten.lenkbeschleunigung); 
}
*/