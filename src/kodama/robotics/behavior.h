#ifndef _BEHAVIOR_H_
#define _BEHAVIOR_H_

class BEngine;

class BEInterface
{
  friend BEngine;

  protected:
    bool m_precall;

  public:
    BEInterface(BEngine &engine, bool precall_ = false);
    virtual ~BEInterface();

  protected:
    /*
      implement your own
      return true if action shall be called
    */
    virtual bool condition();

    /*
        implement your own
        execute action
    */
    virtual int action();

    /*
      return true if this behavior should be allways called
    */
    virtual bool precall() final;
};

#endif
