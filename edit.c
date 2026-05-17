#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit.h"
#include "view.h"

Status read_and_validate_edit(char *argv[]) // Define function to read and validate edit operation arguments
{
    if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
        return e_failure;

    if (strstr(argv[4], ".mp3") == NULL)
        return e_failure;

    return e_success;
}

int match_frame(char *id, char *option) // Define function to check if the frame ID matches the edit option provided by the user
{
    if (strcmp(option, "-t") == 0 && strcmp(id, "TIT2") == 0)
        return 1;
    if (strcmp(option, "-a") == 0 && strcmp(id, "TPE1") == 0)
        return 1;
    if (strcmp(option, "-A") == 0 && strcmp(id, "TALB") == 0)
        return 1;
    if (strcmp(option, "-y") == 0 && strcmp(id, "TYER") == 0)
        return 1;
    if (strcmp(option, "-c") == 0 && strcmp(id, "COMM") == 0)
        return 1;
    return 0;
}

Status edit_operation(char *argv[]) // Define function to perform the edit operation, read the MP3 file, update the specified tag and write back to the file
{
    FILE *src = fopen(argv[4], "rb");
    FILE *temp = fopen("temp.mp3", "wb");

    if (!src || !temp)
    {
        printf("Error opening file\n");
        return e_failure;
    }

    /* Copy ID3 header */
    char header[10];
    fread(header, 1, 10, src);
    fwrite(header, 1, 10, temp);

    while (1) // Loop to read each frame, check for the matching frame ID, and update the tag if a match is found
    {
        char id[5];
        int size;
        char flags[2]; // ✅ CORRECT: 2 bytes only

        if (fread(id, 1, 4, src) != 4)
            break;

        id[4] = '\0';

        if (strcmp(id, "\0\0\0\0") == 0)
            break;

        fread(&size, 1, 4, src);
        int original_size = size;

        convert_endian(&size);

        fread(flags, 1, 2, src); // ✅ Read 2 bytes only

        if (size <= 0)
            break;

        char *frame_data = malloc(size);
        if (!frame_data)
            break;

        fread(frame_data, 1, size, src);

        fwrite(id, 1, 4, temp); // ✅ Write frame ID to temp file

        if (match_frame(id, argv[2]))
        {
            int new_size = strlen(argv[3]) + 1;
            int be_size = new_size;
            convert_endian(&be_size);

            fwrite(&be_size, 1, 4, temp);
            fwrite(flags, 1, 2, temp); // ✅ Write 2 bytes

            char encoding = 0;
            fwrite(&encoding, 1, 1, temp);
            fwrite(argv[3], 1, strlen(argv[3]), temp);

            printf("Tag updated successfully\n");
        }
        else
        {
            fwrite(&original_size, 1, 4, temp);
            fwrite(flags, 1, 2, temp); // ✅ Write 2 bytes
            fwrite(frame_data, 1, size, temp);
        }

        free(frame_data);
    }

    /* Copy remaining audio */
    char ch;
    while (fread(&ch, 1, 1, src) == 1)
        fwrite(&ch, 1, 1, temp);

    fclose(src);
    fclose(temp);

    remove(argv[4]);
    rename("temp.mp3", argv[4]);

    return e_success;
}