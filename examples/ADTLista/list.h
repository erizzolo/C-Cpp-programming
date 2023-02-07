/**
 * Purpose: basic list declarations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
 */

// common guard to avoid multiple inclusions
#ifndef LIST_H
#define LIST_H

// incomplete type, will be defined in list.cpp
struct list;

// basic operations
size_t size(const list &);                   // number of elements
size_t capacity(const list &);               // maximum number of elements
bool insertFront(list &, const item &);      // insert at front
bool insertBack(list &, const item &);       // insert at back
bool removeFront(list &, item &);            // remove from front
bool removeBack(list &, item &);             // remove from back
bool insertAt(list &, const item &, size_t); // insert at position (0 = front, size = back)
bool removeFrom(list &, item &, size_t);     // remove from position (0 = front, size - 1 = back)
bool insertOrdered(list &, const item &);    // insert in order (requires < to be defined)
void clear(list &);                          // empty the list (i.e removes all elements)

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const list &, ostream &out = cout, bool newLine = true);

#endif