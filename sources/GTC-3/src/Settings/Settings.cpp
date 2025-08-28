// 2022/05/05 15:23:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"


static const Settings def_set =
{
    0,
    0,
    // Display
    {
        {1, 1, 1, 0},
        { TypeDisplayedInformation::AllMeasures }
    },
    // System
    {
        0                                           // serial_number
    },
    // Measures
    {
        {-30, 225, 10, -30},
        { 60, 1000, 98,  60},
        { ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT },
        { ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT, ERROR_VALUE_FLOAT }
    }
};


Settings gset = def_set;


void Settings::Load()
{
#ifndef WIN32

    Settings settings;

    if (HAL_ROM::LoadSettings(settings))
    {
        gset = settings;
    }
    else
    {
        gset = def_set;
    }

#endif
}


void Settings::Reset()
{
    gset = def_set;
}


void Settings::Save()
{
#ifndef WIN32

    Settings settings;

    bool need_save = false;

    if (HAL_ROM::LoadSettings(settings))
    {
        if (gset != settings)
        {
            need_save = true;
        }
    }
    else
    {
        need_save = true;
    }

    if (need_save)
    {
        gset.number++;

        HAL_ROM::SaveSettings(gset);
    }

#endif
}


bool Settings::operator==(const Settings &rhs)
{
    return  std::memcmp(&display, &rhs.display, sizeof(display)) == 0 &&
            std::memcmp(&system, &rhs.system, sizeof(system)) == 0 &&
            std::memcmp(&measures, &rhs.measures, sizeof(measures)) == 0; //-V1014
}


bool Settings::operator!=(const Settings &rhs)
{
    return !(*this == rhs);
}


void Settings::SaveMeasure(TypeMeasure::E type, float value)
{
    if (gset.measures.value_max[type] == ERROR_VALUE_FLOAT)
    {
        gset.measures.value_max[type] = value;
    }

    if (gset.measures.value_min[type] == ERROR_VALUE_FLOAT)
    {
        gset.measures.value_min[type] = value;
    }

    if (value > gset.measures.value_max[type])
    {
        gset.measures.value_max[type] = value;
    }
    else if (value < gset.measures.value_min[type])
    {
        gset.measures.value_min[type] = value;
    }

    Save();
}


void Settings::ResetMeasure(TypeMeasure::E type)
{
    gset.measures.value_max[type] = ERROR_VALUE_FLOAT;

    gset.measures.value_min[type] = ERROR_VALUE_FLOAT;
}
