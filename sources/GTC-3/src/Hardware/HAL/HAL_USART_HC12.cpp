// 2023/04/11 12:09:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


namespace HAL_USART_HC12
{
    static UART_HandleTypeDef handleUART;

    void *handle = (void *)&handleUART;

    char recv_byte = 0;
}


void HAL_USART_HC12::Init()
{
    GPIO_InitTypeDef  is;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    is.Pin = GPIO_PIN_9;
    is.Mode = GPIO_MODE_AF_PP;
    is.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = GPIO_PIN_10;              // TX
    is.Pull = GPIO_NOPULL;
    is.Mode = GPIO_MODE_INPUT;

    HAL_GPIO_Init(GPIOA, &is);

    handleUART.Instance = USART1;
    handleUART.Init.BaudRate = 9600;
    handleUART.Init.WordLength = UART_WORDLENGTH_8B;
    handleUART.Init.StopBits = UART_STOPBITS_1;
    handleUART.Init.Parity = UART_PARITY_NONE;
    handleUART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handleUART.Init.Mode = UART_MODE_TX_RX;
    handleUART.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&handleUART);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    HAL_UART_Receive_IT(&handleUART, (uint8 *)&recv_byte, 1);
}


void HAL_USART_HC12::Transmit(const void *buffer, int size)
{
    if (!buffer)
    {
        return;
    }

    HAL_UART_Transmit(&handleUART, (uint8_t *)buffer, (uint16_t)size, 0xFFFF);
}
