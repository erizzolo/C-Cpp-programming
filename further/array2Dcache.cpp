/**
 * Purpose: Multidimensional arrays and cache
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/01/07
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 1

#define DIM 20000

/// global variable (visible everywhere)
int v[DIM][DIM];

/// main function
int main(int argc, char *argv[])
{
    // random asssignment
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            v[i][j] = rand();
        }
    }

    clock_t startTime = clock(); // read clock
    // outer loop on first index, inner loop on second
    // follows allocation strategy: optimal cache usage
    // time 1s approximately on my platform
    long long int sumByFirstIndex = 0;
    for (int f = 0; f < DIM; f++)
    {
        for (int s = 0; s < DIM; s++)
        {
            sumByFirstIndex += v[f][s];
        }
    }
    cout << "somma = " << sumByFirstIndex << endl;

    clock_t endTime = clock(); // read clock again
    double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
    cout << " completed in " << duration << "ms" << endl;

    clock_t startTime2 = clock(); // read clock
    long long int sumBySecondIndex = 0;
    // outer loop on second index, inner loop on first
    // does not follow allocation strategy: non optimal cache usage
    // time 12s approximately on my platform
    for (int s = 0; s < DIM; s++)
    {
        for (int f = 0; f < DIM; f++)
        {
            sumBySecondIndex += v[f][s];
        }
    }
    cout << "somma = " << sumBySecondIndex << endl;

    clock_t endTime2 = clock(); // read clock again
    double duration2 = 1000.0 * (endTime2 - startTime2) / CLOCKS_PER_SEC;
    cout << " completed in " << duration2 << "ms" << endl;
    /// successful termination
    return 0;
}
