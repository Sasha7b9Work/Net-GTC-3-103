// 2023/7/19 21:13:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"


namespace HAL_USART_HC12
{
    void *handle = nullptr;

    char recv_byte = 0;
}


void HAL_USART_HC12::Transmit(const void *buffer, int size)
{

}
