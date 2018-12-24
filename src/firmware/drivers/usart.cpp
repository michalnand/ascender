#include <usart.h>
#include <gpio.h>

#include <config.h>
#include <stm32f7xx.h>
#include <stm32f7xx_hal.h>


//use usart1, on pins PA9 and PA10
#define USART      USART1

#define    USART_BAUD            115200
#define    USART_TX_PORT         GPIOA
#define    USART_TX_PIN          GPIO_PIN_9
#define    USART_RX_PORT         GPIOA
#define    USART_RX_PIN          GPIO_PIN_10

Usart::Usart()
{

}


void Usart::init(unsigned int baudrate)
{
    RCC->AHB1ENR|= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR|= RCC_APB2ENR_USART1EN;

    GPIO_InitTypeDef gpio_init_structure;

    // GPIO TX
    gpio_init_structure.Pin = USART_TX_PIN;
    gpio_init_structure.Mode = GPIO_MODE_AF_PP;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(USART_TX_PORT, &gpio_init_structure);

    // GPIO RX
    gpio_init_structure.Pin = USART_RX_PIN;
    gpio_init_structure.Mode = GPIO_MODE_AF_PP;
    gpio_init_structure.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(USART_RX_PORT, &gpio_init_structure);


     UART_HandleTypeDef UartHandle1;
     // UART init
     UartHandle1.Instance = USART;
     UartHandle1.Init.BaudRate     = baudrate;
     UartHandle1.Init.WordLength   = UART_WORDLENGTH_8B;
     UartHandle1.Init.StopBits     = UART_STOPBITS_1;
     UartHandle1.Init.Parity       = UART_PARITY_NONE;
     UartHandle1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
     UartHandle1.Init.Mode         = UART_MODE_TX_RX;
     UartHandle1.Init.OverSampling = UART_OVERSAMPLING_8;
     UartHandle1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
     UartHandle1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
     HAL_UART_Init(&UartHandle1);
}

Usart::~Usart()
{


}

void Usart::put_char(char c)
{
 
  while( !(USART->ISR & USART_ISR_TXE) )
		__asm("nop");

  USART->TDR = c;
}

char Usart::get_char()
{
  unsigned int c;
  while ( (c = ischar()) == NO_CHAR)
    __asm("nop");

  return c;
}

unsigned int Usart::ischar()
{
  if (USART->ISR & USART_ISR_RXNE)
  {
    return USART->RDR;
  }

  return NO_CHAR;
}
