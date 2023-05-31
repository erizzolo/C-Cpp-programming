/**
 * Purpose: test 2023-05-19
 * Author:  Emanuele Rizzolo
 * Class:   3BIN
 * Date:    2023/05/19
 * Note:
 */

/*
Media precedenti (previous)
Realizzare un’applicazione che consenta di modificare i dati rilevati da un
sensore e memorizzati in un array di N valori di tipo double, sostituendo in
un’opportuna funzione “average” a ciascuno dei valori nelle posizioni da S (S >
0) a N – 1 la media aritmetica tra il valore stesso e gli S valori precedenti.
Ad esempio, dato N = 6, S = 1 e l’array v: [1, 3, 2, 5, 7, 9], la funzione deve
modificare l’array riducendolo v: [1, 2, 2.5, 3.5, 6, 8]; infatti:
◦ nuovo v[1] = (v[1] + v[0]) / 2 = (3 + 1) / 2 = 2
◦ nuovo v[2] = (v[2] + v[1]) / 2 = (2 + 3) / 2 = 2.5
◦ nuovo v[3] = (v[3] + v[2]) / 2 = (5 + 2) / 2 = 3.5
e così via...
Ad esempio, dato N = 6, S = 2 e l’array v: [1, 3, 2, 5, 7, 9], la funzione deve
modificare l’array riducendolo v: [1, 3, 2, 3.333, 4.666, 7]; infatti:
◦ nuovo v[2] = (v[2] + v[1] + v[0]) / 3 = (2 + 3 + 1) / 3 = 2
◦ nuovo v[3] = (v[3] + v[2] + v[1]) / 3 = (5 + 2 + 3) / 3 = 3.333
◦ nuovo v[4] = (v[4] + v[3] + v[2]) / 3 = (7 + 5 + 2) / 3 = 4.666
e così via...
L’applicazione deve implementare la funzione “average” con opportuni
parametri e consentire all’utente di testarla facendogli inserire un array da
tastiera e visualizzando il risultato dell’esecuzione della funzione sull’array (o
una sua copia) per tutti i valori di S congrui con la dimensione dell’array.
*/

#include <iostream>
#include <limits>
using namespace std;

const bool DEBUG = true;

using type = double;

long long int getIntInRange(const char *prompt, long long int min, long long int max);
double getDoubleInRange(const char *prompt, double min, double max);

void average(type a[], int N, int S);
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON
void copia(const type a[], type c[], int end, int begin = 0);           // copy (a range of) an array

void test(const type a[], int N)
{
    cout << "Array originale: ";
    JSON(a, N);
    cout << endl;
    type *work = new type[N]; // assume ok
    for (int S = 1; S < N; S++)
    {
        copia(a, work, N);
        average(work, N, S);
        cout << "S: " << S << " -> ";
        JSON(work, N);
        cout << endl;
    }
    delete[] work;
}

// main function
int main(int argc, char *argv[])
{
    type a[]{1, 3, 2, 5, 7, 9};
    test(a, 6);

    int N = getIntInRange("Immetti N: ", 2, numeric_limits<int>::max());
    type *b = new type[N];
    for (size_t i = 0; i < N; i++)
    {
        cout << i;
        b[i] = getDoubleInRange(": ", -numeric_limits<double>::infinity(), numeric_limits<double>::infinity());
    }
    test(b, N);
    delete[] b;
    return 0;
}

/// @brief a[i] = average of a[i - S], ..., a[i]
/// @param a   the array to process
/// @param N   numero di elementi
/// @param S numero di precedenti da considerare
void average(type a[], int N, int S)
{
    type sum = 0;
    for (int i = 0; i < S; ++i)
    {
        sum += a[N - 1 - i];
    }
    // sum = sum of last S elements
    int avg = N - 1, next = N - 1 - S;
    while (next >= 0)
    {
        sum += a[next]; // include next element
        type current = a[avg];
        a[avg] = sum / (S + 1);
        sum -= current;
        avg--, next--;
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

/// @brief Acquisisce un double nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
double getDoubleInRange(const char *prompt, double min, double max)
{
    double result = 0;
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
