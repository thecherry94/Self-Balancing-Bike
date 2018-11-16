
#ifndef GLOBAL__H
#define GLOBAL__H






#include <WiFi.h>

/* 
 * Setzt den Modus auf debug.
 * durch #ifdef __DEBUG__ in eurem Code könnt ihr nun irgendwelche Meldung ausgeben (LOG, Serial, wifi)
 * Auskommentieren, falls __DEBUG__ Meldungen/Aktionen nicht mehr stattfinden sollen
 */ 
#define __DEBUG__ 



/*
 * Dieses namespace enthält alle relevanten Daten, um das WiFi Modul zu initialisieren
 * Ihr könnt hier gerne auch eigene namespaces für eure Konfigurationen hinzufügen
 * TODO: Mögliche konstanten hier auslagern
 */
namespace WiFiConfig
{
    // Philipp WLAN
    //
    //static const char*     apSSID = "Cherry";
    //static const char*     apPASS = "4991Pk1994";

    // Walter WLAN
    //
    //static const char*     apSSID = "HIT-FRITZBOX-7490";
    //static const char*     apPASS = "63601430989011937932";

    // Max Hotspot
    //
    //static const char*     apSSID = "Max WLAN";
    //static const char*     apPASS = "asdfghjkl";

    //Andy WLAN
    static const char*     apSSID = "Trandyspot";
    static const char*     apPASS = "12345678";


    static const IPAddress softapIP(10, 10, 10, 0);
    static const IPAddress softapMASK(255, 255, 255, 0);
};

namespace BNO055Config
{
    static const unsigned char Address = 55;
}


namespace WebPages
{
    static const char* GyroControl = "<html><head><title>Gyro Control User Interface</title><style>.container{border:1px solid black;width:50%;margin:auto;padding:0.5em}.center{text-align:center}.main_body{border-top:none;height:40%}.float-right{float:right}input[type=range]{-webkit-appearance:none;background:transparent;width:85%}</style> <script>var rngPower;var btnSend;var chkSend;var send_int_time=100;var send_int=null;document.addEventListener(\"DOMContentLoaded\",function(event) {rngPower=document.getElementById(\"rngPower\");btnSend=document.getElementById(\"btnSend\");chkSend=document.getElementById(\"chkSend\");rngPower.addEventListener(\"input\",function(ev) {if(!chkSend.checked) return;if(send_int==null) {send_int=setInterval(function() {send_http_request(\"/gyro/power\",\"GET\",function(res) {console.log(res);},function(xhr) {console.log(xhr.error);},\"?val=\"+rngPower.value);},send_int_time);console.log(\"INT\");}});rngPower.addEventListener(\"change\",function(ev) {if(!chkSend.checked) return;clearInterval(send_int);send_int=null;send_http_request(\"/gyro/power\",\"GET\",function(res) {console.log(res);},function(xhr) {console.log(xhr.error);},\"?val=\"+rngPower.value);});chkSend.addEventListener(\"change\",function(ev) {if(!chkSend.checked) {clearInterval(send_int);send_int=null;}});btnSend.addEventListener(\"click\",function(ev) {send_http_request(\"/gyro/power\",\"GET\",function(res) {console.log(res);},function(xhr) {console.log(xhr.error);},\"?val=\"+rngPower.value);});});function send_http_request(url,method,success,error,data) {var xhr=new XMLHttpRequest();xhr.onreadystatechange=function() {if(xhr.readyState!==4)return;if(xhr.status>=200&&xhr.status<300) {success(xhr.responseText);} else {error(xhr);}};xhr.open(method,url+data,true);xhr.send(data);}</script> </head><body><div class=\"container center\"><h1 class=\"\">Gyro Control User Interface</h1></div><div class=\"container main_body\"> <label>Gyromotorleistung [%]</label> <br /> <input id=\"rngPower\" min=\"0\" max=\"100\" type=\"range\" class=\"range\" /> <label id=\"lblPower\" class=\"float-right\">0%</label> <br /> <br /> <button id=\"btnSend\" type=\"button\">Senden</button><div class=\"float-right\"><input id=\"chkSend\" type=\"checkbox\" />autom. Senden</div></div></body></html>";

}







#endif