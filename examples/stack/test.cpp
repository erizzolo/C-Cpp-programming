/**
 * Purpose: test di uno stack di int
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// definizione del tipo di dati contenuto nello stack
using item = int;

// dichiarazioni delle operazioni
#include "stack.h"

#define CAPACITY 10

// implementazione e completamento dichiarazioni
#include "stackFLA.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    stack s;    // variable of type stack
    item i = 1; // an item
    // fill the stack
    while (push(s, i))
    {
        print(s);
        i++;
    }
    // empty the stack
    while (pop(s, i))
    {
        cout << "Extracted " << i << endl;
        print(s);
    }
    // successful termination
    return 0;
}
