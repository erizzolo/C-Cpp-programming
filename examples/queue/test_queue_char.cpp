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
using item = char;

// dichiarazioni delle operazioni
#include "queue.h"

#define CAPACITY 10

// implementazione e completamento dichiarazioni
// #include "queueFLA.cpp"
#include "queueDAC.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    queue q;      // variable of type queue
    item i = 'A'; // an item
    // fill the queue
    while (insert(q, i) && i <= 'Z')
    {
        cout << "Inserted " << i << ": ";
        print(q);
        if (i % 3 == 0)
        {
            item d;
            if (remove(q, d))
            {
                cout << "Extracted " << d << ": ";
                print(q);
            }
        }
        i++;
    }
    // empty the queue
    while (remove(q, i))
    {
        cout << "Extracted " << i << ": ";
        print(q);
    }
    // successful termination
    return 0;
}
