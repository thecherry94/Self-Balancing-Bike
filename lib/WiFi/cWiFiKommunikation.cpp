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



cWiFiKommunikation::cWiFiKommunikation()
{
  
}


void cWiFiKommunikation::attachURL(String url, ArRequestHandlerFunction request_handler)
{
    _pserver->on(url.c_str(), HTTP_GET, request_handler);
}

AsyncWebSocket* cWiFiKommunikation::attachWebSocket(std::string url)
{
	AsyncWebSocket* ws = new AsyncWebSocket(url.c_str());
	_pserver->addHandler(ws);
	_pserver->begin();
	return ws;
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
		digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

	digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("WiFi Verbindung erfolgreich hergestellt");
    Serial.print("IP Adresse: ");
    Serial.println(WiFi.localIP());


    //_pws = new AsyncWebSocket("/ws");
    //_pws->onEvent(&onEvent);


    _pserver = new AsyncWebServer(80);
    //_pserver->addHandler(_pws);
    
    
    _pserver->begin();

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