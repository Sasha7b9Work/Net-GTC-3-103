// 2023/06/15 08:56:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <stm32f1xx_hal.h>


namespace HAL_ADC
{
    static ADC_HandleTypeDef handleADC;
    void *handle = (void *)&handleADC;

    static float voltage = 0.0f;
}


void HAL_ADC::Init()
{
#ifndef WIN32
    __HAL_RCC_ADC1_CLK_ENABLE();
#endif

    GPIO_InitTypeDef is;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    is.Pin = GPIO_PIN_3;
    is.Mode = GPIO_MODE_ANALOG;
    is.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &is);

    ADC_ChannelConfTypeDef sConfig = { 0 };

    handleADC.Instance = ADC1;
    handleADC.Init.ScanConvMode = ADC_SCAN_DISABLE;
    handleADC.Init.ContinuousConvMode = DISABLE;
    handleADC.Init.DiscontinuousConvMode = DISABLE;
    handleADC.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    handleADC.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    handleADC.Init.NbrOfConversion = 1;

    HAL_ADC_Init(&handleADC);

    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

    HAL_ADC_ConfigChannel(&handleADC, &sConfig);

    HAL_NVIC_SetPriority(ADC1_IRQn, 1, 1);

    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    HAL_ADC_Start_IT(&handleADC);
}


float HAL_ADC::GetVoltage()
{
    return voltage;
}


void HAL_ADC::Update()
{
    static TimeMeterMS meter;

    if (meter.ElapsedTime() > 250)
    {
        HAL_ADC_Start_IT((ADC_HandleTypeDef *)HAL_ADC::handle);

        meter.Reset();
    }
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    HAL_ADC::voltage = (float)HAL_ADC_GetValue(hadc) / (1 << 12) * 3.3f * 1.25f;
}
