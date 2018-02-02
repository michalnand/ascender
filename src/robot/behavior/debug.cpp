#include "debug.h"

Debug::Debug(BEngine &engine, bool precall_)
        :BEInterface(engine, precall_)
{
  ticker.set_interval(200);
}

Debug::~Debug()
{

}

bool Debug::condition()
{
  return ticker.is_time();
}

int Debug::action()
{
  ticker.reset();
//  terminal << "line sensor     : " << line_sensor.result.on_line << " " << line_sensor.result.left_line_position << "\n";
//  terminal << "distance sensor : " << distance_sensor.result.front << " " << distance_sensor.result.left << " " << distance_sensor.result.right << "\n";
  terminal << "imu             : " << imu.angle.x << " " << imu.angle.y << " " << imu.angle.z << " " << imu.acceleration.x << " " << imu.acceleration.y << " " << imu.acceleration.z <<"\n";

  terminal << "\n\n";

  return 0;
}
