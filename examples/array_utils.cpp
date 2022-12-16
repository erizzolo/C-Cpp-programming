/**
 * Purpose: basic utilities for arrays
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2022/11/27
 * Note:
 */

#include <iostream>
#include <ctime>
using namespace std;

const bool DEBUG = true;
/**
 * Si chiede di implementare le funzioni di seguito elencate,
 * basandosi sullo schema della funzione forwardScan (o backWardScan se necessario).
 * Aggiungere dei semplici test con array inizializzati nel codice.
 */

using type = int;

// basic scan prototypes with default parameter begin
void forwardScan(type a[], int end, int begin = 0);  // scansione crescente da begin a end escluso: [begin, end)
void backwardScan(type a[], int end, int begin = 0); // scansione decrescente da end escluso a begin: [begin, end)
// applicazione delle precedenti scansioni per la visualizzazione di un array
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON

// Utility functions
// Initializing
void fill(type a[], type value, int end, int begin = 0);
void iota(type a[], type value, int end, int begin = 0);
// Modifying
void add(type a[], type value, int end, int begin = 0);
// Searching
int firstIndexOf(type a[], type value, int end, int begin = 0);
int lastIndexOf(type a[], type value, int end, int begin = 0);
int count(type a[], type value, int end, int begin = 0);
type max(type a[], int end, int begin = 0);
type min(type a[], int end, int begin = 0);

void fillRandom(type a[], type min, type max, int end, int begin = 0);

bool isOrdered(type a[], int end, int begin = 0);

void orderArray(type a[], int end, int begin = 0);

// main function
int main(int argc, char *argv[])
{
    srand(time(NULL));
    const int SIZE = 10;
    type primes[SIZE] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // 10 prime numbers
    cout << "Here are some primes:" << endl;
    JSON(primes, SIZE);
    cout << endl;


    cout<<endl<<"Is the array ordered?"<<endl;
    bool  result = isOrdered(primes, SIZE);
    cout<<result<<endl;

    cout << "Setting all elements to 11:" << endl;
    fill(primes, 11, SIZE);
    JSON(primes, SIZE);
    cout << endl;

    cout << "Counting value 11: " << count(primes, 11, SIZE) << endl;
    cout << "Counting value 111: " << count(primes, 111, SIZE) << endl;

    cout << "Setting all elements equals to their index:" << endl;
    iota(primes, 0, SIZE);
    JSON(primes, SIZE);
    cout << endl;

    cout << "Finding first 5: " << firstIndexOf(primes, 5, SIZE) << endl;
    cout << "Finding last 5: " << lastIndexOf(primes, 5, SIZE) << endl;
    cout << "Finding last 0: " << lastIndexOf(primes, 0, SIZE) << endl;
    cout << "Finding last 50: " << lastIndexOf(primes, 50, SIZE) << endl;


    cout << "Minimum element: " << min(primes, SIZE) << endl;
    cout << "Maximum element: " << max(primes, SIZE) << endl;


    cout << "Adding 3 to all elements:" << endl;
    add(primes, 3, SIZE);
    JSON(primes, SIZE);
    cout << endl;
    cout << "Setting all elements to random:" << endl;
    fillRandom(primes, 1, 100, SIZE);
    JSON(primes, SIZE);

    cout<<endl<<"Is the array ordered?"<<endl;
    result = isOrdered(primes, SIZE);
    cout<<result<<endl;

    cout<<"Ordered Array: "<<endl;
    orderArray(primes,SIZE);
    JSON(primes,SIZE);
    cout << endl;
    // and so on ....
    // successful termination
    return 0;
}

/// @brief Restituisce l'indice del primo elemento uguale a value in [begin, end), oppure end
/// @param a     the array to scan
/// @param value the value to be found
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il minimo indice per cui a[i] == value, oppure end
int firstIndexOf(type a[], type value, int end, int begin /* = 0 */)
{
//    // con sentinella
//    type saved = a[end - 1];    // salvo ultimo elemento
//    a[end - 1] = value; // metto la sentinella
//    while (a[begin] != value)
//    {
//        ++begin;
//    }
//    a[end - 1] = saved; // rimetto a posto
//    if(a[begin] != value) { // ultimo controllo
//        ++begin;
//    }
    while (begin < end && a[begin] != value)
    {
        ++begin;
    }
    return begin;
}

/// @brief Restituisce l'indice dell'ultimo elemento uguale a value in [begin, end), oppure end
/// @param a     the array to scan
/// @param value the value to be found
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il massimo indice per cui a[i] == value, oppure end
int lastIndexOf(type a[], type value, int end, int begin /* = 0 */)
{
    end--;
    while (begin <= end && a[end] != value)
    {
        if (DEBUG) cout << "end =" << end << endl;
        --end;
    }
    return end;
}

/// @brief Restituisce il minimo elemento in [begin, end)
/// Undefined behaviour se [begin, end) è vuoto
/// @param a     the array to scan
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il minimo elemento in [begin, end)
type min(type a[], int end, int begin /* = 0 */)
{
    type result = a [begin];
    for (int i = begin + 1; i < end; ++i)
    {

        if (a[i] < result)
            result = a[i];
    }
    return result;

}

/// @brief Restituisce il massimo elemento in [begin, end)
/// Undefined behaviour se [begin, end) è vuoto
/// @param a     the array to scan
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il massimo elemento in [begin, end)
type max(type a[], int end, int begin /* = 0 */)
{
    type result = a [begin];
    for (int i = begin + 1; i < end; ++i)
    {

        if (a[i] > result)
            result = a[i];
    }
    return result;
}

/// @brief Restituisce il numero di occorrenze di value in [begin, end)
/// @param a     the array to scan
/// @param value the value to be counted
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il numero di occorrenze di value in [begin, end)
int count(type a[], type value, int end, int begin /* = 0 */)
{
    int result = 0;
    for (int i = begin; i < end; ++i)
    {

        if (a[i] == value)
            ++result;
    }
    return result;
}

/// @brief Aggiunge value agli elementi in [begin, end)
/// @param a     the array to change
/// @param value the value of the increment
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void add(type a[], type value, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] += value;

    }
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

/// @brief Imposta gli elementi in [begin, end) al valore value
/// @param a     the array to change
/// @param value the value to set in each element
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void fill(type a[], type value, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = value;
    }
}

/// @brief Basic forward scan (with default limits)
/// scansione crescente da begin a end escluso: [begin, end)
/// @param a     the array to scan
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void forwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}

/// @brief Basic backward scan (with default limits)
/// scansione decrescente da end escluso a begin: [begin, end)
/// @param a     the array to scan
/// @param end   inizio (escluso) della scansione: a[end] non viene elaborato
/// @param begin fine (inclusa) della scansione: a[begin] e' l'ultimo elemento elaborato
void backwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = end; i-- > begin;)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
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
            out << ", ";
        out << a[i];
    }
    out << " ]";
}
void fillRandom(type a[], type min, type max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = rand() %(max - min + 1) +min;
    }
}
bool isOrdered(type a[], int end, int begin /* = 0 */)
{
//    bool result = true;
////    for (int i = begin +1; i < end; ++i)
//    for (int i = begin +1; i < end && result; ++i)
//    {
//        if (DEBUG)
//            cout<<a[i]<<" "<<a[i-1]<<endl;
//        if (a[i] < a[i-1])
//            result = false;
//    }
//    return result;
    for (int i = begin +1; i < end; ++i)
    {
        if (DEBUG)
            cout<<a[i]<<" "<<a[i-1]<<endl;
        if (a[i] < a[i-1])
            return false;
    }
    return true;
}
void orderArray(type a[], int end, int begin /* = 0 */)
{
    while(end > begin + 1)
    {
        for (int i = begin +1; i < end; ++i)
        {
            if (DEBUG)
                cout<<a[i]<<" "<<a[i-1]<<endl;
            if (a[i] < a[i-1])
            {
                int temp = a[i]; a[i] = a[i-1]; a[i-1] = temp;
            }
        }
        end--;
    }
}

