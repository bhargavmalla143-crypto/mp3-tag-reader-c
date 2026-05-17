/*
Name:-Malla.Surya Bhargav
Batch:-36A

Description:-This project is a command-line based MP3 Tag Reader and Editor developed using C programming.
It reads and displays MP3 metadata such as Title, Artist, Album, Year, Genre, and Comment.
It also allows editing of specific tag fields without affecting the audio content.*/

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "view.h"
#include "edit.h"

OperationType check_operation_type(char *argv[]); // Declare function prototype for check_operation_type

int main(int argc, char *argv[])
{
    if (argc < 2) // Check if at least one argument is provided
    {
        printf("Usage:\n");
        printf("./mp3.exe -v file.mp3\n");
        printf("./mp3.exe -e -t \"New Title\" file.mp3\n");
        printf("./mp3.exe -h\n");
        return e_failure;
    }

    OperationType op = check_operation_type(argv); // Determine the operation type based on the first argument

    /* VIEW OPERATION */
    if (op == e_view) // Check if the operation is view
    {
        printf("VIEW FUNCTION CALLED\n");

        if (read_and_validate_view(argv) == e_success)
        {
            view(argv);
        }
        else
        {
            printf("View validation failed\n");
        }
    }

    /* EDIT OPERATION */
    else if (op == e_edit) // Check if the operation is edit
    {
        printf("EDIT FUNCTION CALLED\n");

        if (read_and_validate_edit(argv) == e_success)
        {
            edit_operation(argv);
        }
        else
        {
            printf("Edit validation failed\n");
        }
    }

    /* HELP OPERATION */
    else if (op == e_help) // Check if the operation is help
    {
        printf("HELP FUNCTION CALLED\n");
        printf("Edit Options:\n");
        printf("-t : Title\n");
        printf("-a : Artist\n");
        printf("-A : Album\n");
        printf("-y : Year\n");
        printf("-c : Comment\n");
    }

    else
    {
        printf("Unsupported operation\n");
    }

    return e_success;
}

/* Function outside main */
OperationType check_operation_type(char *argv[]) // Define the function to check the operation type based on the first argument
{
    if (strcmp(argv[1], "-v") == 0)
        return e_view;
    else if (strcmp(argv[1], "-e") == 0)
        return e_edit;
    else if (strcmp(argv[1], "-h") == 0)
        return e_help;
    else
        return e_unsupported;
}