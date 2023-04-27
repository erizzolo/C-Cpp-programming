/**
 * Purpose: basic sorting algorithms: comparison
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/04/12
 * Note:
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>
#include <algorithm>

const bool DEBUG = true;
using namespace std;
using type = int;

// global operation counters
size_t comparisons = 0;                 // n° of comparisons
size_t swaps = 0;                       // n° of swaps
void showOperations(bool reset = true); // utility to show and maybe reset counters

// comparison function lessThan(lhs, rhs) = lhs < rhs
bool lessThan(const type &lhs, const type &rhs);
bool lessThan(const type &lhs, const type &rhs)
{
    ++comparisons;
    return lhs < rhs;
}

// for qsort
int intLessThan(const void *l, const void *r)
{
    const type *lhs = (const type *)l;
    const type *rhs = (const type *)r;
    ++comparisons;
    if (*lhs < *rhs)
        return -1;
    if (*lhs > *rhs)
        return 1;
    return 0;
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
void fillRandom(type a[], int end, int begin = 0, type min = 0, type max = RAND_MAX); // a[i] = random in [min, max]
void copia(const type a[], type c[], int end, int begin = 0);                         // copy (a range of) an array

// sorting functions
bool isOrdered(const type a[], int end, int begin = 0); // function to start with
void bubbleSort(type a[], int end, int begin = 0);
void selectionSort(type a[], int end, int begin = 0);
void quickSort(type a[], int end, int begin = 0);
void qSort(type a[], int end, int begin = 0);
void stdSort(type a[], int end, int begin = 0);
void stableSort(type a[], int end, int begin = 0);

const int NUM_ALGORITHMS = 6; // # of algorithms

// basic sorting test
void test(type v[], int dim, int which, void sort(type a[], int end, int begin));

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    int dim = 20000;
    type *a = new type[dim];
    cout << "Test with random array" << endl;
    fillRandom(a, dim, 0, 0, dim * 2); // probably with duplicates
    showOperations();
    cout << endl
         << "Bubblesort" << endl;
    test(a, dim, 1, bubbleSort);
    cout << endl
         << "Selectionsort" << endl;
    test(a, dim, 1, selectionSort);
    cout << endl
         << "Quicksort" << endl;
    test(a, dim, 1, quickSort);
    cout << endl
         << "qsort" << endl;
    test(a, dim, 1, qSort);
    cout << endl
         << "std::sort" << endl;
    test(a, dim, 1, stdSort);
    cout << endl
         << "std::stable_sort" << endl;
    test(a, dim, 1, stableSort);

    delete[] a;
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
        if (lessThan(a[i], a[i - 1])) // something's wrong here
            return false;
    }
    return true;
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with last and first swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void bubbleSort(type a[], int end, int begin /* = 0 */)
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

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void selectionSort(type a[], int end, int begin /* = 0 */)
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

void test(type a[], int dim, int which, void sort(type a[], int end, int begin))
{
    type *v = new type[dim];
    copia(a, v, dim); // make a copy
    // record start time
    auto start = std::chrono::high_resolution_clock::now();
    // do some work
    sort(v, dim, 0);
    // record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to order " << dim << " types : " << diff.count() << " s" << endl;
    showOperations();
    cout << " ordinato: " << (isOrdered(v, dim) ? "si' " : "no ");
    comparisons = swaps = 0;
    delete[] v;
}

/// @brief Partizionamento (crescente) degli elementi da begin a end escluso: [begin, end)
/// @details left tale che: a[i] < a[left] per i < left, a[i] >= a[left] per i >= left
/// @param a     l'array con i valori da partizionare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return left: l'indice dell'elemento pivot
size_t partition(type a[], int end, int begin = 0)
{
    type pivot = a[end - 1]; // simple pivot selection, non optimal
    size_t left = begin, right = end - 2;
    do
    {
        while (lessThan(a[left], pivot)) // first not less than pivot
            left++;
        while (left < right && !lessThan(a[right], pivot)) // last less than pivot
            right--;
        if (left < right)
        {
            scambio(a[left], a[right]);
        }
    } while (left < right);
    scambio(a[left], a[end - 1]);
    return left;
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details quicksort with simple pivot selection
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param lessBy la funzione di confronto, per default lessThan
// void quickSort(type a[], int end, int begin /* = 0 */, compare lessBy /* = lessThan */)
void quickSort(type a[], int end, int begin /* = 0 */)
{
    // if (DEBUG)
    //     cout << "quickSort [" << begin << ", " << end << ")" << endl;
    if (end - begin > 1) // at least two element
    {
        // partition
        size_t left = partition(a, end, begin);
        // recurse lower part
        quickSort(a, left, begin);
        // recurse higher part
        quickSort(a, end, left + 1);
    }
}

/// @brief sort with qsort, adapting parameters
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void qSort(type a[], int end, int begin /* = 0 */)
{
    qsort(a, end - begin, sizeof(type), intLessThan);
}

/// @brief sort with std::sort, adapting parameters
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void stdSort(type a[], int end, int begin /* = 0 */)
{
    std::sort(a + begin, a + end, lessThan );
}

/// @brief sort with std::stable_sort, adapting parameters
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void stableSort(type a[], int end, int begin /* = 0 */)
{
    std::stable_sort(a + begin, a + end, lessThan);
}
