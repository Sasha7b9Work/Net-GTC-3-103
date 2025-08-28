// 2023/06/05 14:51:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Math.h"
#include <stm32f1xx_hal.h>
#include <cstring>


/*
* Настройки хранятся в верхних 4 кБ памяти
*/


namespace HAL_ROM
{
    #define ADDR_FLASH_PAGE_62    ((uint)0x0800F800) /* Base @ of Page 62, 1 Kbytes */
    #define ADDR_FLASH_PAGE_63    ((uint)0x0800FC00) /* Base @ of Page 63, 1 Kbytes */

    #define SIZE_SECTOR 1024

    #define ADDR_SECTOR_0   ADDR_FLASH_PAGE_62
    #define ADDR_SECTOR_1   ADDR_FLASH_PAGE_63

    static void Save(uint address, const Settings &set);

    static bool Load(uint address, Settings &);

    static uint Read(uint address);
}



void HAL_ROM::SaveSettings(const Settings &set)
{
    if (Read(ADDR_SECTOR_0) == (uint)(-1))           // Если в нулевой сектор ещё ничего не записано
    {
        Save(ADDR_SECTOR_0, set);
    }
    else if (Read(ADDR_SECTOR_1) == (uint)(-1))      // Если в первый сектор ещё ничего не записано
    {
        Save(ADDR_SECTOR_1, set);
    }
    else
    {
        uint number0 = Read(ADDR_SECTOR_0 + 4);
        uint number1 = Read(ADDR_SECTOR_1 + 4);

        if (number0 < number1)                              // В нулевом секторе более старые настройки
        {
            Save(ADDR_SECTOR_0, set);
        }
        else
        {
            Save(ADDR_SECTOR_1, set);
        }
    }
}


bool HAL_ROM::LoadSettings(Settings &set)
{
    uint number0 = Read(ADDR_SECTOR_0 + 4);
    uint number1 = Read(ADDR_SECTOR_1 + 4);

    if (number0 == (uint)(-1))
    {
        return false;
    }

    if (number1 == (uint)(-1))
    {
        return Load(ADDR_SECTOR_0, set);
    }

    if (number0 > number1)
    {
        return Load(ADDR_SECTOR_0, set);
    }

    return Load(ADDR_SECTOR_1, set);
}


uint HAL_ROM::Read(uint _address)
{
    uint *address = (uint *)_address;

    return *address;
}


bool HAL_ROM::Load(uint address, Settings &set)
{
    std::memcpy((void *)&set, (const void *)address, sizeof(Settings));

    return true;
}


void HAL_ROM::Save(uint address, const Settings &set)
{
    HAL_FLASH_Unlock();

    uint error = 0;
    FLASH_EraseInitTypeDef is;

    is.TypeErase = FLASH_TYPEERASE_PAGES;
    is.PageAddress = address;
    is.NbPages = 1;

    HAL_FLASHEx_Erase(&is, &error);

    uint *data = (uint *)&set;

    for (int i = 0; i < (sizeof(Settings) / sizeof(uint) + 1); i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *data);

        address += 4;
        data++;
    }

    HAL_FLASH_Lock();
}
