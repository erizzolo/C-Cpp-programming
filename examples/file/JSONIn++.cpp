/**
 *  Purpose:    text file JSON input example, C++ style
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:       JSON stands for JavaScript Object Notation
*/

// directive for standard io functions
#include <iostream>
// directive for file io functions
#include <fstream>
// directive for string io functions
#include <sstream>
// directive for string limits functions
#include <limits>

using namespace std;

#include "planet.h"

#define DEBUG 1

#define BUFFER_SIZE 200

// main function
int main(int argc, char *argv[])
{
    char filename[] = "planets++.json";
    // open it for input
    // ifstream infile;                   // declaration
    // infile.open(filename);             // open
    ifstream infile(filename); // automatic open with default open mode in
    // ifstream infile(filename, ios::in); // automatic open with explicit open mode in
    // check failure
    if (infile.is_open()) // or simply if(infile)
    {
        char line[BUFFER_SIZE];
        while (infile.getline(line, BUFFER_SIZE))
        {
            if (DEBUG)
            {
                cout << line << endl;
            }
            planet p;
            istringstream in(line);
            // see planet.h for implementation of >> operator
            in >> p;
            cout << p << endl;
        }
    }
    else
    {
        cout << "failed to open file " << filename << endl;
    }

    // successful termination
    return 0;
}
