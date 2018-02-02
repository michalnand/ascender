#ifndef _PID_INT_H_
#define _PID_INT_H_

#define PIDInt_FRACTION   64

class PIDInt
{
  public:
    short e0, e1;
    short k0, k1;

    short x0, x1, x2;
    short kd_;

  private:
    int u;
    short output_range;

  public:
    //create controller
    //@param kp - proportional constant
    //@param ki - integration constant
    //@param kd - derivative constant
    //@param output_range - maximum otput range, limits output into <-output_range, output_range>
    PIDInt(short kp = 0, short ki = 0, short kd = 0, short output_range_ = 0);
    ~PIDInt();


    //new initialization of parameters see PID
    void init(short kp, short ki, short kd, short output_range_);


    //process one discrete controller step
    //@param error, required_value - meassured_value
    //return controller output
    short process(short error_);

    //process one discrete controller step
    //@param error, required_value - meassured_value
    //@param plant_output -> for better derivative part, to avoid derivative kick
    //return controller output
    short process(short error_, short plant_output);
};


#endif
