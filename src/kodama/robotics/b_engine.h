#ifndef _B_ENGINE_H_
#define _B_ENGINE_H_

#include "behavior.h"

#define BEHAVIOR_COUNT    10

class BEngine
{
  friend BEInterface;

  private:
    int action_idx;
    unsigned long int time_call, time_start, time_end, total_time;

  protected:
    BEInterface  *behavior[BEHAVIOR_COUNT];

  public:
    BEngine();
    virtual ~BEngine();

    //run this in main loop
    //first all behaviors with precall set to true are called
    //then first behavior with true condition is called
    int main();

    unsigned long int duration();
    void print_info();

  protected:
    int add(BEInterface  *behavior_);
    virtual int arbiter();

};


#endif
