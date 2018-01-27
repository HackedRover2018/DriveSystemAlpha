#ifndef CONTROL_SYSTEM_SPEAR_H_
#define CONTROL_SYSTEM_SPEAR_H_

struct polar_coordinate
{
    double mag;
    double dir;
};

void command_to_polar(char* in_str, struct polar_coordinate* out_polar_coord);

#endif /* CONTROL_SYSTEM_SPEAR_H_ */