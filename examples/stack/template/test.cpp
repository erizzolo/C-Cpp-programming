/**
 * Purpose: test di un template stack
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// implementazione e completamento dichiarazioni
#include "stackFLAT.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    // a stack for lowercase alphabet
    stack<char, 26> lower;
    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        if (!push(lower, letter))
        {
            cout << "Could not push letter " << letter << endl;
        }
    }
    cout << "lower: ";
    print(lower);
    cout << "sizeof(lower) " << sizeof(lower) << endl;
    while (size(lower) > 0)
    {
        char letter;
        pop(lower, letter);
        cout << letter << " ";
    }
    cout << endl;

    // a stack for powers of PI
    stack<double> pie_powers;
    double pie = 3.1415926, power = 1; // not very precise
    while (push(pie_powers, power))
    {
        power *= pie;
    }
    cout << "pie_powers: ";
    print(pie_powers);
    cout << "sizeof(pie_powers) " << sizeof(pie_powers) << endl;

    // a stack of powers of e
    stack<double> e_powers;
    double e = 2.718281828; // not very precise
    power = 1;
    while (push(e_powers, power))
    {
        power *= e;
    }
    cout << "e_powers: ";
    print(e_powers);
    cout << "sizeof(e_powers) " << sizeof(e_powers) << endl;

    // a stack of two stacks
    stack<stack<double>, 2> stacks;
    push(stacks, e_powers);
    push(stacks, pie_powers);
    cout << "sizeof(stacks) " << sizeof(stacks) << endl;
    stack<double> some_powers;
    while (pop(stacks, some_powers))
    {
        print(some_powers);
    }

    // successful termination
    return 0;
}
