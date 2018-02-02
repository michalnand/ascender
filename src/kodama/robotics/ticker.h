#ifndef _TICKER_H_
#define _TICKER_H_

#include <kodama.h>


class Ticker
{
  private:
    unsigned long int m_time_end, m_interval;

  public:
    Ticker(unsigned long int interval = 1000);
    ~Ticker();

    void set_interval(unsigned long int interval);

    //return true if time event occurs
    bool is_time();

    void reset();
};


#endif
