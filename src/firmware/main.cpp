#include <clock.h>
#include <drivers.h>
#include <adc_driver.h>
#include <back_led_light.h>

#include <motor.h>


int main()
{
    //core_SystemClock_Config_216();
    core_SystemClock_Config_312();

    drivers.init();

    BackLedLight bl;
    timer.delay_ms(800);
    bl.set_mode(BL_MODE_BREATH);

    key.read();
    bl.set_mode(BL_MODE_FLASHING_FAST);


    drivers.test_encoder_sensor();

    Motor motor;
    motor.init();


/*
    motor.run_left(30);
    timer.delay_ms(200);
    motor.run_left(0);
    timer.delay_ms(200);


    motor.run_left(-30);
    timer.delay_ms(200);
    motor.run_left(0);
    timer.delay_ms(200);



    motor.run_right(30);
    timer.delay_ms(200);
    motor.run_right(0);
    timer.delay_ms(200);


    motor.run_right(-30);
    timer.delay_ms(200);
    motor.run_right(0);
    timer.delay_ms(200);
*/
    while (1)
    {

    }

    return 0;
}
