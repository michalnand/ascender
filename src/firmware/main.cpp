#include <clock.h>
#include <drivers.h>
#include <adc_driver.h>
#include <back_led_light.h>

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


    drivers.test_distance_sensor();

    /*

    Gpio<TGPIOE, 7, GPIO_MODE_OUT> sensor_led;
    sensor_led = 1;

    Gpio<LED_GPIO, LED_PIN, GPIO_MODE_OUT> led;


    ADCDriver adc;

    adc.init();




    while (1)
    {
        led = 1;

        int res = 0;

        timer.reset();
        for (unsigned int i = 0; i < 1000; i++)
        {
            res+= adc.read(ADC_LINE_0);
            res+= adc.read(ADC_LINE_1);
            res+= adc.read(ADC_LINE_2);
            res+= adc.read(ADC_LINE_3);
            res+= adc.read(ADC_LINE_4);
            res+= adc.read(ADC_LINE_5);
            res+= adc.read(ADC_LINE_6);
            res+= adc.read(ADC_LINE_7);
            res+= adc.read(ADC_LEFT);
            res+= adc.read(ADC_FRONT);
            res+= adc.read(ADC_RIGHT);
        }
        long int time_adc = timer.elapsed_time();

        terminal << "time for 1000 runs = " << time_adc << "[ms]\n";

        terminal << adc.read(ADC_LINE_0) << " ";
        terminal << adc.read(ADC_LINE_1) << " ";
        terminal << adc.read(ADC_LINE_2) << " ";
        terminal << adc.read(ADC_LINE_3) << " ";
        terminal << adc.read(ADC_LINE_4) << " ";
        terminal << adc.read(ADC_LINE_5) << " ";
        terminal << adc.read(ADC_LINE_6) << " ";
        terminal << adc.read(ADC_LINE_7) << " ";
        terminal << "\n";

        terminal << adc.read(ADC_LEFT) << " ";
        terminal << adc.read(ADC_FRONT) << " ";
        terminal << adc.read(ADC_RIGHT) << " ";
        terminal << "\n";

        terminal << "\n\n";

        timer.delay_ms(10);
        led = 0;


        timer.delay_ms(100);
    }
    */
    /*
    BackLedLight bl;
    timer.delay_ms(800);
    bl.set_mode(BL_MODE_BREATH);


    key.read();

    bl.set_mode(BL_MODE_FLASHING_FAST);

    drivers.test_imu_sensor();
    */
    while (1)
    {

    }

    return 0;
}
