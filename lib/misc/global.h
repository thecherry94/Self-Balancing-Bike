
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
    static const char*     apSSID = "HIT-FRITZBOX-7490";
    static const char*     apPASS = "63601430989011937932";

    static const IPAddress softapIP(10, 10, 10, 0);
    static const IPAddress softapMASK(255, 255, 255, 0);
};







#endif