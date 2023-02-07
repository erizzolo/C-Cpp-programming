/**
 * Purpose: test di uno stack di char
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// definizione del tipo di dati contenuto nello stack
using item = char;

// dichiarazioni delle operazioni
#include "stack.h"

#define CAPACITY 32

// implementazione e completamento dichiarazioni
#include "stackFLA.cpp"
// #include "stackDA.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    stack s; // variable of type stack
    cout << "sizeof(stack) : " << sizeof(stack) << endl;
    print(s);
    item i = 'a'; // an item
    // fill the stack
    while (push(s, i) && i < 'z')
    {
        print(s);
        i++;
    }
    cout << "After insertion loop: " << endl;
    cout << "sizeof(stack) : " << sizeof(stack) << endl;
    print(s);
    // empty the stack
    while (pop(s, i))
    {
        cout << "Extracted " << i << endl;
        print(s);
    }
    cout << "After extraction loop: " << endl;
    cout << "sizeof(stack) : " << sizeof(stack) << endl;
    print(s);
    // successful termination
    return 0;
}
