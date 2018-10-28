#ifndef WIFI_COM__H
#define WIFI_COM__H

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "cSingleton.h"
#include "../StatusLog/cStatusLog.h"

#define WIFI_COM cWiFiKommunikation::instance()

class cWiFiKommunikation : public cSingleton<cWiFiKommunikation>
{
  friend class cSingleton<cWiFiKommunikation>;

  private:
    AsyncWebServer* _pserver;
    AsyncWebSocket* _pws;
    
  protected:
    cWiFiKommunikation();

  public:
    ~cWiFiKommunikation()
    {
      delete _pserver;
      _pserver = NULL;
    }

    bool connect(String, String);
    bool connectSoftAP(String, String);
    void attachURL(String, ArRequestHandlerFunction);
    AsyncWebSocket* attachWebSocket(std::string url);
};


#endif