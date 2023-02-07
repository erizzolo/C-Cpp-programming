/**
 * Purpose: test di un template stack con operazioni interne alla struct
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
#include "stackFLATI.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    // a stack for lowercase alphabet
    stack<char, 26> lower;
    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        if (!lower.push(letter))
        {
            cout << "Could not push letter " << letter << endl;
        }
    }
    cout << "lower: ";
    lower.print();
    cout << "sizeof(lower) " << sizeof(lower) << endl;
    while (lower.size() > 0)
    {
        char letter;
        lower.pop(letter);
        cout << letter << " ";
    }
    cout << endl;

    // a stack for powers of PI
    stack<double> pie_powers;
    double pie = 3.1415926, power = 1; // not very precise
    while (pie_powers.push(power))
    {
        power *= pie;
    }
    cout << "pie_powers: ";
    pie_powers.print();
    cout << "sizeof(pie_powers) " << sizeof(pie_powers) << endl;

    // a stack of powers of e
    stack<double> e_powers;
    double e = 2.718281828; // not very precise
    power = 1;
    while (e_powers.push(power))
    {
        power *= e;
    }
    cout << "e_powers: ";
    e_powers.print();
    cout << "sizeof(e_powers) " << sizeof(e_powers) << endl;

    // a stack of two stacks
    stack<stack<double>, 2> stacks;
    stacks.push(e_powers);
    stacks.push(pie_powers);
    cout << "sizeof(stacks) " << sizeof(stacks) << endl;
    stack<double> some_powers;
    while (stacks.pop(some_powers))
    {
        some_powers.print();
    }

    // possibili errori
    // modifiche insensate allo stack sono lecite !!!!
    if (pie_powers.theSize = 0) // bug = ==
    {
        // do nothing
    }
    else
    {
        // do something on non empty
        double x;
        pie_powers.pop(x);
    }
    pie_powers.data[0] = 47;
    // pie_powers.theSize = 12;
    pie_powers.print();

    // successful termination
    return 0;
}
