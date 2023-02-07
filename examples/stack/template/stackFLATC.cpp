#ifndef STACKFLAT_CPP
#define STACKFLAT_CPP

/**
 * Purpose: basic template stack implementation based on a fixed length array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:    La struct stack (e le relative operazioni) rappresentano un modello
 *          che deve essere specializzato nell'uso a seconda delle necessità.
 *          Le operazioni sono interne alla struct:
 *          - ciò semplifica la scrittura del codice (e non solo);
 *          - la sintassi è diversa: anziché f(s, ...) si usa s.f(...).
 *          Ciò che è interno alla struct viene identificato come:
 *          - private, cioè accessibile solo dal codice all'interno di essa;
 *          - public, cioè accessibile anche dal codice esterno.
 *          Ciò protegge da utilizzi errati !!!
 *          (Per default in una struct tutto è public, in una class tutto è private)
 *          I parametri di questo modello sono:
 *          - T, il tipo di dati degli elementi gestiti dallo stack
 *            (che deve essere un tipo di dati valido, ad es. int, double, ...);
 *          - CAPACITY, il numero massimo di elementi gestibili
 *            (che deve essere un intero non negativo e vale 10 come default).
 *          Per l'uso si dovrà specializzare il modello (template) fornendo dei
 *          valori validi per T e (opzionalmente) per CAPACITY, ad es.:
 *              stack<double, 30> s1;       // crea uno stack di 30 double
 *              stack<int> s2;              // crea uno stack di 10 int
 *              stack<stack<char>, 2> s3;   // crea uno stack di 2 stack di 10 char
 */

#include <iostream>

// definition of stack data type
template <typename T, size_t CAPACITY = 10>
class stack
{
private:
    T data[CAPACITY];  // the actual data
    size_t theSize{0}; // actual size of the stack (number of elements)
public:
    // basic operations
    size_t size() const
    {
        return theSize;
    }

    size_t capacity() const
    {
        return CAPACITY;
    }

    bool push(const T &i)
    {
        bool result = size() < capacity(); // not full yet
        if (result)
        {
            data[size()] = i; // insert into bottom empty position
            theSize++;        // one element more
        }
        return result;
    }

    bool pop(T &i)
    {
        bool result = size() > 0; // not empty
        if (result)
        {
            theSize--;        // one element less
            i = data[size()]; // extract from top non-empty position
        }
        return result;
    }

    // for debug purposes
    // almost implementation independent
    void print(std::ostream &out = cout, bool newLine = true)
    {
        out << "Stack{ ";
        out << size() << "/" << capacity() << ", bottom :";
        for (size_t i = 0; i < size(); i++)
        {
            // show elements from bottom to top
            cout << " " << data[i]; // implementation dependent
        }
        out << " : top}";
        if (newLine)
        {
            out << endl;
        }
    }
};

#endif