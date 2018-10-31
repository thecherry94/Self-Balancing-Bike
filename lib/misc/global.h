
#ifndef DEBUG__H
#define DEBUG__H

#include <WiFi.h>

/* 
 * Setzt den Modus auf debug.
 * durch #ifdef __DEBUG__ in eurem Code könnt ihr nun irgendwelche Meldung ausgeben (LOG, Serial, wifi)
 * Auskommentieren, falls __DEBUG__ Meldungen/Aktionen nicht mehr stattfinden sollen
 */ 
#define __DEBUG__ 


/*
 * Dieses namespace enthält alle relevanten Daten, um das WiFi Modul zu initialisieren
 * TODO: Mögliche konstanten hier auslagern
 */
namespace WiFiConfig
{
    const IPAddress softapIP(10, 10, 10, 0);
}
 




#endif