/**
 *  Purpose:    binary file input example C
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// directive for standard io functions
#include <stdio.h>
// dynamic memory allocation
#include <stdlib.h>

// planet definition and data
#include "planetC.h"

#define DEBUG 1

void printPlanet(const planet p, FILE *out);
void print(const char title[], const planet planets[], int numPlanets);

// main function
int main(int argc, char *argv[])
{
    // filename
    const char filename[] = "planets.dat";

    // open the file with explicit open mode in and binary
    FILE *infile = fopen(filename, "rb");
    // check failure
    if (infile != NULL)
    {
        // success
        // I/O operation
        // get file dimension
        fseek(infile, 0, SEEK_END); // position at end of file
        size_t dim = ftell(infile); // get absolute position, i.e. file length
        size_t planetsFound = dim / sizeof(planet);
        if (dim != planetsFound * sizeof(planet))
        {
            printf("File size (%lu) not a multiple of sizeof(planet) = %lu\n", dim, sizeof(planet));
        }
        planet *pianeti = malloc(planetsFound * sizeof(planet)); // for reading
        if (pianeti == NULL)
        {
            printf("Cannot allocate memory for %lu planets\n", planetsFound);
        }
        else
        {
            fseek(infile, 0, SEEK_SET); // reposition at begin of file
            size_t letti = fread(pianeti, sizeof(planet), planetsFound, infile);
            print("Pianeti letti:", pianeti, letti);
            // free allocated memory
            free(pianeti);
        }
        // close file
        fclose(infile);
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