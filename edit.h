#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include "types.h"

Status read_and_validate_edit(char *argv[]); // Declare function prototype for read_and_validate_edit
Status edit_operation(char *argv[]);         // Declare function prototype for edit_operation
void write_big_endian(FILE *fp, int size);   // Declare function prototype for write_big_endian

#endif