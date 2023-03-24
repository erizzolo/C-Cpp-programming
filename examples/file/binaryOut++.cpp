/**
 *  Purpose:    binary file output example
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// directive for standard io functions
#include <iostream>
// directive for file io functions
#include <fstream>

using namespace std;

// planet definition and data
#include "planet.h"

#define DEBUG 1

void print(const char title[], const planet planets[], int numPlanets);

// main function
int main(int argc, char *argv[])
{
    print("Planets to be written:", planets, numPlanets);

    // filename
    const char filename[] = "planets++.dat";

    // open the file for output
    // automatic open with explicit open mode out and binary
    ofstream outfile(filename, ios::out | ios::binary);
    // check failure
    if (outfile)
    {
        // I/O operation
        outfile.write((char *)planets, sizeof(planets));
        if (DEBUG)
        {
            cout << outfile.tellp() / sizeof(planet) << " planets written on " << filename << endl;
        }
        // close file
        outfile.close();
    }
    else
    {
        cout << "failed to open file " << filename << endl;
    }

    // successful termination
    return 0;
}

void print(const char title[], const planet planets[], int numPlanets)
{
    cout << title << endl;
    for (int p = 0; p < numPlanets; p++)
    {
        cout << planets[p] << endl;
    }
    cout << endl;
}
