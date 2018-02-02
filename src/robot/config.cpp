#include "config.h"

class CConfig config;

CConfig::CConfig()
{

}

CConfig::~CConfig()
{

}

int CConfig::init()
{
  //TODO load from flash or usart

  //line sensor config
  line_sensor_config.dt = 4;
  line_sensor_config.threshold = 500; //300;   //above this value line is detected
  line_sensor_config.step = 64;

  line_sensor_config.weights[0] = -4*line_sensor_config.step;
  line_sensor_config.weights[1] = -3*line_sensor_config.step;
  line_sensor_config.weights[2] = -2*line_sensor_config.step;
  line_sensor_config.weights[3] = -1*line_sensor_config.step;
  line_sensor_config.weights[4] =  1*line_sensor_config.step;
  line_sensor_config.weights[5] =  2*line_sensor_config.step;
  line_sensor_config.weights[6] =  3*line_sensor_config.step;
  line_sensor_config.weights[7] =  4*line_sensor_config.step;

  //IR distance sensor config
  distance_sensor_config.dt = 10;
  distance_sensor_config.threshold_front = 20;
  distance_sensor_config.threshold_left = 20;
  distance_sensor_config.threshold_right = 20;

  //IMU sensor config
  imu_sensor_config.dt = 10;


  //motor controll config
  motor_config.dt = 4;

  motor_config.left_kp  =  800;   //P = 0.8
  motor_config.left_ki  =  90;   //I = 0.09
  motor_config.left_kd  =  1000;  //D = 1.0
  motor_config.left_aw  =  1000;  //antiwindup = 1.0

  motor_config.right_kp  =  800;   //P = 0.8
  motor_config.right_ki  =  90;    //I = 0.09
  motor_config.right_kd  =  1000;  //D = 1.0
  motor_config.right_aw  =  1000;  //antiwindup = 1.0

  return 0;
}
