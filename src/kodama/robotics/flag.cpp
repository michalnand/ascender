#include "flag.h"


Flag::Flag()
{
  m_flag = false;
}

void Flag::clear()
{
  m_flag = false;
}

void Flag::set()
{
  m_flag = true;
}

bool Flag::get()
{
  return m_flag;
}
