#ifndef _KODAMA_H_
#define _KODAMA_H_

#include "kodama_config.h"
#include "drivers/drivers.h"
#include "robotics/robotics.h"

extern Mem mem;
extern VPU       math;
extern TI2C<I2C_PORT, I2C_SDA_PIN, I2C_SCL_PIN, I2C_SPEED> i2c;
extern Terminal terminal;
extern Timer timer;

void kodama_init();

#endif
