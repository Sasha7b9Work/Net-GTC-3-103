// 2022/08/04 14:32:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"
#include "Hardware/HAL/HAL.h"


extern const DPage pageMain;


static int cur_field = 0;
static int state = 0;
static PackedTime time;


void OnClose_Battery(bool)
{

}


void OnDraw_Battery(int x, int y)
{
    String<>("%.2f ¬", HAL_ADC::GetVoltage()).Draw(x + 90, y + 5, Color::WHITE);
}


DEF_BUTTON(bBattery,
    "¿ ¡",
    *PageSystem::self,
    OnClose_Battery,
    OnDraw_Battery,
    nullptr
)


static void Before_OpenTime(bool open)
{
    if (open)
    {
        time = HAL_RTC::GetTime();
    }
}

DEF_TIMEITEM(tTime, *PageSystem::self, Before_OpenTime, cur_field, state, time)


DEF_GOVERNOR(gSerialNumber,
    "—/Õ",
    *PageSystem::self,
    nullptr,
    0, (int)0x7FFFFFFF,
    gset.system.serial_number
)


void ClosePageSystem(bool)
{
    PageSystem::self->Close();
}


DEF_BUTTON(bClosePageSystem,
    "«‡Í˚Ú¸",
    *PageSystem::self,
    ClosePageSystem,
    nullptr,
    nullptr
);


DEF_PAGE_4(pageSystem, //-V1027
    "—»—“≈Ã¿",
    pageMain,
    nullptr,
    nullptr,
    bBattery,
    tTime,
    gSerialNumber,
    bClosePageSystem
)


const Page *const PageSystem::self = (const Page *)&pageSystem;
