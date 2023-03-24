/**
 *  Purpose:    text file JSON output example, C++ style
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:       JSON stands for JavaScript Object Notation
*/

// directive for standard io functions
#include <iostream>
// directive for file io functions
#include <fstream>

using namespace std;

#include "planet.h"

#define DEBUG 0

// main function
int main(int argc, char *argv[])
{
    char filename[] = "planets++.json";

    // open the file for output
    ofstream outfile(filename); // automatic open with default open mode out
    // check failure
    if (outfile) // or if (outfile.is_open())
    {
        // success
        // I/O operation
        for (int p = 0; p < numPlanets; p++)
        {
            // see planet.h for implementation of << operator
            outfile << planets[p] << endl;
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
