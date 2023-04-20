/**
 * Purpose: basic sorting algorithms: selection sort derived step by step
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
bool isOrdered(const type a[], int end, int begin = 0);                               // function to check sorting

// sorting functions
void shuffle(type a[], int end, int begin = 0);       // function to start with
void sortIterative(type a[], int end, int begin = 0); // full sorting, iterative
void sortRecursive(type a[], int end, int begin = 0); // full sorting, recursive
void sortOptimized(type a[], int end, int begin = 0); // full sorting, iterative + swap optimization

const int NUM_ALGORITHMS = 4; // # of algorithms

// basic sorting test
void test(type v[], int dim, int which);

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    int dim = 10;
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

    cout << endl
         << "Test with worst case array for optimized algorithm" << endl;
    reverse(a + 1, dim - 1);
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

/// @brief Mescolamento degli elementi da 0 a end escluso: [0, end)
/// @param a     l'array con i valori da mescolare
/// @param toBeShuffled   fine (esclusa) della scansione: a[toBeShuffled] non viene elaborato
void shuffleAll(type a[], int toBeShuffled)
{
    while (toBeShuffled > 1) // at least two elements
    {
        int random = rand() % toBeShuffled;  // pick a random element
        --toBeShuffled;                      // one less
        scambio(a[random], a[toBeShuffled]); // swap
    }
}

/// @brief Mescolamento degli elementi da begin a end escluso: [begin, end)
/// @param a     l'array con i valori da mescolare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void shuffle(type a[], int end, int begin /* = 0 */)
{
    // the simple way: adapt parameters to shuffleAll
    // shuffleAll(a + begin, end - begin);
    // but we need this to start with
    while (end - begin > 1) // at least two elements
    {
        int random = begin + rand() % (end - begin); // pick a random element in [begin, end)
        --end;                                       // one less to shuffle
        scambio(a[random], a[end]);                  // swap with last element
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details This is the first complete step: the idea is simply
/// to pick the best (worst?) element instead of one at random
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortIterative(type a[], int end, int begin /* = 0 */)
{
    while (end - begin > 1) // at least two elements
    {
        --end;                          // place for best element
        for (int i = end; i-- > begin;) // scan backward
        {
            if (lessThan(a[end], a[i]))
            {
                scambio(a[end], a[i]); // new best element
            }
        }
        // here last position is best element,
        // but the others might still be out of order !!!
    }
    // here every element is ordered
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details This is the same as sortIterative, with tail recursion
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortRecursive(type a[], int end, int begin /* = 0 */)
{
    if (end - begin > 1) // at least two element
    {
        --end;                          // place for best element
        for (int i = end; i-- > begin;) // scan backward
        {
            if (lessThan(a[end], a[i]))
            {
                scambio(a[end], a[i]); // new best element
            }
        }
        // here last position is best element,
        // but the others might still be out of order !!!
        sortRecursive(a, end, begin); // Let's sort the rest
    }
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void sortOptimized(type a[], int end, int begin /* = 0 */)
{
    while (end - begin > 1) // at least two elements
    {
        int best = --end;               // place for best element
        for (int i = end; i-- > begin;) // scan backward
        {
            if (lessThan(a[best], a[i]))
            {
                best = i; // new best element
            }
        }
        if (best != end)
        {
            scambio(a[end], a[best]); // swap only if needed
        }
    }
}

void sortIt(type v[], int dim, int which)
{
    switch (which)
    {
    case 1:
        cout << "After shuffle: ";
        shuffle(v, dim);
        break;
    case 2:
        cout << "After sortIterative: ";
        sortIterative(v, dim);
        break;
    case 3:
        cout << "After sortRecursive: ";
        sortRecursive(v, dim);
        break;
    case 4:
        cout << "After sortOptimized: ";
        sortOptimized(v, dim);
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
