#include "behavior.h"
#include "b_engine.h"

BEInterface::BEInterface(BEngine &engine, bool precall_)
{
  engine.add(this);
  m_precall = precall_;
}


BEInterface::~BEInterface()
{

}

bool BEInterface::condition()
{
  return false;
}

int BEInterface::action()
{
  return 0;
}

bool BEInterface::precall()
{
  return m_precall;
}
