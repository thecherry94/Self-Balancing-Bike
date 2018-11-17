#ifndef WEBSERVER__H
#define WEBSERVER__H

#include <Arduino.h>
#include <map>
#include <string>
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "cSingleton.h"
#include <WiFi.h>
#include <ArduinoJson.h>


#define SERVER cWebServer::instance()

using AsyncWebSocketEventHandler = std::function<void(AsyncWebSocket* server, uint32_t client_id, JsonObject& root)>;

class cWebServer : public cSingleton<cWebServer>
{
    friend class cSingleton<cWebServer>;

    private:
        AsyncWebServer* _pserver;
        AsyncWebSocket* _pws;
        std::map<std::string, AsyncWebSocketEventHandler> _socket_events;

        void onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);

    protected:
        cWebServer();

        

    public:
        void connectToAP(const char*, const char*);
        void createSoftAP(const char*, const char*);

        void attachURL(const char*, ArRequestHandlerFunction, WebRequestMethod);
        void attachJSON(const char*, ArJsonRequestHandlerFunction);
        void attachSocketEvent(char* name, AsyncWebSocketEventHandler handler);

        AsyncWebSocketClient* get_client(uint8_t client_id);
};






#endif