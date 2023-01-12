/**
 * Purpose: basic utilities for arrays
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2022/11/27
 * Note:
 */

/*
## Radice intera ( isqrt )
### Descrizione del problema
È dato un numero naturale n di cui si deve calcolare la radice intera, ovvero il massimo numero naturale x tale che x<sup>2</sup> <= n.

Scrivere un programma che calcoli la radice intera di un numero dato.

**Assunzione**: 0 ≤ n ≤ 10<sup>18</sup>.

**Formato di input**: leggere n da tastiera (con controlli di validità).

**Formato di output**: il risultato richiesto, cioè la radice intera di n, in forma decimale.
Esempi:
Input Output
6 2
1 1
121 11
**Esempi**:
| Input | Output | Note                                       |
| ----- | ------ | ------------------------------------------ |
| 6     | 2      | 2<sup>2</sup> = 4, 3<sup>2</sup> = 9       |
| 1     | 1      | 1<sup>2</sup> = 1, 2<sup>2</sup> = 4       |
| 121   | 11     | 11<sup>2</sup> = 121, 12<sup>2</sup> = 144 |

*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

long long int getIntInRange(const char *prompt, long long int min, long long int max);

unsigned long long int isqrt(unsigned long long int n)
{
    unsigned long long int result;
    // poiché n in [0, 2^64) : 0 <= n < 2^64
    // sqrt(n) in [0, 2^32) : 0 <= n < 2^32
    // intervallo di ricerca [begin, end) : begin <= sqrt(n) < end
    unsigned long long int begin = 0, end = 1LL << 32;
    while (end - begin > 1) // ricerca non finita: più di un valore possibile
    {
        unsigned long long int middle = begin + (end - begin) / 2;
        unsigned long long int square = middle * middle;
        if (DEBUG)
        {
            cout << "[" << begin << ", " << end << "): middle = " << middle << ", square = " << square << endl;
        }
        if (square < n)
        {
            begin = middle;
        }
        else if (square > n)
        {
            end = middle;
        }
        else
        { // square == n
            begin = middle;
            end = middle + 1;
        }
    }
    // qui l'intervallo è ridotto a [begin, begin + 1)
    result = begin;
    return result;
}

unsigned long long int icbrt(unsigned long long int n)
{
    unsigned long long int result;
    unsigned long long int begin = 0, end = 2641856;
    while (end - begin > 1) // ricerca non finita: più di un valore possibile
    {
        unsigned long long int middle = begin + (end - begin) / 2;
        unsigned long long int cube = middle * middle * middle;
        if (DEBUG)
        {
            cout << "[" << begin << ", " << end << "): middle = " << middle << ", cube = " << cube << endl;
        }
        if (cube < n)
        {
            begin = middle;
        }
        else if (cube > n)
        {
            end = middle;
        }
        else
        { // cube == n
            begin = middle;
            end = middle + 1;
        }
    }
    result = begin;
    return result;
}

// main function
int main(int argc, char *argv[])
{
    unsigned long long int n = getIntInRange("Immetti n: ", 0, 1'000'000'000'000'000'000);
    cout << "sqrt(" << n << ") = " << isqrt(n) << endl;
    cout << "cbrt(" << n << ") = " << icbrt(n) << endl;

    // successful termination
    return 0;
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
