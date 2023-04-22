/**
 * Purpose: basic sorting algorithms: bubble sort derived step by step
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/04/12
 * Note:
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

const bool DEBUG = true;
using namespace std;
using type = int;

// global operation counters
size_t comparisons = 0;                 // n° of comparisons
size_t swaps = 0;                       // n° of swaps
void showOperations(bool reset = true); // utility to show and maybe reset counters

// comparison function lessThan(lhs, rhs) = lhs < rhs
bool lessThan(const type &lhs, const type &rhs, bool count = true);
bool lessThan(const type &lhs, const type &rhs, bool count /* = true */)
{
    if (count) // only in sorting algorithms
        ++comparisons;
    return lhs < rhs;
}

// swap function scambio(lhs, rhs)
void scambio(type &lhs, type &rhs);
void scambio(type &lhs, type &rhs)
{
    ++swaps;
    // type temp = lhs; lhs = rhs; rhs = temp;
    swap(lhs, rhs);
}

// utility functions
void JSON(const type a[], int end, int begin = 0, ostream &out = cout);               // output su out in formato JSON
void iota(type a[], type value, int end, int begin = 0);                              // fill with increasing values
void reverse(type a[], int end, int begin = 0);                                       // rovescia l'ordine degli elementi
void fillRandom(type a[], int end, int begin = 0, type min = 0, type max = RAND_MAX); // a[i] = random in [min, max]
void copia(const type a[], type c[], int end, int begin = 0);                         // copy (a range of) an array

// sorting functions
bool isOrdered(const type a[], int end, int begin = 0);   // function to start with
void sortFirst(type a[], int end, int begin = 0);         // first step
void sortRecursive(type a[], int end, int begin = 0);     // full sorting, recursive
void sortIterative(type a[], int end, int begin = 0);     // full sorting, iterative
void sortOptimizedBool(type a[], int end, int begin = 0); // full sorting, iterative + boolean optimization
void sortOptimizedLast(type a[], int end, int begin = 0); // full sorting, iterative + optimization on end
void sortOptimizedBoth(type a[], int end, int begin = 0); // full sorting, iterative + optimization on end and begin

const int NUM_ALGORITHMS = 6; // # of algorithms

// basic sorting test
void test(type v[], int dim, int which);

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    int dim = 20;
    type v[dim], a[dim];

    cout << "Test with random array" << endl;
    fillRandom(a, dim, 0, 0, dim * 2); // probably with duplicates
    JSON(a, dim);
    cout << " ordinato: " << (isOrdered(a, dim) ? "si' " : "no ");
    showOperations();
    for (int algo = 1; algo <= NUM_ALGORITHMS; ++algo)
    {
        copia(a, v, dim); // make a copy
        test(v, dim, algo);
    }

    cout << endl
         << "Test with best case array" << endl;
    iota(a, 0, dim);
    JSON(a, dim);
    cout << " ordinato: " << (isOrdered(a, dim) ? "si' " : "no ");
    showOperations();
    for (int algo = 1; algo <= NUM_ALGORITHMS; ++algo)
    {
        copia(a, v, dim); // make a copy
        test(v, dim, algo);
    }

    cout << endl
         << "Test with worst case array" << endl;
    reverse(a, dim);
    JSON(a, dim);
    cout << " ordinato: " << (isOrdered(a, dim) ? "si' " : "no ");
    showOperations();
    for (int algo = 1; algo <= NUM_ALGORITHMS; ++algo)
    {
        copia(a, v, dim); // make a copy
        test(v, dim, algo);
    }

    return 0;
}

/// @brief Verifica ordinamento (crescente) elementi da begin a end escluso: [begin, end)
/// @param a     l'array con i valori di cui verificare l'ordinamento
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return      true se gli elementi sono ordinati, false altrimenti
bool isOrdered(const type a[], int end, int begin /* = 0 */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        if (lessThan(a[i], a[i - 1], false)) // something's wrong here
            return false;
    }
    return true;
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details This is the first incomplete step: the idea is simply
/// trying to fix an anomaly when we find it
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortFirst(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        if (lessThan(a[i], a[i - 1]))
        {
            scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
        }
    }
    // here last position is maximum element,
    // but the others might still be out of order !!!
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details This is the first complete sorting algorithm, recursive
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortRecursive(type a[], int end, int begin /* = 0 */)
{
    if (end - begin > 1) // at least two element
    {
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessThan(a[i], a[i - 1]))
            {
                scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
            }
        }
        // here last position is maximum element,
        // but the others might still be out of order !!!
        sortRecursive(a, end - 1, begin); // Let's sort the rest
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details This is the same algorithm but we changed the tail recursion into an iteration
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortIterative(type a[], int end, int begin /* = 0 */)
{
    // if becomes a while ...
    while (end - begin > 1) // at least two element
    {
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessThan(a[i], a[i - 1]))
            {
                scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
            }
        }
        --end; // Let's start again with end decreased
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with boolean optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortOptimizedBool(type a[], int end, int begin /* = 0 */)
{
    bool swapped = true;               // need true to enter the while
    while (end - begin > 1 && swapped) // at least two element
    {
        swapped = false; // no swaps so far
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessThan(a[i], a[i - 1]))
            {
                scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
                swapped = true;          // at least one swap
            }
        }
        --end; // Let's start again with end decreased
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with last swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortOptimizedLast(type a[], int end, int begin /* = 0 */)
{
    while (end - begin > 1) // at least two element
    {
        int lastSwap = 0;
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessThan(a[i], a[i - 1]))
            {
                scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
                lastSwap = i;            // remember last swap
            }
        }
        end = lastSwap; // Let's start again with end decreased
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with last and first swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortOptimizedBoth(type a[], int end, int begin /* = 0 */)
{
    int limit = begin;      // remember array start limit
    while (end - begin > 1) // at least two element
    {
        int lastSwap = 0, firstChanged = end;
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessThan(a[i], a[i - 1]))
            {
                scambio(a[i], a[i - 1]); // something's wrong here: let's fix it
                lastSwap = i;            // remember last swap
                if (firstChanged > i)
                {
                    firstChanged = i - 1; // remember first element changed
                }
            }
        }
        end = lastSwap;                                                    // Let's start again with end decreased
        begin = firstChanged == limit ? firstChanged : (firstChanged - 1); // starting with the first possibly changed test
    }
}

void sortIt(type v[], int dim, int which)
{
    switch (which)
    {
    case 1:
        cout << "After sortFirst: ";
        sortFirst(v, dim);
        break;
    case 2:
        cout << "After sortRecursive: ";
        sortRecursive(v, dim);
        break;
    case 3:
        cout << "After sortIterative: ";
        sortIterative(v, dim);
        break;
    case 4:
        cout << "After sortOptimizedBool: ";
        sortOptimizedBool(v, dim);
        break;
    case 5:
        cout << "After sortOptimizedLast: ";
        sortOptimizedLast(v, dim);
        break;
    case 6:
        cout << "After sortOptimizedBoth: ";
        sortOptimizedBoth(v, dim);
        break;
    }
    JSON(v, dim);
    cout << " ordinato: " << (isOrdered(v, dim) ? "si', " : "no, ");
    showOperations();
}

void test(type v[], int dim, int which)
{
    sortIt(v, dim, which);
}

/// @brief Output su out in formato JSON da begin a end escluso: [begin, end)
/// @param a     the array to output
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param out   the output stream to be used
void JSON(const type a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
{
    out << "[ ";
    for (int i = begin; i < end; ++i)
    {
        if (i != begin)
        {
            out << ", ";
        }
        out << a[i];
    }
    out << " ]";
}

/// @brief Imposta gli elementi in [begin, end) con valori crescenti a partire da value
/// @param a     the array to change
/// @param value the starting value, incremented with ++value
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void iota(type a[], type value, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = value;
        ++value;
    }
}

/// @brief Rovescia gli elementi da begin a end escluso: [begin, end)
/// @param a     l'array con i valori da rovesciare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void reverse(type a[], int end, int begin /* = 0 */)
{
    for (int inf = begin, sup = end - 1; inf < sup; inf++, sup--)
    {
        swap(a[inf], a[sup]);
    }
}

/// #brief Inizializzazione con valore casuale degli elementi da begin a end escluso: [begin, end)
/// @param a     l'array da inizializzare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param min   valore casuale minimo
/// @param max   valore casuale massimo
void fillRandom(type a[], int end, int begin /* = 0 */, type min /* = 0 */, type max /* = RAND_MAX */)
{
    for (int i = begin; i < end; i++)
    {
        a[i] = min + rand() % (max - min + 1);
    }
}
/// #brief Copia gli elementi da begin a end escluso: [begin, end)
/// @param a     l'array da cui copiare
/// @param c     l'array da inizializzare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void copia(const type a[], type c[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; i++)
    {
        c[i] = a[i];
    }
}

/// @brief Shows operation counters if DEBUG
/// @param reset whether to reset counters or not
void showOperations(bool reset /* = true */)
{
    if (DEBUG)
    {
        cout << "comparisons: " << comparisons << ", swaps: " << swaps << endl;
    }
    if (reset)
    {
        comparisons = swaps = 0;
    }
}
