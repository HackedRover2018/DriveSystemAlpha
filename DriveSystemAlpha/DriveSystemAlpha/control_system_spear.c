#include "control_system_spear.h"
#include <string.h>
#include <stdlib.h>

void command_to_polar(char* in_str, struct polar_coordinate* out_polar_coord)
{
    char* mag_str = strtok(in_str, " ");
    out_polar_coord->mag = atof(mag_str);
    char* dir_str = strtok(NULL, " ");
    out_polar_coord->dir = atof(dir_str);
}
