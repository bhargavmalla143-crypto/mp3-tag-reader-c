#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

/* Convert Big Endian to Little Endian */
void convert_endian(int *size)
{
    char *ptr = (char *)size;
    char temp;

    temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;

    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}

Status read_and_validate_view(char *argv[]) // Define function to read and validate view operation arguments
{
    if (argv[2] == NULL)
        return e_failure;

    if (strstr(argv[2], ".mp3") == NULL)
        return e_failure;

    return e_success;
}

void print_tag(char *id, char *data) // Define function to print the tag information based on the frame ID
{
    if (strcmp(id, "TIT2") == 0)
        printf("TITLE   : %s\n", data);
    else if (strcmp(id, "TPE1") == 0)
        printf("ARTIST  : %s\n", data);
    else if (strcmp(id, "TALB") == 0)
        printf("ALBUM   : %s\n", data);
    else if (strcmp(id, "TYER") == 0)
        printf("YEAR    : %s\n", data);
    else if (strcmp(id, "TCON") == 0)
        printf("GENRE   : %s\n", data);
    else if (strcmp(id, "COMM") == 0)
        printf("COMMENT : %s\n", data);
}

Status view(char *argv[]) // Define function to perform the view operation, read the MP3 file and print the tag details
{
    FILE *fp = fopen(argv[2], "rb"); // Open the MP3 file in binary mode
    if (!fp)
    {
        printf("Unable to open file\n");
        return e_failure;
    }

    char header[10];

    /* Read ID3 header */
    fread(header, 1, 10, fp);

    if (strncmp(header, "ID3", 3) != 0) // Validate that the file has an ID3 tag
    {
        printf("Not a valid MP3 file\n");
        fclose(fp);
        return e_failure;
    }

    printf("\n------ MP3 TAG DETAILS ------\n");

    while (1) // Loop to read each frame until the end of the tag is reached
    {
        char id[5];
        int size;
        char flags[2];

        if (fread(id, 1, 4, fp) != 4)
            break;

        id[4] = '\0';

        if (strcmp(id, "\0\0\0\0") == 0)
            break;

        fread(&size, 1, 4, fp);
        convert_endian(&size); // Convert the size from big endian to little endian

        fread(flags, 1, 2, fp);

        if (size <= 0)
            break;

        char *data = malloc(size);
        if (!data)
            break;

        fread(data, 1, size, fp);

        /* First byte is encoding */
        char *text = data + 1;

        /* Ensure null termination */
        text[size - 1] = '\0';

        print_tag(id, text);

        free(data);
    }

    fclose(fp);
    return e_success;
}