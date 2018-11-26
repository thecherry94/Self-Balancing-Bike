#include "global.h"

void SerialPrettyPrint(std::string txt, uint8_t chars_per_line, char border)
{
    float l = ((float)txt.size() / (float)chars_per_line);

    int lines;
    l == (int)l ? lines = (int)l : lines = (int)l + 1;

    for(int i = 0; i < chars_per_line + 4; i++)
        Serial.print(border);
    
    Serial.print("\n* ");
    for(int i = 0; i < chars_per_line + 4; i++);
}