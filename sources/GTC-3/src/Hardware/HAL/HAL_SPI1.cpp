// 2023/08/07 10:09:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <stm32f1xx_hal.h>


namespace HAL_SPI1
{
    static SPI_HandleTypeDef handle =
    {
        SPI1,
        {
            SPI_MODE_MASTER,                // Init.Mode
            SPI_DIRECTION_2LINES,           // Init.Direction
            SPI_DATASIZE_8BIT,              // Init.DataSize
            SPI_POLARITY_HIGH,              // Init.CLKPolarity
            SPI_PHASE_2EDGE,                // Init.CLKPhase
            SPI_NSS_SOFT,                   // Init.NSS
            SPI_BAUDRATEPRESCALER_2,        // Init.BaudRatePrescaler
            SPI_FIRSTBIT_MSB,               // Init.FirstBit
            SPI_TIMODE_DISABLE,             // Init.TIMode
            SPI_CRCCALCULATION_DISABLE,     // Init.CRCCalculation
            7                               // InitCRCPolynomial
        },
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0, 0, HAL_UNLOCKED, HAL_SPI_STATE_RESET, 0
    };

    namespace WP
    {
        void Init()
        {
            GPIO_InitTypeDef is =
            {
                GPIO_PIN_0,
                GPIO_MODE_OUTPUT_PP,
                GPIO_PULLUP,
                GPIO_SPEED_FREQ_HIGH
            };

            HAL_GPIO_Init(GPIOB, &is);

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

            Timer::Delay(50);

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

            Timer::Delay(50);

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        }
    }

    namespace CS
    {
        void Set()
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        }

        void Reset()
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        }
    }
}


void HAL_SPI1::Init()
{
    WP::Init();

    GPIO_InitTypeDef is =
    {//      SCK       MOSI
        GPIO_PIN_5 | GPIO_PIN_7,
        GPIO_MODE_AF_PP,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_HIGH
    };

    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = GPIO_PIN_6;                // MISO
    is.Mode = GPIO_MODE_INPUT;
    is.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &is);

    is.Pin = GPIO_PIN_4;                // NSS
    is.Mode = GPIO_MODE_OUTPUT_PP;

    HAL_GPIO_Init(GPIOA, &is);

    CS::Set();

    HAL_SPI_Init(&handle);
}


void HAL_SPI1::WriteRead(const void *out, uint8 *in, int size)
{
    CS::Reset();

    HAL_SPI_TransmitReceive(&handle, (uint8 *)out, in, (uint16)size, 10000);

    CS::Set();
}


void HAL_SPI1::Write(const void *data, int size)
{
    CS::Reset();

    HAL_SPI_Transmit(&handle, (uint8 *)data, (uint16)size, 100);

    CS::Set();
}


void HAL_SPI1::Write(uint8 byte)
{
    Write(&byte, 1);
}
