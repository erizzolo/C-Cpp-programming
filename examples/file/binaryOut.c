/**
 *  Purpose:    binary file output example C
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// directive for standard io functions
#include <stdio.h>

// planet definition and data
#include "planetC.h"

#define DEBUG 1

void printPlanet(const planet p, FILE *out);
void print(const char title[], const planet planets[], int numPlanets);

// main function
int main(int argc, char *argv[])
{
    print("Planets to be written:", planets, numPlanets);

    // filename
    const char filename[] = "planets.dat";

    // open the file with explicit open mode out and binary
    FILE *outfile = fopen(filename, "wb");
    // check failure
    if (outfile != NULL)
    {
        // I/O operation
        size_t written = fwrite(planets, sizeof(planet), numPlanets, outfile);
        if (DEBUG)
        {
            printf("%lu planets written on %s\n", written, filename);
        }
        // close file
        fclose(outfile);
    }
    else
    {
        printf("failed to open file %s\n", filename);
    }

    // successful termination
    return 0;
}

void print(const char title[], const planet planets[], int numPlanets)
{
    printf("%s\n", title);
    for (int p = 0; p < numPlanets; p++)
    {
        printPlanet(planets[p], stdout);
        printf("\n");
    }
    printf("\n");
}

void printPlanet(const planet p, FILE *out)
{
    fprintf(out, "{\"name\": \"%s\"", p.name);
    fprintf(out, ", \"mass\": %lg", p.mass);
    fprintf(out, ", \"distance\": %lg", p.distance);
    fprintf(out, " \"inhabited\": %s", p.inhabited ? "true" : "false");
    fprintf(out, " ,\"numSatellites\": %d}", p.numSatellites);
}