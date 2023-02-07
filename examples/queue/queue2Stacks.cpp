/**
 * Purpose: basic queue implementation based on two stacks
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:
 */

/**
 * The idea is to use two stacks, one for insertion and one for removal,
 * decant from the first into the second as needed.
 */

#include "stack.h"
#include "stackFLA.cpp"

// definition of queue data type
struct queue
{
    item data[CAPACITY]; // the actual data
    stack insertion;     // insertion stack (reverse order)
    stack removal;       // removal stack (queue order)
};

// basic operations
size_t size(const queue &q)
{
    return size(q.insertion) + size(q.removal);
}
size_t capacity(const queue &q)
{
    return capacity(q.insertion); // actually we could do better
}
bool insert(queue &q, const item &i)
{
    bool result = size(q) < capacity(q); // not full yet
    if (result)
    {
        push(q.insertion, i);
    }
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = size(q) > 0; // not empty
    if (result)
    {
        if (!pop(q.removal, i))
        {
            while (pop(q.insertion, i))
            {
                push(q.removal, i);
            }
            pop(q.removal, i);
        }
    }
    return result;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", insertion stack: ";
    print(q.insertion, out, false);
    out << ", removal stack: ";
    print(q.removal, out, false);
    out << " }";
    if (newLine)
    {
        out << endl;
    }
}
