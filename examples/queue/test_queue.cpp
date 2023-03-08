/**
 * Purpose: test di una queue di int
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
 */

#include <iostream>

using namespace std;

// definizione del tipo di dati contenuto nello queue
using item = int;

// dichiarazioni delle operazioni
#include "queue.h"

#define CAPACITY 4

// implementazione e completamento dichiarazioni
// #include "queueFLA.cpp"  // fixed length array
// #include "queueFLAC.cpp" // fixed length array circular
// #include "queueDA.cpp" // dynamic array
#include "queueDAC.cpp" // dynamic array circular
// #include "queue2Stacks.cpp" // queue using 2 stacks
// #include "queueSLL.cpp" // queue as a list (recursive)

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    cout << "sizeof(queue) = " << sizeof(queue) << endl;
    queue shop;                 // variable of type queue
    item customer = 1, serving; // an item
    const item LAST = 100;
    // fill the queue
    while (insert(shop, customer) && customer < LAST)
    {
        // every third customer entering the shop, one customer is served
        if (customer % 3 == 0)
        {
            remove(shop, serving); // we know it's possible
            cout << "Serving number " << serving << endl;
        }
        print(shop);
        customer++;
    }
    // the shop is full: close it and serve customers already in the queue
    // empty the queue
    while (remove(shop, serving))
    {
        cout << "Serving number " << serving << endl;
        print(shop);
    }
    // the shop is empty: employees can finally go home and rest...
    // successful termination
    return 0;
}
