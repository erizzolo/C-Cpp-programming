/**
 * Purpose: basic list implementation with a doubly linked list
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    item must be defined as a valid data type (e.g. with using item = int;)
 */

// common guard to avoid multiple inclusions
#ifndef LISTADL_CPP
#define LISTADL_CPP

#include <cstddef>

struct node
{
    item info;           // one and only one item per node
    node *next{nullptr}; // link to next node
    node *prev{nullptr}; // link to previous node
};

// complete type
struct list
{
    node *front{nullptr}; // first node in the list
    node *back{nullptr};  // last node in the list
    size_t size{0};       // size for efficiency
};

/*
 * CAVEAT
 * With this definition of list data type
 * data are NOT part of the struct !!!
 *     size of struct:
 *           sizeof(front) i.e. sizeof(node *) usually 4B or 8B, independent of capacity!
 *         + sizeof(back) i.e. sizeof(node *) usually 4B or 8B, independent of capacity!
 *         + sizeof(size_t)
 * If the struct is copied, the addresses of the front & back nodes are copied
 * but the actual nodes/data are shared between the copies !!!!
 */

// basic operations
// number of elements
size_t size(const list &l)
{
    return l.size;
    // size_t result = 0;
    // node *current = l.front;
    // while (current != nullptr)
    // {
    //     result++;                // count current node
    //     current = current->next; // go to next node if any
    // }
    // return result;
}
// maximum number of elements
size_t capacity(const list &l)
{
    return SIZE_MAX; // hopefully it won't be reached
}

// insert at front
bool insertFront(list &l, const item &i)
{
    // create a new node for insertion
    node *inserted = new (nothrow) node;
    // check success
    if (inserted != nullptr)
    {
        // setup of the new node
        inserted->info = i;       // insert data
        inserted->next = l.front; // link to next
        // inserted->prev = nullptr; // not needed: default value
        // update old front node (if any) and list
        if (l.front == nullptr)
        {
            l.front = l.back = inserted; // new back and new front
        }
        else
        {
            l.front = l.front->prev = inserted; // new previous and new front
        }
        l.size++; // one element more
        return true;
    }
    return false;
}
// insert at back)
bool insertBack(list &l, const item &i)
{
    // create a new node for insertion
    node *inserted = new (nothrow) node;
    // check success
    if (inserted != nullptr)
    {
        // setup of the new node
        inserted->info = i; // insert data
        // inserted->next = nullptr; // not needed: default value
        inserted->prev = l.back; // link to previous
        // update old back node (if any) and list
        if (l.back == nullptr)
        {
            l.back = l.front = inserted; // new front and new back
        }
        else
        {
            l.back = l.back->next = inserted; // new next and new back
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
    if (l.front != nullptr)
    {
        // remember removed node
        node *removed = l.front;
        // get data
        i = removed->info;
        // update new front node (if any) and list
        if (removed->next == nullptr)
        {
            l.front = l.back = nullptr; // new back and new front (empty list)
        }
        else
        {
            l.front = removed->next; // new front
            l.front->prev = nullptr; // new previous
        }
        l.size--;       // one element less
        delete removed; // delete unused node: no memory leakage, please
        return true;
    }
    return false;
}
// remove from back)
bool removeBack(list &l, item &i)
{
    // if list not empty
    if (l.back != nullptr)
    {
        // remember removed node
        node *removed = l.back;
        // get data
        i = removed->info;
        // update new back node (if any) and list
        if (removed->prev == nullptr)
        {
            l.back = l.front = nullptr; // new front and new back (empty list)
        }
        else
        {
            l.back = removed->prev; // new back
            l.back->next = nullptr; // new next
        }
        l.size--;       // one element less
        delete removed; // delete unused node: no memory leakage, please
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
        // create a new node for insertion
        node *inserted = new (nothrow) node;
        // check success
        if (inserted != nullptr)
        {
            // could be optimized (backward if p > size(l) / 2)
            // search node before insertion point
            node *before = l.front;
            while (--p > 0)
            {
                // move p - 1 times
                before = before->next;
            }
            // setup of the new node
            inserted->info = i;            // insert data
            inserted->next = before->next; // link to next
            inserted->prev = before;       // link to previous
            // update contiguous nodes
            before->next = inserted;         // new next
            inserted->next->prev = inserted; // new previous
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
    else if (p == 0) // check special cases: front
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
        // search node at removal point
        node *removed = l.front;
        while (p-- > 0)
        {
            // move p times
            removed = removed->next;
        }
        // get data
        i = removed->info;
        // update contiguous nodes
        removed->prev->next = removed->next; // new next
        removed->next->prev = removed->prev; // new previous
        // update list
        l.size--;       // one element less
        delete removed; // delete unused node: no memory leakage, please
        return true;
    }
    return false;
}

// insert in order (requires < to be defined)
bool insertOrdered(list &l, const item &i)
{

    if (l.front == nullptr) // check special cases: empty list
    {
        return insertFront(l, i);
    }
    else if (i < l.front->info) // check special cases: least item
    {
        return insertFront(l, i);
    }
    else if (l.back->info <= i) // check special cases: greatest item
    {
        return insertBack(l, i);
    }
    else // general case: between two real nodes!!!
    {
        // create a new node for insertion
        node *inserted = new (nothrow) node;
        // check success
        if (inserted != nullptr)
        {
            // search node before insertion point
            // such that [ before->info <= i ] && i < before->next->info
            node *before = l.front;
            while (!(i < before->next->info))
            {
                before = before->next;
            }
            // setup of the new node
            inserted->info = i;            // insert data
            inserted->next = before->next; // link to next
            inserted->prev = before;       // link to previous
            // update contiguous nodes
            before->next = inserted;         // new next
            inserted->next->prev = inserted; // new previous
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
    // // the idiot way
    // item i;
    // while (removeFront(l, i))
    //     ;   // do nothing, just repeat
    // the clever way
    while (l.back != nullptr)
    {

        node *removed = l.back; // remember removed node
        l.back = removed->prev; // new back
        delete removed;         // delete unused node: no memory leakage, please
    }
    l.front = nullptr;
    l.size = 0;
}

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const list &l, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Lista{ ";
    out << size(l) << "/" << capacity(l) << ", front :";
    node *current = l.front;
    while (current != nullptr)
    {
        out << " " << current->info;
        current = current->next;
    }
    out << " : back }";
    if (newLine)
    {
        out << endl;
    }
}

#endif