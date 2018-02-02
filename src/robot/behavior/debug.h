#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <config.h>
#include <kodama.h>
#include <libs.h>


class Debug: public BEInterface
{
  private:
    Ticker ticker;


  public:
    Debug(BEngine &engine, bool precall_ = false);
    ~Debug();

    bool condition();
    int action();
};

#endif
