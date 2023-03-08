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
#include "stackFLA.cpp"   // fixed length array
// #include "stackDA.cpp"    // dynamic array
// #include "stackDANEW.cpp" // dynamic array using new/delete
// #include "stackSLL.cpp"   // stack as a list (recursive)

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    stack s; // variable of type stack
    cout << "sizeof(stack): " << sizeof(stack) << endl;
    item i = 1; // an item
    // fill the stack
    while (push(s, i))
    {
        print(s);
        i++;
    }
    print(s);
    cout << capacity(s) << endl;
    // empty the stack
    while (pop(s, i))
    {
        cout << "Extracted " << i << endl;
        print(s);
    }
    print(s);
    // successful termination
    return 0;
}
