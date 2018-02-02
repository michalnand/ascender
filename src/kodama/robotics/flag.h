#ifndef _FLAG_H_
#define _FLAG_H_

class Flag
{
  private:
    bool m_flag;

  public:
    Flag();

    void clear();
    void set();

    bool get();
};


#endif
