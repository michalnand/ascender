#include <motor.h>
#include <stm32f7xx_hal.h>

#define PWM_FREQUENCY   10000
#define PWM_PERIOD      ((F_CPU/PWM_FREQUENCY) - 1)

Motor::Motor()
{

}

Motor::~Motor()
{

}

void Motor::init()
{
    motor_enable = 1;

    pwm_a_left = 0;
    pwm_b_left = 0;

    pwm_a_right  = 0;
    pwm_b_right  = 0;

/*
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    TIM_HandleTypeDef htim1;

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = PWM_PERIOD;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
    HAL_TIM_PWM_Init(&htim1);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
    sConfigOC.Pulse = 650;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_MspInit(&htim1);


    unsigned int pwm = 20;
    TIM1->CCR1 = (pwm*(PWM_PERIOD-1))/MOTOR_SPEED_MAX;
*/
}


void Motor::pwm_init()
{
  //alternate function
  pwm_a_left.set_mode(GPIO_MODE_AF);
  pwm_b_right.set_mode(GPIO_MODE_AF);

  //connect pins to timer 1
  pwm_a_left.set_af(0x01);
  pwm_b_right.set_af(0x01);


  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  //timer 1 clock enable

  TIM1->CR1 = 0x00;                    //TIM_CounterMode_Up
  TIM1->ARR = PWM_PERIOD;              //set period
  TIM1->PSC = 2;                       //set the prescaler value

  TIM1->RCR = 0;  //repetition counter
  TIM1->EGR = 1;  //generate update event to reload


  TIM1->CCR1 = 0;
  TIM1->CCR2 = 0;

  TIM1->CR2 = 0x0100;     //  TIM_OCIdleState_Set
  TIM1->CCMR1 = 0x00070 | (0x00070<<8);  //  TIM_OCMode_PWM2

  //TIM_OCPolarity_Low, TIM_OutputState_Enable, TIM_OCNPolarity_High, TIM_OutputNState_Enable
  unsigned int tmp = 0x0002 | 0x0001 | 0x0000 | 0x0004;
  TIM1->CCER = tmp | (tmp <<4);

  //enable timer 1
  TIM1->CR1 |= TIM_CR1_CEN;

  //enable pwm output
  TIM1->BDTR |= TIM_BDTR_MOE;
}


void Motor::run_left(int pwm)
{
    //check way of motor

    if (pwm == 0)
    {
        pwm_a_left = 0;
        pwm_b_left = 0;
    }
    else
    if (pwm < 0)
    {
        //left backward
        pwm_a_left = 1;
        pwm_b_left = 0;

        pwm = MOTOR_SPEED_MAX - pwm;
    }
    else
    {
        //left forward
        pwm_a_left = 0;
        pwm_b_left = 1;
    }

    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;

    //TIM1->CCR2 = (pwm*(PWM_PERIOD-1))/MOTOR_SPEED_MAX;
}

void Motor::run_right(int pwm)
{
    //check way of motor

    if (pwm == 0)
    {
        pwm_a_right = 0;
        pwm_b_right = 0;
    }
    else
    if (pwm < 0)
    {
        //left backward
        pwm_a_right = 0;
        pwm_b_right = 1;

        pwm = MOTOR_SPEED_MAX - pwm;
    }
    else
    {
        //right forward
        pwm_a_right = 1;
        pwm_b_right = 0;
    }

    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;

    //TIM1->CCR2 = (pwm*(PWM_PERIOD-1))/MOTOR_SPEED_MAX;
}
