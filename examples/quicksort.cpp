/**
 * Purpose: quick sort with array of struct and different comparison functions
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/04/15
 * Note:
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

struct planet // the struct we are working with
{
    char name[10 + 1]; // planet name (max 10 chars)
    double mass;       // mass in kg
    double distance;   // distance from Sun in km
    bool inhabited;    // inhabited (usually false)
    int numSatellites; // number of satellites
};

const planet planets[] = { // the array of planets
    {"Mars", 6.4171E23, 206700000, false, 2},
    {"Jupiter", 1.8982E27, 740520000, false, 79},
    {"Mercury", 3.3011E23, 46001200, false, 0},
    {"Venus", 4.8675E24, 107477000, false, 0},
    {"Earth", 5.9726E24, 147098074, true, 1},
    {"Saturn", 5.6834E26, 1352550000, false, 1'000'000},
    {"Uranus", 8.6810E25, 2.742E9, false, 27},
    {"Neptune", 1.02413E26, 4.5E9, false, 14}};

const size_t numPlanets = sizeof(planets) / sizeof(planet); // array dimension

using namespace std;

// overload dell'operatore << per output in JSON format
ostream &operator<<(ostream &os, const planet &p)
{
    os << "{ \"name\": \"" << p.name << "\"";
    os << ", \"mass\": " << p.mass;
    os << ", \"distance\": " << p.distance;
    os << ", \"inhabited\": " << (p.inhabited ? "true" : "false");
    os << ", \"numSatellites\": " << p.numSatellites;
    os << "}";
    os << endl; // sorry about it
    return os;
}

// overload dell'operatore < per confronto lessicografico
bool operator<(const planet &lhs, const planet &rhs)
{
    return strcmp(lhs.name, rhs.name) < 0;
}

const bool DEBUG = true;

using type = planet;

// global operation counters
size_t comparisons = 0;                 // n° of comparisons
size_t swaps = 0;                       // n° of swaps
void showOperations(bool reset = true); // utility to show and maybe reset counters

using compare = bool (*)(const type &lhs, const type &rhs); // definition of comparison function type

bool lessThan(const type &lhs, const type &rhs); // default comparison function lessThan(lhs, rhs) = lhs < rhs
bool lessThan(const type &lhs, const type &rhs)
{
    ++comparisons;
    return lhs < rhs;
}

bool lessThanByMass(const type &lhs, const type &rhs); // comparison function by mass
bool lessThanByMass(const type &lhs, const type &rhs)
{
    ++comparisons;
    return lhs.mass < rhs.mass;
}

bool lessThanBySatellites(const type &lhs, const type &rhs); // comparison function by satellite number
bool lessThanBySatellites(const type &lhs, const type &rhs)
{
    ++comparisons;
    return lhs.numSatellites < rhs.numSatellites;
}

// swap function scambio(lhs, rhs)
void scambio(type &lhs, type &rhs);
void scambio(type &lhs, type &rhs)
{
    ++swaps;
    swap(lhs, rhs);
}

// utility functions
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON
void shuffle(type a[], int end, int begin = 0);                         // randomly shuffles the given array
void copia(const type a[], type c[], int end, int begin = 0);           // copy (a range of) an array

// sorting functions with possibly custom compare function
void quickSort(type a[], int end, int begin = 0, compare lessBy = lessThan);
bool isOrdered(const type a[], int end, int begin = 0, compare lessBy = lessThan);

const int NUM_COMPARE = 3; // # of compare functions

// basic sorting test
void test(type v[], int dim, int which);

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    type v[numPlanets]; // working copy of the planets array

    for (int comp = 1; comp <= NUM_COMPARE; ++comp)
    {
        copia(planets, v, numPlanets); // make a copy
        shuffle(v, numPlanets);
        cout << "start with randomly ordered planets:" << endl;
        JSON(v, numPlanets);
        cout << endl;
        test(v, numPlanets, comp);
    }

    copia(planets, v, numPlanets); // make a copy
    shuffle(v, numPlanets);
    cout << "start with randomly ordered planets:" << endl;
    JSON(v, numPlanets);
    cout << endl;
    // Since the sorting algorithm is stable, we can do
    // sorting with multiple criteria in reverse order of importance
    cout << "Since the sorting algorithm is stable, we can do" << endl;
    cout << "sorting with multiple criteria in reverse order of importance" << endl;
    quickSort(v, numPlanets, 0, lessThan); // just in case of equal number of satellites
    quickSort(v, numPlanets, 0, lessThanBySatellites);
    cout << "After sort with lessThan and then with lessThanBySatellites: " << endl;
    JSON(v, numPlanets);
    showOperations();
    // of course, I could define a compare function to consider all the criteria at once
    // and that would reduce the number of operations involved, but...

    return 0;
}

/// @brief Partizionamento (crescente) degli elementi da begin a end escluso: [begin, end)
/// @details left tale che: a[i] < a[left] per i < left, a[i] >= a[left] per i >= left
/// @param a     l'array con i valori da partizionare
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param lessBy la funzione di confronto, per default lessThan
/// @return left: l'indice dell'elemento pivot
size_t partition(type a[], int end, int begin = 0, compare lessBy = lessThan)
{
    type pivot = a[end - 1]; // simple pivot selection, non optimal
    size_t left = begin, right = end - 2;
    do
    {
        while (lessBy(a[left], pivot)) // first not less than pivot
            left++;
        while (left < right && !lessBy(a[right], pivot)) // last less than pivot
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
void quickSort(type a[], int end, int begin /* = 0 */, bool lessBy(const type &, const type &) /* = lessThan */)
{
    if (end - begin > 1) // at least two element
    {
        // partition
        size_t left = partition(a, end, begin, lessBy);
        // recurse lower part
        quickSort(a, left, begin, lessBy);
        // recurse higher part
        quickSort(a, end, left + 1, lessBy);
    }
}

void sortIt(type v[], int dim, int which)
{
    switch (which)
    {
    case 1:
        cout << "After sort with lessThan: " << endl;
        quickSort(v, dim, 0, lessThan);
        showOperations();
        cout << "Ordered? " << (isOrdered(v, dim, 0, lessThan) ? "yes" : "no") << endl;
        break;
    case 2:
        cout << "After sort with lessThanByMass: " << endl;
        quickSort(v, dim, 0, lessThanByMass);
        showOperations();
        cout << "Ordered? " << (isOrdered(v, dim, 0, lessThanByMass) ? "yes" : "no") << endl;
        break;
    case 3:
        cout << "After sort with lessThanBySatellites: " << endl;
        quickSort(v, dim, 0, lessThanBySatellites);
        showOperations();
        cout << "Ordered? " << (isOrdered(v, dim, 0, lessThanBySatellites) ? "yes" : "no") << endl;
        break;
    }
    JSON(v, dim);
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

/// @brief Verifica ordinamento (crescente) elementi da begin a end escluso: [begin, end)
/// @param a     l'array con i valori di cui verificare l'ordinamento
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return      true se gli elementi sono ordinati, false altrimenti
/// @param lessBy la funzione di confronto, per default lessThan
bool isOrdered(const type a[], int end, int begin /* = 0 */, compare lessBy /* = lessThan */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        if (lessBy(a[i], a[i - 1])) // something's wrong here
            return false;
    }
    return true;
}
