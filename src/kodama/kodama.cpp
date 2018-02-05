#include "kodama.h"

Mem mem;
VPU       math;
TI2C<I2C_PORT, I2C_SDA_PIN, I2C_SCL_PIN, I2C_SPEED> i2c;
Terminal terminal;
Timer timer;

void kodama_init()
{
  timer.init();
  terminal.init();
}
