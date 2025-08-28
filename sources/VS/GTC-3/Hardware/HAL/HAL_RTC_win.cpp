// 2023/7/19 21:07:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"


PackedTime HAL_RTC::GetTime()
{
    return PackedTime();
}


uint HAL_RTC::SetTime(const PackedTime &)
{
    return 0;
}
