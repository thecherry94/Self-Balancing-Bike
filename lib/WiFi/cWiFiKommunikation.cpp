#include "cWiFiKommunikation.h"



/*
void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT)
  {
    //client connected
    
  } 
  else if(type == WS_EVT_DISCONNECT)
  {
    //client disconnected
    //os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } 
  else if(type == WS_EVT_ERROR)
  {
    //error was received from the other end
    //os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } 
  else if(type == WS_EVT_PONG)
  {
    //pong message was received (in response to a ping request maybe)
    //os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } 
  else if(type == WS_EVT_DATA)
  {
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len)
    {
      //the whole message is in a single frame and we got all of it's data
      //os_printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      if(info->opcode == WS_TEXT)
      {
        //os_printf("%s\n", (char*)data);
        
        data[len] = 0;

        Serial.print("Got something: ");
        Serial.println((char*)data);

        std::string d = std::string((char*)data);

        if(d == "__ping__")
        {
        	client->text("__pong__");
        }
      } 
      else 
      {
        for(size_t i=0; i < info->len; i++)
        {
          //os_printf("%02x ", data[i]);
        }
        //os_printf("\n");
      }
      if(info->opcode == WS_TEXT)
        client->text("I got your text message");
      else
        client->binary("I got your binary message");
    } 
    else 
    {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if(info->index == 0)
      {
        //if(info->num == 0)
          //os_printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
        //os_printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
      }

      //os_printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT)?"text":"binary", info->index, info->index + len);
      if(info->message_opcode == WS_TEXT)
      {
        data[len] = 0;
        //os_printf("%s\n", (char*)data);
      } 
      else 
      {
        for(size_t i=0; i < len; i++)
        {
          //os_printf("%02x ", data[i]);
        }
        //os_printf("\n");
      }

      if((info->index + len) == info->len)
      {
        //os_printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
        if(info->final)
        {
            //os_printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
            
        }
      }
    }
  }
}
*/


/*
void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

	if(type == WS_EVT_DATA)
	{
		//data packet
		AwsFrameInfo * info = (AwsFrameInfo*)arg;
		if(info->final && info->index == 0 && info->len == len)
		{
			//the whole message is in a single frame and we got all of it's data
			//os_printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
			if(info->opcode == WS_TEXT)
			{
				data[len] = 0;
				std::string d = std::string((char*)data);

				if(d == "__ping__")
				{
					client->text("__pong__");
				}
			}
		} 
	}
}

*/


/*
if(d == "__ping__")
                {
                    std::stringstream ss;					
                    ss << "{";
                    ss << "\"type\":";
                    ss << "\"pong\"" << ", ";
                    ss << "\"data\":{";
                    ss << "}}";

                    client->text(ss.str().c_str());
                }
                else if(d == "neigung")
                {
                    sensors_vec_t v;
                    v = _sensor_neigung->getEvent().orientation;

                    std::stringstream ss;					
                    ss << "{";
                    ss << "\"type\":";
                    ss << "\"neigung\"" << ", ";
                    ss << "\"data\":{";
                    ss << "\"x\":" << v.x << ", ";
                    ss << "\"y\":" << v.y << ", ";
                    ss << "\"z\":" << v.z;
                    ss << "}}";

                    client->text(ss.str().c_str());
                }
*/


cWiFiKommunikation::cWiFiKommunikation()
{
  
}


void cWiFiKommunikation::attachURL(String url, ArRequestHandlerFunction request_handler)
{
    _pserver->on(url.c_str(), HTTP_GET, request_handler);
}

void cWiFiKommunikation::attachEvent(const char* name, WiFiEventHandler_t func)
{
	_events[name] = func;
}

/*
AsyncWebSocket* cWiFiKommunikation::attachWebSocket(std::string url)
{
	AsyncWebSocket* ws = new AsyncWebSocket(url.c_str());
	_pserver->addHandler(ws);
	_pserver->begin();
	return ws;
}
*/

// Verbindet den ESP zum spezifizierten WiFi-Netz und startet einen asynchronen Webserver
// und startet eine WebSockets-Schnittstelle
bool cWiFiKommunikation::connect(String ssid, String pw)
{
	// Bereits Verbunden? Falls ja, bestehende Verbindung beenden und Speicher freigeben
    if (WiFi.status() == WL_CONNECTED)
    {
		//WiFi.close();

        delete _pserver;
        _pserver = NULL;

		delete _pws;
		_pws = NULL;
    }

	// Statusmeldung
    Serial.print("Verbindungsaufbau mit: ");
    Serial.println(ssid);

	// Verbinde zu AP
    WiFi.begin(ssid.c_str(), pw.c_str());

	// Serial Signal ausgeben und eingebaut LED blinken lassen während Verbindungsvorgang
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
		digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
	}

	// Wenn die Verbindung aufgebaut worden ist leuchtet die LED konstant
	digitalWrite(LED_BUILTIN, HIGH);

	// Statusmeldung auf Serial ausgeben und IP Adresse
    Serial.println("WiFi Verbindung erfolgreich hergestellt");
    Serial.print("IP Adresse: ");
    Serial.println(WiFi.localIP());



	// WebSockets Schnittstelle erstellen
    _pws = new AsyncWebSocket("/ws");
    _pws->onEvent([&](AsyncWebSocket* server, AsyncWebSocketClient* client, 
        AwsEventType type, void* arg, 
        uint8_t* data, size_t len)
    {
		Serial.print("got");

        if(type == WS_EVT_DATA)
	    {
			AwsFrameInfo * info = (AwsFrameInfo*)arg;
            //the whole message is in a single frame and we got all of its data
            //os_printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
            if(info->opcode == WS_TEXT)
            {	
				// Daten aufbereiten
				//
                data[len] = 0;
                std::string d = std::string((char*)data);

				// JSON parsen
				rapidjson::Document doc;
				doc.Parse(d.c_str());

				// Event Name
				std::string type = doc["type"].GetString();

				// Suche in der event hashmap, ob dieses event existiert
				if (_events.find(type) != _events.end())
				{
					// Existiert
					//

					// Event ausführen
					_events[type](client, doc["data"]);
				}
            } 
	    }
    });

	// WebServer erstellen auf Port 80 mit WebSockets Schnittstelle
    _pserver = new AsyncWebServer(80);
    _pserver->addHandler(_pws);
    
    // Server starten	
    _pserver->begin();

	// Erfolg
    return true;
}


bool cWiFiKommunikation::connectSoftAP(String ssid, String pw)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return false;
    }

    Serial.print("Erstelle Soft AP: ");
    Serial.println(ssid);

    WiFi.softAP(ssid.c_str(), pw.c_str());

    Serial.println("Soft Access Point erstellt");
    Serial.print("IP Adresse: ");
    Serial.println(WiFi.softAPIP());

    _pserver = new AsyncWebServer(80);
    _pserver->begin();

    return true;
}