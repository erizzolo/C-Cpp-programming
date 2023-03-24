/**
 *  Purpose:    text file CSV output example, C++ style
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:       CSV stands for Comma Separated Values
*/

// directive for standard io functions
#include <iostream>
// directive for io manipulation
#include <iomanip>
// directive for file io functions
#include <fstream>

using namespace std;

#include "planet.h"

#define DEBUG 0

const bool header = true; // whether to use an header line
const char delim = '"';   // string delimiter (usually ")
const char escape = '\\'; // escape character

void printCSV(const planet &p, ostream &os)
{
    // output planet p on os
    os << quoted(p.name, delim, escape);
    os << "," << p.mass;
    os << "," << p.distance;
    os << "," << p.inhabited;
    os << "," << p.numSatellites;
    os << endl;
}

// main function
int main(int argc, char *argv[])
{
    char filename[] = "planets++.csv";

    // open the file for output
    ofstream outfile(filename); // automatic open with default open mode out
    // check failure
    if (outfile) // or if (outfile.is_open())
    {
        // success
        // I/O operation
        if (header)
        {
            outfile << "name,mass,distance,inhabited,numSatellites" << endl;
        }
        for (int p = 0; p < numPlanets; p++)
        {
            printCSV(planets[p], outfile);
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
