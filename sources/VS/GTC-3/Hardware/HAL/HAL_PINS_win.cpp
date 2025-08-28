// 2023/08/18 16:23:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL_PINS.h"


PinOut pinWP(Port::B, Pin::_0, PMode::OUTPUT_PP_PULL_UP);

Pin::Pin(Port::E _port, Pin::E _pin, PMode::E _mode) : port(_port), pin(_pin), mode(_mode) { }

PinOut::PinOut(Port::E _port, Pin::E _pin, PMode::E _mode) : Pin(_port, _pin, _mode) {}


void PinOut::ToHi()
{

}


void PinOut::ToLow()
{

}
