/**
 * Purpose: basic queue declarations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:
 */

// common guard to avoid multiple inclusions
#ifndef QUEUE_H
#define QUEUE_H

// incomplete type, will be defined in queue.cpp
struct queue;

// basic operations
size_t size(const queue &);
size_t capacity(const queue &);
bool insert(queue &, const item &);
bool remove(queue &, item &);

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const queue &, ostream &out = cout, bool newLine = true);

#endif