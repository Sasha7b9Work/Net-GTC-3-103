// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"


/*
* Измерение температуры, влжаности, давления
*/
namespace BME280
{
    void Init();

    bool GetMeasures(float *temp, float *pressure, float *humidity);
}
