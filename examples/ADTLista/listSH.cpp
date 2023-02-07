/**
 * Purpose: basic list implementation with a singly linked hashed list
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    item must be defined as a valid data type (e.g. with using item = int;)
 */

// common guard to avoid multiple inclusions
#ifndef LISTASH_CPP
#define LISTASH_CPP

#include <cstddef>

#define NONE (SIZE_MAX)

// complete type
struct list
{
    item *info{nullptr};   // actual elements
    size_t *next{nullptr}; // next indexes array (will be used for free list also)
    size_t front{NONE};    // index of first item
    size_t back{NONE};     // index of last item
    size_t free{NONE};     // index of first free slot in data array
    size_t capacity{0};    // capacity of the arrays
    size_t size{0};        // size for efficiency
};

/*
 * CAVEAT
 * With this definition of list data type
 * data are NOT part of the struct !!!
 *     size of struct:
 *           sizeof(data) i.e. sizeof(item *) usually 4B or 8B, independent of capacity!
 *         + sizeof(next) i.e. sizeof(size_t *) usually 4B or 8B, independent of capacity!
 *         + 5 x sizeof(size_t) usually 4B or 8B, independent of capacity!
 * If the struct is copied, the addresses of the data, next and prev indexes are copied
 * but the actual data/indexes are shared between the copies !!!!
 */

// will be used by insertions, and possibly to extend/reduce/free allocated memory
bool extendCapacity(list &, size_t);
#define START_CAPACITY 2

// basic operations
// number of elements
size_t size(const list &l)
{
    return l.size;
}
// maximum number of elements
size_t capacity(const list &l)
{
    return l.capacity;
}
// insert at front
bool insertFront(list &l, const item &i)
{
    if (size(l) == l.capacity)
    {
        if (extendCapacity(l, l.capacity == 0 ? START_CAPACITY : l.capacity * 2))
        {
            return insertFront(l, i);
        }
    }
    else
    {
        // get the first free slot
        size_t inserted = l.free;
        l.free = l.next[l.free];
        l.info[inserted] = i;       // insert data
        l.next[inserted] = l.front; // link to next
        // update list
        l.front = inserted; // new front
        if (l.back == NONE)
        {
            l.back = inserted; // new back also
        }
        l.size++; // one element more
        return true;
    }
    return false;
}
// insert at back)
bool insertBack(list &l, const item &i)
{
    if (size(l) == l.capacity)
    {
        if (extendCapacity(l, l.capacity == 0 ? START_CAPACITY : l.capacity * 2))
        {
            return insertBack(l, i);
        }
    }
    else
    {
        // get the first free slot
        size_t inserted = l.free;
        l.free = l.next[l.free];
        l.info[inserted] = i;    // insert data
        l.next[inserted] = NONE; // no next
        // update old back links (if any) and list
        if (l.back == NONE)
        {
            l.back = l.front = inserted; // new front and new back
        }
        else
        {
            l.back = l.next[l.back] = inserted; // new next and new back
        }
        l.size++; // one element more
        return true;
    }
    return false;
}
// remove from front
bool removeFront(list &l, item &i)
{
    // if list not empty
    if (size(l) > 0)
    {
        // remember removed slot
        size_t removed = l.front;
        // get data
        i = l.info[removed];
        // update new front links (if any) and list
        if (l.next[removed] == NONE)
        {
            l.front = l.back = NONE; // new back and new front (empty list)
        }
        else
        {
            l.front = l.next[removed]; // new front
        }
        l.size--; // one element less
        // update free slots list
        l.next[removed] = l.free;
        l.free = removed;
        return true;
    }
    return false;
}
// remove from back)
bool removeBack(list &l, item &i)
{
    // if list not empty
    if (size(l) > 0)
    {
        // remember removed slot
        size_t removed = l.back;
        // get data
        i = l.info[removed];
        // update new back links (if any) and list
        if (l.front == removed)
        {
            l.back = l.front = NONE; // new front and new back (empty list)
        }
        else
        {
            // must find the new back
            l.back = l.front;
            while (l.next[l.back] != removed)
            {
                l.back = l.next[l.back];
            }
            l.next[l.back] = NONE; // no next
        }
        l.size--; // one element less
        // update free slots list
        l.next[removed] = l.free;
        l.free = removed;
        return true;
    }
    return false;
}
// insert at position (0 = front, size = back)
bool insertAt(list &l, const item &i, size_t p)
{

    if (p < 0 || p > size(l)) // check argument position
    {
        return false;
    }
    else if (p == 0) // check special cases: front

    {
        return insertFront(l, i);
    }
    else if (p == size(l)) // check special cases: back
    {
        return insertBack(l, i);
    }
    else // general case: between two real nodes!!!
    {
        if (size(l) == l.capacity)
        {
            if (extendCapacity(l, l.capacity == 0 ? START_CAPACITY : l.capacity * 2))
            {
                return insertAt(l, i, p);
            }
        }
        else
        {
            // could be optimized (backward if p > size(l) / 2)
            // search index before insertion point
            size_t before = l.front;
            while (--p > 0)
            {
                // move p - 1 times
                before = l.next[before];
            }
            // get the first free slot
            size_t inserted = l.free;
            l.free = l.next[l.free];
            l.info[inserted] = i;              // insert data
            l.next[inserted] = l.next[before]; // new next
            // update contiguos links
            l.next[before] = inserted; // new next
            // update list
            l.size++; // one element more
            return true;
        }
    }
    return false;
}
// remove from position (0 = front, size - 1 = back)
bool removeFrom(list &l, item &i, size_t p)
{
    if (p < 0 || p >= size(l)) // check argument position
    {
        return false;
    }
    if (p == 0) // check special cases: front
    {
        return removeFront(l, i);
    }
    else if (p == size(l) - 1) // check special cases: back
    {
        return removeBack(l, i);
    }
    else // general case: between two real nodes!!!
    {
        // could be optimized (backward if p > size(l) / 2)
        // search index before removal point
        size_t before = l.front;
        while (--p > 0)
        {
            // move p - 1 times
            before = l.next[before];
        }
        // remember removed slot
        size_t removed = l.next[before];
        // get data
        i = l.info[removed];
        // update contiguos links
        l.next[before] = l.next[removed]; // new next
        // update list
        l.size--; // one element less
        // update free slots list
        l.next[removed] = l.free;
        l.free = removed;
        return true;
    }
    return false;
}

// insert in order (requires < to be defined)
bool insertOrdered(list &l, const item &i)
{
    if (l.front == NONE) // check special cases: empty list
    {
        return insertFront(l, i);
    }
    else if (i < l.info[l.front]) // check special cases: least item
    {
        return insertFront(l, i);
    }
    else if (l.info[l.back] <= i) // check special cases: greatest item
    {
        return insertBack(l, i);
    }
    else // general case: between two real nodes!!!
    {
        if (size(l) == l.capacity)
        {
            if (extendCapacity(l, l.capacity == 0 ? START_CAPACITY : l.capacity * 2))
            {
                return insertOrdered(l, i);
            }
        }
        else
        {
            // search index before insertion point
            // such that [ data[before] <= i ] && i < data[next[before]]
            size_t before = l.front;
            while (!(i < l.info[l.next[before]]))
            {
                before = l.next[before];
            }
            // get the first free slot
            size_t inserted = l.free;
            l.free = l.next[l.free];
            l.info[inserted] = i;              // insert data
            l.next[inserted] = l.next[before]; // new next
            // update contiguos links
            l.next[before] = inserted; // new next
            // update list
            l.size++; // one element more
            return true;
        }
    }
    return false;
}

// empty the list (i.e removes all elements)
void clear(list &l)
{
    // free dynamic memory ...
    free(l.info);
    l.info = nullptr; // just to be on the safe side
    free(l.next);
    l.next = nullptr; // just to be on the safe side
    l.capacity = 0;
    // and empty the list
    l.size = 0;
    l.front = l.back = l.free = NONE;
}
// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const list &l, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Lista{ ";
    out << size(l) << "/" << capacity(l) << ", front :";
    size_t current = l.front;
    while (current != NONE)
    {
        out << " " << l.info[current];
        current = l.next[current];
    }
    out << " : back }";
    if (newLine)
    {
        out << endl;
    }
}

bool extendCapacity(list &l, size_t newCapacity)
{
    // resize the data array to newCapacity
    item *pd = (item *)realloc(l.info, newCapacity * sizeof(l.info[0]));
    if (pd != nullptr)
    {
        // successfully extended!!!
        // resize the next indexes array to newCapacity
        size_t *pn = (size_t *)realloc(l.next, newCapacity * sizeof(l.next[0]));
        if (pn != nullptr)
        {
            // successfully extended!!!
            // successfully extended!!!
            // that is successfully extended the list
            l.info = pd; // might have changed !!!
            l.next = pn; // might have changed !!!
            // setup new indexes
            for (size_t i = l.capacity; i < newCapacity; ++i)
            {
                l.next[i] = i + 1;
            }
            l.next[newCapacity - 1] = SIZE_MAX;
            l.free = l.capacity;
            l.capacity = newCapacity;
            return true;
        }
        else
        {
            // return to previous capacity
            // resize the data array to to old capacity
            l.info = (item *)realloc(l.info, l.capacity * sizeof(l.info[0]));
        }
    }
    return false;
}

#endif