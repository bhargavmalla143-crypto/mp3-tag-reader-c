#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include "types.h"

Status read_and_validate_view(char *argv[]); // Declare function prototype for read_and_validate_view
Status view(char *argv[]);                   // Declare function prototype for view

void convert_endian(int *size); // Declare only once

#endif