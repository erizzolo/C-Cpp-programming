/**
 *  Purpose:    binary file I/O example C
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// directive for standard io functions
#include <stdio.h>
// dynamic memory allocation
#include <stdlib.h>

// should be optimized according to filesystem
#define BUFFER_SIZE 1024 // 1 KB

#define DEBUG 1

// main function
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        // open file for input
        // open the file with explicit open mode in and binary
        FILE *infile = fopen(argv[1], "rb");
        // check failure
        if (infile == NULL)
        {
            printf("failed to open file %s\n", argv[1]);
        }
        else
        {
            // success
            // open file for output
            FILE *outfile = fopen(argv[2], "wb");
            // check failure
            if (outfile == NULL)
            {
                printf("failed to open file %s\n", argv[2]);
            }
            else
            {
                // success
                // allocate buffer
                char *buffer = malloc(BUFFER_SIZE); // for reading
                if (buffer == NULL)
                {
                    printf("Cannot allocate buffer memory for %d bytes\n", BUFFER_SIZE);
                }
                else
                {
                    // I/O operations
                    size_t letti;
                    do
                    {
                        letti = fread(buffer, 1, BUFFER_SIZE, infile);
                        if (letti > 0)
                        {
                            if (DEBUG)
                            {
                                printf("%lu bytes read\n", letti);
                            }
                            size_t scritti = fwrite(buffer, 1, letti, outfile);
                            if (scritti != letti)
                            {
                                fprintf(stderr, "Written %lu bytes instead of %lu!\n", scritti, letti);
                            }
                        }
                    } while (letti > 0);
                    free(buffer);
                }
                // close file
                fclose(outfile);
            }
            // close file
            fclose(infile);
        }
    }
    else
    {
        printf("Usage %s <inputfile> <outputfile>\n", argv[0]);
    }

    // successful termination
    return 0;
}
