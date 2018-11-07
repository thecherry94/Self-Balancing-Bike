#ifndef WEBSERVER__H
#define WEBSERVER__H

#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "cSingleton.h"
#include <WiFi.h>
#include <ArduinoJson.h>


#define SERVER cWebServer::instance()



class cWebServer : public cSingleton<cWebServer>
{
    friend class cSingleton<cWebServer>;

    private:
        AsyncWebServer* _pserver;

    protected:
        cWebServer();

    public:
        void connectToAP(const char*, const char*);
        void createSoftAP(const char*, const char*);

        void attachURL(const char*, ArRequestHandlerFunction, WebRequestMethod);
        void attachJSON(const char*, ArJsonRequestHandlerFunction);
};






#endif