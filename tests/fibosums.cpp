/*
 * Rappresentazione numerica tramite numeri di Fibonacci
 * Author:  ER
 * Date:    2023/04/28
 * Note:
 */

/*
Somme di Fibonacci (fibosums)
Ogni numero naturale N è rappresentabile come somma di zero o più numeri di
Fibonacci diversi. Si ricorda che i numeri di Fibonacci Fi sono i numeri della
successione: 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, …
Ad esempio, il numero N = 31 è rappresentabile come:
N = 31 = 21 + 8 + 2 = F8 + F6 + F3
N = 31 = 13 + 8 + 5 + 3 + 1 + 1 = F7 + F6 + F5 + F4 + F2 + F1
e, forse, in altri modi ancora ...
Date M stringhe di caratteri '0' ed '1', in cui l'i-esimo carattere della stringa (la
posizione del primo carattere della stringa è i = 1) indica la presenza o meno
dell'i-esimo numero di Fibonacci nella somma, determinare la rappresentazione
decimale del numero N corrispondente a ciascuna stringa.
Ad esempio, data la stringa S = “00100101”, in cui il 3°, 6° ed 8° carattere
sono '1', essa corrisponde alla somma F3 + F6 + F8 e quindi il numero N
corrispondente è, in notazione decimale, 31.
Allo stesso modo, data la stringa S = “1101111”, il numero N corrispondente è,
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
00100101    31      Esempio del testo.
1101111

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
number fibonacciIterativo(number n);
// number fibonacciRicorsivo(number n); NOT to be used !!!
number fibonacciRicorsivoMemoization(number n);

// the main function
int main(int argc, char *args[])
{
    // setup fibonacci numbers
    number fibonacci[MAX_LENGTH + 1]; // fibonacci numbers
    for (size_t f = 0; f <= MAX_LENGTH; f++)
    {
        fibonacci[f] = fibonacciIterativo(f);
    }
    // better
    fibonacci[0] = fibonacci[1] = 1;
    for (size_t f = 2; f <= MAX_LENGTH; f++)
    {
        fibonacci[f] = fibonacci[f - 1] + fibonacci[f - 2];
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
                n += fibonacci[i];
            }
            ++i;
        }
        cout << n << endl;
    }

    // successful termination
    return 0;
}

number fibonacciIterativo(number n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        number k = 2;               // current
        number f_k_2 = 0;           // f[k-2]
        number f_k_1 = 1;           // f[k-1]
        number f_k = f_k_1 + f_k_2; // f[k]
        while (k < n)
        {
            // compute next
            k++;
            f_k_2 = f_k_1;
            f_k_1 = f_k;
            f_k = f_k_1 + f_k_2;
        }
        return f_k;
    }
}

number fibonacciRicorsivo(number n)
{
    if (DEBUG)
    {
        cout << "--> fibonacciRicorsivo(" << n << ")." << endl;
    }
    return n < 2 ? n : fibonacciRicorsivo(n - 1) + fibonacciRicorsivo(n - 2);
}

number fibonacciRicorsivoMemoization(number n)
{
    static number soluzioni[MAX_LENGTH + 1];
    if (DEBUG)
    {
        cout << "--> fibonacciRicorsivoMemoization(" << n << ")." << endl;
    }
    if (n < 2)
        return n;
    if (soluzioni[n] == 0)
    { // not solved yet
        soluzioni[n] = fibonacciRicorsivoMemoization(n - 1) + fibonacciRicorsivoMemoization(n - 2);
    }
    return soluzioni[n];
}
