#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "cSingleton.h"
#include "../StatusLog/cStatusLog.h"

#define WIFI_COM cWiFiKommunikation::instance()

#pragma once

class cWiFiKommunikation : public cSingleton<cWiFiKommunikation>
{
  friend class cSingleton<cWiFiKommunikation>;

  private:
    AsyncWebServer* _pserver;
    
  protected:
    cWiFiKommunikation();

  public:
    ~cWiFiKommunikation()
    {
      delete _pserver;
      _pserver = NULL;
    }

    bool connect(String, String);
    void attachEvent(String, ArRequestHandlerFunction);
};



cWiFiKommunikation::cWiFiKommunikation()
{
  
}


void cWiFiKommunikation::attachEvent(String url, ArRequestHandlerFunction request_handler)
{
  _pserver->on(url.c_str(), HTTP_GET, request_handler);
}

bool cWiFiKommunikation::connect(String ssid, String pw)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    //WiFi.end();
    delete _pserver;
    _pserver = NULL;
  }
  
  Serial.print("Verbindungsaufbau mit: ");
  Serial.println(ssid);

  WiFi.begin(ssid.c_str(), pw.c_str());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Verbindung erfolgreich hergestellt");
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP());

  _pserver = new AsyncWebServer(80);
  _pserver->begin();
}