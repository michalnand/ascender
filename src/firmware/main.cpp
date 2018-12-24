#include <clock.h>
#include <drivers.h>
#include <back_led_light.h>

int main()
{
    //core_SystemClock_Config_216();
    core_SystemClock_Config_300();

    drivers.init();

    BackLedLight bl;
    timer.delay_ms(800);
    bl.set_mode(BL_MODE_BREATH);

    key.read();

    bl.set_mode(BL_MODE_FLASHING_FAST);

    drivers.test_imu_sensor();

    while (1)
    {

    }

    return 0;
}
