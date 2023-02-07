/**
 * Purpose: basic stack declarations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
 */

// common guard to avoid multiple inclusions
#ifndef STACK_H
#define STACK_H

// incomplete type, will be defined in stack.cpp
struct stack;

// basic operations
size_t size(const stack &);
size_t capacity(const stack &);
bool push(stack &, const item &);
bool pop(stack &, item &);

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const stack &, ostream &out = cout, bool newLine = true);

#endif