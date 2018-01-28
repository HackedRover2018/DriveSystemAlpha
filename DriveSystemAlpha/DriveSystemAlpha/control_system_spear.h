#ifndef CONTROL_SYSTEM_SPEAR_H_
#define CONTROL_SYSTEM_SPEAR_H_

struct polar_coordinate
{
    double mag;
    double dir;
};

struct motor_levels
{
    double left_level;
    double right_level;
};

void command_to_polar(char* in_str, struct polar_coordinate* out_polar_coord);

struct motor_levels compute_levels(struct polar_coordinate in_polar);



#endif /* CONTROL_SYSTEM_SPEAR_H_ */