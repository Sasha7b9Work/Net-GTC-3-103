// 2022/05/06 11:30:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Keyboard.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include <stm32f1xx_hal.h>


Key key1(Key::_1);
Key key2(Key::_2);


namespace Keyboard
{
    static const int TIME_LONG_PRESS = 500;

    TimeMeterMS meter;

    bool pressed[Key::Count] = { false, false };        // Если true, клавиша нажата
    bool taboo_long[Key::Count] = { false, false };     // Если true, запрещено длинное срабатывание

    static bool KeyPressed(Key::E);
    static void UpdateKey(Key::E);
}


void Keyboard::Init()
{
    GPIO_InitTypeDef is =
    {
        GPIO_PIN_8 | GPIO_PIN_9,
        GPIO_MODE_INPUT,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_MEDIUM
    };

    HAL_GPIO_Init(GPIOB, &is);
}


void Keyboard::Update()
{
    for (int i = 0; i < Key::Count; i++)
    {
        UpdateKey((Key::E)i);
    }
}


void Keyboard::UpdateKey(Key::E key)
{
    if (meter.ElapsedTime() < 100)
    {
        return;
    }

    if (pressed[key])
    {
        if (meter.ElapsedTime() > TIME_LONG_PRESS && !taboo_long[key])
        {
            Menu::LongPress(key);
            taboo_long[key] = true;
        }
        else
        {
            if (!KeyPressed(key))
            {
                pressed[key] = false;
                meter.Reset();
                if (!taboo_long[key])
                {
                    Menu::ShortPress(key);
                }
                taboo_long[key] = false;
            }
        }
    }
    else
    {
        if (KeyPressed(key))
        {
            pressed[key] = true;
            meter.Reset();
        }
    }
}


bool Keyboard::KeyPressed(Key::E key)
{
    static const uint16 pins[Key::Count] = { GPIO_PIN_8, GPIO_PIN_9 };

    return HAL_GPIO_ReadPin(GPIOB, pins[key]) == GPIO_PIN_RESET;
}


bool Key::IsPressed() const
{
    return Keyboard::pressed[value];
}
