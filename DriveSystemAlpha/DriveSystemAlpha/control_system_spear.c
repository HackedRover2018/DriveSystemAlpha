#include "control_system_spear.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DELTA_SCALE 0.5
#define MAGNIUTUDE_SCALE 0.666

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
    //printf("compute left: %i /100; right: %i /100\n", (int) out_levels.left_level*100, (int) out_levels.right_level*100);
    return out_levels;
}

double left_set_point_delta(struct polar_coordinate in_polar)
{
    //printf("sin(dir) = %i; cos(dir) = %i; mag = %i; DELTA_SCALE = %i; MAGNITUDE_SCALE = %i\n", (int)(sin(in_polar.dir)*100), (int)(cos(in_polar.dir)*100), (int) (in_polar.mag*100), (int) (DELTA_SCALE*100), (int) (MAGNIUTUDE_SCALE*100));
    return  MAGNIUTUDE_SCALE * (in_polar.mag * sin(in_polar.dir) + DELTA_SCALE * in_polar.mag * cos(in_polar.dir));
}

double right_set_point_delta(struct polar_coordinate in_polar)
{
    return MAGNIUTUDE_SCALE * (in_polar.mag * sin(in_polar.dir) - DELTA_SCALE * in_polar.mag * cos(in_polar.dir));
}


