#include "cWebServer.h"


cWebServer::cWebServer()
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
}



void cWebServer::connectToAP(const char* ssid, const char* pass)
{
    // Starte Verbindungsaufbau
    WiFi.begin(ssid, pass);

    // Statusmeldung per Serial und feedback während Verbindungsaufbau
    // TODO delay entfernen bzw. thread starten
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connection established.\n Local IP: ");
    Serial.println(WiFi.localIP().toString().c_str());

    // Web server auf Port 80 starten
    _pserver = new AsyncWebServer(80);
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    _pserver->begin();

    _pserver->onNotFound([](AsyncWebServerRequest *request) {
	if (request->method() == HTTP_OPTIONS) {
		request->send(200);
	} else {
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
