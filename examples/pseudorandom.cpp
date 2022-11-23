/**
 * Esempio di generazione numeri (pseudo)casuali
 * Author:  ER
 * Date:    2022/11/23
 * Note:
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const bool DEBUG = true;

int main(int argc, char *args[])
{
    // showing the range of rand() function
    cout << "0 <= rand() <= RAND_MAX = " << RAND_MAX << endl;
    // see how many bits we have in a random number
    unsigned int bits = 0, power = 1; // 2^bits
    while (power < RAND_MAX)
    {
        power *= 2; // power <<= 1;
        ++bits;
    }
    cout << "0 <= rand() <= RAND_MAX = " << RAND_MAX << " < " << power << " = 2^" << bits << endl;
    // use for test: setting a given seed will give you the same random sequence
    cout << "Seeding with 42. Here are some random numbers: ";
    srand(42);
    for (int number = 0; number < 10; ++number)
    {
        cout << rand() << " ";
    }
    cout << endl;
    cout << "Seeding again with 42. Here are some random numbers: ";
    srand(42);
    for (int number = 0; number < 10; ++number)
    {
        cout << rand() << " ";
    }
    // use for real: setting a "random" seed will give you a random sequence
    cout << endl;
    cout << "Seeding with current time. Here are some random numbers: ";
    srand(time(NULL));
    for (int number = 0; number < 10; ++number)
    {
        cout << rand() << " ";
    }
    cout << endl;
    {
        // generating random numbers in interval [min, max]
        int casuale, calls = 0, min = 10, max = 30;
        cout << "Generating a random number in [" << min << ", " << max << "], the inefficient way!" << endl;
        do
        {
            casuale = rand();
            ++calls;
        } while (casuale < min || casuale > max);
        cout << "Here it is: " << casuale << " after " << calls << " call(s) to rand()!!!" << endl;
    }
    {
        // generating random numbers in interval [min, max]
        int casuale, calls = 0, min = 10, max = 30;
        cout << "Generating a random number in [" << min << ", " << max << "], the efficient (though not perfect) way!" << endl;
        casuale = min + rand() % (max - min + 1);
        ++calls;
        cout << "Here it is: " << casuale << " after " << calls << " call to rand()!!!" << endl;
    }
    {
        // generating random numbers in interval [min, max]
        int calls = 0, min = 10, max = 30;
        cout << "Generating a random number in [" << min << ", " << max << "], the perfect way!" << endl;
        int groups = max - min + 1;   // divide in groups, one group for each possible value
        int size = RAND_MAX / groups; // size of each group
        int group;                    // now choose a random group: group 0 = 0..size-1, group 1 = size..2*size-1, ...
        // note that some numbers may belong to an "invalid" group
        do
        {
            group = rand() / size; // which group?
            ++calls;
        } while (group >= groups); // group may be invalid if groups does not divide RAND_MAX
        int casuale = group + min; // here it is in [min, max]
        cout << "Here it is: " << casuale << " after " << calls << " call to rand()!!!" << endl;
    }

    // open question
    cout << "How do I get a random number if the interval exceeds " << RAND_MAX << " ???" << endl;
    cout << "e.g. what if I want a random number between 0 and " << (1ULL << (2 * bits)) << " ???" << endl;
    // Checking for the period of the random generator, if possible...
    // approximate with the least multiple of 8 greater or equal
    bits = ((bits + 7) / 8) * 8;
    cout << "Checking period using " << bits << " bits..." << endl;
    cout << "Hint: if you see that the bits used for checking is more than 16, hit Ctrl-C now, or be prepared to wait for years !!!!" << endl;
    // initialise random generator seed
    srand(time(NULL));
    // fill 64 bits with the first few random values
    unsigned long long int target = 0;
    for (int i = 0; i < 64 / bits; ++i)
    {
        target = (target << bits) + rand();
    }
    cout << "target 64 bits = " << target << endl;
    // now wait until the 64 bits will come again
    // i.e. the same first random values
    unsigned long long int period = 0;
    unsigned long long int value = 0;
    do
    {
        value = (value << bits) + rand();
        ++period;
    } while (value != target && period != 0);
    // if period found ...
    if (period != 0)
    {
        cout << "Found period = " << period << endl;
        // show that after period we get the same sequence of numbers
        cout << "Sequence: ";
        const int length = 10;
        unsigned long long int calls = period;
        for (int i = 0; i < length; ++i)
        {
            cout << rand() << ", ";
            --calls;
        }
        cout << endl
             << "Waiting " << period << " calls... " << endl;
        while (calls > 0)
        {
            int casuale = rand();
            --calls;
        }
        cout << "Sequence: ";
        for (int i = 0; i < length; ++i)
        {
            cout << rand() << ", ";
            --period;
        }
        for (int i = 0; i < length; ++i)
        {
            cout << rand() << ", ";
        }
        cout << endl
             << "Isn't it the same sequence ??? !!!" << endl;
    }
    else
    {
        cout << "Sorry, period too long ... better terminate" << endl;
        cout << "target = " << target << ", value = " << value << endl;
    }

    // successful termination
    return 0;
}
