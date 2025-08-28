// 2023/09/08 22:13:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hardware/HAL/HAL.h"
#include "Modules/W25Q80DV/W25Q80DV.h"


struct StructData
{
    StructData(PackedTime _time, float _charge, float _latitude, float _longitude, float _temperature, float _humidity) :
        time(_time.ToSecs()),
        charge(_charge),
        latitude(_latitude),
        longitude(_longitude),
        temperature(_temperature),
        humidity(_humidity),
        crc(CalculateCRC()),
        control_field(0x00000000)
    {

    }

    uint     time;              // Время от 2000-го года. Если в старшем бите 1 - это инцидент
    float    charge;
    float    latitude;
    float    longitude;
    float    temperature;
    float    humidity;
    uint     crc;
    BitSet32 control_field;     // Это нужно для контроля правильности записи

    // true, если запись пуста
    bool IsEmpty() const;

    // true, если содержатся корректные данные
    bool IsValid() const;

    void Erase();

    bool Write(uint address) const;

private:

    bool IsErased();

    bool Read(uint address);

    uint *FirstWord();

    uint CalculateCRC() const;
};


struct StructIncident
{
    uint     time;              // Время от 2000-го года. Если в старшем бите 0 - это данные
    uint     code;              // Код инцидента
    uint     field0;
    uint     field1;
    uint     field2;
    uint     field3;
    uint     crc;
    BitSet32 control_field;     // Это нужно для контроля правильности записи
};


struct MemoryStorage
{
    static const uint BEGIN = W25Q80DV::BEGIN;
    static const uint END = W25Q80DV::END;

    static void Init();

    struct Data
    {
        static void Append(const StructData &);

        // Возвращает указатель на самую старую структуру данных (которая считана раньше всех). После использования нужно вызвать Erase()
        // с этим указателем, чтобы стереть структуру из хранилища
        static StructData *GetOldest();

        static void Erase(StructData *);
    };

    struct Incident
    {
        static void Append(const StructIncident &);

        static StructIncident *GetNext();

        static void Erase(StructIncident *);
    };

private:

    static StructData *FindFirstEmpty();

    static void EraseFull();
};
