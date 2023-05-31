/**
 * Purpose: test 2023-05-19
 * Author:  Emanuele Rizzolo
 * Class:   3AIN
 * Date:    2023/05/19
 * Note:
 */

/*
Somma consecutivi (sums)
Realizzare un’applicazione che consenta di verificare se, dato un array v di N
valori positivi di tipo int ed un valore obiettivo T, esiste un intervallo [min, max]
di indici tale che la somma degli elementi v[i] con i compreso nell’intervallo
[min, max] sia pari al valore obiettivo.
La funzione di verifica, interval, deve restituire una struct con i seguenti
componenti:
◦ found: valore booleano indicante l’esito della ricerca;
◦ min: l’estremo inferiore dell’intervallo;
◦ max: l’estremo superiore dell’intervallo.
Le componenti min e max non sono significative se found è false.
Se vi sono più di tali intervalli, la funzione deve restituire quello con valore min
minimo.
Ad esempio, dato N = 6, T = 1 e l’array v: [1, 3, 2, 5, 3, 9], la funzione deve
restituire { found: true, min = 0, max = 0}; infatti la somma degli elementi con
indice nell’intervallo [0, 0] è v[0] = 1 = T.
Ad esempio, dato N = 6, T = 10 e l’array v: [1, 3, 2, 5, 3, 9], la funzione deve
restituire { found: true, min = 1, max = 3}; infatti la somma degli elementi con
indice nell’intervallo [1, 3] è v[1] + v[2] + v[3] = 3 + 2 + 5 = 10 = T.
Si noti che in questo caso T anche nell’intervallo [2, 4] permette di ottenere
come somma v[2] + v[3] + v[4] = 2 + 5 + 3 = 10 = T ma in questo caso
l’estremo inferiore dell’intervallo non è minimo.
Ad esempio, dato N = 6, T = 50 e l’array v: [1, 3, 2, 5, 3, 9], la funzione deve
restituire { found: false, min = ?, max = ?}; infatti tale somma non può essere
ottenuta per nessuno intervallo (? indica un valore non significativo).
L’applicazione deve implementare la funzione interval con opportuni
parametri e consentire all’utente di testarla facendogli inserire un array da
tastiera, l’obiettivo T della ricerca e visualizzando il risultato dell’esecuzione
della funzione sull’array e la somma effettuata.
Ad esempio, dato N = 6, T = 10 e l’array v: [1, 3, 2, 5, 7, 9], la funzione deve
restituire { found: true, min = 1, max = 3} e visualizzare che
v[1] + v[2] + v[3] = 3 + 2 + 5 = 10 = T.
*/
#include <iostream>
#include <limits>
using namespace std;

const bool DEBUG = true;

using type = int;

struct result_t
{
    bool found;
    size_t min;
    size_t max;
};

long long int getIntInRange(const char *prompt, long long int min, long long int max);

result_t search(const type v1[], size_t N1, type target);
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON
void copia(const type a[], type c[], int end, int begin = 0);           // copy (a range of) an array
void fillFromKeyboard(type a[], type min, type max, int end, int begin = 0);

void test(const type v1[], size_t N1, type target)
{
    cout << "Array : ";
    JSON(v1, N1);
    cout << endl;
    cout << "Target: " << target << endl;
    result_t result = search(v1, N1, target);
    cout << "result: " << (result.found ? "" : "not ") << "found";
    if (result.found)
    {
        cout << " at [" << result.min << ", " << result.max << "]; indeed: ";
        type sum = 0;
        for (size_t i = result.min; i <= result.max; i++)
        {
            if (i != result.min)
                cout << " + ";
            cout << v1[i];
            sum += v1[i];
        }
        cout << " = " << sum << (sum == target ? " == " : " != ") << target;
    }
    cout << endl;
}

// main function
int main(int argc, char *argv[])
{
    size_t N1 = 6;
    type v1[N1]{1, 3, 2, 5, 3, 9};
    test(v1, N1, 1);
    test(v1, N1, 10);
    test(v1, N1, 50);

    N1 = getIntInRange("Immetti N1: ", 2, numeric_limits<int>::max());
    type *b1 = new type[N1];
    fillFromKeyboard(b1, numeric_limits<int>::min(), numeric_limits<int>::max(), N1);
    int target = getIntInRange("Immetti target: ", 0, numeric_limits<int>::max());
    test(b1, N1, target);
    delete[] b1;

    return 0;
}

/// @brief search an interval [min, max] of elements with given sum
/// @param v1   array to process
/// @param N1   numero di elementi di v1
/// @param target somma obiettivo
result_t search(const type v1[], size_t N1, type target)
{
    size_t min = 0; // min of range
    size_t max = 0; // max of range
    type sum = v1[min];
    while (max < N1)
    {
        if (sum == target)
        {
            return {true, min, max};
        }
        else if (sum < target)
        {
            ++max;
            if (max < N1)
                sum += v1[max];  // update sum
        } else // sum > target
        {
            sum -=v1[min];   // update sum
            ++min;
        }
    }
    return {false, 0, 0};
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

/// @brief Acquisisce un type nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
type getTypeInRange(const char *prompt, type min, type max)
{
    type result;
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (min <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a type in [" << min << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}

/// @brief Inizializza gli elementi di a da begin a end - 1 con valori nell'intervallo [min, max] da tastiera
/// @param a     l'array da inizializzare
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void fillFromKeyboard(type a[], type min, type max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = getTypeInRange("", min, max);
    }
}
