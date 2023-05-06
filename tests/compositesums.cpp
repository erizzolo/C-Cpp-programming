/*
 * Somme di numeri compositi (compositesums)
 * Author:  ER
 * Date:    2023/04/29
 * Note:
 */

/*
Somme di numeri compositi (compositesums)
Quasi ogni numero naturale N è rappresentabile come somma di zero o più
numeri compositi diversi. Si ricorda che i numeri compositi sono i numeri minori
o uguali ad 1 oppure divisibili per qualche altro numero naturale diverso da se
stessi e dall’unità, e la successione dei numeri compositi è Ci:
0, 1, 4, 6, 8, 9, 10, 12, 14, 15, … per i = 1 …
Ad esempio, il numero N = 31 è rappresentabile come:
N = 31 = 15 + 12 + 4 = C10 + C8 + C3
N = 31 = 14 + 9 + 8 = C9 + C6 + C5
e, forse, in altri modi ancora ...
Date M stringhe di caratteri '0' ed '1', in cui l'i-esimo carattere della stringa (la
posizione del primo carattere della stringa è i = 1) indica la presenza o meno
dell'i-esimo numero composito nella somma, determinare la rappresentazione
decimale del numero N corrispondente a ciascuna stringa.
Ad esempio, data la stringa S = “0010000101”, in cui il 3°, 8° e 10° carattere
sono '1', essa corrisponde alla somma C3 + C8 + C10 e quindi il numero N
corrispondente è, in notazione decimale, 31.
Allo stesso modo, data la stringa S = “000011001”, il numero N
corrispondente è, in notazione decimale, 31.
Assunzione: 0 ≤ N ≤ 1011, 1 < |S| < 50, 1 ≤ M ≤ 100.
Formato di input: la prima linea contiene il numero intero M. Le M successive
linee contengono ciascuna una stringa S. Ogni stringa consiste di una sequenza
di |S| caratteri '0' oppure '1'.
Formato di output: M righe contenenti ciascuna il numero N corrispondente a
ciascuna stringa.
Esempi:
Input       Output  Spiegazione
2           31      Esempio del testo.
0010000101  31      Esempio del testo.
000011001

Nota: con |S| si indica la lunghezza della stringa S.
*/

#include <iostream>

using namespace std;

const bool DEBUG = true;

#define MAX_TESTS 100 // maximum number of tests
#define MAX_LENGTH 49 // maximum string length

// basic numeric type
using number = unsigned long long int;

// prototipi delle funzioni
bool isPrime(number n);

// the main function
int main(int argc, char *args[])
{
    // setup prime numbers
    number composites[MAX_LENGTH + 1]; // composite numbers
    number p = 0;                      // start with 0
    for (size_t f = 0; f <= MAX_LENGTH;)
    {
        if (!isPrime(p))
        {
            composites[f] = p;
            ++f;
        }
        p++;
    }
    number M;
    cin >> M;
    char stringa[MAX_LENGTH + 1];
    // cin.getline(stringa, sizeof(stringa));   // reads first newline
    for (int t = 0; t < M; ++t)
    {
        cin >> stringa;
        // cin.getline(stringa, sizeof(stringa));
        number n = 0;
        size_t i = 0;
        while (stringa[i] != 0)
        {
            if (stringa[i] == '1')
            {
                n += composites[i];
            }
            ++i;
        }
        cout << n << endl;
    }

    // successful termination
    return 0;
}

number sqrt(number n)
{
    number result = 0, step = 1LL << 31;
    while (step > 0)
    {
        number test = result + step;
        if (test * test <= n)
        {
            result = test;
        }
        step /= 2;
    }
    return result;
}

/// @brief Restituisce true se n è primo, false altrimenti (fast version)
/// @param n il numero di cui si verifica la primalità
/// @return true se n è primo, false altrimenti
bool isPrime(number n)
{
    bool prime = n > 1; // no 0 e 1
    if (prime)
    {
        long long int factor = 2, limit = sqrt(n);
        while (factor <= limit && prime)
        {
            prime = n % factor != 0;
            ++factor;
        }
    }
    return prime;
}
