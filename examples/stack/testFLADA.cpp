/**
 * Purpose: test of stackFLA implementation
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>

using namespace std;

// definizione del tipo di dati contenuto nello stack
using item = int;

// dichiarazioni delle operazioni
#include "stack.h"

#define CAPACITY 32

// implementazione e completamento dichiarazioni
#include "stackFLA.cpp"
// #include "stackDA.cpp"

#define DEBUG 1

void details(const stack &s, const char name[])
{
    cout << name << " stack: size " << sizeof(s) << " B @ " << &s << endl;
    cout << "stack data stored @ " << &s.data[0] << endl;
    print(s);
}
/// main function
int main(int argc, char *argv[])
{
    stack original; // variable of type stack
    details(original, "original");
    cout << "Pushing something ..." << endl;
    push(original, 1);
    push(original, 2);
    push(original, 3);
    push(original, 4);
    details(original, "original");
    cout << "Making a copy: " << endl;
    stack copy = original;
    details(copy, "copy");
    item i;
    pop(original, i);
    cout << "Changing top of original stack from " << i;
    i++;
    cout << " to " << i << endl;
    push(original, i);
    i++;
    cout << "Pushing " << i << " on original stack: " << endl;
    push(original, i);
    details(original, "original");
    details(copy, "copy");
    cout << "The copy has/has not changed ??? !!!" << endl;
    // successful termination
    return 0;
}
