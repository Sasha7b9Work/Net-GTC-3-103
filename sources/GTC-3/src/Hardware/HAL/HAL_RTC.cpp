// 2023/01/30 15:35:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f1xx_hal.h>
#include <ctime>


namespace HAL_RTC
{
#define WAKEUP_TIMER_ENABLE 0x32F2

    static RTC_HandleTypeDef handleRTC =
    {
        RTC,
        {
            RTC_AUTO_1_SECOND       // AsynchPrediv
        }
    };
}


void HAL_RTC::Init()
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

    /*##-1- Configue LSI as RTC clock soucre ###################################*/
    HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);


    /*##-2- Enable RTC peripheral Clocks #######################################*/
    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    HAL_RTC_Init(&handleRTC);
}


PackedTime HAL_RTC::GetTime()
{
    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

    if (HAL_RTC_GetTimeDate(&handleRTC, &time, &date) == HAL_OK)
    {
        return PackedTime(time.Hours, time.Minutes, time.Seconds, date.Date, date.Month, date.Year);
    }

    return PackedTime();
}


void HAL_RTC::SetTime(const PackedTime &pack_time)
{
    RTC_TimeTypeDef time =
    {
        (uint8)pack_time.hours,
        (uint8)pack_time.minutes,
        (uint8)pack_time.seconds
    };

    RTC_DateTypeDef date =
    {
        0,
        (uint8)pack_time.month,
        (uint8)pack_time.day,
        (uint8)pack_time.year
    };

    HAL_RTC_SetTimeDate(&handleRTC, &time, &date);
}


String<> PackedTime::ToString() const
{
    return String<>("%02u:%02u:%02u", hours, minutes, seconds);
}
