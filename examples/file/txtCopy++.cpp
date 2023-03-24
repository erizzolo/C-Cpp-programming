/**
 *  Purpose:    text file I/O example, C++ style
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2023/03/24
 *  Note:
*/

// directive for standard io functions
#include <iostream>
// directive for file io functions
#include <fstream>

using namespace std;

#define BUFFER_SIZE 100

#define DEBUG 0

// main function
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        // open it for input
        // ifstream infile;                   // declaration
        // infile.open(filename);             // open
        ifstream infile(argv[1]); // automatic open with default open mode in
        // ifstream infile(argv[1], ios::in); // automatic open with explicit open mode in
        // check failure
        if (infile.is_open()) // or simply if(infile)
        {
            // success
            // open the file for output
            ofstream outfile(argv[2]); // automatic open with default open mode out
            // check failure
            if (outfile) // or if (outfile.is_open())
            {
                // I/O operation
                char letti[BUFFER_SIZE];
                // do
                // {
                //     // read word by word ...
                //     // infile >> letti;
                //     // read line by line ...
                //     infile.getline(letti, BUFFER_SIZE);
                //     if (!infile.eof())
                //     {
                //         outfile << letti << endl;
                //     }
                // } while (!infile.eof());
                // alternative
                while (infile.getline(letti, BUFFER_SIZE))
                {
                    outfile << letti << endl;
                    cout << letti << endl;
                }
                // close file
                outfile.close();
            }
            else
            {
                cerr << "failed to open file " << argv[2] << endl;
            }
            // close file
            infile.close();
        }
        else
        {
            cerr << "failed to open file " << argv[1] << endl;
        }
    }
    else
    {
        cerr << "Usage " << argv[0] << " <inputfile> <outputfile>" << endl;
    }
    // successful termination
    return 0;
}
