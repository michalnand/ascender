#include "adc_driver.h"
#include <stdint.h>
#include <stm32f7xx_hal.h>

ADCDriver::ADCDriver()
{

}

ADCDriver::~ADCDriver()
{

}

void ADCDriver::init()
{
    gpio_init();
    adc_init();
}


int ADCDriver::read(unsigned int channel)
{
    adcChannel.Channel = channel;
    HAL_ADC_ConfigChannel(&AdcHandle, &adcChannel);

    HAL_ADC_Start(&AdcHandle);

    while ((ADC1->SR&ADC_FLAG_EOC) == 0)
    {
        __asm("nop");
    }

    return ADC1->DR;
}

void ADCDriver::adc_init()
{
    __ADC1_CLK_ENABLE();

    //HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(ADC_IRQn);

    AdcHandle.Instance = ADC1;

    AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    AdcHandle.Init.Resolution     = ADC_RESOLUTION_12B;
    AdcHandle.Init.ScanConvMode   = DISABLE;
    AdcHandle.Init.ContinuousConvMode     = ENABLE;
    AdcHandle.Init.DiscontinuousConvMode  = DISABLE;
    AdcHandle.Init.NbrOfDiscConversion    = 0;
    AdcHandle.Init.ExternalTrigConvEdge   = ADC_EXTERNALTRIGCONVEDGE_NONE;
    AdcHandle.Init.ExternalTrigConv       = ADC_EXTERNALTRIGCONV_T1_CC1;
    AdcHandle.Init.DataAlign              = ADC_DATAALIGN_RIGHT;
    AdcHandle.Init.NbrOfConversion        = 1;
    AdcHandle.Init.DMAContinuousRequests  = DISABLE;
    AdcHandle.Init.EOCSelection           = ENABLE;

    HAL_ADC_Init(&AdcHandle);

    adcChannel.Channel = ADC_CHANNEL_1;
    adcChannel.Rank = 1;
    adcChannel.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    adcChannel.Offset = 0;

    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannel) != HAL_OK)
    {
        while (1)
        {
            __asm("nop");
        }
    }
}

void ADCDriver::gpio_init()
{
    RCC->AHB1ENR|=  RCC_AHB1ENR_GPIOAEN|
                    RCC_AHB1ENR_GPIOBEN|
                    RCC_AHB1ENR_GPIOCEN;

    GPIO_InitTypeDef gpioInit;
    gpioInit.Mode = GPIO_MODE_ANALOG;
    gpioInit.Pull = GPIO_NOPULL;

    gpioInit.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOC, &gpioInit);
    gpioInit.Pin = GPIO_PIN_5;
    HAL_GPIO_Init(GPIOC, &gpioInit);

    gpioInit.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_5;
    HAL_GPIO_Init(GPIOA, &gpioInit);
    gpioInit.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOB, &gpioInit);

    gpioInit.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &gpioInit);
}
