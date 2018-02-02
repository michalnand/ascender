#ifndef _IMU_H_
#define _IMU_H_

#include <i2c.h>

struct sIMU_3VECT
{
    int32_t x, y, z;
};

class IMU
{
  public:
    struct sIMU_3VECT acceleration;

    struct sIMU_3VECT angular_rate;
    struct sIMU_3VECT angle;

    struct sIMU_3VECT offset;

    int32_t present;
    int32_t samples;


  private:
    class I2C_Interface *i2c;

  public:
    IMU();
    ~IMU();

    void init(class I2C_Interface *i2c_);
    void read(bool calibration = false);

  private:
    void delay_loops(uint32_t loops);
};

extern IMU imu;

#endif
