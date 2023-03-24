/**
 *  Purpose:    text file CSV input example, C++ style
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
// directive for string io functions
#include <sstream>
// directive for string limits functions
#include <limits>
// directive for C-style string functions
#include <cstring>

using namespace std;

#include "planet.h"

#define DEBUG 1

const bool header = true; // whether to use an header line
const char delim = '"';   // string delimiter (usually ")
const char escape = '\\'; // escape character

#define BUFFER_SIZE 100

bool readCSV(const char line[], planet &p)
{
    static auto ignoreable = numeric_limits<streamsize>::max();
    istringstream in(line);
    string name;
    in >> quoted(name, delim, escape);
    strcpy(p.name, name.c_str());
    in.ignore(ignoreable, ',') >> p.mass;          // ignore , and read
    in.ignore(ignoreable, ',') >> p.distance;      // ignore , and read
    in.ignore(ignoreable, ',') >> p.inhabited;     // ignore , and read
    in.ignore(ignoreable, ',') >> p.numSatellites; // ignore , and read
    return !(in.bad() || in.fail());
}

// main function
int main(int argc, char *argv[])
{
    char filename[] = "planets++.csv";
    // open it for input
    // ifstream infile;                   // declaration
    // infile.open(filename);             // open
    ifstream infile(filename); // automatic open with default open mode in
    // ifstream infile(filename, ios::in); // automatic open with explicit open mode in
    // check failure
    if (infile.is_open()) // or simply if(infile)
    {
        char line[BUFFER_SIZE];
        if (header)
        {
            infile.ignore(numeric_limits<streamsize>::max(), '\n'); // skip header line
        }
        while (infile.getline(line, BUFFER_SIZE))
        {
            if (DEBUG)
            {
                cout << line << endl;
            }
            planet p;
            if (readCSV(line, p))
            {
                cout << p << endl;
            }
        }
    }
    else
    {
        cout << "failed to open file " << filename << endl;
    }

    // successful termination
    return 0;
}
