/*
    Purpose:    Allocation of arrays in memory
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2019/11/23
    Note:
*/
// directive for standard io functions
#include <iostream>
// directive for io manipulation
#include <iomanip>

using namespace std;

#define DEBUG 1

// funzione principale
int main(int argc, char *argv[])
{
    {
        cout << "ARRAY ALLOCATION IN MEMORY: ONE DIMENSION" << endl;
        cout << "Declaring an array variable means:" << endl;
        cout << "1. reserving enough contiguous memory space for each element" << endl;
        cout << "2. assigning to the variable name the (initial) address of the space" << endl;
        cout << "   N.B. - the address cannot be changed during variable's lifetime!!!" << endl;
        double v[4]; /// example of an array of 4 doubles named v
        cout << "Example with an array of 4 doubles named v:" << endl;
        cout << "double v[4];	/// declaration" << endl;
        cout << "reserves 4 * " << sizeof(v[0]) << " = " << sizeof(v) << " B of memory like this:" << endl;
        cout << "                      0   1   2   3   4   5   6   7" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << "v: " << setw(15) << v << "  |   |   |   |   |   |   |   |   | first double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[1] << "  |   |   |   |   |   |   |   |   | second double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[2] << "  |   |   |   |   |   |   |   |   | third double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[3] << "  |   |   |   |   |   |   |   |   | fourth double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << endl;
    }

    {
        cout << "ARRAY ALLOCATION IN MEMORY: TWO DIMENSIONS" << endl;
        cout << "Declaring an array variable means:" << endl;
        cout << "1. reserving enough contiguous memory space for each element" << endl;
        cout << "2. assigning to the variable name the (initial) address of the space" << endl;
        cout << "   N.B. - the address cannot be changed during variable's lifetime!!!" << endl;
        cout << "BUT!!! How are the elements ordered in this memory space???" << endl;
        cout << "There is no obvious answer but two possibilities:" << endl;
        cout << "1. the last index varies more rapidly than the first" << endl;
        cout << "2. the last index varies more slowly than the first" << endl;
        cout << "Let's see which one the compiler chooses." << endl;
        double v[4][3]; /// example of an array of 4x3 = 12 doubles named v
        cout << "Example with an array of 4x3 = 12 doubles named v:" << endl;
        cout << "double v[4][3];	/// declaration" << endl;
        // typedef double row[3]; row v[4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                cout << "v[" << i << "][" << j << "] @ " <<  &v[i][j] << " : " << v[i][j] << endl;
        cout << "That is, we have an array of 4 elements (first index) and each element consists of 3 doubles." << endl;
        cout << "--> 1. the last index varies more rapidly than the first !!!" << endl;
        cout << "That means, cache memory will perform better if I access elements varying" << endl;
        cout << "the last index(es) more rapidly than the first one(s)." << endl;
        cout << "i.e use the first index for the most important ordering criterion, than the second, third ..." << endl;
        cout << "i.e when I use nested loops to process the elements, the outermost loop should be on the first index" << endl;
        cout << "and the innermost loop should be on the last index." << endl;
    }

    // successful termination
    return 0;
}
