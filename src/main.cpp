#include <Arduino.h>




#include "cBike.h"


#define GYRO_PWM_PIN 0


cBike bike(GYRO_PWM_PIN);

void setup() 
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    
    bike.run();
}

void loop() 
{
    bike.update();
}