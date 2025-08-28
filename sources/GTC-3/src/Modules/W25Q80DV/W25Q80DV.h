// 2023/08/07 09:56:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace W25Q80DV
{
    static const uint BEGIN = 0;
    static const uint END = 1024 * 1024;
    static const int SIZE_SECTOR = 4 * 1024;

    // Размер буфера ограничен 1024 байтами
    void WriteLess1024bytes(uint address, const void *buffer, int size);

    // Размер буфера ограничен 1024 байтами
    void ReadLess1024bytes(uint address, void *buffer, int size);

    void ReadID(uint8 id[2]);

    // Стереть страницу, которой принадлежит address
    void EraseSectorForAddress(uint address);

    void ErasePage(int num_page);

    void WriteUInt(uint address, uint value);

    void Write(uint address, uint8 byte);

    uint8 Read(uint address);

    namespace Test
    {
        bool Run();

        bool Result();
    }
}
