#include <device/core.h>


#include <kodama.h>
#include <libs/imu.h>

#include "sht21.h"

class BlinkThread : public Thread
{
  private:
    TGpio<TGPIOA, 8> led;
    TGpio<TGPIOD, 13> led_back;
    TGpio<TGPIOE, 7> led_line;

    unsigned int cnt = 0;

    IMU imu;

  public:
    BlinkThread()
    {
      cnt = 0;
      imu.init(&i2c);
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
 
      imu.read();
//      sht.read();
      terminal << " " << imu.angular_rate.x << " " << imu.angular_rate.y << " " << imu.angular_rate.z << " ";
      terminal << " " << imu.acceleration.x << " " << imu.acceleration.y << " " << imu.acceleration.z << "\n";
  //    terminal << " " << sht.temperature << " " << sht.humidity << "\n";

    }
};

int main()
{
  core_init();
  kodama_init();

  terminal.printf("starting threads\n");

  BlinkThread blink;
  timer.add_task(&blink, 50, false);
  while (1)
  {
    timer.main();
  }


  TGpio<TGPIOA, 8> led;
  while (1)
  {
    led = 1;
    timer.delay_loops(20000);
    led = 0;
    timer.delay_loops(200000);
  }
  return 0;
}
