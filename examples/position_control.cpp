#include <iiwa_driver/LBRConfig.h>
#include <iiwa_driver/LBRDriver.h>

class LBR: public IRobot {
public:
LBR(char* hostname, unsigned int port): hostname_(hostname_), port_(port) {}

private:
int id_;                //!< Number of the robot (If using several robots).

char hostname_;
unsigned int port_;

LBRState state;
}

template<A>
class Manipulator<A> {
public:
Manimpulator(const A& robot): robot_(robot) {}
~Manimpulator() {}

void get_position(double* values) {

}


private:
IRobot robot_;
}


int main() {

// JOINTS_NUMBER
// JOINTS_MASK
// NETWORK (host, port)
YAML::Node lbr_config_node = YAML::LoadFile("lbr_config.yaml");
Manipulator<LBR> lbr = lbr_config_node.as<Manipulator<LBR> >();

/*
/// COMMANDS
lbr.set_postion(int joint, double value);
lbr.set_postion(double* values);

lbr.set_torque(int joint, double value);
lbr.set_wrench(double* values);

lbr.set_iovalue();

/// STATES
double position = lbr.get_position(int joint);
double position* = lbr.get_position();

double torque = lbr.get_torque(int joint);
double* wrench = lbr.get_wrench();

auto value = lbr.get_iovalue(char* name);

double dt = lbr.get_dt();
*/

while (1) {

double position_des[LBR::JOINTS_NUMBER] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double position[LBR::JOINTS_NUMBER] = lbr.get_postion();

// error compute
double error[LBR::JOINTS_NUMBER];
for(int i = 0; i < LBR::JOINTS_NUMBER); ++i) {
  error[i] = position_des[i] - position[i];
}

// PD-control 
// TODO check if `set_postion` already has controller
double dt;

double kp = 5.0;
double kd = 10.0;

double u[LBR::JOINTS_NUMBER];
double error_old[LBR::JOINTS_NUMBER] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
for(int i = 0; i < LBR::JOINTS_NUMBER); ++i) {
  dt = lbr.get_dt()
  u[i] = kp * error[i] + kd * (error[i] - error_old[i]) / dt;
  error_old[i] = error[i];
}
lbr.set_position(u);

}

return 0;
}