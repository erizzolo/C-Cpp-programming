/**
 *  Purpose:    text file I/O example
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// directive for standard io functions
#include <stdio.h>

#define BUFFER_SIZE 100

#define DEBUG 0

// main function
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        // open file for input 
        FILE *infile = fopen(argv[1], "r");
        // check failure
        if (infile == NULL)
        {
            printf("failed to open file %s\n", argv[1]);
        }
        else
        {
            // success
            // open file for output
            FILE *outfile = fopen(argv[2], "w");
            // check failure
            if (outfile == NULL)
            {
                printf("failed to open file %s\n", argv[2]);
            }
            else                                                              
            {
                // I/O operation
                char letti[BUFFER_SIZE];
                // do
                // {
                //     // read word by word ...
                //     // fscanf(infile, "%100s", letti);
                //     // read line by line ...
                //     fgets(letti, BUFFER_SIZE, infile);
                //     if (!feof(infile))
                //     {
                //         fprintf(outfile, "%s", letti);
                //     }
                // } while (!feof(infile));
                // alternative
                while (fgets(letti, BUFFER_SIZE, infile) != NULL)
                {
                    if (DEBUG)
                    {
                        fprintf(stdout, "%s\n", letti);
                    }
                    fprintf(outfile, "%s", letti);
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
