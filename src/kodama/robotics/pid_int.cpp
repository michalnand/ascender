#include "pid_int.h"


//create controller
//@param kp - proportional constant, kp = PIDInt_FRACTION, means kp = gain x1
//@param ki - integration constant, ki = PIDInt_FRACTION, means ki = gain x1
//@param kd - derivative constant, kd = PIDInt_FRACTION, means kd = gain x1
//@param output_range - maximum otput range, limits output into <-output_range, output_range>
PIDInt::PIDInt(short kp , short ki , short kd , short output_range_ )
{
  init(kp, ki, kd, output_range_);
}

PIDInt::~PIDInt()
{

}

//new initialization of parameters see PIDInt
void PIDInt::init(short kp, short ki, short kd, short output_range_)
{
  e0 = 0;
  e1 = 0;


  k0 = kp + ki;
  k1 = -kp;

  kd_ = kd;
  x0 = 0;
  x1 = 0;
  x2 = 0;

  u = 0;

  this->output_range = output_range_;
}


//process one discrete controller step
//@param error, required_value - meassured_value
//return controller output
short PIDInt::process(short error_)
{
  return process(error_, -error_);
}


//process one discrete controller step
//@param error, required_value - meassured_value
//@param x, plant output -> for derivative part
//return controller output

short PIDInt::process(short error_, short plant_output)
{ 
  e1 = e0;
  e0 = error_;

  x2 = x1;
  x1 = x0;
  x0 = plant_output;

  u+= (k0*e0 + k1*e1 - kd_*(x0 - 2*x1 + x2))/PIDInt_FRACTION;

  if (u > output_range)
    u = output_range;

  if (u < -output_range)
    u = -output_range;

  return u;
}
