#ifndef WIFI_COM__H
#define WIFI_COM__H

#include <map>
#include <functional>

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "cSingleton.h"
#include "../StatusLog/cStatusLog.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

#include "global.h"


#define WIFI_COM cWiFiKommunikation::instance()

using WiFiEventHandler_t = std::function<void(AsyncWebSocketClient*, rapidjson::Value&)>;


// In der .cpp sind die Funktionen auch beschrieben


class cWiFiKommunikation : public cSingleton<cWiFiKommunikation>
{
	// cSingleton muss eine friend class sein, damit es funktioniert
	friend class cSingleton<cWiFiKommunikation>;

	private:

		// Der asynchrone WebServer
		AsyncWebServer* _pserver;

		// Der asynchrone WebScoket
		AsyncWebSocket* _pws;

		// Event hashmap mit Funktionszeigern, die auf alle Events zeigt
		// Momentan eine Funktion je Event
		// TODO: Implementiere mehrere Funktionen pro Event (std::vector?)
		std::map<std::string, WiFiEventHandler_t> _events;

		// Ein Event kann durch mehrere Bedingunen in den WebSockets ausgelöst werden
		// Diese Funktion wird aufgerufen wenn solch eine Bedingung eintritt
		void handle_data(AsyncWebSocketClient* client, uint8_t* data, size_t len);


	protected:
		cWiFiKommunikation();

	public:
		~cWiFiKommunikation()
		{
			delete _pserver;
			_pserver = NULL;

			delete _pws;
			_pws = NULL;
		}

		bool connect(String, String);
		bool connectSoftAP(String, String);
		void attachURL(String, ArRequestHandlerFunction);
		void attachEvent(const char* name, WiFiEventHandler_t);
};


#endif