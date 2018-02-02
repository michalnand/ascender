#ifndef _USART_CPP_H_
#define _USART_CPP_H_

#define NO_CHAR       0xffff


class USART
{
  public:
    USART();
    ~USART();

    void init();

    void put_char(char c);
    char get_char();

    unsigned int ischar();
};


#endif
