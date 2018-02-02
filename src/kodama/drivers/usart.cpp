#include "usart.h"
#include "tgpio.h"

#include <kodama_config.h>


//use usart1, on pins PA9 and PA10
#define USART_HW      USART1


#define    COM1_BAUD            115200
#define    COM1_TX_PORT         GPIOA
#define    COM1_TX_PIN          GPIO_PIN_9
#define    COM1_RX_PORT         GPIOA
#define    COM1_RX_PIN          GPIO_PIN_10

USART::USART()
{


}

USART::~USART()
{


}

void USART::init()
{
  // UART Clock Enable
  __HAL_RCC_USART1_CLK_ENABLE();


  GPIO_InitTypeDef gpio_init_structure;

  // GPIO TX
  gpio_init_structure.Pin = COM1_TX_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(COM1_TX_PORT, &gpio_init_structure);

  // GPIO RX
  gpio_init_structure.Pin = COM1_RX_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(COM1_RX_PORT, &gpio_init_structure);

  UART_HandleTypeDef UartHandle1;
  // UART init
  UartHandle1.Instance = USART_HW;
  UartHandle1.Init.BaudRate     = COM1_BAUD;
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

void USART::put_char(char c)
{
  while( !(USART_HW->ISR & USART_ISR_TXE) )
		__asm("nop");

	USART_HW->TDR = c;
}

char USART::get_char()
{
  unsigned int c;
  while ( (c = ischar()) == NO_CHAR)
    __asm("nop");

  return c;

  return 0;
}

unsigned int USART::ischar()
{
  if (USART_HW->ISR & USART_ISR_RXNE)
  {
    return USART_HW->RDR;
  }

  return NO_CHAR;
}



/*

#define UART_RX_BUFFER_SIZE   8

unsigned int g_uart_wr_ptr, g_uart_rd_ptr;
unsigned char g_uart_rx_buffer[UART_RX_BUFFER_SIZE];

void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0, itpos = 0, itmask = 0;
  uint32_t usartxbase = 0;


  usartxbase = (uint32_t)USARTx;

  usartreg = (((uint16_t)USART_IT) >> 0x08);

  itpos = USART_IT & ((uint32_t)0x000000FF);
  itmask = (((uint32_t)0x01) << itpos);

  if (usartreg == 0x02)
  {
    usartxbase += 0x04;
  }
  else if (usartreg == 0x03)
  {
    usartxbase += 0x08;
  }
  else
  {
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}
*/
