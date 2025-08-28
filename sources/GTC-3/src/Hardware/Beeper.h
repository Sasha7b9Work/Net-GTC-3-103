// 2022/6/19 6:30:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Beeper
{
    void Init();

    void Beep(int frequency, uint timeMS);

    void Start(int frequency);

    void Stop();

    // ���������� true, ���� ���� ���
    bool Running();

    void CallbackOnTimer();

    extern void *handleTIM3;       // TIM_HandleTypeDef
}
