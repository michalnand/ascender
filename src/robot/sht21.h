#ifndef _SHT_21_H_
#define _SHT_21_H_

class SHT21
{
  public:
    int temperature, humidity;

  public:

    SHT21();
    ~SHT21();
    void read();

  private:
    unsigned int read_(unsigned char command);
    void delay(unsigned int loops);
};

#endif
