#include <clock.h>
#include <drivers.h>
#include <adc_driver.h>
#include <back_led_light.h>

#include <motor.h>

int main()
{
    core_SystemClock_Config_216();
    //core_SystemClock_Config_312();

    drivers.init();

    BackLedLight bl;
    timer.delay_ms(800);
    bl.set_mode(BL_MODE_BREATH);

    key.read();
    //bl.set_mode(BL_MODE_FLASHING_FAST);

/*
    Motor motor;
    motor.init();

    motor.run_left(100);
    timer.delay_ms(800);
    motor.run_left(0);
    timer.delay_ms(800);


    motor.run_left(-100);
    timer.delay_ms(800);
    motor.run_left(0);
    timer.delay_ms(800);


    motor.run_right(100);
    timer.delay_ms(800);
    motor.run_right(0);
    timer.delay_ms(800);


    motor.run_right(-100);
    timer.delay_ms(800);
    motor.run_right(0);
    timer.delay_ms(800);

*/

    //drivers.test_motor_speed_feedback();
    //drivers.test_motor_gyro_feedback();

    drivers.test_line_follower(); 



    return 0;
}
