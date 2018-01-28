#include "control_system_spear.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DELTA_SCALE 0.5
#define MAGNIUTUDE_SCALE 2/3

// Private functions
double left_set_point_delta(struct polar_coordinate in_polar);
double right_set_point_delta(struct polar_coordinate in_polar);

void command_to_polar(char* in_str, struct polar_coordinate* out_polar_coord)
{
    char* mag_str = strtok(in_str, " ");
    out_polar_coord->mag = atof(mag_str);
    char* dir_str = strtok(NULL, " ");
    out_polar_coord->dir = atof(dir_str);
}

struct motor_levels compute_levels(struct polar_coordinate in_polar)
{
    struct motor_levels out_levels;
    out_levels.right_level = right_set_point_delta(in_polar);
    out_levels.left_level = left_set_point_delta(in_polar);
    return out_levels;
}

double left_set_point_delta(struct polar_coordinate in_polar)
{
    return  MAGNIUTUDE_SCALE * (in_polar.mag * sin(in_polar.dir) + DELTA_SCALE * in_polar.mag * cos(in_polar.dir));
}

double right_set_point_delta(struct polar_coordinate in_polar)
{
    return MAGNIUTUDE_SCALE * (in_polar.mag * sin(in_polar.dir) - DELTA_SCALE * in_polar.mag * cos(in_polar.dir));
}


