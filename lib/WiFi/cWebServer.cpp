#include "cWebServer.h"



void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{}


cWebServer::cWebServer()
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
}



void cWebServer::connectToAP(const char* ssid, const char* pass)
{
    // Starte Verbindungsaufbau
    WiFi.begin(const_cast<char *> (ssid), const_cast<char *> (pass));

    // Statusmeldung per Serial und feedback während Verbindungsaufbau
    // TODO delay entfernen bzw. thread starten
    Serial.print("Connecting to ");
    Serial.println(ssid);

    /*
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    */

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connection established.\n Local IP: ");
    Serial.println(WiFi.localIP().toString().c_str());

    // Web server auf Port 80 starten
    _pserver = new AsyncWebServer(80);
    _pserver->begin();

    _pws = new AsyncWebSocket("/ws");
    _pws->onEvent(
        std::bind(&cWebServer::onWebSocketEvent, this, 
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    _pserver->addHandler(_pws);

    _pserver->onNotFound([](AsyncWebServerRequest *request) 
    {
	    if (request->method() == HTTP_OPTIONS) 
        {
		    request->send(200);
	    } 
        else 
        {
		    request->send(404);
	    }
    });
}


void cWebServer::attachURL(const char* url, ArRequestHandlerFunction func, WebRequestMethod method = HTTP_GET)
{
    _pserver->on(url, method, func);
}


void cWebServer::attachJSON(const char* url, ArJsonRequestHandlerFunction handler)
{
    _pserver->addHandler(new AsyncCallbackJsonWebHandler(url, handler));
}


void cWebServer::attachSocketEvent(char* name, AsyncWebSocketEventHandler handler)
{
    _socket_events[name] = handler;
}


void cWebServer::onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{
    switch(type)
    {
        case AwsEventType::WS_EVT_CONNECT:
            Serial.println("[WebSocket] New client connected");
            break;
        
        case AwsEventType::WS_EVT_DISCONNECT:
            Serial.println("[WebSocket] Client disconnected");
            break;
        
        case AwsEventType::WS_EVT_ERROR:
            Serial.println("[WebSocket] WebSocket error");
            break;
        
        case AwsEventType::WS_EVT_DATA:
            AwsFrameInfo* info = (AwsFrameInfo*)arg;

            if (info->opcode == WS_TEXT)
            {
                data[len] = 0;
                char* d = (char*)data;
                
                Serial.print("[WebSocket] Got message: ");
                Serial.println(d);

                StaticJsonBuffer<512> jsonbuf;
                JsonObject& root = jsonbuf.parse(d);

                if (root.success())
                {
                    Serial.println("[WebSocket] Valid Json received");

                    if (root.containsKey("type"))
                    {
                        Serial.println("[WebSocket] Json correct format");
                        _socket_events[root["type"].asString()](server, client->id(), root);
                    }
                    else
                    {
                        Serial.println("[WebSocket] Json incorrect format");
                    }
                }
                else
                {
                    Serial.println("[WebSocket] Invalid Json received");
                }
            }
            break;
    }


}


AsyncWebSocketClient* cWebServer::get_client(uint8_t client_id)
{
    return _pws->client(client_id);
}
