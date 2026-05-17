#ifndef TYPES_H
#define TYPES_H

typedef enum // Define a new type 'Status' as an enumeration
{
    e_success,
    e_failure
} Status;

typedef enum // Define a new type 'OperationType' as an enumeration
{
    e_view,
    e_edit,
    e_help,
    e_unsupported
} OperationType;

#endif