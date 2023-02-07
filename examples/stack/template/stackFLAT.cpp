#ifndef STACKFLAT_CPP
#define STACKFLAT_CPP

/**
 * Purpose: basic template stack implementation based on a fixed length array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:    La struct stack (e le relative operazioni) rappresentano un modello
 *          che deve essere specializzato nell'uso a seconda delle necessità.
 *          I parametri di questo modello sono:
 *          - T, il tipo di dati degli elementi gestiti dallo stack
 *            (che deve essere un tipo di dati valido, ad es. int, double, ...)
 *          - CAPACITY, il numero massimo di elementi gestibili
 *            (che deve essere un intero non negativo e vale 10 come default)
 *          Per l'uso si dovrà specializzare il modello (template) fornendo dei
 *          valori validi per T e (opzionalmente) per CAPACITY, ad es.:
 *              stack<double, 30> s1;       // crea uno stack di 30 double
 *              stack<int> s2;              // crea uno stack di 10 int
 *              stack<stack<char>, 2> s3;   // crea uno stack di 2 stack di 10 char
 */

#include <iostream>

// definition of stack data type
template <typename T, size_t CAPACITY = 10>
struct stack
{
    T data[CAPACITY]; // the actual data
    size_t size{0};   // actual size of the stack (number of elements)
};

// basic operations
template <typename T, size_t CAPACITY>
size_t size(const stack<T, CAPACITY> &s)
{
    return s.size;
}

template <typename T, size_t CAPACITY>
size_t capacity(const stack<T, CAPACITY> &s)
{
    return CAPACITY;
}

template <typename T, size_t CAPACITY>
bool push(stack<T, CAPACITY> &s, const T& i)
{
    bool result = size(s) < capacity(s); // not full yet
    if (result)
    {
        s.data[size(s)] = i; // insert into bottom empty position
        s.size++;            // one element more
    }
    return result;
}
template <typename T, size_t CAPACITY>
bool pop(stack<T, CAPACITY> &s, T &i)
{
    bool result = size(s) > 0; // not empty
    if (result)
    {
        s.size--;            // one element less
        i = s.data[size(s)]; // extract from top non-empty position
    }
    return result;
}

// for debug purposes
// almost implementation independent
template <typename T, size_t CAPACITY>
void print(const stack<T, CAPACITY> &s, std::ostream &out = cout, bool newLine = true)
{
    out << "Stack{ ";
    out << size(s) << "/" << capacity(s) << ", bottom :";
    for (size_t i = 0; i < size(s); i++)
    {
        // show elements from bottom to top
        cout << " " << s.data[i]; // implementation dependent
    }
    out << " : top}";
    if (newLine)
    {
        out << endl;
    }
}

#endif