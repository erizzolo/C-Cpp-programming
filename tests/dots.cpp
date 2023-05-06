/**
 * Purpose: bubble sort with array of struct and different comparison functions
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/04/28
 * Note:    Adapted to point structure
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "geometry.h"

using namespace std;
using type = punto;

const bool DEBUG = true;

// overload dell'operatore << per output in showPoints format
ostream &operator<<(ostream &os, const punto &p)
{
    print(p, os);
    return os;
}

using compare = bool (*)(const type &lhs, const type &rhs); // definition of comparison function type

bool lessDistantFromOrigin(const type &lhs, const type &rhs)
{
    punto ORIGINE = getPunto(0, 0);
    return distance(lhs, ORIGINE) < distance(rhs, ORIGINE);
}

int quadrant(const type &p)
{
    if (p.x >= 0 && p.y >= 0)
        return 1;
    if (p.x < 0 && p.y >= 0)
        return 2;
    if (p.x < 0 && p.y < 0)
        return 3;
    return 4;
}

bool moreQuadrant(const type &lhs, const type &rhs)
{
    return quadrant(lhs) > quadrant(rhs);
}

// utility functions
void showPoints(const type a[], int end, int begin = 0, ostream &out = cout);
void shuffle(type a[], int end, int begin = 0);               // randomly shuffles the given array
void copia(const type a[], type c[], int end, int begin = 0); // copy (a range of) an array
type getRandom()                                              // get a random element
{
#define MAX_COORD 1000.0
#define MIN_COORD -1000.0
    double x = (MIN_COORD + rand() * (MAX_COORD - MIN_COORD) / RAND_MAX);
    double y = (MIN_COORD + rand() * (MAX_COORD - MIN_COORD) / RAND_MAX);
    return getPunto(x, y);
}
void initRandom(type a[], int end, int begin = 0) // randomly init the given array
{
    for (size_t i = begin; i < end; i++)
    {
        a[i] = getRandom();
    }
}

// sorting functions with possibly custom compare function
void sortBy(type a[], int end, int begin, compare lessBy); // full sorting, iterative + optimization on end and begin

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    const size_t numPoints = 10;

    type v[numPoints], a[numPoints];

    initRandom(v, numPoints, 0);

    cout << "by distance" << endl;
    copia(v, a, numPoints); // make a copy
    sortBy(a, numPoints, 0, lessDistantFromOrigin);
    showPoints(a, numPoints);
    cout << endl;

    cout << "by quadrant" << endl;
    copia(v, a, numPoints); // make a copy
    sortBy(a, numPoints, 0, moreQuadrant);
    showPoints(a, numPoints);
    cout << endl;

    return 0;
}

/// @brief Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
/// elementi da begin a end escluso: [begin, end)
/// @details sortIterative with last and first swap optimization
/// @param a     l'array con i valori da ordinare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param lessBy la funzione di confronto, per default lessThan
// void sortBy(type a[], int end, int begin /* = 0 */, compare lessBy /* = lessThan */)
void sortBy(type a[], int end, int begin /* = 0 */, bool lessBy(const type &, const type &) /* = lessThan */)
{
    int limit = begin;      // remember array start limit
    while (end - begin > 1) // at least two element
    {
        int lastSwap = 0, firstChanged = end;
        for (int i = begin + 1; i < end; ++i)
        {
            if (lessBy(a[i], a[i - 1]))
            {
                swap(a[i], a[i - 1]); // something's wrong here: let's fix it
                lastSwap = i;         // remember last swap
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

/// @brief Output su out in formato showPoints da begin a end escluso: [begin, end)
/// @param a     the array to output
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param out   the output stream to be used
void showPoints(const type a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
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

/// @brief Copia gli elementi da begin a end escluso: [begin, end)
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

/// @brief Mescola gli elementi da begin a end escluso: [begin, end)
/// @param a     l'array da mescolare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void shuffle(type a[], int end, int begin /* = 0 */)
{
    while (end - begin > 1)
    {
        int random = begin + rand() % (end - begin); // one element at random
        --end;                                       // adjust position
        swap(a[end], a[random]);                     // swap
    }
}
