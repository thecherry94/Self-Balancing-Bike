#include "global.h"

void SerialPrettyPrint(std::string txt, uint8_t chars_per_line = 40, char border = '*')
{
    float l = ((float)txt.size() / (float)chars_per_line);

    int lines;

    l == (int)l ? lines = (int)l : lines = (int)l + 1;

    for(int i = 0; i < chars_per_line + 4; i++)
        Serial.print(border);  

    for(int i = 0; i < lines; i++)
    {
        Serial.print("\n* ");
        for(int j = 0; j < chars_per_line; j++)
        {
            int k = i * j;
            if (k >= txt.size())
                Serial.print(" ");
            
            Serial.print(txt[k]);
        }
        Serial.print(" *");
    }

    for(int i = 0; i < chars_per_line + 4; i++)
        Serial.print(border);  
}