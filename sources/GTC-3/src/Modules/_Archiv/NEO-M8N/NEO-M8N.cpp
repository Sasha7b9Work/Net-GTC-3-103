// 2023/04/04 08:29:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/NEO-M8N/NEO-M8N.h"
#include <cstring>
#include <cstdlib>


namespace NEO_M8N
{
    static void Parse(char *);

    static const int SIZE_MESSAGE = 100;
    static char message[SIZE_MESSAGE] = { '\0' };

    char *GetData() { return message; }
}


void NEO_M8N::Init()
{

}


void NEO_M8N::ReceiveNewSymbolHandler(char symbol)
{
    static bool in_mode_receive = false;                // Если true, то находимся в режиме приёма данных

    if (in_mode_receive)
    {
        static char data[256];
        static int pointer = 0;

        if (symbol == 0x0d)
        {
            data[pointer] = '\0';
            Parse(data);
            in_mode_receive = false;
            pointer = 0;
        }
        else
        {
            data[pointer++] = symbol;
        }
    }
    else
    {
        static const char *request = "$GNGGA";

        static int ptr = 0;

        if (symbol == request[ptr])
        {
            ptr++;
            
            if (ptr == (int)std::strlen(request))
            {
                ptr = 0;
                in_mode_receive = true;
            }
        }
        else
        {
            ptr = 0;
        }
    }
}


void NEO_M8N::Parse(char *data)
{
    std::strcpy(message, data);
}


char *NEO_M8N::ExtractField(int num_filed, char buffer[32])
{
    if (std::strlen(message) == 0)
    {
        buffer[0] = 0;
    }
    else
    {
        int pos = 0;

        while (num_filed > 0)
        {
            if (message[pos] == ',' || message[pos] == '\0')
            {
                num_filed--;
            }
            pos++;
        }

        if (message[pos] == ',' || message[pos] == '\0')
        {
            buffer[0] = 0;
        }
        else
        {
            int pos_start = pos;

            while (message[pos] != ',' && message[pos] != '\0')
            {
                pos++;
            }

            int pos_end = pos;
            int iterator = 0;

            for (pos = pos_start; pos < pos_end; pos++)
            {
                buffer[iterator++] = message[pos];
            }

            buffer[iterator] = '\0';
        }
    }

    return buffer;
}


float NEO_M8N::GetLatitude()
{
    char buffer[32];

    ExtractField(2, buffer);

    if (buffer[0] == 0)
    {
        return 0.0f;
    }

    float result = std::atof(buffer);

    return result / 100.0f;
}


float NEO_M8N::GetLongitude()
{
    char buffer[32];

    ExtractField(4, buffer);

    if (buffer[0] == 0)
    {
        return 0.0f;
    }

    float result = std::atof(buffer);

    return result / 100.0f;
}


float NEO_M8N::GetAltitude()
{
    char buffer[32];

    ExtractField(9, buffer);

    if (buffer[0] == 0)
    {
        return 0.0f;
    }

    return std::atof(buffer);
}
