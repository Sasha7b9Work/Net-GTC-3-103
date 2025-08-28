// 2023/09/08 22:14:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Storage/MemoryStorage.h"
#include "Utils/Math.h"
#include "Modules/W25Q80DV/W25Q80DV.h"
#include <cstring>


void MemoryStorage::Init()
{
    for (StructData *address = (StructData *)BEGIN; (uint)address < END; address++)
    {
        if (address && address->IsEmpty())
        {
            if (address->IsEmpty())
            {
                continue;
            }

            if (!address->IsValid())
            {
                address->Erase();
            }
        }
    }
}


void MemoryStorage::Data::Append(const StructData &data)
{
    StructData *address = FindFirstEmpty();

    if (!address)
    {
        EraseFull();

        address = (StructData *)BEGIN;
    }

    data.Write((uint)address);
}


StructData *MemoryStorage::Data::GetOldest()
{
    StructData *result = nullptr;

    for (StructData *data = (StructData *)BEGIN; data < (StructData *)END; data++)
    {
        if (data && data->IsValid())
        {
            if (!result)
            {
                result = data;
            }
            else
            {
                if (data->time < result->time)
                {
                    result = data;
                }
            }
        }
    }

    return result;
}


void MemoryStorage::Data::Erase(StructData *data)
{
    data->Erase();
}


void MemoryStorage::EraseFull()
{
    int start_page = BEGIN / W25Q80DV::SIZE_SECTOR;

    int end_page = END / W25Q80DV::SIZE_SECTOR;

    for (int page = start_page; page < end_page; page++)
    {
        W25Q80DV::ErasePage(page);
    }
}


StructData *MemoryStorage::FindFirstEmpty()
{
    for (StructData *data = (StructData *)BEGIN; data < (StructData *)END; data++)
    {
        if (data && data->IsEmpty())
        {
            return data;
        }
    }

    return nullptr;
}


bool StructData::IsEmpty() const
{
    uint8 *address = (uint8 *)this;

    uint8 *end = address + sizeof(*this);

    while (address < end)
    {
        if (*address != 0xFF)
        {
            return false;
        }

        end++;
    }

    return true;
}


bool StructData::IsValid() const
{
    uint *pointer = (uint *)this;

    if (*pointer == (uint)-1)
    {
        return true;
    }

    return (crc == CalculateCRC()) &&
           (control_field.bytes[0] == 0x00) &&
           (control_field.bytes[1] == BINARY_U8(01111110));
}


void StructData::Erase()
{
    W25Q80DV::WriteUInt((uint)FirstWord(), 0U);
}


bool StructData::IsErased()
{
    return *FirstWord() == 0U;
}


uint *StructData::FirstWord()
{
    return (uint *)this;
}


uint StructData::CalculateCRC() const
{
    return Math::CalculateCRC(this, sizeof(StructData) - sizeof(crc) - sizeof(control_field));
}


bool StructData::Write(uint address) const
{
    W25Q80DV::WriteLess1024bytes(address, (const uint8 *)this, (int)sizeof(StructData));

    return std::memcmp((void *)this, (void *)address, sizeof(StructData)) == 0;
}


bool StructData::Read(uint address)
{
    std::memcpy((void *)address, this, sizeof(StructData));

    return (CalculateCRC() == crc) && (control_field.word == 0);
}
