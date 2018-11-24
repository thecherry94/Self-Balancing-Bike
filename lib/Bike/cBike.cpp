#include "cBike.h"
#include "cMeasurementLog.h"
#include "stdio.h"


#define hz2ms(x)     1000.0f*(1.0f/(float)x)


#define HTML_SCHECKER_DEMO "<html><head><title>Selbststabilisierendes Fahrrad - Gyro Demo</title><style>*{font-family:Arial,Helvetica,sans-serif;padding:0;margin:0;letter-spacing:2px}h1{font-size:5vmin;margin-bottom:20px}h2{font-size:3vmin}#containerContainer{width:80%;height:100%;display:flex;flex-direction:column;margin-left:auto;margin-right:auto;justify-content:center;color:#3c3c3c}@media (max-width:1000px){#containerContainer{width:100%}}.subjectContainer{height:25%;text-align:center;display:flex;flex-direction:column;align-items:center;justify-content:center;background-color:#fff;font-size:3vmin}#titleContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#statusContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#sliderContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#neigungContainer{border-right:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#sliderRevsSlider{width:95%;margin-left:auto;margin-right:auto}input[type=range]{-webkit-appearance:none;width:100%;margin:22.75px 0}input[type=range]:focus{outline:0}input[type=range]::-webkit-slider-runnable-track{width:100%;height:4.5px;cursor:pointer;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;background:#036;border-radius:2px;border:.2px solid #010101}input[type=range]::-webkit-slider-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer;-webkit-appearance:none;margin-top:-22.95px}input[type=range]:focus::-webkit-slider-runnable-track{background:#004080}input[type=range]::-moz-range-track{width:100%;height:4.5px;cursor:pointer;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;background:#036;border-radius:2px;border:.2px solid #010101}input[type=range]::-moz-range-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer}input[type=range]::-ms-track{width:100%;height:4.5px;cursor:pointer;background:0 0;border-color:transparent;color:transparent}input[type=range]::-ms-fill-lower{background:#00264d;border:.2px solid #010101;border-radius:4px;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d}input[type=range]::-ms-fill-upper{background:#036;border:.2px solid #010101;border-radius:4px;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d}input[type=range]::-ms-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer;height:4.5px}input[type=range]:focus::-ms-fill-lower{background:#036}input[type=range]:focus::-ms-fill-upper{background:#004080}</style><script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script><script>function connect(){set_status_message(\"Connecting...\",\"darkyellow\"),(ws=new WebSocket(\"ws://192.168.0.67/ws\")).onopen=on_open,ws.onmessage=on_msg,ws.onclose=on_close}function on_connection_lost(){ws=null,setTimeout(connect,3e3),connected=!1}function ping(){ws.send(\"__ping__\"),set_status_message(\"Verbunden\",\"green\"),pp_tm=setTimeout(function(){set_status_message(\"Nicht verbunden\",\"red\"),on_connection_lost()},pp_time)}function pong(){clearTimeout(pp_tm),pp_tm=null,connected=!0,ping()}function on_slider_changed(n){var e=parseInt(n/power_max*100);$(\"#sliderRevSliderPerc\").html(e+\"%\"),has_changed=!0}function on_neigung_changed(n){$(\"#neigungValueContainer\").html(n)}function set_status_message(n,e){$(\"#fontStatus\").html(n),$(\"#fontStatus\").attr(\"color\",e)}var ws=null,pp_tm=null,pp_time=1e3,connected=!1;$(function(){connect()});var on_open=function(){set_status_message(\"Verbunden\",\"green\"),setTimeout(ping,1e3),connected=!0},on_msg=function(n){console.log(n);var e=JSON.parse(n.data);\"pong\"!=e.type?\"neigung\"==e.type&&console.log(e.data):pong()},on_close=function(){set_status_message(\"Nicht verbunden\",\"red\"),on_connection_lost()}</script></head><body><div id=\"containerContainer\"><div id=\"titleContainer\" class=\"subjectContainer\"><h1>Gyroansteuerung - Demo</h1><h2>Selbststabilisierendes Fahrrad</h2></div><div id=\"statusContainer\" class=\"subjectContainer\">Status:<br><br><font id=\"fontStatus\" color=\"red\">nicht verbunden</font></div><div id=\"sliderContainer\" class=\"subjectContainer\">Drehzahl [%]<br><br/><input type=\"range\" min=\"1\" max=\"1300\" value=\"0\" id=\"sliderRevsSlider\" oninput=\"on_slider_changed(this.value)\"><br/><div id=\"sliderRevSliderPerc\">0%</div></div><div id=\"neigungContainer\" class=\"subjectContainer\">Neigung [deg]<br><br/><div id=\"neigungValueContainer\">###</div></div></div></body></html>"

static cMeasurementLog<float> lg("Zeit [s]", "Amplitude", "Phase");
static ulong t1 = 0;
static ulong t2 = 0;
static ulong ttotal = 500;
static bool do_log = false;

static int auswuchten_client_id = -1;

cLenkersensor Lenkersensor;
lenkerDaten Sensordaten;

cBike::cBike(byte gyroPWMPin)
    : _gyro(gyroPWMPin)       //Hier wird die cGyro initialisiert
{ 
    // Hier eure Klassen initialisieren
    
   
    // Oder oben im Konstruktor
    // ...


    // Fahrradstatus auf STARTING setzen
    _state = EBikeState::STARTING;
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Bike starting"));


     //Setup Lenkersensor
    pinMode(ENCODER_INPUT, INPUT);
    pinMode(ENCODER_DIRECTION, INPUT);
    pinMode(ENCODER_ZERO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_ZERO), isr_lenkersensor, RISING);

    //Objekte ertellen
   
    //Motor.setFrequenz(500);

    //Lenkersensor Kalibrieren
    Serial.println("Lenkersensor wird kalibriert...");
    // while(Lenkersensor.getData(Sensordaten) == 1)
    // {
    //   ;
    // }
    Serial.println("Lenkersensor kalibriert!!!");

    
}


// Hier werden alle Servermethoden für die Drahtloskommunikation definiert
//
void cBike::setup_webserver_methods()
{

    SERVER->connectToAP(WiFiConfig::apSSID, WiFiConfig::apPASS);

    /*
     **********************************************
     * Gibt den Lenkerwinkel an den Client zurück *
     **********************************************
     */
    SERVER->attachURL("/data/winkel/lenker", [this](AsyncWebServerRequest* req)
    {
        //std::stringstream ss;

        if(req->hasParam("val"))
        {
            int winkel = atoi(req->getParam("val")->value().c_str());

            #ifdef __DEBUG __
                Serial.printf("Lenkerwinkel set %d\n", winkel);
            #endif

            // Hier Winkel setzen
        
            req->send(200, "text/plain", "");
        }
        else
        {
            //sprintf(buf, "[GET] Winkel ist %s", winkel);

            char buf[3];
            sprintf(buf, "%d", -1);
            req->send(200, "text/plain", buf);
        }

        Serial.println("Sending");
        
    }, HTTP_GET);


    /*
     ************************************************
     * Gibt den Neigungswinkel an den Client zurück *
     ************************************************
     */
    SERVER->attachURL("/data/winkel/neigung/get", [this](AsyncWebServerRequest* req)
    {
        
    }, HTTP_GET);

    SERVER->attachURL("/data/auswuchten/toggle", [&](AsyncWebServerRequest* req)
    {
        req->send(200, "text/plain", do_log ? "Logging gestoppt" : "Logging gestartet");
        do_log = !do_log;
        
    }, HTTP_GET);

    SERVER->attachURL("/data/auswuchten/pulse", [&](AsyncWebServerRequest* req)
    {
        req->send(200, "text/plain", "Messpuls für 2s");
        t2 = 500.0L * 1000.0L;

    }, HTTP_GET);

    SERVER->attachURL("/data/auswuchten/reset", [&](AsyncWebServerRequest* req)
    {
        lg.reset();
        req->send(200, "text/plain", "Messlog resetted");
    }, HTTP_GET);


    SERVER->attachURL("/data/auswuchten/gyro", [&](AsyncWebServerRequest* req)
    {
        if(req->hasParam("leistung"))
        {
            int leistung = atoi(req->getParam("leistung")->value().c_str());

            _gyro.setLeistung(leistung);

            char buf[128];
            sprintf(buf, "Leistung gesetzt auf: %d%s", leistung, "%");
            req->send(200, "text/plain", buf);
            
        }
        else
            req->send(200, "text/plain", "Kein Parameter!");
    }, HTTP_GET);


    /*
     ********************************************************
     *             AUSWUCHTEN TEMPORÄR                      *
     * Bietet den momentaten Measurementlog als download an *
     ********************************************************
     */
    SERVER->attachURL("/data/auswuchten/get", [&](AsyncWebServerRequest* req)
    {
        AsyncWebServerResponse* res = req->beginResponse(200, "text/plain", lg.exprt(EMeasurementLogFormatting::FORMAT_EXCEL).c_str());
        res->addHeader("Content-Type", "text/plain");
        res->addHeader("Content-Disposition", "attachment; filename=\"auswuchten.txt\"");

        req->send(res);
    }, HTTP_GET);


    SERVER->attachURL("/gyro/", [&](AsyncWebServerRequest* req)
    {
        req->send(200, "text/html", WebPages::GyroControl);
    }, HTTP_GET);


    SERVER->attachURL("/gyro/leistung", [&](AsyncWebServerRequest* req)
    {
        if(req->hasParam("val"))
        {
            int leistung = atoi(req->getParam("val")->value().c_str());
            _gyro.setLeistung(leistung); 

            Serial.println(leistung);       
        }

        char buf[3];
        sprintf(buf, "%d", _gyro.getLeistung(false));
        req->send(200, "text/plain", buf);
    }, HTTP_GET);


    SERVER->attachURL("/lenker/winkel", [&](AsyncWebServerRequest* req)
    {
        if(req->hasParam("val"))
        {
            // Lenkerwinkel setzen   
        }

        char buf[16];
        sprintf(buf, "%f", _lenkerSensor.getLenkerwinkel());
        req->send(200, "text/plain", buf);
    }, HTTP_GET);






    SERVER->attachSocketEvent("ping", [&](AsyncWebSocket* server, uint32_t client_id, JsonObject& root)
    {
        Serial.print("[WebSocket] got WS event: ");
        Serial.println(root["type"].asString());

        server->client(client_id)->text("{\"type\": \"pong\", \"data\":{}}");
    });



    SERVER->attachSocketEvent("auswuchten_set_client_request", [&](AsyncWebSocket* server, uint32_t client_id, JsonObject& root)
    {
        auswuchten_client_id = client_id;

        char buf[256];
        sprintf(buf, "{\"type\": \"auswuchten_set_client_response\", \"data\": {\"result\": true, \"client_id\": %d}}", auswuchten_client_id);

        server->client(client_id)->text(buf);
        Serial.println("Auswuchten client set");
    });

    Serial.println("Web methods set");

    _Lenkmotor.setLenkerSensor(&_lenkerSensor);
}




void cBike::run()
{
     _gyro.setMotorfreigabe(true); //das war ich und muss es wieder raus nehmen!!!!! MAX (Hust)
     
    // Anfangsstatus setzen
    setup_webserver_methods();

    _livelog = new cLivelog<float>(100, "Zeit[ms]", "Amplitude");
    _livelog->SetSufficientValuesReachedCallback(
        [&](std::vector<float> values, std::vector<std::string> headers, int num_data_in_row, int rows)
    {
        if(auswuchten_client_id > 0)
        {
            const char* json = cLivelog<float>::make_json("auswuchten_data", values, headers, num_data_in_row, rows).c_str();
            SERVER->get_client(auswuchten_client_id)->text(json);
        }
    });

    //_sensorNeigung = new cNeigungssensor(BNO055Config::Address);
    // _Lenkmotor.setBike(this);

    


    _state = EBikeState::RUNNING;
    t1 = millis();
}




void cBike::update()
{
    std::vector<float> data_row;
    data_row.reserve(2);
    data_row.push_back(millis());
    data_row.push_back(5 * sin(2.0 * 3.1416 * (100.0/(millis() / 1000.0))));
    _livelog->write(data_row);

    /*
    //Lenkeransteuerung
   _Lenkmotor.runLenkermotor();
    if ((do_log || t2 > 1) && (micros() - t1 >= ttotal))
    {
        imu::Vector<3> raw_data = _sensorNeigung->getRawData(Adafruit_BNO055::adafruit_vector_type_t::VECTOR_LINEARACCEL);
        Serial.printf("[X]: %f\t[Y]: %f\t[Z]: %f\n", raw_data.x(), raw_data.y(), raw_data.z());

        _lenkerSensor.readCounter();
        lg.write((float)(millis() / 1000.0L), raw_data.z(), _lenkerSensor.getMotorwinkel());

        t1 = micros();

        if (t2 > 1)
            t2 -= ttotal;
    }

    /*if(Sensordaten.lenkwinkel > LENKERWINKEL_MAX || Sensordaten.lenkwinkel < LENKERWINKEL_MIN)
    {
        _Lenkmotor.setMotorfreigabe(false, 4567);
    }
    //Gyromotor
    switch(_state)
    {
        case EBikeState::STARTING:
        // Hier gyro auf drehzal bringen und überprüfen ob es auf drehzahl ist
        // Wenn es auf drehzahl ist, dann auf EBikeState::RUNNING wechseln
        break;

        case EBikeState::RUNNING:
            _gyro.anlaufen();
            //_lenkerSensor.readCounter(); 
        break;
    }
    */
}