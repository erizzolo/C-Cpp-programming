/**
 * Purpose: test 2023-05-19
 * Author:  Emanuele Rizzolo
 * Class:   3AIN
 * Date:    2023/05/19
 * Note:
 */

/*
Fusione (fusion)
Realizzare un’applicazione che consenta di effettuare la fusione di due array
ordinati in un unico array anch’esso ordinato. Implementare quindi una
funzione merge che, dati due array V1 e V2, rispettivamente di N1 ed N2
elementi, inserisca tutti gli elementi dei due array in un unico array V di
N = N1 + N2 elementi in modo tale che anche l’array V sia ordinato allo stesso
modo di V1 (anche se V2 è ordinato in modo diverso).
Ad esempio, dato N1 = 6, V1 = [1, 2, 2, 5, 7, 9], N2 = 3, V2 = [1, 3, 8], la
funzione deve assegnare gli N = 9 elementi dell’array V in modo tale che
V = [1, 1, 2, 2, 3, 5, 7, 8, 9].
Ad esempio, dato N1 = 4, V1 = [9, 6, 5, 5], N2 = 3, V2 = [1, 2, 8], la funzione
deve assegnare gli N = 7 elementi dell’array V in modo tale che
V = [9, 8, 6, 5, 5, 2, 1].
L’applicazione deve implementare la funzione merge con opportuni parametri
e consentire all’utente di testarla facendogli inserire i due array V1 e V2 da
tastiera (si suppone che gli elementi, di tipo double, siano ordinati) e
visualizzando il risultante array V.
*/
#include <iostream>
#include <limits>
using namespace std;

const bool DEBUG = true;

using type = int;

long long int getIntInRange(const char *prompt, long long int min, long long int max);

void fusion(const type v1[], size_t N1, const type v2[], size_t N2, type v[]);
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON
void copia(const type a[], type c[], int end, int begin = 0);           // copy (a range of) an array
void fillFromKeyboard(type a[], type min, type max, int end, int begin = 0);
void reverse(type a[], int end, int begin = 0); // rovescia l'ordine degli elementi

void test(const type v1[], size_t N1, const type v2[], size_t N2)
{
    cout << "Array originale v1: ";
    JSON(v1, N1);
    cout << endl;
    cout << "Array originale v2: ";
    JSON(v2, N2);
    cout << endl;
    type *v = new type[N1 + N2]; // assume ok
    fusion(v1, N1, v2, N2, v);
    cout << "Array risultante v: ";
    JSON(v, N1 + N2);
    cout << endl;
    delete[] v;
}

// main function
int main(int argc, char *argv[])
{
    size_t N1 = 6, N2 = 3;
    type v1[N1]{1, 2, 2, 5, 7, 9}, v2[N2]{1, 3, 8};
    test(v1, N1, v2, N2);

    N1 = 4;
    N2 = 3;
    type V1[N1]{9, 6, 5, 5};
    type V2[N2]{1, 2, 8};
    test(V1, N1, V2, N2);

    N1 = getIntInRange("Immetti N1: ", 2, numeric_limits<int>::max());
    type *b1 = new type[N1];
    fillFromKeyboard(b1, numeric_limits<int>::min(), numeric_limits<int>::max(), N1);
    N2 = getIntInRange("Immetti N2: ", 2, numeric_limits<int>::max());
    type *b2 = new type[N2];
    fillFromKeyboard(b2, numeric_limits<int>::min(), numeric_limits<int>::max(), N2);
    test(b1, N1, b2, N2);
    delete[] b1;
    delete[] b2;

    return 0;
}
bool myLess(const type &lhs, const type &rhs)
{
    return lhs < rhs;
}
bool more(const type &lhs, const type &rhs)
{
    return lhs > rhs;
}
using comp = bool (*)(const type &lhs, const type &rhs);
/// @brief merge ascending arrays v1 and v2 into ascending v
/// @param v1   first array to process
/// @param N1   numero di elementi di v1
/// @param v2   second array to process
/// @param N2   numero di elementi di v2
/// @param v    destination array (with N1 + N2 elements)
void merge(const type v1[], size_t N1, const type v2[], size_t N2, type v[], comp cmp)
{
    size_t i1 = 0;             // index in v1
    size_t i2 = 0;             // index in v2
    size_t i = 0;              // index in v
    while (i1 < N1 && i2 < N2) // both arrays to consider
    {
        if (cmp(v1[i1], v2[i2]))
        {
            v[i] = v1[i1];
            i++, i1++;
        }
        else
        {
            v[i] = v2[i2];
            i++, i2++;
        }
    }
    while (i1 < N1) // copy rest of v1
    {
        v[i] = v1[i1];
        i++, i1++;
    }
    while (i2 < N2) // copy rest of v2
    {
        v[i] = v2[i2];
        i++, i2++;
    }
}

/// @brief merge ordered arrays v1 and v2 into ordered v
/// @param v1   first array to process
/// @param N1   numero di elementi di v1
/// @param v2   second array to process
/// @param N2   numero di elementi di v2
/// @param v    destination array (with N1 + N2 elements)
void fusion(const type v1[], size_t N1, const type v2[], size_t N2, type v[])
{
    if (v1[0] > v1[N1 - 1]) // v1 descending
    {
        if (v2[0] < v2[N2 - 1]) // v2 ascending
        {
            type *t = new type[N2];
            copia(v2, t, N2);
            reverse(t, N2);
            merge(v1, N1, t, N2, v, more);
            delete[] t;
        }
        else
            merge(v1, N1, v2, N2, v, more);
    }
    else
    {
        if (v2[0] > v2[N2 - 1]) // v2 descending
        {
            type *t = new type[N2];
            copia(v2, t, N2);
            reverse(t, N2);
            merge(v1, N1, t, N2, v, myLess);
            delete[] t;
        }
        else
            merge(v1, N1, v2, N2, v, myLess);
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

