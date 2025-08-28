// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/CDC/CDC.h"
#include "Utils/Math.h"
#include <stm32f1xx_hal.h>
#include <cstring>


static void SystemClock_Config();


void HAL::Init()
{
    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_RTC_ENABLE();

#ifndef WIN32
    __HAL_AFIO_REMAP_SWJ_NONJTRST();
#endif

    HAL_PINS::Init();

    HAL_I2C1::Init();

    CDC::Init();

    HAL_RTC::Init();

    HAL_USART_HC12::Init();

    HAL_ADC::Init();

    HAL_SPI1::Init();
}


void HAL::Delay(unsigned int timeMS)
{
    HAL_Delay(timeMS);
}


static void SystemClock_Config()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
  
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}


uint HAL::GetUID()
{
#ifdef WIN32
    return 123;
#else
    uint8 bytes[12];

    std::memcpy(bytes, (void *)0x1FFFF7E8, 12); //-V566

    return Math::CalculateCRC(bytes, 12);
#endif
}


void Error_Handler()
{
    while(1)
    {
    }
}
