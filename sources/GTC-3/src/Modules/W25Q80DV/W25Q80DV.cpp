// 2023/08/07 09:57:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/W25Q80DV/W25Q80DV.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Buffer.h"
#include "Hardware/Timer.h"
#include <cstdlib>


/*
*   Block 0
*   Sector 0
*   Адреса 000000h - 0000FFh
*/

//                            page
#define PROGRAM_PAGE  0x02  /* 34 */
#define READ_DATA     0x03  /* 26 */
#define WRITE_DISABLE 0x04  /* 23 */
#define READ_STATUS_1 0x05  /* 24 */
#define WRITE_ENABLE  0x06  /* 22 */
#define SECTOR_ERASE  0x20  /* 36 */


namespace W25Q80DV
{
    // Записывает uin8, а затем младшие 3 байта из второго значения
    static void Write32bit(uint8, uint);

    static bool IsBusy();

    static void WaitRelease();

    namespace Test
    {
        static bool result = false;
    }
}


void W25Q80DV::WriteLess1024bytes(uint address, const void *_buffer, int size)
{
    const uint8 *buffer = (const uint8 *)_buffer;

    pinWP.ToHi();

    WaitRelease();

    HAL_SPI1::Write(WRITE_ENABLE);          // Write enable

    Buffer<uint8, 1024> data;

    data[0] = PROGRAM_PAGE; //-V525
    data[1] = (uint8)(address >> 16);       // \ 
    data[2] = (uint8)(address >> 8);        // | Адрес
    data[3] = (uint8)(address);             // / 

    for (int i = 0; i < size; i++)
    {
        data[4 + i] = buffer[i];
    }

    //                          команда   адрес
    HAL_SPI1::Write(data.Data(), size + 1 + 3);     // Page program

    HAL_SPI1::Write(WRITE_DISABLE);                 // Write disable

    pinWP.ToLow();
}


void W25Q80DV::WriteUInt(uint address, uint value)
{
    WriteLess1024bytes(address, &value, (int)sizeof(value));
}


void W25Q80DV::Write(uint address, uint8 byte)
{
    pinWP.ToHi();

    WriteLess1024bytes(address, &byte, 1);

    pinWP.ToLow();
}


void W25Q80DV::EraseSectorForAddress(uint address)
{
    pinWP.ToHi();

    address /= SIZE_SECTOR;     // \ 
                                // | Рассчитываем адрес первого байта стираемого сектора
    address *= SIZE_SECTOR;     // / 

    WaitRelease();

    HAL_SPI1::Write(WRITE_ENABLE);

    Write32bit(SECTOR_ERASE, address);

    HAL_SPI1::Write(WRITE_DISABLE);

    pinWP.ToLow();
}


void W25Q80DV::ErasePage(int num_page)
{
    EraseSectorForAddress((uint)num_page * SIZE_SECTOR);
}


void W25Q80DV::ReadLess1024bytes(uint address, void *_buffer, int size)
{
    uint8 *buffer = (uint8 *)_buffer;

    WaitRelease();

    Buffer<uint8, 1024> out;

    out[0] = READ_DATA; //-V525
    out[1] = (uint8)(address >> 16);
    out[2] = (uint8)(address >> 8);
    out[3] = (uint8)(address);

    Buffer<uint8, 1024> in;

    HAL_SPI1::WriteRead(out.Data(), in.Data(), size + 1 + 3);

    for (int i = 0; i < size; i++)
    {
        buffer[i] = in[4 + i];
    }
}


uint8 W25Q80DV::Read(uint address)
{
    uint8 result = 0;

    ReadLess1024bytes(address, &result, 1);

    return result;
}


bool W25Q80DV::Test::Run()
{
    EraseSectorForAddress(0);

    result = false;

    for (uint i = 0; i < 1024; i++)
    {
        uint8 byte = (uint8)std::rand();

        Write(i, byte);

        if (byte != Read(i))
        {
            EraseSectorForAddress(0);
            result = false;
            return result;
        }
    }

    EraseSectorForAddress(0);

    result = true;

    return result;
}


bool W25Q80DV::Test::Result()
{
    return result;
}


void W25Q80DV::Write32bit(uint8 command, uint bits24)
{
    pinWP.ToHi();

    uint8 data[4];

    data[0] = command;
    data[1] = (uint8)(bits24 >> 16);
    data[2] = (uint8)(bits24 >> 8);
    data[3] = (uint8)(bits24);

    HAL_SPI1::Write(data, 4);

    pinWP.ToLow();
}


void W25Q80DV::WaitRelease()
{
    TimeMeterMS meter;

    while (IsBusy())
    {
        if (meter.ElapsedTime() > 100)
        {
            break;
        }
    }
}


bool W25Q80DV::IsBusy()
{
    static const uint8 out[2] = { READ_STATUS_1, 0 };
    static uint8 in[2] = { 0, 0 };

    HAL_SPI1::WriteRead(out, in, 2);

    return (in[1] & 0x01);
}


void W25Q80DV::ReadID(uint8 id[2])
{
    pinWP.ToHi();

    uint8 out[6] = { 0x90, 0, 0, 0, 0, 0 };
    uint8 in[6] = { 0, 0, 0, 0, 0, 0 };

    HAL_SPI1::WriteRead(out, in, 6);

    id[0] = in[4];
    id[1] = in[5];

    pinWP.ToLow();
}
