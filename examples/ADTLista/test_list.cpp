/**
 * Purpose: test di una list
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>

using namespace std;

// definizione del tipo di dati contenuto nella list
using item = int;

// dichiarazioni delle operazioni
#include "list.h"

// implementazione e completamento dichiarazioni
#if defined DH
#include "listDH.cpp"
#elif defined SH
#include "listSH.cpp"
#elif defined SL
#include "listSL.cpp"
#else
#include "listDL.cpp"
#endif

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    list shop;                  // variable of type list
    item customer = 1, serving; // an item
    cout << "Inserting powers of 2 front " << endl;
    for (int i = 0; i < 5; i++)
    {
        insertFront(shop, customer);
        customer *= 2;
    }
    print(shop);
    customer = 1; // an item
    cout << "Inserting powers of 5 back " << endl;
    for (int i = 0; i < 5; i++)
    {
        insertBack(shop, customer);
        customer *= 5;
    }
    print(shop);
    cout << "Inserting 0 at 0" << endl;
    insertAt(shop, 0, 0);
    cout << "Inserting 3 at 3" << endl;
    insertAt(shop, 3, 3);
    cout << "Inserting " << size(shop) << " at " << size(shop) << endl;
    insertAt(shop, size(shop), size(shop));
    print(shop);
    removeFront(shop, customer);
    cout << "Extracted front " << customer << endl;
    removeBack(shop, customer);
    cout << "Extracted back " << customer << endl;
    print(shop);
    removeFrom(shop, customer, 2);
    cout << "Extracted from 2 " << customer << endl;
    print(shop);
    cout << "Inserting ordered 31" << endl;
    insertOrdered(shop, 31);
    print(shop);
    list newShop;
    cout << "Inserting ordered all from shop into newShop" << endl;
    while (removeBack(shop, customer))
    {
        insertOrdered(newShop, customer);
    }
    cout << "Shop: ";
    print(shop);
    cout << "newShop: ";
    print(newShop);
    cout << "Clearing newShop" << endl;
    clear(newShop);
    print(newShop);
    // successful termination
    return 0;
}
