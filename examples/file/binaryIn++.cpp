/**
 *  Purpose:    binary file input example
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

#define DEBUG 0

void print(const char title[], const planet planets[], int numPlanets);

// main function
int main(int argc, char *argv[])
{

    // filename
    const char filename[] = "planets++.dat";

    // open the file for input
    // automatic open with explicit open mode in and binary
    ifstream infile(filename, ios::in | ios::binary);
    // check failure
    if (infile)
    {
        // success
        // I/O operation
        // get file dimension
        infile.seekg(0, ios::end);   // position at end of file
        size_t dim = infile.tellg(); // get absolute position, i.e. file length
        size_t planetsFound = dim / sizeof(planet);
        if (dim != planetsFound * sizeof(planet))
        {
            cout << "File size (" << dim << ") not a multiple of sizeof(planet) = " << sizeof(planet) << endl;
        }
        planet *pianeti = new planet[planetsFound]; // for reading
        if (pianeti == nullptr)
        {
            cout << "Cannot allocate memory for " << planetsFound << " planets" << endl;
        }
        else
        {
            infile.seekg(0); // reposition at begin of file
            infile.read((char *)pianeti, planetsFound * sizeof(planet));
            size_t letti = infile.gcount() / sizeof(planet);
            print("Pianeti letti:", pianeti, letti);
            // free allocated memory
            delete[] pianeti;
        }
        // close file
        infile.close();
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
