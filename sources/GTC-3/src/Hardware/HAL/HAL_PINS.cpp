// 2023/06/15 14:13:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>


PinOut pinWP(Port::B, Pin::_0, PMode::OUTPUT_PP_PULL_UP);


namespace HAL_PINS
{
    static const uint16 pins[Pin::Count] =
    {
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11,
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15
    };

    static GPIO_TypeDef *const ports[Port::Count] =
    {
        GPIOA,
        GPIOB,
        GPIOC,
        GPIOD
    };
}


void HAL_PINS::Init()
{
    pinWP.Init();
    pinWP.ToLow();
}


void PinOut::ToLow()
{
    HAL_PINS::ports[port]->BSRR = (uint)(HAL_PINS::pins[pin] << 16);
}


void Pin::Init()
{
    GPIO_InitTypeDef is;

    is.Pin = HAL_PINS::pins[pin];

    GPIO_TypeDef *gpio = HAL_PINS::ports[port];

    if (mode == PMode::OUTPUT_PP_PULL_UP || mode == PMode::OUTPUT_PP_PULL_DOWN)
    {
        is.Mode = GPIO_MODE_OUTPUT_PP;
        is.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(gpio, &is);

        uint data = gpio->ODR;

        if (mode == PMode::OUTPUT_PP_PULL_DOWN)
        {
            _CLEAR_BIT(data, pin);
        }
        else
        {
            _SET_BIT(data, pin);
        }

        gpio->ODR = data;
    }
    else if (mode == PMode::INPUT_NO_PULL || mode == PMode::INPUT_PULL_DOWN)
    {
        is.Mode = GPIO_MODE_INPUT;
        is.Speed = GPIO_SPEED_FREQ_HIGH;
        is.Pull = (mode == PMode::INPUT_NO_PULL) ? GPIO_NOPULL : GPIO_PULLDOWN;

        HAL_GPIO_Init(gpio, &is);

        uint data = gpio->ODR;

        if (mode == PMode::INPUT_PULL_DOWN)
        {
            _CLEAR_BIT(data, pin);
        }
        else
        {
            _SET_BIT(data, pin);
        }

        gpio->ODR = data;
    }

    if (port == Port::D && (pin == Pin::_0 || pin == Pin::_1))
    {
        __HAL_AFIO_REMAP_PD01_ENABLE();
    }
}


Pin::Pin(Port::E _port, Pin::E _pin, PMode::E _mode) :
    port(_port), pin(_pin), mode(_mode)
{
}


PinOut::PinOut(Port::E _port, Pin::E _pin, PMode::E _mode) : Pin(_port, _pin, _mode) {}


void PinOut::Set(bool state)
{
    if (state)
    {
        ToHi();
    }
    else
    {
        ToLow();
    }
}


void PinOut::ToHi()
{
    HAL_PINS::ports[port]->BSRR = HAL_PINS::pins[pin];
}

