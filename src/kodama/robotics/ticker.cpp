#include "ticker.h"

Ticker::Ticker(unsigned long int interval)
{
  set_interval(interval);
}

Ticker::~Ticker()
{

}

void Ticker::set_interval(unsigned long int interval)
{
  m_time_end = 0;
  m_interval = interval;
}


bool Ticker::is_time()
{
  if (timer.get_time() >= m_time_end)
    return true;

  return false;
}

void Ticker::reset()
{
  m_time_end = timer.get_time() + m_interval;
}
