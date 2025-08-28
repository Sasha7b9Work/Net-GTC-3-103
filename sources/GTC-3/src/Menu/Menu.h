// 2022/05/05 12:28:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Menu/MenuItems.h"
#include "Hardware/Keyboard.h"


namespace Menu
{
    void ShortPress(Key::E);

    void LongPress(Key::E);

    void DoubleClick(Key::E);

    void Draw();

    bool Opened();

    namespace Title
    {
        const int HEIGHT = 27;
    }
}
