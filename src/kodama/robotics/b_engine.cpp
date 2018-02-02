#include "b_engine.h"

#include <kodama.h>

BEngine::BEngine()
{
  for (unsigned int i = 0; i < BEHAVIOR_COUNT; i++)
  {
    behavior[i] = nullptr;
  }

  time_start = 0;
  time_end = 0;
  time_call = 0;

  action_idx = -1;

  total_time = 0;
}

BEngine::~BEngine()
{

}

int BEngine::add(BEInterface  *behavior_)
{
  for (unsigned int i = 0; i < BEHAVIOR_COUNT; i++)
  if (behavior[i] == nullptr)
  {
    behavior[i] = behavior_;
    return 0;
  }

  return -1;
}


int BEngine::main()
{
  time_start = timer.get_time();

  for (unsigned int i = 0; i < BEHAVIOR_COUNT; i++)
    if (behavior[i] != nullptr)
    if (behavior[i]->precall())
    if (behavior[i]->condition())
      behavior[i]->action();


  action_idx = arbiter();

  if (action_idx != -1)
  {
    time_call = timer.get_time();
    behavior[action_idx]->action();
  }

  time_end = timer.get_time();

  return action_idx;
}

unsigned long int BEngine::duration()
{
  return time_end-time_start;
}

void BEngine::print_info()
{
  terminal << "time " << time_call << " action " << action_idx << " duration " << duration() << "[ms] " <<"\n";
}

int BEngine::arbiter()
{
  for (unsigned int i = 0; i < BEHAVIOR_COUNT; i++)
    if (behavior[i] != nullptr)
    if (behavior[i]->precall() == false)
    if (behavior[i]->condition())
    {
      return i;
    }

  return -1;
}
