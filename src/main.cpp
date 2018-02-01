#include <device/core.h>


#include <kodama.h>




class BlinkThread : public CThread
{
  private:
    TGpio<TGPIOA, 8> led;
    TGpio<TGPIOD, 13> led_back;
    TGpio<TGPIOE, 7> led_line;

    unsigned int cnt = 0;
  public:
    BlinkThread()
    {
      cnt = 0;
    }

    ~BlinkThread()
    {

    }

    void main()
    {
      if (timer.get_time() > 1100)
        led_line = 1;

      if (timer.get_time() > 1600)
        led_back = 1;
      else
      if (timer.get_time() > 800)
      {
        if ((cnt%2) == 0)
          led_back = 1;
        else
          led_back = 0;
      }



      if ((cnt%10) < 5)
        led = 1;
      else
        led = 0;

      cnt++;
    }
};

int main()
{
  core_init();

  terminal.init();
  timer.init();

  terminal.printf("starting threads\n");

  BlinkThread blink;
  timer.add_task(&blink, 50, false);
  while (1)
  {
    timer.main();
  }



  return 0;
}
