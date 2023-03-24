/**
 *  Purpose:    binary file I/O example
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

// should be optimized according to filesystem
#define BUFFER_SIZE 1024 // 1 KB

#define DEBUG 1

// main function
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        // open the file for input
        // automatic open with explicit open mode in and binary
        ifstream infile(argv[1], ios::in | ios::binary);
        // check failure
        if (infile)
        {
            // success
            // open the file for output
            // automatic open with explicit open mode out and binary
            ofstream outfile(argv[2], ios::out | ios::binary);
            // check failure
            if (outfile)
            {
                // success
                // allocate buffer
                char *buffer = new char[BUFFER_SIZE];
                if (buffer == nullptr)
                {
                    cout << "Cannot allocate buffer memory for " << BUFFER_SIZE << " bytes" << endl;
                }
                else
                {
                    // I/O operations
                    size_t letti, scritti, lastPos = outfile.tellp();
                    do
                    {
                        infile.read(buffer, BUFFER_SIZE);
                        letti = infile.gcount();
                        if (letti > 0)
                        {
                            if (DEBUG)
                            {
                                cout << letti << " bytes read" << endl;
                            }
                            outfile.write(buffer, letti);
                            scritti = outfile.tellp() - lastPos;
                            lastPos = outfile.tellp();
                            if (scritti != letti)
                            {
                                cerr << "Written " << scritti << " bytes instead of " << letti << endl;
                            }
                        }
                    } while (letti > 0);

                    // free allocated memory
                    delete[] buffer;
                }
                // close file
                outfile.close();
            }
            else
            {
                cout << "failed to open file " << argv[2] << endl;
            }
            // close file
            infile.close();
        }
        else
        {
            cout << "failed to open file " << argv[1] << endl;
        }
    }
    else
    {
        cout << "Usage " << argv[0] << " <inputfile> <outputfile>" << endl;
    }
    // successful termination
    return 0;
}
