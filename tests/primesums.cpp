/*
 * Somme di primi (primesums)
 * Author:  ER
 * Date:    2023/04/29
 * Note:    Il secondo esempio e' errato:
 *          dovrebbe essere P6 + P5 + P4 e quindi "000111"
 */

/*
Somme di primi (primesums)
Quasi ogni numero naturale N è rappresentabile come somma di zero o più
numeri primi diversi. Si ricorda che i numeri primi sono i numeri maggiori di 1 e
divisibili solo per se stessi e per l’unità, e la successione dei numeri primi è Pi:
2, 3, 5, 7, 11, 13, 17, 19, 23, … per i = 1 …
Ad esempio, il numero N = 31 è rappresentabile come:
N = 31 = 17 + 11 + 3 = P7 + P5 + P2
N = 31 = 13 + 11 + 7 = P6 + P5 + P3
e, forse, in altri modi ancora ...
Date M stringhe di caratteri '0' ed '1', in cui l'i-esimo carattere della stringa (la
posizione del primo carattere della stringa è i = 1) indica la presenza o meno
dell'i-esimo numero primo nella somma, determinare la rappresentazione
decimale del numero N corrispondente a ciascuna stringa.
Ad esempio, data la stringa S = “0100101”, in cui il 2°, 5° e 7° carattere sono
'1', essa corrisponde alla somma P2 + P5 + P7 e quindi il numero N
corrispondente è, in notazione decimale, 31.
Allo stesso modo, data la stringa S = “001011”, il numero N corrispondente è,
in notazione decimale, 31.
Assunzione: 0 ≤ N ≤ 1011, 1 < |S| < 50, 1 ≤ M ≤ 100.
Formato di input: la prima linea contiene il numero intero M. Le M successive
linee contengono ciascuna una stringa S. Ogni stringa consiste di una sequenza
di |S| caratteri '0' oppure '1'.
Formato di output: M righe contenenti ciascuna il numero N corrispondente a
ciascuna stringa.
Esempi:
Input       Output  Spiegazione
2           31      Esempio del testo.
0100101     31      Esempio del testo.
001011

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
    number primes[MAX_LENGTH + 1]; // prime numbers
    number p = 2;   // start with 2
    for (size_t f = 0; f <= MAX_LENGTH; )
    {
        if(isPrime(p)) {
            primes[f] = p;
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
                n += primes[i];
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

