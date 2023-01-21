/**
 * Purpose: test 2023-01-14
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/01/21
 * Note:
 */

#include <iostream>
#include <ctime>
#include <limits>

using namespace std;

const bool DEBUG = true;
/**
Multipli (multiples)
Si realizzi una funzione con il prototipo:
void multiples(int a[], int base, int dim);
che assegni agli elementi dell’array a con indice da 0 a dim – 1 i valori dei
successivi multipli interi del valore base in modo tale che a[indice] risulti pari a
base * indice.
Ad es. dato l’array dichiarato come
int multipli[10];
dopo la chiamata alla funzione powers seguente
multiples(multipli, 2, 10);
l’array multipli deve risultare uguale a quello così inizializzato
int mult[10] {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
ovvero contenere i valori dei primi 10 multipli di 2, in ordine crescente.
Realizzare un’applicazione che consenta all’utente di verificare la correttezza
della funzione, immettendo da tastiera il valore della base ed il numero di
elementi dell’array e visualizzando il contenuto dell’array ottenuto.
Assunzione: -100 <= base <= 100, 1 <= numero elementi <= 10.
Formato di input: leggere da tastiera (con controllo di validità) il valore della
base ed il valore del numero elementi.
*/

// basic scan prototypes with default parameter begin
void forwardScan(int a[], int end, int begin = 0);  // scansione crescente da begin a end escluso: [begin, end)
void backwardScan(int a[], int end, int begin = 0); // scansione decrescente da end escluso a begin: [begin, end)
// applicazione delle precedenti scansioni per la visualizzazione di un array
void JSON(const int a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON

// Utility functions
// Initializing
void fill(int a[], int value, int end, int begin = 0);
void iota(int a[], int value, int end, int begin = 0);
// Modifying
void add(int a[], int value, int end, int begin = 0);
// Searching
int firstIndexOf(int a[], int value, int end, int begin = 0);
int lastIndexOf(int a[], int value, int end, int begin = 0);
int count(int a[], int value, int end, int begin = 0);
int max(int a[], int end, int begin = 0);
int min(int a[], int end, int begin = 0);

void fillRandom(int a[], int min, int max, int end, int begin = 0);

bool isOrdered(int a[], int end, int begin = 0);

void orderArray(int a[], int end, int begin = 0);

long long int getIntInRange(const char *prompt, long long int min, long long int max);

void multiples(int a[], int base, int dim);

// main function
int main(int argc, char *argv[])
{
    int base = getIntInRange("Base: ", -100, 100);
    int elementi = getIntInRange("Numero di elementi: ", 0, 10);
    //    cout << base << " " << elementi << endl;
    int resti[elementi];
    multiples(resti, base, elementi);
    JSON(resti, elementi);
    // successful termination
    return 0;
}

/// @brief Restituisce l'indice del primo elemento uguale a value in [begin, end), oppure end
/// @param a     the array to scan
/// @param value the value to be found
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @return il minimo indice per cui a[i] == value, oppure end
int firstIndexOf(int a[], int value, int end, int begin /* = 0 */)
{
    //    // con sentinella
    //    int saved = a[end - 1];    // salvo ultimo elemento
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
int lastIndexOf(int a[], int value, int end, int begin /* = 0 */)
{
    end--;
    while (begin <= end && a[end] != value)
    {
        if (DEBUG)
            cout << "end =" << end << endl;
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
int min(int a[], int end, int begin /* = 0 */)
{
    int result = a[begin];
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
int max(int a[], int end, int begin /* = 0 */)
{
    int result = a[begin];
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
int count(int a[], int value, int end, int begin /* = 0 */)
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
void add(int a[], int value, int end, int begin /* = 0 */)
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
void iota(int a[], int value, int end, int begin /* = 0 */)
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
void fill(int a[], int value, int end, int begin /* = 0 */)
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
void forwardScan(int a[], int end, int begin /* = 0 */)
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
void backwardScan(int a[], int end, int begin /* = 0 */)
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
void JSON(const int a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
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
void fillRandom(int a[], int min, int max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = rand() % (max - min + 1) + min;
    }
}
bool isOrdered(int a[], int end, int begin /* = 0 */)
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
    for (int i = begin + 1; i < end; ++i)
    {
        if (DEBUG)
            cout << a[i] << " " << a[i - 1] << endl;
        if (a[i] < a[i - 1])
            return false;
    }
    return true;
}
void orderArray(int a[], int end, int begin /* = 0 */)
{
    while (end > begin + 1)
    {
        for (int i = begin + 1; i < end; ++i)
        {
            if (DEBUG)
                cout << a[i] << " " << a[i - 1] << endl;
            if (a[i] < a[i - 1])
            {
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
            }
        }
        end--;
    }
}

/// @brief Acquisisce un intero nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
long long int getIntInRange(const char *prompt, long long int min, long long int max)
{
    long long int result = 0; // assegno un valore non valido
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (min <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a number in [" << min << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}

void multiples2(int a[], int base, int dim)
{
    a[0] = 0;    // entro i limiti ???
    a[1] = base; // entro i limiti ???
    for (int i = 2; i < dim; ++i)
    {
        a[i] = a[i - 1] + base;
    }
}

void multiples(int a[], int base, int dim)
{
    int mult = 0;
    for (int i = 0; i < dim; ++i)
    {
        //        a[i] = i * base;
        a[i] = mult;
        mult += base;
    }
}
