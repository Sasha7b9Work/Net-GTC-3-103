// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/HC12/HC12.h"
#include "stm32f1xx_hal.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <cstring>


namespace HAL_USART_HC12
{
    extern char recv_byte;
}


namespace HC12
{
#define PORT_SET GPIOA
#define PIN_SET  GPIO_PIN_6

    struct RecvBuffer
    {
        static const int SIZE = 128;

        RecvBuffer() : pointer(0) { }

        void Push(char symbol)
        {
            if (pointer < SIZE)
            {
                data[pointer++] = symbol;
            }
        }

        char *Data()        { return &data[0]; }
        int NumSymbols()    { return pointer;  }
        void Clear()        { pointer = 0;     }

    private:
        char data[SIZE];
        int pointer;
    } recv_buffer;
}


void HC12::Init()
{
    GPIO_InitTypeDef is;
    is.Pin = PIN_SET;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    is.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PORT_SET, &is);

    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_SET);
}


void HC12::Transmit(const void *buffer, int size)
{
    HAL_USART_HC12::Transmit(buffer, size);
}


void HC12::Command(pchar command)
{
    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_RESET);

    TimeMeterMS().PauseOnMS(40);

    recv_buffer.Clear();

    Transmit(command, (int)std::strlen(command));
    Transmit("\r", 1);

    HAL_GPIO_WritePin(PORT_SET, PIN_SET, GPIO_PIN_SET);

//    TimeMeterMS().WaitMS(80);
//
//    char *answer = recv_buffer.Data();
//    answer = answer;
//    
//    int num = recv_buffer.NumSymbols();
//    num = num;
}


void HC12::ReceiveCallback()
{
    recv_buffer.Push(HAL_USART_HC12::recv_byte);

    HAL_UART_Receive_IT((UART_HandleTypeDef *)HAL_USART_HC12::handle, (uint8 *)&HAL_USART_HC12::recv_byte, 1);
}
