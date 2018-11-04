#include "cBike.h"


#define hz2ms(x)     1000.0f*(1.0f/(float)x)


#define HTML_SCHECKER_DEMO "<html><head><title>Selbststabilisierendes Fahrrad - Gyro Demo</title><style>*{font-family:Arial,Helvetica,sans-serif;padding:0;margin:0;letter-spacing:2px}h1{font-size:5vmin;margin-bottom:20px}h2{font-size:3vmin}#containerContainer{width:80%;height:100%;display:flex;flex-direction:column;margin-left:auto;margin-right:auto;justify-content:center;color:#3c3c3c}@media (max-width:1000px){#containerContainer{width:100%}}.subjectContainer{height:25%;text-align:center;display:flex;flex-direction:column;align-items:center;justify-content:center;background-color:#fff;font-size:3vmin}#titleContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#statusContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#sliderContainer{border-right:1px solid #3c3c3c;border-bottom:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#neigungContainer{border-right:1px solid #3c3c3c;border-left:1px solid #3c3c3c}#sliderRevsSlider{width:95%;margin-left:auto;margin-right:auto}input[type=range]{-webkit-appearance:none;width:100%;margin:22.75px 0}input[type=range]:focus{outline:0}input[type=range]::-webkit-slider-runnable-track{width:100%;height:4.5px;cursor:pointer;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;background:#036;border-radius:2px;border:.2px solid #010101}input[type=range]::-webkit-slider-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer;-webkit-appearance:none;margin-top:-22.95px}input[type=range]:focus::-webkit-slider-runnable-track{background:#004080}input[type=range]::-moz-range-track{width:100%;height:4.5px;cursor:pointer;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;background:#036;border-radius:2px;border:.2px solid #010101}input[type=range]::-moz-range-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer}input[type=range]::-ms-track{width:100%;height:4.5px;cursor:pointer;background:0 0;border-color:transparent;color:transparent}input[type=range]::-ms-fill-lower{background:#00264d;border:.2px solid #010101;border-radius:4px;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d}input[type=range]::-ms-fill-upper{background:#036;border:.2px solid #010101;border-radius:4px;box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d}input[type=range]::-ms-thumb{box-shadow:1px 1px 1px #000,0 0 1px #0d0d0d;border:1px solid #3c3c3c;height:50px;width:50px;border-radius:25px;background:#fff;cursor:pointer;height:4.5px}input[type=range]:focus::-ms-fill-lower{background:#036}input[type=range]:focus::-ms-fill-upper{background:#004080}</style><script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script><script>function connect(){set_status_message(\"Connecting...\",\"darkyellow\"),(ws=new WebSocket(\"ws://192.168.0.67/ws\")).onopen=on_open,ws.onmessage=on_msg,ws.onclose=on_close}function on_connection_lost(){ws=null,setTimeout(connect,3e3),connected=!1}function ping(){ws.send(\"__ping__\"),set_status_message(\"Verbunden\",\"green\"),pp_tm=setTimeout(function(){set_status_message(\"Nicht verbunden\",\"red\"),on_connection_lost()},pp_time)}function pong(){clearTimeout(pp_tm),pp_tm=null,connected=!0,ping()}function on_slider_changed(n){var e=parseInt(n/power_max*100);$(\"#sliderRevSliderPerc\").html(e+\"%\"),has_changed=!0}function on_neigung_changed(n){$(\"#neigungValueContainer\").html(n)}function set_status_message(n,e){$(\"#fontStatus\").html(n),$(\"#fontStatus\").attr(\"color\",e)}var ws=null,pp_tm=null,pp_time=1e3,connected=!1;$(function(){connect()});var on_open=function(){set_status_message(\"Verbunden\",\"green\"),setTimeout(ping,1e3),connected=!0},on_msg=function(n){console.log(n);var e=JSON.parse(n.data);\"pong\"!=e.type?\"neigung\"==e.type&&console.log(e.data):pong()},on_close=function(){set_status_message(\"Nicht verbunden\",\"red\"),on_connection_lost()}</script></head><body><div id=\"containerContainer\"><div id=\"titleContainer\" class=\"subjectContainer\"><h1>Gyroansteuerung - Demo</h1><h2>Selbststabilisierendes Fahrrad</h2></div><div id=\"statusContainer\" class=\"subjectContainer\">Status:<br><br><font id=\"fontStatus\" color=\"red\">nicht verbunden</font></div><div id=\"sliderContainer\" class=\"subjectContainer\">Drehzahl [%]<br><br/><input type=\"range\" min=\"1\" max=\"1300\" value=\"0\" id=\"sliderRevsSlider\" oninput=\"on_slider_changed(this.value)\"><br/><div id=\"sliderRevSliderPerc\">0%</div></div><div id=\"neigungContainer\" class=\"subjectContainer\">Neigung [deg]<br><br/><div id=\"neigungValueContainer\">###</div></div></div></body></html>"


cBike::cBike(byte gyroPWMPin)
    : _gyro(gyroPWMPin)         //Hier wird die cGyro initialisiert
{ 
    // Hier eure Klassen initialisieren
    
   
    // Oder oben im Konstruktor
    // ...


    // Fahrradstatus auf STARTING setzen
    _state = EBikeState::STARTING;
    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Bike starting"));


    


}


void cBike::run()
{
     _gyro.setMotorfreigabe(true); //das war ich und muss es wieder raus nehmen!!!!!
     
    // Anfangsstatus setzen
    _state = EBikeState::STARTING;

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Trying to connect to " + std::string(WIFI_SSID)));

    // Verbindung mit AP herstellen
    WIFI_COM->connect(WiFiConfig::apSSID, WiFiConfig::apPASS);

    //_sensor_neigung = new cNeigungssensor(55);

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Connection successfull"));

    
    WIFI_COM->attachURL("/measurements/neigung", [](AsyncWebServerRequest* req)
    {
        // Hier wird die Neigung gesendet
    });

    
    WIFI_COM->attachURL("/ui/gyro_demo", [&](AsyncWebServerRequest* req)
    {
        // Hier soll eine HTML-Seite übertragen werden, um das Gyro währenden der Demo
        // für Schecker steuern zu können

        // Hier kann JULIAN seine website einfügen

        req->send(200, "text/html", HTML_SCHECKER_DEMO);
    });

    /*
    WIFI_COM->attachEvent("/control/gyro", [&](AsyncWebServerRequest* req)
    {
        // Hier wird das gyro angesteuert
        // ANDIs part

        // Überprüfen, ob parameter überhaupt gesendet wurde
        if (req->hasParam("power"))
        {
            // Parameter holen
            AsyncWebParameter* p = req->getParam("power");
            
            // Wert ist als string hinterlegt. Wir brauchen aber einen integer
            // Konvertieren
            int power_percent = atoi(p->value().c_str());

            _gyro.setMotorfreigabe(true);
            _gyro.setLeistung(power_percent); 
        }
    });

    // Überprüft den Fahrradstatus
    // Bei genauerer Überlegung eigentlich unnötig und bescheuert
    WIFI_COM->attachEvent("/status", [](AsyncWebServerRequest* req)
    {
        Serial.println("Received status check request");
        req->send(200, "text/html", "s");
    });
    */

   WIFI_COM->attachEvent("pp", [&](AsyncWebSocketClient* client, rapidjson::Value& json) 
   {
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		json.Accept(writer);

        Serial.println(strbuf.GetString());
		client->text(strbuf.GetString());
   });

    LOG->write(cStatusLogEntry(EStatusLogEntryType::NOTIFICATION, MODULE_BIKE, "Shutdown"));


    _state = EBikeState::RUNNING;
}


void cBike::update()
{
    //Lenkeransteuerung
   _Lenkmotor.runLenkermotor();

    if(Sensordaten.lenkwinkel > LENKERWINKEL_MAX || Sensordaten.lenkwinkel < LENKERWINKEL_MIN)
    {
        _Lenkmotor.setMotorfreigabe(false);
    }
    /*********************************************************/
    //Gyromotor
    switch(_state)
    {
        case EBikeState::STARTING:
        // Hier gyro auf drehzal bringen und überprüfen ob es auf drehzahl ist
        // Wenn es auf drehzahl ist, dann auf EBikeState::RUNNING wechseln
        break;

        case EBikeState::RUNNING:
            _gyro.anlaufen();
            _lenkerSensor.readCounter(); 
        break;
    }
    /****************************************************************/
}