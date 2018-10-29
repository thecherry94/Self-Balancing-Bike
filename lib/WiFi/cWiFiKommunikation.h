#ifndef WIFI_COM__H
#define WIFI_COM__H

#include <map>

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "cSingleton.h"
#include "../StatusLog/cStatusLog.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

#define WIFI_COM cWiFiKommunikation::instance()

typedef void (*WiFiEventHandler_t)(AsyncWebSocketClient*, rapidjson::Value&);

class cWiFiKommunikation : public cSingleton<cWiFiKommunikation>
{
  friend class cSingleton<cWiFiKommunikation>;

  private:
    AsyncWebServer* _pserver;
    AsyncWebSocket* _pws;
    std::map<std::string, WiFiEventHandler_t> _events;

    
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