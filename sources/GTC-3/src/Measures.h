// 2023/06/12 16:46:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


namespace Measures
{
    // Фиксирует последние измерения на экране
    void SetFixed(bool fixed);
    bool IsFixed();
    bool InRange(TypeMeasure::E, float);
}
