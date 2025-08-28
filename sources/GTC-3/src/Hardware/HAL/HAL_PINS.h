// 2023/06/15 14:13:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL_PINS
{
    void Init();
}


struct Port
{
    enum E
    {
        A,
        B,
        C,
        D,
        Count
    };
};


struct PMode
{
    enum E
    {
        OUTPUT_PP_PULL_UP,
        OUTPUT_PP_PULL_DOWN,
        INPUT_NO_PULL,
        INPUT_PULL_DOWN
    };
};


struct Pin
{
    enum E
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
        Count
    };

    Pin(Port::E, Pin::E, PMode::E);
    void Init();
protected:
    Port::E  port;
    Pin::E   pin;
    PMode::E mode;
};


struct PinOut : public Pin
{
    PinOut(Port::E, Pin::E, PMode::E);
    void ToHi();
    void ToLow();
    void Set(bool);
};


extern PinOut pinWP;
