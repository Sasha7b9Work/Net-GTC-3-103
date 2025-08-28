// 2023/06/12 16:46:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Measures.h"
#include "Display/Display.h"
#include "Settings/Settings.h"


namespace Measures
{
    static bool fixed = false;
}


void Measures::SetFixed(bool _fixed)
{
    fixed = _fixed;
}


bool Measures::IsFixed()
{
    return fixed;
}


bool Measures::InRange(TypeMeasure::E type, float value)
{
    if (value < (float)gset.measures.limit_min[type])
    {
        return false;
    }

    if (value > (float)gset.measures.limit_max[type])
    {
        return false;
    }

    return true;
}
