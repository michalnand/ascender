#ifndef _CONFIG_LOAD_H_
#define _CONFIG_LOAD_H_

#include <kodama.h>

struct sLineSensorConfig
{
  int dt;
  int threshold;
  int step;
  int weights[8];
};


struct sDistanceSensorConfig
{
  int dt;
  int threshold_front;
  int threshold_left;
  int threshold_right;
};

struct sImuSensorConfig
{
  int dt;
};

struct sMotorControllConfig
{
  int dt;
  int left_kp, left_ki, left_kd, left_aw; //left motor PID controller parameters x1000
  int right_kp, right_ki, right_kd, right_aw; //left motor PID controller parameters x1000
};



class CConfig
{
  public:
    struct sLineSensorConfig      line_sensor_config;
    struct sDistanceSensorConfig  distance_sensor_config;
    struct sImuSensorConfig       imu_sensor_config;
    struct sMotorControllConfig   motor_config;

  public:
    CConfig();
    ~CConfig();

    int init();
};

extern class CConfig config;

#endif
