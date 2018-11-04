#include <Arduino.h>                // damit millis und analogWrite geht.
#include "driver/pcnt.h"
#include "cLenkersensor.h"


bool lenkerflag = 1;
pcnt_config_t config_pcnt;
int16_t counter;

cLenkersensor::cLenkersensor()
{
    lastLenkwinkel = 0;
    lastLenkgeschwindigkeit = 0;
    lastZeit = millis();
    daten.lenkbeschleunigung = 0;
    daten.lenkgeschwindigkeit = 0;
    daten.lenkwinkel = 0;
    
    // Set PCNT input signal and control GPIOs
    config_pcnt.pulse_gpio_num = ENCODER_INPUT;
    config_pcnt.ctrl_gpio_num = ENCODER_DIRECTION;
    config_pcnt.channel = PCNT_CHANNEL_0,
    config_pcnt.unit = ENCODER_1;
    // What to do on the positive / negative edge of pulse input?
    config_pcnt.pos_mode = PCNT_COUNT_INC;   // Count up on the positive edge
    config_pcnt.neg_mode = PCNT_COUNT_DEC;   // Keep the counter value on the negative edge
    // What to do when control input is low or high?
    config_pcnt.lctrl_mode = PCNT_MODE_KEEP; // Reverse counting direction if low
    config_pcnt.hctrl_mode = PCNT_MODE_REVERSE; // Keep the primary counter mode if high
    // // Set the maximum and minimum limit values to watch
    config_pcnt.counter_h_lim = ENCODER_MAX_VALUE;
    config_pcnt.counter_l_lim = ENCODER_MIN_VALUE;
    
    pcnt_unit_config(&config_pcnt);
    pcnt_counter_pause(ENCODER_1);
    pcnt_counter_clear(ENCODER_1);
}

void cLenkersensor::readCounter()
{
    pcnt_get_counter_value(ENCODER_1, &counter);
    daten.lenkwinkel = 360/511.0*counter*9/28.0;
    daten.lenkgeschwindigkeit = (daten.lenkwinkel - lastLenkwinkel) / (millis() - lastZeit) * 1000; // [°/s]
    daten.lenkbeschleunigung = (daten.lenkgeschwindigkeit - lastLenkgeschwindigkeit) / (millis() - lastZeit) * 1000; // [°/s²]
    
    lastLenkwinkel = daten.lenkwinkel;
    lastLenkgeschwindigkeit = daten.lenkgeschwindigkeit;
    lastZeit = millis();
}

bool cLenkersensor::getData(lenkerDaten &pdaten)
{
    pdaten = daten;     // Daten rückgeben
    if (daten.lenkwinkel >= 100 || daten.lenkwinkel <= -100 || lenkerflag == 1)
        return 1;
    else 
        return 0;
}

void isr_lenkersensor()
{
    lenkerflag = 0;
    pcnt_counter_resume(ENCODER_1);
}